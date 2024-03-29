
if (window["console"] === undefined) {
  window.console = {"log": Prototype.emptyFunction};
}

if (!kwo) var kwo = {};

Kwo = {

  "registry": {},
  "Class": {},
  "Composer": {},
  "Visitor": {},
  "dialog": null,
  "dialogs": [],
  "Dialogs": {},
  "Widgets": {},
  "Handlers": {},
  "Layers": {},
  "callbacks": {},
  "flags": {},
  "scripts": {},

  "getDialog": function() {
    if (Kwo.dialogs.length < 1) return null;
    return Kwo.dialogs[Kwo.dialogs.length - 1];
  },

  "setDialog": function(dialog) {
    Kwo.dialogs.push(dialog);
  },

  "unsetDialog": function() {
    return Kwo.dialogs.pop();
  },

  "onViewportChange": function(e) {
    if (Kwo.dialogs.length > 0) {
      var l = Kwo.dialogs.length;
      for (var i = 0; i < l; i++) {
        Kwo.dialogs[i].place();
      }
    }
  },

  "F": function(model) {
    model = model.toLowerCase();
    if (model in Kwo.registry) return Kwo.registry[model];
    Kwo.registry[model] = new Kwo.Class.Obj(model);
    return Kwo.registry[model];
  },

  

  "mergeArgs": function() {
    var h = new Hash({}), n = arguments.length, arg;
    for (var i = 0; i < n; i++) {
      arg = arguments[i];
      if (arg === undefined || arg === null || arg === false || arg === true) {
        continue;
      }
      if (Object.isString(arg)) {
        arg = arg.toQueryParams();
        h.update(arg);
      }
      else if (typeof arg == "object") {
        if (Object.isArray(arg)) {
          arg.each(function (item) {
            h.update(Kwo.mergeArgs(item));
          });
        }
        else if (Object.isElement(arg)) {
          var s = $(arg).readAttribute("data-values");
          if (s != null && s.length > 1) {
            h.update(s.evalJSON());
          }
          if (arg.tagName.toUpperCase() == "FORM") {
            if (Kwo.isBack()) {
              var xml_file = arg.getAttribute("data-xml-file");
              if (xml_file) {
                h.set("xml_file", xml_file);
              }
            }
            arg = $(arg).serialize(true);
          }
          else if ($(arg)) {
            var form;
            if ("form" in arg && arg.form) {
              form = $(arg.form)
              arg = form.serialize(true);
            }
            else {
              form = $(arg).up("form");
              arg = form ? form.serialize(true) : {};
            }
            if (form && Kwo.isBack()) {
              var xml_file = form.getAttribute("data-xml-file");
              if (xml_file) {
                h.set("xml_file", xml_file);
              }
            }
          }
          h.update(arg);
        }
        else {
          h.update(arg);
        }
      }
    }
    return h;
  },

  "isBack": function() {
    return "_scope" in window && window["_scope"] === "back";
  },

  "isFront": function() {
    return "_scope" in window && window["_scope"] === "front";
  },

  "isMiddle": function() {
    return "_scope" in window && window["_scope"] === "middle";
  },

  "exec": function(action, args, options) {

    if (Object.isElement(action)) {
      var elt = $(action);
      action = elt.readAttribute("data-action");
      args = {};
      if (elt.hasAttribute("data-args")) {
        args = Object.toJSON(elt.readAttribute("data-args"));
      }
      if (Kwo.isBack()) {
        args["context"] = {};
        elt.ancestors().each(function (ancestor) {
          if (ancestor.tagName != "DIV" || !ancestor.hasClassName("data-item")) return ;
          args["context[" + ancestor.getAttribute("data-model") + "_id]"] = ancestor.getAttribute("data-id");

        });
      }
      options = {};
      if (elt.hasAttribute("data-confirm")) {
        options["confirm"] = elt.getAttribute("data-confirm");
      }
      if (elt.hasAttribute("data-callback")) {
        options["callback"] = elt.getAttribute("data-callback");
      }
      if (elt.hasAttribute("data-container")) {
        options["container"] = elt.getAttribute("data-container");
      }
    }

    options = options || {};

    if ("disable" in options) {
      if (options["disable"] === true) {
        options["disable"] = args;
      }
      options["disable"] = $(options["disable"]);
      if (options["disable"].hasClassName("kwo-disabled")) {
        return ;
      }
    }

    if ("confirm" in options) {
      var msg;
      if (Object.isElement(options["confirm"])) {
        msg = $(options["confirm"]).getAttribute("data-confirm");
      }
      else {
        msg = options["confirm"] == true ? "êtes vous sûr ?" : options["confirm"];
      }
      if (msg.length >= 1 && !confirm(msg.ucfirst())) { return false; }
    }

    var params = Kwo.mergeArgs(args, {"__token": Math.random()});
    var opts = {};

    if ("container" in options && options["container"]) {
      var container = $(options["container"]);
      if (!container) {
        console.log("Attention ! No AJAX Container.");
        return false;
      }
/*      if (Kwo.isBack() && container.up().hasClassName("deck")) {
        container.up().raise(container);
      }*/
      opts = {"parameters": params.toObject(),
              "evalScripts": false,
              "onComplete": function () {
                if ("callback" in options && options["callback"]) {
                  options["callback"].call(container);
                };
                container.fire("container:updated", {"action": action, "args": args});
              },
              "requestHeaders": {"X-Kwo-Referer": window.location.href,
                                 "X-Kwo-Request": "update"}};
      new Ajax.Updater(container, action, opts);
      return false;
    }
    else if ("callback" in options && Object.isString(options["callback"])) {
      params["callback"] = options["callback"];
      action += action.indexOf("?") == -1 ? "?" : "&";
      Kwo.load(action + params.toQueryString());
      return false;
    }

//    console.log(params.toObject());

    opts = {
      "requestHeaders": {"X-Kwo-Referer": window.location.href,
                         "X-Kwo-Request": "exec"},
      "asynchronous": "async" in options ? options["async"] : true,
      "evalJS": false,
      "evalJSON": false,
      "parameters": params.toObject(),
      "onCreate": function() {
//        if (window.top.$("loading")) { window.top.$("loading").show(); }
        if ("toggle" in options) { $(options.toggle).toggle(); }
        if ("disable" in options) {
          options["disable"].addClassName("kwo-disabled");
          if (options["disable"].tagName.toUpperCase() == "FORM") {
            options["disable"].disable();
          }
        }
      },
      "onSuccess": function(t) {
        var res = t.responseText.evalJSON();
        if (options["callback"] == true || options["callback"] == "true") {
          options["callback"] = true;
          if ((action.indexOf("/") == -1 && window.location.href.indexOf("/account/") != -1) ||
              action.indexOf("/account") != -1) {
            options["callback"] = Kwo.Account.refresh;
          }
          else {
            options["callback"] = Kwo.callback;
          }
        }
        if (Kwo.hasError(res)) {
          if ("callback" in options && !Object.isElement(options["callback"])) {
            options["callback"].call(null, res);
          }
          else if (res["error"] == 401) {
            return new Kwo.Class.Auth();
          }
          else {
            Kwo.error(res);
          }
        }
        else {
          if ("callback" in options) {
            if (options["callback"] === null || Object.isUndefined(options["callback"])) {

            }
            else if (Object.isElement(options["callback"])) {
              var elt = $(options["callback"]);
              if (elt.tagName.toUpperCase() == "SELECT") {
                elt.length = 0;
                $H(res["result"]["values"]).each(function (pair) {
                  elt.insert("<option value='"+pair.key+"'>"+pair.value+"</option>");
                });
                elt.selectedIndex = 0;
              }
              else {
                if (!elt.visible()) {
                  elt.show();
                }
                elt.update(res["result"]["callback_message"]);
                elt.addClassName("node-updated");
                if (elt.hasClassName("vanish")) {
                  elt.addClassName("vanish-on");
                  setTimeout(function () {
                    elt.removeClassName("vanish-on");
                    elt.hide(); }, 3000);
                }
                if (elt.hasClassName("dialog-close")) {
                  setTimeout(function () { Kwo.getDialog().close(); }, 2000);
                }
              }
            }
            else {
              options["callback"].call(null, res);
            }
          }
          if ("reset" in options) {
            options["reset"] = Object.isElement(options["reset"])
                             ? $(options["reset"])
                             : $(args);
            options["reset"].reset();
          }
        }
      },
      "on404": function(t) {
        console.log("AJAX Error : " + t.statusText + " was not found");
      },
      "onFailure": function(t) {
        console.log("AJAX Failure [" + t.status + "] : " + t.statusText);
      },
      "onException": function(t, e) {
        console.log("AJAX Exception [" + e.name + "] : " + e.message);
      },
      "onComplete": function(t) {
        if ("toggle" in options) { $(options.toggle).toggle(); }
        if ("disable" in options) {
          options["disable"].removeClassName("kwo-disabled");
          if (options["disable"].tagName.toUpperCase() == "FORM") {
            options["disable"].enable();
          }
        }
      }
    };

    new Ajax.Request(action, opts);

    return false;
  },


  "go": function(action, args, options) {
    var url = action;
    options = options || {};

    if (Object.isElement(url)) {
      url = action.readAttribute("data-url");
    }

    if (!Object.isString(action) && "result" in action && "callback_url" in action["result"]) {
      url = action["result"]["callback_url"];
    }

    if ("confirm" in options) {
      var msg;
      if (Object.isElement(options["confirm"])) {
        msg = $(options["confirm"]).getAttribute("confirm");
      }
      else {
        msg = options["confirm"] == true ? "OK ?" : options["confirm"];
      }
      if (msg.length >= 2 && !confirm(msg.ucfirst())) return ;
    }


    if (!Object.isUndefined(args) && args != null) {
      args = Kwo.mergeArgs(args);
      if (!args.toQueryString().empty()) {
        url = action + "?" + args.toQueryString();
      }
    }

    if ("target" in options) {
      if (options["target"] == "blank") {
        window.open(url);
      }
      else {
        $(options["target"]).src = url;
      }
      return ;
    }

    window.location.href = url;

    return false;
  },

  "anchor": function(name) {
    document.anchors.item(name).scrollIntoView();
    return false;
  },

  "callback": function(h) {
    if (Kwo.hasError(h)) {
      return Kwo.error(h);
    }
    if ("callback_message" in h["result"]) {
      if ("callback_container" in h["result"]) {
        $(h["result"]["callback_container"]).update(h["result"]["callback_message"]);
      }
      else {
        Kwo.warn(h);
      }
    }
    if ("callback_url" in h["result"]) {
      if (h["result"]["callback_url"] == "reload") {
        Kwo.reload();
      }
      else {
        Kwo.go(h["result"]["callback_url"]);
      }
      return ;
    }
    if (!("callback_message" in h["result"]) && !("callback_url" in h["result"])) {
//      Kwo.reload();
    }
  },

  "home": function(h) {
    window.location.href= "/";
  },

  "reload": function() {
    window.location.reload();
  },

"hasError": function(res) {
    if (Object.isUndefined(res)) return false;
    return res["error"] >= 1;
  },

  "error": function(args) {
    if (typeof args == "object" && "result" in args && "msg" in args["result"]) {
      args = args["result"]["msg"];
    }
    if (args instanceof Array) {
      var out = "Attention !\n";
      args.each(function(item) {
        out += " - " + item + "\n";
      });
      alert(out);
    }
    else {
      alert(args.ucfirst());
    }
    return false;
  },

  "warn": function(args) { console.log(args);
    if (typeof args == "object" && "result" in args && "callback_message" in args["result"]) {
      args = args["result"]["callback_message"];
    }
    if (args instanceof Array) {
      var out = "";
      args.each(function(item) {
        out += item + "\n";
      });
      alert(out);
    }
    else {
      alert(args.ucfirst());
    }
    return false;
  },

  "isAuth": function() {
    return "_user_id" in window && window["_user_id"] >= 1;
  },

  "load": function(src, callback, args) {
    var elt = null;
    if (Object.isElement(src)) {
      elt = src;
      src = elt.getAttribute("data-script");
      if (Object.isUndefined(callback) && elt.hasAttribute("data-callback")) {
        callback = elt.getAttribute("data-callback");
        if (callback == "true") {
          callback = function() { console.log(src + " is loaded"); }
        }
        else {
          callback = callback.toFunction();
          callback = callback.bind(elt);
        }
      }
    }
    if (src.indexOf("/") == -1) {
      src = "/app/" + src + "/controller.js";
    }
    if (!Object.isUndefined(callback) && !Object.isUndefined(args)) {
      callback = callback.curry(args);
    }
    if (Kwo.scripts[src] == true) {
      if (!Object.isUndefined(callback)) {
        callback();
      }
      return ;
    }
    var script = new Element("script",
                             {"type": "text/javascript",
                              "src": src,
                              "async": true});
    if (!Object.isUndefined(callback)) {
      if (Prototype.Browser.IE) {
        script.onreadystatechange = function() {
          if (script.readyState == "loaded" ||
              script.readyState == "complete"){
            script.onreadystatechange = null;
            callback();
          }
        }
      }
      else {
        script.onload = callback;
      }
    }
    Kwo.scripts[src] = true;
    $$("head")[0].insert(script);
  },

  "redirect": function(elt) {
    elt = $(elt);
    if (!Kwo.hasClickExpired(elt)) return false;
    var args = {}, opts = {};
    args["url"] = elt.readAttribute("data-url");
    args["item_key"] = elt.readAttribute("data-item");
    if (elt.readAttribute("target")) {
      opts["target"] = elt.readAttribute("target");
    }
    Kwo.go("/core/redirect", args, opts);
    return false;
  },

  "hasClickExpired": function(elt) {
    if (!Object.isElement(elt)) return ;
    var expiration = elt.readAttribute("data-expiration");
    expiration = Object.isString(expiration) ? expiration.intval() : 0;
    var now = new Date().getTime();
    if (expiration > now) return false;
    elt.writeAttribute("data-expiration", (now + 500));
    return true;
  },

  "onNotify": function(res) {
    if (Kwo.hasError(res)) return Kwo.error(res);
    alert(res["result"]["callback_message"]);
  }

};

