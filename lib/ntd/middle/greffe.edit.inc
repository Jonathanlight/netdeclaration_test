<?php

try {

  $adherent = NetDeclaration::getCurrentAdherent();

  $fields = array();
  if ($req->hasAttribute('id', true)) {
    if (!Greffe::exists((int)$req->id)) {
      throw new Exception(l('error'));
    }

    $greffe = Greffe::getInstance((int)$req->id);
    $fields = $greffe->getAttributes();

    if ($greffe->souscription_id == 0) {
      throw new Exception('Souscription invalide');
    }

    if (empty($fields['is_gerant'])) {
      $fields['is_gerant'] = false;
    }
    if (empty($fields['mode_direction'])) {
      $fields['mode_direction'] = GreffeManager::DIRECTION_CONSEIL_ADMINISTRATION;
    }
    $ctx->greffe = $greffe;
  }
  else {
    if (!GreffeManager::isAdherentAllowed($adherent)) {
      return GreffeManager::redirectToPurchaseService();
    }
    $ctx->greffe = Greffe::getInstance();
    $fields['email_deposit'] = $adherent->email_edi;
    $fields['compte_type'] = GreffeManager::COMPTE_SOCIAUX;
    $fields['forme_juridique'] = GreffeManager::FJ_SARL;
    $fields['is_gerant'] = false;
    $fields['is_public'] = true;
    $fields['mode_direction'] = GreffeManager::DIRECTION_CONSEIL_ADMINISTRATION;
    $fields['greffedossier_id'] = GreffeManager::getCurrentDossier()->getId();
  }

  $print = false;
  if ($req->hasAttribute('print', true)) {
    $print = (int)$req->print == 0 ? false : true;
  }
  $ctx->print = $print;

  $form_fields = array('id',
                       'user_id',
                       'greffecommune_id',
                       'greffedossier_id',
                       'civility',
                       'first_name',
                       'last_name',
                       'company',
                       'company_bis',
                       'forme_juridique',
                       'siren',
                       'siret',
                       'address',
                       'address_1',
                       'address_2',
                       'zipbox',
                       'zipcode',
                       'city',
                       'country_id');

  foreach ($adherent->getAttributes() as $key => $value) {
    if (in_array($key, $form_fields)) {
      switch ($key) {
        case 'siret':
          if (!$req->hasAttribute('id', true)) {
            $fields['siren'] = substr($value, 0, 9);
          }
          break;
        case 'forme_juridique':
          if (in_array($value, GreffeManager::$formes_juridique) && !$req->hasAttribute('id', true)) {
            $fields[$key] = array_search($value, GreffeManager::$formes_juridique);
          }
          break;
        default:
          $fields[$key] = $value;
          break;
      }
    }
  }

  if ($greffe && !empty($greffe->documents)) {
    $ctx->reponse_documents = array();
    foreach ($greffe->documents as $document) {
      if (strpos($document, '_envoi.pdf') > -1 || strpos($document, '_facture.pdf') > -1) {
        continue;
      }
      $ctx->reponse_documents[] = array('name' => $document,
                                        'url'  => '/' . $greffe->getResponseDocumentPath() . '/' . $document);
    }
  }

  $ctx->adherent = $adherent;
  $ctx->fields = $fields;
  $ctx->countries = Country::collect(array('order' => array('name_fr' => 'ASC')));
  $ctx->codes_insee = !empty($fields['zipcode']) ? greffeManager::getCodesInsee($fields['zipcode'], true) : array();

  NtdMiddleManager::setCurrentModule(NtdMiddleManager::MODULE_GREFFE);
  NtdMiddleManager::setBreadCrumb(array('Greffe' => '/middle/greffe',
                                        'Edition'));
  if ((!$greffe || $greffe->isEditable()) && !$print) {
    NtdMiddleManager::useTemplate();
  }
  else {
    $type_compte = $greffe->compte_type;
    $forme_juridique = $greffe->forme_juridique;
    $is_gerant = $greffe->is_gerant;
    $mode_direction = $greffe->mode_direction;
    $compte_public = $greffe->is_public;

    $docs = array();
    foreach (GreffeManager::getRequiredDocs($type_compte, $forme_juridique, $is_gerant, $mode_direction, $compte_public) as $doc) {
      $docs[$doc] = GreffeManager::$docs[$doc];
    }
    $ctx->documents = $docs;
    $ctx->registered_documents = $greffe->getDocuments();

    if (!$print) {
      $templates = array(null,
                         'skeleton.front',
                         'skeleton.middle',
                         'app/ntd/templates/middle/greffe.show.psp');
    }
    else {
      $templates = array(null,
                         'app/ntd/templates/middle/greffe.pdf.content.psp',
                         'app/ntd/templates/middle/greffe.show.psp');
    }
    $res->useTemplates($templates);
  }
  NtdMiddleManager::setSEO();

}
catch (Exception $e) {
  $err->add($e);
}
