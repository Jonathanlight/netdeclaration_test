<?php

try {

  $item = Item::getInstance($req->model_id, $req->record_id);

  $ctx->item = $item->asPickerHash();

}
catch (Exception $e) { $err->add($e); }


