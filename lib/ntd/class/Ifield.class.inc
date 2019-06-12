<?php

// "Donnée créée";
// "Libellé modifié";
// "Imprimé"; -> formulairetype_id
// "Millésime"; -> millesime
// "Code EDI"; -> code_edi
// "Type segment"; -> type_segment
// "Composite"; -> type_composite
// "Simple"; -> type_simple
// "N°donnée simple"; -> no_donnee_simple
// "Libellé"; -> label
// "Indice donnée"; -> indice_donnee
// "Table EDI"; -> table_edi

class Ifield extends ActiveRecord {
  const TABLE_MILLESIME = 'ntd_ifield_millesime';

  public $imprime;
  public $values;
  public $required;
  public $_default_value;

  const STATUS_OFFLINE = 0;
  const STATUS_ONLINE = 1;

  const FLAG_REQUIRED = 1;
  const FLAG_DEPOSE_NEANT = 2;
  const FLAG_EXPORTABLE = 4;
  const FLAG_READONLY = 8;
  const FLAG_CCI_DEFAULT = 16;
  const FLAG_PAD_VALUE = 32;
  const FLAG_AUTOCOMPLETE_VALUES = 64;

  public static $statuses = array(
    self::STATUS_OFFLINE => 'hors ligne',
    self::STATUS_ONLINE => 'en ligne'
  );

  const TYPE_MOA_C516_5004 = 'moa.C516.5004';
  const TYPE_CCI_C889_7111 = 'cci.C889.7111';
  const TYPE_CUX_C504_6345 = 'cux.C504.6345';
  const TYPE_CUX_0000_5402 = 'cux.0000.5402';
  const TYPE_DTM_C507_2380 = 'dtm.C507.2380';
  const TYPE_FTX_C108_4440 = 'ftx.C108.4440';
  const TYPE_PCD_C501_5482 = 'pcd.C501.5482';
  const TYPE_QTY_C186_6060 = 'qty.C186.6060';
  const TYPE_RFF_C506_1154 = 'rff.C506.1154';
  const TYPE_NAD_C082_3039 = 'nad.C082.3039';
  const TYPE_NAD_C059_3036 = 'nad.C059.3036';
  const TYPE_NAD_C080_3036 = 'nad.C080.3036';
  const TYPE_NAD_C059_3042 = 'nad.C059.3042';
  const TYPE_NAD_C080_3042 = 'nad.C080.3042';
  const TYPE_NAD_0000_3164 = 'nad.0000.3164';
  const TYPE_NAD_0000_3251 = 'nad.0000.3251';
  const TYPE_NAD_0000_3207 = 'nad.0000.3207';
  const TYPE_NAD_C076_3148 = 'nad.C076.3148';
  const TYPE_NAD_C819_3228 = 'nad.C819.3228';
  const TYPE_NAD_C819_3229 = 'nad.C819.3229';
  const TYPE_NAD_C819_3042_1 = 'nad.C819.3042-1';
  const TYPE_NAD_C819_3042_2 = 'nad.C819.3042-2';
  const TYPE_FII_C078_3194 = 'fii.C078.3194';
  const TYPE_CPT_C593_1147 = 'cpt.C593.1147';
  const TYPE_CPT_C593_1146 = 'cpt.C593.1146';
  const TYPE_CTA_C056_3412 = 'cta.C056.3412';
  const TYPE_COM_C076_3148 = 'com.C076.3148';

