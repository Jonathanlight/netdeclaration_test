var ntd = {};

ntd.Manager = Class.create(
  {

    parent: null,
    initialize: function (elt, opts) {
      var that = this;
      this.parent = $(elt);

      /*Event.observe(window, "resize", function() {
       that.onWindowResize();
       });*/

      this.onCreate(opts);

      /*
       if (document.readyState == "complete") {
       this.onPaint();
       }
       else {
       Event.observe(window, "load", function(evt) {
       that.onWindowLoaded();
       });
       }
       */
    },

    down: function (expr) {
      return this.parent.down(expr);
    },
    select: function (expr) {
      return this.parent.select(expr);
    },
    log: function (args) {
      console.log(args);
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

    onWindowLoaded: function () {
      this.onPaint();
    },
    onWindowResize: function () {
      this.onPaint();
    },
    onCreate: function (opts) {
    },
    onPaint: function () {
    }

  });

ntd.onLeave = function (elt) {
  elt = $(elt);
  var url = elt.readAttribute("data-fallback") || "/";
  Kwo.exec("/community/user.logout", null,
           {callback: Kwo.go.curry(url, {}, {}),
             confirm: elt});
};

ntd.onLogIn = function (form) {
  form = $(form);
  Kwo.exec(form.readAttribute('action'),
           form,
           {callback: function (resp) {
             if (Kwo.hasError(resp)) return Kwo.error(resp);
             //window["_user_id"] = resp["result"]["user_id"];
             if ("result" in resp && "callback_url" in resp["result"]) {
               return Kwo.go(resp["result"]["callback_url"]);
             }
           }, "disable": true});
};

ntd.onPasswordRequest = function (form) {
  form = $(form);
  Kwo.exec(form.readAttribute('action'),
           form,
           {"callback": function (resp) {
             if (Kwo.hasError(resp)) return Kwo.error(resp);
             form.hide().previous().show();
             Kwo.warn(resp);
           },
             "disable": true});
};


ntd.Search = {

  "results": function(query, offset) {

    var args = {};
    args["offset"] = offset === undefined ? 0 : offset;
    if (query === undefined) {
      if ($("kwo-search-input")) {
        args["query"] = $F('kwo-search-query');
      }
      else {
        return false;
      }
    }
    args["query"] = query;

    if (args["query"].length < 1) return false ;

    Kwo.go("/search/results", args);

  }

};


ntd.FlashInfoManager = Class.create(
  ntd.Manager,
  {
    id: null,
    onCreate: function () {
      this.id = this.readData('id');
      this.parent.observe('click', this.onClick.bind(this));
    },
    onClick: function (evt) {
      var elt = evt.findElement('[data-method]');
      if (elt && elt.readAttribute('data-method') == 'close') {
        this.close();
      }
    },
    close: function () {
      this.parent.stopObserving();
      this.parent.remove();
      Kwo.exec('/flashinfo.close', this.id, {callback: null});
    }
  }
);



ntd.BlockHelpManager = Class.create(
  ntd.Manager,
  {
    form: null,
    onCreate: function () {
      this.parent.observe('click', this.onClick.bindAsEventListener(this));
      this.form = new Kwo.Class.Form(this.down('form'));
      this.form.onAfterSubmitSuccess = function(){
        this.hide.bind(this).delay(2);
      }.bind(this);
    },
    onClick: function (evt) {
      var elt = evt.findElement('[data-method="toggle"]');
      if (elt) {
        this.toggle();
      }
    },
    show: function () {
      this.parent.addClassName('block--help--shown');
    },
    hide: function () {
      this.parent.removeClassName('block--help--shown');
    },
    visible: function () {
      return this.parent.hasClassName('block--help--shown');
    },
    toggle: function () {
      this.visible() ? this.hide() : this.show();
    }

  }
);


ntd.BtnScrollTop = Class.create(ntd.Manager, {
  visible: false,
  onCreate: function(){
    $(document).observe('scroll', this.onDocumentScroll.bind(this));
    this.parent.observe('click', function (evt) {
      var offsets = document.viewport.getScrollOffsets();
      window.scrollTo(offsets['left'], 0);
      this.hide();
    }.bind(this));
    this.hide();
  },
  onDocumentScroll: function () {
    var offsets = document.viewport.getScrollOffsets();
    if (!this.visible) {
      if (offsets['top'] > 0) {
        this.show();
      }
    } else {
      if (offsets['top'] < 10) {
        this.hide();
      }
    }
  },
  show: function () {
    this.parent.addClassName('btn--backtop--shown');
    this.visible = true;
  },
  hide: function () {
    this.parent.removeClassName('btn--backtop--shown');
    this.visible = false;
  }
});

Kwo.Class.Form = Class.create(
  {

    form: null,

    initialize: function (elt) {
      this.form = $(elt);
      this.form.observe("submit", this.onSubmit.bindAsEventListener(this));
    },

    onSubmit: function (evt) {
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

    onSubmitCallback: function (resp) {
      resp = new kwo.Response(resp);
      if (resp.isAuthError()) {
        var auth = new Kwo.Class.Auth();
        auth.onCallback = this.onSubmit.bind(this);
        return;
      }
      var result = resp.getResult();
      if (!("failures" in result)) {
        this.form.hide();
        this.form.next("DIV").update(result["ack"]).show();
        this.onAfterSubmitSuccess();
        return;
      }
      var that = this;
      result["failures"].each(function (field_id) {
        that.form.down(".form-field-" + field_id).addClassName("form-field-failure");
      });
    },
    onAfterSubmitSuccess: Prototype.emptyFunction

  });


ntd.TarifTabs = Class.create(ntd.Manager,{
  onCreate: function() {
    $('tabs-links').select('a').each(function(el) {
      el.observe('click', this.show.bind(this).curry(el));
    }.bind(this));
    this.show($('tabs-links').select('a').first());
  },
  hideAll: function() {
    $('tabs-links').select('a').each(function(el) {
      el.removeClassName('active');
    });
    $('tabs-container').select('.tabs').each(function(el) {
      el.hide();
    });
  },
  show: function(a) {
    this.hideAll();
    $(a).addClassName('active');
    $($(a).getAttribute('data-label')).show();
  }
});

ntd.wysiwyg = {
  toggleCellContent: function(elt){
    $(elt).previous().toggleClassName('limited-cell-content');
    if($(elt).previous().hasClassName('limited-cell-content')) {
      $(elt.update('Voir la suite'));
    }
    else{
      $(elt.update('Cacher'));
    }
  }
};

ntd.helpOverlay = {
  show: function(parent) {
    $(parent.readAttribute('data-dialog')).show();
    parent.addClassName('middle-help-dialog-btn__shown');
  },
  close: function(parent) {
    $(parent.readAttribute('data-dialog')).hide();
    parent.removeClassName('middle-help-dialog-btn__shown');
  }
};

ntd.execDataOnLoad = function(){
  $$("[data-on-load]").each(function (elt) {
    var scriptlet = elt.readAttribute("data-on-load").replace('(this)', '(elt)');
    elt.writeAttribute("data-on-load", "");
    if (scriptlet.length > 1) {
      try{
        eval(scriptlet);
      }catch(err){
        if(window['console']) {
          console.error(err);
        }
      }
    }
  });
};

// Screen loader
ntd.displayLoader = function(elt) {
  $(elt).select('.fa-spinner').invoke('addClassName', 'fa-show');
  $(elt).select('.text-spin').invoke('addClassName', 'hidden');
}
ntd.hideLoader = function() {
  $(elt).select('.fa-spinner').invoke('addClassName', 'fa-show');
  $(elt).select('.text-spin').invoke('addClassName', 'hidden');
}

$(document).observe('dom:loaded', function () {
  ntd.execDataOnLoad();
});
