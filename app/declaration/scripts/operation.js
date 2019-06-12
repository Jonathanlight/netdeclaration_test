declaration.Operation = Class.create({

  wrapper: null,
  imprime: null,
  args: null,

  listenedFields: null,

  _cacheCalcul: null,
  _cacheSum: null,
  _cacheIf: null,
  _cacheIfcond: null,
  _cacheSaisie: null,

  executionAsk: false,

  currentFieldIndex: null,

  initialize: function(wrapper, imprime, args) {
    this.wrapper = wrapper;
    this.imprime = imprime;
    this.args = args;
    this.listenedFields = [];
    this._cacheCalcul = $H({});
    this._cacheSum = $H({});
    this._cacheIf = $H({});
    this._cacheIfcond = $H({});
    this._cacheSaisie = $H({});
    this.executionAsk = false;
    this.currentFieldIndex = 0;
    this.prepare();
  },

  prepare: function() {
    if (declaration.Operation.debug && console && console.groupCollapsed) console.groupCollapsed('[OPERATION] prepare : ' + (this.args['result'] ? this.args['result'] + ' = ' : '') + this.args["formula"]);
    if (declaration.Operation.debug && console && console.time) console.time('time');
    if (declaration.Operation.debug && console && console.log) console.log(this);
    this.onPrepare();
    if (declaration.Operation.debug && console && console.timeEnd) console.timeEnd('time');
    if (declaration.Operation.debug && console.groupEnd) console.groupEnd();
  },
  onPrepare: Prototype.emptyFunction,
  execute: function(fieldIndex) {
    if (declaration.Operation.debug && console && console.groupCollapsed) console.groupCollapsed('[OPERATION] execution : ' + (this.args['result'] ? this.args['result'] + ' = ' : '') + this.args["formula"]);
    if (declaration.Operation.debug && console && console.time) console.time('time');
    if (declaration.Operation.debug && console && console.log) console.log(this);
    this.onExecute(fieldIndex);
    if (declaration.Operation.debug && console && console.timeEnd) console.timeEnd('time');
    if (declaration.Operation.debug && console && console.groupEnd) console.groupEnd();
    this.executionAsk = false;
  },
  onExecute: Prototype.emptyFunction,

  listenFieldChange: function(field_code) {
    $(document).observe(declaration.Field.EVENT.CHANGE + "_" + field_code + "_" + this.imprime.index,
                        function(evt) {
                          if (this.executionAsk) {
                            return;
                          }
                          this.executionAsk = true;
                          this.execute.bind(this, evt.memo['field_index']).defer();
                        }.bind(this));
  },

  getOperandeValue: function(operande, depth) {
    depth = depth || 0;
    this.debugPrint("-> getOperandeValue(" + operande + ")", depth);

    var value = null;

    if (operande.substr(0, 6) == 'IFCOND') {
      var if_parts = this.parseIfcond(operande, depth + 1);
      var formula = this.getConditionValue(if_parts['condition'], depth + 1) ? if_parts['condition_yes'] : if_parts['condition_no'];
      value = this.getConditionValue(formula, depth + 1);
    }

    else if (operande.substr(0, 2) == 'IF') {
      var if_parts = this.parseIf(operande, depth + 1);
      var formula = this.getConditionValue(if_parts['condition'], depth + 1) ? if_parts['calcul_yes'] : if_parts['calcul_no'];
      value = this.getCalculValue(formula, depth + 1);
    }

    else if (operande.substr(0, 4) == '#SUM') {
      var field_code = this.parseSum(operande, depth + 1);
      value = 0;
      var count = this.imprime.getFieldCodeCount(field_code);
      for (var index = 0; index < count; index++) {
        value += Number(this.imprime.getField(field_code, index).getValue());
      }
    }

    else if (operande.substr(0, 4) == '#MAX') {
      var field_codes = this.parseMax(operande, depth + 1);
      var values = [];
      field_codes.each(function(field_code) {
        values.push(this.getOperandeValue(field_code, depth + 1));
      }, this);
      value = values.max();
    }
    else if (operande.substr(0, 4) == '#MIN') {
      var field_codes = this.parseMin(operande, depth + 1);
      var values = [];
      field_codes.each(function(field_code) {
        values.push(this.getOperandeValue(field_code, depth + 1));
      }, this);
      value = values.min();
    }

    else if (operande.substr(0, 1) == '(') {
      operande = operande.replace(/^\(+/, '').replace(/\)+$/, '');
      value = this.getCalculValue(operande, depth);
    }

    else if (isNaN(Number(operande))) {
      var field = this.imprime.getField(operande, this.currentFieldIndex);
      value = field.getValue();
      if (field instanceof declaration.Field.Typemoa
              || field instanceof declaration.Field.Typepcd
              || field instanceof declaration.Field.Typeqty) {

        if (value.startsWith('0') && value != '0') {
          value = value.substr(1);
        }
        if (value.blank()) {
          value = 0;
        }

        if (typeof value === "string" && value.startsWith('-')) {
          value = '(' + value + ')';
        }
        else {
          value = Number(value);
        }
      }
    }

    else {
      value = operande;
    }

    this.debugPrint("<- Resultat : [" + value + "]", depth);
    return value;
  },

  getCalculValue: function (formula, depth) {
    depth = depth || 0;
    this.debugPrint("-> getCalculValue(" + formula + ")", depth);
    var operandes = this.parseCalcul(formula, depth + 1);

    var formula_ready = formula;
    operandes.each(function(operande) {
      formula_ready = formula_ready.replace(operande,
                                            this.getOperandeValue(operande, depth + 1));
    }, this);
    this.debugPrint("formula_ready [" + formula_ready + "]", depth);
    var result = null;
    result = eval(formula_ready);
    this.debugPrint("<- Résultat : [" + result + "]", depth);
    return result;
  },

  getCalculValueNotEvaluated: function (formula, depth) {
    depth = depth || 0;
    this.debugPrint("-> getCalculValue(" + formula + ")", depth);
    var operandes = this.parseCalcul(formula, depth + 1);

    var formula_ready = formula;
    operandes.each(function(operande) {
      formula_ready = formula_ready.replace(operande,
                                            this.getOperandeValue(operande, depth + 1));
    }, this);
    this.debugPrint("formula_ready [" + formula_ready + "]", depth);
    var result = null;
    //result = eval(formula_ready);
    result = formula_ready;
    this.debugPrint("<- Résultat : [" + result + "]", depth);
    return result;
  },

  getConditionValue: function (formula, depth) {
    depth = depth || 0;
    this.debugPrint("-> getConditionValue(" + formula + ")", depth);

    var result = null;
    if (formula.indexOf('#FORM(') !== -1) {
      var imprime_code = this.parseForm(formula, depth + 1);
      var imprime = $D().getImprime(imprime_code);
      result = imprime instanceof declaration.Imprime;
    }
    else if (formula.indexOf('#OPEOR(') !== -1) {
      var parts = formula.split(/[=]/).reject(function(field_code) {
        return field_code.blank();
      });
      var operande_left = parts[0];
      var operande_right = parts[1];

      this.debugPrint("parts = [" + parts + "]", depth + 1);
      this.debugPrint("operande_left = [" + operande_left + "]", depth + 1);
      this.debugPrint("operande_right = [" + operande_right + "]", depth + 1);
      var field_codes = this.parseOpeor(operande_right, depth + 1);
      var values = [];
      field_codes.each(function(field_code) {
        values.push(this.getCalculValue(field_code, depth + 1));
      }, this);
      var operandeLeftValue = this.getCalculValue(operande_left, depth + 1);
      result = values.detect(function(value) {
        return value == operandeLeftValue
      }) != null;
    }
    else if (formula.indexOf('IFCOND(') !== -1) {
      var operande_left = formula;
      this.debugPrint("operande_left = [" + operande_left + "]", depth + 1);

      operande_left = this.parseIfcond(operande_left, depth + 1);
      this.debugPrint(">> operande_left = [" + operande_left + "]", depth + 1);

      var formula = this.getConditionValue(operande_left['condition'], depth + 1) ? operande_left['condition_yes'] : operande_left['condition_no'];
      operande_left_value = this.getConditionValue(formula, depth + 1);

      var formula_ready = formula.replace(formula, operande_left_value);

      this.debugPrint("formula_ready [" + formula_ready + "]", depth);
      result = eval(formula_ready);
    }
    else if (formula.indexOf('SAISIE(') !== -1) {
      var operande_left = formula;
      this.debugPrint("operande_left = [" + operande_left + "]", depth + 1);

      operande_left = this.parseSaisie(operande_left, depth + 1);
      this.debugPrint(">> operande_left = [" + operande_left + "]", depth + 1);

      var operande_left_value = this.getConditionValue(operande_left, depth + 1);
      var formula_ready = formula.replace(formula, operande_left_value);

      this.debugPrint("formula_ready [" + formula_ready + "]", depth);
      result = eval(formula_ready);
    }
    else {
      var parts = formula.split(/[><=]/).reject(function(field_code) {
        return field_code.blank();
      });
      var operande_left = parts[0];
      var operande_right = parts[1];

      this.debugPrint("parts = [" + parts + "]", depth + 1);
      this.debugPrint("operande_left = [" + operande_left + "]", depth + 1);
      this.debugPrint("operande_right = [" + operande_right + "]", depth + 1);

      var operande_left_value = this.getCalculValue(operande_left, depth + 1);
      var operande_right_value = this.getCalculValue(operande_right, depth + 1);

      var formula_ready = formula.replace(operande_left, operande_left_value).replace(operande_right, operande_right_value);
      this.debugPrint("formula_ready [" + formula_ready + "]", depth);
      result = eval(formula_ready);
    }

    this.debugPrint("<- Resultat : " + (result ? 'vrai' : 'faux'), depth);
    return result;
  },



  /* ----- parse Methods ----- */

  parseCalcul: function (formula, depth) {
    depth = depth || 0;
    this.debugPrint("-> parseCalcul(" + formula + ")", depth);
    if (this._cacheCalcul.get(formula)) {
      return this._cacheCalcul.get(formula);
    }

    var operandes = [];
    var open_parenthesis = 0;
    var current_operande = '';
    for (var i = 0; i < formula.length; i++) {
      var _char = formula[i];
      if (open_parenthesis == 0
              && (_char == '+' || (_char == '-' && (['F', 'P', 'T', 'A'].indexOf(current_operande) == -1)) || _char == '*' || _char == '/' )) {
        operandes.push(current_operande);
        current_operande = '';
        continue;
      }
      if (_char == '(') {
        open_parenthesis++;
      }
      else if (_char == ')') {
        open_parenthesis--;
      }
      current_operande += _char;
    }
    operandes.push(current_operande);
    operandes.sort(this.sortOperandes);
    this.debugPrint("<- Resultat : [" + operandes.join(', ') + "]", depth);
    this._cacheCalcul.set(formula, operandes);
    return operandes;
  },

  parseIf: function (formula, depth) {
    depth = depth || 0;
    this.debugPrint("-> parseIf(" + formula + ")", depth);
    if (this._cacheIf.get(formula)) {
      return this._cacheIf.get(formula);
    }

    formula = formula.substr(3); // IF(
    formula = formula.substr(0, formula.length - 1);

    var resultat = {
      condition : '',
      calcul_yes : '',
      calcul_no : ''};
    var index = 'condition';
    var open_parenthesis = 0;

    for (var i = 0; i < formula.length; i++) {
      var _char = formula[i];
      if (_char == '(') {
        open_parenthesis++;
      }
      else if (_char == ')') {
        open_parenthesis--;
      }
      else if (_char == ';') {
        if (open_parenthesis == 0) {
          if (index == 'condition') {
            index = 'calcul_yes';
          }
          else if (index == 'calcul_yes') {
            index = 'calcul_no';
          }
          else {
            break;
          }
          continue;
        }
      }
      resultat[index] += _char;
    }
    this.debugPrint("<- Résultat : [" + resultat['condition'] + "] ? [" + resultat['calcul_yes'] + "] : [" + resultat['calcul_no'] + "]", depth);
    this._cacheIf.set(formula, resultat);
    return resultat;
  },

  parseIfcond: function (formula, depth) {
    depth = depth || 0;
    this.debugPrint("-> parseIfcond(" + formula + ")", depth);
    if (this._cacheIfcond.get(formula)) {
      return this._cacheIfcond.get(formula);
    }

    formula = formula.substr(7); // IFCOND(
    formula = formula.substr(0, formula.length - 1);

    var resultat = {
      condition : '',
      condition_yes : '',
      condition_no : ''
    };
    var index = 'condition';
    var open_parenthesis = 0;

    for (var i = 0; i < formula.length; i++) {
      var _char = formula[i];
      if (_char == '(') {
        open_parenthesis++;
      }
      else if (_char == ')') {
        open_parenthesis--;
      }
      else if (_char == ';') {
        if (open_parenthesis == 0) {
          if (index == 'condition') {
            index = 'condition_yes';
          }
          else if (index == 'condition_yes') {
            index = 'condition_no';
          }
          else {
            break;
          }
          continue;
        }
      }
      resultat[index] += _char;
    }
    this.debugPrint("<- Résultat : [" + resultat['condition'] + "] ? [" + resultat['condition_yes'] + "] : [" + resultat['condition_no'] + "]", depth);
    this._cacheIfcond.set(formula, resultat);
    return resultat;
  },

  parseSaisie: function(formula, depth) {
    depth = depth || 0;
    this.debugPrint("-> parseSaisie(" + formula + ")", depth);
    if (this._cacheSaisie.get(formula)) {
      return this._cacheSaisie.get(formula);
    }

    formula = formula.substr(7); // SAISIE(
    formula = formula.substr(0, formula.length - 1);

    var field_code = formula;
    var field_value = this.imprime.getField(formula, this.currentFieldIndex).getValue();
    var resultat = (!isNaN(field_value) ? field_code + '>0' : field_value.length + '>0');

    this.debugPrint("<- Résultat : [" + resultat + "]", depth);
    this._cacheSaisie.set(formula, resultat);
    return resultat;
  },

  parseSum: function (formula, depth) {
    this.debugPrint("-> parseSum(" + formula + ")", depth);
    // #SUM(field_code)#
    if (this._cacheSum.get(formula)) {
      return this._cacheSum.get(formula);
    }
    var matches = formula.match('#SUM\\((.*)\\)#');
    var field_code = matches[1];
    this.debugPrint("<- Résultat : [" + field_code + "]", depth);
    this._cacheSum.set(formula, field_code);
    return field_code;
  },
  parseForm: function (formula, depth) {
    this.debugPrint("-> parseForm(" + formula + ")", depth);
    // #FORM(@imprime_code)#
    if (this._cacheForm.get(formula)) {
      return this._cacheForm.get(formula);
    }
    var matches = formula.match('#FORM\\(@(.*)\\)#');
    var imprime_code = matches[1];
    this.debugPrint("<- Résultat : [" + imprime_code + "]", depth);
    this._cacheSum.set(formula, imprime_code);
    return imprime_code;
  },
  parseMax: function(formula, depth) {
    this.debugPrint("-> parseMax(" + formula + ")", depth);
    // #MAX(field_code1;field_code2, ...)#
    var matches = formula.match('#MAX\\((.*)\\)#');
    var field_codes = matches[1].split(';');
    this.debugPrint("<- Résultat : [" + field_codes + "]", depth);
    return field_codes;
  },
  parseMin: function(formula, depth) {
    this.debugPrint("-> parseMin(" + formula + ")", depth);
    // #MIN(field_code1;field_code2, ...)#
    var matches = formula.match('#MIN\\((.*)\\)#');
    var field_codes = matches[1].split(';');
    this.debugPrint("<- Résultat : [" + field_codes + "]", depth);
    return field_codes;
  },
  parseOpeor: function(formula, depth) {
    depth = depth || 0;
    this.debugPrint("-> parseOpeor(" + formula + ")", depth);
    // #OPEOR(field_code1;field_code2, ...)#
    var matches = formula.match('#OPEOR\\((.*)\\)#');
    var field_codes = matches[1].split(';');
    this.debugPrint("<- Résultat : [" + field_codes + "]", depth);
    return field_codes;
  },



  /* ----- UTILS ----- */

  debugPrint: function (msg, depth) {
    if (!declaration.Operation.debug) return;
    depth = depth || 0;
    var _print = "";
    _print += " ".times(depth * 4);
    //if (!is_string(msg)) {
    //  msg = var_export(msg, true);
    //}
    _print += msg + "\n";
    if (console && console.debug) {
      console.debug(_print);
    }
  },

  sortOperandes: function (a, b) {
    //Operation::debugPrint('sortOperandes([' + a + '], [' + b + '])');
    if (a == b) {
      return 0;
    }

    if (a.substr(0, 3) == 'IF(' || a.substr(0, 6) == 'IFCOND(' || a.substr(0, 3) == '#SU') {
      //Operation::debugPrint('return 1');
      return -1;
    }
    else if (b.substr(0, 3) == 'IF(' || a.substr(0, 6) == 'IFCOND(' || b.substr(0, 3) == '#SU') {
      //Operation::debugPrint('return -1');
      return 1;
    }
    return (a < b) ? -1 : 1;
  }
});

