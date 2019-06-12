declaration.Field.SelectHelper = {
  readonly: function(elt, bool) {
    if (bool) {
      var selectedIndex = elt.selectedIndex;
      $A(elt.options).each(function(option) {
        option = $(option);
        option.writeAttribute('disabled', 'disabled');
      });
      $(elt.options[selectedIndex]).removeAttribute('disabled');
      elt.writeAttribute('readonly', 'readonly');
    }
    else {
      $A(elt.options).each(function(option) {
        option = $(option);
        option.removeAttribute('disabled');
      });
      elt.removeAttribute('readonly');
    }
  }
};

declaration.Field.Input = Class.create(declaration.Field, {

  input: null,

  onCreate: function($super, imprime) {
    $super(imprime);
    this.input = this.down('input');
    this.input.observe('change',
                       function(evt) {
                         this.onChange();
                       }.bind(this));
    this.input.observe('focus',
                       function(evt) {
                         this.input.select();
                       }.bind(this));
    if (this.isReadonly) {
      this.readonly(true);
    }
  },
  onChange: function($super) {
    if (!this.getValue() || this.getValue().blank()) {
      this.input.setValue(this.readData('default_value'));
    }
    $super();
  },
  getValue: function() {
    return $F(this.input);
  },
  setValue: function(value) {
    this.input.setValue(value);
    this.onChange();
  },
  readonly: function(bool) {
    if (bool) {
      this.input.writeAttribute('readonly', 'readonly');
    }
    else {
      this.input.removeAttribute('readonly');
    }
  },
  setType: function(type) {
    if (type == declaration.Field.TYPE.RESULT) {
      this.readonly(true);
      this.input.addClassName('result');
    }
  },
  setIndex: function($super, index) {
    $super(index);
    this.input.name = this.name;
  },
  disable: function() {
    this.input.disable();
  },
  enable: function() {
    this.input.enable();
  }
});

// TODO : gestion du default
declaration.Field.Typemoa = Class.create(declaration.Field.Input, {

  value: null,
  onCreate: function($super, imprime) {
    $super(imprime);
    this.value = $F(this.input);
  },
  onChange: function($super) {
    this.value = $F(this.input);
    $super();
  },
  check: function($super) {
    $super();
    var value = this.value;
    if (value.include('.') || value.include(',') || !isFinite(Number(value))) {
      throw new Error('Veuillez saisir un nombre entier.');
    }
  },
  getValue: function() {
    return this.value;
    //return $F(this.input);
  },
  setValue: function(value) {
    var value = Number(value);
    if (isFinite(value)) {
      value = value.round();
    }
    else {
      value = 'Erreur';
    }

    this.input.setValue(value);
    this.value = $F(this.input);
    this.onChange();
  }
});


