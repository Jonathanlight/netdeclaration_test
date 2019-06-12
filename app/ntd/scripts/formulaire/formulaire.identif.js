NTD.Identif = {
  code: null,

  p: function(method, args) {
    return NTD.Identif.invoke(method, args);
  },

  t: function(method, args) {
    return NTD.Identif.invoke(method, args);
  },

  f: function(method, args) {
    return NTD.Identif.invoke(method, args);
  },

  pField: function(name) {
    return NTD.Identif.field(name);
  },

  tField: function(name) {
    return NTD.Identif.field(name);
  },

  fField: function(name) {
    return NTD.Identif.field(name);
  },

  init: function() {
    if (!NTD.Identif.code) {
      var code = $($(document).body).down('[data-identif]');
      if (code == 'undefined') {
        console.warn('unspecified identif code');
        return ;
      }
      NTD.Identif.code = code.getAttribute('data-identif');
    }
  },

  invoke: function(method, args) {
    NTD.Identif.init();

    if (NTD[NTD.Identif.code] != 'undefined' && NTD[NTD.Identif.code][method] != "undefined") {
      return NTD[NTD.Identif.code][method].apply(null, args);
    }
    else {
      console.warn('undefined method '+NTD.Identif.code+'@'+method);
      return ;
    }
  },

  field: function(name) {
    NTD.Identif.init();

    if (NTD.Identif.code != null) {
      return NTD.Identif.code + '_' + name;
    }
    else {
      console.warn('undefined identif code for field '+name);
      return name;
    }
  }
};
