<?php

// TODO : plutot passer par updated_at de Metas (<= 30mn)

try { 

  $rs = $dbo->query('SELECT DISTINCT U.id, U.name, U.image'
                    .' FROM '.Intent::TABLE.' AS I,'
                    .     ' '.Visit::TABLE.' AS V,'
                    .     ' '.T('user').' AS U'
                    .' WHERE I.visit_id=V.id'
                    .  ' AND V.user_id>=1'
                    .  ' AND V.user_id=U.id'
                    .  ' AND I.record_id>=1'
                    .  ' AND I.created_on="'.date('Y-m-d').'"'
                    .  ' AND I.created_at>=DATE_SUB("'.Date::now().'", interval 20 MINUTE)'
                    .' GROUP BY I.visit_id'
                    .' ORDER BY I.visit_id DESC'); 
    
  $ctx->users = $rs->asArray();

  $res->useTemplate();

}
catch (Exception $e) { $log->error($e); }