declaration.Field.Typedtm = Class.create(declaration.Field, {
  input: null,
  type: null,
  onCreate: function($super, imprime) {
    $super(imprime);
    this.type = this.down('[data-type]').readAttribute('data-type');
    if (this.type == 'ssaammjj') {
      this.input = this.down('input');
      this.input.observe('change',
                         function(evt) {
                           evt.stop();
                           this.onChange();
                         }.bind(this));
      this.input.onchange = function() {
        this.onChange();
      }.bind(this);
      this.input.observe('click',
                         function(evt) {
                           evt.stop();
                           new Kwo.Datepicker(this.input);
                         }.bind(this));
    }
    else if (this.type == 'ssaammjjssaammjj') {
      this.input = this.down('input[type="hidden"]');
      var inputBeginAt = this.down('[data-name="begin_at"]');
      var inputEndAt = this.down('[data-name="end_at"]');
      var onChange = function() {
        this.input.setValue(inputBeginAt.getValue() + '#' + inputEndAt.getValue());
        this.onChange();
      }.bind(this);
      inputBeginAt.onchange = onChange;
      inputEndAt.onchange = onChange;
      inputBeginAt.observe('click',
                           function(evt) {
                             evt.stop();
                             new Kwo.Datepicker(this.down('[data-name="begin_at"]'));
                           }.bind(this));
      inputEndAt.observe('click',
                         function(evt) {
                           evt.stop();
                           new Kwo.Datepicker(this.down('[data-name="end_at"]'));
                         }.bind(this));
    }
    else if (this.type == 'ssaa') {
      this.input = this.down('select');
      this.input.observe('change',
                         function(evt) {
                           this.onChange();
                         }.bind(this));
    }
    else if (this.type == 'ssaamm') {
      this.input = this.down('input');
      this.select('select').invoke('observe', 'change',
                                   function(evt) {
                                     var value = '';
                                     var selectYear = this.down('select.year');
                                     var selectMonth = this.down('select.month');
                                     if (selectYear.selectedIndex > 0 && selectMonth.selectedIndex > 0) {
                                       value = Number(selectYear.getValue()).toPaddedString(4) + Number(selectMonth.getValue()).toPaddedString(2);
                                     }
                                     this.setValue(value);
                                     this.onChange();
                                   }.bind(this));
    }
    else if (this.type == 'mmjj') {
      this.input = this.down('input');
      this.select('select').invoke('observe', 'change',
                                   function(evt) {
                                     var value = '';
                                     var selectMonth = this.down('select.month');
                                     var selectDay = this.down('select.day');
                                     if (selectDay.selectedIndex > 0 && selectMonth.selectedIndex > 0) {
                                       value = Number(selectMonth.getValue()).toPaddedString(2) + Number(selectDay.getValue()).toPaddedString(2);
                                     }
                                     this.setValue(value);
                                     this.onChange();
                                   }.bind(this));
    }
    else if (this.type == "month_count") {
      this.input = this.down('input');
      this.input.observe('change',
                         function(evt) {
                           this.onChange();
                         }.bind(this));
      this.input.observe('focus',
                         function(evt) {
                           this.input.select()
                         }.bind(this));

    }
    else {
      this.input = this.down('input');
      this.input.observe('change',
                         function(evt) {
                           this.onChange();
                         }.bind(this));
      this.input.observe('focus',
                         function(evt) {
                           this.input.select()
                         }.bind(this));
    }
    if (this.isReadonly) {
      this.readonly(true);
    }
  },
  check: function($super) {
    $super();
    if (this.type == 'month_count') {
      var value = this.getValue();
      if (value && value.length > 0 && isNaN(Number(value))) {
        throw new Error('Veuillez saisir le nombre de mois (exemple 12) ou laissez vide');
      }
    }
    if (this.type == 'ssaammjjssaammjj') {
      var inputBeginAt = this.down('[data-name="begin_at"]');
      var inputEndAt = this.down('[data-name="end_at"]');
      var value = inputBeginAt.getValue();
      if (!value.blank() && !((/\d{2}\/\d{2}\/\d{4}/).match(value))) {//value.length != 'dd/mm/yyyy'.length) {
        throw new Error('Attention, la date doit être exprimée suivant le format "jj/mm/aaaa"');
      }
      var value = inputEndAt.getValue();
      if (!value.blank() && !((/\d{2}\/\d{2}\/\d{4}/).match(value))) {//value.length != 'dd/mm/yyyy'.length) {
        throw new Error('Attention, la date doit être exprimée suivant le format "jj/mm/aaaa"');
      }
    }
  },
  getValue: function() {
    return $F(this.input);
  },
  setValue: function(value) {
    this.input.setValue(value);
    this.onChange();
  },
  readonly: function(bool) {
    if (bool) {
      this.input.writeAttribute('readonly', 'readonly');
    }
    else {
      this.input.removeAttribute('readonly');
    }
  },
  disable: function() {
    this.input.disable();
  },
  enable: function() {
    this.input.enable();
  },
  setType: function(type) {
    if (type == declaration.Field.TYPE.RESULT) {
      this.readonly(true);
      this.input.addClassName('result');
    }
  },
  refreshErrors: function($super) {
    if ($super()) {
      this.input.addClassName('has-error');
    }
    else {
      this.input.removeClassName('has-error');
    }
  },
  setIndex: function($super, index) {
    $super(index);
    this.input.name = this.name;
  }
});


