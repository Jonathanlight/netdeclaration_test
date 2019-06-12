<?php

try {

  $begin_at = Date::toDb($req->begin_at);
  $end_at = Date::toDb($req->end_at);
  if (Date::isNull($begin_at)) {
    $begin_at = Date::today();
  }
  if (Date::isNull($end_at)) {
    $end_at = Date::today();
  }
  switch ($req->status) {
    case Facture::STATUS_PENDING:
      $statuses = array(Facture::STATUS_PENDING);
      break;
    case Facture::STATUS_PENDING:
      $statuses = array(Facture::STATUS_PENDING);
      break;
    default:
      $statuses = Facture::$statuses;
      break;
  }

  $opts = array('filters' => array('|><|created_at' => array($begin_at, $end_at),
                                   '|IN|status'     => $statuses),
                'order' => array('created_at' => 'DESC'),
                'metas' => array('created_at'));
  $factures = Facture::collect($opts);
  
  if ($factures->count() < 1) {
    throw new Exception("Aucun facture à générer dans l'intervalle sélectionné.");
  }

  $dest_folder  = 'doc/ntd/factures';
  $final_folder = 'doc/ntd/factures/'.str_replace('/', '_', $req->begin_at).'_'.str_replace('/', '_', $req->end_at);

  if (!Folder::exists($dest_folder)) {
    Folder::create($dest_folder);
  }
  if (!Folder::exists($final_folder)) {
    Folder::create($final_folder);
  }

  $filename = date('Ymd', strtotime($begin_at)) . '_' . date('Ymd', strtotime($end_at)) . '_FACTURES.csv';
  if ($begin_at == $end_at) {
    $filename = date('Ymd', strtotime($begin_at)) . '_FACTURES.csv';
  }

  if ($factures->count() > 0) {
    foreach ($factures as $facture) {
      H::url('/ntd/facture.print/-/id/'.$facture->getId());
      try {
        $cmd_line  = '/etc/kernix/bin/wkhtmltopdf';
        $cmd_line .= ' --margin-top 0.5cm --margin-bottom 0.5cm --margin-left 0.5cm --margin-right 0.5cm --image-quality 100 --image-dpi 800 --no-pdf-compression';
        $auth = '';
        if (strlen(P('auth.password')) > 2) {
          $auth .= P('auth.login').':'. P('auth.password').'@';
        }
        $cmd_line .= ' http://'.$auth.P('app.domain').'/ntd/facture.print/-/id/'.$facture->getId();
        $file_name = $final_folder.'/facture-'.$facture->getId().'.pdf';
        $cmd_line .= ' '.$file_name;
        S('log')->debug($cmd_line);
        shell_exec($cmd_line);
      } catch (Exception $e) { S('err')->add($e); }
    }
  }

  $ctx->msg = "Génération de ".$factures->count()." factures effectuée dans le dossier ".$final_folder.".";
  $res->useTemplates(array(null, true));

}
catch (Exception $e) {
  $err->add($e);
}
