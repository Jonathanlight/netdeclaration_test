NTD.tva3517bisca = {

  integrity_ae_bisca12: function(elt, num) {
    var itemsArray = $(elt).getAttribute('data-integrity-ae-bisca12-items'+num).split(',');
    var AE = $(itemsArray[0]);
    if (NTD.Control.check_dependances([AE], 'integrity_ae_bisca12')) {
      if (AE.value != '12' && AE.value != '12E') {
        //NTD.Debug.trace('integrity_ae -> erreur, la valeur de AE doit être égal à 12 ou à 12E');
        NTD.Generic.negativ(AE);
      } else {
        NTD.Generic.positiv(AE);
      }
    }
  },

  calcul_es: function(elt, num) {
    var itemsArray = $(elt).getAttribute('data-calcul-es-items'+num).split(',');
    var items_1 = itemsArray.slice(0, 4);
    var items_2 = itemsArray.slice(4, itemsArray.length);

    var ES = $(items_1[0]);
    var FF = $(items_1[1]);
    var GA = $(items_1[2]);
    var GB = $(items_1[3]);

    NTD.Control.setDependances(items_2);
    var total_ES = 0;
    var total_GB;
    items_2.each(function(elt) {
      if ($(elt).value == "") $(elt).value = 0;
      total_ES += parseFloat($(elt).value);
    });

    NTD.Control.setValue(ES, total_ES, true);
    NTD.Control.reset_operations(items_2.concat([ES]));

    if (!GA.hasClassName('edited') && !GB.hasClassName('edited')) {
      if (parseFloat(FF.value) > parseFloat(ES.value)) {
        total_GB = parseFloat(FF.value)-parseFloat(ES.value);
        GB.addClassName('edited');
        NTD.Control.setValue(GB, total_GB, true);
        GA.addClassName('edited');
        NTD.Control.setValue(GA, 0, true);
      } else {
        if (ES.value == "") NTD.Control.removeValue([GA, GB]);
        GB.removeClassName('edited');
        GA.removeClassName('edited');
      }
    }
  },

  integrity_fg_bisca12 : function(elt, num) {
    var itemsArray = $(elt).getAttribute('data-integrity-fg-bisca12-items'+num).split(',');
    var FG = $(itemsArray[0]);

    if (FG.value != "" && FG.value != 0) {
      if (parseFloat(FG.value) < 0 || parseFloat(FG.value) > 100) {
        NTD.Generic.negativ(FG);
      } else {
        NTD.Generic.positiv(FG);
      }
    }
  },

  calcul_ff_bisca12: function(elt, num) {
    var itemsArray = $(elt).getAttribute('data-calcul-ff-bisca12-items'+num).split(',');
    var items_1 = itemsArray.slice(0, 2);
    var items_2 = itemsArray.slice(2, itemsArray.length);

    var FF = $(items_1[0]);
    var KH = $(items_1[1]);

    NTD.Control.setDependances(items_2);
    var total_FF = 0;
    items_2.each(function(elt) {
      if ($(elt).value == "") $(elt).value = 0;
      total_FF += parseFloat($(elt).value);
    });
    NTD.Control.setValue(FF, total_FF, true);
    NTD.Control.reset_operations(items_2.concat([FF]));

    if (parseFloat(FF.value) <= parseFloat(KH.value)) {
      NTD.Generic.negativ(FF);
    }
    else if (parseFloat(FF.value) > parseFloat(KH.value)) {
      NTD.Generic.positiv(FF);
    }
    else {
      NTD.Generic.none(FF);
    }
  },

  calcul_ff_bisca12_2015: function(elt, num) {
    var itemsArray = $(elt).getAttribute('data-calcul-ff-bisca12-2015-items'+num).split(',');
    var items_1 = itemsArray.slice(0, 2);
    var items_2 = itemsArray.slice(2, itemsArray.length);

    var FF = $(items_1[0]);
    var KH = $(items_1[1]);

    NTD.Control.setDependances(items_2);
    var total_FF = 0;
    items_2.each(function(elt) {
      if ($(elt).value == "") $(elt).value = 0;
      total_FF += parseFloat($(elt).value);
    });
    NTD.Control.setValue(FF, total_FF, true);
    NTD.Control.reset_operations(items_2.concat([FF]));

    if (parseFloat(FF.value) < parseFloat(KH.value)) {
      NTD.Generic.negativ(FF);
    }
    else if (parseFloat(FF.value) >= parseFloat(KH.value)) {
      NTD.Generic.positiv(FF);
    }
    else {
      NTD.Generic.none(FF);
    }
  },

  calcul_ga_gb_bisca12 : function(elt, num) {
    var itemsArray = $(elt).getAttribute('data-calcul-ga-gb-bisca12-items'+num).split(',');
    var ES = $(itemsArray[0]);
    var FF = $(itemsArray[1]);
    var result_GA = $(itemsArray[2]);
    var result_GB = $(itemsArray[3]);
    var total = 0;
    if (ES.value == "" && FF.value == "") {

      NTD.Control.removeValue([result_GA, result_GB]);
    } else if (parseFloat(ES.value) >= parseFloat(FF.value)) {
      total = parseFloat(ES.value)-parseFloat(FF.value);

      NTD.Control.setValue(result_GA, total, true);
      NTD.Control.setValue(result_GB, 0, true);
    } else {
      total = parseFloat(FF.value)-parseFloat(ES.value);
      NTD.Control.setValue(result_GB, total, true);
      NTD.Control.setValue(result_GA, 0, true);
    }
  },

  calcul_ja_jb_jc_bisca12 : function(elt, num) {
    var itemsArray = $(elt).getAttribute('data-calcul-ja-jb-jc-bisca12-items'+num).split(',');
    var result_JA = $(itemsArray[0]);
    var result_JB = $(itemsArray[1]);
    var result_JC = $(itemsArray[2]);
    var GA = $(itemsArray[3]);
    var GB = $(itemsArray[4]);
    var HA = $(itemsArray[5]);
    var HB = $(itemsArray[6]);
    var HC = $(itemsArray[7]);

    var total_JA = (NTD.Number.parseFloat(GA.value)+NTD.Number.parseFloat(HC.value))-(NTD.Number.parseFloat(GB.value)+NTD.Number.parseFloat(HA.value)+NTD.Number.parseFloat(HB.value));
    var total_JB = (NTD.Number.parseFloat(HA.value)+NTD.Number.parseFloat(HB.value))-(NTD.Number.parseFloat(HC.value)+NTD.Number.parseFloat(GA.value));
    var total_JC;
    /*if (total_JA > 0) {
     NTD.Control.setValue(result_JA, total_JA, true);
     NTD.Control.setValue(result_JB, 0, true);
     } else if (total_JA == 0) {
     NTD.Control.setValue(result_JA, 0, true);
     }else if (total_JB > 0) {
     NTD.Control.setValue(result_JB, total_JB, true);
     NTD.Control.setValue(result_JA, 0, true);
     } else if (total_JB == 0) {
     NTD.Control.setValue(result_JB, 0, true);
     }*/
    if (total_JA > 0) {
      total_JB = 0;
    } else if (total_JB > 0) {
      total_JA = 0;
    } else {
      total_JA = total_JB = 0;
    }
    NTD.Control.setValue(result_JA, total_JA, true);
    NTD.Control.setValue(result_JB, total_JB, true);

    if (total_JB > 0) {
      total_JC = NTD.Number.parseFloat(GB.value)+NTD.Number.parseFloat(result_JB.value);

    } else {
      total_JC = NTD.Number.parseFloat(GB.value)+NTD.Number.parseFloat(HA.value)+NTD.Number.parseFloat(HB.value)-NTD.Number.parseFloat(HC.value);
    }
    NTD.Control.setValue(result_JC, total_JC, true);

  }
  ,

  calcul_ja_jb_jc_bisca12_2015 : function(elt, num) {
    var itemsArray = $(elt).getAttribute('data-calcul-ja-jb-jc-bisca12-2015-items'+num).split(',');
    var result_JA = $(itemsArray[0]);
    var result_JB = $(itemsArray[1]);
    var result_JC = $(itemsArray[2]);
    var GA = $(itemsArray[3]);
    var GB = $(itemsArray[4]);
    var HA = $(itemsArray[5]);

    var total_JA = (NTD.Number.parseFloat(GA.value))-(NTD.Number.parseFloat(GB.value)+NTD.Number.parseFloat(HA.value));
    var total_JB = (NTD.Number.parseFloat(HA.value))-(NTD.Number.parseFloat(GA.value));
    var total_JC;
    if (total_JA > 0) {
      total_JB = 0;
    } else if (total_JB > 0) {
      total_JA = 0;
    } else {
      total_JA = total_JB = 0;
    }
    NTD.Control.setValue(result_JA, total_JA, true);
    NTD.Control.setValue(result_JB, total_JB, true);

    if (total_JB > 0) {
      total_JC = NTD.Number.parseFloat(GB.value)+NTD.Number.parseFloat(result_JB.value);

    } else {
      total_JC = NTD.Number.parseFloat(GB.value)+NTD.Number.parseFloat(HA.value);
    }
    NTD.Control.setValue(result_JC, total_JC, true);

  }
  ,

  integrity_eh_bisca : function(elt, num) {
    var itemsArray = $(elt).getAttribute('data-integrity-eh-bisca-items'+num).split(',');
    var EH = $(itemsArray[0]);
    var DH = $(itemsArray[1]);

    if (NTD.Number.parseFloat(DH.value) <= 0 && NTD.Number.parseFloat(EH.value) <= 0) {
      return NTD.Generic.positiv([DH, EH], true);
    }
    if (NTD.Number.parseFloat(EH.value) > NTD.Number.parseFloat(DH.value)) {
      NTD.Debug.trace('fonction integrity_EH -> EH doit être inférieur ou égal à DH');
      NTD.Generic.negativ(EH);
    } else if (NTD.Number.parseFloat(EH.value) < 0) {
      NTD.Debug.trace('fonction integrity_EH -> EH doit être supérieur ou égal à 0');
      NTD.Generic.negativ(EH);
    } else if (NTD.Number.parseFloat(EH.value) < Math.round(NTD.Number.parseFloat(DH.value) * 0.021)) {
      NTD.Debug.trace('fonction integrity_EH -> EH doit être strictement supérieur à DH * 2.10%');
      NTD.Generic.negativ(EH);
    } else if (NTD.Number.parseFloat(EH.value) > Math.round(NTD.Number.parseFloat(DH.value) * 0.206)) {
      NTD.Debug.trace('fonction integrity_EH -> EH doit être strictement inférieur à DH * 20.6%');
      NTD.Generic.negativ(EH);
    } else {
      NTD.Debug.trace('fonction integrity_EH -> L\'intégrité de EH est bonne');
      NTD.Generic.positiv([DH, EH], true);
    }
  },

  integrity_ep_bisca : function(elt, num) {
    var itemsArray = $(elt).getAttribute('data-integrity-ep-bisca-items'+num).split(',');
    var EP = $(itemsArray[0]);
    var DP = $(itemsArray[1]);

    if (NTD.Number.parseFloat(DP.value) <= 0 && NTD.Number.parseFloat(EP.value) <= 0) {
      return NTD.Generic.positiv([DP, EP], true);
    }
    if (NTD.Number.parseFloat(EP.value) > NTD.Number.parseFloat(DP.value)) {
      NTD.Debug.trace('fonction integrity_EP -> EP doit être inférieur ou égal à DP');
      NTD.Generic.negativ(EP);
    } else if (NTD.Number.parseFloat(EP.value) < 0) {
      NTD.Debug.trace('fonction integrity_EP -> EP doit être supérieur ou égal à 0');
      NTD.Generic.negativ(EP);
    } else if (NTD.Number.parseFloat(EP.value) < Math.round(NTD.Number.parseFloat(DP.value) * 0.021)) {
      NTD.Debug.trace('fonction integrity_EP -> EP doit être strictement supérieur à DP * 2.10%');
      NTD.Generic.negativ(EP);
    } else if (NTD.Number.parseFloat(EP.value) > Math.round(NTD.Number.parseFloat(DP.value) * 0.206)) {
      NTD.Debug.trace('fonction integrity_EP -> EP doit être strictement inférieur à DP * 20.6%');
      NTD.Generic.negativ(EP);
    } else {
      NTD.Debug.trace('fonction integrity_EP -> L\'intégrité de EP est bonne');
      NTD.Generic.positiv([DP, EP], true);
    }
  },

  report_if_150  : function(elt, num) {
    var results = $(elt).getAttribute('data-report-if-150-results'+num).split(',');
    var operands = $(elt).getAttribute('data-report-if-150-operands'+num).split(',');
    var total = parseFloat($(operands[0]).value);
    if (total >= 150) {
      results.each(function(elt) {
        NTD.Control.setValue($(elt), total, true);
      });
    } else {
      results.each(function(elt) {
        NTD.Control.setValue($(elt), 0, true);
      });
    }
  },

  calcul_nj_bisca12 : function(elt, num) {
    var itemsArray = $(elt).getAttribute('data-calcul-nj-bisca12-items'+num).split(',');
    var result_NJ = $(itemsArray[0]);
    var GB = $(itemsArray[1]);
    var NG = $(itemsArray[2]);
    var NH = $(itemsArray[3]);
    var total_NJ;
    if (NTD.Control.check_dependances([GB, NG], 'calcul_nj_bisca12')) {
      NTD.Control.setDependances([NH]);
      if (parseFloat(GB.value) >= 150) {
        total_NJ = parseFloat(NG.value)-parseFloat(NH.value);
        NTD.Control.setValue(result_NJ, total_NJ, true);
      } else {
        total_NJ = parseFloat(GB.value)+parseFloat(NG.value)-parseFloat(NH.value);
        NTD.Control.setValue(result_NJ, total_NJ, true);
      }
    }
  }
  ,

  integrity_mb_bisca12 : function(elt, num) {
    var itemsArray = $(elt).getAttribute('data-integrity-mb-bisca12-items'+num).split(',');
    var MB = $(itemsArray[0]);
    var MA = $(itemsArray[1]);
    if (MA.value == "") {
      NTD.Generic.none(MB);
    }
    if (parseFloat(MB.value) > parseFloat(MA.value)) {
      NTD.Generic.negativ(MB);
    } else {
      NTD.Generic.positiv(MB);
    }
  },

  report_MA_JC : function(elt, num){
     var itemsArray = $(elt).getAttribute('data-report-MA-JC-items'+num).split(',');
     var MA = $(itemsArray[0]);
     var JC = $(itemsArray[1]);
     var JA = $(itemsArray[2]);
     var MC = $(itemsArray[3]);
     if (JA.value > 0) {
       JC.value = 0;
     }
     else {
       MA.value = JC.value;
       MC.value = MA.value;
     }
  },

  /*disable_all_bisca12 : function(elt, num) {
   console.log('disable_all');
   var itemsArray = $(elt).getAttribute('data-disable-all-bisca12-items'+num).split(',');
   var ND = $(itemsArray).pop();
   console.log(ND);
   if($(ND).checked) {
   NTD.Control.disable_field($$('.field'));
   NTD.Control.enable_field(itemsArray.concat([ND]));
   } else {
   NTD.Control.enable_field($$('.field'));
   }
   }*/

  paiement_3517bisca12: function(elt, num) {

    var NC = $($(elt).getAttribute('data-paiement_3517bisca12-operands'+num));

    if ($F(NC) > 0) {
      NTD.Identif.t("showPaiement", [$F(NC)]);
    } else {
      NTD.Identif.t("hidePaiement", []);
    }
  }

};
