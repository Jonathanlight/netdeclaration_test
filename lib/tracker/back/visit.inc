<?php

try { 

  $id = (int) $req->id;

  if ($id < 1 && $req->hasAttribute('period', true)) {
    list ($year, $month, $day) = explode('-', $req->period);
    $where = '1';
    if ($year > 1990) {
      $where .= ' AND YEAR(created_on)='.intval($year);
    }
    if ($month > 1) {
      $where .= ' AND MONTH(created_on)='.intval($month);
    }
    if ($day> 1) {
      $where .= ' AND DAY(created_on)='.intval($day);
    } 
    $id = $dbo->fetchValue('SELECT id'
                           .' FROM '.Visit::TABLE
                           .' WHERE '.$where
                           .' ORDER BY id ASC'
                           .' LIMIT 1'); 
  }
  
  $visit = Visit::getInstance($id);
  
  $summary = $visit->getSummary();
  
  $rows['date'] = $summary['created_on'];
  $rows['heure'] = substr($summary['created_at'], 0, 5);
  $rows['visiteur'] = $visit->visitor_id;
  $link = $visit->number;
  if ($visit->number > 1) {
    $link = '<a href="javascript:void(0)" data-id="'.$visit->id.'"'
             .' onclick="Kwo.Visit.displaySiblings(this)">'.$visit->number.'</a>';
  }
  $rows['visite n°'] = $link;
  if ($summary['span'] > 0) {
    $rows['précédente'] =' il y a '.$visit->span.' jour(s)';
  }
  $rows['durée'] = $visit->duration.' mn';
  $link = $visit->depth;
  if ($visit->depth > 0) {
    $link = '<a href="javascript:void(0)"'
             .' onclick="Kwo.Visit.displayPath(this)">'.$visit->depth.'</a>';
  }
  $rows['évènements'] = $link;
  $rows['pays'] = $summary['country'];
  $rows['origine'] = $summary['referer'];
  $rows['système'] = $summary['system'];
  $link = '<a href="javascript:void(0)"'
           .' data-url="https://www.db.ripe.net/whois?form_type=simple&full_query_string=&searchtext='.$summary['ip'].'"'
           .' onclick="new Kwo.Preview(this)"'
           .' rel="noreferrer">'.$summary['ip'].'</a>';
  $rows['adresse IP'] = $link;
  $rows['domaine'] = $summary['host'];
  if ($visit->user_id >= 1) {
    $rows['user'] = $summary['user'];
  }

  $ctx->visit = $visit;
  $ctx->rows = $rows;
  $ctx->events = $visit->getPath();
  $res->useTemplate();
  
}
catch (Exception $e) { $err->add($e); }
