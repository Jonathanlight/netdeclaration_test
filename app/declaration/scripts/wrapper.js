var declaration = {};

declaration.Elt = Class.create({

  parent: null,
  initialize: function (elt, opts) {
    var that = this;
    this.parent = $(elt);

    /*Event.observe(window, "resize", function() {
     that.onWindowResize();
     });*/
    this.onCreate(opts);

    /*if (document.readyState == "complete") {
     this.onPaint();
     }
     else {
     Event.observe(window, "load", function(evt) {
     that.onWindowLoaded();
     });
     }*/
  },

  down: function (expr) {
    return this.parent.down(expr);
  },
  select: function (expr) {
    return this.parent.select(expr);
  },
  log: function (args) {
    //console.log(args);
  },

  readData: function (key, _default) {
    return this.hasData(key) ? this.parent.readAttribute("data-".concat(key)) : _default;
  },
  hasData: function (key) {
    return this.parent.readAttribute("data-".concat(key)) ? true : false;
  },
  writeData: function (key, value) {
    this.parent.writeAttribute("data-".concat(key), value);
  },

  onWindowLoaded: function() {
    this.onPaint();
  },
  onWindowResize: function() {
    this.onPaint();
  },
  onCreate: function(opts) {
  },
  onPaint: function() {
  }

});

declaration.Wrapper = Class.create(declaration.Elt, {

  pagination: null,
  homePage: null,
  imprimes: null,
  repetables: null,

  return_link: null,

  onCreate: function() {
    this.parent = $(document.body).down('.wrapper');
    this.return_link = this.readData('return_link');
    this.imprimes = $H({});
    this.repetables = $H({});

    this.select('[data-btn="leave"]').invoke('observe', 'click', this.onLeaveBtnClick.bind(this));
    this.select('[data-btn="print"]').invoke('observe', 'click', this.print.bind(this));
    this.select('[data-btn="download"]').invoke('observe', 'click', this.download.bind(this));
    this.select('[data-btn="duplicate"]').invoke('observe', 'click', this.duplicateDeclaration.bind(this));
    this.onBind();
  },
  onBind: function() {
    var that = this;
    Event.observe(document, 'keydown', function(evt) {
      if (evt.ctrlKey && evt.keyCode == 80) {
        that.print();
        return false;
      }
    });
  },
  start: function() {
    if (this.down('.imprime-page.home')) {
      this.homePage = new declaration.HomePage(this.down('.imprime-page.home'));
    }

    this.select('form.imprime-box').each(function(elt) {
      this.addImprime(elt);
    }, this);

    this.select('.formulaire-repetable').each(function(elt) {
      this.repetables.set(elt.readAttribute('data-code'), new declaration.FormRepetable(elt));
    }, this);
    this.initPagination.bind(this).defer();
  },
  initPagination: function() {
    this.pagination = new declaration.Pagination(this.down('.wrapper-content'));
    this.pagination.goto(0);
  },

  addImprime: function(imprimeElt) {
    var imprime = new declaration.Imprime(imprimeElt, this);
    if (!this.imprimes.get(imprime.code)) {
      this.imprimes.set(imprime.code, $H({}));
    }
    this.imprimes.get(imprime.code).set(imprime.index, imprime);
    return imprime;
  },
  removeImprime: function(imprime, index) {
    index = index === undefined ? 0 : index;
    var code = imprime;
    if (imprime instanceof declaration.Imprime) {
      code = imprime.code;
    }
    this.imprimes.get(code).unset(index);
  },
  getImprime: function(code, index) {
    index = index === undefined ? 0 : index;
    return this.imprimes.get(code).get(index);
  },
  hasImprime: function(code) {
    return this.imprimes.get(code);
  },
  getField: function(code, index, imprime_index) {
    imprime_index = imprime_index === undefined ? 0 : imprime_index;
    var parts = code.split('_');
    var imprime_code = parts[0];
    var field_code = parts[1];

    var imprime = this.getImprime(imprime_code, imprime_index);
    if (!imprime) {
      $D().log('imprime [' + imprime_code + '] does not exists');
    }
    var field = imprime.getField(field_code, index);
    if (!field) {
      $D().log('field [' + field_code + ', ' + index + ',' + imprime_code + '] does not exists [WRAPPER]');
    }
    return field;
  },
  getFieldCodeCount: function(code) {
    var parts = code.split('_');
    var imprime_code = parts[0];
    var field_code = parts[1];

    var imprime = this.getImprime(imprime_code);
    if (!imprime) {
      $D().log('imprime [' + imprime_code + '] does not exists');
    }
    var count = 0;
    imprime.getFields().keys().each(function(key) {
      if (key.startsWith(field_code)) {
        count++;
      }
    }, this);
    return count;
  },
  getRepetable: function(imprime_code) {
    return this.repetables.get(imprime_code);
  },
  onLeaveBtnClick: function(evt) {
    evt.stop();
    var elt = evt.findElement();

    Kwo.exec('/account/declaration/declaration.validate',
             { declaration_id:this.readData('declaration_id')},
             { callback: function(resp) {
               resp = new kwo.Response(resp);
               var message = elt.readAttribute('data-confirm');
               if (resp.hasError()) {
                 message = resp.getError("\n") + "\n" + message;
               }
               if (confirm(message)) {
                 Kwo.go(this.return_link);
               }
             }.bind(this)});
  },
  duplicateDeclaration: function() {
    var msg = "Êtes-vous sur de vouloir modifier votre déclaration ?\n" +
            "La déclaration sera dupliquée et accessible dans le menu 'Accès formulaires déclaratifs'";
    if (!confirm(msg)) {
      return false;
    }
    Kwo.exec('/account/ntd/account.declaration.duplicate',
             { declaration_id: this.readData('declaration_id')},
             { callback: function(resp) {
               resp = new kwo.Response(resp);
               if (resp.hasError()) {
                 resp.alert();
                 return;
               }
               var declaration_id = resp.getAttribute('declaration_id');
               alert('La déclaration a été dupliquée : N°' + declaration_id);
               Kwo.go('/account/declaration/wrapper', { declaration_id: declaration_id});
             }});
  },
  log: function(args) {
    //console.info(args);
  },
  download: function(evt) {
    var elt = evt.findElement('[data-btn="download"]');
    var key = elt.readAttribute('data-key');
    Kwo.go('/declaration.pdf', {key:key}, {target:'blank'});
  },
  print: function() {
    var that = this;
    if (that.hasImprime('F-IDENTIF')) {
      var imprime = that.getImprime('F-IDENTIF');
      if (imprime.getField('CA') && imprime.getField('CB')) {
        var dates = 'Début : ' + imprime.getField('CA').getValue() + ' - Fin : ' + imprime.getField('CB').getValue();
        that.down('.print-footer').down('.exercice-dates').update(dates);
      }
    }
    this.imprimes.each(function(imprime) {
      var controller = that.pagination.getImprimeController(imprime[0]);
      if (controller.index > 0) {
        controller.getImprimes().each(function(imp) {
          imp.prepareHeader();
        })
      }
      else {
        if (controller.isRequired == 1 || controller.parent.readAttribute('data-state') == 'saved') {
          controller.parent.removeClassName('hidden');
        }
        else {
          controller.parent.addClassName('hidden');
        }
        controller.prepareHeader();
      }
    });
    window.print();
  }
});

