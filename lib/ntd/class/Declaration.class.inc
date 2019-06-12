<?php

// TODO : liaison declaration - suivi (onDestroy)

class Declaration extends ActiveRecord implements OperationDataProvider {

  const RCM_2777_2018_DECTYPE_ID = 379;
  const RCM_2777_2019_DECTYPE_ID = 396;

  const STATUS_BROUILLON = -10;
  const STATUS_EDITABLE = 0;
  const STATUS_READY_TO_SEND = 1;
  const STATUS_SENT_TO_TRADXPRESS = 2;
  const STATUS_RECEIVED_BY_TRADXPRESS = 3;

  public static $statuses = array(
    self::STATUS_BROUILLON => '0. brouillon',
    self::STATUS_EDITABLE => '1. éditable',
    self::STATUS_READY_TO_SEND => '2. prête à être envoyée',
    self::STATUS_SENT_TO_TRADXPRESS => '3. Envoyée à Tx',
    self::STATUS_RECEIVED_BY_TRADXPRESS => '4. Pris en compte par Tx',
  );

  public static $statuses_front = array(
    self::STATUS_BROUILLON => 'brouillon',
    self::STATUS_EDITABLE => 'en attente d\'envoi',
    self::STATUS_READY_TO_SEND => 'Télétransmise au(x) destinataire(s)',
    self::STATUS_SENT_TO_TRADXPRESS => 'Envoyée à NetDeclaration',
    self::STATUS_RECEIVED_BY_TRADXPRESS => 'Pris en compte par NetDeclaration',
  );

  const PATH_PDF = 'doc/ntd/imprime';

  private $_imprimes;

