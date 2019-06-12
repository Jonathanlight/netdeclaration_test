<?php

class Formulairetype extends ActiveRecord {
  const TABLE_MILLESIME = 'ntd_formulairetype_millesime';

  const SEPARATOR_IMPRIME_FIELD_CODES = '_';

  const DOCUMENT_CODE_TVA = 1;
  const DOCUMENT_CODE_CVAE = 2;
  const DOCUMENT_CODE_IS = 3;
  const DOCUMENT_CODE_TS = 4;
  const DOCUMENT_CODE_IDENTIF = 5;
  const DOCUMENT_CODE_TDFC = 6;
  const DOCUMENT_CODE_DUCS = 7;
  const DOCUMENT_CODE_DUE = 8;
  const DOCUMENT_CODE_DADSU = 9;
  const DOCUMENT_CODE_RCM = 10;
  const DOCUMENT_CODE_LOC = 11;
  const DOCUMENT_CODE_DSI = 12;
  const DOCUMENT_CODE_IFU = 13;
  const DOCUMENT_CODE_HON = 14;

  const CODE_DAS2T = 'DAS2T';
  const CODE_DAS2TV = 'DAS2TV';

  const FLAG_REPETABLE = 1;
  const FLAG_OLD_SYSTEM = 2;
  const FLAG_EXPORT_AS_REPETABLE = 4;


  const PATH_PDF = 'doc/ntd/ftype';

  public static $flags = array(
    self::FLAG_OLD_SYSTEM => 'Système de formulaire v1',
    self::FLAG_EXPORT_AS_REPETABLE => 'Export au format répétable',
  );

  public static $document_codes = array(
    self::DOCUMENT_CODE_TVA => 'TVA',
    self::DOCUMENT_CODE_CVAE => 'CVAE',
    self::DOCUMENT_CODE_IS => 'IS',
    self::DOCUMENT_CODE_TS => 'TS',
    self::DOCUMENT_CODE_IDENTIF => 'Identif',
    self::DOCUMENT_CODE_TDFC => 'TDFC',
    self::DOCUMENT_CODE_DUCS => 'DUCS',
    self::DOCUMENT_CODE_DUE => 'DUE',
    self::DOCUMENT_CODE_DADSU => 'DADSU',
    self::DOCUMENT_CODE_RCM => 'RCM',
    self::DOCUMENT_CODE_LOC => 'LOC',
    self::DOCUMENT_CODE_DSI => 'DSI',
    self::DOCUMENT_CODE_IFU => 'IFU',
    self::DOCUMENT_CODE_HON => 'HON',
  );

  public static $document_labels = array(
    self::DOCUMENT_CODE_TVA => 'TVA',
    self::DOCUMENT_CODE_CVAE => 'CVAE',
    self::DOCUMENT_CODE_IS => 'IS',
    self::DOCUMENT_CODE_TS => 'TS',
    self::DOCUMENT_CODE_IDENTIF => 'Identif',
    self::DOCUMENT_CODE_TDFC => 'LIASSES FISCALES',
    self::DOCUMENT_CODE_DUCS => 'DUCS',
    self::DOCUMENT_CODE_DUE => 'DUE',
    self::DOCUMENT_CODE_DADSU => 'DADSU',
    self::DOCUMENT_CODE_RCM => 'RCM',
    self::DOCUMENT_CODE_LOC => 'LOC',
    self::DOCUMENT_CODE_DSI => 'DSI',
    self::DOCUMENT_CODE_IFU => 'IFU',
    self::DOCUMENT_CODE_HON => 'HON',
  );

  public function getDocumentCode() {
    return self::$document_codes[$this->document_code];
  }

  public function getCode() {
    return $this->code;
  }

  public function getFormulaireCode() {
    if ($this->document_code == self::DOCUMENT_CODE_IDENTIF) {
      return strtolower($this->getCode() . $this->getDocumentCode());
    }
    return strtolower($this->getDocumentCode() . $this->getCode());
  }

  public function getMillesimes() {
    return S('dbo')->query('SELECT m.*'
                          .' FROM ' . self::TABLE_MILLESIME . ' fm'
                          .' JOIN ' . T('millesime') . ' m ON fm.millesime_id=m.id'
                          .' WHERE formulairetype_id=' . $this->getId()
                          .' ORDER BY millesime_id')
                  ->asCollection('millesime');
  }

  public function getDetails() {
    $hash = array();
    $dectypes = array();
    foreach ($this->getDectypes() as $dectype) {
      $dectypes[] = Item::edit($dectype);
    }
    $hash['Dectype Liées'] = implode('<br>', $dectypes);
    return $hash;
  }

