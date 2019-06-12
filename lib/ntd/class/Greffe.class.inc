<?php

class Greffe extends ActiveRecord {
  const TABLE_DOCUMENTS = 'ntd_greffe_document';

  const STATUS_PENDING    = 0;
  const STATUS_COLLECTING = 1;
  const STATUS_COMPLETED  = 2;
  const STATUS_VALID      = 3;
  const STATUS_SENDED     = 10;
  const STATUS_ACCEPTED   = 11;
  const STATUS_REFUSED    = -1;

  const FLAG_DOCUMENTS_PURGED = 1;

  public static $statuses = array(self::STATUS_PENDING    => 'greffe.status.pending',
                                  self::STATUS_COLLECTING => 'greffe.status.collecting',
                                  self::STATUS_COMPLETED  => 'greffe.status.completed',
                                  self::STATUS_VALID      => 'greffe.status.valid',
                                  self::STATUS_SENDED     => 'greffe.status.sended',
                                  self::STATUS_ACCEPTED   => 'greffe.status.accepted',
                                  self::STATUS_REFUSED    => 'greffe.status.refused');


  public static function getStatuses() {
    $statuses = self::$statuses;
    foreach ($statuses as &$status) {
      $status = c(l($status));
    }
    return $statuses;
  }

  public function isEditable() {
    return $this->status >= self::STATUS_PENDING && $this->status < self::STATUS_VALID;
  }

  public function updateStatus() {
    if ($this->status == self::STATUS_VALID) {
      GreffeManager::generatePackage($this);
    }
    else if ($this->hasAllDocuments() && $this->status < self::STATUS_VALID && $this->status > self::STATUS_REFUSED) {
      $this->setAttribute('status', self::STATUS_COMPLETED);
    }
    else if (count($this->getDocuments()) > 0 && $this->status < self::STATUS_VALID && $this->status > self::STATUS_REFUSED) {
      $this->setAttribute('status', self::STATUS_COLLECTING);
    }
  }

  public function asXml() {
    $adherent = $this->getAdherent();
    $commune = $adherent->getGreffecommune();

    $date_remise = date('Y-m-d');
    $reference_client = $this->getReferenceClient();
    $numero_gestion = $this->getNumeroGestion();
    $designation = $adherent->company;
    $denomination_dap = $this->getDenominationDAP();
    $annule_et_remplace = $this->isAnnuleEtRemplace() ? 'true' : 'false';
    $comptes_consolides = $this->compte_type == GreffeManager::COMPTE_CONSOLIDE ? 'true' : 'false';
    $confidentialite = $this->is_public ? 'false' : 'true';
    $dispense_annexe = $this->hasDispenceAnnexe() ? 'true' : 'false';

    $doc = new DOMDocument('1.0', 'UTF-8');
    $root = $doc->createElement('DCA_DIRECT');

    $root->appendChild($doc->createElement('versionSchema', GreffeManager::XML_VERSION_SCHEMA));
    $root->appendChild($doc->createElement('idDepot', $this->id));
    $root->appendChild($doc->createElement('dateHeureGenerationXml', date('Y-m-d\TH:i:s')));
    $root->appendChild($doc->createElement('referenceClient', $reference_client));
    $root->appendChild($doc->createElement('codeGreffe', $commune->code_greffe));
    $root->appendChild($doc->createElement('numeroSiren', $adherent->siren));
    $root->appendChild($doc->createElement('numeroGestion', $numero_gestion));
    $root->appendChild($doc->createElement('designation', $designation));

    if (!empty($denomination_dap)) {
      $root->appendChild($doc->createElement('denominationDAP', $denomination_dap));
    }

    $root->appendChild($doc->createElement('dateRemise', $date_remise));
    $root->appendChild($doc->createElement('dateCloture', $this->closed_at));
    $root->appendChild($doc->createElement('annuleEtRemplace', $annule_et_remplace));
    $root->appendChild($doc->createElement('comptesConsolides', $comptes_consolides));
    $root->appendChild($doc->createElement('confidentialite', $confidentialite));
    $root->appendChild($doc->createElement('dispenseAnnexe', $dispense_annexe));

    $doc->appendChild($root);

    return $doc->saveXML();
  }

  /** export XML **/

  public function getReferenceClient() {
    $adherent = $this->getAdherent();
    return str_pad($adherent->getId(), 6, '0', STR_PAD_LEFT);
  }

  public function getNumeroGestion() {
    return $this->numero_gestion;
  }

  public function isAnnuleEtRemplace() {
    $dossier = $this->getGreffedossier();
    return $dossier->getGreffes()->count() > 1;
  }

  /** TODO **/
  public function getDenominationDAP() {
    return '';
  }

  public function hasDispenceAnnexe() {
    $type_compte = $this->compte_type;
    $forme_juridique = $this->forme_juridique;
    $is_gerant = $this->is_gerant;
    $mode_direction = $this->mode_direction;
    $compte_public = $this->is_public;
    $docs = GreffeManager::getRequiredDocs($type_compte, $forme_juridique, $is_gerant, $mode_direction, $compte_public);
    return !in_array(GreffeManager::DOC_ANNEXE, $docs);
  }

  /** Documents **/

  public function getDocuments() {
    $sql = 'SELECT * FROM '.self::TABLE_DOCUMENTS.' WHERE greffe_id = '.$this->getId();
    $results = $this->dbo->asArray($sql, null, 'type');
    return $results ? $results : array();
  }

