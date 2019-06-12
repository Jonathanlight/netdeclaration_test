<?php

try {

  $user = $req->getUser();

  $item = Item::getInstanceByKey($req->item_key);

  $dbo->exec('DELETE FROM cty_item_alert'
             .    ' WHERE model_id='.$item->getModelId()
             .      ' AND record_id='.$item->getId());

  $dbo->insert('cty_item_alert',
              array('model_id' => $item->getModelId(),
                    'record_id' => $item->getId()))

  $item->incrementMeta('subscription');

  $res->write(l('alert.start'));

}
catch (AuthException $e) { User::signup(); }
catch (Exception $e) { $err->add($e); }