  public function isRepetable($millesime) {
    $millesime_id = $millesime;
    if ($millesime instanceOf Millesime) {
      $millesime_id = $millesime->getId();
    }
    return S('dbo')->fetchValue('SELECT is_repetable'
                                .' FROM '.Formulairetype::TABLE_MILLESIME
                                .' WHERE formulairetype_id = ' . $this->getId()
                                .' AND millesime_id = ' . $millesime_id);
  }

  public function isV1($millesime) {
    $millesime_id = $millesime;
    if ($millesime instanceOf Millesime) {
      $millesime_id = $millesime->getId();
    }
    return S('dbo')->fetchValue('SELECT is_v1'
                                .' FROM '.Formulairetype::TABLE_MILLESIME
                                .' WHERE formulairetype_id = ' . $this->getId()
                                .' AND millesime_id = ' . $millesime_id);
  }

  public function getIfieldsByMillesime($millesime, $filters=array(), $orders=array()) {
    $millesime_id = $millesime;
    if ($millesime instanceOf Millesime) {
      $millesime_id = $millesime->getId();
    }

    $col = Collection::getEmptyInstance('ifield');
    $filters_sql = empty($filters) ? '1' : $col->hash2sql($filters);

    $_orders = array();
    foreach ($orders as $key => $value) {
      if (!preg_match('/^[\w\.]+$/', $key.$value)) {
        S('log')->error('invalid order value ['.$key.$value.']', __METHOD__);
        continue ;
      }
      if (is_numeric($key)) {
        $_orders[] = $value;
      }
      else {
        $_orders[] = $key.(strtoupper($value) ===  'DESC' ? ' DESC' : '');
      }
    }
    $orders_sql = empty($orders) ? 'id ASC' : implode(', ', $_orders);

    $ifields = S('dbo')->query('SELECT '.T('ifield').'.*'
                                . ' FROM ' . T('ifield')
                                . ' JOIN ' . T('formulairetype') . ' '.T('formulairetype').' ON '.T('ifield').'.formulairetype_id='.T('formulairetype').'.id'
                                . ' JOIN ' . Ifield::TABLE_MILLESIME . ' ON '.Ifield::TABLE_MILLESIME.'.ifield_id='.T('ifield').'.id'
                                . ' WHERE ' .T('ifield').'.status=' . Ifield::STATUS_ONLINE
                                . ' AND ' .T('formulairetype').'.id=' . $this->getId()
                                . ' AND ' .Ifield::TABLE_MILLESIME.'.millesime_id=' . $millesime_id
                                . ' AND ' . $filters_sql
                                . ' ORDER BY ' . $orders_sql
                              )
                      ->asCollection('ifield');
    return $ifields;
  }

  /** **/

  public function asFinderHash($hash) {
    $hash['ifields_count'] = $this->getIfields()->count();
    $hash['itemplates_count'] = $this->getItemplates()->count();
    $hash['operations_count'] = $this->getOperations()->count();
    $hash['document_code'] = self::$document_codes[$hash['document_code']];
    $hash['flag_repetable'] = '';
    return $hash;
  }

  public function addMillesime($opts) {
    $millesime_id = (int)$opts['millesime_id'];
    $millesimes = $this->getMillesimes()->asSet('id');
    if ($millesime_id > 0 && !in_array($millesime_id, $millesimes)) {
      $record = array(
        'formulairetype_id' => $this->getId(),
        'millesime_id'      => $millesime_id,
        'is_repetable'      => (int)$opts['is_repetable'],
        'is_v1'             => (int)$opts['is_v1']
      );
      S('dbo')->insert(Formulairetype::TABLE_MILLESIME, $record);
    }
  }

  public function duplicateMillesime($millesime_new, $millesime_previous, $duplicate_template=true) {
    $changed = array('ifields' => array(),
                     'operations' => array());
    $fields = $this->getIfieldsByMillesime($millesime_previous);
    $operations = $this->getOperations(array('filters' => array('|REGEXP|millesimes' => '(^|,)' . $millesime_previous . '(,|$)')));
    foreach ($fields as $field) {
      $millesimes = $field->getMillesimes()->asSet('id');
      $data_millesimes = $field->getMillesimes()->asHash('id', 'is_extensible');
      $millesimes[] = $millesime_new;
      foreach ($millesimes as $millesime) {
        $field->addMillesime(array(
          'ifield_id'     => $field->getId(),
          'millesime_id'  => $millesime,
          'is_extensible' => $data_millesimes[$field->getId()]
        ));
      }
      $changed['ifields'][] = $field;
    }
    foreach ($operations as $operation) {
      $millesimes = $operation->millesimes;
      $millesimes[] = $millesime_new;
      $operation->setAttribute('millesimes', array_keys(array_combine($millesimes, $millesimes)));
      $changed['operations'][] = $operation;
    }

    $filters = array(
      'formulairetype_id' => $this->getId(),
      'millesime_id' => $millesime_previous
    );
    $itemplates = Itemplate::collect(array('filters' => $filters,
                                           'order' => array('version' => 'DESC')));
    if($itemplates->count() > 0 && $duplicate_template) {
      $itemplate = $itemplates->first();
      $itemplate = $itemplate->duplicate();
      $itemplate->commit(array('millesime_id' => $millesime_new,
                               'name' => 'Template Millesime [' . Millesime::getInstance($millesime_new)->name. ']',
                               'status' => 1));

    }
    $this->build();

    return $changed;
  }

