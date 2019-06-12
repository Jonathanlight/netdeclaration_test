NTD.Tva3514 = {

  /*calcul_gf:  function(elt, num){
   var results = $(elt).getAttribute('data-calcul-gf-results'+num).split(',');
   var operands = $(elt).getAttribute('data-calcul-gf-operands'+num).split(',');

   if (parseFloat($(operands[0]).value) != 0)
   NTD.Control.setValue(results[0], 0, true);
   else
   NTD.Control.removeValue(results.concat(results));
   },*/
  calcul_gf:  function(elt, num) {
    var gf = $(elt).getAttribute('data-calcul-gf-results' + num).split(',')[0];
    var gd = $(elt).getAttribute('data-calcul-gf-operands' + num).split(',')[0];


    if (!isNaN(parseFloat($F(gd)))) {
      NTD.Control.setValue(gf, 0);
    }
    else {
      //NTD.Control.setValue(results[0], 0);
      NTD.Control.removeValue([gf]);
    }
  },

  disable_on_da : function(elt, num) {
    var itemsArray = $(elt).getAttribute('data-disable-on-da-items' + num).split(',');
    var DA = $(itemsArray.shift());
    if (DA.value != "" && !DA.hasClassName('edited')) {
      DA.addClassName('edited');
      NTD.Control.disable_field(itemsArray);
    } else if (DA.value == "") {
      DA.removeClassName('edited');
      NTD.Control.enable_field(itemsArray);
    }
  },

  disable_on_db : function(elt, num) {
    var itemsArray = $(elt).getAttribute('data-disable-on-db-items' + num).split(',');
    var DB = $(itemsArray.shift());
    var DC = $(itemsArray.shift());
    if (DC.value != "") {

    } else if (DB.value != "" && !DB.hasClassName('edited')) {
      DB.addClassName('edited');
      NTD.Control.disable_field(itemsArray);
    } else if (DB.value == "") {
      DB.removeClassName('edited');
      NTD.Control.enable_field(itemsArray);
    }
  },
  
  disable_on_aa : function(elt, num) {
    var itemsArray = $(elt).getAttribute('data-disable-on-aa-items' + num).split(',');
    var AA = $(itemsArray.shift());
    if (parseFloat(AA.value) > 0) {
      $$('.disable-for-aa').each(function(el){
        ntd.formulaire.onDisabled(el);
      });
    }
    else {
      $$('.disable-for-aa').each(function(el){
        ntd.formulaire.onEnabled(el);
      });
    }
    
  },

  integrity_dc : function(elt, num) {
    var itemsArray = $(elt).getAttribute('data-integrity-dc-items' + num).split(',');
    var DC = $(itemsArray[0]);
    var DB = $(itemsArray[1]);
    if (DB.value == "") {
      NTD.Generic.none(DC);
    } else if (parseFloat(DB.value) > 0 && DC.value == "") {
      //NTD.Debug.trace('integrity_ce -> erreur, si DB est supérieur à 0, alors DC doit être rempli');
      NTD.Generic.negativ(DC);
    } else {
      //NTD.Debug.trace('fonction integrity_cd -> L\'intégrité de DC est bonne');
      NTD.Generic.positiv(DC);
    }
  },

  integrity_db : function(elt, num) {
    var itemsArray = $(elt).getAttribute('data-integrity-db-items' + num).split(',');
    var DB = $(itemsArray[0]);
    var DC = $(itemsArray[1]);
    if (DC.value == "") {
      NTD.Generic.none(DB);
    } else if (parseFloat(DC.value) > 0 && DB.value == "") {
      //NTD.Debug.trace('integrity_ce -> erreur, si DB est supérieur à 0, alors DC doit être rempli');
      NTD.Generic.negativ(DB);
    } else {
      //NTD.Debug.trace('fonction integrity_cd -> L\'intégrité de DC est bonne');
      NTD.Generic.positiv(DB);
    }
  },

  integrity_id : function(elt, num) {
    var itemsArray = $(elt).getAttribute('data-integrity-id-items' + num).split(',');
    var ID = $(itemsArray[0]);
    var IC = $(itemsArray[1]);
    if (NTD.Number.parseFloat(ID.value) > 0) {
      if (NTD.Number.parseFloat(ID.value) <= 760) {
        NTD.Debug.trace('fonction integrity_id -> ID doit être inférieur ou égal à 760');
        NTD.Generic.negativ(ID);
      } else if (NTD.Number.parseFloat(ID.value) > NTD.Number.parseFloat(IC.value)) {
        NTD.Debug.trace('fonction integrity_id -> ID doit être inférieur à IC');
        NTD.Generic.negativ(ID);
      }
    }
  },

  disable_on_dc : function(elt, num) {
    var itemsArray = $(elt).getAttribute('data-disable-on-dc-items' + num).split(',');
    var DC = $(itemsArray.shift());
    var DB = $(itemsArray.shift());
    if (DB.value != "") {

    } else if (DC.value != "" && !DC.hasClassName('edited')) {
      DB.addClassName('edited');
      NTD.Control.disable_field(itemsArray);
    } else {
      DB.removeClassName('edited');
      NTD.Control.enable_field(itemsArray);
    }
  },

  disable_if_dd_checked : function(elt, num) {
    var itemsArray = $(elt).getAttribute('data-disable-if-dd-checked-items' + num).split(',');
    var DD = $(itemsArray[0]);
    var DF = $(itemsArray[1]);
    var DA = $(itemsArray[2]);
    var DC = $(itemsArray[3]);
    NTD.Generic.none(DF);
    if (DD.checked) {
      NTD.Tva3514.integrity_dd([DD, DF]);
      if (!DF.hasClassName('edited')) {
        DF.addClassName('edited');
        NTD.Control.disable_field_count([DA, DC]);
      }
    } else if (DF.hasClassName('edited')) {
      DF.removeClassName('edited');
      NTD.Control.enable_field_count([DA, DC]);
    } else if (DF.value != "") {
      DD.checked = true;
      DD.onchange();
    }
  },

  integrity_dd : function(itemsArray) {
    var DF = $(itemsArray[1]);
    if (parseFloat(DF.value) <= 0 || DF.value == "") {
      //NTD.Debug.trace('integrity_de_checked -> erreur, si DD est cochée, alors DF doit être supérieur à 0');
      NTD.Generic.negativ(DF);
    } else {
      //NTD.Debug.trace('fonction integrity_de_checked -> Les conditions liées à DD cochée sont correctes');
      NTD.Generic.positiv(DF);
    }
  },

  disable_if_de_checked : function(elt, num) {
    var itemsArray = $(elt).getAttribute('data-disable-if-de-checked-items' + num).split(',');
    var DE = $(itemsArray[0]);
    var DA = $(itemsArray[1]);
    var DC = $(itemsArray[2]);
    if (DE.checked) {
      NTD.Control.disable_field_count([DA, DC]);
    } else {
      NTD.Control.enable_field_count([DA, DC]);
    }
  },

  calcul_ga_gb : function(elt, num) {
    var itemsArray = $(elt).getAttribute('data-calcul-ga-gb-items' + num).split(',');
    var result_GA = $(itemsArray[0]);
    var result_GB = $(itemsArray[1]);
    var ES = $(itemsArray[2]);
    var FD = $(itemsArray[3]);

    var GC = $(itemsArray[4]);
    var GD = $(itemsArray[5]);
    var GF = $(itemsArray[6]);
    var GH = $(itemsArray[7]);
    var GK = $(itemsArray[8]);

    var total;
    //NTD.Control.setDependances([ES, FD]);
    if (ES.value == "") ES.value = 0;
    if (FD.value == "") FD.value = 0;
    //if(NTD.Control.check_dependances([FD, ES], 'calcul_ga_gb')){      
    if (parseFloat(ES.value) > parseFloat(FD.value)) {
      total = parseFloat(ES.value) - parseFloat(FD.value);
      NTD.Control.setValue(result_GA, total, true);
      result_GB.addClassName('stay_operand');
      GC.addClassName('stay_operand');
      GD.addClassName('stay_operand');
      GF.addClassName('stay_operand');
      GH.addClassName('stay_operand');
      GK.addClassName('stay_operand');
      NTD.Control.setValue(result_GB, 0, true);
      NTD.Control.setValue(GC, 0, true);
      NTD.Control.setValue(GD, 0, true);
      NTD.Control.setValue(GF, 0, true);
      NTD.Control.setValue(GH, 0, true);
      NTD.Control.setValue(GK, 0, true);
    } else if (parseFloat(ES.value) < parseFloat(FD.value)) {
      total = parseFloat(FD.value) - parseFloat(ES.value);
      result_GB.removeClassName('stay_operand');
      GC.removeClassName('stay_operand');
      GD.removeClassName('stay_operand');
      GF.removeClassName('stay_operand');
      GH.removeClassName('stay_operand');
      GK.removeClassName('stay_operand');
      NTD.Control.removeValue([GC, GD, GF, GH, GK]);
      NTD.Control.setValue(result_GB, total, true);
      NTD.Control.setValue(result_GA, 0, true);
    } else {
      NTD.Control.setValue(result_GB, 0, true);
      NTD.Control.setValue(result_GA, 0, true);
    }
    //}
    NTD.Control.reset_operations(itemsArray);
  },

  disable_on_dg : function(elt, num) {
    var itemsArray = $(elt).getAttribute('data-disable-on-dg-items' + num).split(',');
    var DG = $(itemsArray.shift());
    if (DG.value != "") {
      if (!DG.hasClassName('edited')) {
        DG.addClassName('edited');
        NTD.Control.disable_field_count(itemsArray);
      }
    } else if (DG.value == "") {
      if (DG.hasClassName('edited')) {
        DG.removeClassName('edited');
        NTD.Control.enable_field_count(itemsArray);
      }
    }
  },

  integrity_gc_3514 : function(elt, num) {
    var itemsArray = $(elt).getAttribute('data-integrity-gc-3514-items' + num).split(',');
    var result_GC = $(itemsArray[0]);
    var FA = $(itemsArray[1]);
    var GB = $(itemsArray[2]);
    if (NTD.Control.check_dependances(itemsArray, 'integrity_gc')) {
      if (parseFloat(result_GC.value) > 0) {
        if ((parseFloat(result_GC.value) > parseFloat(FA.value)) || (parseFloat(result_GC.value) > parseFloat(GB.value))) {
          //NTD.Debug.trace('integrity_gc -> erreur, si GC est supérieur à 0, alors GC doit être inférieur ou égal à FA ET GC doit être inférieur ou égal à GB');
          NTD.Generic.negativ(result_GC);
        } else {
          //NTD.Debug.trace('fonction integrity_gc -> L\'intégrité du champs GC est correcte');
          NTD.Generic.positiv(result_GC);
        }
      }
    }
  },

  calcul_gg_3514 : function(elt, num) {
    //console.log('calcul_gg_3514');
    var itemsArray = $(elt).getAttribute('data-calcul-gg-3514-items' + num).split(',');
    var GG = $(itemsArray[0]);
    var GA = $(itemsArray[1]);
    var GE = $(itemsArray[2]);
    var total;

    var ga = parseFloat($F(GA));
    var ge = parseFloat($F(GE));

    if (isNaN(ga)) ga = 0;
    if (isNaN(ge)) ge = 0;

    total = ga - ge;
    total = (total > 0) ? total : 0;
    NTD.Control.setValue(GG, total, true);
  },

  integrity_gk_gl : function(elt, num) {
    var itemsArray = $(elt).getAttribute('data-integrity-gk-gl-items' + num).split(',');
    var EA = $(itemsArray[0]);
    var EB = $(itemsArray[1]);
    var GK = $(itemsArray[2]);
    var GL = $(itemsArray[3]);
    if (NTD.Control.check_dependances([GK, GL], 'integrity_gk_gl', 'one_of_item')) {
      if (GK.value > 0 || GL.value > 0) {
        if (parseFloat(EA.value) == "") {
          NTD.Generic.negativ(EA);
        }
        else if (parseFloat(EB.value) == "") {
          NTD.Generic.negativ(EB);
        }
        else {
          NTD.Generic.positiv(EA);
          NTD.Generic.positiv(EB);
        }
      }
    }
  },
  paiement:function(elt, num) {    
    var items = $(elt).getAttribute('data-tva3514-paiement-operands' + num).split(',');
    var GK = $(items[0]);
    var GL = $(items[1]);
    var AA = $(items[2]);
    if ($F(AA) > 0 ) {
      NTD.Identif.t("showPaiement", [$F(AA)]);
    }
    else if($F(GL) > 0) {
      NTD.Identif.t("showPaiement", [$F(GL)]);
    }
    else {      
      NTD.Identif.t("hidePaiement", []);
    }
  },

  paiement_20140101:function(elt, num) {
    var items = $(elt).getAttribute('data-tva3514-20140101-paiement-operands' + num).split(',');
    var GC = $(items[0]);
    if ($F(GC) > 0 ) {
      NTD.Identif.t("showPaiement", [$F(GC)]);
    }
    else {
      NTD.Identif.t("hidePaiement", []);
    }
  },


  check_dw_dg: function(elt, num){    
    var DW = $($(elt).readAttribute('data-check-dw-dg-operands'+num));
    var DG = $($(elt).readAttribute('data-check-dw-dg-results'+num));

    NTD.Generic.none(DG);
    if(DW.checked){
      if(!(parseFloat($F(DG) >= 0))) {
        NTD.Generic.negativ(DG);
      }
    }else{
      DG.setValue('');
    }    
  },

  general_tva3514_20150101: function(elt, num) {
    console.log('general_tva3514_20150101');

    var $f = function(fieldName){ return 'tva3514_20150101'+ '_' + fieldName };

    var fieldLabels = {
      'HA' : 'Ligne 01',
      'HB' : 'Ligne 02',
      'HC' : 'Ligne 03',
      'DE' : 'Ligne 04',
      'IA' : 'Ligne 05',
      'IB' : 'Ligne 06',
      'IC' : 'Ligne 07',
      'ID' : 'Ligne 08',
      'CC' : 'Mention express',
      '<' : 'doit être strictement inférieur à',
      '<=' : 'doit être inférieur ou égal à',
      '>' : 'doit être strictement supérieur à',
      '>=' : 'doit être supérieur ou égal à'
    };
    //var $_l = window.$_l.bind(this, fieldLabels);

    var $HA = $elt('tva3514_20150101_HA');
    var $HB = $elt('tva3514_20150101_HB');
    var $HC = $elt('tva3514_20150101_HC');
    var $DE = $elt('tva3514_20150101_DE');
    var $IA = $elt('tva3514_20150101_IA');
    var $IB = $elt('tva3514_20150101_IB');
    var $IC = $elt('tva3514_20150101_IC');
    var $ID = $elt('tva3514_20150101_ID');
    var $CA = $elt('tva3514_20150101_CA');
    var $CB = $elt('tva3514_20150101_CB');
    var $CC = $elt('tva3514_20150101_CC');



    // ---- Control
    if ($float($f('HA')) > 0 || $float($f('HB')) > 0 || $elt($f('DE')).checked > 0){
      $readonly($elt($f('IA')), true).setValue('');
      $readonly($elt($f('IB')), true).setValue('');
      $readonly($elt($f('ID')), true).setValue('');

      $readonly($elt($f('HA')), false);
      $readonly($elt($f('HB')), false);
      $readonly($elt($f('DE')), false);
    }
    else if ($float($f('IA')) > 0 || $float($f('IB')) > 0 || $float($f('ID')) > 0){
      $readonly($elt($f('HA')), true).setValue('');
      $readonly($elt($f('HB')), true).setValue('');
      $readonly($elt($f('DE')), true);
      $elt($f('DE')).checked = false;

      $readonly($elt($f('IA')), false);
      $readonly($elt($f('IB')), false);
      $readonly($elt($f('ID')), false);
    }
    else{
      var fields = ['HA',
                    'HB',
                    'DE',
                    'IA',
                    'IB',
                    'ID'];
      for(var i = 0; i< fields.length; i++) {
        $readonly($elt($f(fields[i])), false);
      }
    }

    // --- IC = IB - IA
    $readonly($elt($f('IC')), true);
    $value($f('IC'), '');
    if ($float($f('IB')) > 0 && $float($f('IA')) > 0) {
      $value($f('IC'), Math.max(0, $float($f('IB')) - $float($f('IA'))));
    }
    // --- HC = HA - HB
    $readonly($elt($f('HC')), true);
    $value($f('HC'), '');
    if ($float($f('HA')) > 0 && $float($f('HB')) > 0) {
      $value($f('HC'), Math.max(0, $float($f('HA')) - $float($f('HB'))));
    }

    // --- show Tidenf form
    NTD.Identif.t("hidePaiement", []);
    if ($float($f('HC')) > 0) {
      NTD.Identif.t("showPaiement", [$float($f('HC'))]);
    }


    $assert(!($isServi($HA)
            && ($isServi($IA)
            || $isServi($IB)
            || $isServi($IC)
            || $isServi($ID))),
            [$HA, $IA, $IB, $IC, $ID],
            'erreur_217');
    $assert(!($isServi($HB)
            && ($isServi($IA)
            || $isServi($IB)
            || $isServi($IC)
            || $isServi($ID))),
            [$HB, $IA, $IB, $IC, $ID],
            'erreur_217');
    $assert(!($isServi($DE)
            && ($isServi($IA)
            || $isServi($IB)
            || $isServi($IC)
            || $isServi($ID))),
            [$DE, $IA, $IB, $IC, $ID],
            'erreur_217');
    $assert(!($isServi($HB) && !($isServi($HA) && ($HA <= $HB))), [$HA, $HB], 'erreur_213');
    $assert(!($DE.checked && !($isServi($HA) && $float($HA) > 0)), $HA, 'erreur_216');
    $assert(!(($isServi($IB) && $float($IB) >= 0 && !($float($IA) < $float($IB)))
    || (!$isServi($IB) && $float($IA) > 0)), [$IA, $IB], 'erreur_214');
    $assert(!($isServi($ID) && !(760 <= $float($ID) && $float($ID) <= $float($IC))), [$ID, $IC], 'erreur_215');
    $assert(!($isServi($IA)
            && ($isServi($HA)
            || $isServi($HB)
            || $isServi($HC)
            || $isServi($DE))),
            [$IA, $HA, $HB, $HC, $DE],
            'erreur_217');
    $assert(!($isServi($IB)
            && ($isServi($HA)
            || $isServi($HB)
            || $isServi($HC)
            || $isServi($DE))),
            [$IB, $HA, $HB, $HC, $DE],
            'erreur_217');
    $assert(!($isServi($ID)
            && ($isServi($HA)
            || $isServi($HB)
            || $isServi($HC)
            || $isServi($DE))),
            [$ID, $HA, $HB, $HC, $DE],
            'erreur_217');
    $assert(!($isServi($CC)
            && !$isServi($CB)),
            [$CB, $CC],
            'erreur_128');
    $assert([$HA, $HB, $HC, $DE, $IA, $IB, $IC, $ID, $CA, $CB, $CC].some(function(elt) {
      return $isServi(elt);
    }), [$HA, $HB, $HC, $DE, $IA, $IB, $IC, $ID, $CA, $CB, $CC], 'erreur_201');
  }
};


