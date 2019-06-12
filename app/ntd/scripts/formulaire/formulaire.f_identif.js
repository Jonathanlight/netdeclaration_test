NTD.f_identif = {

  onSelectOGA: function(elt) {
    var values = $(elt).value.split(',');
    $('f_identif_OGA').value   = values[0];
    $('f_identif_OGA').onchange();
  }
  
  
};