declaration.Wrapper._instance = null;
declaration.Wrapper.getInstance = function(singleton) {
  if (declaration.Wrapper._instance === null) {
    declaration.Wrapper._instance = new declaration.Wrapper();
    declaration.Wrapper._instance.start();
  }
  return singleton ? declaration.Wrapper._instance[singleton] : declaration.Wrapper._instance;
};
var $D = declaration.Wrapper.getInstance;


declaration.Imprime = Class.create(declaration.Elt, {

  wrapper: null,
  infoBox: null,

  code: null,
  index: null,
  fields: null,
  operations: null,
  managers: null,

  isPrepare: null,
  prepareData: null,
  ifieldsMetas: null,
  isRequired: null,

  onCreate: function(wrapper) {
    this.wrapper = wrapper;
    this.code = this.readData('code');
    this.index = this.readData('index', 0);
    this.isRequired = this.readData('required', 0);
    this.fields = $H({});
    this.managers = $H({});
    this.operations = [];
    this.isPrepare = false;
    this.prepareData = {};
    this.ifieldsMetas = $H({});
  },

  getState: function() {
    return this.readData('state');
  },

  getFields: function() {
    return this.fields;
  },
  getField: function(code, index) {

    if (code.startsWith(this.code)) {
      code = code.substr((this.code + '_').length);
    }
    if (code.include('_')) {
      return this.wrapper.getField(code, index);
    }

    index = index === undefined ? 0 : index;
    if (this.ifieldsMetas.get(code) && this.ifieldsMetas.get(code)['extensible'] == 0) {
      index = 0;
    }
    var key = code + '#' + index;
    var field = this.fields.get(key);
    if (!field) {
      $D().log('field [' + code + ', ' + index + ',' + this.code + '] does not exists [IMPRIME]');
    }
    return field;
  },
  addField: function(elt) {
    var field = null;
    if (elt instanceof declaration.Field) {
      field = elt;
    }
    else {
      field = declaration.Field.getInstance(elt, this);
    }

    var key = field.code + '#' + field.index;
    this.fields.set(key, field);
    if (field instanceof declaration.Field.Typecci && field.hasData('depose_neant')) {
      $(document).observe(declaration.Field.EVENT.CHANGE + "_" + field.getFullCode() + "_" + field.imprime.index,
                          function(evt) {
                            this.checkDeposeNeantField(field);
                          }.bind(this));
      this.checkDeposeNeantField(field);
    }
    return field;
  },
  checkDeposeNeantField: function(field) {
    if (field.input.checked) {
      this.getFields().values().each(function(ifield) {
        if (ifield != field) ifield.disable();
      });
    }
    else {
      this.getFields().values().each(function(ifield) {
        if (ifield != field) ifield.enable();
      });
    }
  },
  removeField: function(field, index) {
    index = index === undefined ? 0 : index;
    var code = field;
    if (field instanceof declaration.Field) {
      code = field.code;
    }
    var key = code + '#' + index;
    this.fields.unset(key);
  },
  getFieldCodeCount: function(code) {
    if (code.startsWith(this.code)) {
      code = code.substr((this.code + '_').length);
      var count = 0;
      this.getFields().keys().each(function(key) {
          var keySplitted = key.split('#')
          if (keySplitted.length > 1 && keySplitted[0] == code) {
            count++;
          }
      }, this);
      return count;
    }
    else {
      return this.wrapper.getFieldCodeCount(code);
    }
  },
  onChange: function() {
    if (this.statePrepare != 'finish') return;
    this.setState('changed');
    this.select('input[type="submit"]').invoke('removeClassName', 'hidden');
    $D().pagination.refreshImprimeState();

    if (this.code == 'P-IDENTIF') {
      var fieldHA = this.getField('HA');
      if (fieldHA) {
        if (fieldHA.getValue() > 0) {
          fieldHA.parent.up('.formulaire-page').removeClassName('force-hidden');
        }
        else {
          // fieldHA.parent.up('.formulaire-page').addClassName('force-hidden').previous();

        }
      }
      this.parent.select('select.select.type-fii').each(function(elt) {
        if (!elt.getValue()) {
          elt.addClassName('no-print');
        }
        elt.observe('change', function(evt) {
          if (evt.target.getValue()) {
            elt.removeClassName('no-print');
          }
          else {
            elt.addClassName('no-print');
          }
        });
      });
    }
  },

  prepareHeader: function() {
    var pages = this.select('.formulaire-page');
    if (!$D().pagination.stepBox && pages.size() > 1) {
      var imprimeTitle = this.down('.ftype-title');
      var imprimeHeader = this.down('.formulaire-header');
      var index = 1;

      pages.each(function(elt) {
        var pageLabel = elt.readAttribute('data-page_label') ? elt.readAttribute('data-page_label') : 'Page N°' + (index++);

        this.select('.formulaire-page-buttons').each(function(formulaire_page_button) {
          if (formulaire_page_button.select('a').size() < index - 1) {
            var button = new Element('a', {className:'ntd-button white'}).writeAttribute('data-page', index - 1)
                                                                         .update(pageLabel);

            formulaire_page_button.insert(button);

            button.observe('click', function() {
              pages.invoke('hide');
              elt.show();
              this.select('.formulaire-page-buttons a').invoke('removeClassName', 'selected');
              this.select('.formulaire-page-buttons a[data-page="' + button.getAttribute('data-page') + '"]').invoke('addClassName', 'selected');
            }.bind(this));
          }
        }.bind(this));

        var pageHeader = imprimeHeader.clone(true);
        pageHeader.down('.ftype-title').addClassName('page-title').update(imprimeTitle.innerHTML + ' - page N°' + (index - 1));
        elt.insert({top: pageHeader});
      }, this);

      pages.invoke('hide');
      this.down('.formulaire-page').show();
      this.select('.formulaire-page-buttons').each(function(formulaire_page_button) {
        formulaire_page_button.show();
        formulaire_page_button.down('a').addClassName('selected');
      }.bind(this));

      imprimeHeader.addClassName('no-print')
    }
  },

  prepare: function() {
    if (this.isPrepare) {
      return;
    }
    this.setState(this.readData('state'));

    this.parent.observe('submit', function(evt) {
      evt.stop();
      this.store();
    }.bind(this));

    this.select('[data-btn="formulaire.validate"]').invoke('observe', 'click', function(evt) {
      evt.stop();
      this.validate();
    }.bind(this));

    this.select('[data-btn="print-formulaire"]').invoke('observe', 'click', function(evt) {
      evt.stop();
      this.print();
    }.bind(this));

    this.select('[data-btn="download-formulaire"]').invoke('observe', 'click', function(evt) {
      evt.stop();
      this.download();
    }.bind(this));

    // page reset
    this.select('[data-btn="page-reset"]').each(function(elt) {
      var form = elt.up("form");
      if (form && form.getAttribute('data-required') == 1) {
        elt.hide();
      }
    });

    this.down('[data-btn="page-reset"]').observe('click', function(evt) {
      evt.stop();

      var elt = $(evt.target);
      var _doReset = function() {
        if (elt.hasAttribute('data-confirm-success')) {
          var form = elt.up('form');
          var imprime_code = form.getAttribute('data-code');
          var index = form.getAttribute('data-index');
          var declaration_id = $F(form.down('[name="declaration_id"]'));
          var formulairetype_id = $F(form.down('[name="formulairetype_id"]'));

          this.removeImprime(imprime_code, index, declaration_id, formulairetype_id);
        }
      }.bind(this);

      if (elt.hasAttribute('data-confirm')) {
        if (confirm(elt.getAttribute('data-confirm'))) {
          _doReset();
        }
      }

    }.bind(this));

    this.parent.observe('change', function(evt) {
      evt.stop();
      this.onChange();
    }.bind(this));
    this.select('input[type="submit"]').invoke('addClassName', 'hidden');

    this.prepareHeader();

    this.isPrepare = true;
    this.statePrepare = 'init';
    this.parent.addClassName('status-preparation');
    this.infoBox = new Element('div', {className: 'load-infos'}).update('<div class="background">&nbsp;</div><div class="content">&nbsp;</div>');
    this.parent.insert({top: this.infoBox});
    this.select('.ifields-box li').each(function(ifield) {
      this.ifieldsMetas.set(ifield.readAttribute('data-code'), {extensible : ifield.readAttribute('data-extensible')});
    }, this);

    this.prepareData['fields'] = this.select('.imprime-field[data-name]');
    this.prepareData['managers'] = this.select('td[data-manager="ExtensibleTableManager"]');
    this.prepareData['operations'] = this.select('.operation-box li');
    this.prepareData['count'] = this.prepareData['fields'].size() + this.prepareData['managers'].size() + this.prepareData['operations'].size();
    this.refreshLoadInfo();
    this.prepareFields.bind(this).defer();

    var imprimeRequireds = this.readData('ftype_required', '');
    if (imprimeRequireds.length > 0) {
      imprimeRequireds = imprimeRequireds.split(',');
      imprimeRequireds.each(function(imprimeCode) {
        var imprime = $D().getImprime(imprimeCode);
        if (imprime) {
          imprime.prepare();
        }
      });
    }
  },

  countPrepare:0,
  statePrepare:'',
  prepareFields: function() {
    if (this.prepareData['fields'].size() < 1) {
      this.prepareManagers.bind(this).defer();
      return;
    }
    var elt = this.prepareData['fields'].pop();
    this.statePrepare = 'Field ' + elt.readAttribute('data-name');
    var field = this.addField(elt);
    try {
      field.check();
    }
    catch(e) {
      field.addError('check', e.message);
    }

    this.refreshLoadInfo();
    if (this.countPrepare++ > 1) {
      this.countPrepare = 0;
      this.prepareFields.bind(this).defer();
    }
    else {
      this.prepareFields();//.bind(this).defer();
    }
  },
  prepareManagers: function() {
    if (this.prepareData['managers'].size() < 1) {
      this.prepareOperations.bind(this).defer();
      return;
    }
    this.statePrepare = 'Managers';
    var elt = this.prepareData['managers'].pop();
    this.managers.set(elt.readAttribute('data-fields'),
                      new declaration.ExtensibleTableManager(elt, {imprime: this}));
    this.refreshLoadInfo();
    if (this.countPrepare++ > 1) {
      this.countPrepare = 0;
      this.prepareManagers.bind(this).defer();
    }
    else {
      this.prepareManagers();
    }
  },
  prepareOperations: function() {
    if (this.prepareData['operations'].size() < 1) {
      this.parent.removeClassName('status-preparation');
      this.parent.addClassName('status-ready');
      this.operations.invoke('execute');
      this.statePrepare = 'finish';
      return;
    }
    this.statePrepare = 'Opérations';
    var elt = this.prepareData['operations'].pop();
    var operation_data = elt.readAttribute('data-operation').evalJSON(true);
    var method = operation_data['method'];
    if (!declaration.Operation[method]) {
      $D().log('method declaration.Operation[' + method + '] doesnt exits !');
      return;
    }
    var operation = new declaration.Operation[method](this.wrapper, this, operation_data['args']);
    this.operations.push(operation);
    this.refreshLoadInfo();
    if (this.countPrepare++ > 1) {
      this.countPrepare = 0;
      this.prepareOperations.bind(this).defer();
    }
    else {
      this.prepareOperations();
    }
  },
  refreshLoadInfo: function() {
    var done = this.prepareData['count'] - (this.prepareData['fields'].size() + this.prepareData['managers'].size() + this.prepareData['operations'].size());
    var percent = 100 * (done / this.prepareData['count']);
    this.infoBox.down('.content').update('[' + this.statePrepare + '] Chargement : ' + percent.round() + '%');
    this.infoBox.down('.background').setStyle('width:' + percent + '%;');
  },

  validate: function() {
    this.select('.throbber').invoke('show');
    Kwo.exec('/account/declaration/declaration.formulaire.validate',
             this.parent,
             { callback: this.validateCallback.bind(this)});
  },

  download: function() {
    var declaration_key = this.parent.down('input[name=declaration_key]').getValue();
    var formulairetype_id = this.parent.down('input[name=formulairetype_id]').getValue();
    Kwo.go('/declaration.pdf', {key:declaration_key, ftype_id:formulairetype_id}, {target:'blank'});
  },

  pagesReset: function() {

    this.prepareData['fields'] = this.select('.imprime-field[data-name]');
    this.prepareData['managers'] = this.select('td[data-manager="ExtensibleTableManager"]');
    this.prepareData['operations'] = this.select('.operation-box li');
    this.prepareData['count'] = this.prepareData['fields'].size() + this.prepareData['managers'].size() + this.prepareData['operations'].size();
    this.refreshLoadInfo();
    this.prepareFields.bind(this).defer();

    this.parent.select('.formulaire-page').each(function(page) {
      page.select('select, input, textarea').each(function(elt) {
        var imprime = elt.up('.imprime-field');
        var field = declaration.Field.getInstance(elt.up('.imprime-field'), this);
        field.setDefaultValue();
        field.onChange();
      }.bind(this));
    }.bind(this));

  },

  removeImprime: function(imprime_code, index, declaration_id, formulairetype_id) {
    var imprime = $D().getImprime(imprime_code, index);
    Kwo.exec('/account/declaration/declaration.formulaire.remove',
             { declaration_id: declaration_id,
               formulairetype_id: formulairetype_id,
               index: index },
             { callback: function(resp) {
               resp = new kwo.Response(resp);
               this.pagesReset();
               this.setState('new');
               $D().pagination.refreshImprimeState();
             }.bind(this) });
    if ($D().homePage) {
      $D().homePage.refresh(imprime);
    }
  },

  print: function() {
    $D().select('.imprime-box').invoke('addClassName', 'hidden');
    this.parent.removeClassName('hidden');

    if ($D().hasImprime('F-IDENTIF')) {
      var imprime = $D().getImprime('F-IDENTIF');
      if (imprime.getField('CA') && imprime.getField('CB')) {
        var dates = 'Début : ' + imprime.getField('CA').getValue() + ' - Fin : ' + imprime.getField('CB').getValue();
        $D().down('.print-footer').down('.exercice-dates').update(dates);
      }
    }
    window.print();
    $D().select('.imprime-box').invoke('removeClassName', 'hidden');
  },
  validateCallback: function(resp) {
    this.select('.throbber').invoke('hide');
    resp = new kwo.Response(resp);
    this.getFields().values().invoke('cleanErrors');
    if (resp.hasError()) {
      $A(resp.getAttribute('field_errors')).each(function (field_error) {
        $D().getField(field_error['field'],
                      field_error['index'],
                      field_error['imprime_index']).addError(field_error['operation_name'],
                                                             field_error['msg']);
      }, this);

      $A(resp.getAttribute('operation_errors')).each(function (operation_error) {
        $A(operation_error['fields']).each(function(field_code) {
          $D().getField(field_code['code'],
                        field_code['index'],
                        field_code['imprime_index']).addError(operation_error['operation_name'],
                                                              operation_error['msg']);
        }, this);
      }, this);
    }
    resp.alert();
  },

  store: function() {
    var that = this;
    if ($D().hasImprime('P-IDENTIF')
            && this.wrapper.readData('rcm')
            && $D().pagination.stepIndex + 1 === $D().pagination.steps.size()) {

      if (!confirm(that.wrapper.readData('rcm'))) return;
      Kwo.exec('/account/declaration/declaration.formulaire.store',
               that.parent,
               { callback: function(resp) {
                 resp = new kwo.Response(resp);
                 if (resp.hasError()) return resp.alert();
                 var message = 'Votre déclaration a bien été enregistrée. (N°' + that.wrapper.readData('declaration_id') + ')';
                 if (!confirm(message)) return;
                 that.select('.throbber').invoke('show');
                 Kwo.go($D().return_link);
               }
               });

    }
    else {
        if (!confirm(this.down('.submit').readAttribute('data-confirm'))) {
        return;
      }
      this.select('.throbber').invoke('show');
      Kwo.exec('/account/declaration/declaration.formulaire.store',
               this.parent,
               { callback: this.storeCallback.bind(this)});

    }
  },
  storeCallback: function(resp) {
    this.select('.throbber').invoke('hide');
    resp = new kwo.Response(resp);

    if (resp.hasError()) {
      resp.alert();
      return;
    }

    this.select('input[type="submit"]').invoke('addClassName', 'hidden');
    this.setState('saved');

    $D().pagination.refreshImprimeState();
    if ($D().hasImprime('P-IDENTIF')
            && this.wrapper.readData('rcm')
            && $D().pagination.stepIndex + 1 === $D().pagination.steps.size()) {
      Kwo.go($D().return_link);
    }
  },
  setState: function(state) {
    var stateElt = this.down('.formulaire-state');
    this.state = state;
    this.writeData('state', state);
    if (this.state == 'new') {
      stateElt.update('Formulaire vide (non enregistré).');
    }
    else if (this.state == 'required') {
      stateElt.update('Formulaire obligatoire.');
    }
    else if (this.state == 'saved') {
      stateElt.update('Formulaire enregistré.');
    }
    else if (this.state == 'saving') {
      stateElt.update('Enregistrement en cours.');
    }
    else if (this.state == 'validating') {
      stateElt.update('Validation en cours.');
    }
    else if (this.state == 'errors') {
      stateElt.update('Erreurs dans le formulaire.');
    }
    else if (this.state == 'changed') {
      stateElt.update('Modification(s) non enregistrée(s).');
    }
    $A(declaration.Imprime.states).each(function(state) {
      stateElt.removeClassName(state);
    }, this);
    stateElt.addClassName(state);

    if ($D().homePage) {
      $D().homePage.refresh(this);
    }

  }
});

