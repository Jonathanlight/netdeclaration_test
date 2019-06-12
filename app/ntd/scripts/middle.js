if (!ntd) var ntd = {};

ntd.middle = {
  //currentAdherent: null,
  //adherent: null,
  //iban: null,
  //tarif: null,
  //declarer: null
  services: null
  //devis: null
};


ntd.middle.adherentForm = Class.create(ntd.Manager, {

  onCreate: function () {
    this.parent.observe('submit',
                        function (evt) {
                          evt.stop();
                          Kwo.exec(this.parent.readAttribute('action'),
                                   this.parent,
                                   {callback: this.onSubmitCallback.bind(this),
                                     disable: true});
                        }.bind(this));
    this.parent.getInputs('radio').invoke('observe', 'click', this.onFormChange.bind(this));

    this.onFormChange();
  },

  onSubmitCallback: function (resp) {
    resp = new kwo.Response(resp);

    if (resp.hasError()) {
      resp.alert();
      this.onFormChange();
      return;
    }

    // TODO :
    //Kwo.go("/account/ntd/bulletin.adhesion/-/id/" + resp.getAttribute('adherent_id'));
  },

  onFormChange: function () {
    var form = this.parent;
    var input;

    // -- type change ?
    /*input = this.parent.getInputs('radio', 'adherent[type]').detect(function (input) {
     return $(input).checked;
     });

     $(form['adherent[oga_agrement]']).disable().up('.elt').hide();
     $(form['adherent[cec_ordre]']).disable().up('.elt').hide();
     if (input) {
     input = $(input);
     var type = $F(input);
     if (type == this.TYPE_CEC) {
     $(form['adherent[cec_ordre]']).enable().up('.elt').show();
     form.down('.email-declaration-3nd-step').show();
     }
     else if (type == this.TYPE_OGA) {
     $(form['adherent[oga_agrement]']).enable().up('.elt').show();
     form.down('.email-declaration-3nd-step').show();
     }
     else if (type == this.TYPE_ENTREPRISE) {
     $(form['adherent[oga_agrement]']).enable().up('.elt').hide();
     form.down('.email-declaration-3nd-step').hide();
     }
     }*/


    // ADRESSE FACTURATION
    input = this.parent.getInputs('radio',
                                  'adherent[has_no_billing_address]')
      .detect(function (input) {
                return $(input).checked;
              });
    this.down('.billing-address-1st-step').hide();

    //this.down('.billing-address-2nd-step').hide();

    if (input && $F(input) == 0) {
      this.down('.billing-address-1st-step').show();
      if (input.up('.input-has-not-billing-address').hasClassName('main-account')) {
          this.down('.billing-address-2nd-step').show();
      }
    }

    input = this.parent.getInputs('radio',
                                  'adherent[is_main_adherent_billing_address]').detect(function (input) {
                                                                                         return $(input).checked;
                                                                                       });
      if (input.up('.billing-address-1st-step').previous().hasClassName('secondary-account')) {
          this.down('.billing-address-2nd-step').hide();
      }

      if (input && $F(input) == 0) {
      this.down('.billing-address-2nd-step').show();
    }


  }
});


ntd.middle.services = {
  onValidatePurchase: function (form) {
    form = $(form);
    Kwo.exec(form.readAttribute('action'),
             form,
             { callback: ntd.middle.services.onValidatePurchaseCallback.bindAsEventListener(this, form) });
  },
  onValidatePurchaseCallback: function (resp, form) {
    resp = new kwo.Response(resp);
    if (resp.hasError()) {
      resp.alert();
      return;
    }
    form.submit();
  }
};

ntd.middle.PaymentForm = Class.create(ntd.Manager, {
  form: null,
  onCreate: function () {
    this.form = this.down('form');
    this.form.observe('submit',
                      function (evt) {
                        evt.stop();
                        Kwo.exec(this.readData('facture-update-url'),
                                 this.form,
                                 { "callback": this.onFinalizeCallback.bind(this),
                                   "disable": this.form});
                      }.bind(this));
    this.down('.methods').observe('click',
                                  function (evt) {
                                    var elt = evt.findElement('input');
                                    if (!elt) {
                                      return;
                                    }

                                    this.select('.payment__label').invoke('removeClassName', 'selected');
                                    this.select('.payment__snippet').invoke('hide');
                                    elt.up('.payment__label').addClassName('selected');
                                    var id =elt.getValue();
                                    var snippet = $('payment__snippet--' + id);
                                    snippet.show();
                                  }.bind(this));
  },
  onFinalizeCallback: function (resp) {
    this.form.enable();
    resp = new kwo.Response(resp);
    if (resp.hasError()) {
      resp.alert();
      return;
    }
    Kwo.exec(this.form.readAttribute('action'),
             this.form,
             {"container": $("psp-container")});
  }
});


