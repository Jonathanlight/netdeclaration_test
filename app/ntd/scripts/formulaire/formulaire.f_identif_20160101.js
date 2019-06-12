NTD.f_identif_20160101 = {

  onSelectOGA: function(elt) {
    var values = $(elt).value.split(',');
    $('f_identif_20160101_OGA').value   = values[0];
    $('f_identif_20160101_OGA').onchange();
  }


};
