NTD.Tva3519 = {

  /*integrity_dj : function(elt, args){
    var DJ = {elt: $(args['DJ'])};
    var DN = {elt: $(args['DN'])};
    var CB = {elt: $(args['CB'])};
    DJ.value = parseFloat(DJ.elt.getValue());
    DN.value = parseFloat(DN.elt.getValue());
    CB.value = CB.elt.getValue(); // 31/12/2014
    if (typeof CB.value != "string" || CB.value.indexOf('/') === -1) {
      return;
    }
    CB.value = CB.value.split('/');
    CB.value = CB.value[1];

    if (DJ.elt.checked) {
      NTD.Generic.none(DN.elt);
      return;
    }
    var min = 760;
    if(CB.value == 12) {
      min = 150;
    }
    if (DN.value < min) {
      NTD.Generic.negativ(DN.elt, 'bad');
    }
    else{
      NTD.Generic.positiv(DN.elt);
    }
  },*/

  integrity_fg : function(elt, num){
    var itemsArray = $(elt).getAttribute('data-integrity-fg-items'+num).split(',');
    var result_FG = $(itemsArray[0]);
    var FC = $(itemsArray[1]);
    var FE = $(itemsArray[2]);
    var FF = $(itemsArray[3]);
    NTD.Generic.none(FE);
    if(NTD.Control.check_dependances([result_FG, FE, FF], 'integrity_fg')){   
      var active_operande ;
      if(parseFloat(FE.value) < parseFloat(FF.value)) {
        active_operande = FF;
      } else {
        active_operande = FE;
      }
      if(parseFloat(result_FG.value) >= parseFloat(active_operande.value)){
         NTD.Debug.trace('integrity_eq -> erreur, FG doit être inférieur ou égal à '+active_operande.id+'');
         NTD.Generic.negativ(result_FG);
      } else {
       NTD.Debug.trace('fonction integrity_fg -> L\'intégrité de FG est bonne');
       NTD.Generic.positiv(result_FG);
     }
    }
  },
  
  tva3519_export : function(elt, num){
    var div_export    = $('exportateur-tva3519');
    var div_no_export = $('no-exportateur-tva3519');
    if(elt.value != "" || elt.value != 0) {
      div_export.hide();
      div_export.select('input').invoke('writeAttribute', {'disabled': 'disabled'});
      div_no_export.show();
    } else {
      div_export.show();
      div_export.select('input').invoke('removeAttribute', 'disabled');
      div_no_export.hide();
    }
  },

  paiement_3519:function(elt, num){
    NTD.Identif.t("hidePaiement", []);
  }


};