  public function asWebServiceRows() {
    try {
      $declarant = $emetteur = $this->getAdherent();
      $dectype = $this->getDectype();
      if (!$dectype->hasFlag(Dectype::FLAG_OLD_SYSTEM)) {
        $this->generateTradeExpressData();
      }
      $formulaires = array();
      if (!$dectype->hasFlag(Dectype::FLAG_OLD_SYSTEM)) {
        foreach ($dectype->getFormulairetypes(array('order' => array('ftype_position' => 'ASC'))) as $ftype) {
          foreach ($this->getFormulaires(array('filters' => array('status' => Formulaire::STATUS_ACTIF,
                                                                  'formulairetype_id' => $ftype->getId()),
                                               'order' => array('position' => 'ASC',
                                                                'id' => 'ASC',))) as $formulaire) {
            $formulaires[] = $formulaire;
          }
        }
      }
      else {
        $formulaires = $this->getFormulaires(array('filters' => array('status' => Formulaire::STATUS_ACTIF),
                                                   'order' => array('position' => 'ASC',
                                                                    'formulairetype_id' => 'ASC',
                                                                    'id' => 'ASC',)));
      }
      if ($declarant->adherent_id > 0) {
        $emetteur = Adherent::getInstance((int) $declarant->adherent_id);
      }

      $entete_row = array(
        'EtatExport' => $this->status,
        'TypeDoc' => Formulairetype::$document_codes[$dectype->document_code_export],
        'TypeDeclaration' => $dectype->code,
        'Millesime' => $dectype->getMillesime()->name,
        'RefEnvoi' => $this->getId(),
        'MailRep' => $declarant->email_edimessage,

        'Emetteur_SIRET' => substr($emetteur->siret, 0, 35),
        'Emetteur_Qualite' => substr(Adherent::$export_types[$emetteur->type], 0, 35),
        'Emetteur_Nom1' => substr($emetteur->company, 0, 35),
        'Emetteur_Nom2' => substr('', 0, 35),
        'Emetteur_Rue1' => substr($emetteur->address, 0, 35),
        'Emetteur_Rue2' => substr($declarant->address_1, 0, 35),
        'Emetteur_Rue3' => substr($declarant->address_2, 0, 35),
        'Emetteur_Ville' => substr($emetteur->city, 0, 35),
        'Emetteur_CodePostal' => substr($emetteur->zipcode, 0, 5),


        'Declarant_SIRET' => substr($declarant->siret, 0, 35),
        'Declarant_Nom1' => substr($declarant->company, 0, 35),
        'Declarant_Nom2' => substr('', 0, 35),
        'Declarant_Rue1' => substr($declarant->address, 0, 35),
        'Declarant_Rue2' => substr($declarant->address_1, 0, 35),
        'Declarant_Rue3' => substr($declarant->address_2, 0, 35),
        'Declarant_Ville' => substr($declarant->city, 0, 35),
        'Declarant_CodePostal' => substr($declarant->zipcode, 0, 5),
      );

      try {
        $entete_row['Declarant_Pays'] = substr($declarant->getCountry()->code, 0, 3);
      }
      catch (Exception $e) {
        S('log')->error('Declarant country not valid [' . $declarant->country_id . ']', __METHOD__);
        $entete_row['Declarant_Pays'] = '';
      }

      try {
        $entete_row['Emetteur_Pays'] = substr($emetteur->getCountry()->code, 0, 3);
      }
      catch (Exception $e) {
        S('log')->error('Emmeteur country not valid [' . $emetteur->country_id . ']', __METHOD__);
        $entete_row['Emetteur_Pays'] = '';
      }


      if (!$dectype->hasFlag(Dectype::FLAG_OLD_SYSTEM) || count($dectype->destinataires) > 0) {
        foreach (Destinataire::$types_exported as $type) {
          $entete_row['Dest' . $type] = (int) isset($this->destinataires[$type]);
        }

        if ($this->destinataires[Destinataire::TYPE_OGA]['siretoga']) {
          $oga_details = array('siret' => $this->destinataires[Destinataire::TYPE_OGA]['siretoga']);
          $oga_details_agrement = $this->destinataires[Destinataire::TYPE_OGA]['idoga'];
        }
      }
      elseif ($dectype->hasFlag(Dectype::FLAG_OLD_SYSTEM)) {
        $oga_details = null;
        foreach ($formulaires as $formulaire) {
          $data = $formulaire->data;
          if (!empty($data['OGA'])) {
            $oga_details = array('siret' => $data['OGA']);
            $oga_details_agrement = $data['IDOGA'];
            break;
          }
        }
      }

      // ----- Entete OGA
      $entete_row['DestOGA'] = 0;
      if ($oga_details !== null && Adherent::exists($oga_details)) {
        $adherent_oga = Adherent::getInstance($oga_details);
        $entete_row['DestOGA'] = 1;
        $entete_row['OGA_NoRefInterneOGA'] = substr($oga_details_agrement, 0, 70);
        $entete_row['OGA_SIRET'] = substr($adherent_oga->siret, 0, 35);

        $entete_row['OGA_Nom1'] = substr($adherent_oga->company, 0, 35);
        $entete_row['OGA_Nom2'] = substr('', 0, 35);

        $entete_row['OGA_Rue1'] = substr($adherent_oga->address, 0, 35);
        $entete_row['OGA_Rue2'] = substr($adherent_oga->address_1, 0, 35);
        $entete_row['OGA_Rue3'] = substr($adherent_oga->address_2, 0, 35);

        $entete_row['OGA_Ville'] = substr($adherent_oga->city, 0, 35);
        $entete_row['OGA_CodePostal'] = substr($adherent_oga->zipcode, 0, 5);
        try {
          $entete_row['OGA_Pays'] = substr($adherent_oga->getCountry()->code, 0, 3);
        }
        catch (Exception $e) {
          S('log')->error('OGA country not valid [' . $adherent_oga->country_id . ']', __METHOD__);
          $entete_row['OGA_Pays'] = '';
        }
      }


      // ----- Entete CEC
      if ($dectype->hasFlag(Dectype::FLAG_OLD_SYSTEM)) {
        $entete_row['DestCEC'] = 0;
        if (isset($this->destinataires[Destinataire::TYPE_CEC])) {
          $entete_row['DestCEC'] = 1;
          $entete_row['CEC_NoRefInterneCEC'] = substr($this->destinataires[Destinataire::TYPE_CEC]['no_ref_interne_cec'], 0, 70);
          $entete_row['CEC_SIRET'] = substr($this->destinataires[Destinataire::TYPE_CEC]['siret'], 0, 35);
          $entete_row['CEC_Nom1'] = substr($this->destinataires[Destinataire::TYPE_CEC]['nom_1'], 0, 35);
          $entete_row['CEC_Nom2'] = substr($this->destinataires[Destinataire::TYPE_CEC]['nom_2'], 0, 35);
          $entete_row['CEC_Rue1'] = substr($this->destinataires[Destinataire::TYPE_CEC]['rue_1'], 0, 35);
          $entete_row['CEC_Rue2'] = substr($this->destinataires[Destinataire::TYPE_CEC]['rue_2'], 0, 35);
          $entete_row['CEC_Rue3'] = substr($this->destinataires[Destinataire::TYPE_CEC]['rue_3'], 0, 35);
          $entete_row['CEC_Ville'] = substr($this->destinataires[Destinataire::TYPE_CEC]['ville'], 0, 35);
          $entete_row['CEC_CodePostal'] = substr($this->destinataires[Destinataire::TYPE_CEC]['code_postal'], 0, 5);
          $entete_row['CEC_Pays'] = substr(Country::exists((int) $this->destinataires[Destinataire::TYPE_CEC]['pays']) ? Country::getInstance((int) $this->destinataires[Destinataire::TYPE_CEC]['pays'])->code : 'FR', 0, 3);
        }
      }


      // ----- Entete F-identif & Row Formulaires
      $identif_row = array();
      $formulaire_rows = array();
      $formulairetype_counts = array();
      foreach ($formulaires as $formulaire) {
        $row = array();

        $formulaire_type = $formulaire->getFormulairetype();
        $formulaire_prefix = $formulaire_type->prefix_export;

        $millesime = $dectype->getMillesime();
        $ftype_is_repetable = $formulaire_type->isRepetable($millesime);

        if ($ftype_is_repetable || $formulaire_type->hasFlag(Formulairetype::FLAG_EXPORT_AS_REPETABLE)) {
          $formulairetype_counts[$formulaire_type->getId()]++;
          $formulaire_prefix .= '/' . ($formulairetype_counts[$formulaire_type->getId()]);
        }

        foreach ($formulaire->data as $field => $value) {
          // jdrzewinski @ correlation des champs entre nouveau et ancien système
          if ($formulaire_type->name === "f_identif" && $formulaire_type->hasFlag(Formulairetype::FLAG_OLD_SYSTEM)
              && $dectype->document_code == Formulairetype::DOCUMENT_CODE_CVAE) {
            if ($field === "AA1") continue ;
            $field = str_replace(array('AA2', 'AA3', 'AA4', 'AA5', 'AA8', 'AA7', 'AA6'),
                                 array('AA02', 'AA03', 'AA05', 'AA06', 'AA10', 'AA09', 'AA08'),
                                 $field);
          } elseif ($formulaire_type->code == 'DAS2TV') {

              if ($field == 'ZZ1') {
                  continue;
              } else if ($field == 'AG14_1') {
                  if ($formulaire->data['ZZ1']) {
                    $row[$formulaire_prefix . '_AG14'] = $value;
                  }
                  continue;
              } else if ($field == 'AG14_2') {
                  if (!$formulaire->data['ZZ1']) {
                    $row[$formulaire_prefix . '_AG14'] = $value;
                  }
                  continue;
              }
          } elseif ($formulaire_type->code == 'ifu2561') {
              if ($field == 'ZZ1') {
                  continue;
              } else if ($field == 'AE14_1') {
                  if ($formulaire->data['ZZ1']) {
                      $row[$formulaire_prefix . '_AE14'] = $value;
                  }
                  continue;
              } else if ($field == 'AE14_2') {
                  if (!$formulaire->data['ZZ1']) {
                      $row[$formulaire_prefix . '_AE14'] = $value;
                  }
                  continue;
              }
              if ($field == 'ZZ2') {
                  continue;
              } else if ($field == 'AG14_1') {
                  if ($formulaire->data['ZZ2']) {
                      $row[$formulaire_prefix . '_AG14'] = $value;
                  }
                  continue;
              } else if ($field == 'AG14_2') {
                  if (!$formulaire->data['ZZ2']) {
                      $row[$formulaire_prefix . '_AG14'] = $value;
                  }
                  continue;
              }
          } elseif ($formulaire_type->code == '2777') {
              if (substr($field, 0, 2) == "ZZ") {
                  continue;
              }
          }
          $row[$formulaire_prefix . '_' . $field] = $value;
        }
        if ($dectype->hasFlag(Dectype::FLAG_OLD_SYSTEM) && $formulaire_type->document_code == Formulairetype::DOCUMENT_CODE_IDENTIF) {
          $identif_row = $row;
        }
        else {
          $formulaire_rows[$formulaire->getId()] = $row;
        }
      }


      $rows = array();
      $rows[] = $entete_row;
      if ($identif_row) {
        $rows[] = $identif_row;
      }
      foreach ($formulaire_rows as $row) {
        $rows[] = $row;
      }
      array_walk_recursive($rows, "Declaration::cleanWebserviceValue");

      return $rows;
    }
    catch (Exception $e) {
      S('log')->error($e, __METHOD__);
      S('log')->debug($this->getAttributes(), __METHOD__);
      return false;
    }
  }

