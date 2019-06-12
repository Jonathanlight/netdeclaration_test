<?php


try {

  //--------------------------------------------------------------------------------------
  $csv = CsvReader::getInstance('doc/mep/snippets.csv');
  foreach ($csv as $row) {
    $commit = array('code' => $row['code'],
                    'app' => $row['app'],
                    'extension_id' => $row['extension_id'],
                    'cache' => base64_decode($row['cache']),
                    'locales' => $row['locales'],
                    'description' => base64_decode($row['description']),
    );
    if (!Snippet::exists($row['code'])) {
      $snippet = Snippet::getInstance();
    }
    else {
      $snippet = Snippet::getInstance($row['code']);
      unset($commit['code']);
    }

    $snippet->commit($commit);
    $snippet->setProperties(array('title' => base64_decode($row['title_fr']),
                                  'description' => base64_decode($row['description_fr']),
                                  'content' => base64_decode($row['content_fr']),
                            ), I18N::LOCALE_FR);
  }

  //--------------------------------------------------------------------------------------
  $csv = CsvReader::getInstance('doc/mep/properties.csv');
  foreach ($csv as $row) {
    if (!Property::exists(array('model_id' => $row['model_id'],
                                'name' => $row['name']))
    ) {
      $p = Property::getInstance();
      $p->commit(array('name' => $row['name'],
                       'model_id' => $row['model_id']));
    }
  }
  print 'terminé';
}
catch (Exception $e) {
  S('log')->debug($e, __METHOD__);
}