  public static $types = array(
    self::TYPE_MOA_C516_5004 => 'Champ MOA : Champ monétaire',
    self::TYPE_CCI_C889_7111 => 'Champ CCI : Valeur codifiée',
    self::TYPE_CUX_C504_6345 => 'Champ CUX : Monnaie (code)',
    self::TYPE_CUX_0000_5402 => 'Champ CUX : Taux de change',
    self::TYPE_DTM_C507_2380 => 'Champ DTM : Date',
    self::TYPE_FTX_C108_4440 => 'Champ FTX : Saisie de texte',
    self::TYPE_PCD_C501_5482 => 'Champ PCD : Pourcentage',
    self::TYPE_QTY_C186_6060 => 'Champ QTY : Quantité',
    self::TYPE_RFF_C506_1154 => 'Champ RFF : Référence',
    self::TYPE_NAD_C082_3039 => 'Champ NAD : 01',
    self::TYPE_NAD_C059_3036 => 'Champ NAD : 02+03+04',
    self::TYPE_NAD_C080_3036 => 'Champ NAD : 02+03+04',
    self::TYPE_NAD_C059_3042 => 'Champ NAD : 06+05+07',
    self::TYPE_NAD_C080_3042 => 'Champ NAD : 06+05+07',
    self::TYPE_NAD_0000_3164 => 'Champ NAD : 08',
    self::TYPE_NAD_0000_3251 => 'Champ NAD : 09',
    self::TYPE_NAD_0000_3207 => 'Champ NAD : 10',
    self::TYPE_NAD_C076_3148 => 'Champ NAD : 12 ou 13',
    self::TYPE_NAD_C819_3228 => 'Champ NAD : 14',
    self::TYPE_NAD_C819_3229 => 'Champ NAD : 15',
    self::TYPE_NAD_C819_3042_1 => 'Champ NAD : 16',
    self::TYPE_NAD_C819_3042_2 => 'Champ NAD : 17',
    self::TYPE_FII_C078_3194 => 'Champ FII',
    self::TYPE_CPT_C593_1147 => 'Champ CPT 1147',
    self::TYPE_CPT_C593_1146 => 'Champ CPT 1146',
    self::TYPE_CTA_C056_3412 => 'Champ CTA',
    self::TYPE_COM_C076_3148 => 'Champ COM',
  );

  public static $segment_indexes = array(
    'NAD' => array(
      'type_simple.no_donnee_simple' => 'nad_index',
      '3039.01'   => '01',
      '3036.01'   => '02',
      '3036.02'   => '03',
      '3036.03'   => '04',
      '3042.01'   => '05',
      '3042.02'   => '06',
      '3042.03'   => '07',
      '3164.01'   => '08',
      '3251.01'   => '09',
      '3207.01'   => '10',
      '3148.01'   => '12',
      '3148.02'   => '13',
      '3228.01'   => '14',
      '3229.01'   => '15',
      '3042-1.01' => '16',
      '3042-1.02' => '17',
    ),
    'CUX' => array(
      '6345.01' => '01',
      '6345.02' => '02',
      '5402.01' => '03',
    ),
  );

  public static $flags = array(
    self::FLAG_REQUIRED            => 'Obligatoire',
    self::FLAG_DEPOSE_NEANT        => 'Déposé néant',
    self::FLAG_EXPORTABLE          => 'Exportable',
    self::FLAG_READONLY            => 'Non modifiable',
    self::FLAG_CCI_DEFAULT         => 'Champs CCI: valeur par défaut si non cochée (0)',
    self::FLAG_PAD_VALUE           => 'Formatter la valeur sur x caractères (selon maxlength) (0)',
    self::FLAG_AUTOCOMPLETE_VALUES => 'Champs CCI: Activer l\'autocompletion des valeurs',
  );

