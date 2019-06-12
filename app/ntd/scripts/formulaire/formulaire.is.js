NTD.Is = {

  compare : function(elt, num) {
    //console.log(elt);
    var results = $(elt).getAttribute('data-compare-results' + num).split(',');
    var operands = $(elt).getAttribute('data-compare-operands' + num).split(',');
    results.each(function(result) {
      if (!$(result).hasClassName('result')) {
        if ($(result).value != "" && $(result).value > 0) {
          NTD.Control.setDependances(results);
          NTD.Control.disable_field(operands);
        } else if ($(result).value == "") {
          NTD.Control.enable_field(operands);
        }
      }
    });
    NTD.Control.reset_operations(operands.concat(results));
  },

  soustraction_cada : function(elt, num) {
    var itemsArray = $(elt).getAttribute('data-soustraction-cada-items' + num).split(',');
    var CA = itemsArray[0];
    var DA = itemsArray[1];
    var AD = itemsArray[2];
    var BD = itemsArray[3];
    var EA = itemsArray[4];

    if ($(AD).value == "" && $(BD).value == "") {
      NTD.Control.removeValue([CA, DA]);
    }
    var total = $(AD).value;
    total -= $(BD).value;
    if (total > 0 && !isNaN(total)) {
      NTD.Control.setValue($(CA), Math.abs(total));
      NTD.Control.setValue($(DA), 0);
      NTD.Control.setValue($(EA), 0);
    } else if (total < 0 && !isNaN(total)) {
      NTD.Control.setValue($(DA), Math.abs(total));
      NTD.Control.setValue($(CA), 0);

      if ($(EA).value == "" || $(EA).value == 0) {
        NTD.Control.removeValue([$(EA)]);
        $(EA).value = 0;
      }
    } else {
      NTD.Control.setValue($(DA), 0);
      NTD.Control.setValue($(CA), 0);
    }
    /*if($(AD).value == 0 && $(BD).value == 0){
     NTD.Control.removeValue([AD, BD]);
     }  */
    NTD.Control.reset_operations(itemsArray);
  },

  verification_ea: function(elt, num) {
    var itemsArray = $(elt).getAttribute('data-verification-ea-items' + num).split(',');
    var AD = $(itemsArray[0]);
    var BD = $(itemsArray[1]);
    var DA = $(itemsArray[2]);
    var EA = $(itemsArray[3]);
    var EB = $(itemsArray[4]);
    var soustraction = false;
    if (AD.value == "") {
      NTD.Control.removeValue([AD,DA,EA,EB]);
    }
    if ((parseFloat(AD.value) >= parseFloat(BD.value) || (parseFloat(EA.value) > parseFloat(DA.value))) && parseFloat(DA.value) != 0) {
      NTD.Generic.negativ(EA);
      NTD.Control.setValue(EB, 0);
      return;
    } else {
      if (DA.value == '0') {
        NTD.Generic.positiv(EA);
      }
      NTD.Control.checkValue(EA);
    }
    if (AD.value == '') {
      return;
    } else if (EA.value == '') {
      NTD.Control.setDependances([EA]);
      EA.value = 0;
      return;
    } else {
      soustraction = true;
    }
    if (soustraction) {
      var result;
      result = parseFloat(DA.value) - parseFloat(EA.value);
      NTD.Control.setValue(EB, result);
    }
    NTD.Control.reset_operations(itemsArray);
  },
  is2571_paiement: function(elt, num) {
    var CE = $($(elt).getAttribute('data-is2571-paiement-operands' + num));

     if ($F(CE) > 0) {
      NTD.Identif.p("showPaiement", [$F(CE)]);
    } else {
      NTD.Identif.p("hidePaiement", []);
    }
  },
  is2572_paiement: function(elt, num) {
    var items = $(elt).getAttribute('data-is2572-paiement-operands' + num).split(',');
    var CA = $(items[0]);    

     if ($F(CA) > 0) {
      NTD.Identif.p("showPaiement", [$F(CA)]);
    } else {
      NTD.Identif.p("hidePaiement", []);
    }    
  },
  is2573_paiement: function(elt, num) {
    NTD.Identif.p("hidePaiement", []);
  }
};