declaration.Field.Typerff = Class.create(declaration.Field.Input, {
  onCreate: function($super, imprime) {
    $super(imprime);
    this.isRof = (this.imprime_code == 'F-IDENTIF' && this.code == 'KD');
    this.isRefPayment = (this.imprime_code == 'P-IDENTIF' && ['KA', 'KB', 'KC'].indexOf(this.code) != -1);
    if (this.isRof) {
      declaration.Field.SelectHelper.readonly(this.down('select'), true);
      this.down('input[type="checkbox"]').observe('click', this.onCheckboxClick.bind(this));
    }
    if (this.isRefPayment) {
      //this.down('input[type="button"]').observe('click', this.onButtonClick.bind(this));
    }
  },
  check: function($super) {
    $super();
    if (this.isRof) {
      var value = Number(this.getValue());
      if (!(value > 0 && value < 200)) {
        throw new Error("L'indice d'activité doit etre compris entre 1 et 199.");
      }
    }
  },
  onCheckboxClick: function(evt) {
    var elt = evt.findElement('input[type="checkbox"]');
    if (elt.checked) {
      declaration.Field.SelectHelper.readonly(this.down('select'), false);
      this.select('input[type="text"], select').each(function(elt) {
        elt.setValue('');
      });
      this.down('input[type="text"]').writeAttribute('readonly', 'readonly');
      declaration.Field.SelectHelper.readonly(this.down('select'), true);
      this.removeError('check');
    }
    else {
      declaration.Field.SelectHelper.readonly(this.down('select'), false);
      this.select('input[type="text"], select').each(function(elt) {
        elt.setValue(elt.readAttribute('data-default-value'));
      });
      declaration.Field.SelectHelper.readonly(this.down('select'), true);
      this.down('input[type="text"]').removeAttribute('readonly');
    }
  },
  onChange: function($super) {
    if (!this.isRof) {
      $super();
    }
    else {
      try {
        this.removeError('check');
        this.check();
      }
      catch (e) {
        this.addError('check', e.message);
        return;
      }
      this.dispatch();
    }
  }

});


declaration.Field.Typeqty = Class.create(declaration.Field.Input, {
  check: function($super) {
    $super();
    var value = $F(this.input);
    if (value.include(',')) {
      throw new Error('Utilisez un point pour séparer les décimales.');
    }
    if (isNaN(Number(value))) {
      throw new Error('La valeur doit être un nombre entier ou décimal (avec 2 décimales maximum).');
    }
    if (!(Number(value) >= 0)) {
      throw new Error('La valeur doit être un nombre positif.');
    }
  },
  onChange: function($super) {
    var value = this.getValue();
    if (isFinite(value)) {
      var sep = value.indexOf('.');
      if (sep != -1) {
        value = value.substr(0, sep + 3);
        this.input.setValue(value);
      }
    }
    $super();
  }
});

declaration.Field.Typepcd = Class.create(declaration.Field.Input, {
  check: function($super) {
    $super();
    var value = $F(this.input);
    if (value.include(',')) {
      throw new Error('Utilisez un point pour séparer les décimales.');
    }
    if (isNaN(Number(value))) {
      throw new Error('La valeur doit être un nombre entier ou décimal (avec 2 décimales maximum).');
    }
    if (!(Number(value) >= 0)) {
      throw new Error('La valeur doit être un nombre positif.');
    }
  },
  onChange: function($super) {
    var value = this.getValue();
    if (isFinite(value)) {
      var sep = value.indexOf('.');
      if (sep != -1) {
        value = value.substr(0, sep + 3);
        this.input.setValue(value);
      }
    }
    $super();
  }
});

declaration.Field.Typeftx = Class.create(declaration.Field.Input, {});
declaration.Field.Typecpt = Class.create(declaration.Field.Input, {});
declaration.Field.Typenad = Class.create(declaration.Field, {
  input: null,
  onCreate: function($super, imprime) {
    $super(imprime);
    var type = this.down('[data-type]').readAttribute('data-type');
    if (type == 'select') {
      this.input = this.down('select');
    }
    else {
      this.input = this.down('input');
    }

    this.input.observe('change',
                       function(evt) {
                         this.onChange();
                       }.bind(this));
    this.input.observe('focus',
                       function(evt) {
                         this.input.select();
                       }.bind(this));

    if (this.isReadonly) {
      this.readonly(true);
    }
  },
  getValue: function() {
    return $F(this.input);
  },
  setValue: function(value) {
    this.input.setValue(value);
    this.onChange();
  },
  readonly: function(bool) {
    if (bool) {
      this.input.writeAttribute('readonly', 'readonly');
    }
    else {
      this.input.removeAttribute('readonly');
    }
  },
  disable: function() {
    this.input.disable();
  },
  enable: function() {
    this.input.enable();
  },
  setType: function(type) {
    if (type == declaration.Field.TYPE.RESULT) {
      this.readonly(true);
      this.input.addClassName('result');
    }
  },
  refreshErrors: function($super) {
    if ($super()) {
      this.input.addClassName('has-error');
    }
    else {
      this.input.removeClassName('has-error');
    }
  },
  setIndex: function($super, index) {
    $super(index);
    this.input.name = this.name;
  }
});

