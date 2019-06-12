var ntd = {};

ntd.formulaire = {
  onPHPValidate: function(form, formulaire_type) {
    Kwo.exec('/account/ntd/account.formulaire.validate',
             Kwo.mergeArgs(form, {formulaire_validate_type: formulaire_type}),
             {callback: ntd.formulaire.onPHPValidateCallback});
  },

  onPHPValidateCallback: function(res) {
    if (Kwo.hasError(res)) return Kwo.error(res);
    if (res['result'] && res['result']['errors']) {
      var errors = $H(res['result']['errors']);
      errors.each(function(pair) {
        NTD.Control.removeClassChecked($(pair.key));
        $(pair.key).next('.output').update(pair.value.msg).show();
      });
      $(errors.keys().first()).scrollTo();

    } else if (res['result'] && res['result']['tests']) {
      if (res['result']['tests'].length > 0) {
        var tests = $H(res['result']['tests']);
        tests.each(function(pair) {
          $(pair.key).next('.output').update(pair.value.msg);
        });
      }
    }
  },

  onEnabled: function(elt) {
    $(elt).select('input, select, textarea').each(function(el) {
      el.removeAttribute('disabled');
    });
    $(elt).select('input, select, textarea').each(function(el) {
      try {
        if (typeof el.onchange !== "function") {
          return;
        }
        el.onchange();
      }
      catch (error) {
        console.log(el, error);
      }
    });
  },

  onDisabled: function(elt) {
    $(elt).select('input, select, textarea')
      .invoke('writeAttribute', {'disabled': 'disabled'});
  },

  onShowAndEnabled: function(elt, target, disabled) {
    disabled = typeof disabled !== 'undefined' ? disabled : false;
    if (elt) {
      $(elt).up().insert('<img class="form-loader" src="/app/ntd/pix/form_loader.gif" />');
      new PeriodicalExecuter(function(pe) {
        pe.stop();
        $(target).addClassName('formulaire-page');
        ntd.formulaire.onEnabled(target);
        $(target).show();
        $(target).select('.page-form').each(function(page) {
            page.show();
        })
        var codeForm = $(target).readAttribute('data-code');
        $$('.formulaire-repetable').each(function(element) {
          if (element.hasClassName(codeForm)) {
            element.select('option').each(function(elt, index){
              if (index == 0) {
                elt.selected = true;
              } else {
                elt.selected = false;
              }
            })
            element.show();
          } else {
            element.hide();
          }
        })
        $(elt).up().select('.form-loader').invoke('remove');
      }, 1);
    } else {
      $(target).addClassName('formulaire-page');
      if (!disabled) {
        ntd.formulaire.onEnabled(target);
      }
      $(target).show();
    }
    $(target).insert({top: '<div class="break"></div>'});
  },

  onHideAndDisabled: function(elt, target) {
    $(target).hide();
    $(target).removeClassName('formulaire-page');
    ntd.formulaire.onDisabled(target);
    if ($(target).down('.temp')) {
      $(target).down('.break').remove();
    }
    var codeForm = $(target).readAttribute('data-code');
    $$('.formulaire-repetable').each(function(element) {
      if (element.hasClassName(codeForm)) {
        element.hide();
      }
    })
  },

  onShow: function(elt) {
    $(elt).up('div').select('a').invoke('removeClassName', 'selected');
    $(elt).addClassName('selected');
    $$('.formulaire-visibility').invoke('hide');
    var checkbox = $(elt).down('input[type=checkbox]');
    var codeForm = $($(elt).readAttribute('data-item')).readAttribute('data-code');
      $$('.formulaire-repetable').each(function(element) {
          if (element.hasClassName(codeForm)) {
              element.select('option').each(function(elt, index){
                  if (index == 0) {
                      elt.selected = true;
                  } else {
                      elt.selected = false;
                  }
              })
              element.show();
          } else {
              element.hide();
          }
      })
    if (!checkbox || (checkbox && checkbox.checked)) {
      var eltToShow =  $($(elt).readAttribute('data-item'));
        eltToShow.show();
        eltToShow.select('.page-form').each(function(page) {
            page.show();
        })
      ntd.formulaire.onEnabled($($(elt).readAttribute('data-item')));
    }
  }

};