declaration.Operation.debug = false;


declaration.Operation.evaluate = Class.create(declaration.Operation, {
  resultField: null,
  onExecute: function(fieldIndex) {
    this.currentFieldIndex = fieldIndex;
    var result = this.getCalculValue(this.args["formula"]);

    var resultField = this.imprime.getField(this.args['result'], this.currentFieldIndex);
    if (resultField) {
      resultField.setValue(result)
    }
  },

  onPrepare: function() {
    this.resultField = this.imprime.getField(this.args['result']);
    if (!this.resultField) {
      alert('Champ manquant : ' + this.args['result']);
      return;
    }
    this.resultField.setType(declaration.Field.TYPE.RESULT);
    //this.resultField.setInfos(this.args['formula'], 'OPERATION : ' + this.args['formula']);

    var field_codes = this.args['formula'].match(new RegExp('(([A-Z0-9]|(F\-)|(P\-)|(T\-)|(A\-))+_[A-Z0-9]+)', 'g'));
    field_codes = field_codes.uniq();

    $A(field_codes).each(function(field_code) {
      this.listenFieldChange(field_code);
    }, this);


  }
});

declaration.Operation.copy = Class.create(declaration.Operation, {
  resultField: null,
  onExecute: function(fieldIndex) {
    this.currentFieldIndex = fieldIndex;
    var result = this.getCalculValueNotEvaluated(this.args["formula"]);
    var resultField = this.imprime.getField(this.args['result'], this.currentFieldIndex);
    if (resultField) {
      resultField.setValue(result)
    }
  },

  onPrepare: function() {
    this.resultField = this.imprime.getField(this.args['result']);
    if (!this.resultField) {
      alert('Champ manquant : ' + this.args['result']);
      return;
    }
    //this.resultField.setType(declaration.Field.TYPE.RESULT);

    var field_codes = this.args['formula'].match(new RegExp('(([A-Z0-9]|(F\-)|(P\-)|(T\-)|(A\-))+_[A-Z0-9]+)', 'g'));
    field_codes = field_codes.uniq();

    $A(field_codes).each(function(field_code) {
      this.listenFieldChange(field_code);
    }, this);
  }
});



