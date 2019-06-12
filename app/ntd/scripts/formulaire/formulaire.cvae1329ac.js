if (!Formulaire) var Formulaire = {};

Formulaire.cvae1329ac = {

  FORMULAIRE_CODE: 'cvae1329ac',

  accompteAVerser: function(elt, args) {
    var itemsArray = args['items'];
    var result = $(Formulaire.cvae1329ac.FORMULAIRE_CODE + '_' + itemsArray[0]);
    var item1 = $(Formulaire.cvae1329ac.FORMULAIRE_CODE + '_' + itemsArray[1]);
    var item2 = $(Formulaire.cvae1329ac.FORMULAIRE_CODE + '_' + itemsArray[2]);
    var item3 = $(Formulaire.cvae1329ac.FORMULAIRE_CODE + '_' + itemsArray[3]);
    var total = (NTD.Number.parseFloat(item1.value) + NTD.Number.parseFloat(item2.value)) - NTD.Number.parseFloat(item3.value);
    NTD.Control.setValue(result, parseFloat(total));
  },



  

  paiement: function(elt, args) {
    var item_code = args['item'];
    var item = $(Formulaire.cvae1329ac.FORMULAIRE_CODE + '_' + args['item']);
    var checkbox = $(Formulaire.cvae1329ac.FORMULAIRE_CODE + '_' + item_code + '_checkbox');

    if ($F(item) > args['amount_max']) {
      checkbox.checked = false;
    }

    if ($F(item) > 0 && !checkbox.checked) {
      NTD.Identif.p("showPaiement", [$F(item)]);
    } else {
      NTD.Identif.p("hidePaiement", []);
    }
    if (checkbox.checked) {
      $('row-link-' + item_code).show();
    } else {
      $('row-link-' + item_code).hide();
    }
  }


};