ntd.declaration = {
  onSubmit: function(form) {
    if (!confirm($(form).readAttribute('data-confirm'))) return false;
    var formAnnexesBox = $('formulairetype-annexes-box')
    if (formAnnexesBox) {
        formAnnexesBox.select('a').each(function(e) {
            if (e.select('input')[0].checked) {
                ntd.formulaire.onEnabled($($(e).readAttribute('data-item')));
            }
        })
    }

    Kwo.exec('/account/ntd/account.declaration.store', form, {callback: ntd.declaration.onSubmitCallback});
  },
  onSubmitCallback: function(res) {
      var errorLabels = $$('.error-label-occurence');
      errorLabels.each(function(e) {
          $(e).remove();
      })
    if (Kwo.hasError(res)) {
      var errors = $H(res['result']['errors']);
      $$('.formulaires-pagines .formulaire-block').each(function(e) {
          var repetablePages = $(e).select('.page-form');
          var formCode = $(e).readAttribute('data-code');
          var repatableSelectContainer = $$('.formulaire-repetable.'+formCode)[0];
          if (repatableSelectContainer) {
              repatableSelectContainer.select('.select-occurence option').each(function (option) {
                  option.innerHTML = option.text.replace('*** [ERREUR] *** - ', '');
              });
          }
          repetablePages.each(function(elt) {
              if ($(elt).select('.has-error').length) {
                  var occurenceNb =  $(elt).readAttribute('data-position')
                  if ($$('.formulaire-repetable.'+formCode).length) {
                      if (repatableSelectContainer) {
                          var occurenceOption = repatableSelectContainer.select('.select-occurence option[value="'+occurenceNb+'"]')[0];
                          var occurenceOptionText = occurenceOption.text
                          var regex1 = new RegExp('ERREUR');
                          if (!regex1.test(occurenceOptionText)) {
                              occurenceOption.innerHTML = '*** [ERREUR] *** - ' + occurenceOption.text
                          }
                      }
                  }
              }
          })
      })
      $$('.has-error').invoke('removeClassName', 'has-error');
      errors.each(function(pair) {
        if (pair.value.elt) {
          // new method
          NTD.Generic.negativ(pair.value.elt, asserts.core.$dico(pair.value.error_code), pair.value.error_code);
        }
        else {
          // old method
          if (!$(pair.key)) {
            console.error('pair.key [' + pair.key + '] not exists');
            return;
          }
          if ($(pair.key).hasClassName('disabled')) $(pair.key).removeClassName('disabled');
          $(pair.key).addClassName('has-error');
          if (!$(pair.key).next('.elt-tooltip')) {
            var tooltip = new Element('div', {className: 'elt-tooltip'}).update('<div class="elt-tooltip-content"></div>');
            $(pair.key).insert({after: tooltip});
            tooltip.hide();
          }
          $(pair.key).next('.elt-tooltip').down('.elt-tooltip-content').update(pair.value.msg);
        }
      });
      //$(errors.keys().first()).scrollTo();
      Kwo.error(res);
    } else {
      alert('votre déclaration a bien été enregistrée. (N°' + res['result']['id'] + ')');
      Kwo.go('/middle/declarations');
    }
  },
  onPrint: function(elt) {
    elt = $(elt);
    var key = elt.readAttribute('data-key');
    Kwo.go('/declaration.pdf', {key: key}, {target: 'blank'});
  },
  onDisabled: function() {
    if ($$('.account-declaration-edit-box').length <= 0) return;
    $$('.account-declaration-edit-box')[0].select('input[type=radio], input[type=checkbox], input[type=text], select:not(.select-occurence), textarea')
      .invoke('writeAttribute', {'disabled': 'disabled'});
  },
  onDuplicate: function(declaration_id) {
    if (!confirm("êtes-vous sur de vouloir modifier votre déclaration ?\nLa déclaration sera dupliquée et accessible dans le menu 'Accès formulaires déclaratifs'")) return false;
    Kwo.exec('/account/ntd/account.declaration.duplicate', {declaration_id: declaration_id}, {callback: ntd.declaration.onDuplicateCallback});
  },
  onDuplicateCallback: function(res) {
    if (Kwo.hasError(res)) {
      return Kwo.error(res);
    }
    alert('La déclaration a été dupliquée : N°' + res['result']['declaration_id']);
    Kwo.go('/account/ntd/account.declaration.edit', {declaration_id: res['result']['declaration_id']});
  }
};


