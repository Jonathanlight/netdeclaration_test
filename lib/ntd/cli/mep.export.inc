<?php

function getSnippetRow($s) {
  return array(
    'code' => $s->code,
    'app' => $s->app,
    'extension_id' => $s->extension_id,
    'locales' => $s->locales,
    'description' => base64_encode($s->description),
    'title_fr' => base64_encode($s->getProperty('title')),
    'description_fr' => base64_encode($s->getProperty('description')),
    'content_fr' => base64_encode($s->getProperty('content')),
    'cache' => base64_encode($s->cache),
  );
}

try {

  if (!Folder::exists('doc/mep')) {
    Folder::create('doc/mep', true);
  }


  //--------------------------------------------------------------------------------------
  $file = File::getInstance('doc/mep/snippets.csv', 'w');
  $csv = CsvWriter::getInstance(array('fd' => $file,
                                      'columns' => array('code',
                                                         'app',
                                                         'extension_id',
                                                         'locales',
                                                         'description',
                                                         'title_fr',
                                                         'description_fr',
                                                         'content_fr',
                                                         'cache')));

  foreach (Snippet::collect(array('filters' => array('|%%|code' => 'middle.page.'))) as $s) {
    $csv->append(getSnippetRow($s));
  }
  foreach (Snippet::collect(array('filters' => array('|%%|code' => 'account.page.'))) as $s) {
    $csv->append(getSnippetRow($s));
  }
  foreach (Snippet::collect(array('filters' => array('|IN|code' => array('contact',
                                                                         'flashinfo',
                                                                         'global.avantages',
                                                                         'homepage.box.partenaires',
                                                                         'homepage.box.pourqui',
                                                                         'homepage.introduction')))) as $s) {
    $csv->append(getSnippetRow($s));
  }


//--------------------------------------------------------------------------------------
  $file = File::getInstance('doc/mep/properties.csv', 'w');
  $csv = CsvWriter::getInstance(array('fd' => $file,
                                      'columns' => array('model_id',
                                                         'name')));
  foreach (Property::collect(array('filters' => array('|IN|model_id' => array(14322, 14303, 14326)))) as $p) {
    $csv->append(array('model_id' => $p->model_id,
                       'name' => $p->name));
  }


}
catch (Exception $e) {
  $err->add($e);
}