declaration.Operation.equation = Class.create(declaration.Operation, {
  onExecute: function(fieldIndex) {
    this.currentFieldIndex = fieldIndex;
    var result = this.getConditionValue(this.args["formula"]);
    var field_fullcodes = this.getFieldFullCodes();

    if (result) {
      $A(field_fullcodes).each(function(field_fullcode) {
        if (this.args["formula"].indexOf("#SUM(" + field_fullcode + ")#") != -1) {
          //this.imprime.getField(field_fullcode).removeError(this.args["formula"]);
          var count = this.imprime.getFieldCodeCount(field_fullcode);
          for (var index = 0; index < count; index++) {
            this.imprime.getField(field_fullcode, index).removeError(this.args["formula"]);
          }
        }
        else {
          this.imprime.getField(field_fullcode, this.currentFieldIndex).removeError(this.args["formula"]);
        }
      }, this);
    }
    else {
      $A(field_fullcodes).each(function(field_fullcode) {
        var msg = "Erreur : " + this.args['formula'];
        //this.imprime.getField(field_fullcode, this.currentFieldIndex).addError(this.args["formula"], msg);
        if (this.args["formula"].indexOf("#SUM(" + field_fullcode + ")#") != -1) {
          //this.imprime.getField(field_fullcode).addError(this.args["formula"], msg);
          var count = this.imprime.getFieldCodeCount(field_fullcode);
          for (var index = 0; index < count; index++) {
            this.imprime.getField(field_fullcode, index).addError(this.args["formula"], msg);
          }
        }
        else {
          this.imprime.getField(field_fullcode, this.currentFieldIndex).addError(this.args["formula"], msg);
        }
      }, this);
    }
  },

  onPrepare: function() {
    var field_codes = this.getFieldFullCodes();
    $A(field_codes).each(function(field_code) {
      this.listenFieldChange(field_code);
    }, this);
  },
  getFieldFullCodes: function() {
    var field_codes = this.args['formula'].match(new RegExp('(([A-Z0-9]|(F\-)|(P\-)|(T\-)|(A\-))+_[A-Z0-9]+)', 'g'));
    field_codes = field_codes.uniq().reject(function(field_code) {
      return field_code.blank();
    });
    return field_codes;
  }
});