ntd.middle.suivi = {
  Home: Class.create(
    {
      parent: null,
      form: null,
      resultsContainer: null,
      throbber: null,
      offsetElt: null,
      limitElt: null,

      initialize: function (parent) {
        this.parent = $(parent);
        this.form = this.parent.down('form');
        this.form.observe('submit', this.onSubmit.bind(this));
        this.resultsContainer = $(this.form.readAttribute('data-results_container'));
        this.throbber = this.form.down('.throbber');
        this.searchIcon = this.throbber.previous();
        this.offsetElt = this.form.down('[name="form[offset]"]');
        this.limitElt = this.form.down('[name="form[limit]"]');
        this.parent.observe('click',
                            function (evt) {
                              var elt = evt.findElement('[data-offset]');
                              if (elt) {
                                evt.stop();
                                this.offset(elt.readAttribute('data-offset'));
                                this.submit();
                                return;
                              }
                              elt = evt.findElement('[target]');
                              if (elt) {
                                evt.stop();
                                if (elt.hasAttribute('data-dialog') && elt.getAttribute('data-dialog') == "tabs") {
                                  new ntd.SuiviTabsDialog(function() {
                                    Kwo.exec(elt.readAttribute('href'), this.args, {"async": true, "container": this.support, "callback": this.onContentLoaded.bindAsEventListener(this) });
                                  }, null, {width: 600, height: 640});
                                }
                                else {
                                  new Kwo.Dialog(elt.readAttribute('href'), null, {width: 600, height: 520});
                                }
                                return;
                              }
                              elt = evt.findElement('[data-method]');
                              if (elt && elt.readAttribute('data-method') == 'export') {
                                evt.stop();
                                this.exportCsv();
                                return;
                              }
                            }.bind(this));
        this.form.observe('change', this.onFormChange.bind(this));
        this.resultsContainer.observe('change', this.onResultsContainerChange.bind(this));
        this.form.select('.elt-date input').each(function (elt) {
          elt.writeAttribute('onchange', "$(document).fire('ntd:input.change')");
        });
        $(document).observe('ntd:input.change', this.onFormChange.bind(this));
        this.submit();
      },
      onSubmit: function (evt) {
        evt.stop();
        this.submit();
      },
      onFormChange: function (evt) {
        evt.stop();
        this.offset(0);
        this.submit();
      },
      onResultsContainerChange: function (evt) {
        evt.stop();
        var elt = evt.findElement('select[name="form_limit"]');
        if (elt) {
          this.limitElt.setValue(elt.getValue());
        }
        this.offset(0);
        this.submit();
      },
      submit: function () {
        if (this.throbber.visible()) return;
        this.throbber.show();
        this.searchIcon.hide();
        Kwo.exec(this.form.readAttribute('action'),
                 this.form,
                 {container: this.resultsContainer,
                   callback: function () {
                     this.throbber.hide();
                     this.searchIcon.show();
                   }.bind(this)});
      },
      exportCsv: function () {
        Kwo.go(this.form.readAttribute('data-action_csv'),
               this.form,
               { target: 'blank'});
      },
      offset: function (offset) {
        if (offset !== undefined) {
          this.offsetElt.setValue(offset);
        }
        return $F(this.offsetElt);
      }
    })
};

ntd.SuiviTabsDialog = Class.create(Kwo.Dialog, {
  onContentLoaded: function() {
    this.support.down('#select-local').observe('change', this.onLocauxChange.bindAsEventListener(this));
    new ntd.middle.tabs(this.support);
  },

  onLocauxChange: function(evt) {
    var elt = evt.element();
    var id = $F(elt);
    this.support.select('[data-row]').invoke("hide");
    this.support.down('[data-row="'+id+'"]').show();
  }
});


