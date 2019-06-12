<?php

try {

  $model = Imodel::getInstance($req->model_id);

  if ($model->isUsed()) {
    throw new Exception('Echec : le modèle est utilisé dans d\'autres formulaires.');
  }
  
  $model->destroy();
  
}
catch (Exception $e) {
  $err->add($e);
}