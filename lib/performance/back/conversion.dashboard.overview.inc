<?php

try {

  $db = DashBoard::getInstance();

  $b = $db->getBlock();
  $b->setLabel('statistiques générales');
  $ht = array();

  $rs = $dbo->query('SELECT model_id, COUNT(record_id) AS n, SUM(worth) AS w'
                    .' FROM '.T('conversion')
                    .' WHERE '.$db->filter('created_at')
                    .' GROUP BY model_id'
                    .' ORDER BY n DESC');

  $ht['nbre conversion(s)'] = $rs->sum('n');
  $ht['valorisation'] = $rs->sum('w');
  $b->setValues($ht);

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

  $rs = $dbo->query('SELECT medium, COUNT(id) AS n, SUM(worth) AS w'
                    .' FROM '.T('conversion')
                    .' WHERE '.$db->filter('created_at')
                    .  ' AND medium>0'
                    .' GROUP BY medium'
                    .' ORDER BY n DESC');
  $ht = array();
  foreach ($rs as $row) {
    $ht[] = array(Tracker::$mediums[$row['medium']], 
                  $row['n'], 
                  $row['w']);
  }
  if (!empty($ht)) {
    $b = $db->getBlock();
    $b->setLabel('principales sources');
    $b->setColumns(array('medium' => 'source', 
                         'n' => array('width' => '40px',
                                      'label' => 'nbre'),
                         'w' => 'valeur'));
    $b->setValues($ht);
  }


  $res->write($db);

}
catch (Exception $e) { $err->add($e); }