  protected function onAfterCommit($attrs) {
    $this->build();
  }

  public function build() {

    if ($this->hasFlag(self::FLAG_OLD_SYSTEM)) {
      return;
    }

    $attributes = array();
    $ftypes_required = array();
    $millesimes = array();
    foreach ($this->getOperations(array('filters' => array('status' => Operation::STATUS_ACTIF))) as $operation) {
      $millesimes = array_merge($millesimes, $operation->millesimes);
      $fields = Operation::getFormulaFields($operation->method_args['formula']);
      foreach ($fields as $field) {
        if (is_numeric($field)) continue;
        if (strpos($field, '@') !== false) continue;
        if (strpos($field, '_') === false) continue;
        list($ftype_code, $field_code) = explode(Formulairetype::SEPARATOR_IMPRIME_FIELD_CODES, $field, 2);
        if ($ftype_code == 'FIDENTIF') $ftype_code = 'F-IDENTIF';
        elseif ($ftype_code == 'PIDENTIF') $ftype_code = 'P-IDENTIF';
        elseif ($ftype_code == 'TIDENTIF') $ftype_code = 'T-IDENTIF';
        elseif ($ftype_code == 'AIDENTIF') $ftype_code = 'A-IDENTIF';
        elseif ($ftype_code == 'AIDENTIFIFU') $ftype_code = 'A-IDENTIFIFU';
        elseif ($ftype_code == 'AIDENTIFHON') $ftype_code = 'A-IDENTIFHON';

        if ($ftype_code == $this->code) continue;
        $ftypes_required[$ftype_code]++;
      }
    }
    $attributes['formulairetype_required'] = array_keys($ftypes_required);

    foreach ($this->getIfields() as $ifield) {
      $millesimes = array_merge($millesimes, $ifield->getMillesimes()->asSet('id'));
    }
    $millesimes = array_keys(array_combine($millesimes, $millesimes));
    foreach ($millesimes as $millesime_id) {
      $this->addMillesime(array('millesime_id' => $millesime_id));
    }
    $this->setAttributes($attributes);
  }

  public function asView($view) {
    if ($view == 'preview') {
      return $this->code;
    }
    return parent::asView($view);
  }

  public function generatePdf(Declaration $declaration) {

    $path_target  = self::PATH_PDF.'/'.String::urlify($this->name).'-'.time().'.pdf';
    $path_source  = str_replace('.pdf', '.html', $path_target);

    // $content = H::get('/declaration.pdf.content', array('key' => $declaration->getKey(), 'ftype_id' => $this->id));
    $url = sprintf('/declaration.pdf.content?key=%s&ftype_id=%d', $declaration->getKey(),  $this->id);
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

    $adherent = $declaration->getAdherent();

    $header = Dectype::name($declaration->dectype_id);
    $footer = 'Déclaration N°' . $declaration->id . ' - ' . $adherent->company . ' - N° SIRET : ' . $adherent->siret;

    $opts = array('include' => array('formulairetype'),
                  'filters' => array('document_code' => Formulairetype::DOCUMENT_CODE_IDENTIF));
    $formulaires = $declaration->getFormulaires($opts);
    if ($formulaires->count() >= 1) {
        $formulaire = $formulaires->first();
        $datas = $formulaire->data;
    }
    if (is_array($datas)) {
        if (!empty($datas['CA']) && strtotime($datas['CA']) !== false) {
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

    $options = array('--header-center'    => '\''.utf8_decode($header).'\'',
                     '--footer-center'    => '\''.utf8_decode($footer).'\'',
                     '--header-font-size' => '9',
                     '--footer-font-size' => '6',
                     '--encoding'         => 'utf-8',
                     '--username'       => $username,
                     '--password'       => $password,
                     '--page-size'      => 'A4',
                     '--margin-top'     => '15',
                     '--margin-left'    => '10',
                     '--margin-right'   => '10',
                     '--margin-bottom ' => '5',
                     '--header-spacing' => '5',
                     '--footer-spacing' => '0',
                     '--outline-depth'  => '0');

    system('/bin/bash -c "export DISPLAY=127.0.0.1:123; /etc/kernix/bin/wkhtmltopdf '.NetDeclaration::asShellParams($options).' \''.$path_source.'\' \''.$path_target.'\'"');
    //unlink($path_source);

    return $path_target;
  }
}