declaration.Field.Typecux = Class.create(declaration.Field.Input, {
  check: function($super) {
    $super();
    var value = $F(this.input);
    if (this.input.readAttribute('data-type_simple') == '5402') {
      if (value.include(',')) {
        throw new Error('Utilisez un point pour séparer les décimales.');
      }
      if (isNaN(Number(value))) {
        throw new Error('Le taux de change à saisir doit être une valeur numérique.');
      }
    }
  }
});


declaration.Field.Typecci = Class.create(declaration.Field, {
  input: null,
  onCreate: function($super, imprime) {
    $super(imprime);

    this.input = this.down('select') ? this.down('select') : this.down('input[type=checkbox]');

    if (this.down('input[type=text].type-cci')) {
      this.input = this.down('input[type=text].type-cci');
      new declaration.Autocompleter(this.input);
    }

    this.input.observe('change',
                       function() {
                         this.onChange();
                       }.bind(this));
    if (this.isReadonly) {
      this.readonly(true);
    }
  },
  getValue: function() {
    return $F(this.input);
  },
  setValue: function(value) {
    this.input.setValue(value);
    this.onChange();
  },
  readonly: function(bool) {
    if (this.input.tagName == 'SELECT') {
      declaration.Field.SelectHelper.readonly(this.input, bool);
      return;
    }
    if (bool) {
      this.input.writeAttribute('readonly', 'readonly');
    }
    else {
      this.input.removeAttribute('readonly');
    }
  },
  setType: function(type) {
    if (type == declaration.Field.TYPE.RESULT) {
      this.readonly(true);
      this.input.addClassName('result');
    }
  },
  refreshErrors: function($super) {
    if ($super()) {
      this.input.addClassName('has-error');
    }
    else {
      this.input.removeClassName('has-error');
    }
  },
  setIndex: function($super, index) {
    var old_index = this.index;
    $super(index);
    this.input.name = this.input.name.replace('[' + old_index + ']', '[' + this.index + ']');
    var input_hidden = this.input.previous('input[type=hidden]');
    if (input_hidden !== undefined && input_hidden.tagName == 'INPUT') {
        input_hidden.name = this.input.name;
    }
  },
  setDefaultValue: function() {
    this.input.setValue(this.readData('default', 0));
  },
  disable: function() {
    this.input.disable();
  },
  enable: function() {
    this.input.enable();
  }

});

declaration.Field.Typefii = Class.create(declaration.Field, {
  input: null,

  onCreate: function($super, imprime) {
    $super(imprime);
    this.input = this.down('select');
    this.input.observe('change',
                       function(evt) {
                         this.onChange();
                       }.bind(this));
    if (this.isReadonly) {
      this.readonly(true);
    }
  },
  getValue: function() {
    return $F(this.input);
  },
  setValue: function(value) {
    this.input.setValue(value);
    this.onChange();
  },
  readonly: function(bool) {
    declaration.Field.SelectHelper.readonly(this.input, bool);
  },
  setIndex: function($super, index) {
    $super(index);
    this.input.name = this.name;
  },
  disable: function() {
    this.input.disable();
  },
  enable: function() {
    this.input.enable();
  }
});


declaration.Autocompleter = Class.create({
  "elt": null,
  "autocompleter": null,
  "initialize": function(elt) {
    var that = $(this);
    this.elt = $(elt);
    this.autocompleter = new Ajax.Autocompleter(this.elt, this.elt.next(), this.elt.getAttribute('data-action'), {
      'paramName': 'query',
      'minChars': 2,
      'frequency': 0.5,
      'multiple': 0,
      'afterUpdateElement': function(text, li) {
        value = $(li).getAttribute('data-value');
        $(text).previous().setValue(value);
      }
    });

    this.elt.observe('change', this.onFieldChange.bindAsEventListener(this));
  },

  "onFieldChange": function(evt) {
    if (this.elt.getValue() == '') {
      this.elt.previous().setValue('');
    }
  }
});
