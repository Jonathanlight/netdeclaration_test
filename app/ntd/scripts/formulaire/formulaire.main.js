if (!kwo) var kwo = {};

NTD = {};


NTD.init = function() {
  //NTD.Control.linkedEvents();

};

NTD.Debug = {
  container: 'debug',
  actived: false,
  count:0,
  init: function() {
    //$(NTD.Debug.container).show();
    new Draggable($(NTD.Debug.container), {handle: $(NTD.Debug.container).down('.toolbar')});
  },
  trace: function(msg) {
    if (NTD.Debug.count == 1) {
      NTD.Debug.init();
    }
    if (!NTD.Debug.actived) return;
    $(NTD.Debug.container).down('.content').insert(NTD.Debug.count + ' - ' + msg + '<br/>');
    NTD.Debug.count++;
  },
  clear: function() {
    $(NTD.Debug.container).down('.content').update('');
    NTD.Debug.count = 0;
  }
};

NTD.Control = {

  controls: 0,

  displayError : function(elt) {
    elt = $(elt);
    if (elt.hasClassName('has-error')) {
      Kwo.Tooltip.show(elt, elt.next('.elt-tooltip'));
    }
  },

  hideError : function(elt) {
    Kwo.Tooltip.hide();

  },

  disable_field_count : function(itemsArray) {
    itemsArray.each(function(item) {
      item = $(item);
      item.disabled = true;
      if (item.hasAttribute('disabled-count')) {
        item.setAttribute('disabled-count', parseInt(item.getAttribute('disabled-count')) + 1);
      } else {
        item.setAttribute('disabled-count', 1);
      }
    });
  },

  enable_field_count : function(itemsArray) {
    itemsArray.each(function(item) {
      item = $(item);
      if (item.hasAttribute('disabled-count')) {
        item.setAttribute('disabled-count', parseInt(item.getAttribute('disabled-count')) - 1);
      } else {
        item.setAttribute('disabled-count', 0);
      }
      if (parseInt(item.getAttribute('disabled-count')) == 0) {
        item.disabled = false;
      }
    });
  },

  disable_field : function(itemsArray) {
    itemsArray.each(function(item) {
      $(item).disabled = true;
    });
  },
  enable_field : function(itemsArray) {
    itemsArray.each(function(item) {
      $(item).disabled = false;
    });
  },

  setValue : function(elt, value, isPercent, is_enabled, not_round, stopTriggerChange) {
    elt = $(elt);
    if (!elt) {
      console.log("elt is null");
      return;
    }
    if (elt.disabled) return;
    if (isPercent) {
      value = Math.round(value * 100) / 100;
    }
    if (not_round) elt.value = value.toFixed(2);
    else elt.value = Math.round(value);

    if (isNaN(elt.value) || elt.value < 0) elt.value = 0;
    elt.removeClassName('operations_dependances');
    if (!is_enabled) {
      elt.setAttribute('readonly', 'readonly');
      elt.addClassName('result');
    }
    try{
      if(!stopTriggerChange) {
        elt.onchange();
      }
    }
    catch(error){
      console.log(elt, error);
    }
  },

  splitComments : function(elt) {
    var text = $F(elt);
    var id = elt.id;
    var max_length = 512;
    var textes = [];
    for (var i = 1; i <= 5; i++) {
      var split_text = text.substr(0, max_length);
      //if (split_text.indexOf("\n") > 0) {
      //split_text = text.substr(0, split_text.indexOf("\n"));
      //text = text.substr(split_text.length + 1);
      ///}else{
      text = text.substr(split_text.length);
      //}
      $(id + i).setValue(split_text);
    }
  },

  limit : function(elt, max) {
    if (elt.value.length > max) {
      elt.value = elt.value.substring(0, max);
    }
  },

  check_dependances : function(itemsArray, function_name, arg) {
    var walk = true;
    var count = 0;
    if (arg == 'one_of_item') {
      itemsArray.each(function(item) {
        item = $(item);
        if (item.value == "" || item.value == 0) count++;
      });
      if (count == itemsArray.length) walk = false;
      return walk;
    } else {
      itemsArray.each(function(item) {
        item = $(item);
        if (!item) {
          console.log(item + ' does not exists');
          return;
        }
        if (item.value == "" || (item.value == 0 && !item.hasClassName('result'))) {
          walk = false;
        }
      });
      return walk;
    }
  },

  reset_operations : function(items) {
    if (!Object.isArray(items)) items = [items];
    var empty = 0;
    var items_length = items.length;
    items.each(function(item) {
      if (($F(item) == "" || $F(item) == 0) && !$(item).hasClassName('result')) {
        empty++;
      }
    }, this);
    if (empty == items_length) {
      NTD.Control.removeValue(items);
    }
  },

  removeValue : function(els) {
    if (!Object.isArray(els)) els = [els];
    els.each(function(elt) {
      elt = $(elt);
      if (!elt.hasClassName('stay_operand')) {
        elt.value = "";
        if (elt.hasAttribute('readonly')) elt.removeAttribute('readonly');
        if (elt.hasClassName('result')) elt.removeClassName('result');
        if (elt.hasClassName('checked-true')) elt.removeClassName('checked-true');
        if (elt.hasClassName('checked-false')) elt.removeClassName('checked-false');
        if (elt.hasClassName('operations_dependances')) elt.removeClassName('operations_dependances');
        if ((elt.readAttribute('type') == 'checkbox') && (elt.checked == true)) elt.checked = false;
      }
    });
  },

  setDependances : function(operandes, toOperate) {
    operandes.each(function(elt) {
      var eltId = elt;
      elt = $(elt);
      if(!elt) {
        console.log(eltId);
      }
      if (!elt.hasClassName('result')) {
        elt.addClassName('operations_dependances');
        if (elt.value == "") elt.value = 0;
      }
    });
    if (toOperate) {
      toOperate.each(function(elt) {
        elt = $(elt);
        if (!elt.hasClassName('result')) {
          elt.addClassName('operations_dependances');
          if (elt.value == "") elt.value = 0;
        }
      });
    }
  },

  onEdit: function(el) {
    NTD.Control.checkValue(el);
  },

  linkedEvents: function(callback) {
    var compteur = 0;
    var time = new Date().getTime();
    $$('.field[type!=checkbox]').each(function(elt) {
      elt.onkeyup = elt.onchange;
      //elt.onblur = elt.onchange;
      //elt.onfocus = elt.onchange;
    });
    $$('.field').each(function(elt) {
      if (!elt.disabled) {
        if (elt.id.indexOf('tva3310a') != -1) return;
        if (elt.id.indexOf('tva3310ter') != -1) return;
        if (elt.id.indexOf('tva3515sd') != -1) return;
        try{
          elt.onchange();
        }
        catch(error){
          console.log(elt, error);
        }
        //elt.onchange();
        compteur++;
      }

    }, this);
    $$('.field-type-number, .field-type-float, .field-type-pourcentage').each(function(input) {
      input.observe('change', NTD.Control.onInputNumberChange.curry(input));
    });
    //alert(compteur+" : "+((new Date().getTime())-time));
    if (callback) callback.call();
  },

  onInputNumberChange:function(input) {
    if ($(input).hasClassName('field-type-number') && ($F(input).include('.') || $F(input).include(','))) {
      alert('Veuillez saisir un nombre entier sans décimales.');
    }
    if ($F(input).include('-')) {
      alert('Veuillez saisir un nombre positif.');
    }
  },

  isNumeric: function(arg) {
    return /^[0-9]*[,.]?[0-9]+$/.test(arg.value);
  },

  isAlphabetic: function(arg) {
    return /^([a-z])$/.test(arg.value) ? 1 : 0;
  },

  removeClassChecked: function(arg) {
    arg.removeClassName('checked-false');
    arg.removeClassName('checked-true');
    arg.removeClassName('unchecked');
    arg.removeClassName('checked');
  },

  // Hugues : dupliqué
  onValid : function(form, confirmBox) {
    Kwo.exec('/ntd/form.valid', form, {
      callback: NTD.Control.onValidCallback.curry(form, confirmBox)
    });
  },

  // Hugues : dupliqué
  onValidCallback : function(form, confirmBox, res) {
    if (Kwo.hasError(res)) return Kwo.error(res);
    if (res['result'] && res['result']['errors']) {
      if (res['result']['errors'].length < 1) {

        NTD.Control.onConfirm(form, confirmBox);
      } else {
        var errors = $H(res['result']['errors']);
        errors.each(function (pair) {
          NTD.Control.removeClassChecked($(pair.key));
          //$(pair.key).addClassName(pair.value.name);
          $(pair.key).next('.output').update(pair.value.msg);
        });
        $(errors.keys().first()).scrollTo();
      }
    } else if (res['result'] && res['result']['tests']) {
      if (res['result']['tests'].length < 1) {
        return;
      } else {
        var tests = $H(res['result']['tests']);
        tests.each(function (pair) {
          $(pair.key).next('.output').update(pair.value.msg);
        });
      }
    }
  },

  onConfirm : function(form, confirmBox) {
    Kwo.exec('/ntd/form.confirm', form, {
      container: confirmBox,
      //container: 'confirm-box',
      callback: NTD.Control.onConfirmCallback.curry(form)
    });
    if (confirmBox.hasClassName('hidden')) confirmBox.removeClassName('hidden');
  },

  onConfirmCallback: function(form, res) {
    if (Kwo.hasError(res)) return Kwo.error(res);
    form.addClassName('hidden');
  },

  onStore: function(form, confirmBox) {
    NTD.Control.cleanErrors();
    Kwo.exec('/ntd/form.store', form, {
      callback: NTD.Control.onStoreCallback.curry(form, confirmBox)
    });
    form.removeClassName('hidden');
    confirmBox.addClassName('hidden');
  },

  onStoreCallback: function(res) {
    if (Kwo.hasError(res)) return Kwo.error(res);
    if (res['result'] && res['result']['errors']) {
      if (res['result']['errors'].length > 1) {
        var errors = $H(res['result']['errors']);
        errors.each(function (pair) {
          $(pair.key).addClassName(pair.value.name);
          $(pair.key).next('.output').update(pair.value.msg);
        });
        $(errors.keys().first()).scrollTo();
      }
    } else {
      alert('Votre formulaire a été enregistré avec succès');
    }
  },

  onCancelConfirm: function(form, confirmBox) {
    form.removeClassName('hidden');
    confirmBox.addClassName('hidden');
  },

  cleanErrors: function () {
    $$('.field').each(function(elt) {
      if ($(elt).hasClassName('hasError')) {
        NTD.Control.cleanError(elt);
      }
    });
  },

  cleanError: function (elt) {
    if ($(elt).hasClassName('has-error')) {
      $(elt).removeClassName('has-error');
      if($(elt).next('.elt-tooltip')) {
        $(elt).next('.elt-tooltip').hide().down('.elt-tooltip-content').update('&nbsp;');
      }
    }
  },

  checkValue : function(elt) {
    elt = $(elt);
    NTD.Control.cleanError(elt);

    if (elt.hasClassName('alpha')) {
      if (NTD.Control.isAlphabetic(elt)) {
        NTD.Control.removeClassChecked(elt);
        elt.addClassName('checked-true');
      }
    }
    else if (elt.hasClassName('input-date')) {
      if (elt.name.indexOf('identif[CA]') != -1 || elt.name.indexOf('identif[CB]') != -1) {
        if (document.body.down('input[name*="identif[CA]"]') && document.body.down('input[name*="identif[CB]"]')) {
          var dates = 'Début : ' + document.body.down('input[name*="identif[CA]"]').getValue() + ' - Fin : ' + document.body.down('input[name*="identif[CB]"]').getValue();
          document.body.down('.print-footer').down('.exercice-dates').update(dates);
        }
      }
      NTD.Control.removeClassChecked(elt);
    }
    else {
      if (!elt.hasClassName('checkbox') && elt.readAttribute('type') != 'checkbox') {
        if (elt.value == "") {
          NTD.Control.removeClassChecked(elt);
        }
        else if (NTD.Control.isNumeric(elt)) {
          NTD.Control.removeClassChecked(elt);
          elt.addClassName('checked-true');
          //$(elt).value = $(elt).value.replace(',', '.');
        }
        else if ((!NTD.Control.isNumeric(elt) )) { //&& $(elt).value.charAt(0) == "-" || $(elt).value.charAt(2) == "." || $(elt).value.charAt(1) == ".")) {
          elt.addClassName('checked-true');
        }
        else {
          NTD.Control.removeClassChecked(elt);
          elt.addClassName('checked-false');
        }
      }
    }
  },

  /*checkValue : function(elt){
   NTD.Control.cleanError($(elt));
   if($(elt).value == "") {
   elt.removeClassName('checked-false');
   return;
   } else if(elt.hasClassName('checkbox') && elt.readAttribute('type') == 'checkbox') {
   return;
   } else if(NTD.Control.isNumeric(elt)) {
   $(elt).value = $(elt).value.replace(',','.');
   elt.removeClassName('checked-false');
   } else if(!NTD.Control.isNumeric(elt) &&
   $(elt).value.charAt(0) == "-" /*||
   $(elt).value.charAt(2) == "." ||
   $(elt).value.charAt(1) == ".") {
   elt.removeClassName('checked-false');
   } else {
   elt.addClassName('checked-false');
   }

   },	  */

  checkForm: function() {
    var ret = true;
    $$('.field').each(function(elt) {
      if (!$(elt).hasClassName('checked-true')) {
        ret = false;
        $(elt).scrollTo();
        alert('il y a une erreur dans le champ ' + elt.id);
        throw $break;
      }
    });
    if (ret) {
      alert('votre formulaire est correctement rempli');
    }
    return ret;
  },


  /* ----- Hugues : form control ----- */
  onValidate : function(form) {
    Kwo.exec('/ntd/formulaire.validate',
             form,
             {callback: NTD.Control.onValidateCallback.curry(form)});
  },



  onValidateCallback : function(form, res) {
    if (Kwo.hasError(res)) {
      return Kwo.error(res);
    }

    if (res['result'] && res['result']['errors'] && res['result']['errors'].length > 1) {
      var errors = $H(res['result']['errors']);
      errors.each(function (pair) {
        NTD.Control.removeClassChecked($(pair.key));
        $(pair.key).addClassName(pair.value.name);
        $(pair.key).next('.error_php').update(pair.value.msg);
      });
      $(errors.keys().first()).scrollTo();
    }
    else if (res['result'] && res['result']['tests'] && res['result']['tests'].length > 1) {
      var tests = $H(res['result']['tests']);
      tests.each(function (pair) {
        $(pair.key).next('.error_php').update(pair.value.msg);
      });
    }
    else {
      NTD.Control.onSubmit(form);
    }
  },
  onSubmit: function(form) {
    NTD.Control.cleanErrors();
    Kwo.exec('/ntd/formulaire.store', form, {
      callback: NTD.Control.onStoreCallback.curry(form)
    });
  },

  onSubmitCallback: function(res) {
    if (Kwo.hasError(res)) {
      return Kwo.error(res);
    }
    if (res['result'] && res['result']['errors']) {
      if (res['result']['errors'].length > 1) {
        var errors = $H(res['result']['errors']);
        errors.each(function (pair) {
          $(pair.key).addClassName(pair.value.name);
          $(pair.key).next('.error_php').update(pair.value.msg);
        });
        $(errors.keys().first()).scrollTo();
      }
    } else {
      alert('Votre formulaire a été enregistré avec succès');
    }
  }

};

NTD.Table = {
  onAddLine: function(elt, max_row) {
    var table = $(elt).up('table');
    var tpl = table.down('.row-tpl').innerHTML;
    var index = parseInt(table.readAttribute('data-index'));
    index++;
    if (index <= max_row) {
      var tr_content = tpl.replace(new RegExp("(#row#)", "g"), index);
      var tr = new Element('tr', {className:'elt'}).update(tr_content);

      table.down('tbody').insert(tr);
      table.writeAttribute('data-index', index);
      return;
    } else {
      return;
    }
  }
};

NTD.Tab = {
  show: function(el) {
    $$('.tab-content').invoke('hide');
    $$('.tab-nav').invoke('removeClassName', 'tab-nav-selected');
    $(el + '-tab-nav').addClassName('tab-nav-selected');
    $(el + '-tab-content').show();
  },
  showNav: function(el) {
    $(el + '-tab-nav').show();
    NTD.Tab.show(el);
  }
};

NTD.Number = {
  parseFloat: function(value) {
    var val = parseFloat(value);
    if (isNaN(val)) {
      return 0;
    }
    return val;
  }

};