ntd.declaration.PaginationController = Class.create({
                                                      pagesContainer: null,
                                                      pages: null,
                                                      form: null,
                                                      pageRepetables: null,
                                                      initialize: function(pagesContainer, form) {
                                                        this.pagesContainer = pagesContainer;
                                                        this.form = form;

                                                        this.pageRepetables = $$('.imprime-page.formulaire-repetable')
                                                        // construction du cheminard
                                                        this.pages = [];
                                                        this.pagesContainer.select('.formulaire-page').each(function(elt) {
                                                          if (!elt.up('.formulaires-annexes-no-required')) {
                                                            this.pages.push(elt);
                                                          }
                                                        }, this);

                                                        var pages = [];
                                                        var firsts = [];
                                                        var lasts = [];
                                                        this.pages.each(function(elt) {
                                                          if (elt.readAttribute('data-position') == 'last') {
                                                            lasts.push(elt);
                                                          } else if (elt.readAttribute('data-position') == 'first') {
                                                            firsts.push(elt);
                                                          } else {
                                                            pages.push(elt);
                                                          }
                                                          if (elt.up('.formulaire-block')) {
                                                            elt.up('.formulaire-block').addClassName('hidden');
                                                          }
                                                          if (elt.select('table')[0]) {
                                                            var formName =  elt.select('table')[0].getAttribute('class')
                                                            if (formName) {
                                                                asserts.run(formName);
                                                            }
                                                          }
                                                        }, this);
                                                        this.pages = firsts.concat(pages, lasts);
                                                        $('declaration-steps-box').addClassName('steps-count-' + this.pages.size());
                                                        this.pages.each(function(page, index) {
                                                          var span = new Element('span', {className: 'step-name step-' + (index + 1)}).update(page.readAttribute('data-label'));
                                                          $('declaration-steps-box').insert(span);
                                                        });

                                                        // buttons
                                                        this.form.select('.pagination-previous').invoke('hide');
                                                        this.form.select('.submit').invoke('hide');
                                                        this.form.select('.cancel').invoke('hide');

                                                        // formulaire-page
                                                        this.pages.invoke('hide');
                                                        $$('.page-form').invoke('hide');
                                                        this.pages.first().show().addClassName('visible');
                                                        if (this.pages.first().up('.formulaire-block')) {
                                                          this.pages.first().up('.formulaire-block').removeClassName('hidden');
                                                        }
                                                        $('declaration-steps-box').addClassName('current-step-1');
                                                        if (this.form.down('.formulaire-annexes')) {
                                                          this.form.down('.formulaires-pagines').insert({bottom: this.form.down('.formulaire-annexes')});
                                                        }
                                                      },


                                                      next: function() {
                                                        var current_formulaire = this.pagesContainer.down('.page-form.visible').hide().removeClassName('visible');
                                                        var formBlock = current_formulaire.up('.formulaire-block');
                                                        if (formBlock) {
                                                            formBlock.addClassName('hidden');
                                                        }

                                                        var next_formulaire;
                                                        // nextForm is for repetable forms. It's actual page to display instead of next_formulaire that represent the form "type"
                                                        var nextForm;
                                                        if (current_formulaire.hasClassName('formulaire-page')) {
                                                          next_formulaire = this.pages[this.pages.indexOf(current_formulaire) + 1];
                                                          nextForm = next_formulaire;
                                                        } else {
                                                          var previousFormulairePage = current_formulaire.previous('.formulaire-page');
                                                          if (current_formulaire.readAttribute('data-label') != previousFormulairePage.readAttribute('data-label')) {
                                                              previousFormulairePage = previousFormulairePage.previous('.formulaire-page');
                                                          }
                                                          next_formulaire = this.pages[this.pages.indexOf(previousFormulairePage) + 1];

                                                          nextForm = current_formulaire.next('.page-repetable');
                                                          if (nextForm) {
                                                              while ((nextForm instanceof Element || nextForm instanceof HTMLDocument) && current_formulaire.readAttribute('data-position') != nextForm.readAttribute('data-position')) {
                                                                  nextForm = nextForm.next('.page-repetable');
                                                              }
                                                          }
                                                        }

                                                        if (nextForm) {
                                                            nextForm.show().addClassName('visible');
                                                        } else {
                                                            next_formulaire.addClassName('visible')
                                                        }

                                                        if (next_formulaire.hasClassName('formulaire-annexes')) {
                                                           var linksAnnexe = $('formulairetype-annexes-box').select('a.selected')
                                                            if (linksAnnexe[0].select('input:checked').length) {
                                                                linksAnnexe[0].click();
                                                            }
                                                        }

                                                        var nextFormulaireFormBlock = next_formulaire.up('.formulaire-block')

                                                        if (nextFormulaireFormBlock) {
                                                          nextFormulaireFormBlock.removeClassName('hidden');

                                                          var nextFormulaireCode = next_formulaire.up('.formulaire-block').readAttribute('data-code');
                                                          $$('.formulaire-repetable').each(function(element) {
                                                              if (element.hasClassName(nextFormulaireCode)) {
                                                                element.select('option').each(function(elt, index){
                                                                  if (index == nextForm.readAttribute('data-position')) {
                                                                      elt.selected = true;
                                                                  } else {
                                                                      elt.selected = false;
                                                                  }
                                                                })
                                                                element.show();
                                                              } else {
                                                                element.hide();
                                                              }
                                                          })

                                                          var formulaireName = nextFormulaireFormBlock.down('.page-form table').readAttribute('class');
                                                          asserts.run(formulaireName);
                                                        }

                                                        this.form.select('.pagination-previous').invoke('show');
                                                        if (!this.pages[this.pages.indexOf(next_formulaire) + 1]) {
                                                          this.form.select('.pagination-next').invoke('hide');
                                                          this.form.select('.submit').invoke('show');
                                                          this.form.select('.cancel').invoke('show');
                                                          var nextFormBlock = next_formulaire.up('.formulaire-block');
                                                          var nextFormFtype = nextFormBlock.down('.ftype-code');
                                                          if (nextFormFtype.innerHTML.indexOf('identif') != -1
                                                            || nextFormFtype.innerHTML.indexOf('IDENTIF') != -1
                                                            || nextFormFtype.innerHTML.indexOf('Identif') != -1) {
                                                              nextFormBlock.down('.formulaire-header').addClassName('hidden');
                                                          }
                                                          $$('.hide-on-last-page').invoke('hide');
                                                        }
                                                        this.processStepBox();
                                                      },


                                                      previous: function() {
                                                        var current_formulaire = this.pagesContainer.down('.page-form.visible').hide().removeClassName('visible');
                                                        var formBlock = current_formulaire.up('.formulaire-block');
                                                        if (formBlock) {
                                                          formBlock.addClassName('hidden');
                                                        }

                                                        var previous_formulaire;
                                                        // prevForm is for repetable forms. It's actual page to display instead of previous_formulaire that represent the form "type"
                                                        var prevForm;
                                                        if (current_formulaire.hasClassName('formulaire-page')) {
                                                            previous_formulaire =  this.pages[this.pages.indexOf(current_formulaire) - 1];
                                                            prevForm = previous_formulaire;
                                                        } else {
                                                            var previousFormulairePage = current_formulaire.previous('.formulaire-page');
                                                            if (current_formulaire.readAttribute('data-label') != previousFormulairePage.readAttribute('data-label')) {
                                                                previousFormulairePage = previousFormulairePage.previous('.formulaire-page');
                                                            }
                                                            previous_formulaire = this.pages[this.pages.indexOf(previousFormulairePage) - 1];

                                                            prevForm = current_formulaire.previous('.page-repetable');
                                                            if (prevForm) {
                                                                while ((prevForm instanceof Element || prevForm instanceof HTMLDocument) && current_formulaire.readAttribute('data-position') != prevForm.readAttribute('data-position')) {
                                                                    prevForm = prevForm.previous('.page-repetable');
                                                                }
                                                            }
                                                        }

                                                        if (prevForm) {
                                                            prevForm.show().addClassName('visible');
                                                        } else {
                                                            previous_formulaire.show().addClassName('visible');
                                                        }

                                                        if (previous_formulaire.hasClassName('formulaire-annexes')) {
                                                          var linksAnnexe = $('formulairetype-annexes-box').select('a.selected')
                                                            if (linksAnnexe[0].select('input:checked').length) {
                                                                linksAnnexe[0].click();
                                                            }
                                                        }

                                                        var previousFormulaireFormBlock = previous_formulaire.up('.formulaire-block');
                                                        if (previousFormulaireFormBlock) {
                                                            previousFormulaireFormBlock.removeClassName('hidden');

                                                            var prevFormulaireCode = previous_formulaire.up('.formulaire-block').readAttribute('data-code');
                                                            $$('.formulaire-repetable').each(function(element) {
                                                                if (element.hasClassName(prevFormulaireCode)) {
                                                                    element.select('option').each(function(elt, index){
                                                                        if (index == prevForm.readAttribute('data-position')) {
                                                                            elt.selected = true;
                                                                        } else {
                                                                            elt.selected = false;
                                                                        }
                                                                    })
                                                                    element.show();
                                                                } else {
                                                                    element.hide();
                                                                }
                                                            })

                                                            var formulaireName = previousFormulaireFormBlock.down('.page-form table').readAttribute('class');
                                                            asserts.run(formulaireName);
                                                        }
                                                        this.form.select('.pagination-next').invoke('show');
                                                        this.form.select('.submit').invoke('hide');
                                                        this.form.select('.cancel').invoke('hide');

                                                        $$('.hide-on-last-page').invoke('show');
                                                        if (!this.pages[this.pages.indexOf(previous_formulaire) - 1]) {
                                                          this.form.select('.pagination-previous').invoke('hide');
                                                        }
                                                        this.processStepBox();
                                                      },

                                                      deleteOccurence: function(element) {
                                                          var selectOccurence = element.previous('.elt-select').select('select')[0];
                                                          var formCode = element.up('.formulaire-repetable').readAttribute('data-code');
                                                          var formBlock = $$('.formulaire-block.'+formCode);
                                                          if (!formBlock.length) {
                                                              formBlock = $$('.formulaire-visibility.'+formCode);
                                                          }
                                                          var formPages = formBlock[0].select('.page-repetable')
                                                          var formRemoved = false;
                                                          var positionUpdated = false;
                                                          var indexFormRemoved;
                                                          var pages = this.pages
                                                          var pageLabel;
                                                          formPages.each(function(elt) {
                                                              if (elt.readAttribute('data-position') == selectOccurence.getValue()) {
                                                                  if ($(elt).hasClassName('visible')) {
                                                                      pageLabel = $(elt).readAttribute('data-label')
                                                                  }
                                                                  elt.remove();
                                                                  formRemoved = true;
                                                                  indexFormRemoved = pages.indexOf(elt)
                                                              }
                                                          })
                                                          var optionRemoved = false;
                                                          selectOccurence.select('option').each(function(elt) {
                                                              if (elt.value == selectOccurence.getValue() && !optionRemoved) {
                                                                  elt.remove();
                                                                  optionRemoved = true;
                                                              }
                                                              // Removed 18/02/2019 - Voir si besoin dans le futur
                                                              if (optionRemoved) {
                                                                  elt.value = elt.value-1;
                                                              }
                                                          })

                                                          formPages = formBlock[0].select('.page-repetable')
                                                          formPages.each(function(elt, i) {
                                                              elt.writeAttribute('data-position', i)
                                                              if (i == selectOccurence.getValue()) {
                                                                  if ($(elt).readAttribute('data-label') == pageLabel) {
                                                                      elt.show();
                                                                      elt.addClassName('visible');
                                                                  }
                                                                  elt.addClassName('formulaire-page');
                                                                  pages[indexFormRemoved] = elt;
                                                              }
                                                              var rows = elt.select('.dynamic-row')
                                                              ntd.tableRowManager.rewriteTableRowsInputsName(null, null, rows);
                                                          })

                                                          this.pages = pages;
                                                          if (selectOccurence.select('option').length == 1) {
                                                              element.hide();
                                                          }
                                                      },

                                                      addOccurence: function(element) {
                                                          var selectOccurence = element.previous('.elt-select').select('select');
                                                          var selectOptions = selectOccurence[0].select('option');
                                                          var newOccurence = selectOptions.length;
                                                          var newOption = new Element('option', {value: newOccurence}).update('Occurence N° '+(newOccurence + 1))
                                                          selectOccurence[0].insert(newOption)
                                                          selectOptions.each(function(option) {
                                                              option.selected = false;
                                                          })
                                                          newOption.selected = true;

                                                          element.up('.formulaire-repetable').select('.btn-delete')[0].show();

                                                          var formCode = element.up('.formulaire-repetable').readAttribute('data-code');
                                                          var formBlock = $$('.formulaire-block.'+formCode);
                                                          if (!formBlock.length) {
                                                              formBlock = $$('.formulaire-visibility.'+formCode);
                                                          }
                                                          var formPages = formBlock[0].select('.page-repetable')
                                                          var currentElement
                                                          formPages.each(function(elt, i) {
                                                              elt.hide();
                                                              if ($(elt).hasClassName('visible')) {
                                                                  currentElement = elt
                                                                  elt.removeClassName('visible');
                                                              }
                                                              if ($(elt).readAttribute('data-position') == newOccurence-1) {
                                                                  var newForm = elt.clone(true);
                                                                  newForm.removeClassName('formulaire-page');
                                                                  newForm.select('select').each(function(elt) {
                                                                      if (elt[0]) {
                                                                          elt[0].selected  = true;
                                                                      }
                                                                  });
                                                                  newForm.select('input').each(function(elt) {
                                                                      if (elt.hasClassName('field-type-number')) {
                                                                          elt.value = '';
                                                                      } else {
                                                                          elt.value = '';
                                                                      }
                                                                  });
                                                                  newForm.setAttribute('data-position', newOccurence)
                                                                  if (currentElement && newForm.readAttribute('data-label') == currentElement.readAttribute('data-label')) {
                                                                    newForm.addClassName('visible');
                                                                    newForm.show();
                                                                  }
                                                                  formBlock[formBlock.length-1].insert({
                                                                      bottom: newForm
                                                                  })
                                                              }
                                                          })

                                                          formBlock[0].select('.page-repetable').each(function(page) {
                                                              var rows = page.select('.dynamic-row')
                                                              ntd.tableRowManager.rewriteTableRowsInputsName(null, null, rows);
                                                          })
                                                      },

                                                      processStepBox: function() {
                                                        var index = 0;
                                                        this.pages.detect(function(elt) {
                                                          index++;
                                                          var found = false;
                                                          var siblingVisible = elt.adjacent('.visible')

                                                            if (elt.hasClassName('visible')) {
                                                             found = true;
                                                            } else if (siblingVisible.length) {
                                                              if (siblingVisible[0].readAttribute('data-label') == elt.readAttribute('data-label')) {
                                                                  found = true;
                                                              }
                                                            }
                                                          return found;
                                                        });
                                                        $R(0, this.pages.size(), false).each(function(key) {
                                                          $('declaration-steps-box').removeClassName('current-step-' + key);
                                                        });
                                                        $('declaration-steps-box').addClassName('current-step-' + index);
                                                        $$('body').first().scrollTo();
                                                      }
                                                    });

