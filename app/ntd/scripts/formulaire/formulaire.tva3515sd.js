NTD.Tva3515sd = {
  
  integrity_ca_3515sd : function(elt, num){
     var itemsArray = $(elt).getAttribute('data-integrity-ca-3515sd-items'+num).split(',');
     var CA = $(itemsArray[0]);
     var BD = $(itemsArray[1]);   
     if(NTD.Control.check_dependances([BD], 'integrity_ca')){
       if(parseFloat(CA.value) < parseFloat(BD.value)){
         //NTD.Debug.trace('integrity_ca -> erreur, CA doit être supérieur ou égal à BD');
         NTD.Generic.negativ(CA);
       } else if(parseFloat(CA.value) >= parseFloat(BD.value)){
         //NTD.Debug.trace('integrity_ca -> correct ! Intégrité du champs CA vérifiée');
         NTD.Generic.positiv(CA);
       } else {
         NTD.Generic.none(CA);
       }
     }
  },
  
  report_BC_BD : function(elt, num){
     var itemsArray = $(elt).getAttribute('data-report-BC-BD-items'+num).split(',');
     var result_CB = $(itemsArray[0]);
     var result_CA = $(itemsArray[1]);
     var BC = $(itemsArray[2]);   
     var BD = $(itemsArray[3]);   
     if(NTD.Control.check_dependances([BC, BD], 'report_BC_BD')){       
       if(parseFloat(BC.value) < parseFloat(BD.value)){
         NTD.Control.setValue(result_CA, BD.value, true);
         NTD.Control.setValue(result_CB, 0, true);
       } else if(parseFloat(BC.value) > parseFloat(BD.value)){
         NTD.Control.setValue(result_CB, BC.value, true);
         NTD.Control.setValue(result_CA, 0, true);
       }      
     }
  },
  
  soustraction_da_db_3515sd : function(elt, num){
     var itemsArray = $(elt).getAttribute('data-soustraction-da-db-3515sd-items'+num).split(',');
     var result_DC = $(itemsArray[0]);
     var result_DD = $(itemsArray[1]);   
     var DA = $(itemsArray[2]);   
     var DB = $(itemsArray[3]);   
     var total;
     if(NTD.Control.check_dependances([DA, DB], 'soustraction_da_db_3515sd')){
       total = parseFloat(DA.value) - parseFloat(DB.value)
       if(total < 0){
         NTD.Control.setValue(result_DD, Math.abs(total), true);
         NTD.Control.setValue(result_DC, 0, true);
       } else if (total > 0) {
         NTD.Control.setValue(result_DC, Math.abs(total), true);
         NTD.Control.setValue(result_DD, 0, true);
       } else {
         NTD.Control.setValue(result_DC, 0, true);
         NTD.Control.setValue(result_DD, 0, true);
       }
     }
  }
}


