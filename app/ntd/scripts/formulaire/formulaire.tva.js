NTD.Tva = {
  
  calcul0_90 : function(elt, num){
    var results = $(elt).getAttribute('data-calcul-090-results'+num).split(',');
    var result = $(results[0]);
    var operandes = $(elt).getAttribute('data-calcul-090-operands'+num).split(',');
    var total;
    operandes.each(function(elt){
      total = parseFloat($(elt).value) * 0.009;
    });
    NTD.Control.setValue(result, parseFloat(total));
    NTD.Control.reset_operations(operandes.concat(results));
  },  
  
  calcul1_05 : function(elt, num){
    var results = $(elt).getAttribute('data-calcul-105-results'+num).split(',');
    var result = $(results[0]);
    var operandes = $(elt).getAttribute('data-calcul-105-operands'+num).split(',');
    var total;
    operandes.each(function(elt){
      total = parseFloat($(elt).value) * 0.0105;
    });
    NTD.Control.setValue(result, parseFloat(total));
    NTD.Control.reset_operations(operandes.concat(results));
  },
  
  calcul1_75 : function(elt, num){
    var results = $(elt).getAttribute('data-calcul-175-results'+num).split(',');
    var result = $(results[0]);
    var operandes = $(elt).getAttribute('data-calcul-175-operands'+num).split(',');
    var total;
    operandes.each(function(elt){
      total = parseFloat($(elt).value) * 0.0175;
    });
    NTD.Control.setValue(result, parseFloat(total));
    NTD.Control.reset_operations(operandes.concat(results));
  },
  
  calcul2_10 : function(elt, num){
    var results = $(elt).getAttribute('data-calcul-210-results'+num).split(',');
    var result = $(results[0]);
    var operandes = $(elt).getAttribute('data-calcul-210-operands'+num).split(',');
    var total;
    operandes.each(function(elt){
      total = parseFloat($(elt).value) * 0.0210;
    }, this);
    NTD.Control.setValue(result, parseFloat(total));
    NTD.Control.reset_operations(operandes.concat(results));
  },
  
  calcul5_50 : function(elt, num){
    var results = $(elt).getAttribute('data-calcul-550-results'+num).split(',');
    var result = $(results[0]);
    var operandes = $(elt).getAttribute('data-calcul-550-operands'+num).split(',');
    var total;
    operandes.each(function(elt){
      total = parseFloat($(elt).value) * 0.055;
    });
    NTD.Control.setValue(result, parseFloat(total));
    NTD.Control.reset_operations(operandes.concat(results));
  },

  calcul7_00 : function(elt, num){
    var results = $(elt).getAttribute('data-calcul-700-results'+num).split(',');
    var result = $(results[0]);
    var operandes = $(elt).getAttribute('data-calcul-700-operands'+num).split(',');
    var total;
    operandes.each(function(elt){
      total = parseFloat($(elt).value) * 0.070;
    });
    NTD.Control.setValue(result, parseFloat(total));
    NTD.Control.reset_operations(operandes.concat(results));
  },

  calcul8_00 : function(elt, num){
    var results = $(elt).getAttribute('data-calcul-800-results'+num).split(',');
    var result = $(results[0]);
    var operandes = $(elt).getAttribute('data-calcul-800-operands'+num).split(',');
    var total;
    operandes.each(function(elt){
      total = parseFloat($(elt).value) * 0.08;
    });
    NTD.Control.setValue(result, parseFloat(total));
    NTD.Control.reset_operations(operandes.concat(results));
  },   
  
  calcul8_50 : function(elt, num){
    var results = $(elt).getAttribute('data-calcul-850-results'+num).split(',');
    var result = $(results[0]);
    var operandes = $(elt).getAttribute('data-calcul-850-operands'+num).split(',');
    var total;
    operandes.each(function(elt){
      total = parseFloat($(elt).value) * 0.085;
    });
    NTD.Control.setValue(result, parseFloat(total));
    NTD.Control.reset_operations(operandes.concat(results));
  },  
  
   calcul10_00 : function(elt, num){
    var results = $(elt).getAttribute('data-calcul-1000-results'+num).split(',');
    var result = $(results[0]);
    var operandes = $(elt).getAttribute('data-calcul-1000-operands'+num).split(',');
    var total;
    operandes.each(function(elt){
      total = parseFloat($(elt).value) * 0.1000;
    });
    NTD.Control.setValue(result, parseFloat(total));
    NTD.Control.reset_operations(operandes.concat(results));
  },
 
  calcul13_00 : function(elt, num){
    var results = $(elt).getAttribute('data-calcul-1300-results'+num).split(',');
    var result = $(results[0]);
    var operandes = $(elt).getAttribute('data-calcul-1300-operands'+num).split(',');
    var total;
    operandes.each(function(elt){
      total = parseFloat($(elt).value) * 0.1300;
    });
    NTD.Control.setValue(result, parseFloat(total));
    NTD.Control.reset_operations(operandes.concat(results));
  },  
  
  calcul19_60 : function(elt, num){
    var results = $(elt).getAttribute('data-calcul-1960-results'+num).split(',');
    var result = $(results[0]);
    var operandes = $(elt).getAttribute('data-calcul-1960-operands'+num).split(',');
    var total;
    operandes.each(function(elt){
      total = parseFloat($(elt).value) * 0.1960;
    });
    NTD.Control.setValue(result, parseFloat(total));
    NTD.Control.reset_operations(operandes.concat(results));
  },

  calcul20_00 : function(elt, num){
    var results = $(elt).getAttribute('data-calcul-2000-results'+num).split(',');
    var result = $(results[0]);
    var operandes = $(elt).getAttribute('data-calcul-2000-operands'+num).split(',');
    var total;
    operandes.each(function(elt){
      total = parseFloat($(elt).value) * 0.2000;
    });
    NTD.Control.setValue(result, parseFloat(total));
    NTD.Control.reset_operations(operandes.concat(results));
  },

  calcul_percent:function(elt, args){   
    var result  = $(args['result']);
    var percent = args['percent'];
    var value   = Object.isString(args['value']) && $(args['value']) ? $(args['value']).value : $F(elt);
    
    if (!result) return;
    if (Object.isString(percent) && $(percent)) percent = $(percent).value;
    var total = parseFloat(value) * (percent / 100);
    NTD.Control.setValue(result, parseFloat(total));
    //NTD.Control.reset_operations(result);
  },

  paiement_3517ddr:function(elt, num) {
    NTD.Identif.t("hidePaiement", []);
  }

};
