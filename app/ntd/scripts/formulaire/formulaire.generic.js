NTD.Generic = {

  addition : function(elt, num) {
    var operands = $(elt).getAttribute('data-addition-operands'+num).split(',');
    var results = $(elt).getAttribute('data-addition-results'+num).split(',');
    NTD.Control.setDependances(operands);
    var total = 0;
    operands.each(function(elt) {
      total += NTD.Number.parseFloat($(elt).value);
    });
    results.each(function(elt) {
      if (isNaN(total)) {
        NTD.Control.setValue($(elt), 0);
      } else {
        NTD.Control.setValue($(elt), parseFloat(total), true);
      }
    });
    NTD.Control.reset_operations(operands.concat(results));
  },

  soustraction : function(elt, num) {
    var results = $(elt).getAttribute('data-soustraction-results'+num).split(',');
    var value = $(elt).getAttribute('data-soustraction-value'+num);
    var operands = $(elt).getAttribute('data-soustraction-operands'+num).split(',');
    var args = $(elt).getAttribute('data-soustraction-args'+num).split(',');

    this._soustraction(value, operands, $(results[0]), args[0]);
  },

  // result = value - SUM(operands)
  _soustraction: function(value, operands, result, minimum){
    if (!Object.isArray(operands)) {
      operands = [operands];
    }
    NTD.Control.setDependances(operands, [value]);
    var total = parseFloat($(value).value);
    operands.each(function(elt) {
      //if($(elt).value == "") $(elt).value = 0;
      total -= parseFloat($(elt).value);
    });
    if (isNaN(total)) {
      NTD.Control.setValue(result, parseFloat(0));
    }
    else {
      if (!isNaN(minimum) && parseFloat(total) < parseFloat(minimum)) {
        total = args[0];
        NTD.Control.setValue(result, parseFloat(total));
      }
      else {
        NTD.Control.setValue(result, parseFloat(total), true);
      }
    }
    NTD.Control.reset_operations(operands.concat(result, [value]));
  },

  multiplication : function(elt, num) {
    var operands = $(elt).getAttribute('data-multiplication-operands'+num).split(',');
    var results = $(elt).getAttribute('data-multiplication-results'+num).split(',');
    var total = 1;
    NTD.Control.setDependances(operands);
    operands.each(function(elt) {
      //if($(elt).value == "") $(elt).value = 0;
      total *= parseFloat($(elt).value);
    });
    results.each(function(elt) {
      if (isNaN(total)) {
        NTD.Control.setValue($(elt), 0);
      } else {
        NTD.Control.setValue($(elt), parseFloat(total), true);
      }
    });
    NTD.Control.reset_operations(operands.concat(results));
  },


  positiv : function(elts) {
    if (!Object.isArray(elts)) {
      elts = [elts];
    }
    elts.each(function(elt) {
      elt = $(elt);
      elt.removeClassName('checked-false');
      elt.addClassName('checked-true');
    });
  },

  negativ : function(elts, tooltip_msg, error_code) {
    if (!Object.isArray(elts)) {
      elts = [elts];
    }
    elts.each(function(elt) {
      try{
        elt = $(elt);
        elt.removeClassName('checked-true');
        elt.addClassName('checked-false');
        if (tooltip_msg) {
          if (elt.type == "checkbox" || elt.type == "radio") {
            if(elt.up('.input-container')) {
              elt.up('.input-container').addClassName('has-error');
            }
            else if (elt.up('td')) {
              elt.up('td').addClassName('has-error');
            }
            else if (elt.up('th')) {
              elt.up('th').addClassName('has-error');
            }
          }
          if (elt.hasClassName('field-type-date-ssaamm')) {
              elt.next('div.elt-ssaamm-container').addClassName('has-error');
          }
          elt.addClassName('has-error');

          if(elt.up('.input-container') && elt.up('.input-container').next('.elt-tooltip')) {
            var tooltip = elt.up('.input-container').next('.elt-tooltip');
          }
          else if (elt.next('.elt-tooltip')) {
            var tooltip = elt.next('.elt-tooltip');
          }
          else{
            var tooltip = new Element('div', {className:'elt-tooltip'}).update('<div class="elt-tooltip-content"></div>');
            elt.insert({after:tooltip});
            tooltip.hide();
          }


          var tooltip_html = tooltip_msg;
          if(typeof error_code == "string" && error_code.length > 0) {
            if(typeof elt.tooltips === "undefined") {
              elt.tooltips = {};
            }
            elt.tooltips[error_code] = tooltip_msg;


            tooltip_html = '<ul style="list-style: inside none disc;">';

            for(var code  in elt.tooltips) {
              tooltip_html += "<li style='margin-bottom: 5px'>"
              + '<span style="display: none">[' + code + "] </span>"
              + elt.tooltips[code]
              + "</li>";
            }
            tooltip_html += "</ul>";
            //tooltip_msg = "<ul style='list-style: inside none disc;'><li>"+Object.values(elt.tooltips).join('</li><li>')+"</li></ul>";
          }
          else{
            tooltip_html = tooltip.down('.elt-tooltip-content').innerHTML+ tooltip_msg+"<br />";
          }

          tooltip.down('.elt-tooltip-content').update(tooltip_html);

        }
      }catch(error){
        console.error(error);
      }

    }, this);
  },

  none : function(elts, error_code) {
    if (!Object.isArray(elts)) {
      elts = [elts];
    }
    elts.each(function(elt) {
      elt = $(elt);
      if (elt.hasClassName('checked-false') && !elt.hasClassName('edited')) {
        elt.removeClassName('checked-false');
        elt.removeClassName('checked-true');
      }
      if (typeof error_code !== "undefined" && typeof elt.tooltips !== "undefined") {
        delete elt.tooltips[error_code];



        var tooltip_html = '<ul style="list-style: inside none disc;">';
        for(var code  in elt.tooltips) {
          tooltip_html += "<li style='margin-bottom: 5px'>"
          + '<span style="display: none">[' + code + "] </span>"
          + elt.tooltips[code]
          + "</li>";
        }
        tooltip_html += "</ul>";
        if(elt.up('.input-container') && elt.up('.input-container').next('.elt-tooltip')) {
          var tooltip = elt.up('.input-container').next('.elt-tooltip');
        }
        else if (elt.next('.elt-tooltip')) {
          var tooltip = elt.next('.elt-tooltip');
        }
        tooltip.down('.elt-tooltip-content').update(tooltip_html);
      }
      if(typeof elt.tooltips === "undefined" || Object.values(elt.tooltips).length == 0){
        if (elt.type == "checkbox" || elt.type == "radio") {
          if(elt.up('.input-container')) {
            elt.up('.input-container').removeClassName('has-error');
          }
          else if (elt.up('td')) {
            elt.up('td').removeClassName('has-error');
          }
          else if(elt.up('th')) {
            elt.up('th').removeClassName('has-error');
          }
        }
        elt.removeClassName('has-error');
      }
    });
  },

  check_need_and_or : function(elt, num) {
    //console.log('check_need_and_or');
    var i = 0;
    var results = $(elt).getAttribute('data-check-need-and-or-results'+num).split(',');
    var operands = $(elt).getAttribute('data-check-need-and-or-operands'+num).split(',');
    operands.each(function(elt) {
      elt = $(elt);
      if (elt.checked || elt.value != "" || elt.value != 0) {
        results.each(function(elt) {
          elt = $(elt);
          elt.disabled = false;
          if ((elt.value) != "") i++;
        });
        if (i == 0) {
          results.each(function(elt) {
            NTD.Generic.negativ(elt);
          });
        } else {
          results.each(function(elt) {
            NTD.Generic.positiv(elt);
          });
        }
      } else {
        results.each(function(elt) {
          elt = $(elt);
          elt.value = "";
          elt.disabled = true;
          NTD.Generic.none(elt);
        });
      }
    });
  },

  check_need_and_or_input : function(elt, num) {
    var i = 0;
    var results = $(elt).getAttribute('data-check-need-and-or-input-results'+num).split(',');
    var operands = $(elt).getAttribute('data-check-need-and-or-input-operands'+num).split(',');
    operands.each(function(elt) {
      if ($(elt).value != "") {
        results.each(function(elt) {
          if (($(elt).value) != "")
            i++;
        });
        if (i == 0) {
          results.each(function(elt) {
            NTD.Generic.negativ(elt);
            $(elt).addClassName('edited');
          });
        } else {
          results.each(function(elt) {
            NTD.Generic.positiv(elt);
          });
        }
      } else {
        //console.log('none');
        results.each(function(elt) {
          $(elt).removeClassName('edited');
          NTD.Generic.none(elt);
        });
      }
    });
  },

  check_uneed_and_or : function(elt, num) {
    var i = 0;
    var results = $(elt).getAttribute('data-check-uneed-and-or-results'+num).split(',');
    var operands = $(elt).getAttribute('data-check-uneed-and-or-operands'+num).split(',');

    operands.each(function(elt) {
      //console.log(elt.id);
      if ($(elt).value == "") {
        results.each(function(elt) {
          if (($(elt).value) == "")
            i++;
        });
        if (i == 0) {
          results.each(function(elt) {
            NTD.Generic.negativ(elt);
          });
        }
        else {
          results.each(function(elt) {
            NTD.Generic.positiv(elt);
          });
        }
      }
      else {
        results.each(function(elt) {
          NTD.Generic.none(elt);
        });
      }
    });
  },

  check_set_unchecked : function(elt, args) {
    //var items = $(elt).getAttribute('data-check-set-unchecked-results'+num).split(',');
    //var results = $(elt).getAttribute('data-check-set-unchecked-results'+num).split(',');
    //var operands = $(elt).getAttribute('data-check-set-unchecked-operands'+num).split(',');

    if ($(elt).checked) {
      if (args && args['fields']) {
        args['fields'].each(function(field) {
          if (elt == $(field)) return;
          $(field).checked = false;
        }, this);
      }
    }
  },

  check_positiv_zero_set_checked : function(elt, num) {
    var i = 0;
    var results = $(elt).getAttribute('data-check-positiv-zero-set-checked-results'+num).split(',');
    var operands = $(elt).getAttribute('data-check-positiv-zero-set-checked-operands'+num).split(',');

    operands.each(function(elt) {
      if (parseFloat($(elt).value) >= 0) {
        NTD.Generic.positiv(elt);
        results.each(function(elt) {
          $(elt).checked = true;
        });
      }
      else if (parseFloat($(elt).value) < 0) {
        NTD.Generic.positiv(elt);
        results.each(function(elt) {
          $(elt).checked = false;
        });
      }
      else {
        NTD.Generic.none(elt);
        results.each(function(elt) {
          $(elt).checked = false;
        });
      }
    });
  },

  check_positiv : function(elt, num) {
    var itemsArray = $(elt).getAttribute('data-check-positiv-items'+num).split(',');
    var item1 = $(itemsArray[0]);
    var item2 = $(itemsArray[1]);

    if (item1.value > 0 && (item2.value == 0 || item2.value == "")) {
      NTD.Generic.negativ(item2);
    } else if (item2.value > 0 && (item1.value == 0 || item1.value == "")) {
      NTD.Generic.negativ(item1);
    } else {
      NTD.Generic.none([item1, item2], true);
    }
  },

  check_negativ : function(elt, num) {
    var itemsArray = $(elt).getAttribute('data-check-negativ-items'+num).split(',');
    var item1 = $(itemsArray[0]);
    var item2 = $(itemsArray[1]);

    if (item1.value > 0 && (item2.value != 0 && item2.value != "")) {
      NTD.Generic.negativ(item2);
    } else if (item2.value > 0 && (item1.value != 0 && item1.value != "")) {
      NTD.Generic.negativ(item1);
    } else {
      NTD.Generic.none([item1, item2], true);
    }
  },

  check_positiv_one_item : function(elt, num) {
    var itemsArray = $(elt).getAttribute('data-check-positiv-one-item-items'+num).split(',');
    var item1 = $(itemsArray[0]);

    if (item1.value == "") {
      NTD.Generic.none(item1);
    } else if (item1.value <= 0) {
      NTD.Generic.negativ(item1);
    } else if (item1.value > 0) {
      NTD.Generic.positiv(item1);
    }
  },

  check_set_positiv_zero : function(elt, num) {
    var results = $(elt).getAttribute('data-check-set-positiv-zero-results'+num).split(',');
    var operands = $(elt).getAttribute('data-check-set-positiv-zero-operands'+num).split(',');

    if ($(operands[0]).checked == true) {
      results.each(function(elt) {
        if (parseFloat($(elt).value) >= 0)
          NTD.Generic.positiv(elt);
        else
          NTD.Generic.negativ(elt);
      });
    }
    else {
      results.each(function(elt) {
        NTD.Generic.none(elt);
      });
    }
  },

  check_set_empty : function(elt, num) {
    var results = $(elt).getAttribute('data-check-set-empty-results'+num).split(',');
    var operands = $(elt).getAttribute('data-check-set-empty-operands'+num).split(',');

    if ($(operands[0]).checked == true) {
      if (parseFloat($(elt).value) >= 0) {
        results.each(function(elt) {
          NTD.Control.setValue($(elt), "", true);
          NTD.Generic.positiv(elt);
        });
      }
      else {
        results.each(function(elt) {
          NTD.Generic.none(elt);
        });
        NTD.Control.removeValue(results.concat(results));
      }
    }
    else {
      results.each(function(elt) {
        NTD.Generic.none(elt);
      });
    }
  },

  check_positiv_zero : function(elt, num) {
    var results = $(elt).getAttribute('data-check-positiv-zero-results'+num).split(',');
    var operands = $(elt).getAttribute('data-check-positiv-zero-operands'+num).split(',');
    var x = 0;
    var y = 0;

    operands.each(function(elt) {
      if ($(elt).hasClassName('checked-false'))
        x = 1;

      if (parseFloat($(elt).value) > 0 && x == 0)
        NTD.Generic.positiv(elt);
      else if (parseFloat($(elt).value) <= 0)
        NTD.Generic.negativ(elt);
      else
        NTD.Generic.none(elt);
    });
    results.each(function(elt) {
      if ($(elt).hasClassName('checked-false'))
        y = 1;
      if (parseFloat($(elt).value) > 0 && y == 0)
        NTD.Generic.positiv(elt);
      else if (parseFloat($(elt).value) <= 0)
        NTD.Generic.negativ(elt);
      else
        NTD.Generic.none(elt);
    });
  },

  check_percent : function(elt, num) {
    var operands = $(elt).getAttribute('data-check-percent-operands'+num).split(',');
    var item = $(operands[0]);
    var value = item.value;
    if (value.indexOf('.') != -1) {
      if (value.split('.')[0].length > 2 || value.split('.')[1].length > 2) {
        NTD.Generic.negativ(elt);
      }
    } else if (value.length > 2) {
      NTD.Generic.negativ(elt);
    } else if (value == "") {
      NTD.Generic.none(elt);
    } else {
      NTD.Generic.positiv(elt);
    }
  },

  check_egal_percent : function(elt, num) {
    var results = $(elt).getAttribute('data-check-egal-percent-results'+num).split(',');
    var x = 0;

    results.each(function(elt) {
      if ($(elt).hasClassName('checked-false'))
        x = 1;
      if (parseFloat($(elt).value) >= 0 && parseFloat($(elt).value) <= 100 && x == 0)
        NTD.Generic.positiv(elt);
      else if (parseFloat($(elt).value) < 0 || parseFloat($(elt).value) > 100 || x == 1)
        NTD.Generic.negativ(elt);
      else
        NTD.Generic.none(elt);
    });
  },

  check_inf_egal: function(elt, num) {
    var operands = $(elt).getAttribute('data-check-inf-egal-operands'+num).split(',');
    var x = false;
    var y = false;

    if ($(operands[0]).hasClassName('checked-false'))
      x = true;
    if ($(operands[1]).hasClassName('checked-false'))
      y = true;

    if ($(operands[0]).hasClassName('pulse'))
      x = false;
    else if ($(operands[1]).hasClassName('pulse'))
      y = false;

    if (parseFloat($(operands[0]).value) <= parseFloat($(operands[1]).value) && !x)
      NTD.Generic.positiv(operands[0]);
    else if (parseFloat($(operands[0]).value) > parseFloat($(operands[1]).value) || x)
      NTD.Generic.negativ(operands[0]);
    else
      NTD.Generic.none(operands[0]);

    if (parseFloat($(operands[0]).value) <= parseFloat($(operands[1]).value) && !y)
      NTD.Generic.positiv(operands[1]);
    else if (parseFloat($(operands[0]).value) > parseFloat($(operands[1]).value) || y)
      NTD.Generic.negativ(operands[1]);
    else
      NTD.Generic.none(operands[1]);
  },

  check_inf: function(elt, num) {
    var operands = $(elt).getAttribute('data-check-inf-operands'+num).split(',');
    var x = false;
    var y = false;

    if ($(operands[0]).hasClassName('checked-false'))
      x = true;
    if ($(operands[1]).hasClassName('checked-false'))
      y = true;

    if ($(operands[0]).hasClassName('pulse'))
      x = false;
    else if ($(operands[1]).hasClassName('pulse'))
      y = false;

    if (parseFloat($(operands[0]).value) < parseFloat($(operands[1]).value) && !x)
      NTD.Generic.positiv(operands[0]);
    else if (parseFloat($(operands[0]).value) >= parseFloat($(operands[1]).value) || x)
      NTD.Generic.negativ(operands[0]);
    else
      NTD.Generic.none(operands[0]);

    if (parseFloat($(operands[0]).value) < parseFloat($(operands[1]).value) && !y)
      NTD.Generic.positiv(operands[1]);
    else if (parseFloat($(operands[0]).value) >= parseFloat($(operands[1]).value) || y)
      NTD.Generic.negativ(operands[1]);
    else
      NTD.Generic.none(operands[1]);
  },

  format_ssaammjj: function(elt, num) {
    var itemsArray = $(elt).getAttribute('data-format-ssaammjj-items'+num).split(',');
    //console.log(itemsArray);
    var item = $(itemsArray[0]);
    var date = item.value;
    var SS = date.substring(0, 2);
    var AA = date.substring(4, 2);
    var MM = date.substring(6, 4);
    var JJ = date.substring(8, 6);
    if (parseFloat(SS) < 01 || parseFloat(SS) > 99 ||
            parseFloat(AA) < 00 || parseFloat(AA) > 99 ||
            parseFloat(MM) < 01 || parseFloat(MM) > 12 ||
            parseFloat(JJ) < 01 || parseFloat(JJ) > 31) {
      NTD.Generic.negativ(item);
    } else {
      NTD.Generic.positiv(item);
    }
  },

  format_jjmmaa: function(elt, num) {
    var date = $F(elt);
    var JJ = date.substring(0, 2);
    var MM = date.substring(5, 3);
    var AAAA = date.substring(10, 6);

    if (parseFloat(JJ) < 01 || parseFloat(JJ) > 31 ||
            parseFloat(MM) < 01 || parseFloat(MM) > 12 ||
            parseFloat(AAAA) < 0000 || parseFloat(AAAA) > 9999) {
      NTD.Generic.negativ(elt);
    } else {
      NTD.Generic.positiv(elt);
    }
  },

  format_mm: function(elt, num) {
    var itemsArray = $(elt).getAttribute('data-format-mm-items'+num).split(',');
    var item = $(itemsArray[0]);
    var date = item.value;
    var MM = date.substring(0, 2);
    if (parseFloat(MM) < 01 || parseFloat(MM) > 12) {
      NTD.Generic.negativ(item);
    } else {
      NTD.Generic.positiv(item);
    }
  },

  format_mmaa: function(elt, num) {
    var itemsArray = $(elt).getAttribute('data-format-mmaa-items'+num).split(',');
    var item = $(itemsArray[0]);
    var date = item.value;
    var month = date.substring(0, 2);
    var year = date.substring(3, 7);
    if (parseFloat(month) < 0 || parseFloat(month) > 12 ||
            parseFloat(year) < 0 || parseFloat(year) > 9999) {
      NTD.Generic.negativ(item);
    } else if (date.length > 7) {
      NTD.Generic.negativ(item);
    } else {
      NTD.Generic.positiv(item);
    }
  },

  format_ssaamm: function(elt, num) {
    var itemsArray = $(elt).getAttribute('data-format-ssaammjj-items'+num).split(',');
    var item = $(itemsArray[0]);
    var date = item.value;
    var SS = format_ssaammdate.substring(0, 2);
    var AA = date.substring(4, 2);
    var MM = date.substring(6, 4);
    if (parseFloat(SS) < 01 || parseFloat(SS) > 99 ||
            parseFloat(AA) < 00 || parseFloat(AA) > 99 ||
            parseFloat(MM) < 01 || parseFloat(MM) > 12) {
      NTD.Generic.negativ(item);
    } else {
      NTD.Generic.positiv(item);
    }
  },

  check_positiv_zero_set_zero : function(elt, num) {
    var results = $(elt).getAttribute('data-check-positiv-zero-set-zero-results'+num).split(',');
    var operands = $(elt).getAttribute('data-check-positiv-zero-set-zero-operands'+num).split(',');

    operands.each(function(elt) {
      if (parseFloat($(elt).value) >= 0) {
        NTD.Generic.positiv(elt);
        results.each(function(elt) {
          NTD.Control.setValue($(elt), 0, true);
        });
      }
      else {
        if ($(elt).hasClassName('checked-true'));
        $(elt).removeClassName('checked-true');
        $(elt).addClassName('checked-false');
      }
    });
  },

  check_full_set_zero : function(elt, num) {
    var results = $(elt).getAttribute('data-check-full-set-zero-results'+num).split(',');
    var operands = $(elt).getAttribute('data-check-full-set-zero-operands'+num).split(',');
    var i = 0;

    operands.each(function(elt) {
      if (operands.each == "")
        i++;
    });
    if (i == 0) {
      results.each(function(elt) {
        NTD.Control.setValue($(elt), 0, true);
      });
    }
    else
      NTD.Control.removeValue(results.concat(results));
  },


  /*------------------------------------Bon, mais ajouter le removevalue--------------------------------*/
  /*------------------------------------Aucune idée d'ou on en est avec elle meme après relecture en fait--------------------------------*/


  check_positiv_set_zero : function(elt, num) {
    var results = $(elt).getAttribute('data-check-positiv-set-zero-results'+num).split(',');
    var operands = $(elt).getAttribute('data-check-positiv-set-zero-operands'+num).split(',');
    operands.each(function(elt) {
      if (parseFloat($(elt).value) > 0) {
        NTD.Generic.positiv(elt);
        results.each(function(elt) {
          NTD.Control.setValue($(elt), 0, true);
        });
      }
      else {
        if ($(elt).hasClassName('checked-true'));
        $(elt).removeClassName('checked-true');
        $(elt).addClassName('checked-false');
      }
    });
  },

  /*------------------------------------Bon, mais ajouter le removevalue--------------------------------*/


  check_positiv_set_full : function(elt, num) {
    var results = $(elt).getAttribute('data-check-positiv-set-full-results'+num).split(',');
    var operands = $(elt).getAttribute('data-check-positiv-set-full-operands'+num).split(',');

    operands.each(function(elt) {
      if (parseFloat($(elt).value) > 0) {
        NTD.Generic.positiv(elt);
        results.each(function(elt) {
          if (($(elt).value) != "")
            NTD.Generic.positiv(elt);
          else if (($(elt).value) == "")
            NTD.Generic.negativ(elt);
        });
      }
      else if (parseFloat($(elt).value) <= 0) {
        NTD.Generic.negativ(elt);
        results.each(function(elt) {
          NTD.Generic.none(elt);
        });
      }
      else {
        NTD.Generic.none(elt);
        results.each(function(elt) {
          NTD.Generic.none(elt);
        });
      }
    });
    ;
  },

  check_positiv_set_empty : function(elt, num) {
    var results = $(elt).getAttribute('data-check-positiv-set-empty-results'+num).split(',');
    var operands = $(elt).getAttribute('data-check-positiv-set-empty-operands'+num).split(',');

    operands.each(function(elt) {
      if (parseFloat($(elt).value) > 0) {
        NTD.Generic.positiv(elt);
        results.each(function(elt) {
          NTD.Control.setValue($(elt), "", true);
        });
      }
      else if (parseFloat($(elt).value) <= 0) {
        NTD.Generic.negativ(elt);
        results.each(function(elt) {
          NTD.Generic.none(elt);
        });
      }
      else {
        NTD.Generic.none(elt);
        results.each(function(elt) {
          NTD.Control.removeValue(results.concat(operands)); // ca c'est a verifier, le results.concat(operands) je le sent très moderement
          NTD.Generic.none(elt);
        });
      }
    });
  },

  check_positiv_zero_set_full : function(elt, num) {
    var results = $(elt).getAttribute('data-check-positiv-zero-set-full-results'+num).split(',');
    var operands = $(elt).getAttribute('data-check-positiv-zero-set-full-operands'+num).split(',');

    operands.each(function(elt) {
      if (parseFloat($(elt).value) >= 0) {
        NTD.Generic.positiv(elt);
        results.each(function(elt) {
          if (parseFloat($(elt).value) != null)
            NTD.Generic.positiv(elt);
          else if (parseFloat($(elt).value) == null)
            NTD.Generic.negativ(elt);
        });
      }
      else if (parseFloat($(elt).value) < 0) {
        NTD.Generic.negativ(elt);
        results.each(function(elt) {
          NTD.Generic.none(elt);
        });
      }
      else {
        NTD.Generic.none(elt);
        results.each(function(elt) {
          NTD.Generic.none(elt);
        });
      }
    });
    ;
  },

  check_positiv_zero_set_empty : function(elt, num) {
    var results = $(elt).getAttribute('data-check-positiv-zero-set-empty-results'+num).split(',');
    var operands = $(elt).getAttribute('data-check-positiv-zero-set-empty-operands'+num).split(',');

    operands.each(function(elt) {
      if (parseFloat($(elt).value) >= 0) {
        NTD.Generic.positiv(elt);
        results.each(function(elt) {
          NTD.Generic.positiv(elt);
          NTD.Control.setValue($(elt), "", true);
        });
      }
      else if (parseFloat($(elt).value) < 0) {
        NTD.Generic.negativ(elt);
        results.each(function(elt) {
          NTD.Generic.negativ(elt);
          NTD.Generic.none(elt);
        });
      }
      else {
        NTD.Generic.none(elt);
        results.each(function(elt) {
          NTD.Control.removeValue(results.concat(operands));
          NTD.Generic.none(elt);
        });
      }
    });
  },

  check_null_or_zero_set_zero : function(elt, num) {
    var results = $(elt).getAttribute('data-check-null-or-zero-set-zero-results'+num).split(',');
    var operands = $(elt).getAttribute('data-check-null-or-zero-set-zero-operands'+num).split(',');

    if (($(operands[0]).value) == "" || parseFloat($(operands[0]).value) == 0) {
      results.each(function(elt) {
        NTD.Control.setValue($(elt), 0, true);
      });
    }
    else {
      results.each(function(elt) {
        $(elt).removeAttribute('readonly', 'readonly');
        $(elt).removeClassName('result');
        NTD.Generic.none(elt);
      });
    }
  },

  check_full : function(elt, num) {
    var results = $(elt).getAttribute('data-check-full-results'+num).split(',');
    var operands = $(elt).getAttribute('data-check-full-operands'+num).split(',');
    var value = $(elt).type == "radio" || $(elt).type == "checkbox" ? ($(elt).checked ? 1 : "") : $(elt).value;
    if (value != "") {
      operands.each(function(elt) {
        if ($(elt).readAttribute('readonly') && !$(elt).hasClassName('result')) {
          $(elt).removeAttribute('readonly');
        }
        if (($(elt).value) == "") NTD.Generic.negativ(elt);
      });
      results.each(function(elt) {
        if (($(elt).value) == "") NTD.Generic.negativ(elt);
      });
    }
    else {
      operands.each(function(elt) {
          NTD.Generic.positiv(elt);
        });
        results.each(function(elt) {
          NTD.Generic.positiv(elt);
      });
    }
  },

  check_negativ_or_zero_disable : function(elt, num) {
    var results = $(elt).getAttribute('data-check-negativ-or-zero-disable-results'+num).split(',');
    var operands = $(elt).getAttribute('data-check-negativ-or-zero-disable-operands'+num).split(',');

    if ($(operands[0]).value > 0)
      NTD.Control.removeValue(results.concat(results));
    else
      NTD.Control.setValue($(results[0]), "", true);
  },

  disable : function(elt, num) {
    var itemsArray = $(elt).getAttribute('data-disable-items'+num).split(',');
    var KF = $(itemsArray[0]);
    if (KF.checked) {
      //console.log('disable');
      $$('.field').each(function(elt) {
        if (elt.id.contains('identif')) return;
        if (itemsArray.indexOf(elt.id) == -1) {
          NTD.Control.removeValue([elt]);
          NTD.Control.disable_field([elt]);
          //elt.setAttribute('disable', 'disable');
        }
      });
      $$('.form-show').each(function(elt) {
        elt.hide();
      });
    }
    else {
      NTD.Control.enable_field($$('.field'));
      $$('.form-show').each(function(elt) {
        elt.show();
      });
    }
  },

  check_integer : function(elt, num) {
    var results = $(elt).getAttribute('data-check-integer-results'+num).split(',');
    if (isNaN($(results[0]))) {
      return;
    } else {
      $(results[0]).value = parseInt($(results[0]).value);
    }
  },

  report : function(elt, num) {
    var results = $(elt).getAttribute('data-report-results'+num).split(',');
    var operands = $(elt).getAttribute('data-report-operands'+num).split(',');

    var total = $(operands[0]).value;
    results.each(function(elt) {
      NTD.Control.setValue($(elt), total, true);
    });
  },

  empty_and_desactive : function(elt, num) {
    elt = $(elt);
    if (!elt.checked) return false;
    var results = $(elt).getAttribute('data-empty-and-desactive-results'+num).split(',');
    var operands = $(elt).getAttribute('data-empty-and-desactive-operands'+num).split(',');
    operands.each(function(elt) {
      $(elt).value = "";
      $(elt).writeAttribute('readonly', 'readonly');
      NTD.Generic.none(elt);
    });
  },

  copy_value: function(elt, args) {
    var target = $(args['target']);
    if (!target
            || target.disabled
            || elt.disabled
            || (elt.hasAttribute('disabled') && elt.readAttribute('disabled') == 'disabled')
            ) {
      return false;
    }
    target.setValue($F(elt));
    target.onchange();
  },

  check_bic: function(elt, num) {
    if ($(elt).value.length == 0) return;
    var regex = new RegExp("^[A-Z0-9]+$");
    if ($(elt).value.length != 8 && $(elt).value.length != 11 && !regex.exec($(elt).value)) {
      NTD.Generic.negativ(elt, "BIC incorrect", "erreur_bic");
    }
    else {
      NTD.Generic.positiv(elt);
    }
  },

  check_iban: function(elt, num) {
    if ($(elt).value.length == 0) return;
    var regex = new RegExp("^[A-Z]{2}[0-9]{2}[A-Z0-9]+$");
    if ($(elt).value.length < 27 || !regex.exec($(elt).value)) {
      NTD.Generic.negativ(elt, "IBAN incorrect", "erreur_iban");
    }
    else {
      NTD.Generic.positiv(elt);
    }
  },

  integrity_equation: function(elt, args) {
    var left = args['left'];
    var right = args['right'];
    var operator= args['operator'];
    if(!operator) {
      operator = '=';
    }
    var total_left = 0;
    var total_right = 0;
    left.each(function(left_elt) {
      total_left += Number($F(left_elt));
    }, this);
    right.each(function(right_elt) {
      total_right += Number($F(right_elt));
    }, this);

    left.each(function(left_elt) {
      $(left_elt).removeClassName('has-error');
    }, this);
    right.each(function(right_elt) {
      $(right_elt).removeClassName('has-error');
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
        NTD.Generic.positiv($(left_elt));
      }, this);
      right.each(function(right_elt) {
        NTD.Generic.positiv($(right_elt));
      }, this);
    } else {
      left.each(function(left_elt) {
        NTD.Generic.negativ($(left_elt));
      }, this);
      right.each(function(right_elt) {
        NTD.Generic.negativ($(right_elt));
      }, this);
    }
  }

};

NTD.Generic.date_ssaamm = {

  onSelectChange:function(elt, select_month, select_year) {
    if ($F(select_month) == "" || $F(select_year) == "") return elt.setValue("");
    var month = Number($F(select_month)).toPaddedString(2);
    var date = month+'/'+$F(select_year);
    elt.setValue(date);
  }

};

NTD.Generic.date_ssmmjj = {

  onSelectChange:function(elt) {
    var fieldId = elt.readAttribute('id');
    var container = elt.up('.elt-ssmmjj-container');

    if (fieldId.slice(-3) == 'day') {
      var input = container.previous('input.'+fieldId.substr(0, fieldId.length-4));
    } else {
        var input = container.previous('input.'+fieldId.substr(0, fieldId.length-6));
    }
    var selects = container.select('select');
    var select_day = $F(selects[0]);
    var select_month = $F(selects[1]);


    if (select_day == "" || select_month == "") return input.setValue("");
    var day = Number(select_day).toPaddedString(2);
    var date = day+'/'+Number(select_month).toPaddedString(2);
    input.setValue(date);
  }

};