  public function generateTradeExpressData() {
    $dectype = $this->getDectype();
    foreach ($this->getFormulaires(array('filters' => array('status' => Formulaire::STATUS_ACTIF))) as $formulaire) {
      $ftype = $formulaire->getFormulairetype();
      if ($ftype->hasFlag(Formulairetype::FLAG_OLD_SYSTEM)) continue;
      $imprime = new Imprime();
      $imprime->setFormulaire($formulaire, $dectype->getFtypeMillesime($ftype));
      $formulaire->setAttribute('data', $imprime->asTradeXpressExportHash());
    }
  }

  public static function cleanWebserviceValue(&$value, $key) {
     // jdrzewinski @ Mantis #21979 : clean du pipe sur les values
    $value = str_replace(array("\r\n", "\r", "\n", "|"), array(" ", " ", " ", ","), $value);
  }


  protected function onBeforeDestroy() {
    $formulaires = $this->getFormulaires();
    foreach ($formulaires as $formulaire) {
      $formulaire->destroy();
    }
  }

  public static function getInstanceAuth($id, $user) {
    $declaration = Declaration::getInstance($id);
    if ($declaration->getAdherent()->user_id != $user->getId()) {
      throw new MaliciousException();
    }
    return $declaration;
  }

  public function asFinderHash($hash) {
    if ($this->status == self::STATUS_EDITABLE) {
      $hash['_color'] = 'green';
    }
    elseif ($this->status == self::STATUS_READY_TO_SEND) {
      $hash['_color'] = 'yellow';
    }
    elseif ($this->status == self::STATUS_SENT_TO_TRADXPRESS) {
      $hash['_color'] = 'blue';
    }
    elseif ($this->status == self::STATUS_RECEIVED_BY_TRADXPRESS) {
      $hash['_color'] = 'green';
    }

    try {
      $dectype = $this->getDectype();
      $adherent = $this->getAdherent();

      $hash['dectype_name'] = $dectype->name;
      $hash['dectype_millesime_name'] = $dectype->getMillesime()->name;
      $hash['adherent_siret'] = $adherent->siret;
      $hash['adherent_company'] = $adherent->company;

    } catch (Exception $e) {
      error_log($e->getMessage());
    }

    return $hash;
  }

