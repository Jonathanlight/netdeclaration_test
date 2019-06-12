Kwo.Glossary = {

  "term": "",

  "selectLetter": function(letter, glossary_id) {
    $("kwo-letter-" + letter).up(".kwo-letters").select("A").invoke("removeClassName", "selected");
    $("kwo-letter-" + letter).addClassName("selected");
    Kwo.exec("/cms/terms", 
             {"glossary_id": glossary_id, "letter": letter, "term": Kwo.Glossary.term}, 
             {"container": "kwo-terms"});
    Kwo.Glossary.term = "";
  },

  "selectTerm": function(element) {
    element = $(element);
    element.up("ul").select("p").invoke("hide");
    element.next("p").show();
  }

}

document.fire("kwo:glossary:loaded");