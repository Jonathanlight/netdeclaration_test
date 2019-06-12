<?php

try {
  $file = new File($req->file_path,'W');
}
catch (Exception $e) {
  $log->error($e);
  $err->add($e);
  exit (0);
}

File::show_file_path($file->getPath());

?>

<div style="margin:10px 10px 10px 10px;">
<form action="/back/file/content_store" method="post" id="_form" >
 <input type="hidden" name="file_path" value="<?=$file->getName()?>" />
 <textarea name="content" style="width:100%; height:370px; margin-bottom:10px;"><?=$file->getContent()?></textarea>
 <img src="/<?=PIX_PATH?>/action/store.gif"
      onclick="$('_form').submit()" class="button" />
 <img src="/<?=PIX_PATH?>/action/back.gif"
      onclick="file.view('<?=$file->getName()?>')" class="button" />
</form>
</div>