declaration.Imprime.states = ['new', 'required', 'saved', 'saving', 'validating', 'errors', 'changed'];


declaration.Field = Class.create(declaration.Elt, {

  imprime: null,

  code: null,
  name: null,
  imprime_code: null,
  tooltip: null,
  errors: null,
  infos: null,
  index: null,
  extensible: null,
  isRequired: null,

  onCreate: function(imprime) {
    this.imprime = imprime;
    this.code = this.readData('code');
    this.index = this.readData('index');
    this.imprime_code = this.readData('imprime_code');
    this.name = this.readData('name');
    this.isRequired = this.readData('required', 0) > 0;
    this.isReadonly = this.readData('readonly', 0) > 0;
    this.tooltip = this.down('.elt-tooltip');
    this.errors = $H({});
    this.infos = $H({});
  },
  getImprime: function() {
    //return $D().getImprime(this.imprime_code, this.index);
    return this.imprime;
  },

  getFullCode: function() {
    return this.imprime_code + '_' + this.code;
  },
  dispatch: function() {
    //console.log('dispatch', declaration.Field.EVENT.CHANGE + '_' + this.getFullCode() + '_' + this.imprime.index);
    document.fire(declaration.Field.EVENT.CHANGE + '_' + this.getFullCode() + '_' + this.imprime.index,
                  { field_fullcode: this.getFullCode(),
                    imprime_index: this.imprime.index,
                    field_index: this.index });
  },
  onChange: function() {
    this.getImprime().onChange();
    try {
      this.removeError('check');
      this.check();
    }
    catch(e) {
      this.addError('check', e.message);
      return;
    }
    this.dispatch();
  },
  check: function() {
    if (this.isRequired) {
      if (('' + this.getValue()).empty()) {
        throw new Error('Ce champ est obligatoire');
      }
    }
  },
  getValue: Prototype.emptyFunction,
  setValue: Prototype.emptyFunction,

  readonly: function(bool) {
  },
  disable: function() {
  },
  enable: function() {
  },
  setType: function(type) {
  },

  setInfos: function(code, msg) {
    this.infos.set(code, msg);
    this.refreshTooltips();
  },
  addError: function(code, msg) {
    this.errors.set(code, msg);
    this.refreshTooltips();
  },
  removeError: function(code) {
    this.errors.unset(code);
    this.refreshTooltips();
  },
  cleanErrors: function() {
    this.errors = new $H({});
    this.refreshTooltips();
  },
  refreshTooltips: function() {
    var tooltipContent = '<p style="font-weight:bold">' + this.getFullCode() + '</p><br />';
    tooltipContent += this.infos.values().join('<br />') + '<br/>';
    tooltipContent += this.errors.values().join('<br />');
    this.tooltip.down('.elt-tooltip-content').update(tooltipContent);

    Kwo.Tooltip.hide();
    this.parent.stopObserving('mouseenter');
    this.parent.stopObserving('mouseleave');
    this.parent.removeClassName('has-error');
    if (this.errors.size() == 0 && this.infos.size() == 0) {
      return;
    }
    this.parent.observe('mouseenter',
                        function(evt) {
                          evt.stop();
                          Kwo.Tooltip.show(this.parent, this.tooltip, false);
                        }.bind(this));
    this.parent.observe('mouseleave',
                        function(evt) {
                          evt.stop();
                          Kwo.Tooltip.hide();
                        }.bind(this));
    if (this.errors.size() > 0) {
      this.parent.addClassName('has-error');
    }
  },

  setIndex: function(index) {
    this.index = index;
    this.writeData('index', index);
    this.name = this.name.replace(/\[\d+\]$/, '[' + index + ']');
  },
  setDefaultValue: function() {
    this.setValue(this.readData('default_value', ''));
    this.cleanErrors();
  }
});

