NTD.t_identif_20170101 = {

  onSelectModePaiement: function(elt) {
    elt = $(elt);
    $$('.paiement-box-tlra, .paiement-box-nopaiement').each(function(paiement_box) {
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
          if (paiement_box.select('select').length > 0) {
            paiement_box.select('select').each(function(a) {
              a.observe('change', function(evt) {
                if (evt.target.getValue()) {
                  evt.target.up('.elt-select').removeClassName('no-print');
                }
                else {
                  evt.target.up('.elt-select').addClassName('no-print');
                }
              });
            });
          }
        }

        paiement_box.show();
        paiement_box.select('input, select').each(function(input) {
          $(input).removeAttribute('disabled');
        });
      });

      if ($$("[name='t_identif_20170101_opts[payment]']").length > 0)
        $$("[name='t_identif_20170101_opts[payment]']").first().setValue($F(elt));
    }
  },

  showPaiement: function(amount) {
    var initialize = true;
    $('table-t_identif_20170101_select_paiement').show();
    $('table-t_identif_20170101_select_paiement').select('input[name=select_paiement]').each(function(select_paiement) {
      select_paiement = $(select_paiement);
      if (select_paiement.checked) {
        NTD.t_identif_20170101.onSelectModePaiement(select_paiement);
        initialize = false;
      }
    });

    if (initialize) {
      NTD.t_identif_20170101.onSelectModePaiement(null);
      $('select_paiement_tlra').click(null);
    }

    if ($F('declaration-status') != 0) return;

    var total_amount = Number($F('t_identif_20170101_HA')) + Number($F('t_identif_20170101_HB')) + Number($F('t_identif_20170101_HC'));
    if (total_amount != amount) {
      $('t_identif_20170101_HA').setValue(amount);
      $('t_identif_20170101_HB').setValue(0);
      $('t_identif_20170101_HC').setValue(0);
    }
    $$('.buttons-container').last().removeClassName('hide-on-last-page');
      $('table-t_identif_20170101_select_paiement').select('input[type="radio"]').each(function(radio) {
          radio.show();
      });
  },

  hidePaiement: function() {
    $('table-t_identif_20170101_select_paiement').hide();

    NTD.t_identif_20170101.onSelectModePaiement(null);

    if ($F('declaration-status') != 0) return;

    $('t_identif_20170101_HA').setValue('');
    $$('.buttons-container').last().addClassName('hide-on-last-page');
      $('table-t_identif_20170101_select_paiement').select('input[type="radio"]').each(function(radio) {
          radio.hide();
    });
    $('t_identif_20170101_hidden_payment').setValue('');
  },

  onSelectOGA: function(elt) {
    $('t_identif_20170101_OGA').setValue($F(elt));
    $('t_identif_20170101_OGA').onchange();
  }

};
