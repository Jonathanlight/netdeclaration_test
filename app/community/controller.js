
if (!Kwo) var Kwo = {};

Kwo.Auth = {

  onLogIn: function(args) {
    Kwo.exec("/community/user.login", args,
             {"callback": Kwo.Auth.onAuthCallback, "disable": true});
  },

  onSignUp: function(args) {
    var input = $(args).down(".terms_of_use");
    if (!Object.isUndefined(input) && !input.checked) {
      return Kwo.warn(input.readAttribute("data-confirm"));
    }
    Kwo.exec("/community/user.signup", args,
             {"callback": Kwo.Auth.onAuthCallback, "disable": true});
  },

  onAuthCallback: function(resp) {
    if (Kwo.hasError(resp)) return Kwo.error(resp);
    window["_user_id"] = resp["result"]["user_id"];
    var dialog = Kwo.getDialog();
    if (dialog && dialog.name === "auth") {
      dialog.onCallback();
      dialog.close();
    }
    else if ("onAuthCallback" in window) {
      window.onAuthCallback();
    }
    else if (window.location.href.indexOf("sign") != -1) {
      Kwo.home()
    }
    else {
      Kwo.reload();
    }
  },

  onPasswordRequest: function(args) {
    Kwo.exec("/community/password.send", args,
             {"callback": Kwo.Auth.onPasswordRequestCallback.bind($(args)),
              "disable": true});
  },

  onPasswordRequestCallback: function(resp) {
    if (Kwo.hasError(resp)) return Kwo.error(resp);
    this.hide().previous().show();
    Kwo.warn(resp);
  }

};

Kwo.Class.Auth = Class.create(Kwo.Dialog, {

 initialize: function($super, opts) {
   this.opts = opts || {};
   this.name = "auth";
   this.width = window["_auth_width"] || 720;
   this.height = window["_auth_height"] || 450;
   if ("callback" in this.opts) {
     this.onCallback = function () {
       if (Object.isString(this.opts["callback"])) {
         Kwo.go(this.opts["callback"]);
       }
       else {
         this.opts["callback"].call();
       }
     }
   }
   else {
     this.onCallback = function () {
       if ("onAuthCallback" in window) {
         window.onAuthCallback();
       }
     }
   }
   $super(this.onDisplay);
  },

  onDisplay: function() {
    var args = {};
    if ("mode" in this.opts) {
      /** login | signup **/
      args["mode"] = this.opts["mode"];
    }
    Kwo.exec("/community/signup", args,
             {"container": this.support,
              "callback": this.onDisplayCompleted.bind(this)});
  },

  onDisplayCompleted: function() {

  }

});

Kwo.Account = {

  timeout: null,

  onEnter: function(module, mode) {
    if (Object.isElement(module)) {
      module = module.readAttribute("data-module");
    }
    else {
      module = module || "/community/account";
    }
    if (!Kwo.isAuth()) {
      var opts = {"callback": module};
      if (mode) {
        opts["mode"] = mode;
      }
      new Kwo.Class.Auth(opts);
      return ;
    }
    Kwo.go(module);
  },

  onLeave: function(elt, fallback_url) {
    elt = $(elt);
    var url = elt.readAttribute("data-fallback") || "/";
    Kwo.exec("/community/user.logout", null,
             {callback: Kwo.go.curry(url, {}, {}),
              confirm: elt});
  },

  refresh: function(resp) {
    if (Kwo.hasError(resp)) return Kwo.error(resp);
    if ("result" in resp && "callback_url" in resp["result"]) {
      return Kwo.go(resp["result"]["callback_url"]);
    }
    Kwo.reload();
  },

  setMessage: function(msg, error) {
    error = false;
    if (typeof msg == "object" && "error" in msg) {
      if (msg["error"] >= 1) {
        error = "Attention ! " + msg["result"]["msg"].join(",");
      }
      else {
        msg = msg["result"]["callback_message"];
      }
    }
    else {
      error = error || false;
    }
    var pix = "icon_declaration_validate.png";
    if (error != false) {
      pix = "ko.png";
      msg = error;
    }
    else {
      msg = Object.isUndefined(msg) ||  msg.empty() ? "ok" : msg;
    }
    if (!$("account-notice")) return ;
    var notice = $("account-notice");
    notice.show();
    notice.update(msg.ucfirst() + '<img src="/app/ntd/pix/account/' + pix + '" />'
                                   +'<div style="clear:both;"></div>');
    window.clearTimeout(Kwo.Account.timeout);
    Kwo.Account.timeout = window.setTimeout(notice.hide.bind(notice), 5000);
  },

  initAuthBox: function() {
    Kwo.exec("/community/widget.auth", null,
             {container: "kwo-auth-box"});
  }

};

