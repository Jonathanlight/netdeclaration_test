
Formulaire.tva3310ca3g = {

  disable_forms: function(elt, num) {
    var itemsArray = $(elt).getAttribute('disable-forms-items'+num).split(',');
    var parents = $(elt).up('.form-ntd').select(".formulaire-page[data-label*='3310CA3G']");
    parents.each(function(parent) {
      if (!$(elt).checked) {
        parent.select('select, input, textarea').each(function(field) {
          if (itemsArray.indexOf(field.id) == -1) {
            field.removeAttribute('disabled');
          }
        });
      }
      else {
        if ($('formulairetype-annexes-box')) {
          $('formulairetype-annexes-box').select('input[type=checkbox]').each(function(field) {
            field.checked = false;
            field.onclick();
          });
        }
        parent.select('select, input, textarea').each(function(field) {
          if (itemsArray.indexOf(field.id) == -1) {
            field.writeAttribute('disabled', 'disabled');
            field.value = '';

            try{
              if (field.getAttribute("name").indexOf("_opts[") != -1) {
                return;
              }
              field.onchange();
            }
            catch(error){
              console.log(elt, error, field);
            }

          }
        });
      }
    });
  },

  paiement: function(elt, num) {
    var FE = $('tva3310ca3g_FE');
    if ($F(FE) > 0) {
      NTD.Identif.t("showPaiement", [$F(FE)]);
    } else {
      NTD.Identif.t("hidePaiement", []);
    }
  },

  paiement_20130331: function(elt, num) {
    var FE = $('tva3310ca3g_20130331_FE');
    if ($F(FE) > 0) {
      NTD.Identif.t("showPaiement", [$F(FE)]);
    } else {
      NTD.Identif.t("hidePaiement", []);
    }
  },

  paiement_20131231: function(elt, num) {
    var FE = $('tva3310ca3g_20131231_FE');
    if ($F(FE) > 0) {
      NTD.Identif.t("showPaiement", [$F(FE)]);
    } else {
      NTD.Identif.t("hidePaiement", []);
    }
  },

  paiement_20140101: function(elt, num) {
    var FE = $('tva3310ca3g_20140101_FE');
    if ($F(FE) > 0) {
      NTD.Identif.t("showPaiement", [$F(FE)]);
    } else {
      NTD.Identif.t("hidePaiement", []);
    }
  },

};
