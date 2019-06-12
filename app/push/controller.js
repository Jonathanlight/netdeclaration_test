
Kwo.Subscriptions = {
  
  onSubmit: function(args) {
    Kwo.exec("/account/push/subscriptions.set", args, 
             {disable:true, callback:Kwo.Account.refresh});
  }
  
};

Kwo.Newsletter = {
  
  onCallback: function(resp) {
    if (Kwo.hasError(resp)) return Kwo.error(resp);
    var box = this.down(".confirmation-box");
    if (box) {
      var msg = resp["result"]["callback_message"].ucfirst() + ".";
      box.addClassName("confirmation").update(msg);
    }
  },

  onRecipientSave: function(elt) {
    Kwo.exec("/account/push/recipient.save", elt,
             {"disable": true, "callback": true});
  },

  onSubmit: function(elt) { 
    elt = $(elt);
    var input = elt.down("INPUT[data-placeholder]");
    if (input) {
      if (input.readAttribute("data-placeholder") == input.getValue()) {
        input.value = "";
        input.focus();
        return ;
      }
    }
    Kwo.exec("/push/newsletter.subscribe", elt,
             {"disable":true, "reset":true,
              "callback": Kwo.Newsletter.onCallback.bind(elt)});
  }
  
};

Kwo.Class.Newsletter = Class.create(Kwo.Dialog, {

  initialize: function($super, elt) {
    this.name = "newsletter";
    this.className = "layout-hbox";
    this.width = 500;
    this.height = 300;
    this.args = {"item_key": $(elt).readAttribute("data-item")};
    $super(this.onDisplay, this.args);
  },
  
  onDisplay: function() {
    Kwo.exec("/push/newsletter.signup", this.args, 
             {"container": this.support});
  }

});