declaration.Field.getInstance = function(elt, imprime) {
  var instance = null;
  var field_type = elt.readAttribute('data-type');
  if (declaration.Field['Type' + field_type]) {
    instance = new declaration.Field['Type' + field_type](elt, imprime);
  }
  else {
    $D().log('Field type unknown : ' + field_type, elt);
    instance = new declaration.Field(elt, imprime);
  }
  //instance.addError('code', instance.code);
  return instance;
};

declaration.Field.TYPE = {
  RESULT: 'result'
};

declaration.Field.EVENT = {
  CHANGE: 'declaration.Field.EVENT:change'
};



declaration.ExtensibleTableManager = Class.create(declaration.Elt, {

  imprime: null,
  codes: null,

  rowsGroups: null,
  extensibleCode: null,
  extensibleMax: null,

  onCreate: function(opts) {
    this.imprime = opts['imprime'];
    this.codes = this.readData('fields').split(',');
    this.extensibleCode = this.readData('extensible_code');
    this.extensibleMax = this.readData('extensible_max');
    this.rowsGroups = [];
    var rowIndex = -1;
    this.parent.up('tbody').select('.extensible-row[data-extensible-fields="' + this.readData('fields') + '"]').each(function(row) {
      if (row.down('.btn-remove')) {
        rowIndex++;
        row.down('.btn-remove').writeAttribute('data-index', rowIndex);
        row.down('.btn-remove').writeAttribute('data-fields', this.readData('fields'));
        row.down('.btn-remove').observe('click', this.onBtnRemoveClick.bind(this));
      }
      this.rowsGroups.push(row);
      row.writeAttribute('data-index', rowIndex);

    }, this);

    this.parent.up('tbody').down('.btn-add[data-fields="' + this.readData('fields') + '"]').observe('click', function(evt) {
        evt.stop();
        var index = this.rowsGroups.last().readAttribute('data-index');
        if ((this.extensibleMax - 1) > index || this.extensibleMax == 0 || this.extensibleMax == null) {
            this.addRow();
            if (this.extensibleCode > 0) {
                $(document).fire('declaration.ExtensibleTableManager:row.added',
                    { imprime: this.imprime,
                        extensibleCode: this.extensibleCode,
                        manager: this});
            }
        } else {
          alert('Vous avez atteint le nombre maximum de lignes: '+this.extensibleMax);
        }
    }.bind(this));
    $(document).observe('declaration.ExtensibleTableManager:row.added', function(evt) {
      if (evt.memo['imprime'] == this.imprime
              && evt.memo['extensibleCode'] == this.extensibleCode
              && evt.memo['manager'] != this) {
        this.addRow();
      }
    }.bind(this));
    $(document).observe('declaration.ExtensibleTableManager:row.removed', function(evt) {
      if (evt.memo['imprime'] == this.imprime
              && evt.memo['extensibleCode'] == this.extensibleCode
              && evt.memo['manager'] != this) {
        this.removeRow(evt.memo['index']);
      }
    }.bind(this));

  },

  onBtnRemoveClick: function(evt) {
    evt.stop();
    var elt = evt.findElement('.btn-remove');
    this.removeRow(elt.readAttribute('data-index'));
    if (this.extensibleCode > 0) {
      $(document).fire('declaration.ExtensibleTableManager:row.removed',
                       { imprime: this.imprime,
                         extensibleCode: this.extensibleCode,
                         manager: this,
                         index: elt.readAttribute('data-index')});
    }
  },

  removeRow: function(index) {
    //
    this.codes.each(function(code) {
      this.imprime.removeField(code, index);


    }, this);
    if (this.rowsGroups.size() == 1) { // TODO : Meilleure vérif!
      this.addRow();
    }


    this.getRows(index).each(function(remove_row) {
      this.rowsGroups = this.rowsGroups.without(remove_row);
      remove_row.remove();
    }, this);

    this.refreshRowsIndex();
    this.codes.each(function(code) {
      this.imprime.getField(code, 0).dispatch();
    }, this);
  },

  getRows: function(index) {
    var indexAttr = '';
    if (index !== undefined) {
      indexAttr = '[data-index="' + index + '"]';
    }
    return this.parent.up('tbody').select('.extensible-row[data-extensible-fields="' + this.readData('fields') + '"]' + indexAttr);
  },

  addRow: function() {
    var new_rows = [];
    var index = this.rowsGroups.last().readAttribute('data-index');
    var newIndex = Number(index) + 1;
    this.getRows(index).each(function(row) {
      var new_row = row.clone(true);
      this.rowsGroups.last().insert({after: new_row});
      this.rowsGroups.push(new_row);
      new_row.writeAttribute('data-index', newIndex);
      new_row.select('.imprime-field').each(function(elt) {
        var field = declaration.Field.getInstance(elt, this.imprime);
        field.setDefaultValue();
        field.setIndex(newIndex);
        this.imprime.addField(field);
        if (field instanceof declaration.Field.Typecci) {
            field.setIndex(newIndex);
        }
      }, this);
      if (new_row.down('.btn-remove')) {
        new_row.down('.btn-remove').writeAttribute('data-index', newIndex);
        new_row.down('.btn-remove').observe('click', this.onBtnRemoveClick.bind(this));
      }
      if (new_row.down('.line_number')) {
        new_row.down('.line_number').update(newIndex + 1);
      }
    }, this);
  },

  refreshRowsIndex: function () {
    var rowsfields = [];
    var indexes = [];
    this.getRows().each(function(row) {
      var index = row.readAttribute('data-index');

      var newIndex = indexes.size();
      if (indexes.indexOf(index) !== -1) {
        newIndex--;
      }
      row.writeAttribute('data-index', newIndex);
      if (row.down('.btn-remove')) {
        row.down('.btn-remove').writeAttribute('data-index', newIndex);
      }
      if (row.down('.line_number')) {
        row.down('.line_number').update(newIndex + 1);
      }
      if (indexes.indexOf(index) !== -1) {
        return;
      }
      indexes.push(index);

      var rowfield = [];
      this.codes.each(function(code) {
        var field = this.imprime.getField(code, index);
        if (!field) return;
        rowfield.push(field);
        this.imprime.removeField(code, index);
      }, this);
      if (rowfield.size() > 0) {
        rowsfields.push(rowfield);
      }
    }, this);

    rowsfields.each(function(rowfields, index) {
      rowfields.each(function(field) {
        field.setIndex(index);
        this.imprime.addField(field);
      }, this);
    }, this);

  }
});


