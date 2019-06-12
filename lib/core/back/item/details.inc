<?php

try {
  
  $item = Item::getInstance(MODEL, (int) $req->id);

  $infos = array();
  if (Model::hasFields($item, array('model_id', 'record_id')) && 
      $item->model_id >= 1 && $item->record_id >= 1) { 
    $hash = array();
    try {
      $i = $item->getItem();     
      $hash['ID'] = $i->getId();
      $hash['type'] = $i->getModel();
      $hash['intitulé'] = $i->getName();
      $hash['date mise à jour'] = $i->getMeta('updated_at');
      $hash['date création'] = $i->getMeta('created_at');
    }
    catch (Exception $e) {
      $hash['intitulé'] = '('.Model::name($item->model_id).' ) ?';
    }
    $infos += array('object associé' => $hash);
  }

  $metas = $item->getMetas();

  $visit = null;
  try {
    $visit = $item->getVisit();
    $infos += array('visite' => $visit->getModalLink());
  }
  catch (Exception $e) {}
  $visit = null;
  try {
    $user = $item->getUser();
    $infos += array('createur' => Item::edit($user));
  }
  catch (Exception $e) {}
  
  
  $update = $metas['updated_at'];
  if (Model::parameter($item, 'revision') === true) {
    $n = $dbo->fetchValue('SELECT COUNT(*)'
                          .' FROM '.Item::TABLE_REVISION
                          .' WHERE model_id='.$item->getModelId()
                          .  ' AND record_id='.$item->getId());
    if ($n > 0) {
      $update .= '<br/><a href="javascript:void(0)" onclick="Kwo.F(\''.$item->getModel().'\').onExec(\'revisions\', this, {container: $(this).up(\'.deck-pane\')})" data-id="'.$item->getId().'">voir les modifications</a>';
    }
  }

  $infos = array('ID' => $item->getId(),
                 'création' => $metas['created_at'],
                 'mise à jour' => $update) + $infos;
  
  if ($metas['download']) {
    $infos['téléchargement(s)'] = $metas['download'];
  }
  
  if ($item instanceof Purchasable) {
    $n = $dbo->fetchValue('SELECT COUNT(p.id) FROM '.T('purchase').' AS p, '.T('order').' AS o'
                          .' WHERE p.model_id='.$item->getModelId()
                          .  ' AND p.record_id='.$item->getId()
                          .  ' AND p.order_id=o.id'
                          .  ' AND o.status='.Order::STATUS_PROCESSED);
    $infos['achat(s)'] = (int) $n;
    $rs = $dbo->query('SELECT * FROM '.Discount::TABLE_ITEM
                      .' WHERE model_id='.$item->getModelId()
                      .  ' AND record_id='.$item->getId());
    $discounts = array();
    foreach ($rs as $row) {
      $discounts[] = c(Discount::name($row['discount_id'])).' : '.$row['amount'].' EUR';
    }
    if (!empty($discounts)) {
      $infos['réduction(s) en cours'] = join('<br/>', $discounts);
    }
  }

  /*  if (Extension::exists('search')) {
    $key = 'Moteur de recherche interne';
    $link_index = '<a href="javascript:void(0)" onclick="Kwo.F(\''.MODEL.'\').onExec(\'document.index\', {id: '.$item->getId().'})">indexer</a>';
    if (Document::hasItem($item)) {
       $link_remove = '<a href="javascript:void(0)" onclick="Kwo.F(\''.MODEL.'\').onExec(\'document.remove\', {id: '.$item->getId().'})">désindexer</a>';
      $infos[$key] = 'présent - '.$link_index.' - '.$link_remove;
    }
    else {
      $infos[$key] = 'absent - '.$link_index;
    }
    
    }*/

  $belongs_to = (array) Model::parameter($item->getModel(), 'belongs_to');
  foreach ($belongs_to as $name => $hash) {
    $id = $item->getAttribute($name.'_id');
    if ($id < 1) continue ;
    $o = Item::getInstance($name, $item->getAttribute($name.'_id'));
    $infos['Liaison : '.ucfirst(Model::label($o))] = $o->getName().' ('.$o->getId().')';                          
  }

  $ctx->infos = $infos;

  if (method_exists($item, 'getDetails')) {
    $hash = $item->getDetails(); 
    foreach ($hash as $key => $value) {
      $ctx->infos[$key] = $value;
    }
  }
  
  $opinion = array();
  if ($metas['abuse']) {
    $opinion['report(s) d’abus'] = $metas['abuse'];
  }
  if ($metas['like'] || $metas['dislike']) {
    $opinion['j’aime / J’aime pas'] = 'up ('.$metas['like'].') &middot; down ('.$metas['dislike'].')';
  }
  if ($metas['comments']) {
    $opinion['commentaire(s)'] = $metas['comments'];
  }
  if ($metas['rate']) {
    $opinion['évaluation'] = $metas['rating'].' - '.$metas['rate'].' vote(s)';
  }
  if ($metas['share']) {
    $opinion['partage(s)'] = $metas['share'];
  }
  if ($metas['favorite']) {
    $opinion['mise(s) en favoris'] = $metas['favorite'];
  }
  $n = $dbo->fetchValue('SELECT COUNT(*)'
                        .' FROM '.T('subscription')
                        .' WHERE model_id='.$item->getModelId()
                        .  ' AND record_id='.$item->getId()
                        .  ' AND status>0');
  if ($n > 0) {
    $opinion['abonné(s)'] = $n;
  }
  $n = $dbo->fetchValue('SELECT COUNT(*)'
                        .' FROM '.T('subscription')
                        .' WHERE model_id='.$item->getModelId()
                        .  ' AND record_id='.$item->getId()
                        .  ' AND status<1');
  if ($n > 0) {
    $opinion['désabonné(s)'] = $n;
  }
  
  
  $ctx->opinion = $opinion; 

  if (Model::exists('valuation')) {
    $row = array('model_id' => $item->getModelId(),
                 'record_id' => $item->getId());
    if (Item::exists('valuation', $row)) {
      $hash = array();
      $valuation = Valuation::getInstance($row);
      $hash['commentaire'] = $valuation->comment;
      foreach ($valuation->getCriterions() as $criterion) {
        $hash[$criterion->name] = $criterion->grade;
      }
      $ctx->valuation = $hash;
    }
  }

  $res->useXml();

}
catch (Exception $e) { $err->add($e); }