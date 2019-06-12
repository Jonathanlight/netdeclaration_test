
NTD.p_identif = {

  /*onSelectModePaiement: function(elt) {
   $$('.paiement-box-tlra, .paiement-box-especes, .paiement-box-cheque, .paiement-box-virement').invoke('hide');
   $('t_identif_EA', 't_identif_EB', 't_identif_EC', 't_identif_ED').each(function(checkbox) {
   checkbox.removeAttribute('checked');
   });
   if ($(elt) && $F(elt)) {
   var mode = $F(elt);
   $$('.paiement-box-' + mode).invoke('show');
   $(elt).next('span').down('input').writeAttribute('checked', 'checked');
   }
   },*/

  showPaiement:function(amount) {
    $('p_identif_HA').setValue(amount);
    $('p_identif_HA').up('table').show();
    $('p_identif_HA').up('table').select('select').each(function(elt) {
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
  },
  hidePaiement:function() {
    $('p_identif_HA').setValue('');
    $('p_identif_HA').up('table').hide();
    $$('.buttons-container').last().addClassName('hide-on-last-page');
  }

};
