NTD.f_identif_20140320 = {

  onSelectOGA: function(elt) {
    var values = $(elt).value.split(',');
    $('f_identif_20140320_OGA').value   = values[0];
    $('f_identif_20140320_OGA').onchange();
  }


};