ntd.declaration.pagination = {
  controller: null,
  init: function(pagesContainer, form) {
    ntd.declaration.pagination.controller = new ntd.declaration.PaginationController(pagesContainer, form);
  },
  previous: function() {
    ntd.declaration.pagination.controller.previous();
  },
  next: function() {
    ntd.declaration.pagination.controller.next();
  },
  deleteOccurence: function(element) {
    ntd.declaration.pagination.controller.deleteOccurence(element);
  },
  addOccurence: function(element) {
    ntd.declaration.pagination.controller.addOccurence(element);
  },
};

$(document).on('change', 'th.folding-action label input.field-type-checkbox', function(evt){
    ntd.tableExpandManager.toogleTab(evt.target);
});

$(document).on('click', '.autocomplete-container li', function(evt) {
    var value = evt.target.readAttribute('data-value');
    var autocompleteContainer = evt.target.up('.autocomplete-container');
    var input = autocompleteContainer.previous('input');
    input.value = value;
    autocompleteContainer.hide();
});

ntd.tableExpandManager = {
  toogleTab: function (element) {
    var tbodies = $(element).up('table').select('tbody');
    var tfoots = $(element).up('table').select('tfoot');
    var chevron_up = $(element).previous('i.fa-chevron-up');
    if (chevron_up.hasClassName('hidden')) {
        chevron_up.removeClassName('hidden');
    } else {
        chevron_up.addClassName('hidden');
    }
    var chevron_down  = $(element).previous('i.fa-chevron-down');
    if (chevron_down.hasClassName('hidden')) {
        chevron_down.removeClassName('hidden');
    } else {
        chevron_down.addClassName('hidden');
    }
    tbodies.each(function(tbody){
        if (tbody.hasClassName('hidden')) {
            tbody.removeClassName('hidden');
        } else {
            tbody.addClassName('hidden');
        }
    });
    tfoots.each(function(tfoot){
        if (tfoot.hasClassName('hidden')) {
            tfoot.removeClassName('hidden');
        } else {
            tfoot.addClassName('hidden');
        }
    });
  }
};