  public function generatePdf() {

    $dectype = $this->getDectype();
    $path_target  = self::PATH_PDF.'/'.String::urlify($dectype->name).'-'.time().'.pdf';
    $path_source  = str_replace('.pdf', '.html', $path_target);


    $url = '/declaration.pdf.content?key='.$this->getKey();
    $prefix  = P('app.url.secure') ? 'https://' : 'http://';
    if (P('auth.login')) {
      $prefix .= P('auth.login');
      if (P('auth.password')) {
        $prefix .= ':'.P('auth.password');
      }
      $prefix .= '@';
    }
    $prefix .= P('app.domain');
    $prefix .= P('app.url.port') ? ':'.P('app.url.port') : '';
    $url = $prefix.$url;

    // Use cURL (H::get and file_get_contents don't work)
    $curl_handle = curl_init();
    curl_setopt($curl_handle, CURLOPT_URL, $url);
    curl_setopt($curl_handle, CURLOPT_CONNECTTIMEOUT, 2);
    curl_setopt($curl_handle, CURLOPT_RETURNTRANSFER, 1);
    curl_setopt($curl_handle, CURLOPT_SSL_VERIFYPEER, false);
    $content = curl_exec($curl_handle);
    curl_close($curl_handle);


    $adherent = $this->getAdherent();

    $header = Dectype::name($this->dectype_id);
    $footer = 'Déclaration N°' . $this->id . ' - ' . $adherent->company . ' - N° SIRET : ' . $adherent->siret;

    $opts = array('include' => array('formulairetype'),
                  'filters' => array('document_code' => Formulairetype::DOCUMENT_CODE_IDENTIF));
    $formulaires = $this->getFormulaires($opts);
    if ($formulaires->count() >= 1) {
        $formulaire = $formulaires->first();
        $datas = $formulaire->data;
    }

    if (is_array($datas)) {
        if (!empty($datas['CA']) && strtotime($datas['CA']) !== false && $dectype->code != Dectype::CODE_DAS2T) {
            $footer .= ' - Début : ' . date("d/m/Y", strtotime($datas['CA']));
        } elseif (!empty($datas['BB']) && strtotime($datas['BB']) !== false) {
            $footer .= ' - Début : ' . date("d/m/Y", strtotime($datas['BB']));
        }
        if (!empty($datas['CB']) && strtotime($datas['CB']) !== false) {
            $footer .= ' - Fin : ' . date("d/m/Y", strtotime($datas['CB']));
        } elseif (!empty($datas['BC']) && strtotime($datas['BC']) !== false) {
            $footer .= ' - Fin : ' . date("d/m/Y", strtotime($datas['BC']));
        }
    }

    $fp = fopen($path_source, 'w');
    fwrite($fp, $content);
    fclose($fp);

    if (P('auth.login') && P('auth.password')) {
      $username = P('auth.login');
      $password = P('auth.password');
    } else {
      $username = null;
      $password = null;
    }

      $footer = str_replace('\'', ' ', $footer);

      $options = array('--header-center'    => '\''.utf8_decode($header).'\'',
                     '--footer-center'      => '\''.utf8_decode($footer).'\'',
                     '--header-font-size' => '9',
                     '--footer-font-size' => '6',
                     '--username'         => $username,
                     '--password'         => $password,
                     '--encoding'         => 'utf-8',
                     '--page-size'        => 'A4',
                     '--margin-top'       => '15',
                     '--margin-left'      => '10',
                     '--margin-right'     => '10',
                     '--margin-bottom '   => '15',
                     '--header-spacing'   => '5',
                     '--footer-spacing'   => '0',
                     '--outline-depth'    => '0');
    system('/bin/bash -c "export DISPLAY=127.0.0.1:123; /etc/kernix/bin/wkhtmltopdf '.NetDeclaration::asShellParams($options).' \''.$path_source.'\' \''.$path_target.'\'"');
    //unlink($path_source);


    return $path_target;
  }

