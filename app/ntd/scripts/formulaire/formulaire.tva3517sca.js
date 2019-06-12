NTD.Tva3517sca = {
  
  integrity_aa_sca12: function(elt, num){
    var itemsArray = $(elt).getAttribute('data-integrity-aa-sca12-items'+num).split(',');
    var AA = $(itemsArray[0]);
    if(NTD.Control.check_dependances([AA], 'integrity_aa')) {
      if(AA.value != '12' && AA.value != '12E') {
        //NTD.Debug.trace('integrity_aa -> erreur, la valeur de AA doit être égal à 12 ou à 12E');
         NTD.Generic.negativ(AA);
      } else {
        NTD.Generic.positiv(AA);
      }
    }
  },  
  
  calcul_na: function(elt, num){
    //console.log('calcul_na');
		var results = $(elt).getAttribute('data-calcul-na-results'+num).split(',');
		var operands = $(elt).getAttribute('data-calcul-na-operands'+num).split(',');
		var NA = $(results[0]);
    var LA = $(operands[0]);
    var MC = $(operands[1]);
    var LB = $(operands[2]);
    var MA = $(operands[3]);
    var MB = $(operands[4]);    
    var NB = $(operands[5]); 
    var NC = $(operands[6]); 
    NTD.Control.enable_field([NA]);
    //if(NTD.Control.check_dependances(operands, 'calcul_na')){
      var total = (NTD.Number.parseFloat(LA.value) + NTD.Number.parseFloat(MC.value)) - (NTD.Number.parseFloat(LB.value) + NTD.Number.parseFloat(MA.value) + NTD.Number.parseFloat(MB.value));
      if(total < 0){
        //NTD.Control.removeValue([NA]);
        //NTD.Control.disable_field([NA]);
        NTD.Control.setValue(NA, 0);
      } else if(total == 0){
        NTD.Control.setValue(NA, 0);
      } else if(total > 0){
        NTD.Control.setValue(NA, total);
        NTD.Control.setValue(NB, 0);
        NTD.Control.setValue(NC, 0);
      } 
    //}  
  },  

  calcul_nb: function(elt, num){
		var results = $(elt).getAttribute('data-calcul-nb-results'+num).split(',');
		var operands = $(elt).getAttribute('data-calcul-nb-operands'+num).split(',');
		var NB = $(results[0]);
    var MA = $(operands[0]);
    var MB = $(operands[1]);
    var LA = $(operands[2]);
    var MC = $(operands[3]);   
    NTD.Control.enable_field([NB]);
    //if(NTD.Control.check_dependances(operands, 'calcul_nb')){
      var total = (NTD.Number.parseFloat(MA.value) + NTD.Number.parseFloat(MB.value)) - (NTD.Number.parseFloat(LA.value) + NTD.Number.parseFloat(MC.value));
      if(total < 0){
        //NTD.Control.removeValue([NB]);
        //NTD.Control.disable_field([NB]);
        NTD.Control.setValue(NB, 0);
      } else if(total == 0){
        NTD.Control.setValue(NB, 0);
      } else if(total > 0){
        NTD.Control.setValue(NB, total);
      } 
    //}  
  },
  
  calcul_nc: function(elt, num){
		var results = $(elt).getAttribute('data-calcul-nc-results'+num).split(',');
		var operands = $(elt).getAttribute('data-calcul-nc-operands'+num).split(',');
		var NC = $(results[0]);
    var LB = $(operands[0]);
    var NB = $(operands[1]);
    var MA = $(operands[2]);
    var MB = $(operands[3]);   
    var MC = $(operands[4]);   
    var total;
    
    //if(NTD.Control.check_dependances(operands, 'integrity_nc')){
      if(NB.value != ""){
        total = NTD.Number.parseFloat(LB.value) + NTD.Number.parseFloat(NB.value);
      } else {
        total = NTD.Number.parseFloat(LB.value) + NTD.Number.parseFloat(MA.value) + NTD.Number.parseFloat(MB.value) - NTD.Number.parseFloat(MC.value);
      }
      if(total > 0) {
        NTD.Control.setValue(NC, total);
      } else {
        NTD.Control.setValue(NC, 0);
      }
    //}
  },


  calcul_na_2015: function(elt, num) {
    var results = $(elt).getAttribute('data-calcul-na-2015-results' + num).split(',');
    var operands = $(elt).getAttribute('data-calcul-na-2015-operands' + num).split(',');
    var NA = $(results[0]);
    var LA = $(operands[0]);
    var LB = $(operands[1]);
    var MA = $(operands[2]);
    var NB = $(operands[3]);
    var NC = $(operands[4]);
    NTD.Control.enable_field([NA]);
    var total = (NTD.Number.parseFloat(LA.value)) - (NTD.Number.parseFloat(LB.value) + NTD.Number.parseFloat(MA.value));
    if (total < 0) {
      NTD.Control.setValue(NA, 0);
    } else if (total == 0) {
      NTD.Control.setValue(NA, 0);
    } else if (total > 0) {
      NTD.Control.setValue(NA, total);
      NTD.Control.setValue(NB, 0);
      NTD.Control.setValue(NC, 0);
    }
  },

  calcul_nb_2015: function(elt, num){
    var results = $(elt).getAttribute('data-calcul-nb-2015-results' + num).split(',');
    var operands = $(elt).getAttribute('data-calcul-nb-2015-operands' + num).split(',');
    var NB = $(results[0]);
    var MA = $(operands[0]);
    var LA = $(operands[1]);
    NTD.Control.enable_field([NB]);
    var total = (NTD.Number.parseFloat(MA.value)) - (NTD.Number.parseFloat(LA.value));
    if (total < 0) {
      NTD.Control.setValue(NB, 0);
    } else if (total == 0) {
      NTD.Control.setValue(NB, 0);
    } else if (total > 0) {
      NTD.Control.setValue(NB, total);
    }
  },

  calcul_nc_2015: function(elt, num) {
    var results = $(elt).getAttribute('data-calcul-nc-2015-results' + num).split(',');
    var operands = $(elt).getAttribute('data-calcul-nc-2015-operands' + num).split(',');
    var NC = $(results[0]);
    var LB = $(operands[0]);
    var NB = $(operands[1]);
    var MA = $(operands[2]);
    var total;
    if (NB.value != "") {
      total = NTD.Number.parseFloat(LB.value) + NTD.Number.parseFloat(NB.value);
    } else {
      total = NTD.Number.parseFloat(LB.value) + NTD.Number.parseFloat(MA.value);
    }
    if (total > 0) {
      NTD.Control.setValue(NC, total);
    } else {
      NTD.Control.setValue(NC, 0);
    }
  },

  calcul_rd: function(elt, num){
		var results = $(elt).getAttribute('data-calcul-rd-results'+num).split(',');
		var operands = $(elt).getAttribute('data-calcul-rd-operands'+num).split(',');
    NTD.Control.setDependances(operands);
    var RD = $(results[0]);
    var QN = $(operands.shift());
    var total;
    var tosubstract = NTD.Number.parseFloat(QN.value);
    var total_addition = 0;
    operands.each(function(elt){
      total_addition += NTD.Number.parseFloat($(elt).value);
    });
    total = tosubstract - total_addition;
    if(total > 0) {
      NTD.Control.setValue(RD, total);
    } 
    else {
      NTD.Control.setValue(RD, 0);
    }
    
  },  
  
  calcul_sb: function(elt, num){
		var results = $(elt).getAttribute('data-calcul-sb-results'+num).split(',');
		var operands = $(elt).getAttribute('data-calcul-sb-operands'+num).split(',');
    NTD.Control.setDependances(operands);
    var SB = $(results[0]);
    var QN = $(operands.shift());
    var total;
    var tosubstract = NTD.Number.parseFloat(QN.value);
    var total_addition = 0;
    operands.each(function(elt){
      total_addition += NTD.Number.parseFloat($(elt).value);
    });
    total = total_addition - tosubstract;
    if(total > 0) {
      NTD.Control.setValue(SB, total);
    } 
    else {
      NTD.Control.setValue(SB, 0);
    }

  },

  calcul_sb_2015: function(elt, num){
		var results = $(elt).getAttribute('data-calcul-sb-2015-results'+num).split(',');
		var operands = $(elt).getAttribute('data-calcul-sb-2015-operands'+num).split(',');
    NTD.Control.setDependances(operands);
    var SB = $(results[0]);
    var total = 0;
    operands.each(function(elt){
      total += NTD.Number.parseFloat($(elt).value);
    });
    if(total > 0) {
      NTD.Control.setValue(SB, total);
    }
    else {
      NTD.Control.setValue(SB, 0);
    }

  },
/*

  integrity_eg : function(elt, num) {
    var itemsArray = $(elt).getAttribute('data-integrity-eg-items'+num).split(',');
    var EG = $(itemsArray[0]);
    var FG = $(itemsArray[1]);

    if (NTD.Number.parseFloat(FG.value) <= 0 && NTD.Number.parseFloat(EG.value) <= 0) {
      return NTD.Generic.positiv([FG, EG], true);
    }
    if (NTD.Number.parseFloat(EG.value) > NTD.Number.parseFloat(FG.value)) {
      NTD.Debug.trace('fonction integrity_EG -> EG doit être inférieur ou égal à FG');
      NTD.Generic.negativ(EG);
    } else if (NTD.Number.parseFloat(EG.value) < 0) {
      NTD.Debug.trace('fonction integrity_EG -> EG doit être supérieur ou égal à 0');
      NTD.Generic.negativ(EG);
    } else if (NTD.Number.parseFloat(EG.value) <= NTD.Number.parseFloat(FG.value) * 0.021) {
      NTD.Debug.trace('fonction integrity_EG -> EG doit être strictement supérieur à FG * 2.10%');
      NTD.Generic.negativ(EG);
    } else if (NTD.Number.parseFloat(EG.value) >= NTD.Number.parseFloat(FG.value) * 0.200) {
      NTD.Debug.trace('fonction integrity_EG -> EG doit être strictement inférieur à FG * 20%');
      NTD.Generic.negativ(EG);
    } else {
      NTD.Debug.trace('fonction integrity_EG -> L\'intégrité de EG est bonne');
      NTD.Generic.positiv([FG, EG], true);
    }
  },
 */

  integrity_fg_3517 : function(elt, num) {
    var itemsArray = $(elt).getAttribute('data-integrity-fg-3517-items'+num).split(',');
    var FG = $(itemsArray[0]);
    var EG = $(itemsArray[1]);

    if (NTD.Number.parseFloat(EG.value) <= 0 && NTD.Number.parseFloat(FG.value) <= 0) {
      return NTD.Generic.positiv([EG, FG], true);
    }
    if (NTD.Number.parseFloat(FG.value) > NTD.Number.parseFloat(EG.value)) {
      NTD.Debug.trace('fonction integrity_FG -> FG doit être inférieur ou égal à EG');
      NTD.Generic.negativ(FG);
    } else if (NTD.Number.parseFloat(FG.value) < 0) {
      NTD.Debug.trace('fonction integrity_FG -> FG doit être supérieur ou égal à 0');
      NTD.Generic.negativ(FG);
    } else if (NTD.Number.parseFloat(FG.value) < Math.round(NTD.Number.parseFloat(EG.value) * 0.021)) {
      NTD.Debug.trace('fonction integrity_FG -> FG doit être strictement supérieur à EG * 2.10%');
      NTD.Generic.negativ(FG);
    } else if (NTD.Number.parseFloat(FG.value) > Math.round(NTD.Number.parseFloat(EG.value) * 0.206)) {
      NTD.Debug.trace('fonction integrity_FG -> FG doit être strictement inférieur à EG * 20.6%');
      NTD.Generic.negativ(FG);
    } else {
      NTD.Debug.trace('fonction integrity_FG -> L\'intégrité de FG est bonne');
      NTD.Generic.positiv([EG, FG], true);
    }
  },

  integrity_fp : function(elt, num) {
    var itemsArray = $(elt).getAttribute('data-integrity-fp-items'+num).split(',');
    var FP = $(itemsArray[0]);
    var EP = $(itemsArray[1]);

    if (NTD.Number.parseFloat(EP.value) <= 0 && NTD.Number.parseFloat(FP.value) <= 0) {
      return NTD.Generic.positiv([EP, FP], true);
    }
    if (NTD.Number.parseFloat(FP.value) > NTD.Number.parseFloat(EP.value)) {
      NTD.Debug.trace('fonction integrity_FP -> FP doit être inférieur ou égal à EP');
      NTD.Generic.negativ(FP);
    } else if (NTD.Number.parseFloat(FP.value) < 0) {
      NTD.Debug.trace('fonction integrity_FP -> FP doit être supérieur ou égal à 0');
      NTD.Generic.negativ(FP);
    } else if (NTD.Number.parseFloat(FP.value) < NTD.Number.parseFloat(EP.value) * 0.021) {
      NTD.Debug.trace('fonction integrity_FP -> FP doit être strictement supérieur à EP * 2.10%');
      NTD.Generic.negativ(FP);
    } else if (NTD.Number.parseFloat(FP.value) > NTD.Number.parseFloat(EP.value) * 0.206) {
      NTD.Debug.trace('fonction integrity_FP -> FP doit être strictement inférieur à EP * 20.6%');
      NTD.Generic.negativ(FP);
    } else {
      NTD.Debug.trace('fonction integrity_FP -> L\'intégrité de FP est bonne');
      NTD.Generic.positiv([EP, FP], true);
    }
  },

  integrity_eq : function(elt, num){
    var itemsArray = $(elt).getAttribute('data-integrity-eq-items'+num).split(',');
    var EQ = $(itemsArray[0]);
    var FP = $(itemsArray[1]);
    NTD.Generic.none(EQ);
    if(NTD.Control.check_dependances(itemsArray, 'integrity_eq')){      
      if(parseFloat(EQ.value) > parseFloat(FP.value)){
         //NTD.Debug.trace('integrity_eq -> erreur, EQ doit être inférieur ou égal à FP');
         NTD.Generic.negativ(EQ);
      } else {
       //NTD.Debug.trace('fonction integrity_eq -> L\'intégrité de EQ est bonne');
       NTD.Generic.positiv(EQ);
     }
    }
  },
  
   integrity_fe : function(elt, num){
    var itemsArray = $(elt).getAttribute('data-integrity-fe-items'+num).split(',');
    var FE = $(itemsArray[0]);
    var KD = $(itemsArray[1]);
    NTD.Generic.none(FE);
    if(NTD.Control.check_dependances(itemsArray, 'integrity_fe')){      
      if(parseFloat(FE.value) >= parseFloat(KD.value)){
         //NTD.Debug.trace('integrity_fe -> erreur, FE doit être strictement supérieur à KD');
         NTD.Generic.negativ(FE);
      } else {
       //NTD.Debug.trace('fonction integrity_fe -> L\'intégrité de FE est bonne');
       NTD.Generic.positiv(FE);
     }
    }
  },
  
  calcul_la_or_lb : function(elt, num){
    var itemsArray = $(elt).getAttribute('data-calcul-la-or-lb-items'+num).split(',');
    var LA = $(itemsArray[0]);
    var LB = $(itemsArray[1]);
    var GC = $(itemsArray[2]);
    var KD = $(itemsArray[3]);
    var total;
    //NTD.Generic.none(FE);
    if(parseFloat(GC.value) > parseFloat(KD.value)){
      total = parseFloat(GC.value - KD.value);
         NTD.Control.setValue(LA, total);
         NTD.Control.setValue(LB, 0);
         //NTD.Control.disable_field([LB]);
         //NTD.Control.removeValue([LB]);
      } else {
       total = parseFloat(KD.value - GC.value);
         NTD.Control.setValue(LB, total);
         NTD.Control.setValue(LA, 0);
         //NTD.Control.disable_field([LA]);
         //NTD.Control.removeValue([LA]);
    }
  },
  
  integrity_rb : function(elt, num){
   var itemsArray = $(elt).getAttribute('data-integrity-rb-items'+num).split(',');
   var RB = $(itemsArray[0]);
   var RA = $(itemsArray[1]);   
   if(NTD.Control.check_dependances(itemsArray, 'integrity_rb')){
     if(parseFloat(RB.value) > parseFloat(RA.value)){
       //NTD.Debug.trace('integrity_rb -> erreur, RB doit être inférieur ou égal à RA');
       NTD.Generic.negativ(RB);
     } else {
       //NTD.Debug.trace('integrity_rb -> correct ! Intégrité du champs RB vérifiée');
       NTD.Generic.positiv(RB);
     }
    }
  },
 
  calcul_va : function(elt, num){
   var results = $(elt).getAttribute('data-calcul-va-results'+num).split(',');
	 var operands = $(elt).getAttribute('data-calcul-va-operands'+num).split(',');
   var VA = $(results[0]);
   var FR = $(operands[0]);  
   var FL = $(operands[1]);  
   var FM = $(operands[2]);  
   var EQ = $(operands[3]);  
   var HC = $(operands[4]);  
   var total = NTD.Number.parseFloat(FR.value);
   var total_addition = 0;
   //if(NTD.Control.check_dependances(operands, 'calcul_va')){
   total_addition = NTD.Number.parseFloat(FL.value) + NTD.Number.parseFloat(FM.value) + NTD.Number.parseFloat(EQ.value) + NTD.Number.parseFloat(HC.value);
   total -= total_addition;
   if(total > 0) {
      NTD.Control.setValue(VA, total);
    } else {
      NTD.Control.setValue(VA, 0);
    }
   // }
  },
  
  calcul_nj : function(elt, num){
    var results = $(elt).getAttribute('data-calcul-nj-results'+num).split(',');
    var operands = $(elt).getAttribute('data-calcul-nj-operands'+num).split(',');
    var NJ = $(results[0]);
    var NG = $(operands[0]);  
    var NH = $(operands[1]);  
    var LB = $(operands[2]);  
    var total;
    if(NTD.Control.check_dependances(operands, 'calcul_nj')){
      if(LB.value < 150) {
        total = parseFloat(NG.value) + parseFloat(NH.value) - parseFloat(LB.value);
      } else {
        total = parseFloat(NG.value) + parseFloat(NH.value)
      }
      NTD.Control.setValue(NJ, total);
    }
  },
  
  disable_all : function(elt, num) {
    //console.log('disable_all');
    var itemsArray = $(elt).getAttribute('data-disable-all-items'+num).split(',');
    var SD = $(itemsArray).pop();
    //console.log(SD);
    if($(SD).checked) {
      NTD.Control.disable_field($$('.field'));
      NTD.Control.enable_field(itemsArray.concat([SD]));
    } else {
      NTD.Control.enable_field($$('.field'));
    }
  },
  paiement_3517sca12: function(elt, num){

    var SC = $($(elt).getAttribute('data-paiement_3517sca12-operands' + num));

     if ($F(SC) > 0) {
      NTD.Identif.t("showPaiement", [$F(SC)]);
    } else {
      NTD.Identif.t("hidePaiement", []);
     }
  }

};
