
Kwo.Composer.Comment = Class.create(Kwo.Dialog, {

  initialize: function($super, elt) {
    this.name = "comment";
    this.className = "layout-hbox";
    this.width = 600;
    this.height = 400;
    this.elt = $(elt);
    this.args = {"item_key": this.elt.readAttribute("data")};
    $super(this.paint);
  },
  
  paint: function() {
    Kwo.exec("/comment/comment.compose", this.args, 
             {container: this.support});
  },

  onSubmit: function(args) {
    Kwo.exec("/core/item.comment", args,
             {disable:true, callback: this.onCallback.bind(this)});
  },

  onCallback: function(res) {
    if (res["error"] == 401) return new Kwo.Class.Auth();
    if (Kwo.hasError(res)) return Kwo.error(res);
    Kwo.exec("/comment/comments", this.args,
             {container: this.elt.up(".widget-comments")});
    this.close();
  }

});


Kwo.Comment = {

  onSwitchPage: function(elt, offset) {
    var widget = $(elt).up(".widget-comments")
    var args = {};
    args["offset"] = offset;
    args["item_key"] = widget.readAttribute("data");
    Kwo.exec("/comment/comments", args,
             {container: widget});
  }

};