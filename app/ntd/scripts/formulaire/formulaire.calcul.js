if (!Formulaire) var Formulaire = {};

Formulaire.calcul = {

  ifCheckboxThenMultiplyFieldByPercent: function(elt, args, params) {
    //log('Formulaire.calcul.ifCheckboxThenMultiplyFieldByPercent()');
    var formulaire_code = params['formulaire_code'];

    var checkbox = $(formulaire_code + '_' + args['checkbox']);
    var field = $(formulaire_code + '_' + args['field']);
    var result_field = $(formulaire_code + '_' + args['result_field']);
    var percent = args['percent'];
    if (!checkbox.checked) {
      NTD.Control.setValue(result_field, $F(field) * percent);
    }
    else {
      NTD.Control.setValue(result_field, 0);
    }
  },

  itemsSumAndPercent: function(elt, args, params) {
    //log('Formulaire.calcul.itemsSumAndPercent()');
    var formulaire_code = params['formulaire_code'];

    var total = 0;
    args['items'].each(function(item) {
      total += parseFloat($F(formulaire_code + '_' + item));
    }, this);
    total *= args['percent'];
    var result_field = $(formulaire_code + '_' + args['result_field']);
    NTD.Control.setValue(result_field, total);
  },

  calcul: function(elt, args, params) {
    //log('Formulaire.calcul.calcul()');
    var formulaire_code = params['formulaire_code'];

    var setInputStyle = function(input, image) {
      return;
      image = '/app/ntd/pix/formulaires/operateur_' + image + '.png';
      var oldStyle = input.getStyle('background');
      input.setStyle({background :"orange url(" + image + ") no-repeat right center "});

    };

    var total = 0;
    args['items'].each(function(item) {
      item = item.split('|');
      var operateur = item[0];
      var field = formulaire_code + '_' + item[1];
      if (!$(field)) {
        log('field not exists : "' + field + '"');
        return;
      }
      var image = '';

      if (operateur == '+') {
        total += Number($F(field));
        image += 'addition';
      }
      if (operateur == '-') {
        total -= Number($F(field));
        image += 'soustraction';
      }
      if (operateur == '*') {
        total *= Number($F(field));
        image += 'multiplication';
      }
      if (operateur == '/') {
        total /= Number($F(field));
        image += 'division';
      }
      setInputStyle($(field), image);

    }, this);
    total = Math.max(0, total);
    NTD.Control.setValue($(formulaire_code + '_' + args['field_result']), total);
    setInputStyle($(formulaire_code + '_' + args['field_result']), 'egalite');
  },


  onlyOneInputFilled: function(elt, args, params) {
    //log('Formulaire.calcul.onlyOneInputFilled()');
    var formulaire_code = params['formulaire_code'];

    var items = args['items'];
    var input_filled = null;
    items.each(function(item) {
      var field = $(formulaire_code + '_' + item);
      field.enable();
      if (!input_filled && $F(field) != '') {
        input_filled = field;
      }
    }, this);
    if (!input_filled) {
      return;
    }
    items.each(function(item) {
      var field = $(formulaire_code + '_' + item);
      if (input_filled == field) {
        field.enable();
      }
      else {
        field.disable();
      }
    }, this);
  },


  equation: function(elt, args, params) {

    var formulaire_code = params['formulaire_code'];
    var left = args['left'];
    var right = args['right'];
    var operator = args['operator'];
    if (!operator) {
      operator = '=';
    }
    var total_left = 0;
    var total_right = 0;
    left.each(function(left_elt) {
      total_left += Number($F(formulaire_code + '_' + left_elt));
    }, this);
    right.each(function(right_elt) {
      if (isNaN(Number(right_elt))) {
        total_right += Number($F(formulaire_code + '_' + right_elt));
      }
      else {
        total_right += Number(right_elt);
      }
    }, this);

    left.each(function(left_elt) {
      $(formulaire_code + '_' + left_elt).removeClassName('has-error');
    }, this);
    right.each(function(right_elt) {
      if (isNaN(Number(right_elt))) {
        $(formulaire_code + '_' + right_elt).removeClassName('has-error');
      }
    }, this);


    var isEquationOK = false;
    if ((operator == '=') && (total_left == total_right)) {
      isEquationOK = true;
    }
    else if ((operator == '<') && (total_left < total_right)) {
      isEquationOK = true;
    }
    else if ((operator == '<=') && (total_left <= total_right)) {
      isEquationOK = true;
    }
    else if ((operator == '>') && (total_left > total_right)) {
      isEquationOK = true;
    }
    else if ((operator == '>=') && (total_left >= total_right)) {
      isEquationOK = true;
    }


    if (isEquationOK) {
      left.each(function(left_elt) {
        NTD.Generic.positiv($(formulaire_code + '_' + left_elt));
      }, this);
      right.each(function(right_elt) {
        if (isNaN(Number(right_elt))) {
          NTD.Generic.positiv($(formulaire_code + '_' + right_elt));
        }
      }, this);
    }
    else {

      //var msg = left.join(' + ')+' doit être '+operator+' à '+right.join(' + ');
      left.each(function(left_elt) {
        NTD.Generic.negativ($(formulaire_code + '_' + left_elt));
      }, this);
      right.each(function(right_elt) {
        if (isNaN(Number(right_elt))) {
          NTD.Generic.negativ($(formulaire_code + '_' + right_elt));
        }
      }, this);
    }
  },

  paiement: function(elt, args, params) {
    if (params['formulaire_code'] == 'cvae1329ac_20140101') {
      var item_code = args['item'];
      var item = $(params['formulaire_code'] + '_' + args['item']);
      var checkbox = $(params['formulaire_code'] + '_' + item_code + '_checkbox');

      if ($F(item) > args['amount_max']) {
        checkbox.checked = false;
      }

      if ($F(item) > 0 && !checkbox.checked) {
        NTD.Identif.p('showPaiement', [$F(item)]);
      } else {
        NTD.Identif.p('hidePaiement', []);
      }
      if (checkbox.checked) {
        $('row-link-' + item_code).show();
      } else {
        $('row-link-' + item_code).hide();
      }
    }
    else if (params['formulaire_code'] == 'cvae1329def_20140101') {
      Formulaire.cvae1329def.paiement(elt, args, params);  
    }
    else {
      var FE = $(params['formulaire_code'] + '_' + args['field']);
      if ($F(FE) > 0) {
        NTD.Identif.p('showPaiement', [$F(FE)]);
      } else {
        NTD.Identif.p('hidePaiement', []);
      }
    }
  }

};
