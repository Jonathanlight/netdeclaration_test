NTD.Tva3525bis = {

  integrity_bc_3525bis : function(elt, num) {
    var itemsArray = $(elt).getAttribute('data-integrity-bc-3525bis-items' + num).split(',');
    var BC = $(itemsArray[0]);
    var BB = $(itemsArray[1]);
    if (NTD.Control.check_dependances(itemsArray, 'integrity_bc')) {
      if (parseFloat(BC.value) > parseFloat(BB.value)) {
        NTD.Generic.negativ(BC);
      } else {
        NTD.Generic.positiv(BC);
      }
    }
  },

  disable_all_3525bis : function(elt, num) {
    var itemsArray = $(elt).getAttribute('data-disable-all-3525bis-items' + num).split(',');
    var BE = $(itemsArray).shift();
    if ($(BE).checked) {
      itemsArray.each(function(field) {
        $(field).writeAttribute('disabled', 'disabled');
        $(field).value = '';
        $(field).onchange();
      });

    } else {
      itemsArray.each(function(field) {
        $(field).removeAttribute('disabled');
      });
    }
  },
  paiement_tva3525bis: function(elt, num) {
    var items = $(elt).getAttribute('data-paiement-tva3525bis-operands' + num).split(',');
    var BD = $(items[0]);

    if ($F(BD) > 0) {
      NTD.Identif.t("showPaiement", [$F(BD)]);
    } else {
      NTD.Identif.t("hidePaiement", []);
    }
  }
};


