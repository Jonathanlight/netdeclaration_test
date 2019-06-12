ntd.account = {


  callback: function (resp) {
    resp = new kwo.Response(resp);
    if (resp.hasError()) {
      return resp.alert();
    }
    resp.alert();
    Kwo.reload();
  },

  onFormSubmit: function (form) {
    Kwo.exec($(form).readAttribute('action'),
             form,
             { callback: ntd.account.callback,
               disable: true});
  },

  onEmailConfirm: function (elt) {
    Kwo.exec("/community/email.confirm.request", null,
             {callback: $(elt).up("div")});
  },

  adherentForm: Class.create(ntd.Manager, {
    TYPE_CEC: 1,
    TYPE_ENTREPRISE: 2,
    TYPE_OGA: 3,
    TYPE_PRO_SANTE: 4,
    TYPE_INTERNATIONAL: 5,

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
      this.parent.getInputs('checkbox').invoke('observe', 'click', this.onFormChange.bind(this));

      this.onFormChange();
    },

    onSubmitCallback: function (resp) {
      resp = new kwo.Response(resp);

      if (resp.hasError()) {
        resp.alert();
        this.onFormChange();
        return;
      }
      Kwo.go("/middle/bulletin");
    },

    onFormChange: function () {
      var form = this.parent;
      var input;

      // -- type change ?
      input = this.parent.getInputs('radio', 'adherent[type]').detect(function (input) {
        return $(input).checked;
      });

      $(form['adherent[oga_agrement]']).disable().up('.elt').hide();
      $(form['adherent[cec_flags]']).disable().up('.elt').hide();
      $(form['adherent[cec_ordre]']).disable().up('.elt').hide();

      // => adherent[cec_flags]
      var cec_avocat = $(form['elt-2-0']);

      if (input) {
        input = $(input);
        var type = $F(input);
        if (type == this.TYPE_CEC) {
          $(form['adherent[cec_flags]']).enable().up('.elt').show();
          $(form['adherent[cec_ordre]']).enable().up('.elt').show();
          form.down('.email-declaration-3nd-step').show();

          $(form['adherent[oga_agrement]']).setValue('');
        }
        else if (type == this.TYPE_OGA) {
          $(form['adherent[oga_agrement]']).enable().up('.elt').show();
          form.down('.email-declaration-3nd-step').show();

          $(form['adherent[cec_ordre]']).setValue('');
          cec_avocat.checked = false;
        }
        else if (type == this.TYPE_ENTREPRISE || type == this.TYPE_INTERNATIONAL || type == this.TYPE_PRO_SANTE) {
          form.down('.email-declaration-3nd-step').hide();

          $(form['adherent[cec_ordre]']).setValue('');
          $(form['adherent[oga_agrement]']).setValue('');
          cec_avocat.checked = false;
        }

        if (cec_avocat.checked || type != this.TYPE_CEC) {
          $(form['adherent[cec_ordre]']).enable().up('.elt').hide();
          $(form['adherent[cec_ordre]']).setValue('');
        }
        else {
          $(form['adherent[cec_ordre]']).enable().up('.elt').show();
        }
      }

      // ADRESSE FACTURATION
      input = this.parent.getInputs('radio',
                                    'adherent[has_no_billing_address]')
        .detect(function (input) {
                  return $(input).checked;
                });
      this.down('.billing-address-1st-step').hide();
      this.down('.billing-address-2nd-step').hide();

      if (input && $F(input) == 0) {
        this.down('.billing-address-1st-step').show();
      }

      input = this.parent.getInputs('radio',
                                    'adherent[is_main_adherent_billing_address]').detect(function (input) {
                                                                                           return $(input).checked;
                                                                                         });
      if (input && $F(input) == 0) {
        this.down('.billing-address-2nd-step').show();
      }


    }
  })


};


Kwo.User = {
  onEmailConfirm: ntd.account.onEmailConfirm
};
