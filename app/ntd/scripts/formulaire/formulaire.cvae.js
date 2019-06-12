NTD.Cvae = {

  /************************************* fonctions Calculs CVAE AC ************************************/

  calcB : function(elt, num) {
    log('NTD.Cvae.calcB()');
    var operandes = $(elt).getAttribute('data-calc-b-operands'+num).split(',');
    var results = $(elt).getAttribute('data-calc-b-results'+num).split(',');
    var active_operande;
    var total;
    operandes.each(function(operande) {
      if ($(operande).value != "" && !$(operande).hasClassName('result')) {
        active_operande = $(operande);
        NTD.Control.setDependances([active_operande]);
      }
    });
    if (active_operande != undefined) {
      if (active_operande.value < 500000) {
        total = 0;
      } else if (active_operande.value >= 500000 && active_operande.value <= 3000000) {
        total = (0.5 * (active_operande.value-500000)) / 2500000;
      } else if (active_operande.value > 3000000 && active_operande.value <= 10000000) {
        total = ((0.9 * (active_operande.value-3000000)) / 7000000)+0.5;
      } else if (active_operande.value > 10000000 && active_operande.value <= 50000000) {
        total = ((0.1 * (active_operande.value-10000000)) / 40000000)+1.4;
      } else if (active_operande.value > 50000000) {
        total = 1.5;
      }
    }
    results.each(function(result) {
      if (total != undefined) {
        total = total.toFixed(2);
      } else {
        NTD.Control.setValue($(result), 0);
      }
      NTD.Control.setValue($(result), total, true, 0, 1);
    });
  },


  calcD : function(elt, num) {
    log('NTD.Cvae.calcD()');
    var operandes = $(elt).getAttribute('data-calc-d-operands'+num).split(',');
    var results = $(elt).getAttribute('data-calc-d-results'+num).split(',');
    var checkbox = $(operandes[0]);
    operandes.shift();

    var active_operande = null;
    operandes.each(function(operande) {
      operande = $(operande);    
      if ($F(operande) != "" && !operande.hasClassName('result')) {
        active_operande = operande;
        NTD.Control.setDependances([active_operande]);
        //throw $break;
      }
    }, this);
    
    var total = 0;
    if (active_operande) {
      total = parseFloat($F(active_operande));
      total *= (total <= 7600000) ? 0.8 : 0.85;
    }

    results.each(function(elt) {
      elt = $(elt);
      if (elt.hasAttribute('result')) {
        return;
      }
      if(!checkbox.checked) {
        NTD.Control.setValue(elt, total);
      }else{
        elt.value = '';
      }
    }, this);
  },

  calcFac: function(elt, num) {
    log('NTD.Cvae.calcFac()');
    var itemsArray = $(elt).getAttribute('data-calc-fac-items'+num).split(',');
    var result_CB = $(itemsArray[0]);
    var AA = $(itemsArray[1]);
    var AD = $(itemsArray[2]);
    var CA = $(itemsArray[3]);
    var active_operande;
    var total;
    [AA, AD].each(function(operande) {
      if (operande.value != "" && !operande.hasClassName('result')) {
        active_operande = operande;
        NTD.Control.setDependances([active_operande]);
      }
    });
    if (active_operande != undefined) {
      if (active_operande.value < 2000000) {
        if (CA.value <= 1000) {
          total = 0;
        } else {
          total = (parseFloat(CA.value)-1000) * 0.5;
        }
      }
      else {
        total = parseFloat(CA.value) * 0.5;
      }
      NTD.Control.setValue(result_CB, total);
    }
  },

  montantCotisation: function(elt, num) {
    log('NTD.Cvae.montantCotisation()');
    var itemsArray = $(elt).getAttribute('data-montant-cotisation-items'+num).split(',');
    var result_CA = $(itemsArray[4]);
    var AC = $(itemsArray[0]);
    var BA = $(itemsArray[1]);
    var BB = $(itemsArray[2]);
    var BC = $(itemsArray[3]);
    var total;
    NTD.Control.setDependances(itemsArray);
    if (!BC.checked) {
      if (parseFloat(BA.value) > parseFloat(BB.value)) {
        total = parseFloat(BB.value * AC.value) / 100;
        NTD.Control.setValue(result_CA, total);
      } else {
        total = parseFloat(BA.value * AC.value) / 100;
        NTD.Control.setValue(result_CA, total);
      }
    } else {
      total = parseFloat(BA.value * AC.value) / 100;
      NTD.Control.setValue(result_CA, total);
    }
  },





  /*************************************** fonctions Calcul CVAE DEF ******************************************/

  calcF: function(elt, num) {
    log('NTD.Cvae.calcF()');
    return;
    var itemsArray = $(elt).getAttribute('data-calc-f-items'+num).split(',');
    var result_CB = $(itemsArray[0]);
    var AA = $(itemsArray[1]);
    var CA = $(itemsArray[2]);
    var total;
    if (AA.value < 2000000) {
      if (CA.value <= 1000)
        total = 0;
      else {
        total = parseFloat(CA.value)-1000;
      }
    }
    else {
      total = parseFloat(CA.value);
      NTD.Control.setValue(result_CB, total);
    }
  },

  cotisationMinimum: function(elt, num) {
    log('NTD.Cvae.cotisationMinimum()');
    var itemsArray = $(elt).getAttribute('data-cotisation-minimum-items'+num).split(',');
    var AA = $(itemsArray[0]);
    var AD = $(itemsArray[1]);
    var EA = $(itemsArray[2]);
    var CB = $(itemsArray[3]);
    var DA = $(itemsArray[4]);
    var DB = $(itemsArray[5]);

    if(DA.value.blank()) DA.value = 0;
    if(DB.value.blank()) DB.value = 0;    


    var total = 0;

    var value = parseFloat(AA.value > 0 ? AA.value : AD.value);
    if (value > 500000) {      
      total = Math.max(250, (parseFloat(CB.value) - parseFloat(DA.value) - parseFloat(DB.value)));
    }
    NTD.Control.setValue(EA, total);
/*
    log('NTD.Cvae.cotisationMinimum()');
    var itemsArray = $(elt).getAttribute('data-cotisation-minimum-items'+num).split(',');
    var result_CH = $(itemsArray[0]);
    var AA = $(itemsArray[1]);
    var CE = $(itemsArray[2]);
    var CG = $(itemsArray[3]);
    var total;
    if (parseFloat(AA.value) > 500000) {
      if (parseFloat(CE.value) < 250) {
        total = 250;
        NTD.Control.setValue(result_CH, parseFloat(total));
        result_CH.value = 250;
      } else {
        total = CG.value;
        NTD.Control.setValue(result_CH, parseFloat(total));
      }
    } else {
      total = CG.value;
      NTD.Control.setValue(result_CH, parseFloat(total));
    }
   */
  },

  cotisationAvantReduction: function(elt, num) {
    log('NTD.Cvae.cotisationAvantReduction()');
    var itemsArray = $(elt).getAttribute('data-cotisation-avant-reduction-items'+num).split(',');
    var result_CB = $(itemsArray[0]);
    var AA = $(itemsArray[1]);
    var CA = $(itemsArray[2]);
    var total;
    if (parseFloat(AA.value) < 2000000 && parseFloat(CA.value) <= 1000) {
      total = 0;
      NTD.Control.setValue(result_CB, parseFloat(total));
    } else if ((parseFloat(AA.value) < 2000000 || AA.value == "") && parseFloat(CA.value) > 1000) {
      total = parseFloat(CA.value)-1000;
      NTD.Control.setValue(result_CB, parseFloat(total));
    } else if (parseFloat(AA.value) >= 2000000) {
      total = parseFloat(CA.value);
      NTD.Control.setValue(result_CB, parseFloat(total));
    }
  },

  fraisGestion : function(elt, num) {
    log('NTD.Cvae.fraisGestion()');
    var itemsArray = $(elt).getAttribute('data-frais-gestion-items'+num).split(',');
    var result_CI = $(itemsArray[0]);
    var CH = $(itemsArray[1]);
    var CL = $(itemsArray[2]);
    CL.onchange();
    var total;
    total = parseFloat(CH.value) * 0.01;
    NTD.Control.setValue(result_CI, parseFloat(total));
  }


  


};
