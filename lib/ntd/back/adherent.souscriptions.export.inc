<?php

try {

//  $opts = array('filters' => array('status' => Souscription::STATUS_ACTIVE));
  $opts = array();

  if ($req->limit == 1) {
    $opts['limit'] = intval($req->limit_value);
  }
  if (strlen($req->from) > 5) {
    $opts['filters']['|>=|sign_at'] = Date::toDb($req->from);
  }
  if (strlen($req->to) > 5) {
    $opts['filters']['|<=|sign_at'] = Date::toDb($req->to);
  }
  if ($req->hasAttribute('partenaire_id', true)) {
    $partenaire = Partenaire::getInstance((int) $req->partenaire_id);
    $opts['filters']['partenaire_id'] = (int) $req->partenaire_id;
    $filename = 'souscriptions-'.String::urlify($partenaire->name).'-'.Date::today();
  }
  else {
    $opts['filters']['|>|partenaire_id'] = 0;
    $filename = 'souscriptions-tous-partenaires-'.Date::today();
  }

  $souscriptions = Souscription::collect($opts);

  $columns = array('Partenaire', 'Siret', 'Raison sociale', 'Adhérent', 'Type Adhérent', 'Service', 'Montant', 'Commission', 'Etat', 'Date de signature', 'Date de début souscription', 'Date de fin souscription');

  $opts = array('columns' => $columns,
                'encoding' => 'UTF-8',
                'filename' => $filename);
  $csv = CsvWriter::getInstance($opts);

  if ($souscriptions->count() < 1) return ;

  foreach ($souscriptions as $souscription) {
    $adherent = $souscription->getAdherent();
    $partenaire = $souscription->getPartenaire();
    $service = $souscription->getService();
    $context = $souscription->context;
    $line = array('Partenaire' => $partenaire->name,
                  'Siret' => $adherent->siret,
                  'Raison sociale' => $adherent->company,
                  'Adhérent' => $adherent->identity(),
                  'Type Adhérent' => c(Adherent::$types[$adherent->type]),
                  'Service' => $service->name,
                  'Montant' => $souscription->price ? number_format($souscription->price, 2, ',', '') : number_format($context['price_ht'], 2, ',', ''),
                  'Commission' => $souscription->commission ? number_format($souscription->commission, 2, ',', '') : number_format($context['commission'], 2, ',', ''),
                  'Etat' => Souscription::$export_statuses[$souscription->status],
                  'Date de signature' => H::date($souscription->sign_at),
                  'Date de début souscription' => H::date($souscription->start_at),
                  'Date de fin souscription' => H::date($souscription->finish_at));
    $csv->append($line);
  }

} catch (Exception $e) { $err->add($e);}