Kwo.User = {

  onAvatarSet: function(file) {
    Kwo.exec("/account/community/avatar.save", {"image": file},
             {callback: Kwo.User.onAvatarCallback});
  },

  onAvatarCallback: function(resp) {
    if (Kwo.hasError(resp)) return Kwo.error(resp);
    Kwo.exec("/account/community/avatar.edit", null,
             {container: $("avatar-box")});
  },

  onEmailSubmit: function(args) {
    Kwo.exec("/account/community/email.save", args,
             {callback: true, disable: true});
  },

  onEmailConfirm: function(elt) {
    Kwo.exec("/community/email.confirm.request", null,
             {callback: $(elt).up("div")});
  },

  onPasswordSubmit: function(args) {
    Kwo.exec("/account/community/password.save", args,
             {callback: true, disable: true, reset: true});
    return true;
  },

  onProfileSubmit: function(args) {
    Kwo.exec("/account/community/profile.save", args,
             {callback: true, disable: true});
  }

};

Kwo.Composer.Message = Class.create(Kwo.Dialog, {

  initialize: function($super, elt) {
    this.name = "abuse";
    this.layout = "hbox";
    this.width = 600;
    this.height = 400;
    this.args = {item_key: $(elt).readAttribute("data-item")};
    $super("/community/message.compose");
  },

  onSubmit: function(elt) {
    elt = $(elt);
    Kwo.exec("/community/message.send", [this.args, elt],
             {callback: elt, disable: elt});
  }

});

Kwo.Composer.Favorite = Class.create(Kwo.Dialog, {

  initialize: function($super, elt) {
    elt = $(elt);
    this.name = "favorite";
    this.layout = "hbox";
    this.args = {item_key: elt.readAttribute("data-item"),
                 url: elt.readAttribute("data-url")};
    this.width = 400;
    this.height = 320;
    $super("/community/favorite.prompt", this.args);
  },

  onSave: function(elt) {
    if (!Kwo.isAuth()) {
      var auth = new Kwo.Class.Auth();
      auth.onCallback = this.onSave.bind(this).curry(elt);
      return ;
    }
    elt = $(elt); console.log(this.args);
    Kwo.exec("/community/favorite.save", [this.args, elt],
             {callback: elt.down("UL"), disable: elt});
  }

});

Kwo.Class.Like = Class.create({

  initialize: function(elt) {
    this.elt = $(elt);
    this.onSubmit();
  },

  onSubmit: function() {
    if (!Kwo.isAuth()) {
      var auth = new Kwo.Class.Auth();
      auth.onCallback = this.onSubmit.bind(this);
      return ;
    }
    var args = {"item_key": this.elt.readAttribute("data-item")};
    Kwo.exec("/core/item.like", args,
             {callback: this.onCallback.bind(this)});
  },

  onCallback: function(resp) {
    if (Kwo.hasError(resp)) return Kwo.error(resp);
    this.elt.down("SPAN").update("(" + resp["result"]["like_count"] + ")");
  }

});

Kwo.Favorite = {

  onAlertUnset: function(elt) {
    elt = $(elt);
    Kwo.exec("/community/favorite.alert.unset",
             {id: elt.up("TR").readAttribute("data-id")},
             {confirm: elt, callback: Kwo.Favorite.onCallback});
  },

  onCallback: function(resp) {
    if (Kwo.hasError(resp)) return Kwo.error(resp);
    Kwo.reload();
  },

  onDelete: function(elt) {
    elt = $(elt);
    Kwo.exec("/community/favorite.delete",
             {id: elt.readAttribute("data-id")},
             {confirm: elt, callback: Kwo.Favorite.onCallback});
  }

}

Kwo.Notice = {

  onSubmit: function(args) {
    Kwo.exec("notice.save", args,
             {callback: true, disable: true});
  }

};

