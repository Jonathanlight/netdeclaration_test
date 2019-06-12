
Kwo.Dir = {

  addDir: function()   {
    if (!(dir_name=prompt("Nom du nouveau répertoire ?",""))) return ;
    Kwo.exec("/back/file/dir.add_dir", {"path": _path, "dir_name": dir_name},
             {callback: Kwo.Dir.view});
  },

  addFile: function() {
    $("form_upload").submit();
  },

  compress: function() {
    if (!confirm("Etes vous sur de vouloir créer une archive de ce répertoire\n<" + _path + "> ?")) return ;
    Kwo.exec("/back/file/dir.compress", {"path": _path},
            {callback: Kwo.Dir.view});
  },

  filter: function() {
    if (!window.keyword) window.keyword = "";
    window.keyword = prompt("Mot clef ?", window.keyword);
    Kwo.go("/back/file/dir", 
           {"path":_path, "keyword":keyword});
    window.keyword = keyword;
  },

  check: function ()   { 
    Kwo.exec("/back/file/file.check", 
             {"remote_file_path": $F("remote_file_path"), "path": _path}, 
             {callback: Kwo.Dir.onCheckCallback});
  },

  onCheckCallback: function (res) {
    if (Kwo.hasError(res)) return Kwo.error(res);
    if (res["result"]["has_file"] == 1 && 
        !confirm("Etes vous sûr de vouloir écraser le fichier distant ?")) return ;
    Kwo.Dir.addFile();
  },

  selectFile: function() {
    if (window._file_path.length >= 2) {
      $("file_box", "upload_box").invoke("toggle");
    }
    else {
      $("upload_box").toggle(); 
    }
  },

  unlink: function() {
    if (!confirm("Etes vous sur de vouloir supprimer "
                 +"le répertoire\n<"+_path+">\n ainsi que "
                 +"les fichiers qu'il contient ?")) return ;
    Kwo.exec("/back/file/dir.unlink", {"path": _path},
             {callback: Kwo.Dir.view});
  },

  view: function(res) { 
    var args = {};
    if (res === undefined) {
      args["path"] = _path;
      if ($("layout")) {
        args["layout"] = $F("layout");
      }
    }
    else if (Object.isString(res)) {
      args["path"] = res;
    }
    else if (Object.isElement(res)) {
      args["path"] = res.readAttribute("data-path");
    }
    else { 
      if (Kwo.hasError(res)) return Kwo.error(res);
      args["path"] = res["result"]["path"];
    }
    Kwo.go("/back/file/dir", args);
  },

  refresh: function(res) {
    if (res != undefined && Kwo.hasError(res)) return Kwo.error(res);
    Kwo.Dir.view();
  }

};

Kwo.File = {

  "download": function() {
    Kwo.go("/back/file/file.download", {"file_path": _file_path});
  },

  "edit": function() {
    Kwo.go("/back/file/content_edit", {"file_path":_file_path});
  },

  "encode": function() {
    Kwo.exec("/back/file/file.encode", {"file_path":_file_path}, {callback: Kwo.File.view});
  },

  "move": function(node) {
    //    if (!confirm("Etes vous sûr de vouloir déplacer le fichier <"+_selected_file_path+">\ndans ce répertoire ?")) return ;
    if (!confirm(node.getAttribute("title").ucfirst()+" ?")) return ;
    Kwo.exec("/back/file/file.move", {"path": _path});
  },

  "rename":  function() {
    var new_filename;
    if (new_filename = prompt("Nom du nouveau fichier ?", _filename)) {
      if (new_filename != _filename) {
	Kwo.exec("/back/file/file.rename",
                 {"file_path": _file_path, "new_filename": new_filename},
                 {callback: Kwo.File.view});
      }
    }
  },

  "preview": function(path) {
    var thumb = $("thumb");
    if (Object.isElement(path)) {
      path = path.getAttribute("data-path");
    }
    $("dim").update("");
    $("file_box", "upload_box").invoke("hide");
    $("file_box").show();
    window._file_path = path;
    $("file_path").value = path;
    if (path.indexOf(".jpg") > 0 || path.indexOf(".jpeg") > 0 || 
        path.indexOf(".png") > 0 || path.indexOf(".gif") > 0) {
      thumb.hide();
      var img = new Image();
      img.onload = function() {
        var max = 240;
        $("dim").innerHTML = this.width + "x" + this.height;
        thumb.src = this.src; 
        if (this.width <= max && this.height <= max) {
          thumb.setStyle({width: this.width + "px", height: this.height + "px"});
        }
        else {
          if (this.width > max) {
            thumb.setStyle({height: Math.ceil(this.height * (max / this.width)) + "px", width: max + "px"});
          } 
        }
        thumb.show();
      };
      img.src = path;
    }
    else {
      thumb.hide();
    }
  },

  "resize": function() {
    Kwo.exec("/back/file/img.resize",
             {"file_path": _file_path, "width": $F("width"), "height": $F("height")},
             {callback: Kwo.File.view});
  },

  "rotate": function() {
    var angle = "90";
    if ($("angle180").checked == true) angle = 180; 
    Kwo.exec("/back/file/img.rotate",
              {"file_path": _file_path, "angle": angle});
  },

  "select": function() {
    Kwo.exec("/back/file/file.select", {"file_path": _file_path});
  },

  "unlink": function() { 
    if (!confirm("Etes vous sûr de vouloir supprimer ce fichier ?")) return ;
    $("file_box").hide();
    Kwo.exec("/back/file/file.unlink", {"file_path": _file_path},
             {callback: Kwo.Dir.view});
  },

  "unzip": function() { 
    if (!confirm("Etes vous sûr de vouloir décompresser ce fichier ?")) return ;
    Kwo.exec("/back/file/file.unzip", {"file_path": _file_path},
             {callback: Kwo.Dir.refresh});
  },

  "view": function(res) {
    if (Object.isString(res)) {
      return Kwo.go("/back/file/file", {"file_path": res});
    }
    if (Kwo.hasError(res)) return Kwo.error(res);
    Kwo.File.view(res["result"]["file_path"]);
  }

};


/*
function File () {
  this.crop = function () {
    Kwo.exec("/back/file/crop", "file_path="+_file_path+"&x1="+x1+"&y1="+y1+"&x2="+x2+"&y2="+y2);
  }
  this.cropselect = function () {
    window.location = "/back/file/img?file_path="+_file_path;
  }
}
file = new File();
*/