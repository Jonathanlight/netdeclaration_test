<?php

try {
  
  foreach ($req->data as $col_data) {
    $data[] = $col_data['value'].( $col_data['options'] ? '&'.http_build_query($col_data['options']) : '');
  }
  $opts = (array) $req->opts;

  $model = Imodel::getInstance($req->model_id);

  $ctx->model = $model->getHtmlDescription($data).'<span class="data">[Model:'.$req->model_id.';'.implode(';', $data).']</span>';
  
  $ctx->id = $model->id;
  
  $ctx->data = implode(';', $data);
  $ctx->opts = http_build_query($opts);
  $ctx->row_options = implode(',', array_keys($opts));

  //$ctx->model = '[Model:'.$req->model_id.';'.implode(';', $data).']';

}
catch (Exception $e) {
  $err->add($e);
}