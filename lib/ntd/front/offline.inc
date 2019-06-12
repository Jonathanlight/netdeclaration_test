<?php

try {
  
  $res->useTemplate(array(null, true));

}
catch (Exception $e) {
  $log->error($e);
}
