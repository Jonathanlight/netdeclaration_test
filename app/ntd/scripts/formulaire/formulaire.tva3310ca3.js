NTD.tva3310ca3 = {

  calcul_gc : function(elt, num) {
    var results = $(elt).getAttribute('data-calcul-gc-results'+num).split(',');
    var operands = $(elt).getAttribute('data-calcul-gc-operands'+num).split(',');

    if (parseFloat($(operands[0]).value) >= Math.round(($(operands[1]).value) * 0.021) && parseFloat($(operands[0]).value) <= Math.round(($(operands[1]).value) * 0.196)) {
      operands.each(function(elt) {
        NTD.Generic.positiv(elt);
      });
    }
    else if (parseFloat($(operands[0]).value) < Math.round(($(operands[1]).value) * 0.021) || parseFloat($(operands[0]).value) > Math.round(($(operands[1]).value) * 0.196)) {
      operands.each(function(elt) {
        NTD.Generic.negativ(elt);
      });
    }
    else {
      operands.each(function(elt) {
        NTD.Generic.none(elt);
      });
    }
  },

  calcul_ke : function(elt, num) {
    var results = $(elt).getAttribute('data-calcul-ke-results'+num).split(',');
    var operands = $(elt).getAttribute('data-calcul-ke-operands'+num).split(',');
    var KE = $(results[0]);

    var has_one_empty = operands.detect(function(operand) {
      return $F(operand).blank();
    });
    //if (!has_one_empty) {
    var total = NTD.Number.parseFloat($(operands[0]).value)+NTD.Number.parseFloat($(operands[1]).value)-NTD.Number.parseFloat($(operands[2]).value)+NTD.Number.parseFloat($(operands[3]).value)-NTD.Number.parseFloat($(operands[4]).value);
    NTD.Control.setValue(KE, total, true);
    NTD.Generic.positiv(KE);

    if ($F(KE) > 0) {
      NTD.Identif.t("showPaiement", [$F(KE)]);
    } else {
      NTD.Identif.t("hidePaiement", []);
    }
  },

  calcul_ke_2015 : function(elt, num) {
    var results = $(elt).getAttribute('data-calcul-ke-2015-results'+num).split(',');
    var operands = $(elt).getAttribute('data-calcul-ke-2015-operands'+num).split(',');
    var KE = $(results[0]);


    var total = NTD.Number.parseFloat($(operands[0]).value)
      + NTD.Number.parseFloat($(operands[1]).value)
      - NTD.Number.parseFloat($(operands[2]).value);

    NTD.Control.setValue(KE, total, true);
    NTD.Generic.positiv(KE);

    if ($F(KE) > 0) {
      NTD.Identif.t("showPaiement", [$F(KE)]);
    } else {
      NTD.Identif.t("hidePaiement", []);
    }
  },

  calcul_kc : function(elt, num) {
    var results = $(elt).getAttribute('data-calcul-kc-results'+num).split(',');
    var operands = $(elt).getAttribute('data-calcul-kc-operands'+num).split(',');
    var total = parseFloat($(operands[1]).value)+parseFloat($(operands[2]).value)+parseFloat($(operands[3]).value);

    if (($(operands[0]).value) > total) {
      results.each(function(elt) {
        NTD.Generic.positiv(elt);
      });
    }
    else if (($(operands[0]).value) <= total) {
      results.each(function(elt) {
        NTD.Generic.negativ(elt);
      });
    }
    else {
      results.each(function(elt) {
        NTD.Generic.none(elt);
      });
    }
  },

  calcul_ja : function(elt, num) {
    var results = $(elt).getAttribute('data-calcul-ca3-ja-results'+num).split(',');
    var operands = $(elt).getAttribute('data-calcul-ca3-ja-operands'+num).split(',');
    var GH = $(operands[0]);
    var HG = $(operands[1]);
    var RM = $(operands[2]);
    var result_JA = results[0];
    var value = NTD.Number.parseFloat(HG.value)-NTD.Number.parseFloat(GH.value) /*+ ( !RM.disabled ? NTD.Number.parseFloat(RM.value) : 0)*/;
    NTD.Control.setValue(result_JA, value, true);
  },

  calcul_ka : function(elt, num) {
    var results = $(elt).getAttribute('data-calcul-ca3-ka-results'+num).split(',');
    var operands = $(elt).getAttribute('data-calcul-ca3-ka-operands'+num).split(',');
    var GH = $(operands[0]);
    var HG = $(operands[1]);
    var QM = $(operands[2]);
    var result_KA = results[0];
    var value = NTD.Number.parseFloat(GH.value)-NTD.Number.parseFloat(HG.value) /*+ ( !QM.disabled ? NTD.Number.parseFloat(QM.value) : 0)*/;
    NTD.Control.setValue(result_KA, value, true);
  },

  integrity_cc : function(elt, num) {
    var itemsArray = $(elt).getAttribute('data-integrity-cc-items'+num).split(',');
    var CC = $(itemsArray[0]);
    var GJ = $(itemsArray[1]);
    NTD.Generic.none(CC);
    if (NTD.Control.check_dependances(itemsArray, 'integrity_cc')) {
      if (parseFloat(CC.value) < parseFloat(GJ.value)) {
        NTD.Generic.negativ(CC);
      } else {
        NTD.Generic.positiv(CC);
      }
    }
    if (parseFloat(CC.value) > 0) {
      if (!( parseFloat(GJ.value) > 0)) {
        NTD.Generic.negativ(GJ);
      }
    }
  },

  integrity_cd : function(elt, num) {
    var itemsArray = $(elt).getAttribute('data-integrity-cd-items'+num).split(',');
    var CD = $(itemsArray[0]);
    var CC = $(itemsArray[1]);
    NTD.Generic.none(CD);
    if (NTD.Control.check_dependances(itemsArray, 'integrity_cd')) {
      if (parseFloat(CD.value) > 0 && parseFloat(CD.value) > parseFloat(CC.value)) {
        NTD.Generic.negativ(CD);
      } else {
        NTD.Generic.positiv(CD);
      }
    }
  },

  integrity_ce : function(elt, num) {
    var itemsArray = $(elt).getAttribute('data-integrity-ce-items'+num).split(',');
    var CE = $(itemsArray[0]);
    var HH = $(itemsArray[1]);
    if (NTD.Control.check_dependances(itemsArray, 'integrity_ce')) {
      if (parseFloat(HH.value) > 0 && parseFloat(CE.value) <= 0) {
        NTD.Debug.trace('integrity_ce -> erreur, si HH est supérieur à 0, alors CE doit également être supérieur à 0');
        NTD.Generic.negativ(CE);
      } else {
        NTD.Debug.trace('fonction integrity_cd -> L\'intégrité de CD est bonne');
        NTD.Generic.positiv(CE);
      }
    }
  },

  integrity_gc : function(elt, num) {
    var itemsArray = $(elt).getAttribute('data-integrity-gc-items'+num).split(',');
    var GC = $(itemsArray[0]);
    var FC = $(itemsArray[1]);

    if (NTD.Number.parseFloat(FC.value) <= 0 && NTD.Number.parseFloat(GC.value) <= 0) {
      return NTD.Generic.positiv([FC, GC], true);
    }
    /*if (FC.value == "" && GC.value == "") {
     NTD.Generic.none([FC, GC], true);
     return;
     }
     if (FC.value == "" || GC.value == "") {
     NTD.Generic.none([FC, GC], true);
     NTD.Debug.trace('fonction integrity_gc -> GC ou FC vide');
     return;
     }*/
    if (NTD.Number.parseFloat(GC.value) > NTD.Number.parseFloat(FC.value)) {
      NTD.Debug.trace('fonction integrity_gc -> GC doit être inférieur ou égal à FC');
      NTD.Generic.negativ(GC);
    } else if (NTD.Number.parseFloat(GC.value) < 0) {
      NTD.Debug.trace('fonction integrity_gc -> GC doit être supérieur ou égal à 0');
      NTD.Generic.negativ(GC);
    } else if (NTD.Number.parseFloat(GC.value) < NTD.Number.parseFloat(FC.value) * 0.021) {
      NTD.Debug.trace('fonction integrity_gc -> GC doit être strictement supérieur à FC * 2.10%');
      NTD.Generic.negativ(GC);
    } else if (NTD.Number.parseFloat(GC.value) > NTD.Number.parseFloat(FC.value) * 0.196) {
      NTD.Debug.trace('fonction integrity_gc -> GC doit être strictement inférieur à FC * 19.60%');
      NTD.Generic.negativ(GC);
    } else {
      NTD.Debug.trace('fonction integrity_gc -> L\'intégrité de GC est bonne');
      NTD.Generic.positiv([FC, GC], true);
    }
  },

  integrity_gc_2014 : function(elt, num) {
    var itemsArray = $(elt).getAttribute('data-integrity-gc-2014-items'+num).split(',');
    var GC = $(itemsArray[0]);
    var FC = $(itemsArray[1]);

    if (NTD.Number.parseFloat(FC.value) <= 0 && NTD.Number.parseFloat(GC.value) <= 0) {
      return NTD.Generic.positiv([FC, GC], true);
    }
    if (NTD.Number.parseFloat(GC.value) > NTD.Number.parseFloat(FC.value)) {
      NTD.Debug.trace('fonction integrity_gc -> GC doit être inférieur ou égal à FC');
      NTD.Generic.negativ(GC);
    } else if (NTD.Number.parseFloat(GC.value) < 0) {
      NTD.Debug.trace('fonction integrity_gc -> GC doit être supérieur ou égal à 0');
      NTD.Generic.negativ(GC);
    } else if (NTD.Number.parseFloat(GC.value) < NTD.Number.parseFloat(FC.value) * 0.021) {
      NTD.Debug.trace('fonction integrity_gc -> GC doit être strictement supérieur à FC * 2.10%');
      NTD.Generic.negativ(GC);
    } else if (NTD.Number.parseFloat(GC.value) > NTD.Number.parseFloat(FC.value) * 0.200) {
      NTD.Debug.trace('fonction integrity_gc -> GC doit être strictement inférieur à FC * 20%');
      NTD.Generic.negativ(GC);
    } else {
      NTD.Debug.trace('fonction integrity_gc -> L\'intégrité de GC est bonne');
      NTD.Generic.positiv([FC, GC], true);
    }
  },

  integrity_gj : function(elt, num) {
    var itemsArray = $(elt).getAttribute('data-integrity-gj-items'+num).split(',');
    var GJ = $(itemsArray[0]);
    var CC = $(itemsArray[1]);
    var GH = $(itemsArray[2]);
    var GK = $(itemsArray[3]);
    NTD.Generic.none(GJ);

    if (NTD.Control.check_dependances(itemsArray, 'integrity_gj')) {
      if (parseFloat(GJ.value) > parseFloat(CC.value)) {
        NTD.Generic.negativ(GJ);
      }
      else if (parseFloat(GJ.value) > parseFloat(GH.value)) {
        NTD.Generic.negativ(GJ);
      }
      else if (parseFloat(GH.value) == 0 && parseFloat(GJ.value) != 0) {
        NTD.Generic.negativ(GJ);
      }
      else if ((parseFloat(GJ.value)+parseFloat(GK.value)) > parseFloat(GH.value)) {
        NTD.Generic.negativ(GJ);
      }
      else if (parseFloat(GJ.value) == 0 && parseFloat(CC.value) != 0) {
        NTD.Generic.negativ(GJ);
      }
      else {
        NTD.Generic.positiv(GJ);
      }
    }
    if ((parseFloat(GJ.value) > 0 || parseFloat(CC.value) > 0)
            && !((parseFloat(GJ.value) <= Math.round(parseFloat(CC.value) * 0.196))
            || (parseFloat(GJ.value) <= Math.round(parseFloat(CC.value) * 0.021))
            || (parseFloat(GJ.value) <= Math.round(parseFloat(CC.value) * 0.055)))) {
      NTD.Generic.negativ(GJ);
      NTD.Generic.negativ(CC);
    }
  },

  integrity_gj_2014 : function(elt, num) {
    var itemsArray = $(elt).getAttribute('data-integrity-gj-2014-items'+num).split(',');
    var GJ = $(itemsArray[0]);
    var CC = $(itemsArray[1]);
    var GH = $(itemsArray[2]);
    var GK = $(itemsArray[3]);
    NTD.Generic.none(GJ);

    if (NTD.Control.check_dependances(itemsArray, 'integrity_gj')) {
      if (parseFloat(GJ.value) > parseFloat(CC.value)) {
        NTD.Generic.negativ(GJ);
      }
      else if (parseFloat(GJ.value) > parseFloat(GH.value)) {
        NTD.Generic.negativ(GJ);
      }
      else if (parseFloat(GH.value) == 0 && parseFloat(GJ.value) != 0) {
        NTD.Generic.negativ(GJ);
      }
      else if ((parseFloat(GJ.value)+parseFloat(GK.value)) > parseFloat(GH.value)) {
        NTD.Generic.negativ(GJ);
      }
      else if (parseFloat(GJ.value) == 0 && parseFloat(CC.value) != 0) {
        NTD.Generic.negativ(GJ);
      }
      else {
        NTD.Generic.positiv(GJ);
      }
    }
    if ((parseFloat(GJ.value) > 0 || parseFloat(CC.value) > 0)
            && !((parseFloat(GJ.value) <= Math.round(parseFloat(CC.value) * 0.200))
            || (parseFloat(GJ.value) <= Math.round(parseFloat(CC.value) * 0.021))
            || (parseFloat(GJ.value) <= Math.round(parseFloat(CC.value) * 0.055)))) {
      NTD.Generic.negativ(GJ);
      NTD.Generic.negativ(CC);
    }
  },

  integrity_gj_2015 : function(elt, num) {
    var itemsArray = $(elt).getAttribute('data-integrity-gj-2015-items'+num).split(',');
    var GJ = $(itemsArray[0]);
    var CC = $(itemsArray[1]);
    var GH = $(itemsArray[2]);
    var GK = $(itemsArray[3]);


    if (NTD.Control.check_dependances(itemsArray, 'integrity_gj')) {
      if (parseFloat(GJ.value) > parseFloat(CC.value)) {
        NTD.Generic.negativ(GJ);
      }
      else if (parseFloat(GJ.value) > parseFloat(GH.value)) {
        NTD.Generic.negativ(GJ);
      }
      else if (parseFloat(GH.value) == 0 && parseFloat(GJ.value) != 0) {
        NTD.Generic.negativ(GJ);
      }
      else if ((parseFloat(GJ.value)+parseFloat(GK.value)) > parseFloat(GH.value)) {
        NTD.Generic.negativ(GJ);
      }
      else if (parseFloat(GJ.value) == 0 && parseFloat(CC.value) != 0) {
        NTD.Generic.negativ(GJ);
      }
      else {
        NTD.Generic.positiv(GJ);
      }
    }
    if ((parseFloat(GJ.value) > 0 || parseFloat(CC.value) > 0)
            && !((parseFloat(GJ.value) <= Math.round(parseFloat(CC.value) * 0.200))
            || (parseFloat(GJ.value) <= Math.round(parseFloat(CC.value) * 0.021))
            || (parseFloat(GJ.value) <= Math.round(parseFloat(CC.value) * 0.055)))) {
      NTD.Generic.negativ(GJ);
      NTD.Generic.negativ(CC);
    }
  },

  integrity_gk : function(elt, num) {
    var itemsArray = $(elt).getAttribute('data-integrity-gk-items'+num).split(',');
    var GK = $(itemsArray[0]);
    var GH = $(itemsArray[1]);
    var GJ = $(itemsArray[2]);
    NTD.Generic.none(GK);

    if (NTD.Control.check_dependances(itemsArray, 'integrity_gk')) {
      if ((parseFloat(GJ.value)+parseFloat(GK.value)) > parseFloat(GH.value)) {
        NTD.Debug.trace('integrity_gk -> erreur, GJ + GK doit être inférieur ou égal à GH');
        NTD.Generic.negativ(GK);
      } else if (parseFloat(GK.value) > parseFloat(GH.value)) {
        NTD.Debug.trace('integrity_gk -> erreur, GK doit être inférieur ou égal à GH');
        NTD.Generic.negativ(GK);
      } else {
        NTD.Debug.trace('integrity_gk -> correct ! Intégrité du champs GK vérifiée');
        NTD.Generic.positiv(GK);
      }
    }
  },

  integrity_kc : function(elt, num) {
    var itemsArray = $(elt).getAttribute('data-integrity-kc-items'+num).split(',');
    var KC = $(itemsArray[0]);
    var KA = $(itemsArray[1]);
    var KB = $(itemsArray[2]);
    var KD = $(itemsArray[3]);
    NTD.Generic.none(KC);
    if (NTD.Control.check_dependances(itemsArray, 'integrity_kc')) {
      if(parseFloat(KB.value) > 0 || parseFloat(KD.value) > 0){
         if (parseFloat(KC.value) > (parseFloat(KA.value)+parseFloat(KB.value)+parseFloat(KD.value))) {
          NTD.Generic.negativ(KC);
          return;
        }
      }
      else {
        if (parseFloat(KC.value) > parseFloat(KA.value)) {
          NTD.Generic.negativ(KC);
          return;
        }
      }
      NTD.Generic.positiv(KC);
    }
  },
integrity_kc_2015 : function(elt, num) {
    var itemsArray = $(elt).getAttribute('data-integrity-kc-2015-items'+num).split(',');
    var KA = $(itemsArray[0]);
    var KB = $(itemsArray[1]);
    if (NTD.Control.check_dependances(itemsArray, 'integrity_kc_2015')) {
      if(parseFloat(KB.value) > 0){

      }
      else {

      }
      //NTD.Generic.positiv(KC);
    }
  },

  integrity_hh : function(elt, num) {
    var itemsArray = $(elt).getAttribute('data-integrity-hh-items'+num).split(',');
    var HH = $(itemsArray[0]);
    var HC = $(itemsArray[1]);
    if (NTD.Control.check_dependances(itemsArray, 'integrity_hh')) {
      if (parseFloat(HH.value) > parseFloat(HC.value)) {
        NTD.Debug.trace('integrity_hh -> erreur, HH doit être inférieur ou égal à HC');
        NTD.Generic.negativ(HH);
      } else {
        NTD.Debug.trace('integrity_hh -> correct ! Intégrité du champs HH vérifiée');
        NTD.Generic.positiv(HH);
      }
    }
  },

  integrity_kg : function(elt, num) {
    var itemsArray = $(elt).getAttribute('data-integrity-kg-items'+num).split(',');
    var KG = $(itemsArray[0]);
    var HG = $(itemsArray[1]);
    if (NTD.Control.check_dependances(itemsArray, 'integrity_kg')) {
      if (parseFloat(KG.value) > parseFloat(HG.value)) {
        NTD.Debug.trace('integrity_hh -> erreur, KG doit être inférieur ou égal à HG');
        NTD.Generic.negativ(KG);
      } else {
        NTD.Debug.trace('integrity_hh -> correct ! Intégrité du champs KG vérifiée');
        NTD.Generic.positiv(KG);
      }
    }
  },

  integrity_hf : function(elt, num) {
    var itemsArray = $(elt).getAttribute('data-integrity-hf-items'+num).split(',');
    var HF = $(itemsArray[0]);
    var HG = $(itemsArray[1]);
    if (NTD.Control.check_dependances(itemsArray, 'integrity_hf')) {
      if (parseFloat(HF.value) > parseFloat(HG.value)) {
        NTD.Debug.trace('integrity_hh -> erreur, HF doit être inférieur ou égal à HG');
        NTD.Generic.negativ(HF);
      } else {
        NTD.Debug.trace('integrity_hh -> correct ! Intégrité du champs HF vérifiée');
        NTD.Generic.positiv(HF);
      }
    }
  },

  integrity_jb : function(elt, num) {
    var itemsArray = $(elt).getAttribute('data-integrity-jb-items'+num).split(',');
    var JB = $(itemsArray[0]);
    var JA = $(itemsArray[1]);
    var KJ = $(itemsArray[1]);
    if (NTD.Control.check_dependances(itemsArray, 'integrity_jb')) {
      if (parseFloat(JB.value) > parseFloat(JA.value)-parseFloat(KJ.value)) {
        NTD.Debug.trace('integrity_jb -> erreur, JB doit être inférieur ou égal à JA - KJ');
        NTD.Generic.negativ(JB);
      } else {
        NTD.Debug.trace('integrity_jb -> correct ! Intégrité du champs KG vérifiée');
        NTD.Generic.positiv(JB);
      }
    }
  },

  disable_form: function(elt, num) {
    var itemsArray = $(elt).getAttribute('disable-form-items'+num).split(',');
    var parent = $(elt).up('.formulaire-page');
    if (!$(elt).checked) {
      parent.select('select, input, textarea').each(function(field) {
        if (itemsArray.indexOf(field.id) == -1) {
          field.removeAttribute('disabled');
        }
      });
    }
    else {
      if ($('formulairetype-annexes-box')) {
        $('formulairetype-annexes-box').select('input[type=checkbox]').each(function(field) {
          field.checked = false;
          field.onclick();
        });
      }
      parent.select('select, input, textarea').each(function(field) {
        if (itemsArray.indexOf(field.id) == -1) {
          field.writeAttribute('disabled', 'disabled');
          field.value = '';

          try{
            if (field.getAttribute("name").indexOf("_opts[") != -1) {
              return;
            }
            field.onchange();
          }
          catch(error){
            console.log(elt, error, field);
          }

        }
      });
    }
  },

  integrity_gh : function(elt, num) {
    if (!$F(elt) > 0) return;
    var args = {};
    args.left = $(elt).getAttribute('data-integrity-gh-lefts'+num).split(',');
    args.right = $(elt).getAttribute('data-integrity-gh-rights'+num).split(',');
    NTD.Generic.integrity_equation(elt, args);
  },

  integrity_kt : function(elt, num) {
    var itemsArray = $(elt).getAttribute('data-integrity-kt-items'+num).split(',');
    var KT = $(itemsArray[0]);
    var KR = $(itemsArray[1]);

    var KTValue = parseFloat(KT.value);
    var KRValue = parseFloat(KR.value);
    if(!(KRValue > 0)  ) {
      NTD.Generic.none(KT);
      return;
    }

    if (((KRValue * 0.021) <= KTValue) && (KTValue <= (KRValue * 0.2))) {
      NTD.Generic.positiv(KT);
    }
    else {
      NTD.Generic.negativ(KT);
    }
  }

};