ntd.middle.IbanForm = Class.create(ntd.Manager, {

  id: null,

  onCreate: function () {
    this.id = this.readData('id');
    this.parent.observe('submit',
                        function (evt) {
                          evt.stop();
                          this.submit();
                        }.bind(this));
    this.parent.observe('click',
                        function (evt) {
                          if (evt.findElement('[data-method="destroy"]')) {
                            evt.stop();
                            this.destroy();
                          }
                        }.bind(this));
  },
  submit: function () {
    Kwo.exec(this.parent.readAttribute('action'), this.parent, {callback: this.callback.bind(this), disable: true});
  },
  destroy: function () {
    if (!confirm('êtes-vous sûr de vouloir supprimer ce compte IBAN ?')) {
      return;
    }
    Kwo.exec(this.readData('action-delete'), {id: this.id}, {callback: this.callback.bind(this)});
  },
  callback: function (resp) {
    resp = new kwo.Response(resp);
    if (resp.hasError()) {
      resp.alert();
      return;
    }
    resp.alert();
    Kwo.reload();
  }
});


ntd.middle.AdherentSelector = Class.create(ntd.Manager, {
  form: null,
  button: null,
  onCreate: function () {
    this.form = this.down('.block--adherent-selector__form');
    if (this.form.down('select')) {
      this.form.down('select').observe('change', function (evt) {
        this.submit();
      }.bind(this));
    }
  },
  submit: function () {
    Kwo.exec(this.form.readAttribute('action'),
             this.form,
             { callback: function (resp) {
               resp = new kwo.Response(resp);
               if (resp.hasError()) {
                 return resp.alert();
               }
               Kwo.go('/middle');
             }});
  }
});


ntd.middle.declarations = {
  duplicateDeclaration: function(elt) {
    elt = $(elt);
    if (!confirm(elt.readAttribute('data-confirm'))) {
      return false;
    }
    Kwo.exec(elt.readAttribute('data-url'),
              null,
              {callback: function(resp){
                resp = new kwo.Response(resp);
                if (resp.hasError()) {
                  return resp.alert();
                } else {
                  var declarationId = resp.getResult().declaration_id;
                  Kwo.go('/account/ntd/account.declaration.edit/-/declaration_id/'+declarationId)
                }
              }})
  },
  deleteDeclaration: function (elt) {
    elt = $(elt);
    if (!confirm(elt.readAttribute('data-confirm'))) {
      return false;
    }
    Kwo.exec(elt.readAttribute('data-url'),
             null,
             {callback: function (resp) {
               resp = new kwo.Response(resp);
               if (resp.hasError()) {
                 return resp.alert();
               }
               resp.alert();
               Kwo.reload();
             }});
  },
  validateDeclaration: function (form) {
    form = $(form);
    Kwo.exec(form.readAttribute('action'),
             form,
             {callback: function (resp) {
               resp = new kwo.Response(resp);
               if (resp.hasError()) {
                 resp.alert();
                 return;
               }
               resp.alert();
               Kwo.go('/middle/declarations');
             }});
    return false;
  },

  toggleOgaDetails: function (checkbox) {
    var oga_details = checkbox.up('.elt').next('.oga-details');
    if (checkbox.checked) {
      oga_details.select('#input-idoga, select').invoke('enable');
      oga_details.show();
    }
    else {
      oga_details.select('#input-idoga, select').invoke('disable');
      oga_details.hide();
    }
  },

  toggleCECDetails: function (checkbox) {
    var cec_details = checkbox.up('.elt').next('.cec-details');
    if (checkbox.checked) {
      cec_details.select('input, select').invoke('enable');
      cec_details.show();
    }
    else {
      cec_details.select('input, select').invoke('disable');
      cec_details.hide();
    }
  },

  onSelectOGAChange: function (elt) {
    elt.up('form').down('#input-siretoga').setValue($F(elt));
  }
};


