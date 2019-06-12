if (!Formulaire) var Formulaire = {};

Formulaire.cvae1329def = {  

  paiement: function(elt, args, params) {
    var formulaire_code = params['formulaire_code'];
    var field = $(formulaire_code+'_'+args['field']);
    if (parseFloat($F(field)) > 0) {
      NTD.Identif.p("showPaiement", [parseFloat($F(field))]);
    } else {
      NTD.Identif.p("hidePaiement", []);
    }    
  }


};