declaration.Operation.required = Class.create(declaration.Operation, {
  requiredField: null,
  onExecute: function(fieldIndex) {
    if (this.args["formula"].substr(0, 2) == 'IF') {
      this.currentFieldIndex = fieldIndex;
      var result = this.getCalculValue(this.args["formula"]);
      var resultField = this.imprime.getField(this.requiredField, this.currentFieldIndex);
      if (!result) {
        var msg = "Ce champ est obligatoire car " + this.args['formula'];
        resultField.addError(this.args["formula"], msg);
      }
      else {
        resultField.removeError(this.args["formula"]);
      }
    }
    else {
      this.currentFieldIndex = fieldIndex;
      var result = this.getConditionValue(this.args["formula"]);
      var resultField = this.imprime.getField(this.requiredField, this.currentFieldIndex);
      if (result && resultField.getValue().blank()) {
        var msg = "Ce champ est obligatoire car " + this.args['formula'];
        resultField.addError(this.args["formula"], msg);
      }
      else {
        resultField.removeError(this.args["formula"]);
      }
    }

  },

  onPrepare: function() {

    var field_codes = this.getFieldFullCodes();
    $A(field_codes).each(function(field_code) {
      this.listenFieldChange(field_code);
    }, this);


    var requiredField = this.imprime.getField(this.args['result']);
    if (!requiredField) {
      alert('Champ manquant : ' + this.args['result']);
      return;
    }
    //this.resultField.setType(declaration.Field.TYPE.RESULT);
    this.requiredField = this.args['result'];
    this.listenFieldChange(this.requiredField);

  },
  getFieldFullCodes: function() {
    var field_codes = this.args['formula'].match(new RegExp('(([A-Z0-9]|(F\-)|(P\-)|(T\-)|(A\-))+_[A-Z0-9]+)', 'g'));
    field_codes = field_codes.uniq().reject(function(field_code) {
      return field_code.blank();
    });
    return field_codes;
  }
});