  public function renderHTML($field_index) {

    $html = '<div class="imprime-field"
                  data-type=":type_segment:"
                  data-imprime_code=":imprime_code:"
                  data-code=":code:"
                  data-default_value=":default_value:"
                  data-name=":name:"
                  data-index=":index:"';
    if ($this->hasFlag(self::FLAG_DEPOSE_NEANT)) {
      $html .= ' data-depose_neant="1" ';
    }
    if ($this->hasFlag(self::FLAG_READONLY)) {
      $html .= ' data-readonly="1" ';
    }
    if ($this->isRequired()) {
      $html .= ' data-required="1" ';
    }
    if ($this->isExtensible($this->imprime->getMillesime())) {
      $html .= ' data-extensible="1" ';
    }
    if ($this->hasFlag(self::FLAG_CCI_DEFAULT)) {
        $html .= ' data-has-default="1" ';
    }
    $html .= ' > ';

    $name = 'fields[' . $this->name . '][' . $field_index . ']';

    $html = str_replace(array(':imprime_code:',
                              ':code:',
                              ':index:',
                              ':type_segment:',
                              ':default_value:',
                              ':name:'),
                        array($this->imprime->getCode(),
                              $this->name,
                              $field_index,
                              $this->type_segment,
                              $this->getDefaultValue(),
                              $name),
                        $html);
    $classname = 'Ifield' . $this->type_segment;
    if (class_exists($classname) && method_exists($classname, 'renderHTML')) {
      $html .= call_user_func(array($classname, 'renderHTML'),
                              $this,
                              $name,
                              $this->getValue($field_index));
    }
    else {
      $html .= 'not implemented [' . $this->type_segment . ']';
    }
    $html .= '</div>';

    return $html;
  }

  public function validate($index, $other_field = null) {
    $classname = 'Ifield' . $this->type_segment;
    $value = $this->asTradeXpressExportHash($index);
    if ($this->isRequired() && empty($value)) {
      throw new FieldException($this, $index, $this->imprime->getIndex(), 'Ce champ est obligatoire.');
    }
    $value = $this->getValue($index);
    if (class_exists($classname) && method_exists($classname, 'validate')) {
      try {
        call_user_func(array($classname, 'validate'),
                       $this,
                       $value, $other_field);
      }
      catch (Exception $e) {
        throw new FieldException($this, $index, $this->imprime->getIndex(), $e->getMessage());
      }
    }
  }

  public function asTradeXpressExportHash($index) {
    $classname = 'Ifield' . $this->type_segment;

    if (class_exists($classname) && method_exists($classname, 'asTradeXpressExportHash')) {
      $value = call_user_func(array($classname, 'asTradeXpressExportHash'),
                              $this,
                              $this->getValue($index));
    }
    else {
      $value = $this->getValue($index);
    }

    $maxlength = (int)$this->maxlength;
    if ($this->hasFlag(self::FLAG_PAD_VALUE) && $maxlength > 0) {
      $value = str_pad($value, $maxlength, '0', STR_PAD_LEFT);
    }

    return $value;
  }


  /* ----- HOOK ----- */
  protected function onBeforeCommit(&$hash) {
    if (isset($hash['extensible'])) {
      $hash['indice_donnee'] = $hash['extensible'] > 0 ? '0001' : '0000';
      unset($hash['extensible']);
    }
    if (!empty($hash['type'])) {
      list($hash['type_segment'], $hash['type_composite'], $hash['type_simple']) = explode('.', $hash['type']);
    }
    if ($hash['table_edi'] == 'EM') {
      $hash['no_donnee_simple'] = '02';
    }
  }

  protected function onAfterCommit($hash) {
    $this->setAttribute('code',
                        self::getIfieldCode($this->getFormulairetype()->code,
                                            $this->code_edi,
                                            $this->type_simple,
                                            $this->no_donnee_simple));
    $this->setAttribute('type', $this->getType());
  }

  public function onFind($finder) {
    $coll = $finder->getCollection();
    $filters = $coll->getFilters();
    foreach (self::$flags as $value => $label) {
      if (isset($filters['flag_' . $value])) {
        $not = $filters['flag_' . $value] < 1 ? '!' : '';
        $filters['|' . $not . '&|flags'] = $value;
        unset($filters['flag_' . $value]);
      }
      if (isset($filters['repetable'])) {
        $not = $filters['repetable'] < 1 ? '!' : '';
        $filters['|' . $not . '=|indice_donnee'] = '0001';
        unset($filters['repetable']);
      }
    }

    if (isset($filters['millesimes'])) {
      $millesime_id = (int)$filters['millesimes'];
      unset($filters['millesimes']);

      $sql = 'SELECT '.T('ifield').'.*'
              . ' FROM ' . T('ifield')
              . ' JOIN ' . T('formulairetype') . ' '.T('formulairetype').' ON '.T('ifield').'.formulairetype_id='.T('formulairetype').'.id'
              . ' JOIN ' . Ifield::TABLE_MILLESIME . ' ON '.Ifield::TABLE_MILLESIME.'.ifield_id='.T('ifield').'.id'
              . ' WHERE ';
      $sql .= $coll->hash2sql($filters);
      $sql .= ' AND ' .Ifield::TABLE_MILLESIME.'.millesime_id=' . $millesime_id;
      $coll->setSql($sql);
    }
    else {
      $coll->setFilters($filters);
    }
  }

