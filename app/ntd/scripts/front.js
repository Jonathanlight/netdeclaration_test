
ntd.front = {};

var $existing_id = document.getElementById("personal-data-control");
if ($existing_id) {
  $existing_id.onclick = function(e){
    e.preventDefault();
    tarteaucitron.userInterface.openPanel();
  };
}

ntd.front.AdherentForm = Class.create(ntd.Manager, {
  TYPE_CEC: 1,
  TYPE_ENTREPRISE: 2,
  TYPE_OGA: 3,
  TYPE_PRO_SANTE: 4,
  TYPE_INTERNATIONAL: 5,

  NEWSLETTER_BASE_PUBLIC: 'ntd.public',
  NEWSLETTER_BASE_CEC: 'ntd.cec',
  NEWSLETTER_BASE_ENTREPRISE: 'ntd.entreprise',
  NEWSLETTER_BASE_OGA: 'ntd.oga',
  NEWSLETTER_BASE_PRO_SANTE: 'ntd.pro_sante',
  NEWSLETTER_BASE_INTERNATIONNAL: 'ntd.internationnal',

  onCreate: function () {
    this.parent.observe('submit',
                        function (evt) {
                          evt.stop();

                          var input = this.down(".terms_of_use");
                          if (!Object.isUndefined(input) && !input.checked) {
                            Kwo.warn(input.readAttribute("data-confirm"));
                            return ;
                          }

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

    Kwo.go(resp.getAttribute('callback_url'));
  },

  onFormChange: function () {
    var form = this.parent;
    var that = this;
    var input;

    // -- type change ?
    input = this.parent.getInputs('radio', 'adherent[type]').detect(function (input) {
      return $(input).checked;
    });

    $(form['adherent[oga_agrement]']).disable().up('.elt').hide();
    $(form['adherent[cec_flags]']).enable().up('.elt').hide();
    $(form['adherent[cec_ordre]']).disable().up('.elt').hide();
    $(form['adherent[email_edi]']).disable().up('.elt').hide();

    // => adherent[cec_flags]
    var cec_avocat = $(form['elt-2-0']);

    if (input) {
      input = $(input);
      var type = $F(input);
      if (type == this.TYPE_CEC) {
        $(form['adherent[cec_flags]']).enable().up('.elt').show();
        $(form['adherent[cec_ordre]']).enable().up('.elt').show();
        $(form['adherent[email_edi]']).enable().up('.elt').show();
        $('block__inscription--edi').show();

        $(form['adherent[oga_agrement]']).setValue('');
      }
      else if (type == this.TYPE_OGA) {
        $(form['adherent[oga_agrement]']).enable().up('.elt').show();
        $(form['adherent[email_edi]']).enable().up('.elt').show();
        $('block__inscription--edi').show();

        $(form['adherent[cec_ordre]']).setValue('');
        cec_avocat.checked = false;
      }
      else if (type == this.TYPE_ENTREPRISE || type == this.TYPE_INTERNATIONAL || type == this.TYPE_PRO_SANTE) {
        $('block__inscription--edi').hide();

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


      // Newsletter
      $$("[type='checkbox'][name*='newsletter']").each(function(newsletter) {
        newsletter = $(newsletter);
        var value = newsletter.value;

        if (value == that.NEWSLETTER_BASE_PUBLIC) {
          return;
        }

        if ((type == that.TYPE_ENTREPRISE && value == that.NEWSLETTER_BASE_ENTREPRISE)
            || (type == that.TYPE_PRO_SANTE && value == that.NEWSLETTER_BASE_PRO_SANTE)
            || (type == that.TYPE_CEC && value == that.NEWSLETTER_BASE_CEC)
            || (type == that.TYPE_OGA && value == that.NEWSLETTER_BASE_OGA)
            || (type == that.TYPE_INTERNATIONAL && value == that.NEWSLETTER_BASE_INTERNATIONNAL)
          ) {
          newsletter.up('label').show();
          newsletter.enable();
        }
        else {
          newsletter.up('label').hide();
          newsletter.disable();
          newsletter.checked = false;
        }
      });
    }

    // ADRESSE FACTURATION
    input = this.parent.getInputs('radio',
                                  'adherent[has_no_billing_address]')
      .detect(function (input) {
                return $(input).checked;
              });
    this.down('.billing-address-1st-step').removeClassName('block--shown').addClassName('block--hidden');

    if (input && $F(input) == 0) {
      this.down('.billing-address-1st-step').removeClassName('block--hidden').addClassName('block--shown');
    }
  }
});

ntd.front.NewsletterPublique = Class.create(ntd.Manager, {

  onCreate: function() {
    Kwo.exec(this.parent.readAttribute('action'),
             this.parent,
             {callback: this.onSubmitCallback.bind(this), disable: true});
  },

  onSubmitCallback: function (resp) {
    resp = new kwo.Response(resp);
    if (resp.hasError()) {
      resp.alert();
      return;
    }
    var msg = resp.getMessage();
    if (msg) {
      alert(msg);
    }
  }

});