ntd.middle.tabs = Class.create(ntd.Manager, {

  onCreate: function () {
    var that = this;
    this.select('[data-tab-nav] a').each(function (e) {
      e.observe('click', that.onNavigate.bindAsEventListener(that, e));
    });
  },

  onNavigate: function (evt, elt) {
    evt.stop();
    this.select('[data-tab-nav] a').each(function (e) {
      if (e != elt) e.removeClassName('active');
    });
    elt.addClassName('active');
    var targetDiv = elt.readAttribute('href').substring(1);
    this.select('[data-tabs] .selected').each(function (e) {
      if (e != $(targetDiv)) e.removeClassName('selected');
    });
    $(targetDiv).addClassName('selected');
  }
});

ntd.middle.devis = Class.create(ntd.Manager, {

  typeAdherentSelect: null,
  levelAdherentSelect: null,
  services: null,


  onCreate: function() {
    this.typeAdherentSelect = this.down('select[name="form[adherent_type]"]');
    this.levelAdherentSelect = this.down('select[name="form[adherent_level]"]');
    this.servicesContainer = this.down('.container-services');
    this.typeAdherentSelect.observe('change', this.onAdherentTypeChange.bindAsEventListener(this));
    this.levelAdherentSelect.observe('change', this.onAdherentTypeChange.bindAsEventListener(this));
  },

  onAdherentTypeChange: function(evt) {
    this.servicesContainer.update();
    var typeAdherent = $F(this.typeAdherentSelect);
    if (typeAdherent < 1) {
      return false;
    }
    Kwo.exec('/middle/core/devis.services',
             { adherent_type: typeAdherent,
               adherent_level: $F(this.levelAdherentSelect)},
             {container: this.servicesContainer,
             callback: function(){
               ntd.execDataOnLoad();
             }});
  }
});

ntd.middle.greffe = Class.create(ntd.Manager, {
  compte_type: null,
  forme_juridique : null,

  onCreate: function() {
    var that = this;
    this.compte_type = this.down("[name='greffe[compte_type]']");
    this.forme_juridique = this.down("[name='greffe[forme_juridique]']");

    this.form = this.down('form');
    this.form.observe('submit', this.submit.bindAsEventListener(this));

    this.select('[data-compte], [data-forme]').each(function (e) {
      that.compte_type.observe('change', that.toggleFields.bindAsEventListener(that, e));
      that.forme_juridique.observe('change', that.toggleFields.bindAsEventListener(that, e));
      that.toggleFields(null, e);
    });

    this.compte_type.observe('change', this.updateDocumentList.bindAsEventListener(this));
    this.forme_juridique.observe('change', this.updateDocumentList.bindAsEventListener(this));
    this.select("[name='greffe[is_gerant]'], [name='greffe[mode_direction]'], [name='greffe[is_public]']").each(function(elt, i) {
      $(elt).observe('change', that.updateDocumentList.bindAsEventListener(that));
    });
    this.updateDocumentList(null);
  },

  disableFields: function(elt) {
    $(elt).hide();
    $(elt).select("input, textarea, select").each(function (e) {
      $(e).disable();
    });
  },

  enableFields: function(elt) {
    $(elt).show();
    $(elt).select("input, textarea, select").each(function (e) {
      $(e).enable();
    });
  },

  toggleFields: function(evt, elt) {
    elt = $(elt);
    var compte_value = elt.hasAttribute("data-compte") ? elt.getAttribute("data-compte") : 0;
    var formes_values = elt.hasAttribute("data-formes") ? elt.getAttribute("data-formes").split(",") : [];

    if (compte_value == this.compte_type.value && formes_values.indexOf(this.forme_juridique.value) > -1) {
      this.enableFields(elt);
    }
    else {
      this.disableFields(elt);
    }
  },

  updateDocumentList: function(evt) {
    var args = {};
    var opts = {};

    args["type_compte"] = $F(this.compte_type);
    args["forme_juridique"] = $F(this.forme_juridique);
    args["is_gerant"] = $F(this.down("[name='greffe[is_gerant]']:checked"));
    args["mode_direction"] = $F(this.down("[name='greffe[mode_direction]']:checked"));
    args["is_public"] = $F(this.down("[name='greffe[is_public]']:checked"));

    opts["container"] = this.down("#document-list");

    Kwo.exec("/middle/greffe.documents", args, opts);
  },

  submit: function (evt) {
    evt.stop();
    Kwo.exec(this.form.readAttribute('action'), this.form, {"callback": this.onSubmitCallback.bindAsEventListener(this)});
  },

  onSubmitCallback: function(resp) {
    resp = new kwo.Response(resp);
    if (resp.hasError()) {
      return resp.alert();
    }
    var that = this;
    this.form.select(".form-field-failure").invoke("removeClassName", "form-field-failure");
    if (resp.getAttribute("errors")) {
      resp.getAttribute("errors").each(function(field, i) {
        if (that.form.down("[name='"+field+"']")) {
          that.form.down("[name='"+field+"']").up(".elt").addClassName("form-field-failure");
          if (i == 0)
            that.form.down("[name='"+field+"']").up(".elt").scrollTo();
        }
      });
      return;
    }
    var id = resp.getAttribute("id");
    Kwo.go("/middle/greffe.edit.documents/-/id/" + id);
  }
});