  /* ----- get / set / is ----- */
  public static function getIfieldCode($name, $code_edi, $type_simple, $no_donnee_simple) {
    return implode('_', array($name,
                              $code_edi,
                              $type_simple,
                              $no_donnee_simple));
  }

  public function getValue($index) {
    if (!isset($this->values[$index])) return $this->getDefaultValue();
    return $this->values[$index];
  }

  public function getValuesCount() {
    return count($this->values);
  }

  public function setImprime($imprime) {
    $this->imprime = $imprime;
  }

  public function setValues($values) {
    $this->values = (array) $values;
  }

  public function setDefaultValue($default_value) {
    $this->_default_value = $default_value;
  }

  public function getDefaultValue() {
    if ($this->_default_value !== null) {
      return $this->_default_value;
    }
    return $this->default_value;
  }

  public function setRequired($required) {
    $this->required = $required;
  }

  public function isRequired() {
    if ($this->required !== null) {
      return $this->required;
    }
    return $this->hasFlag(self::FLAG_REQUIRED);
  }

  public function getFullcode() {
    return (($this->imprime) ? $this->imprime->getCode() : $this->getFormulairetype()->code) . '_' . $this->name;
  }

  public function getValues() {
    return $this->values;
  }

  public function getTableEDI() {
    return $this->table_edi;
  }

  public function isExtensible($millesime) {
    if ($millesime instanceOf Millesime) {
      $millesime_id = $millesime->getId();
    }
    return S('dbo')->fetchValue('SELECT is_extensible'
                                .' FROM '.self::TABLE_MILLESIME
                                .' WHERE ifield_id = ' . $this->getId()
                                .' AND millesime_id = ' . $millesime_id);
  }

  public function asFinderHash($hash) {
    //type_field
    $hash['default_value'] = $this->default_value;
    $hash['is_extensible'] = '';
    $hash['exportable'] = $this->hasFlag(self::FLAG_EXPORTABLE) ? 'oui' : '-';
    $hash['obligatoire'] = $this->hasFlag(self::FLAG_REQUIRED) ? 'oui' : '-';
    $hash['type'] = self::$types[$this->getType()];
    $hash['millesimes'] = implode(', ', $this->getMillesimes()->asSet('name'));
    return $hash;
  }

  public function asEditHash() {
    $hash = array();
    if ($this->isLoaded()) {
      //
    }
    $hash['type'] = $this->getType();
    return $hash;
  }

  public function getType() {
    return $this->type_segment . '.' . $this->type_composite . '.' . $this->type_simple;
  }

  public function addMillesime($opts) {
    $millesime_id = (int)$opts['millesime_id'];
    $millesimes = $this->getMillesimes()->asSet('id');
    if ($millesime_id > 0 && !in_array($millesime_id, $millesimes)) {
      $record = array(
        'ifield_id'     => $this->getId(),
        'millesime_id'  => $millesime_id,
        'is_extensible' => (int)$opts['is_repetable']
      );
      S('dbo')->insert(self::TABLE_MILLESIME, $record);
    }
  }

  public function maxIndex() {
      if (count(array_keys((array)$this->values)) > 0) {
          return max(array_keys((array)$this->values));
      } else {
          return 0;
      }
  }

}
