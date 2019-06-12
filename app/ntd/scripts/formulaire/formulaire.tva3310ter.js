NTD.tva3310ter = {
  
  check_non_egal_to_zero : function(elt, num){
    var results = $(elt).getAttribute('data-check-non-egal-to-zero-results'+num).split(',');
    var operandes = $(elt).getAttribute('data-check-non-egal-to-zero-operands'+num).split(',');
	
    results.each(function(result){
       if(NTD.Number.parseFloat($(operandes[0]).value) == NTD.Number.parseFloat($(operandes[1]).value)) {
				 if(NTD.Number.parseFloat($(operandes[0]).value) == 0 || NTD.Number.parseFloat($(operandes[1]).value) == 0) {
					   NTD.Generic.negativ(result);
					   NTD.Generic.negativ(result);
					 }
				 else {
					   NTD.Generic.none(result);
					   NTD.Generic.none(result);
					 } 
		   }
    });
  },
  
  
  
  calcul_qm : function(elt, num){
    var itemsArray = $(elt).getAttribute('data-calcul-qm-items'+num).split(',');
    var result_QM = $(itemsArray[0]);
    var QL = $(itemsArray[1]);
    var SL = $(itemsArray[2]);
    var RL = $(itemsArray[3]);
    var total;
    
    if(NTD.Control.check_dependances([QL, SL, RL], 'calcul_qm')){   
      if(QL.value == "" || SL.value == "" || RL.value== "" ) {
        total = 0;
        NTD.Control.setValue(result_QM, NTD.Number.parseFloat(total), true);
      } else {
        total = (NTD.Number.parseFloat(QL.value) + NTD.Number.parseFloat(SL.value)) - NTD.Number.parseFloat(RL.value);
        NTD.Control.setValue(result_QM, NTD.Number.parseFloat(total), true);
        if(total < 0) {
          total = 0;
          NTD.Control.setValue(result_QM, NTD.Number.parseFloat(total), true);
        }
      }
    }  
  },
 
  calcul_qm_2014 : function(elt, num){
    var itemsArray = $(elt).getAttribute('data-calcul-qm-2014-items'+num).split(',');
    var result_QM = $(itemsArray[0]);
    var QL = $(itemsArray[1]);
    var RL = $(itemsArray[2]);
    var total;

    if(NTD.Control.check_dependances([QL, RL], 'calcul_qm_2014')){
      if(QL.value == "" || RL.value== "" ) {
        total = 0;
        NTD.Control.setValue(result_QM, NTD.Number.parseFloat(total), true);
      } else {
        total = NTD.Number.parseFloat(QL.value) - NTD.Number.parseFloat(RL.value);
        NTD.Control.setValue(result_QM, NTD.Number.parseFloat(total), true);
        if(total < 0) {
          total = 0;
          NTD.Control.setValue(result_QM, NTD.Number.parseFloat(total), true);
        }
      }
    }
  },
 
  calcul_rm : function(elt, num){
    var itemsArray = $(elt).getAttribute('data-calcul-rm-items'+num).split(',');
    var result_RM = $(itemsArray[0]);
    var RL = $(itemsArray[1]);
    var QL = $(itemsArray[2]);
    var SL = $(itemsArray[3]);
    var total;
    if(RL.value == "" || QL.value == "" || SL.value== "" ) {
		  total = 0;
		  NTD.Control.setValue(result_RM, NTD.Number.parseFloat(total), true);
		} else {
		  total = NTD.Number.parseFloat(RL.value) - (NTD.Number.parseFloat(QL.value) + NTD.Number.parseFloat(SL.value));
		  NTD.Control.setValue(result_RM, NTD.Number.parseFloat(total), true);
		  if(total < 0) {
        total = 0;
        NTD.Control.setValue(result_RM, NTD.Number.parseFloat(total), true);
      }  
		}
  },

  calcul_rm_2014 : function(elt, num){
    var itemsArray = $(elt).getAttribute('data-calcul-rm-2014-items'+num).split(',');
    var result_RM = $(itemsArray[0]);
    var RL = $(itemsArray[1]);
    var QL = $(itemsArray[2]);
    var total;
    if(RL.value == "" || QL.value == "") {
                  total = 0;
                  NTD.Control.setValue(result_RM, NTD.Number.parseFloat(total), true);
                } else {
                  total = NTD.Number.parseFloat(RL.value) - (NTD.Number.parseFloat(QL.value));
                  NTD.Control.setValue(result_RM, NTD.Number.parseFloat(total), true);
                  if(total < 0) {
        total = 0;
        NTD.Control.setValue(result_RM, NTD.Number.parseFloat(total), true);
      }
                }
  }
}