declaration.HomePage = Class.create(declaration.Elt, {

  tbodies: null,

  onCreate: function() {
    this.tbodies = new $H({});
    this.select('tbody[data-ftype_code]').each(function(tbody) {
      this.tbodies.set(tbody.readAttribute('data-ftype_code'), tbody);
    }, this);
  },
  addImprime: function(imprime) {
    var tbody = this.tbodies.get(imprime.code);
    var elt = new Element('tr', {'data-index': imprime.index});
    var html = '<td>' +
            '     <p class="formulaire-single">' +
            '       <span class="label">' + imprime.code + ' - Occurence N°' + (Number(imprime.index) + 1) + '</span>' +
            '     </p>' +
            '   </td>' +
            '   <td>' +
            '     <span class="formulaire-state"></span>' +
            '   </td>';
    elt.update(html);
    tbody.insert({bottom: elt});
    this.refresh(imprime);
  },
  removeImprime: function(imprime) {
    var tbody = this.tbodies.get(imprime.code);
    var elt = tbody.down('[data-index=' + imprime.index + ']');
    if (elt) elt.remove();
  },
  refresh: function(imprime) {
    var tbody = this.tbodies.get(imprime.code);
    var state = imprime.readData('state');

    var stateElt = tbody.down('.formulaire-state');
    if (imprime.parent.up('.formulaire-repetable')) {
      stateElt = tbody.down('[data-index="' + imprime.index + '"] .formulaire-state');
    }



    if (state == 'new') {
      stateElt.update('Formulaire vide (non enregistré).');
    }
    else if (state == 'required') {
      stateElt.update('Formulaire obligatoire.');
    }
    else if (state == 'saved') {
      stateElt.update('Formulaire enregistré.');
    }
    else if (state == 'saving') {
      stateElt.update('Enregistrement en cours.');
    }
    else if (state == 'validating') {
      stateElt.update('Validation en cours.');
    }
    else if (state == 'errors') {
      stateElt.update('Erreurs dans le formulaire.');
    }
    else if (state == 'changed') {
      stateElt.update('Modification(s) non enregistrée(s).');
    }
    $A(declaration.Imprime.states).each(function(state) {
      stateElt.removeClassName(state);
    }, this);
    stateElt.addClassName(state);
  }


});

