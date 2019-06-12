<?php

try {

  foreach (Itemplate::collect(array('filters' => array('status' => 1))) as $itemplate) {    
    $path = $itemplate->getTemplatePath();
    print $path."\n";
    $folder_path = dirname($path);
    if (!Folder::exists($folder_path)) {
      Folder::create($folder_path, true);
    }
    file_put_contents($path, $itemplate->psp);
  }

}
catch (Exception $e) {
  print $e->getMessage();
}
