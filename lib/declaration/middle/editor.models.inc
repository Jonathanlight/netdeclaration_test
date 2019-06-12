<?php

try {

  $ctx->html = "";
  foreach (Imodel::collectAsHash() as $model_id => $format) {
    $ctx->html .= '<div data-item="' . $model_id . '" draggable="true" class="item-model'.($req->selected==$model_id? ' selected' : '').'" title="ID:' . $model_id . '">' . $format . '</div>';
  } 
  
}
catch (Exception $e) {
  $err->add($e);
}