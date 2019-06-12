<?php

try {

  $max = date('Y-m-d H:i:0', (time() - 3600));

  $dbo->exec('INSERT IGNORE INTO '.Tracker::TABLE_STRING.' (name, type)'
             . ' SELECT DISTINCT category,'
             .      ' '.Tracker::STR_CATEGORY
             .   ' FROM '.Tracker::TABLE_TMP);
  
  $dbo->exec('INSERT IGNORE INTO '.Tracker::TABLE_STRING.' (name, type)'
             . ' SELECT DISTINCT action,'
             .      ' '.Tracker::STR_ACTION
             .   ' FROM '.Tracker::TABLE_TMP);

  $dbo->exec('INSERT INTO '.Tracker::TABLE_HIT
             .' SELECT visit_id, ta.id, tc.id, created_at'
             .  ' FROM '.Tracker::TABLE_TMP.' AS t'
             .  ' JOIN '.Tracker::TABLE_STRING.' AS ta'
             .    ' ON (ta.name=t.action AND ta.type='.Tracker::STR_ACTION.')'
             .  ' JOIN '.Tracker::TABLE_STRING.' AS tc'
             .    ' ON (tc.name=t.category AND tc.type='.Tracker::STR_CATEGORY.')'
             . ' WHERE t.created_at < "'.$max.'"');

  $dbo->exec('DELETE FROM '.Tracker::TABLE_TMP
             .    ' WHERE created_at < "'.$max.'"');
  
  $hour = (int) date('H');
 
  if ($req->manual == 'yes' || $req->hasAttribute('date') || $hour === 3) {
    $date = $req->hasAttribute('date') ? $req->date : Date::yesterday();
    $rb = new ReportBuilder();
    $rb->enqueue($date);
    $rb->process();
  }
  
  if ($hour === 5) {
    $ts = mktime(0, 0, 0, date('m'), date('d'), date('Y') - 1);
    $limit = date('Y-m-d', $ts).' 0:0:0';
    $dbo->exec('DELETE FROM '.Tracker::TABLE_VISITOR
               .    ' WHERE created_at < "'.$limit.'"'
               .      ' AND counter < 24');
    $dbo->exec('DELETE FROM '.Tracker::TABLE_ROBOT
               .    ' WHERE TO_DAYS("'.Date::now().'") - TO_DAYS(created_at) > 5');
    foreach (array(Tracker::TABLE_TMP, Tracker::TABLE_VISITOR, Tracker::TABLE_ROBOT) as $table) {
      $dbo->getTable($table)->optimize();
    }
  }
  
}
catch (Exception $e) { $err->add($e); }