ntd.tableRowManager = {
  addTableRow: function(className, tagName, elt) {
    if (typeof tagName == "undefined") {
      tagName = 'tr';
    }

    var tr_template
    if (elt) {
        tr_template = elt.up('tr').previous('tr');
    } else {
        tr_template = $$(tagName + '.' + className).last();
    }

    var allLines = $$('.'+className);
    if (tr_template.readAttribute('data-max')) {
        if (tr_template.readAttribute('data-max') == allLines.length) {
            return false;
        }
    }
    var tr = tr_template.clone(true);
    tr_template.insert({after: tr});
    tr.select('input, select').each(function(input) {
      if (input.tagName == 'select') {
        input.selectedIndex = 0;
      } else if (input.type == 'checkbox') {
        input.checked = false;
      } else {
        input.value = '';
      }
      NTD.Generic.none(input);
    }, this);
    ntd.tableRowManager.rewriteTableRowsInputsName(className, tagName);
  },
  removeTableRow: function(tr, className, tagName) {
    Element.prototype.triggerEvent = function(eventName)
    {
      if (document.createEvent) {
        var evt = document.createEvent('HTMLEvents');
        evt.initEvent(eventName, true, true);

        return this.dispatchEvent(evt);
      }

      if (this.fireEvent)
        return this.fireEvent('on' + eventName);
    };

    if (typeof tagName == "undefined") {
      tagName = 'tr';
    }

    var trClasses = tr.classList;
    var previousTrClasses = tr.previous().classList;
    var nextTrClasses = tr.next().classList;

    if (trClasses.value != previousTrClasses.value && trClasses.value != nextTrClasses.value) {
      return false;
    }

    var line_to_update = tr.previous('tbody.'+tr.className);
    if (typeof line_to_update == 'undefined') {
      line_to_update = tr.next('tbody.'+tr.className);
    }

    tr.remove();
    if (typeof line_to_update != 'undefined') {
      line_to_update.select('input[type=text]').each(function(elt) {
        elt.triggerEvent('change');
      });
    }

    ntd.tableRowManager.rewriteTableRowsInputsName(className, tagName);
  },
  rewriteTableRowsInputsName: function(className, tagName, rows) {
    if (!rows) {
      rows = $$(tagName + '.' + className);
    }
    var index = 1;
    var lastPosition = 0;

    rows.each(function(row) {
      var formPage = row.up('.page-form')
      var occurence = formPage.readAttribute('data-position')
      if (!occurence) {
          occurence = 0;
      }
      if (occurence != lastPosition) {
        lastPosition = occurence;
        index = 1;
      }
      row.select('input, select').each(function(input) {
        input = $(input);
        var td = input.up('td');
        var fieldName = td.readAttribute('data-field');
        if (fieldName.indexOf('cvae') || fieldName.indexOf('is') || fieldName.indexOf('rcm')) {
          input.name = input.name.replace(new RegExp("^(.*)\\[" + fieldName + ".*\\]$", "g"), '$1[' + fieldName + '/' + index + '][' + occurence + ']');
          input.addClassName(input.name);
        }
        else {
          input.name = input.name.replace(new RegExp("^(.*)\\[" + fieldName + ".*\\]$", "g"), '$1[' + fieldName + index + '][' + occurence + ']');
        }
        if ((fieldName.indexOf('cvae') || fieldName.indexOf('is')) > 0) {
          input.id = input.id.replace(new RegExp("^(.*)_" + fieldName + ".*$", "g"), '$1_' + fieldName + '/' + index);
        } else {
          input.id = input.id.replace(new RegExp("(" + fieldName + "\/\\d{1})", "g"), fieldName + '/' + index);
        }
        var inputClass = input.id.replace(new RegExp("(" + fieldName + "\/\\d{1})", "g"), fieldName + '/' + index);
        input.addClassName(inputClass.replace('/', '-'));
      }, this);
      row.select('[data-ligne_number]').each(function(ligne_number_elt){
        ligne_number_elt.update(ligne_number_elt.readAttribute('data-ligne_number').replace('((row_index))', index));
      }, this);
      row.select('.elt-ssaamm-container').each(function(ssaamm_container_elt) {
        var td = ssaamm_container_elt.up('td');
        var fieldName = td.readAttribute('data-field');
        ssaamm_container_elt.id = ssaamm_container_elt.id.replace(new RegExp("^(.*)_" + fieldName + ".*$", "g"), '$1_' + fieldName + '/' + index + '-controls-container');
        ssaamm_container_elt.select('select').each(function(select_elt) {
            select_elt.setAttribute('onchange', select_elt.getAttribute('onchange').replace(new RegExp("(" + fieldName + "\/\\d{1})", "g"), fieldName + '/' + index));
        });
      });

      index++;
    }, this);

  }
};


function log(args) {
  console.log(args);
}
