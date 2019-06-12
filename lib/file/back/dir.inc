<?php

try { 

  $folder = new Folder($req->path); 
 
  $ctx->extension = $req->extension();
  $ctx->path = $folder->getPath();
  $ctx->is_root_flag = $folder->isRoot();
  $ctx->selected_file_path = $req->getSession()->getAttribute('selected_file_path');
  
  // 'taille' => $folder->size(),
  $ctx->list_arr = array('fichiers' => $folder->getNbFiles());
  
  $files = $folder->getChildren();
  if ($req->hasAttribute('keyword', true)) {
    $files = array_merge($files, $folder->getFiles(Folder::FILTER_REGEX, 
                                                   $req->keyword));
  }
  elseif ($req->layout == 2) {
    $files = array_merge($files, $folder->getFiles(Folder::FILTER_IMG));
  }
  else {
    $files = array_merge($files, $folder->getFiles()); 
  }
  
  $td = array(array(), array());
  $i = 0;
  foreach ($files as $file) {
    if ($file['is_folder'] == 1) {
      $elem = ' <a href="javascript:void(0)" onclick="Kwo.Dir.view(this);" data-path="'.$file['path'].'"><img src="/'.PIX_PATH.'/mime/dir.gif" />'.$file['name'].'</a>';
    }
    elseif ($req->layout==2) { 
      $elem = '<a href="javascript:void(0)" onclick="Kwo.File.preview(this)" data-path="/'.$ctx->path.'/'.$file['name'].'" title="'.$file['name'].'"><img src="/'.$ctx->path.'/'.$file['name'].'" class="thumb" />'.$file['name'].'</a>';
      $elem .= ' ('.number_format($file['size']/1024,1).'k)';
    }
    else { 
      $icon = Mime::getIcon($file['name']);
      $elem = '<a href="javascript:void(0)" onclick="Kwo.File.preview(this)" data-path="/'.$ctx->path.'/'.$file['name'].'" title="'.$file['name'].'"><img src="/'.PIX_PATH.'/mime/'.$icon.'" />'.$file['name'].'</a>';
    }
    $td[$i++%2][] = ' '.$elem;
  }
  $ctx->cells = $td;
  
  $res->setTitle($folder->getHtmlPath());
  $res->setSeo($folder->getHtmlPath());
  $res->useTemplates('skeleton', true);
  
}
catch (Exception $e) { return $err->add($e); }

