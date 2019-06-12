<?php 


//exit();
try {

//  foreach(Dectype::collect(array('filters' => array('|>=|id' => 76))) as $dectype){
//    $dectype->setAttribute('status', 0);
//  }

  $csv = CsvReader::getInstance('doc/ntd_operation_20140320.csv');
  foreach($csv as $row) {
    $args = unserialize($row['method_args']);
    
    $ftype_code = $args['result'];
    S('log')->debug($args['result']);
    //    $ftype_code = $row['code'];
    list($ftype_code, ) = explode('_', $ftype_code, 2);
    if ($row['id'] == 1901 ) {
      $ftype_code = '2058A';
    }
    $ftypes = Formulairetype::collect(array('filters' => array('code' => $ftype_code,
                                                               '|!&|flags' => Formulairetype::FLAG_OLD_SYSTEM)));
    if($ftypes->count() == 1) {
      $ftype = $ftypes->first();
      $operation = Operation::getInstance();      
      $commit = $row;
      unset($commit['id']);
      $commit['formulairetype_id'] = $ftype->getId();
      $commit['method_args'] = unserialize($row['method_args']);
      $operation->commit($commit);

      if($commit['millesimes'] != '5' && $commit['millesimes'] != '') {        
        var_export($commit);
      }
    }
    else{
      print "ftype [".$ftype_code."] non trouvé\n";
    }
  }


/*  foreach(Operation::collect(array('filters' => array('|>=|id' => 1868))) as $operation ) {
    $method_args = $operation->method_args;
//    print $operation->getId();
    //var_export( $method_args);
        if(key($method_args) == 0) {
    $operation->setAttribute('method_args', $method_args[0]);
      }
  }*/

}
catch(Exception $e){
  print $e->getMessage();
}