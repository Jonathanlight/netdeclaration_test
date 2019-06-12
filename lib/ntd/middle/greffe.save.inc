<?php

try {

  $adherent = NetDeclaration::getCurrentAdherent();

  if (!Adherent::exists((int)$req->adherent_id) || $adherent->getId() != (int)$req->adherent_id) {
    throw new Exception(l('error'));
  }

  if (!$req->hasAttribute('adherent', true)) {
    throw new Exception(l('error'));
  }

  if (!$req->hasAttribute('greffe', true)) {
    throw new Exception(l('error'));
  }


  $form_adherent = $req->adherent;
  $form_greffe = $req->greffe;
  $form = array('adherent' => $form_adherent,
                'greffe'   => $form_greffe);

  $errors = array();
  $required = array('adherent' => array('siren'            => 'int',
                                        'company'          => 'string',
                                        'address'          => 'string',
                                        'zipcode'          => 'int',
                                        'greffecommune_id' => 'int',
                                        'city'             => 'string',
                                        'country_id'       => 'int'),
                    'greffe'   => array('email_deposit'    => 'string',
                                        'start_at'         => 'date',
                                        'closed_at'        => 'date',
                                        'numero_gestion'   => 'pattern',
                                        'compte_type'      => 'int',
                                        'forme_juridique'  => 'int',
                                        'is_public'        => 'yesno'));

  foreach ($required as $key => $require) {
    foreach ($require as $field => $type) {
      switch ($type) {
        case 'int':
        case 'string':
          if (!isset($form[$key][$field]) || empty($form[$key][$field])) {
            $errors[] = sprintf('%s[%s]', $key, $field);
          }
          break;
        case 'date':
          if (!isset($form[$key][$field]) || !Date::isValid($form[$key][$field])) {
            $errors[] = sprintf('%s[%s]', $key, $field);
          }
          break;
        case 'yesno':
          if (!isset($form[$key][$field])) {
            $errors[] = sprintf('%s[%s]', $key, $field);
          }
          break;
        case 'pattern':
          $pattern = '#^([0-9]{4})(B|D)([0-9]{5})$#i';
          if ($field == 'numero_gestion' && (!isset($form[$key][$field]) || !preg_match($pattern, $form[$key][$field]))) {
            $errors[] = sprintf('%s[%s]', $key, $field);
          }
          break;
      }

      if (isset($form['greffe']['closed_at']) && Date::asTimestamp(Date::today()) < Date::asTimestamp($form['greffe']['closed_at'])) {
        $errors[] = sprintf('%s[%s]', 'greffe', 'closed_at');
      }
      if (isset($form['greffe']['closed_at']) && isset($form['greffe']['start_at'])
          && Date::asTimestamp($form['greffe']['closed_at']) <= Date::asTimestamp($form['greffe']['start_at'])) {
        $errors[] = sprintf('%s[%s]', 'greffe', 'closed_at');
        $errors[] = sprintf('%s[%s]', 'greffe', 'start_at');
      }
    }
  }

  if (!empty($errors)) {
    $ctx->errors = $errors;
    return;
  }

  $adherent->commit($form_adherent);

  $form_greffe['adherent_id'] = $adherent->getId();
  $form_greffe['greffedossier_id'] = $form_greffe['greffedossier_id'];
  $form_greffe['start_at'] =  Date::toDb($form_greffe['start_at']);
  $form_greffe['closed_at'] =  Date::toDb($form_greffe['closed_at']);

  $greffe = Greffe::getInstance($req->hasAttribute('id', true) ? (int)$req->id : true);
  $greffe->commit($form_greffe);

  if ($greffe->souscription_id == 0) {
    $souscription = GreffeManager::getAvaillableSouscription($adherent);
    $souscription->setFlag(Souscription::FLAG_CONSUMED);
    $greffe->setAttribute('souscription_id', $souscription->getId());
  }

  $ctx->id = $greffe->getId();

}
catch (Exception $e) { $log->error($e); }