kwo.track = function(action, category) {
  Kwo.exec("/tracker/track", {"action": action, "category": category});
};

kwo.Response = Class.create({
  
  resp: null,
  
  initialize: function(resp) {
    this.resp = resp;
  },
  
  getAttribute: function(attr) {
    return this.resp["result"][attr];
  },
  
  isAuthError: function() {
    return this.hasError() && this.resp["error"] == 401;
  },

  getErrors: function() {
    return this.resp["result"]["msg"];
  },

  alert: function() {
    if (this.hasError()) return alert(this.getError("\n"));
    return alert(this.getMessage());
  },

  getMessage: function() {
    return this.getAttribute("callback_message");
  },

  getResult: function() {
    return this.resp["result"];
  },

  getError: function(sep) {
    sep = sep || "<br/>";
    var args = this.resp["result"]["msg"];
    var out = "";
    if (args instanceof Array) {
      args.each(function(item) {
        out += " - " + item + sep;
      });
    }
    return out;
  },
  
  hasError: function() {
    return this.resp["error"] >= 1;
  }

});


//Kwo.dialogs = new Hash();

Kwo.Locale = {

  onOpen: function (elt) {
    $("kwo-locales-box").toggle();
    var pos = $(elt).cumulativeOffset();
    $("kwo-locales-box").setStyle({top: (pos[1] + $(elt).getHeight()) + "px",
                                   left: pos[0] + "px"});
  },

  onSet: function (locale, fallback) {
    if ($("kwo-locales-box")) $("kwo-locales-box").toggle();
    Kwo.exec("/core/locale.set", {locale: locale},
             {callback: Kwo.Locale.onCallback.curry(fallback)});
  },

  onCallback: function (fallback, h) {
    if (fallback == undefined) {
      var parts = window.location.pathname.substring(1).split("/", 1);
      if (parts.length != 1 || parts[0].length != 2) {
        Kwo.reload();
        return ;
      }
      window.location.href = window.location.href.replace(new RegExp("/" + parts[0] + "(/|$)"),
                                                          "/" + h["result"]["locale"] + "/");
      return ;
    }
    Kwo.go(fallback);
  }

};