ntd.middle.greffecommune = Class.create(ntd.Manager, {
  zipcode : null,
  code_insee : null,

  onCreate: function() {
    var that = this;
    this.zipcode = this.down("[name='adherent[zipcode]']");
    this.code_insee = this.down("[name='adherent[greffecommune_id]']");

    this.zipcode.observe('change', that.updateCodeInseeList.bindAsEventListener(that));
  },

  updateCodeInseeList: function() {
    var args = {"zipcode": $F(this.zipcode)};
    if ($(this.parent).readAttribute("data-greffe-commune-all") == 1) {
      args["all"] = 1;
    }
    Kwo.exec("/middle/greffe.insee", args, {"callback": this.updateCodeInseeListCallback.bind(this)});
  },

  updateCodeInseeListCallback: function(res) {
    resp = new kwo.Response(res);
    if (resp.hasError()) {
     return resp.alert();
    }
    var that = this;
    this.code_insee.options.length = 0;
    if (!$F(this.zipcode).empty()) {
      var i = 0;
      $H(resp.getAttribute("codes")).each(function(e) {
        if (typeof e[1] !== 'function') {
          that.code_insee.options[i++] = new Option(e[1], e[0]);
        }
      });
    }
  }
});

ntd.middle.greffeDocument = Class.create(ntd.Manager, {

  onCreate: function() {
    var that = this;

    this.select("[name='link_liasse_declaration']").each(function(elt, i) {
      $(elt).observe("change", that.onLinkLiasseDeclarationChange.bindAsEventListener(that, $(elt).getValue()));
    });

    if (this.down("[name='link_liasse_declaration']:checked")) {
      var selected = $(this.down("[name='link_liasse_declaration']:checked"));
      this.onLinkLiasseDeclarationChange(null, selected.getValue());
    }

    if (this.down("[data-document]")) {
      var documents = this.select("[data-document]");
      documents.each(function(document) {
        document.observe("click", that.onRemoveDocument.bindAsEventListener(that, document));
      });
    }
  },

  onLinkLiasseDeclarationChange: function(evt, value) {
    var toggle = value != 1;
    this.down("[data-link-liasse-declaration]").toggle(toggle);
  },

  onRemoveDocument: function(evt, elt) {
    evt.stop();
    if (confirm("êtes-vous sûr de vouloir SUPPRIMER ce document ?")) {
      var id = $F(this.down("[name='id']"));
      var document_type = elt.readAttribute("data-document");

      var args = {"id": id, "document_type": document_type};
      Kwo.exec("/middle/greffe.edit.documents.delete", args, {"callback": this.onAfterRemoveDocument.bind(this)});
    }
  },

  onAfterRemoveDocument: function(resp) {
    resp = new kwo.Response(resp);
    if (resp.hasError()) {
      resp.alert();
      return;
    }

    Kwo.reload();
  }
});

