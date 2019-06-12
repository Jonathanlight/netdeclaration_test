NTD.Ts = {

  integrity_ab_ts2501 : function(elt, num) {
    var itemsArray = $(elt).getAttribute('data-integrity-ab-ts2501-items' + num).split(',');
    var AA = $(itemsArray[0]);
    var AB = $(itemsArray[1]);
    if (NTD.Control.check_dependances([AA, AB], 'integrity_ab_ts2501')) {
      if (parseFloat(AB.value) > parseFloat(AA.value)) {
        //NTD.Debug.trace('integrity_ca -> erreur, CA doit être supérieur ou égal à BD');
        NTD.Generic.negativ(AB);
      } else {
        NTD.Generic.none(AB);
      }
    }
  },

  get_active_operand : function(operand1, operand2) {
    var FA = operand1;
    var FB = operand2;
    var active_operande = FB;
    [FA, FB].each(function(operande) {
      if ($(operande).value != 0 && $(operande).hasClassName('result')) {
        active_operande = $(operande);
        NTD.Control.setDependances([active_operande]);
      }
    });
    if (active_operande == undefined) {
      return;
    } else {
      return active_operande;
    }
  },

  calcul4_25 : function(elt, num) {
    var results = $(elt).getAttribute('data-calcul-425-results' + num).split(',');
    var result = $(results[0]);
    var operandes = $(elt).getAttribute('data-calcul-425-operands' + num).split(',');
    //console.log(results);
    var total;
    operandes.each(function(elt) {
      total = parseFloat($(elt).value) * 0.0425;
    });
    total = Math.round(total);

    NTD.Control.setValue(result, parseFloat(total), true);
    //NTD.Control.reset_operations(operandes.concat(results));
  },

  calcul1575 : function(elt, num) {
    var results = $(elt).getAttribute('data-calcul-1575-results' + num).split(',');
    var result = $(results[0]);
    var operandes = $(elt).getAttribute('data-calcul-1575-operands' + num).split(',');
    //console.log(results);
    var total;
    operandes.each(function(elt) {
      total = parseFloat($(elt).value) * 0.1575;
    });
    total = Math.round(total);

    NTD.Control.setValue(result, parseFloat(total), true);
    //NTD.Control.reset_operations(operandes.concat(results));
  },

  calcul9_35 : function(elt, num) {
    var results = $(elt).getAttribute('data-calcul-935-results' + num).split(',');
    var result = $(results[0]);
    var operandes = $(elt).getAttribute('data-calcul-935-operands' + num).split(',');
    var total;
    operandes.each(function(elt) {
      total = parseFloat($(elt).value) * 0.0935;
    });
    total = Math.round(total);
    //NTD.Debug.trace('resultat = '+results);
    //NTD.Debug.trace('operandes = '+operandes);
    NTD.Control.setValue(result, parseFloat(total), true);
    NTD.Control.reset_operations(operandes.concat(results));
  },

  calcul2_95 : function(elt, num) {
    var results = $(elt).getAttribute('data-calcul-295-results' + num).split(',');
    var result = $(results[0]);
    var operandes = $(elt).getAttribute('data-calcul-295-operands' + num).split(',');
    var total;
    operandes.each(function(elt) {
      total = parseFloat($(elt).value) * 0.0295;
    });
    total = Math.round(total);
    NTD.Control.setValue(result, parseFloat(total), true);
    NTD.Control.reset_operations(operandes.concat(results));
  },

  calcul2_55 : function(elt, num) {
    var results = $(elt).getAttribute('data-calcul-255-results' + num).split(',');
    var result = $(results[0]);
    var operandes = $(elt).getAttribute('data-calcul-255-operands' + num).split(',');
    var total;
    operandes.each(function(elt) {
      total = parseFloat($(elt).value) * 0.0255;
    });
    total = Math.round(total);
    NTD.Control.setValue(result, parseFloat(total), true);
    NTD.Control.reset_operations(operandes.concat(results));
  },


  mult_percent : function(elt, num) {
    var results = $(elt).getAttribute('data-multpercent-results' + num).split(',');
    var toOperate = $(elt).getAttribute('data-multpercent-value' + num);
    var operands = $(elt).getAttribute('data-multpercent-operands' + num).split(',');
    var total;

    operands.each(function(operande) {
      total = parseFloat($(toOperate).value) * parseFloat($(operande).value);
    });
    total = total / 100;
    total = Math.round(total);
    results.each(function(result) {
      NTD.Control.setValue($(result), parseFloat(total), true);
    });
  },

  ts_value_percent : function(elt, num) {
    var itemsArray = $(elt).getAttribute('data-ts-value-percent-items' + num).split(',');
    var item1 = $(itemsArray[0]);
    var item2 = $(itemsArray[1]);
    if (NTD.Control.check_dependances([item1], 'integrity_ce')) {
      if (parseFloat(item1.value) > 0 && (parseFloat(item2.value) < 0 || item2.value == "")) {
        //NTD.Debug.trace('integrity_ce -> erreur, si '+item1.id+' est supérieur à 0, alors '+item2.id+' doit être compris entre 0 et 100');
        NTD.Generic.negativ(item2);
      } else if (parseFloat(item1.value) > 0 && parseFloat(item2.value) > 100) {
        //NTD.Debug.trace('integrity_ce -> erreur, si '+item1.id+' est supérieur à 0, alors '+item2.id+' doit être compris entre 0 et 100');
        NTD.Generic.negativ(item2);
      } else {
        //NTD.Debug.trace('fonction integrity_cd -> L\'intégrité de '+item1.id+' est bonne');
        NTD.Generic.positiv(item2);
      }
    }
  },

  franchise_decote : function(elt, num) {
    var itemsArray = $(elt).getAttribute('data-franchise-decote-items' + num).split(',');
    var result_FA = $(itemsArray[0]);
    var result_FB = $(itemsArray[1]);
    var EM = $(itemsArray[2]);
    var total_FA;
    var total_FB;

    if (NTD.Control.check_dependances([EM], 'franchise_decote')) {
      if (EM.value < 840) {
        total_FA = $F(EM);
        total_FB = 0;
      }
      else if ($F(EM) > 840 && $F(EM) <= 1680) {
        total_FA = 0;
        total_FB = ((1680 - $F(EM)) * 3) / 4;
      }
      else {
        total_FA = 0;
        total_FB = 0;
      }
      NTD.Control.setValue(result_FA, parseFloat(total_FA));
      NTD.Control.setValue(result_FB, parseFloat(total_FB));
    }
  },
  franchise_decote_201412 : function(elt, num) {
    var itemsArray = $(elt).getAttribute('data-franchise-decote-201412-items' + num).split(',');
    var result_FA = $(itemsArray[0]);
    var result_FB = $(itemsArray[1]);
    var EM = $(itemsArray[2]);
    var total_FA;
    var total_FB;

    if (NTD.Control.check_dependances([EM], 'franchise_decote_201412')) {
      if (EM.value < 1200) {
        total_FA = $F(EM);
        total_FB = 0;
      }
      else if ($F(EM) > 1200 && $F(EM) <= 2040) {
        total_FA = 0;
        total_FB = ((2040 - $F(EM)) * 3) / 4;
      }
      else {
        total_FA = 0;
        total_FB = 0;
      }
      NTD.Control.setValue(result_FA, parseFloat(total_FA));
      NTD.Control.setValue(result_FB, parseFloat(total_FB));
    }
  },

  abattement : function(elt, num) {
    var itemsArray = $(elt).getAttribute('data-abattement-items' + num).split(',');
    var result_FC = $(itemsArray[0]);
    var EM = $(itemsArray[1]);
    var FA = $(itemsArray[2]);
    var FB = $(itemsArray[3]);
    var total;

    if (NTD.Control.check_dependances([EM, FA, FB], 'abbattement')) {
      var active_operande = NTD.Ts.get_active_operand(FA, FB);
      if ((parseFloat(EM.value) - parseFloat(active_operande.value)) < 6002) {
        total = parseFloat(EM.value) - parseFloat(active_operande.value);
        NTD.Control.setValue(result_FC, total, true);
      } else {
        total = 6002;
        NTD.Control.setValue(result_FC, total, true);
      }
      if (result_FC.value == 6002) {
        total = 0;
        //NTD.Control.setValue(result_FC, total, true);
      }
    }
  },
  abattement_201412 : function(elt, num) {
    var itemsArray = $(elt).getAt*tribute('data-abattement-201412-items' + num).split(',');
    var result_FC = $(itemsArray[0]);
    var EM = $(itemsArray[1]);
    var FA = $(itemsArray[2]);
    var FB = $(itemsArray[3]);
    var total;

    if (NTD.Control.check_dependances([EM, FA, FB], 'abattement_201412')) {
      var active_operande = NTD.Ts.get_active_operand(FA, FB);
      if ((parseFloat(EM.value) - parseFloat(active_operande.value)) < 20161) {
        total = parseFloat(EM.value) - parseFloat(active_operande.value);
        NTD.Control.setValue(result_FC, total, true);
      } else {
        total = 20161;
        NTD.Control.setValue(result_FC, total, true);
      }
      if (result_FC.value == 20161) {
        total = 0;
        //NTD.Control.setValue(result_FC, total, true);
      }
    }
  },

  taxeNetteDue : function(elt, num) {
    var itemsArray = $(elt).getAttribute('data-taxe-nette-due-items' + num).split(',');
    var result_FD = $(itemsArray[0]);
    var EM = $(itemsArray[1]);
    var FA = $(itemsArray[2]);
    var FB = $(itemsArray[3]);
    var FC = $(itemsArray[4]);
    if ($(FC).getValue() == '') $(FC).setValue(0);
    var total;
    //if (NTD.Control.check_dependances([EM, FA, FB, FC], 'taxeNetteDue')) {
      var active_operande = NTD.Ts.get_active_operand(FA, FB);
      total = parseFloat(EM.value) - (parseFloat(active_operande.value) + parseFloat(FC.value));
      NTD.Control.setValue(result_FD, total, true);
    //}
  },

  ts2501_paiement: function(elt, num) {
    var AC = $($(elt).getAttribute('data-ts2501-paiement-operands' + num));

    if ($F(AC) > 0) {
      NTD.Identif.p("showPaiement", [$F(AC)]);
    } else {
      NTD.Identif.p("hidePaiement", []);
    }
  },
  ts2502_paiement: function(elt, num) {
    var items = $(elt).getAttribute('data-ts2502-paiement-operands' + num).split(',');
    var GA = $(items[0]);

    if ($F(GA) > 0) {
      NTD.Identif.p("showPaiement", [$F(GA)]);
    } else {
      NTD.Identif.p("hidePaiement", []);
    }
  },

  ts2502_controlGB: function(elt, num) {
    var operands = $(elt).getAttribute('data-ts2502-controlgb-operands' + num).split(',');
    var GC = operands[0];
    var GD = operands[1];
    var GE = operands[2];
    var GB = $(elt).getAttribute('data-ts2502-controlgb-results' + num).split(',');
    GB = GB[0];

    NTD.Generic.none(GB);
    NTD.Generic.none(GC);
    NTD.Generic.none(GD);
    NTD.Generic.none(GE);

    $(GB).removeClassName('has-error');
    $(GC).removeClassName('has-error');
    $(GD).removeClassName('has-error');
    $(GE).removeClassName('has-error');

    if ($F(GB) > 0 || $F(GC) > 0 || $F(GD) > 0 || $F(GE) > 0) {
      var amount = isNaN(parseInt($F(GC))) ? 0 : parseInt($F(GC));
      amount += isNaN(parseInt($F(GD))) ? 0 : parseInt($F(GD));
      amount += isNaN(parseInt($F(GE))) ? 0 : parseInt($F(GE));

      if (amount <= $F(GB)) {
        NTD.Generic.positiv(GB);
        NTD.Generic.positiv(GC);
        NTD.Generic.positiv(GD);
        NTD.Generic.positiv(GE);
      }
      else {
        NTD.Generic.negativ(GB);
        NTD.Generic.negativ(GC);
        NTD.Generic.negativ(GD);
        NTD.Generic.negativ(GE);
      }
    }

    if ($F(GB) > 0 && !($F(GC) > 0 || $F(GD) > 0 || $F(GE) > 0)) {
      NTD.Generic.negativ(GC);
      NTD.Generic.negativ(GD);
      NTD.Generic.negativ(GE);
    }
  },

  ts2502_controlFC: function(elt, num) {
    var operands = $(elt).getAttribute('data-ts2502-control-fc-operands' + num).split(',');
    var EM = operands[0];
    var FA = operands[1];
    var FB = operands[2];
    var FC = $(elt).getAttribute('data-ts2502-control-fc-results' + num).split(',');
    FC = FC[0];

    NTD.Generic.none(EM);
    NTD.Generic.none(FA);
    NTD.Generic.none(FB);
    NTD.Generic.none(FC);

    if ($F(EM) > 0 || $F(FA) > 0 || $F(FB) > 0 || $F(FC) > 0) {
      var seuil = 20507;

      var amount_EM = isNaN(parseInt($F(EM))) ? 0 : parseInt($F(EM));
      var amount_FA = isNaN(parseInt($F(FA))) ? 0 : parseInt($F(FA));
      var amount_FB = isNaN(parseInt($F(FB))) ? 0 : parseInt($F(FB));

      var amount = amount_EM - (amount_FA + amount_FB);

      if ($F(FC) == 0 || ($F(FC) < seuil && $F(FC) == amount) || ($F(FC) == seuil && amount >= seuil)) {
        NTD.Generic.positiv(EM);
        NTD.Generic.positiv(FA);
        NTD.Generic.positiv(FB);
        NTD.Generic.positiv(FC);
      }
      else {
        NTD.Generic.negativ(EM);
        NTD.Generic.negativ(FA);
        NTD.Generic.negativ(FB);
        NTD.Generic.negativ(FC);
      }
    }
  },

  ts2502_calculeHB: function(elt, num) {
    var operands = $(elt).getAttribute('data-ts2502-calcule-hb-operands' + num).split(',');
    var HA = operands[0];
    var HB = $(elt).getAttribute('data-ts2502-calcule-hb-results' + num).split(',');
    HB = HB[0];

    var amount = ($F(HA) * 0.04) - 20507;

    if (amount > 0) {
      NTD.Control.setValue(HB, amount);
    }
    else {
      NTD.Control.setValue(HB, 0);
    }
  },

  ts2502_calculeHC: function(elt, num) {
    var operands = $(elt).getAttribute('data-ts2502-calcule-hc-operands' + num).split(',');
    var FD = operands[0];
    var HB = operands[1];
    var HC = $(elt).getAttribute('data-ts2502-calcule-hc-results' + num).split(',');
    HC = HC[0];

    NTD.Control.setValue(HC, Math.min($F(FD), $F(HB)));
  },

  ts2502_checkHE: function(elt, num, attribute, date) {
    var HE = $(elt).getAttribute(attribute + num).split(',');
    var CB = $(NTD.Identif.pField('CB'));
    var KF = $(NTD.Identif.pField('KF'));
    HE = HE[0];

    if(CB !== null && KF !== null && HE !== null) {
      var CB_date = moment.utc($F(CB), 'DD/MM/YYYY');
      var KF_date = moment.utc($F(KF), 'MM/YYYY');

      if ($F(HE).trim() != '') {
        if ($F(HE) > 0 && ((CB_date.isValid() && CB_date.diff(date) < 0) || (KF_date.isValid() && KF_date.diff(date) < 0))) {
          NTD.Generic.negativ(HE);
        }
        else {
          NTD.Generic.positiv(HE);
        }
      }
    }
  },

  ts2502_checkHE_2018: function(elt, num) {
    var date = moment.utc('01/02/2018', 'DD/MM/YYYY');
    NTD.Ts.ts2502_checkHE(elt, num, 'data-ts2502-check-he-2018-results', date);
  }
};
