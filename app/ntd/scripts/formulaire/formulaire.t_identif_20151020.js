NTD.t_identif_20151020 = {

  onSelectModePaiement: function(elt) {
    elt = $(elt);
    $$('.paiement-box-tlra, .paiement-box-especes, .paiement-box-cheque, .paiement-box-virement, .paiement-box-nopaiement').each(function(paiement_box){
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

      if ($$("[name='t_identif_20151020_opts[payment]']").length > 0)
        $$("[name='t_identif_20151020_opts[payment]']").first().setValue($F(elt));
    }
  },

  showPaiement:function(amount) {
    var initialize = true;
    $('table-t_identif_20151020_select_paiement').show();
    $('table-t_identif_20151020_select_paiement').select('input[name=select_paiement]').each(function(select_paiement){
      select_paiement = $(select_paiement);
      if (select_paiement.checked) {
        NTD.t_identif_20151020.onSelectModePaiement(select_paiement);
        initialize = false;
      }
    });
    if (initialize) {
      NTD.t_identif_20151020.onSelectModePaiement(null);
      $('select_paiement_tlra').click(null);
    }
    if($F('declaration-status') != 0) return;
    var total_amount = Number($F('t_identif_20151020_HA')) + Number($F('t_identif_20151020_HB')) + Number($F('t_identif_20151020_HC'));
    if (total_amount != amount) {
      $('t_identif_20151020_HA').setValue(amount);
      $('t_identif_20151020_HB').setValue(0);
      $('t_identif_20151020_HC').setValue(0);
    }
    $$('.buttons-container').last().removeClassName('hide-on-last-page');
  },

  hidePaiement:function() {
    $('table-t_identif_20151020_select_paiement').hide();
    $('table-t_identif_20151020_select_paiement').select('input[type="radio"]').each(function(radio) {
      radio.checked = false;
      radio.removeAttribute('checked')
    });
    if ($$("[name='t_identif_20151020_opts[payment]']").length > 0 && $F($$("[name='t_identif_20151020_opts[payment]']").first()) == "nopaiement") {
      $("select_paiement_nopaiement").checked = true;
      NTD.t_identif_20151020.onSelectModePaiement($("select_paiement_nopaiement"));
    }
    else {
      NTD.t_identif_20151020.onSelectModePaiement(null);
    }
    $('t_identif_20151020_HA').setValue('');
    $$('.buttons-container').last().addClassName('hide-on-last-page');
  },

  onSelectOGA: function(elt) {
    $('t_identif_20151020_OGA').setValue($F(elt));
    $('t_identif_20151020_OGA').onchange();
  }

};