declaration.Pagination = Class.create(declaration.Elt, {

  buttonsContainers: null,
  previousBtns: null,
  nextBtns: null,
  selects: null,

  pages: null,
  steps: null,
  currentPage: null,
  currentImprimeCode: null,
  stepIndex: 0,
  currentStep: 0,
  stepBox: null,

  onCreate: function() {
    this.currentPage = null;
    this.pages = $H({});
    this.select('.imprime-page').each(function(page) {
      this.pages.set(page.readAttribute('data-code'), page);
    }, this);

    this.buttonsContainers = this.select('.buttons-container');
    this.previousBtns = this.select('.pagination-previous');
    this.nextBtns = this.select('.pagination-next');
    this.selects = this.select('.imprime-select select');

    this.previousBtns.invoke('observe', 'click', this.previous.bind(this));
    this.nextBtns.invoke('observe', 'click', this.next.bind(this));


    if ($('declaration-steps-box')) {
      this.selects.invoke('hide');
      this.initSteps();
    }
    else {
      this.selects.invoke('observe', 'change', function(evt) {
        evt.stop();
        var select = evt.element();
        this.gotoPage($F(select));
      }.bind(this));

    }
  },

  initSteps: function() {
    this.stepBox = $('declaration-steps-box');
    this.steps = [];
    this.stepIndex = 0;

    this.select('[data-page_label]').each(function(elt) {
      this.steps.push(elt);
    }, this);

    var pages = [];
    var firsts = [];
    var lasts = [];
    this.steps.each(function(elt) {
      if (elt.readAttribute('data-position') == 'last') {
        lasts.push(elt);
      } else if (elt.readAttribute('data-position') == 'first') {
        firsts.push(elt);
      }
      else {
        pages.push(elt);
      }
    }, this);
    this.steps = firsts.concat(pages, lasts);
    this.steps.each(function(page, index) {
      var span = new Element('span', {className:'step-name step-' + (index + 1)}).update(page.readAttribute('data-page_label'));
      this.stepBox.insert(span);
    }, this);
    this.stepBox.addClassName('steps-count-' + this.steps.size());
    this.steps.invoke('hide');
  },

  refreshImprimeState: function() {


    return;
  },

  goto: function(index) {
    if (this.stepBox) {
      this.gotoStep(index);
    }
    else {
      this.gotoPage(this.selects.first().options[index].value);
    }
  },
  gotoPage: function(imprimeCode) {
    if (this.currentImprimeCode && this.getImprimeController(this.currentImprimeCode).getState() == 'changed') {
      if (!confirm('Des formulaires n\'ont pas été enregistrés. Confirmez-vous le changement de page ?')) {
        this.selects.invoke('setValue', this.currentImprimeCode);
        return;
      }
    }

    if (this.currentPage) {
      this.currentPage.hide();
    }

    this.currentPage = this.pages.get(imprimeCode);
    this.currentPage.show();

    this.selects.invoke('setValue', imprimeCode);
    this.nextBtns.invoke('show');
    this.previousBtns.invoke('show');
    var select = this.selects.first();
    if (select.selectedIndex == select.options.length - 1) {
      this.nextBtns.invoke('hide');
    }
    if (select.selectedIndex == 0) {
      this.previousBtns.invoke('hide');
    }

    this.parent.up('body').scrollTo();
    if (imprimeCode == '') {
      this.currentImprimeCode = null;
      return;
    }
    this.currentImprimeCode = imprimeCode;
    this.getImprimeController(imprimeCode).prepare();
  },

  gotoStep: function(index) {
    if (this.currentImprimeCode && this.getImprimeController(this.currentImprimeCode).getState() == 'changed') {
      if (!confirm('Des formulaires n\'ont pas été enregistrés. Confirmez-vous le changement de page ?')) {
        return;
      }
    }

    this.stepIndex = index;

    this.nextBtns.invoke('show');
    this.previousBtns.invoke('show');
    if (this.stepIndex == this.steps.size() - 1) {
      this.nextBtns.invoke('hide');
    }
    if (this.stepIndex == 0) {
      this.previousBtns.invoke('hide');
    }

    this.steps.each(function(elt) {
      elt.up('.imprime-page').hide();
    });
    if (this.currentStep) {
      this.currentStep.hide();
    }
    this.currentStep = this.steps[this.stepIndex];
    var imprimeElt = this.currentStep.up('.imprime-page');
    imprimeElt.show();

    if (this.stepIndex == this.steps.size() - 1) {
      imprimeElt.down('.formulaire-header').hide();
      imprimeElt.down('.imprime-header').hide();
    }

    if (this.stepIndex == 0) {
      imprimeElt.down('.formulaire-header').show();
      imprimeElt.down('.imprime-header').show();
    }

    this.currentStep.show();

    $R(1, this.steps.size(), false).each(function(key) {
      this.stepBox.removeClassName('current-step-' + key);
    }, this);
    this.stepBox.addClassName('current-step-' + (this.stepIndex + 1));

    this.parent.up('body').scrollTo();

    this.currentImprimeCode = imprimeElt.readAttribute('data-code');
    this.getImprimeController(this.currentImprimeCode).prepare();
  },

  getImprimeController: function(imprimeCode) {
    var page = this.pages.get(imprimeCode);
    var pageController = null;
    if (page.hasClassName('formulaire-repetable')) {
      pageController = $D().getRepetable(imprimeCode);
    }
    else {
      pageController = $D().getImprime(imprimeCode);
    }
    return pageController;
  },

  next: function() {
    if (!this.stepBox) {
      var select = this.selects.first();
      this.gotoPage(select.options[select.selectedIndex + 1].value);
    }
    else {
      var index = 0;
      this.steps.each(function(elt) {
        if (elt.visible()) {
          throw $break;
        }
        index++;
      });
      index++;
      index = index >= this.steps.size() ? this.steps.size() - 1 : index;
      this.gotoStep(index);
    }

  },


  previous: function() {
    if (!this.stepBox) {
      var select = this.selects.first();
      this.gotoPage(select.options[select.selectedIndex - 1].value);
    }
    else {
      var index = 0;
      this.steps.each(function(elt) {
        if (elt.visible()) {
          throw $break;
        }
        index++;
      });
      index--;
      index = index < 0 ? 0 : index;
      this.gotoStep(index);

    }
  }

});



