
if (!Kwo) var Kwo = {};

Kwo.Search = {

  "results": function(query, offset) {

    var args = {};
    args["offset"] = offset === undefined ? 0 : offset;
    if (query === undefined) {
      if ($("kwo-search-input")) {
        args["query"] = $F('kwo-search-query');
      }
      else {
        return false;
      }
    }
    args["query"] = query;

    if (args["query"].length < 1) return false ;

    Kwo.go("/search/results", args);

  }

};