  public function getImprimes() {
    if (!is_array($this->_imprimes)) {
      $dectype = $this->getDectype();
      $this->_imprimes = array();
      foreach ($this->getFormulaires(array('filters' => array('status' => Formulaire::STATUS_ACTIF),
                                           'order' => array('position' => 'ASC',
                                                            'formulairetype_id' => 'ASC',
                                                            'id' => 'ASC'))) as $formulaire) {
        $imprime = new Imprime();
        $imprime->setFormulaire($formulaire, $dectype->getFtypeMillesime($formulaire->formulairetype_id));
        $this->_imprimes[$imprime->getCode()][$imprime->getIndex()] = $imprime;
      }
    }
    return $this->_imprimes;
  }

  public function validateFields() {
    $exceptions = array();
    foreach ($this->getImprimes() as $imprime) {
      $exceptions = array_merge($exceptions, $imprime->validateFields());
    }
    return $exceptions;
  }

  public function validateOperations() {
    $exceptions = array();
    foreach ($this->getImprimes() as $imprime) {
      $exceptions = array_merge($exceptions, $imprime->validateOperations(true, $this));
    }
    return $exceptions;
  }

  public function getValues($imprime_code, $imprime_index, $field_code) {
    return $this->_imprimes[$imprime_code][$imprime_index]->getField($field_code)->getValues();
  }