declaration.FormRepetable = Class.create(declaration.Elt, {

  btnAdd: null,
  btnDelete: null,
  index: null,
  selectElt: null,
  imprimeCode: null,
  isRequired: null,


  onCreate: function() {
    this.index = 0;

    this.imprimeCode = this.readData('code');
    this.isRequired = this.readData('required', 0);
    this.btnAdd = this.down('.btn-add');
    this.btnDelete = this.down('.btn-delete');
    this.selectElt = this.down('> .formulaire-repetable-select select');


    this.select('.panels form.imprime-box').each(function(elt) {
      var imprime = $D().getImprime(elt.readAttribute('data-code'), elt.readAttribute('data-index'));
      this.index = Math.max(this.index, Number(imprime.index) + 1);
    }, this);

    this.btnAdd.observe('click', function(evt) {
      evt.stop();
      var imprime = this.addImprime();
      this.selectImprime(imprime.index);
    }.bind(this));

    this.btnDelete.observe('click', function(evt) {
      evt.stop();
      if (!confirm('Êtes-vous sûr de vouloir supprimer ce formulaire ? ')) {
        return;
      }
      var index = $F(this.selectElt);
      this.removeImprime(index);
    }.bind(this));

    this.selectElt.observe('change', function(evt) {
      evt.stop();
      var index = $F(this.selectElt);
      if (index == '') {
        this.btnDelete.hide();
      }
      else {
        this.btnDelete.show();
      }
      this.selectImprime(index);
    }.bind(this));

    var index = $F(this.selectElt);
    if (index == '') {
      this.btnDelete.hide();
    }
    else {
      this.btnDelete.show();
    }
    this.selectImprime(index);


  },

  addImprime: function() {
    var imprimeParent = this.down('form.imprime-model').clone(true);
    imprimeParent.removeClassName('imprime-model');
    imprimeParent.addClassName('imprime-box');
    imprimeParent.writeAttribute('data-index', this.index);
    imprimeParent.down('input[name="index"]').setValue(this.index);
    imprimeParent.select('input, textarea, select').each(function(elt) {
      elt.name = elt.name.replace('[-1]', '[' + this.index + ']');
    }, this);
    imprimeParent.select('[data-name]').each(function(elt) {
      elt.writeAttribute('data-name', elt.readAttribute('data-name').replace('[-1]', '[' + this.index + ']'));
    }, this);
    this.down('.panels').insert(imprimeParent);
    var imprime = $D().addImprime(imprimeParent);

    this.selectElt.options[this.selectElt.options.length] = new Option('Occurence N°' + (Number(imprime.index) + 1), imprime.index);
    this.index = Math.max(this.index, Number(imprime.index) + 1);
    $D().pagination.refreshImprimeState();

    var index = $F(this.selectElt);
    if (index == '') {
      this.btnDelete.hide();
    }
    else {
      this.btnDelete.show();
    }

    if ($D().homePage) {
      $D().homePage.addImprime(imprime);
    }


    return imprime;
  },

  selectImprime: function(index) {
    this.select('.panels form.imprime-box').invoke('hide');
    this.down('.default-page').hide();
    this.selectElt.setValue(index);

    if (index == '') {
      this.down('.default-page').show();
      return;
    }

    var imprimeElt = this.down('form.imprime-box[data-index="' + index + '"]').show();
    var imprime = $D().getImprime(imprimeElt.readAttribute('data-code'),
                                  imprimeElt.readAttribute('data-index'));
    imprime.prepare();
    imprime.parent.select('input[type="submit"]').invoke('show');
  },
  getImprimes: function() {
    var imprimes = [];
    var imprimeElts = this.select('form.imprime-box[data-index]');
    imprimeElts.each(function(imprimeElt) {
      var imprime = $D().getImprime(imprimeElt.readAttribute('data-code'),
                                    imprimeElt.readAttribute('data-index'));
      imprimes.push(imprime);
    }, this);
    return imprimes;
  },

  removeImprime: function(index) {
    var imprime = $D().getImprime(this.imprimeCode, index);
    Kwo.exec('/account/declaration/declaration.formulaire.remove',
             { declaration_id: this.btnDelete.readAttribute('data-declaration_id'),
               formulairetype_id: this.btnDelete.readAttribute('data-formulairetype_id'),
               index: index },
             { callback: function(resp) {
               resp = new kwo.Response(resp);
               if (resp.hasError()) {
                 //resp.alert();
                 //return;
               }
               $D().removeImprime(this.imprimeCode, index);
               var optionIndex = 0;
               $A(this.selectElt.options).each(function(option) {
                 if (option.value == index) throw $break;
                 optionIndex++;
               });
               this.selectElt.options[optionIndex] = null;
               imprime.parent.remove();
               this.selectImprime('');
               $D().pagination.refreshImprimeState();
             }.bind(this) });
    if ($D().homePage) {
      $D().homePage.removeImprime(imprime);
    }
  },

  prepare: function() {
    var index = $F(this.selectElt);
    if (index == '') {
      this.btnDelete.hide();
    }
    else {
      this.btnDelete.show();
    }
    this.selectImprime(index);
  },

  getState: function() {
    var state = 'none';
    var saved = 0;
    var news = 0;
    this.getImprimes().each(function(imprime) {
      if (imprime.getState() == 'changed') {
        state = 'changed';
        throw $break;
      }
      if (imprime.getState() == 'saved') {
        saved++;
      }
      if (imprime.getState() == 'new') {
        news++;
      }
    }, this);
    if (saved > 0 && saved == this.getImprimes().size()) return 'saved';
    if (news > 0 && news == this.getImprimes().size()) return 'new';
    return state;
  }


});
