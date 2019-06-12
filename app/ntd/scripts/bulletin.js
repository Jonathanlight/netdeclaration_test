NTD.Bulletin = {

  "onValidate": function(elt) {
    elt = $(elt)
    Kwo.exec("/bulletin.validate", {"key": elt.readAttribute('data-key')}, {"callback": NTD.Bulletin.onValidateCallback});
  },

  "onValidateCallback": function(resp) {
    resp = new kwo.Response(resp);
    if (resp.hasError()) return resp.alert();
    Kwo.reload();
  }

};