Kwo.DateManager = {

  birthdate: function (elt) {
    var input = $(elt).previous("INPUT"), date = {}, tmp;
    tmp = input;
    for (var i = 1; i <= 3; i++) {
      tmp = tmp.next("SELECT");
      if (tmp.className.indexOf("day") != -1) date["day"] = $F(tmp);
      else if (tmp.className.indexOf("month") != -1) date["month"] = $F(tmp);
      else date["year"] = $F(tmp);
    }
    input.value = date["year"] + "-" + date["month"] + "-" + date["day"];
  },

  monthyear: function(elt) {
    var input = $(elt).previous("INPUT"), date = {}, tmp;
    tmp = input;
    for (var i = 1; i <= 2; i++) {
      tmp = tmp.next("SELECT");
      if (tmp.className.indexOf("month") != -1) date["month"] = $F(tmp);
      else date["year"] = $F(tmp);
    }
    input.value = date["year"] + "-" + date["month"] + "-01";
  }

};



Kwo.Tag = {

  "view": function (tag) {
    Kwo.Search.results(tag, 0);
  }

};

Kwo.Tooltip = {

  "elt": null,
  "anchor": null,
  "followMouse": null,

  "hide": function() {
    document.stopObserving("mousemove", Kwo.Tooltip.onMouseMove);
    if (Kwo.Tooltip.elt) Kwo.Tooltip.elt.hide();
  },

  "show": function(anchor, id, followMouse) {
    Kwo.Tooltip.hide();
    Kwo.Tooltip.followMouse = followMouse === undefined ? true : followMouse;
    anchor = $(anchor);
    Kwo.Tooltip.elt = id === undefined
                    ? anchor.previous(".kwo-tooltip")
                    : $(id);
    Kwo.Tooltip.anchor = anchor;
    document.observe("mousemove", Kwo.Tooltip.onMouseMove);
    Kwo.Tooltip.elt.show();
    if (window.event) Kwo.Tooltip.onMouseMove(window.event);
  },

  "onMouseMove": function(e) {
    var dim = document.viewport.getDimensions();
    var pos = document.viewport.getScrollOffsets();
    var size = Kwo.Tooltip.elt.getDimensions();
    var top;
    var left;
    if(Kwo.Tooltip.followMouse) {
      top = (Event.pointerY(e) + 20);
      left = (Event.pointerX(e) + 20);
      if (left + size["width"] > dim["width"] + pos["left"]) {
        left -= (left + size["width"]) - (dim["width"] + pos["left"]) + 5;
      }
      if (top + size["height"] > dim["height"] + pos["top"]) {
        top -= size["height"] + 40;
      }
    }
    else {
      var offset = Kwo.Tooltip.anchor.cumulativeOffset();
      var anchorDim = Kwo.Tooltip.anchor.getDimensions();
      top = anchorDim["height"] + offset.top;
      left = anchorDim["width"] + offset.left;

      if (left + size["width"] > dim["width"] + pos["left"]) {
        left -= (left + size["width"]) - (dim["width"] + pos["left"]);
      }
      if (top + size["height"] > dim["height"] + pos["top"]) {
        top -= size["height"] + anchorDim["height"];
      }
    }


    Kwo.Tooltip.elt.setStyle({"top": top + "px", "left": left + "px"});
  }

};








