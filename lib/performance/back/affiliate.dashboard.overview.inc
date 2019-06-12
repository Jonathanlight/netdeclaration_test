<?php

try {

  $db = DashBoard::getInstance();

  $b = $db->getBlock();
  $b->setLabel('statistiques générales');
  $ht = array(); 

  $n = $dbo->fetchValue('SELECT COUNT(*) FROM '.Meta::TABLE.' AS m'
                        .' WHERE m.'.Meta::FIELD_MODEL.'='.I(MODEL)
                        .  ' AND '.$db->filter('m.created_on'));
  $ht['nouveaux affiliés'] = $n;

  $attrs = $dbo->fetchAttributes('SELECT COUNT(*) AS n'
                                 .' FROM '.Visit::TABLE.' AS v'
                                 .' WHERE v.medium='.Tracker::MEDIUM_AFFILIATE
                                 .  ' AND '.$db->filter('v.created_on'));
  $ht['nbre de visites'] = $attrs['n'];

  if (Model::exists('conversion')) {
    $attrs = $dbo->fetchAttributes('SELECT COUNT(*) AS n, SUM(c.worth) AS w'
                                   .' FROM '.T('conversion').' AS c'
                                   .' WHERE c.medium='.Tracker::MEDIUM_AFFILIATE
                                   .  ' AND '.$db->filter('c.created_at'));
    $ht['conversions - nbre'] = $attrs['n'];
    $ht['conversions - gains'] = (float) $attrs['w'];
  }
  
  $b->setValues($ht);

  $rs = $dbo->query('SELECT s.name, COUNT(v.source) AS n'
                    .' FROM '.Visit::TABLE.' AS v,'
                    .     ' '.Tracker::TABLE_STRING.' AS s'
                    .' WHERE v.medium='.Tracker::MEDIUM_AFFILIATE
                    .  ' AND '.$db->filter('v.created_on')
                    .  ' AND v.source=s.id'
                    .' GROUP BY v.source'
                    .' LIMIT 20');
  $ht = array();
  foreach ($rs as $row) {
    $ht[Item::asSourceName($row['name'])] = $row['n'];
  }
  if (!empty($ht)) {
    $b = $db->getBlock();
    $b->setLabel('classement: visites');
    $b->setValues($ht);
  }
  
  if (Model::exists('conversion')) {
    $rs = $dbo->query('SELECT s.name, COUNT(c.source) AS n'
                      .' FROM '.T('conversion').' AS c,'
                      .     ' '.Tracker::TABLE_STRING.' AS s'
                      .' WHERE c.medium='.Tracker::MEDIUM_AFFILIATE
                      .  ' AND '.$db->filter('c.created_at')
                      .  ' AND c.source=s.id'
                      .' GROUP BY c.source'
                      .' LIMIT 20');
    $ht = array();
    foreach ($rs as $row) {
      $ht[Item::asSourceName($row['name'])] = $row['n'];
    }
    if (!empty($ht)) {
      $b = $db->getBlock();
      $b->setLabel('classement: conversions');
      $b->setValues($ht);
    }

    $rs = $dbo->query('SELECT c.model_id, COUNT(c.source) AS n, SUM(c.worth) AS w'
                      .' FROM '.T('conversion').' AS c'
                      .' WHERE c.medium='.Tracker::MEDIUM_AFFILIATE
                      .  ' AND '.$db->filter('c.created_at')
                      .' GROUP BY c.model_id'
                      .' ORDER BY n DESC'); 
    
    $ht = array();
    foreach ($rs as $row) {
      $ht[] = array(N($row['model_id']), $row['n'], $row['w']);
    }
    if (!empty($ht)) {
      $b = $db->getBlock();
      $b->setLabel('principaux types de conversions');
      $b->setColumns(array('model_id' => 'type', 
                           'n' => array('width' => '40px',
                                        'label' => 'nbre'),
                           'w' => 'valeur'));
      $b->setValues($ht);
    }
    
  }

  $res->write($db);
  
}
catch (Exception $e) { $err->add($e); }
