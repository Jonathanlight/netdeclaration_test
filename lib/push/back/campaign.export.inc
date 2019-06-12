<?php

try { 

  $rs = $dbo->query('SELECT E.email AS email, '
                    .      'E.id AS email_id'
                    .' FROM psh_act AS A, '
                    .       T('email').' AS E'
                    .' WHERE A.email_id=E.id'
                    .  ' AND A.campaign_id='.intval($req->id)
                    .  ' AND A.type='.intval($req->type));

  $res->sendData($rs, array('filename' => 'emails'));

}
catch (Exception $e) { $err->add($e); }