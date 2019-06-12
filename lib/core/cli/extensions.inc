<?php

foreach (glob(ETC_PATH.'/extensions/*/parameters.conf.inc') as $file_path) {
  $parameter = array(); 
  include($file_path);
  $extensions[$parameter['name']] = $parameter['id'];
}

asort($extensions);

print_r($extensions);