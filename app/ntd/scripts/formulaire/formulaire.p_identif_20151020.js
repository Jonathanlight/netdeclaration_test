
NTD.p_identif_20151020 = {

  onSelectModePaiement: function(elt) {
    elt = $(elt);
    $$('.paiement-box-tlra, .paiement-box-nopaiement').each(function(paiement_box){
      if (!$(paiement_box)) {
        return ;
      }
      paiement_box = $(paiement_box);
      paiement_box.hide();
      paiement_box.select('input, select').each(function(input) {
        $(input).writeAttribute({disabled: 'disabled'});
      });
    });

    if (elt && $F(elt)) {
      var mode = $F(elt);
      var index = 1;
      $$('.paiement-box-' + mode).each(function(paiement_box) {
        paiement_box = $(paiement_box);
        if (mode == 'tlra') {
          if (paiement_box.hasClassName('elt')) {
            if (paiement_box.down('select')) {
              paiement_box.down('select').observe('change', function(evt) {
                if (evt.target.getValue()) {
                  evt.target.up('.elt-select').removeClassName('no-print');
                }
                else {
                  evt.target.up('.elt-select').addClassName('no-print');
                }
              });
            }
          }
          paiement_box.show();
        }
        else {
          paiement_box.show();
        }
        paiement_box.select('input, select').each(function(input){
          $(input).removeAttribute('disabled');
        });
      });
    }
  },

  showPaiement:function(amount) {

    var initialize = true;
    $('table-p_identif_20151020_select_paiement').show();
    $('table-p_identif_20151020_select_paiement').select("input[name='p_identif_20151020_opts[payment]']").each(function(select_paiement){
      select_paiement = $(select_paiement);
      if (select_paiement.checked) {
        NTD.p_identif_20151020.onSelectModePaiement(select_paiement);
        initialize = false;
      }
    });
    if (initialize) {
      NTD.p_identif_20151020.onSelectModePaiement(null);
      $('select_paiement_tlra').click(null);
    }

    $('p_identif_20151020_HA').setValue(amount);
    $('p_identif_20151020_HA').up('table').show();
    $('p_identif_20151020_HA').up('table').select('select').each(function(elt) {
      if (!elt.getValue()) { elt.addClassName('no-print'); }
      elt.observe('change', function(evt) {
        if (evt.target.getValue()) {
          evt.target.removeClassName('no-print');
        }
        else {
          evt.target.addClassName('no-print');
        }
      });
    });
    $$('.buttons-container').last().removeClassName('hide-on-last-page');
    $$('[id*="identif_select_paiement"]').invoke('show');
  },
  hidePaiement:function() {
    NTD.p_identif_20151020.onSelectModePaiement(null);
    $('table-p_identif_20151020_select_paiement').hide();
    $('p_identif_20151020_HA').setValue('');
    $('p_identif_20151020_HA').up('table').hide();
    $$('.buttons-container').last().addClassName('hide-on-last-page');
  }

};