Kwo.Editor = Class.create({

  "doc": null,
  "iframe": null,
  "range": null,
  "selection": null,
  "src": null,
  "version": 1.1,
  "win": null,

  initialize: function(name) {
    if (!("execCommand" in window.document)) return ;
    var actions = {"bold": false, "italic": false, "underline": false,
                   "increasefontsize": false, "indent":true,"outdent":true,
                   "insertorderedlist": false, "insertunorderedlist": false,
                   "createlink": false, "insertimage": false, "paste": false,
                   "removeformat": false};
    this.src = $(name);
    this.src.hide();
    this.iframe = new Element("iframe", {designmode: "on", name: "_" + name, id: "_" + name});
    this.iframe.setStyle({height: this.src.getStyle("height"), width: this.src.getStyle("width")});
    this.iframe.addClassName("richtext");
    this.src.insert({after: this.iframe});
    if (Prototype.Browser.IE) {
      this.win = window.frames["_" + name];
      this.doc = this.win.document;
    }
    else {
      this.win = this.iframe.contentWindow;
      this.doc = this.iframe.contentDocument;
    }
    if (!Prototype.Browser.Gecko) {
      this.doc.designMode = "on";
    }
    this.doc.open("text/html");
    this.doc.write("<html><head><style>"
                   + "BODY { background:" + this.src.getStyle("background-color") + "; cursor:text; height:100%; "
                   + "       border:none; color:#777; font-family:monospace; margin:0; padding:0 4px; }"
                   + "BLOCKQUOTE { border-left:2px solid #eee; padding-left:4px; margin-left:4px; }"

                   + "</style></head><body></body></html>");
    this.doc.close();
    if (Prototype.Browser.Gecko) {
      this.doc.designMode = "on";
    }
    if (this.src.getValue().length >= 1) {
      this.doc.body.innerHTML = this.src.getValue();
    }
    if (Prototype.Browser.Gecko || Prototype.Browser.WebKit) {
      this.doc.execCommand("styleWithCSS", false, false);
    }
    this.iframe.observe("mouseout", this.onStore.bindAsEventListener(this));
    if (this.doc.addEventListener) {
      this.doc.addEventListener("keyup", this.onStore.bindAsEventListener(this), false);
    }
    else {
      this.doc.attachEvent("onkeyup", this.onStore.bindAsEventListener(this));
    }
    var toolbar = new Element("div").setStyle({width: this.src.getStyle("width")});
    toolbar.addClassName("kwo-toolbar");
    this.src.insert({after: toolbar});
    var img;
    for (key in actions) {
      if ((Prototype.Browser.IE ||  Prototype.Browser.WebKit) &&
          key == "increasefontsize") continue ;
      img = new Element("img", {src: "/app/core/pix/editor/" + key + ".png"});
      img.observe("click", this.exec.bind(this, key, actions[key]));
      toolbar.insert(img);
    };
  },

  onStore: function() {
    var source = this.doc.body.innerHTML;
    source = source.replace(/<br class\="webkit-block-placeholder">/gi, "<br />");
    source = source.replace(/<span class="Apple-style-span">(.*)<\/span>/gi, "$1");
    source = source.replace(/ class="Apple-style-span"/gi, "");
    source = source.replace(/ style="">/gi, "");
    source = source.replace(/<span style="font-weight: bold;">(.*)<\/span>/gi, "<strong>$1</strong>");
    source = source.replace(/<span style="font-style: italic;">(.*)<\/span>/gi, "<em>$1</em>");
    source = source.replace(/<br>/gi, "<br />");
    source = source.replace(/<br \/>\s*<\/(h1|h2|h3|h4|h5|h6|li|p)/gi, "</$1");
    source = source.replace(/<b(\s+|>)/g, "<strong$1");
    source = source.replace(/<\/b(\s+|>)/g, "</strong$1");
    source = source.replace(/<i(\s+|>)/g, "<em$1");
    source = source.replace(/<\/i(\s+|>)/g, "</em$1");
    source = source.replace(/(<[^\/]>|<[^\/][^>]*[^\/]>)\s*<\/[^>]*>/gi, "");
    source = source.replace(/\.\.\/doc\//g, "/doc/");
    this.src.value = source;
    //this.log();
  },

  exec: function(name, value) {
    if (name == "createlink") {
      if (value == false) {
        this.saveRange();
        new Kwo.Prompt({title: "Adresse du site ?", prefix: "http://"}, this.exec.bind(this).curry(name));
        return ;
      }
      if (!Object.isString(value) || value.legnth < 5) return ;
      if (!(value.toLowerCase().startsWith("http://") || value.toLowerCase().startsWith("https://"))) {
        value = "http://" + value;
      }
      if (value.toLowerCase().startsWith("http://http://")) {
        value = value.substr(7);
      }
      this.restoreRange();
      if (Prototype.Browser.IE && this.range) {
        this.range.select();
      }
      this.doc.execCommand(name, false, value);
    }
    else if (name == "paste") {
      if (value == false) {
        this.saveRange();
        var d = new Kwo.Dialog("/core/editor.paste", {});
        var that = this;
        d.onSubmit = function (elt) {
          that.exec(name, $F("input-paste"));
          d.close();
        };
//        d.close();
//        d = null;
        return ;
      }
      this.restoreRange();
      this.insertHTML(value.replace(/\n/g, "<br/>"));
    }
    else if (name == "insertimage") {
      if (value == false) {
        this.saveRange();
        new Kwo.FileDialog(this.exec.bind(this));
        return ;
      }
      this.restoreRange();
      this.insertHTML('<img src="/' + value + '" />');
    }
    else {
      this.win.focus();
      this.doc.execCommand(name, false, value);
    }
    if (Prototype.Browser.Gecko || Prototype.Browser.WebKit) {
      this.win.getSelection().collapseToEnd();
    }
    this.onStore();
  },

  saveRange: function() {
    if (Prototype.Browser.IE) {
      this.range = null;
      if (this.doc.selection.createRange().text.length >= 1) {
        this.range = this.doc.selection.createRange();
      }
    }
    else if (Prototype.Browser.Gecko) {
      this.selection = this.win.getSelection();
      this.range = this.selection.getRangeAt(0).cloneRange();
//      console.log(this.range);
    }
  },

  restoreRange: function() {
    this.win.focus();
    if (!Prototype.Browser.Gecko) return ;
    var selection = this.win.getSelection();
    selection.removeAllRanges();
    if (this.range) {
      selection.addRange(this.range);
    }
  },

  insertHTML: function(content) {
    this.win.focus();
    if (Prototype.Browser.IE) {
      if (this.range === null) {
        this.range = this.doc.selection.createRange();
      }
      this.range.pasteHTML(content);
      this.range.collapse(false);
      this.range = null;
    }
    else {
      this.doc.execCommand("insertHTML", false, content);
    }
  },

  log: function() {
    console.log(this.doc.body.innerHTML);
    console.log(this.src.value);
  }

});

Kwo.Layer = function() {
  var args = $A(arguments);
  var type = args.shift();
  var name = args.shift().toLowerCase();
  var code = type + ":" + name;
  if (!(code in Kwo.Layers)) {
    Kwo.Layers[code] = Class.create(Kwo[type.ucfirst()], Kwo.Handlers[name]);
  }
//  console.log(code);
/*  var that = {initialize: function($super) {
    $super.apply(this, args);
  }};*/
  return new (Class.create(Kwo.Layers[code],
                           {initialize: function($super) {
                             $super.apply(this, args);
                           }}));
}

Kwo.Dialog = Class.create({

  "args": null,
//  "bind": null,
  "className": null,
  "width": null,
  "height": null,
  "layout": null,
  "name": null,
  "opts": null,
  "overlay": null,
  "shadow": null,
  "support": null,

  "scroll": {},

  initialize: function(paint_method, args, opts) {
    opts = opts || {};
    this.args = args || this.args;
    if (this.opts === null) {
      this.opts = opts;
    }
    this.name = this.opts["name"] || this.name || "dialog";
    this.className = this.opts["className"] || this.className || "";
    if (this.layout) {
      this.className +=  "layout-" + this.layout;
    }
    this.width = this.opts["width"] || this.width || 500;
    this.height = this.opts["height"] || this.height || 300;
    if (this.overlay === null) {
      this.overlay = new Element("div").setStyle("display:none; position:absolute; top:0; left:0; opacity:0.2;").addClassName("dialog-overlay");
      this.shadow = new Element("div").setStyle("display:none; position:absolute; top:0; left:0;").addClassName("dialog-shadow kwo-layer");
      this.support = new Element("div").setStyle("display:none;");
      this.support.addClassName("dialog-support dialog-" + this.name + " " + this.className);
      var cross = new Element("A", {"href": "javascript:;"}).addClassName("dialog-close");
//      if (this.opts["noclose"] != 1 && window["_scope"] != "back") {
      if (this.opts["noclose"] != 1) {
        var that = this;
        this.shadow.appendChild(cross).observe("click", function () {
          that.close();
        });
        cross.observe("mousedown", function(evt) {
          Event.stop(evt);
        });
      }
      /*if (Prototype.Browser.IE) {
        this.place();
      }*/

      if (Kwo.dialogs.length < 1) {
        if (Prototype.Browser.Gecko) {
          this.scroll["x"] = window.pageXOffset;
          this.scroll["y"] = window.pageYOffset;
        }
        Event.observe(document, "keyup", this.onEscape.bindAsEventListener(this));
/*        Event.observe(document, "scroll", this.onScroll); */
        document.documentElement.style.overflow = "hidden";
/*        console.log(document.body.style.overflow); */
      }
      /*if (!Prototype.Browser.IE) {
        this.place();
      }*/
      this.place();
      document.body.appendChild(this.overlay);
      document.body.appendChild(this.shadow);
      this.shadow.appendChild(this.support);
      if (this.opts["noclose"] != 1) {
        this.overlay.observe("click", this.close);
      }
/*      if (Kwo.isBack() && window["_scope"] == "back") {
        new Draggable(this.shadow,
                      {starteffect: Prototype.emptyFunction,
                       endeffect: Prototype.emptyFunction});
//        new Draggable(this.support,
//                      {starteffect: Prototype.emptyFunction,
//                       endeffect: Prototype.emptyFunction,
//                       snap:[0,0]});
//        cross.style.zIndex++;
      }*/
    }
//    this.bind = this.place.bindAsEventListener(this);
    Event.observe(window, "resize", Kwo.onViewportChange);
    Event.observe(document, "MozScrollAreaChanged", Kwo.onViewportChange);
    Kwo.setDialog(this);
    if (Prototype.Browser.IE && navigator.userAgent.indexOf("MSIE 6") > -1) {
      $$("SELECT").invoke("hide");
    }
    this.support.update();
    if (Object.isFunction(paint_method)) {
      paint_method.call(this, this.args);
    }
    else if (!Object.isUndefined(paint_method)) {
      Kwo.exec(paint_method, this.args, {"async": true, "container": this.support});
    }
    $(this.overlay, this.shadow, this.support).invoke("show");
    if ("onAfterPlace" in this) {
      this.onAfterPlace();
    }
    cross.focus();
    if (false && window["_gaq"]) {
      _gaq.push(["_trackEvent", "dialog", this.name]);
    }
  },

  onScroll: function(event) {
//    console.log(event);
  },

  onEscape: function (event) {
    if (event.keyCode == Event.KEY_ESC) {
/*      var dialog = Kwo.getDialog();
      if (dialog.opts["noclose"] == 1) return ;
      event.stopPropagation();
      dialog.close();*/
      if (this.opts["noclose"] == 1) return ;
      event.stopPropagation();
      this.close();
    }
  },

  place: function () {
    var dimensions = document.viewport.getDimensions();
    var offsets = document.viewport.getScrollOffsets();
    var height = this.height;
    if (Object.isString(height) && height.endsWith("%")) {
      height = height.substr(0, height.length - 1);
      height = parseInt(dimensions.height * height / 100);
    }
    var dh = height;
    if (dh >= dimensions.height) {
      dh = dimensions.height - 30;
    }
    var width = this.width;
    if (Object.isString(width) && width.endsWith("%")) {
      width = width.substr(0, width.length - 1);
      width = parseInt(dimensions.width * width / 100);
    }
//    console.log(width);
    var left = parseInt(offsets.left + ((dimensions.width - width)/ 2));
    var top = parseInt(offsets.top + ((dimensions.height - dh)/ 2));
    top = top < 0 ? 0 : top;
    left = left < 0 ? 0 : left;
//    top += 15;
//    var width = dimensions.width;
//    var height = dimensions.height;
    var oh = dimensions.height;
    if (Prototype.Browser.Gecko) {
      oh = document.documentElement.scrollHeight;
    }
    this.overlay.setStyle({"width": dimensions.width + "px",
                           "height": oh + "px",
                           "left": offsets.left + "px",
                           "top": offsets.top + "px"});
    this.shadow.setStyle({"width": width + "px",
                          "height": dh + "px",
                          "left": left + "px",
                          "top": top + "px"});
    this.support.setStyle({"width": width + "px",
                           "height": dh + "px"});
  },

  apply: function(value) {
    if (Object.isUndefined(this.callback)) alert(value);
    else if (Object.isElement(this.callback)) this.callback.value = value;
    else this.callback(value);
    this.close();
  },

  close: function() {
    var dialog = Kwo.getDialog();
    if (Object.isFunction(dialog.onBeforeClose)) {
      dialog.onBeforeClose();
    }
    dialog.shadow.remove();
    dialog.overlay.remove();
    if (Kwo.dialogs.length == 1) {
      if (Prototype.Browser.IE) {
        document.documentElement.style.overflow = "auto";
      }
      else {
        var dimensions = document.viewport.getDimensions();
        document.documentElement.style.overflowX = document.documentElement.scrollWidth > dimensions.width ? "scroll" : "auto";
        if (document.documentElement.scrollHeight > dimensions.height) {
          document.documentElement.style.overflowY = "scroll";
          // WORKAROUND
          if (Prototype.Browser.Gecko && dialog.scroll["y"] > 0) {
            window.scroll(dialog.scroll["x"],
                          dialog.scroll["y"]);
          }
        }
        else {
          document.documentElement.style.overflowY = "auto";
        }
      }
      //console.log({sw: document.documentElement.scrollWidth, dw: dimensions.width});
      if (Prototype.Browser.IE && navigator.userAgent.indexOf("MSIE 6") > -1) {
        $$("SELECT").invoke("show");
      }
      Event.stopObserving(document, "keyup", dialog.onEscape.bindAsEventListener(dialog));
    }
    Kwo.unsetDialog();
//    Kwo.unsetDialog(dialog.name);
    if (Object.isFunction(dialog.onAfterClose)) {
      dialog.onAfterClose();
    }
  }

});

Kwo.Widget = Class.create({

  "args": null,
  "bind": null,
  "className": null,
  "width": null,
  "height": null,
  "layout": null,
  "name": null,
  "opts": null,
  "overlay": null,
  "shadow": null,
  "support": null,

  initialize: function(paint_method, args, opts) {
    opts = opts || {};
    this.args = args || this.args;
    if (this.opts === null) {
      this.opts = opts;
    }
    this.name = this.opts["name"] || this.name || "widget";
    this.className = this.opts["className"] || this.className || "";
    if (this.layout) {
      this.className +=  "layout-" + this.layout;
    }
    this.width = this.opts["width"] || this.width || 500;
    this.height = this.opts["height"] || this.height || 300;
    if (!("y_position" in this.opts)
         || (this.opts["y_position"] != "top"
             && this.opts["y_position"] != "bottom")) {
      if (Object.isElement(this.elt)
          && document.viewport.getHeight() < this.elt.viewportOffset().top + this.height) {
        this.y_position = "top";
      }
      else {
        this.y_position = "bottom";
      }
    }
    else {
      this.y_position = this.opts["y_position"] || "bottom";
    }
    if (!("x_position" in this.opts)
         || (this.opts["x_position"] != "left"
             && this.opts["x_position"] != "right")) {
      if (Object.isElement(this.elt)
          && document.viewport.getWidth() < this.elt.viewportOffset().left + this.width) {
        this.x_position = "right";
      }
      else {
        this.x_position = "left";
      }
    }
    else {
      this.x_position = this.opts["x_position"] || "left";
    }
    if (this.overlay === null) {
      this.overlay = new Element("div").setStyle("display:none; opacity:0; position:absolute; top:0; left:0; background-color:black;").addClassName("widget-overlay");
      this.shadow = new Element("div").setStyle("display:none; position:absolute; top:0; left:0;").addClassName("widget-shadow kwo-layer");
      this.support = new Element("div").hide();
      this.support.addClassName("widget-support widget-" + this.name + " " + this.className);
      var cross = new Element("div").addClassName("dialog-close");
      if (Kwo.dialogs.length < 1) {
        Event.observe(document, "keyup", this.onEscape);
       // document.documentElement.style.overflow = "hidden";
      }
      this.place();
      document.body.appendChild(this.overlay);
      document.body.appendChild(this.shadow);
      this.shadow.appendChild(this.support);
      if (this.opts["noclose"] != 1) {
        this.overlay.observe("click", this.close);
      }
      if ("_scope" in window && window["_scope"] == "back") {
        new Draggable(this.shadow,
                      {starteffect: Prototype.emptyFunction,
                       endeffect: Prototype.emptyFunction});
        new Draggable(this.support,
                      {starteffect: Prototype.emptyFunction,
                       endeffect: Prototype.emptyFunction,
                       snap:[0,0]});
        cross.style.zIndex++;
      }
    }
    this.bind = this.place.bindAsEventListener(this);
    Event.observe(window, "resize", Kwo.onViewportChange);
    Kwo.setDialog(this);
    if (Prototype.Browser.IE && navigator.userAgent.indexOf("MSIE 6") > -1) {
      $$("SELECT").invoke("hide");
    }
    this.support.update();
    if (Object.isFunction(paint_method)) {
      paint_method.call(this, this.args);
    }
    else if (!Object.isUndefined(paint_method)) {
      Kwo.exec(paint_method, this.args, {async: true, container: this.support});
    }
    $(this.overlay, this.shadow, this.support).invoke("show");
//    $(this.shadow).focus();
    if ("onAfterPlace" in this) {
      this.onAfterPlace();
    }
  },

  onEscape: function (event) {
    if (event.keyCode == Event.KEY_ESC) {
      var dialog = Kwo.getDialog();
      if (dialog.opts["noclose"] == 1) return ;
      event.stopPropagation();
      dialog.close();
    }
  },

  place: function () {
    var scrolloffset = document.viewport.getScrollOffsets();
    var offset_top = this.y_position == "bottom" ? this.elt.getHeight() : -this.height;
    var offset_left = this.x_position == "left" ? 0 : -this.width + this.elt.getWidth();
    if (this.x_position == "right") {
      var border_right_width = parseInt(this.elt.getStyle("border-right-width"));
      var border_left_width = parseInt(this.elt.getStyle("border-left-width"));
      offset_left -= isNaN(border_right_width) ? 0 : border_right_width;
      offset_left -= isNaN(border_left_width) ? 0 : border_left_width;
    }
    var top = this.elt.viewportOffset()[1] + offset_top + scrolloffset.top;
    var left = this.elt.viewportOffset()[0] + offset_left + scrolloffset.left;
    var width = $(document.body).getWidth();
    var height = $(document.body).getHeight();
    this.overlay.setStyle({width: width + "px",
                           height: height + "px"});
    this.shadow.setStyle({width: this.width + "px",
                          height: this.height + "px",
                          left: left + "px",
                          top: top + "px"});
    this.support.setStyle({width: this.width + "px",
                           height: this.height + "px"});
  },

  apply: function(value) {
    if (Object.isUndefined(this.callback)) alert(value);
    else if (Object.isElement(this.callback)) this.callback.value = value;
    else this.callback(value);
    this.close();
  },

  close: function() {
    var dialog = Kwo.getDialog();
    dialog.shadow.remove();
    dialog.overlay.remove();
    if (Kwo.dialogs.length == 1) {
      //console.log({sw: document.documentElement.scrollWidth, dw: dimensions.width});
      if (Prototype.Browser.IE && navigator.userAgent.indexOf("MSIE 6") > -1) {
        $$("SELECT").invoke("show");
      }
      Event.stopObserving(document, "keyup", this.onEscape);
    }
//    Kwo.unsetDialog(dialog.name);
    Kwo.unsetDialog();
    if (Object.isFunction(dialog.onAfterClose)) {
      dialog.onAfterClose();
    }
  }

});

Kwo.Prompt = Class.create(Kwo.Dialog, {

  initialize: function($super, opts) {
    this.name = "prompt";
    this.className = "layout-hbox";
    this.opts = opts || {};
    if ("title" in this.opts && Object.isElement(this.opts["title"])) {
      this.opts["title"] = this.opts["title"].readAttribute("data-title");
    }
    if ("description" in this.opts && Object.isElement(this.opts["description"])) {
      this.opts["description"] = this.opts["description"].readAttribute("data-description");
    }
    if ("value" in this.opts && Object.isElement(this.opts["value"])) {
      this.opts["value"] = this.opts["value"].readAttribute("data-value");
    }
    this.height = 150;
    if ("rows" in this.opts) {
      this.height += this.opts["rows"] * 15;
    }
    $super(this.onDisplay);
  },

  onDisplay: function() {
    Kwo.exec("/core/dialog.prompt", this.opts,
             {container: this.support,
              callback: this.onDisplayCompleted.bind(this)});
  },

  onDisplayCompleted: function() {
    this.input = this.support.down(".text");
    if (Object.isElement(this.opts["onsucceed"])) {
      this.onSucceed = function () {
        this.opts["onsucceed"].value = this.input.getValue();
        this.close();
      }
    }
    this.support.down(".button-ok").observe("click", this.onSucceed.bind(this));
    this.support.down(".elt-link").observe("click", this.onCancel.bind(this));
  },

  onCancel: function() {
    this.close();
  },

  onSucceed: function() {
    alert(this.input.value);
  },

  getValue: function() {
    return this.input.getValue();
  }

});

Kwo.Class.Subscription = Class.create(Kwo.Dialog, {

 initialize: function($super, elt) {
   this.name = "subscription";
   this.className = "layout-hbox";
   this.width = 400;
   this.height = 300;
   this.args = {item_key: $(elt).readAttribute("data-item")};
   $super(this.onDisplay, this.args);
 },

 onDisplay: function(args) {
   Kwo.exec("/core/subscription.prompt", args,
            {container: this.support});
 },

 onSave: function(elt) {
   if (!Kwo.isAuth()) {
     var auth = new Kwo.Class.Auth();
     auth.onCallback = this.onSave.bind(this).curry(elt);
     return ;
   }
   Kwo.exec("/core/subscription.save", this.args,
            {callback: elt});
 }

});




Kwo.FileDialog = Class.create(Kwo.Dialog, {

  initialize: function($super, callback, opts) {
    this.name = "file";
    this.callback = callback;
    this.opts = opts || {};
    $super("/community/files.dialog", null);
  },

  "onUploadCompleted": function(file_path) {
    if (this.opts["mode"] == "upload") {
      this.apply(file_path);
    }
    else {
      this.refresh();
    }
  },

  "refresh": function() {
    this.support.innerHTML = "";
    Kwo.exec("/community/files.dialog", null,
             {container: this.support});
  },

  "preview": function(path) {
    path = "/" + path;
    if (path.indexOf(".jpg") > 0 || path.indexOf(".jpeg") > 0 ||
        path.indexOf(".png") > 0 || path.indexOf(".gif") > 0) {
      $("preview").hide();
      var img = new Image();
      img.onload = function() {
        var max = 200;
        $("preview").style.display = "block";
        $("preview").src = this.src;
        if (this.width <= max && this.height <= max) {
          $("preview").width = this.width;
          $("preview").height = this.height;
        }
        else if (this.width > max || this.height > max) {
          if (this.width > this.height) {
            this.width = max;
//            this.height = Math.ceil(this.height * max / this.width);
            delete (this.height);
          }
          else {
//            this.width = Math.ceil(this.width * (max / this.height));
            delete (this.width);
            this.height = max;
          }
        }
        $("preview").show();
        $("preview").update(this);
      };
      img.src = path;
    }
    else {
      $("preview").hide();
    }
  },

  "apply": function(path) {
    if (Object.isUndefined(this.callback)) {
      return alert(path);
    }
    else if (Object.isElement(this.callback)) {
      if ("name_only" in this.opts) {
        path = path.basename();
      }
      $(this.callback).value = path;
    }
    else if (Object.isFunction(this.callback)) {
      this.callback("insertimage", path);
    }
    this.close();
  }

});

Kwo.Class.Upload = Class.create(Kwo.Dialog, {

  initialize: function($super, callback, opts) {
    this.name = "upload";
    this.callback = callback;
    this.opts = opts || {};
    this.opts["width"] = 400;
    this.opts["height"] = 200;
    var args = {};
    if ("filter" in this.opts) {
      args["filter"] = this.opts["filter"];
    }
    $super("/core/upload.select", args);
  },

  onUploadCompleted: function(args) {
    if (Object.isString(args)) {
      this.apply(args);
    }
  },

  onBeforeSubmit: function(elt) {
    this.form = $(elt);
    if (this.form.down("INPUT[type=file]").value.blank()) {
      return ;
    }
    Kwo.exec("/core/upload.check",
             {file: this.form.down("INPUT[type=file]").value,
              replace: this.form.down("INPUT[type=checkbox]").checked ? 1 : 0,
              filter: this.opts["filter"]},
             {callback:this.onSubmit.bind(this)});
  },

  onSubmit: function(res) {
    if (res["error"] == 2) {
      return this.form.down("LABEL.upload-crush").show();
    }
    else if (res["error"] >= 1) {
//      return this.form.down("DIV.form-error").update(res["result"]["msg"]);
      return Kwo.error(res);
    }
    $(this.form, "loading-box").invoke("toggle");
    this.form.down("input[name=filter]").value = this.opts["filter"];
    this.form.action = "/core/upload";
    this.form.stopObserving("submit");
    this.form.down("DIV.form-error").hide();
    this.form.submit();
  },

  refresh: function(args) {
    alert(args["error"]);
    $("loading-box", this.form).invoke("toggle");
    this.form.reset();
  },

  apply: function(path) {
    if (Object.isUndefined(this.callback)) {
      return alert(path);
    }
    else if (Object.isElement(this.callback)) {
      var previous = $(this.callback).previous("INPUT[type=hidden]");
      if (!Object.isUndefined(previous)) {
        previous.value = path;
      }
      $(this.callback).value = path.basename();
    }
    else if (Object.isFunction(this.callback)) {
      this.callback(path);
    }
    this.close();
  }

});


Kwo.Class.Abuse = Class.create(Kwo.Dialog, {

  initialize: function($super, elt) {
    this.name = "abuse";
    this.className = "layout-hbox";
    this.width = 440;
    this.height = 330;
    this.args = {"item": $(elt).readAttribute("data-item")};
    $super(this.onDisplay, this.args);
  },

  onDisplay: function(args) {
    Kwo.exec("/abuse/abuse.compose", args,
             {"container": this.support});
  },

  onSubmit: function(elt) {
    elt = $(elt);
    Kwo.exec("/abuse/abuse.report", elt,
             {"disable": elt, 
              "callback": $("abuse-button")});
  }

});

Kwo.Handlers["date"] = {

  "initialize": function($super, elt, opts) {
    this.name = "date";
    this.className = "layout-hbox";
    this.opts = opts || {};
    //this.width = this.opts["has_time"] == true ? 440 : 238;
    //this.height = 330;
    this.width = this.opts["has_time"] == true ? 440 : 360;
    this.height = 340;
    this.elt = $(elt);
    if ("periods" in this.opts) {
      this.opts["periods"] = Object.toJSON(this.opts["periods"]);
    }
    $super(this.onDisplay, elt);
  },

  onAfterPlace: function() {
    this.listeners = {};
    var that = this;
    this.listeners["change"] = function(event) {
      var target = Event.element(event);
      if (target.hasAttribute("data-change")) {
        that.onDisplay(target.readAttribute("data-change"));
        event.stop();
      }
    };
    this.listeners["click"] = function(event) {
      var target = Event.element(event);
      if (target.hasAttribute("data-date")) {
        if (that.opts["has_time"]) {
          var datetimeinput = that.support.down("[name=\"datetime\"]");
          datetimeinput.value = target.readAttribute("data-date");
          that.support.select('a').invoke('removeClassName', 'selected');
          target.addClassName('selected');
        }
        else {
          that.onSelect(target.readAttribute("data-date"));
        }
        event.stop();
      }
      else if (target.hasAttribute("data-datetime")) {
        that.onSelect(target.readAttribute("data-datetime"));
        event.stop();
      }
      else if (target.hasAttribute("data-change")) {
        that.onDisplay(target.readAttribute("data-change"));
        event.stop();
      }
    };
    this.support.observe("click", this.listeners["click"]);
    this.support.observe("change", this.listeners["change"]);
  },

  onAfterClose: function() {
    this.support.stopObserving("click", this.listeners["click"]);
    this.support.stopObserving("change", this.listeners["change"]);
  },

  onDisplay: function(elt) {
    var v = Object.isElement(elt) ? $F(elt) : elt;
    this.opts["datetime"] = v;    
    Kwo.exec("/core/date.select", this.opts,
             {"container": this.support});
  },

  onSelect: function(datetime) {
    if (Object.isElement(this.elt)) {
      this.elt.value = datetime;
      if (this.elt.onchange != undefined && this.elt.onchange instanceof Function) {
        this.elt.onchange();
      }
      this.close();
      return ;
    }
    alert(datetime);
  }

};

Kwo.Datepicker = Class.create(Kwo.Dialog, Kwo.Handlers["date"]);

Kwo.Dialogs.Date = Class.create(Kwo.Dialog, Kwo.Handlers["date"]);

Kwo.Colorpicker = Class.create(Kwo.Dialog, {

  initialize: function($super, input, opts) {
    this.name = "color";
    this.input = input;
    opts = opts || {};
    this.width = 220;
    this.height = 180;
    $super(this.onDisplay);
  },

  onDisplay: function() {
    Kwo.exec("/core/dialog.colorpicker", null,
             {"container": this.support,
              "callback": function () {
                Kwo.col = new Kwo.Color();
              }});
  },

  put: function(value) {
    if ("goal" in this.opts) {
      if (this.opts["goal"] == "bgcolor") {
        Kwo.getEditor().setBgColor("#" + value);
      }
      else {
        Kwo.getEditor().setFgColor("#" + value);
      }
    }
    else {
      $(this.input).setValue(value);
    }
    this.close();
  }

});

Kwo.Color = Class.create({

  "initialize": function() {
    this.strhex = "0123456789ABCDEF";
    this.is_mouse_down = false;
    this.is_mouse_over = false;
  },

  "changeColor": function(color) {
    if ('#' == color.charAt(0)) {
      color = color.substring(1, color.length);
    }
    $("color_hex").setValue(color);
    $("show_color").setStyle({"backgroundColor": "#" + color});
  },

  "dec2hex": function(n) {
    return this.strhex.charAt(Math.floor(n / 16)) + this.strhex.charAt(n % 16);
  },

  "getColor": function(e) {
    var x = e.offsetX ? e.offsetX : (e.target ? e.layerX-e.target.x : 0);
    var y = e.offsetY ? e.offsetY : (e.target ? e.layerY-e.target.y : 0);
    var width = $("color_picker").width / 6;
    var height = $("color_picker").height - 5;

    if ((x >= 0 && x <= 110) && (y >= 0 && y <= 5)) {
      var red = 255;
      var green = 255;
      var blue = 255;
    }
    else if ((x > 110 && x <= 220) && (y >= 0 && y <= 5)) {
    var red = 0;
      var green = 0;
      var blue = 0;
    }
    else {
      y -= 5;
      var red = (x >= 0) * (x < width) * 255
        + (x >= width) * (x < 2*width) * (2 * 255 - x * 255 / width)
        + (x >= 4 * width) * (x < 5 * width) * (-4 * 255 + x * 255 / width)
        + (x >= 5 * width) * (x < 6 * width) * 255;
      var blue = (x >= 2 * width) * (x < 3 * width) * (-2 * 255 + x * 255 / width)
        + (x >= 3 * width) * (x < 5 * width) * 255
      + (x >= 5 * width) * (x < 6*width) * (6 * 255 - x * 255 / width);
      var green = (x >= 0) * (x < width) * (x * 255 / width)
        + (x >= width) * (x < 3 * width) * 255
        + (x >= 3 * width) * (x < 4 * width) * (4 * 255 - x * 255 / width);

      var coef = (height - y) / height;

      red = 128 + (red - 128) * coef;
      green = 128 + (green - 128) * coef;
      blue = 128 + (blue - 128) * coef;
    }

    // mise à jour de la valeur hexa
    this.changeColor(this.dec2hex(red) + this.dec2hex(green) + this.dec2hex(blue));
  },

  "updateHexa": function(value) {
    $("show_color").style.backgroundColor = "#" + value;
  },

  "do": function() {
    $("color_container").update("coucou");
  }

});

Kwo.Class.Snippet = Class.create(Kwo.Dialog, {

  initialize: function($super, code) {
    this.name = "snippet";
    this.className = "layout-hbox";
    if (Object.isElement(code)) {
      code = code.readAttribute("data-code");
    }
    this.args = {"code": code};
    this.width = 550;
    this.height = 400;
    $super(this.onDisplay);
  },

  onDisplay: function() {
    Kwo.exec("/core/snippet", this.args,
             {"container": this.support});
  }

});

Kwo.Class.Faq = Class.create(Kwo.Dialog, {

  initialize: function($super, elt) {
    this.name = "faq";
    this.className = "layout-hbox";
    this.args = {"code": $(elt).readAttribute("data-code")};
    this.width = 600;
    this.height = 450;
    $super("/faq/faq", this.args);
  },

  onRewind: function() {
    this.support.down("div").scrollTop = 0;
  },

  onSelect: function(id) {
    var pos = $("component-" + id).positionedOffset();
    this.support.down("DIV.layout-hbox-content").scrollTop = pos[1];
  }

});


Kwo.Composer.Feed = Class.create(Kwo.Dialog, {

  initialize: function($super, elt) {
    this.name = "feed";
    this.className = "layout-hbox";
    this.args = {"url": $(elt).readAttribute("data-url")};
    this.width = 400;
    this.height = 340;
    $super(this.onDisplay, this.args);
  },

  onDisplay: function() {
    Kwo.exec("/core/feed.prompt", this.args,
             {"container": this.support});
  }

});

Kwo.Class.Valuation = Class.create(Kwo.Dialog, {

  initialize: function($super, args) {
    this.name = "valuation";
    this.className = "layout-hbox";
    this.args = {"item": $(args).readAttribute("data-item")};
    this.width = 700;
    this.height = 400;
    $super(this.onDisplay, this.args);
  },

  onSubmit: function(elt) {
    Kwo.exec("/rating/valuation.save",
             [elt, {"item": this.args["item"]}],
             {"disable": elt,
              "callback": this.onCallback.bind(this)});
  },

  onCallback: function(res) {
    if (Kwo.hasError(res)) return Kwo.error(res);
    this.close();
    Kwo.reload();
  },

  bindStars: function() {
    $$(".valuation-stars")[0].observe("click", this.onClick);
  },

  onClick: function(evt) {
    var elt = evt.element();
    if (!elt.hasClassName("star")) return ;
    elt.up("TR").select("IMG.star").each(function (img) {
      img.src = img.src.sub("-on", "-off");
    });
    elt.src = elt.src.sub("-off", "-on");
    elt.previousSiblings().each(function (img) {
      img.src = img.src.sub("-off", "-on");
    });
    elt.up("TR").down("SPAN").update(elt.readAttribute("data-value") + " / 5");
    elt.up("TR").down("INPUT").value = elt.readAttribute("data-value");
  },

  onDisplay: function() {
    Kwo.exec("/rating/valuation", this.args,
             {"container": this.support});
  }

});


Kwo.Class.Geolocator = Class.create(Kwo.Dialog, {
  map: null,
  geo: null,
  marker: null,

  initialize: function($super, elt) {
    this.name = "geolocator";
    this.elt = $(elt);
    if (this.elt.readAttribute("data-point")) {
      this.args = {"point": this.elt.readAttribute("data-point").split(",")};
    }
    else {
      this.args = {"address": this.elt.readAttribute("data-address")};
    }
    this.width = 640;
    this.height = 530;
    $super(this.onDisplay, null);
  },

  onDisplay: function() {
    Kwo.exec("/core/geolocator", this.args,
             {"container": this.support,
              "callback": this.onDisplayCompleted.bind(this) })
  },

  onDisplayCompleted: function() {
    if (typeof GBrowserIsCompatible == "function") {
      this.onCallback();
    }
    else {
      var gmk = this.elt.readAttribute("data-gmk");
      Kwo.load("http://maps.google.com/maps?file=api&v=2&sensor=false&key=" + gmk + "&async=2&callback=Kwo.dialog.onCallback");
    }
  },

  setPoint: function() {
    if (this.marker) {
      var point = this.marker.getPoint();
      var result = {latitude:point.y, longitude:point.x, zoom:this.map.getZoom()}
      this.setValue(result);
    }
    else {
      alert("Vous n’avez pas choisi de point");
    }
  },

  setValue: function(point) {
    alert(Object.toJSON(point));
    this.close();
  },

  onCallback: function () {
    document.body.onunload = GUnload;
    if (GBrowserIsCompatible()) {
      this.map = new GMap2(document.getElementById("map"));
      this.geo = new GClientGeocoder();
      this.map.addMapType(G_PHYSICAL_MAP);
      var control = new GMapTypeControl();
      this.map.addControl(control);
      this.map.addControl(new GLargeMapControl3D());
      this.map.enableScrollWheelZoom();
      GEvent.addListener(this.map, "zoomend", this.changeZoom.bind(this));
      GEvent.addListener(this.map, "click", this.addOverlay.bind(this));
      if (this.args.point && this.args.point.length == 3) {
        var point = new GLatLng(this.args.point[0], this.args.point[1]);
        this.map.setCenter(point, parseInt(this.args.point[2]));
        this.addPoint(point);
      }
      else if (this.args.address) {
        this.map.setCenter(new GLatLng(46.227638, 2.213749), 5);
        this.searchAddress(this.args.address);
      }
      else {
        this.map.setCenter(new GLatLng(46.227638, 2.213749), 5);
      }
    }
  },

  searchAddress: function (address) {
    this.geo.getLatLng(address, this.addPoint.bind(this));
  },

  addOverlay: function (overlay, point) {
    this.addPoint(point);
  },

  addPoint: function (point) {
    this.map.clearOverlays();
    this.marker = new GMarker(point, {draggable: true});
    GEvent.addListener(this.marker, "dragend", this.moveOverlay.bind(this));
    this.map.addOverlay(this.marker);
    this.map.panTo(new GLatLng(point.y, point.x));
  },

  moveOverlay: function () {
    if (this.marker) {
      var point = this.marker.getPoint();
      this.map.panTo(point);
    }
  },

  changeZoom: function () {
    if (this.marker) {
      //var point = this.marker.getPoint();
    }
  }

});


Kwo.Elt = {

  onImageCallback: function(path) {
    this.value = path.basename();
    this.hide();
    this.next().src = "/" + path;
    this.next().show();
  },

  onTagAdd: function(elt) {
    if (elt.value.blank() || elt.value == elt.title) return ;
    var tags = elt.getValue().stripTags().split(",");
    var input = elt.previous(0).getValue().split(",");
    elt.clear();
    var tag, span, spans = elt.next("DIV");
    for (var i = 0; i < tags.length; i++) {
      tag = tags[i].strip();
      if (tag.blank() || input.indexOf(tag) != -1) continue ;
      span = new Element("SPAN", {onclick: "Kwo.Elt.onTagEdit($(this))"}).update(tag);
      spans.insert(span);
    }
    Kwo.Elt.onTagStore(spans);
  },

  onTagEdit: function(elt) {
    var spans = elt.up();
    spans.previous("INPUT").value = elt.innerHTML;
    elt.remove();
    Kwo.Elt.onTagStore(spans);
  },

  onTagFocus: function(elt) {
    elt = $(elt);
    if (elt.value == elt.title) {
      elt.clear();
    }
    elt.next().show()
  },

  onTagStore: function(elt) {
    var tags = [];
    elt.select("SPAN").each(function (span) {
      tags.push(span.innerHTML);
    });
    elt.previous("INPUT", 1).value = tags.join(",");
  },

  onTooltipHide: function(elt) {
    elt.up("DIV.elt").select("DIV.elt-tooltip")[0].hide();
  },

  onTooltipShow: function(elt) {
    var tooltip = elt.up("DIV.elt").select("DIV.elt-tooltip")[0];
    if (!tooltip.hasClassName("elt-widget")) {
      tooltip.addClassName("elt-widget");
      var pointer = new Element("DIV").addClassName("elt-tooltip-pointer-down elt-widget");
      pointer.insert(new Element("DIV").addClassName("elt-tooltip-pointer-down-inner"));
      tooltip.insert(pointer);
    }
    var pos = elt.viewportOffset();
    var dim = tooltip.getDimensions();
    var top  = pos["top"] - (dim["height"] + 16);
    var left = (pos["left"] - Math.ceil(dim["width"] / 2)) + 5;
    tooltip.setStyle({"top": top + "px", "left": left + "px"});
    tooltip.show();
  },

  onNodeSelect: function(elt, target_id) {
    elt = $(elt);
    var target = $(target_id);
    if (elt.getValue() == 0) {
      target.length = 0;
      target.update('<option value="0">-</option>');
      return ;
    }
    Kwo.exec("/tree/node.children", {node_id: elt.getValue()},
             {callback: target});
  }

};

Kwo.Currency = {

  onSelect: function(arg) {
    $("kwo-currencies").toggle();
    var pos = $(arg).cumulativeOffset();
    $("kwo-currencies").setStyle({top: (pos[1] + $(arg).getHeight()) + "px",
                                  left: pos[0] + "px"});
  },

  onSubmit: function(code) {
    $("kwo-currencies").hide();
    Kwo.exec("/core/currency.set", {"code": code}, {callback: Kwo.reload});
  }

};

Object.extend(String.prototype, {

  intval: function() {
    return this.length < 1 ? 0 : parseInt(this);
  },

  toggle: function() {
    return parseInt(this) == 1 ? "0" : "1";
  },

  ucfirst: function() {
   return this.charAt(0).toUpperCase() + this.substring(1);
  },

  basename: function() {
    return this.match(/[^\/\\]+$/);
  },

  dirname: function() {
    return this.match(/(.*)[\/\\]/)[1];
  },

  isImage: function() {
    return this.match(/\.(gif|jpeg|jpg|png)$/i);
  },

  stripAccents: function() {
    var exps = [ /[\xC0-\xC2]/g, /[\xE0-\xE2]/g,
                 /[\xC8-\xCA]/g, /[\xE8-\xEB]/g,
                 /[\xCC-\xCE]/g, /[\xEC-\xEE]/g,
                 /[\xD2-\xD4]/g, /[\xF2-\xF4]/g,
                 /[\xD9-\xDB]/g, /[\xF9-\xFB]/g ];
    var chars = ["A","a","E","e","I","i","O","o","U","u"];
    var s = this, l = exps.length;
    for (var i = 0; i < l; i++) {
      s = s.replace(exps[i], chars[i]);
    }
    return s;
  },

  toFunction: function() {
    var parts = this.split(".");
    var func = window;
    for (var i = 0; i < parts.length; i++) {
      func = func[parts[i]];
    }
    return func;
  }

});

Element.addMethods({

  turn: function(elt) {
    elt = $(elt);
    var img;
    if (elt.tagName.toUpperCase() == "IMG") {
      img = elt;
    }
    else {
      img = elt.down("IMG");
      if (Object.isUndefined(img)) return elt;
    }
    if (img.src.match("-off.")) {
      img.src = img.src.sub("-off.", "-on.", 1);
    }
    else {
      img.src = img.src.sub("-on.", "-off.", 1);
    }
    return elt;
  },

  inModal: function(elt) {
    elt = $(elt);
    return elt.up(".dialog-support") != undefined && elt.up(".deck") == undefined;
  }

});