  public function setDocuments($documents) {
    foreach ($documents as $key => $document) {
      $documents[$key]['greffe_id'] = $this->getId();
    }

    $this->dbo->exec('DELETE FROM '.self::TABLE_DOCUMENTS.' WHERE greffe_id = '.$this->getId());
    $this->dbo->insert(self::TABLE_DOCUMENTS, $documents);
    $this->updateStatus();
  }

  public function hasAllDocuments() {
    $documents = array_keys($this->getDocuments());
    $required_documents = GreffeManager::getRequiredDocs($this->compte_type, $this->forme_juridique, $this->is_gerant, $this->mode_direction, $this->is_public);

    $keys = array_diff($required_documents, $documents);
    if (!empty($keys)) {
      return false;
    }
    return true;
  }

  public function hasMandat() {
    $path = $this->dbo->fetchValue('SELECT path FROM '.self::TABLE_DOCUMENTS
                                   .' WHERE greffe_id = '.$this->getId().' AND type = '.GreffeManager::DOC_MANDAT_DEPOT);
    if (empty($path) || !file_exists($path)) {
      return false;
    }
    return true;
  }

  public function getDocumentPath() {
    return GreffeManager::getInternalDocumentPath() . '/' . $this->getId();
  }

  public function getResponseDocumentPath() {
    return GreffeManager::getResponseDocumentPath() . '/' . $this->getKey();
  }

  public function getPdfPath() {
    return GreffeManager::getPdfPath() . '/' . $this->getKey();
  }

  /** Hooks **/

  public function onBeforeCommit(&$hash) {
    if ($this->isItem()) {
      if (isset($hash['status']) && $this->status < self::STATUS_VALID && $hash['status'] == self::STATUS_VALID) {
        $date = Date::toDb(Date::now());
        $this->setAttribute('status_valid_at', $date);
      }
    }
  }

  public function onAfterCommit($hash) {
    $this->updateStatus();

    if ($this->status == self::STATUS_ACCEPTED) {
      $this->getGreffedossier()->setStatus(Greffedossier::STATUS_CLOSED);
    }
  }

  /** KWO **/

  public function asEditHash() {
    $hash = array();
    if ($this->isItem()) {
      $adherent = $this->getAdherent();
      $commune = $adherent->getGreffecommune();
      $hash['code_insee'] = $commune->code_insee;
      $hash['code_greffe'] = $commune->code_greffe;
      $hash = $this->asDocumentsEditHash($hash);
      $hash = $this->asResponseDocumentsEditHash($hash);
    }
    return $hash;
  }

  private function asDocumentsEditHash($hash) {
    $documents = $this->getDocuments();
    $required_documents = GreffeManager::getRequiredDocs($this->compte_type, $this->forme_juridique, $this->is_gerant, $this->mode_direction, $this->is_public);

    $html = '';
    $html .= '<table class="fixed">'."\n";
    $html .=   '<thead>'."\n";
    $html .=     '<tr>'."\n";
    $html .=       '<th>Document</th>'."\n";
    $html .=       '<th>Nom du fichier</th>'."\n";
    $html .=       '<th>Date de soumission</th>'."\n";
    $html .=     '</tr>'."\n";
    $html .=   '</thead>'."\n";
    $html .=   '<tbody>'."\n";
    foreach ($required_documents as $type) {
      $html .=     '<tr>'."\n";
      $html .=       '<td>'.GreffeManager::$docs[$type].'</td>'."\n";
      $html .=       '<td style="word-wrap: break-word;">'.basename($documents[$type]['path']).'</td>'."\n";
      $html .=       '<td>'.(Date::isValid($documents[$type]['register_at']) ? H::datenice($documents[$type]['register_at']) : 'Non soumis').'</td>'."\n";
      $html .=     '</tr>'."\n";
    }

    $extra_docs = array_diff(array_keys($documents), $required_documents);
    foreach ($extra_docs as $type) {
      $html .=     '<tr>'."\n";
      $html .=       '<td>'.GreffeManager::$docs[$type].'</td>'."\n";
      $html .=       '<td style="word-wrap: break-word;">'.basename($documents[$type]['path']).'</td>'."\n";
      $html .=       '<td>'.(Date::isValid($documents[$type]['register_at']) ? H::datenice($documents[$type]['register_at']) : 'Non soumis').'</td>'."\n";
      $html .=     '</tr>'."\n";
    }
    $html .=   '</tbody>'."\n";
    $html .= '</table>'."\n";

    $hash['documents'] = $html;
    return $hash;
  }

  private function asResponseDocumentsEditHash($hash) {
    $html = '';
    $html .= '<table class="fixed">'."\n";
    $html .=   '<thead>'."\n";
    $html .=     '<tr>'."\n";
    $html .=       '<th>Document reçus</th>'."\n";
    $html .=     '</tr>'."\n";
    $html .=   '</thead>'."\n";
    $html .=   '<tbody>'."\n";
    foreach ((array)$this->documents as $document) {
      $url = '/' . $this->getResponseDocumentPath() . '/' . $document;
      $html .=     '<tr>'."\n";
      $html .=       '<td><a href="'.$url.'" target="_blank">'.$document.'</a></td>'."\n";
      $html .=     '</tr>'."\n";
    }
    $html .=   '</tbody>'."\n";
    $html .= '</table>'."\n";

    $hash['documents_reponse'] = $html;
    return $hash;
  }

  public function asFinderHash($hash) {
    if ($this->isItem()) {
      $adherent = $this->getAdherent();
      $hash['siret'] = $adherent->siret;
      $hash['status'] = c(l(self::$statuses[$this->status]));
    }
    return $hash;
  }
}