  public function ImprimeExists($imprime_code) {
    $this->getImprimes();
    return isset($this->_imprimes[$imprime_code]);
  }

  public function canDuplicate() {
    if (!$this->isLoaded()) return false;
    if (!$this->getDectype()->isOnline()) return false;
    if ($this->status < Declaration::STATUS_RECEIVED_BY_TRADXPRESS) return false;
    if (!Suivi::exists(array('declaration_id' => $this->getId()))) return false;
    if (in_array($this->getDectype()->document_code, array(Formulairetype::DOCUMENT_CODE_TDFC, Formulairetype::DOCUMENT_CODE_IFU, Formulairetype::DOCUMENT_CODE_HON))) return true;
    $suivi = Suivi::getInstance(array('declaration_id' => $this->getId()));
    $opts = array('filters' => array('flg_depot' => 0,
                                     array('OR' => array('flg_envoi' => 0)),
                                     array('OR' => array('flg_ack' => 0))));
    $destinataires = $suivi->getDestinataires($opts);
    return $destinataires->count() > 0;
  }

  public function getMissingRequired() {
    $dectype = $this->getDectype();

    $ftypes = $dectype->getFormulairetypes(array('filters' => array('ntd_dectype_formulairetype.type' => Dectype::RELATION_TYPE_OBLIGATOIRE)));
    $formulaires = $this->getFormulaires(array('filters' => array('status' => Formulaire::STATUS_ACTIF)))->asHash('formulairetype_id',
                                                                                                                  'formulairetype_id');
    $missing_ftypes = array();
    foreach ($ftypes as $ftype) {
      if (!isset($formulaires[$ftype->getId()])) {
        $missing_ftypes[] = $ftype->code;
      }
    }
    return $missing_ftypes;
  }

  public function getStatus() {

    $status = Declaration::$statuses_front[$this->status];
    $destinataires = array_map(function ($value) {
      return Destinataire::$types[$value];
    }, array_keys($this->destinataires));
    $dectype = $this->getDectype();
    if ($dectype->hasFlag(Dectype::FLAG_OLD_SYSTEM) && count($dectype->destinataires) < 1) {
      $destinataires = array('DGFiP');
    }
    $status = str_replace('au(x) destinataire(s)', implode(', ', $destinataires), $status);
    return $status;
  }


}
