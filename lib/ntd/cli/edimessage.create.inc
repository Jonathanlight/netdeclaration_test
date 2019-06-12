<?php

try {

  $edimessage = Edimessage::getInstance();
  $edimessage->commit(array('ref_message' => '3437281_831607'));

}
catch (Exception $e) {
  $err->add($e);
}