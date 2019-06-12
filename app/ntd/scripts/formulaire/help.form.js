
/* Reload assert event on occurence form when some event fired */

document.on('change', '.field', reloadAssertRun); // select fields
document.on('keyup', '.field', reloadAssertRun); // input text fields
document.on('click', '.btn-add', reloadAssertRunOnAddNewOccurrence); // Run assert when new occurrence is added

function reloadAssertRun(evt, elm){
  evt.stop();
  let table = elm.up('table');
  let table_class = table.readAttribute('class');
  asserts.run(table_class);
}

function reloadAssertRunOnAddNewOccurrence(evt, elm) {

  // get the form code
 let table = $$('.page-repetable table');
 let class_name = table[0].readAttribute('class');

  asserts.run(class_name); // like das2tv_20190101 - run assert
}
/* end */

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

ntd.BlockHelpManager = Class.create(
  ntd.Manager,
  {
    form: null,
    onCreate: function () {
      this.parent.observe('click', this.onClick.bindAsEventListener(this));
      this.form = new Kwo.Class.Form(this.down('form'));
      this.form.onAfterSubmitSuccess = function () {
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

$(document).observe('dom:loaded', function () {
  $$("[data-on-load]").each(function (elt) {
    var scriptlet = elt.readAttribute("data-on-load").replace('(this)', '(elt)');
    elt.writeAttribute("data-on-load", "");
    if (scriptlet.length > 1) eval(scriptlet);
  });
});