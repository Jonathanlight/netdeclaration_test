<?php

try {

  if(P('app.state') != 'dev') return;

  $res->useTemplates(array(null, 'skeleton.decbdd', true));

}
catch (Exception $e) {
  $err->add($e);
}