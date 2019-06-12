<?php

try { 

  $item = Item::getInstance(MODEL, (int) $req->id);

  $intent_type = (int) $req->intent_type;

  $rs = $dbo->query('SELECT i.created_at, i.visit_id,'
                    .     ' INET_NTOA(v.ip) AS ip, i.value'
                    .' FROM '.Intent::TABLE.' AS i,'
                    .     ' '.Visit::TABLE.' AS v'
                    .' WHERE i.model_id='.$item->getModelId()
                    .  ' AND i.record_id='.$item->getId()
                    .  ' AND DATE_FORMAT(i.created_on, "%Y-%m")=":date:"'
                    .  ' AND i.type='.$intent_type
                    .  ' AND i.visit_id=v.id',
                    array(':date:' => $req->date)); 

  $opts = array('filename' => 'clics-export');
  $res->sendData($rs, $opts);

}
catch (Exception $e) { $err->add($e); }