/*var test_.go = function() {
 test_.imprimes_data = {
 'AA' : 1,
 'AB' : 2,
 'AC' : 3,
 'AD' : 4,
 'AE' : [1, 2, 3, 4, 5],
 'AF' : [1, 1],
 'AG' : [1, 2],
 'SU' : [1, 2],
 'MU' : [1, 2],
 'UM' : [1, 2],
 'tva_AB' : 5
 };
 var tests = $H({
 'AA+AB+AC+AD' : 10,
 'AA+AB+(AC*AD)' : 15,
 '(7*8/9*AD)/(AA+AB+(AC*AD))' : 1.6592592592593,
 'IF(AB>AC;AA;AD)' : 4,
 'IF(AB<AC;AA;AD)' : 1,
 'IF(AB>=2;1;10000)' : 1,
 'IF(AB>2;1;10000)' : 10000,
 'AA+IF(AB>5;1;10000)+AC+AD' : 10008,
 'IF(AB>=AC;AB-AC;15)' : 15,
 'IF(AB<AC;AB-AC;15)' : -1,
 'IF(AB<AC;AB-AC;15)+AB' : 1,
 'AB+IF(AB<AC;AB-AC;15)' : 1,
 'AB+IF(AB<AC;AB-AC;15)+AD+IF(AA>1;1;-1)' : 4,
 'AB+IF(AB<AC;IF(AB-AC>0;150;10);15)' : 12,
 '#SUM(AE)#' : 15,
 'AA+#SUM(AE)#' : 16,
 '#SUM(AE)#-AB' : 13,
 'AC*(#SUM(AE)#-AB)' : 39,
 'AC*(#SUM(AE)#-AB)/IF(AC>4;2;3)' : 13,
 'AC*(#SUM(AE)#-AB)/IF(#SUM(AE)#>4;#SUM(AG)#;#SUM(AF)#)' : 13,
 'AC*(#SUM(AE)#-tva_AB)/IF(#SUM(AE)#>4;#SUM(UM)#;#SUM(AF)#)' : 10
 });

 tests.each(function(test) {
 test_.debug = false;
 var value = test_.getCalculValue(test.key);
 console.log('[' + ((value.toFixed(2) == test.value.toFixed(2)) ? 'OK' : 'ERREUR') + "]\t " + test.key + " = " + value + "\n");

 }, this);
 test_.getCalculValue('AA+AB+AC+AD');

 };
 */
