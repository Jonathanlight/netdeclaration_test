<?php

try {

  $original_itemplate = Itemplate::getInstance($req->ori);
  $duplicated_itemplate = Itemplate::getInstance($req->dup);

  print $original_itemplate->getId() . ' <=> ' . $duplicated_itemplate->getId() . "\n";

  $original_attributes = $original_itemplate->getAttributes();
  $duplicated_attributes = $duplicated_itemplate->getAttributes();

  $original_version = $duplicated_itemplate->version - 1;
  if ($original_version < 1) {
    print '$original_version < 1' . "\n";
    return;
  }
  $original_modified = array('millesime_id' => $duplicated_attributes['millesime_id'],
                             'psp' => $duplicated_attributes['psp'],
                             'html' => $duplicated_attributes['html'],
                             'code' => $duplicated_attributes['code'],
                             'version' => $original_version,
                             'name' => substr($duplicated_attributes['name'], 0, strlen($duplicated_attributes['name']) - strlen(' (dupliqué)')));
  $duplicate_modified = array('millesime_id' => $original_attributes['millesime_id'],
                              'name' => $original_attributes['name'],
                              'psp' => $original_attributes['psp'],
                              'html' => $original_attributes['html'],
                              'code' => $original_attributes['code'],
                              'version' => $original_attributes['version']);
//    var_export($original_modified);
//    var_export($duplicate_modified);




  print "do it \n";
  $original_itemplate->setAttributes($original_modified);
  $duplicated_itemplate->setAttributes($duplicate_modified);

  print "finish\n";


  return;



  $names = array(
    'tdfc1330cvae',
    'tdfc1330cvaee',
    'tdfc1330cvaepe',
    'tdfc2025a',
    'tdfc2025c',
    'tdfc2025d',
    'tdfc2026a',
    'tdfc2026b',
    'tdfc2026c',
    'tdfc2026d',
    'tdfc2026f',
    'tdfc2027a',
    'tdfc2027b',
    'tdfc2027c',
    'tdfc2027d',
    'tdfc2027e',
    'tdfc2027f',
    'tdfc2027g',
    'tdfc2027h',
    'tdfc2028a',
    'tdfc2028b',
    'tdfc2028c',
    'tdfc2028d',
    'tdfc2029b',
    'tdfc2029bbis',
    'tdfc2029e',
    'tdfc2029f',
    'tdfc2029g',
    'tdfc2029h',
    'tdfc2029i',
    'tdfc2031',
    'tdfc2031bis',
    'tdfc2031ter',
    'tdfc2033a',
    'tdfc2033b',
    'tdfc2033c',
    'tdfc2033d',
    'tdfc2033e',
    'tdfc2033f',
    'tdfc2033g',
    'tdfc2035',
    'tdfc2035a',
    'tdfc2035b',
    'tdfc2035e',
    'tdfc2035f',
    'tdfc2035g',
    'tdfc2035suite',
    'tdfc2036',
    'tdfc2036bis',
    'tdfc2039',
    'tdfc2050',
    'tdfc2051',
    'tdfc2052',
    'tdfc2053',
    'tdfc2054',
    'tdfc2054bis',
    'tdfc2055',
    'tdfc2056',
    'tdfc2057',
    'tdfc2058a',
    'tdfc2058ab',
    'tdfc2058b',
    'tdfc2058bb',
    'tdfc2058c',
    'tdfc2058cg',
    'tdfc2058dg',
    'tdfc2058er',
    'tdfc2058es',
    'tdfc2058fc',
    'tdfc2058ifa',
    'tdfc2058pap',
    'tdfc2058pv',
    'tdfc2058rg',
    'tdfc2058sg',
    'tdfc2058ts',
    'tdfc2059a',
    'tdfc2059b',
    'tdfc2059c',
    'tdfc2059d',
    'tdfc2059e',
    'tdfc2059f',
    'tdfc2059g',
    'tdfc2059h',
    'tdfc2059i',
    'tdfc2065',
    'tdfc2065bis',
    'tdfc2065ter',
    'tdfc2066',
    'tdfc2067',
    'tdfc2067bis',
    'tdfc2072c',
    'tdfc2072ca1',
    'tdfc2072ca5',
    'tdfc2072ca8',
    'tdfc2072e',
    'tdfc2072s',
    'tdfc2072sa1',
    'tdfc2072sca2',
    'tdfc2079a',
    'tdfc2079cice',
    'tdfc2079fce',
    'tdfc2083',
    'tdfc2083m',
    'tdfc2139',
    'tdfc2139a',
    'tdfc2139b',
    'tdfc2139bis',
    'tdfc2139c',
    'tdfc2139d',
    'tdfc2139e',
    'tdfc2139ter',
    'tdfc2143',
    'tdfc2143ver',
    'tdfc2144',
    'tdfc2145',
    'tdfc2146',
    'tdfc2146bis',
    'tdfc2147',
    'tdfc2147bis',
    'tdfc2148',
    'tdfc2149',
    'tdfc2150',
    'tdfc2151',
    'tdfc2151bis',
    'tdfc2151ter',
    'tdfc2152',
    'tdfc2152bis',
    'tdfc2153',
    'tdfc2154',
    'tdfc2900',
    'tdfc2901',
    'tdfc2902',
    'tdfc2903',
    'tdfc2904',
    'tdfcannexlib01',
    'tdfcannexlib02',
    'tdfcannexlib03',
    'tdfcannexlib04',
    'tdfcannexlib05',
    'tdfcattestapec',
    'tdfcattestataa',
    'tdfcca17prorec',
    'tdfcca18chapay',
    'tdfcca19charep',
    'tdfcca20chaava',
    'tdfcca21proava',
    'tdfccalc219bf4',
    'tdfcdeducactio',
    'tdfcdemagrecor',
    'tdfcdemagrezfu',
    'tdfcdreszfurec',
    'tdfcdreszfuver',
    'tdfclteng219b4',
    'tdfcoptanc219f',
    'tdfcrescofin',
    'tdfcsciicsuivi',
    'tdfcsuiv093rec',
    'tdfcsuiv093ver',
    'tdfcsuiv219rec',
    'tdfcsuiv219ver',
    'tdfcsuivpvsuim',
    'tdfcsuivpvsuis',
    'tdfczfcfiche01',
    'tdfczfcfiche02',
    'tdfczfcfiche03',
  );

  $names = 'tdfc2033b';

  foreach (Formulairetype::collect(array('filters' => array('name' => $names))) as $ftype) {
    if ($ftype->hasFlag(Formulairetype::FLAG_OLD_SYSTEM)) continue;


    if ($ftype->getItemplates(array('filters' => array('millesime_id' => 5, 'status' => 1)))->count() > 0) {
//      print "template 2014 active\n";
      continue;
    }
    print $ftype->code . "\n";
continue;

    $original_itemplate = $ftype->getItemplates(array('filters' => array('millesime_id' => 8, 'version' => 1)));
    $duplicated_itemplate = $ftype->getItemplates(array('filters' => array('millesime_id' => 5),
                                                        'order' => array('version' => 'DESC')));
    if ($original_itemplate->count() > 0) {
      $original_itemplate = $original_itemplate->first();
    }
    else {
      continue;
    }
    if ($duplicated_itemplate->count() > 0) {
      $duplicated_itemplate = $duplicated_itemplate->first();
    }
    else {
      continue;
    }


    if (strrpos($duplicated_itemplate->name, ' (dupliqué)') !== strlen($duplicated_itemplate->name) - strlen(' (dupliqué)')) {
      print "Erreur, pas de (dupliqué) dans le nom de la template Dupliqué : " . $duplicated_itemplate->name . "\n";
      continue;
    }
    if ($ftype->getItemplates(array('filters' => array('millesime_id' => 8)))->count() > 1) {
      print "plusieurs template 2015\n";
      continue;
    }
//continue;


    print $original_itemplate->getId() . ' <=> ' . $duplicated_itemplate->getId() . "\n";

    $original_attributes = $original_itemplate->getAttributes();
    $duplicated_attributes = $duplicated_itemplate->getAttributes();

    $original_version = $duplicated_itemplate->version - 1;
    if ($original_version < 1) {
      print '$original_version < 1' . "\n";
      continue;
    }
    $original_modified = array('millesime_id' => $duplicated_attributes['millesime_id'],
                               'psp' => $duplicated_attributes['psp'],
                               'html' => $duplicated_attributes['html'],
                               'code' => $duplicated_attributes['code'],
                               'version' => $original_version,
                               'name' => substr($duplicated_attributes['name'], 0, strlen($duplicated_attributes['name']) - strlen(' (dupliqué)')));
    $duplicate_modified = array('millesime_id' => $original_attributes['millesime_id'],
                                'name' => $original_attributes['name'],
                                'psp' => $original_attributes['psp'],
                                'html' => $original_attributes['html'],
                                'code' => $original_attributes['code'],
                                'version' => $original_attributes['version']);
//    var_export($original_modified);
//    var_export($duplicate_modified);


//    $prompt = Shell::prompt('do ? (y/N)', 'N');
    if (true || $prompt == 'y') {
      print "do it \n";
      $original_itemplate->setAttributes($original_modified);
      $duplicated_itemplate->setAttributes($duplicate_modified);
    }
    print "finish\n";

    var_export($original_attributes);
    var_export($duplicated_attributes);

//      array('name' => $original_itemplate->name,
//                                 'code' => $original_itemplate->code,
//                                 'millesime_id' => $original_itemplate->millesime_id,
//                                 'html' => $original_itemplate->html,
//                                 'psp' => $original_itemplate->psp);
// 	  $duplicated_attributes = array('name' => $duplicated_itemplate->name,
//                                   'code' => $duplicated_itemplate->code,
//                                   'millesime_id' => $duplicated_itemplate->millesime_id,
//                                   'html' => $duplicated_itemplate->html,
//                                   'psp' => $duplicated_itemplate->psp);
//    status
//    formulairetype_id
//    version


  }

}
catch (Exception $e) {
  $err->add($e);
}