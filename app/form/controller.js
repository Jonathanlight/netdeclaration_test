
Kwo.Class.Form =  Class.create({

  form: null,

  initialize: function(elt) {
    this.form = $(elt);
    this.form.observe("submit", this.onSubmit.bindAsEventListener(this));
  },

  onSubmit: function(evt) {
    if (evt) {
      evt.stop();
    }
    this.form.select(".form-field").each(function (elt) {
      elt.removeClassName("form-field-failure");
    });
    Kwo.exec(this.form.readAttribute("action"), this.form,
             {"callback": this.onSubmitCallback.bind(this),
              "disable": this.form});
    return false;
  },

  onSubmitCallback: function(resp) {
    resp = new kwo.Response(resp);
    if (resp.isAuthError()) {
      var auth = new Kwo.Class.Auth();
      auth.onCallback = this.onSubmit.bind(this);
      return ;
    }
    var result = resp.getResult(); console.log(result);
    if (!("failures" in result)) {
      this.form.hide();
      this.form.next("DIV").update(result["ack"]).show();
      return ;
    }
    var that = this;
    result["failures"].each(function(field_id) {
      that.form.down(".form-field-" + field_id).addClassName("form-field-failure");
    });
  }

});