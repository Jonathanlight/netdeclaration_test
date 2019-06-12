<?php

try {

  $res->useTemplate();

}
catch (Exception $e) {
  $log->error($e);
}