ntd.middle.greffeFilters = Class.create(ntd.Manager, {
  onCreate: function() {
    this.form = this.down('form');
    this.resultsContainer = $(this.form.readAttribute('data-results_container'));
    this.throbber = this.form.down('.throbber');
    this.searchIcon = this.throbber.previous();
    this.offsetElt = this.form.down('[name="search[offset]"]');

    this.form.observe('submit', this.onSubmit.bind(this));
    this.form.observe('change', this.onFormChange.bind(this));
    this.resultsContainer.observe('change', this.onResultsContainerChange.bind(this));

    this.submit();
  },

  onSubmit: function (evt) {
    evt.stop();
    this.submit();
  },

  onFormChange: function (evt) {
    evt.stop();
    this.offset(0);
    this.submit();
  },

  onResultsContainerChange: function (evt) {
    evt.stop();
    this.offset(0);
    this.submit();
  },

  submit: function () {
    if (this.throbber.visible()) return;
    this.throbber.show();
    this.searchIcon.hide();
    Kwo.exec(this.form.readAttribute('action'), this.form, {
      container: this.resultsContainer,
      callback: function () {
        this.throbber.hide();
        this.searchIcon.show();
        this.bindOnOffsetClick();
      }.bind(this)
    });
  },

  offset: function (offset) {
    if (offset !== undefined) {
      this.offsetElt.setValue(offset);
    }
    return $F(this.offsetElt);
  },

  bindOnOffsetClick: function() {
    var that = this;
    this.resultsContainer.select('[data-offset]').each(function(elt, i) {
      $(elt).observe('click', that.onOffsetClick.bindAsEventListener(that));
    });
  },

  onOffsetClick: function(evt) {
    if (!evt) return;
    var elt = evt.findElement('[data-offset]');
    if (elt) {
      evt.stop();
      this.offset(elt.readAttribute('data-offset'));
      this.submit();
      return;
    }
  }
});

ntd.middle.greffeDossierDialog = Class.create(ntd.Manager, {
  onCreate: function() {
    this.down("a").observe("click", this.onOpen.bindAsEventListener(this));
  },

  onOpen: function(evt) {
    evt.stop();
    var that = this;
    var elt = $(evt.target);
    new Kwo.Dialog(function() {
      Kwo.exec(elt.readAttribute('href'), null, {"async": true, "container": this.support, "callback": that.onAfterPaint.bind(this) });
    }, null, {width: 600, height: 400});
  },

  onAfterPaint: function() {
    new ntd.middle.greffeDossier(this.support.down("[data-container]"));
  }
});

ntd.middle.greffeDossier = Class.create(ntd.Manager, {
  onCreate: function() {
    var that = this;

    this.form = this.down('form');
    this.form.observe('submit', this.submit.bindAsEventListener(this));
  },

  submit: function (evt) {
    evt.stop();
    Kwo.exec(this.form.readAttribute('action'), this.form, {"callback": this.onSubmitCallback.bindAsEventListener(this)});
  },

  onSubmitCallback: function(resp) {
    resp = new kwo.Response(resp);
    if (resp.hasError()) {
      return resp.alert();
    }

    Kwo.reload();
  }
});

ntd.middle.greffeEligibilityDialog = Class.create(ntd.Manager, {
  onCreate: function() {
    this.down("a").observe("click", this.onOpen.bindAsEventListener(this));
  },

  onOpen: function(evt) {
    evt.stop();
    var that = this;
    var elt = $(evt.target);
    new Kwo.Dialog(function() {
      Kwo.exec(elt.readAttribute('href'), null, {"async": true, "container": this.support, "callback": that.onAfterPaint.bind(this) });
    }, null, {width: 600, height: 300});
  },

  onAfterPaint: function() {
    new ntd.middle.greffeEligibility(this.support.down("[data-on-load]"));
    new ntd.middle.greffecommune(this.support.down("[data-on-load]").down("[data-on-load]"));
  }
});

ntd.middle.greffeEligibility = Class.create(ntd.Manager, {
  form: null,

  onCreate: function() {
    var that = this;

    this.form = this.down('form');
    this.form.observe('submit', this.submit.bindAsEventListener(this));
  },

  submit: function (evt) {
    evt.stop();
    Kwo.exec(this.form.readAttribute('action'), this.form, {"callback": this.onSubmitCallback.bindAsEventListener(this)});
  },

  onSubmitCallback: function(resp) {
    resp = new kwo.Response(resp);
    if (resp.hasError()) {
      return resp.alert();
    }
    var that = this;

    this.down("[data-is-eligible]").hide();
    this.down("[data-not-eligible]").hide();

    if (resp.getAttribute("eligible")) {
      this.down("[data-is-eligible]").show();
    }
    else {
      this.down("[data-not-eligible]").show();
    }
  }
});
