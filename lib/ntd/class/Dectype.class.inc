<?php

class Dectype extends ActiveRecord {

  const RELATION_TYPE_OBLIGATOIRE = 0;
  const RELATION_TYPE_ANNEXE = 1;

  const REF_PAIEMENT_TYPE_ECHEANCE_ACCOMPTE = 'A';
  const REF_PAIEMENT_TYPE_ECHEANCE_SOLDE = 'S';

  const FLAG_OLD_SYSTEM = 1;
  const FLAG_STEP_DISPLAY = 2;
  const FLAG_PRINT_ONE_PAGE = 4;

  const PARAMS_DEFAULT_VALUES = 'default_values';
  const PARAMS_REQUIRED_FIELDS = 'required_fields';

  const DECTYPE_DOCUMENT_CODE_HON = 14;

  const CODE_DAS2T = 'DAS2T';


  public static $relation_types = array(
    self::RELATION_TYPE_OBLIGATOIRE => 'obligatoire',
    self::RELATION_TYPE_ANNEXE => 'annexe',
  );

  public static $flags = array(
    self::FLAG_OLD_SYSTEM => 'système formulaire v1',
    self::FLAG_STEP_DISPLAY => 'Affichage par étape',
    self::FLAG_PRINT_ONE_PAGE => 'Imprimer en 1 page',
  );

  public static $ref_paiement_type_echeance = array(
    self::REF_PAIEMENT_TYPE_ECHEANCE_ACCOMPTE => 'Accompte',
    self::REF_PAIEMENT_TYPE_ECHEANCE_SOLDE => 'Solde',
  );

  public static $v2tov1 = array(
    'DAS2T'
  );


  public function asRelationEditHash($elts, $relation) {
    $elts['type']['type'] = 'select';
    $elts['type']['options'] = self::$relation_types;
    $elts['millesime_id']['type'] = 'select';
    $elts['millesime_id']['options'] = $relation->getMillesimes();
    $elts['millesime_id']['label'] = 'Millesime';

    $filters = array('filters' => array('|!=|id' => $relation->getId()),
                     'order'   => array('name' => 'asc'));
    $formulaires = $this->getFormulairetypes($filters);
    $_formulaires = array();
    foreach ($formulaires as $formulaire) {
      $_formulaires[$formulaire->getId()] = '[' .$formulaire->name . '] ' . $formulaire->code;
    }

    $elts['required_formulairetype_id']['type'] = 'select';
    $elts['required_formulairetype_id']['options'] = array(0 => '---') + $_formulaires;
    $elts['required_formulairetype_id']['label'] = 'Formulaire requis';

    return $elts;
  }

  public function asRelationRow($relation, $row) {
    $millesime = Millesime::getInstance($row['millesime_id']);
    return '[' . self::$relation_types[$row['type']] . '][' . $millesime->getName() . '] ' . $relation->name;
  }

  public function asEditHash() {
    $hash[self::PARAMS_DEFAULT_VALUES] = '';
    $hash[self::PARAMS_REQUIRED_FIELDS] = '';
    foreach ($this->getDefaultValues() as $imprime_code => $field_values) {
      foreach ($field_values as $field_code => $value) {
        $hash[self::PARAMS_DEFAULT_VALUES] .= $imprime_code . Formulairetype::SEPARATOR_IMPRIME_FIELD_CODES . $field_code . '=' . $value . "\n";
      }
    }
    foreach ($this->getRequiredFields() as $imprime_code => $field_requireds) {
      foreach ($field_requireds as $field_code => $value) {
        $hash[self::PARAMS_REQUIRED_FIELDS] .= $imprime_code . Formulairetype::SEPARATOR_IMPRIME_FIELD_CODES . $field_code . '=' . $value . "\n";
      }
    }
    return $hash;
  }

  public function asFinderHash($hash) {
    $hash['formulairetype_count'] = $this->getFormulairetypes()->count();
    $hash['document_code'] = Formulairetype::$document_codes[$hash['document_code']];
    $hash['destinataires'] = implode(', ', array_map(function($item){
      return Destinataire::$types[$item];
    }, $hash['destinataires']));
    $hash['flag_systeme_v1'] = $this->hasFlag(self::FLAG_OLD_SYSTEM) ? 'oui' : '';
    return $hash;
  }

  public function onFind($finder){
    $collection = $finder->getCollection();
    $filters = $collection->getFilters();
    if(isset($filters['flag_systeme_v1'])) {
      if($filters['flag_systeme_v1'] > 0) {
        $filters['|&|flags'] = self::FLAG_OLD_SYSTEM;
      }
      else{
        $filters['|!&|flags'] = self::FLAG_OLD_SYSTEM;
      }
      unset($filters['flag_systeme_v1']);
    }
    $collection->setFilters($filters);
  }


  public function getDefaultValues($ftype_code = null) {
    $default_values = $this->params[self::PARAMS_DEFAULT_VALUES];
    if ($ftype_code) {
      $default_values = $default_values[$ftype_code];
    }
    return $default_values;
  }

  public function getRequiredFields($ftype_code = null) {
    $required_fields = $this->params[self::PARAMS_REQUIRED_FIELDS];
    if ($ftype_code) {
      $required_fields = $required_fields[$ftype_code];
    }
    return $required_fields;
  }

  protected function onBeforeCommit(&$hash) {

    if (isset($hash[self::PARAMS_DEFAULT_VALUES])) {
      $hash[self::PARAMS_DEFAULT_VALUES] = String::asHash($hash[self::PARAMS_DEFAULT_VALUES]);
      array_filter($hash[self::PARAMS_DEFAULT_VALUES]);
      $default_values = array();
      foreach ($hash[self::PARAMS_DEFAULT_VALUES] as $code => $value) {
        list($imprime_code, $field_code) = explode(Formulairetype::SEPARATOR_IMPRIME_FIELD_CODES, $code, 2);
        $default_values[$imprime_code][$field_code] = $value;
      }
      unset($hash[self::PARAMS_DEFAULT_VALUES]);
      $hash['params'][self::PARAMS_DEFAULT_VALUES] = $default_values;
    }
    if (isset($hash[self::PARAMS_REQUIRED_FIELDS])) {
      $hash[self::PARAMS_REQUIRED_FIELDS] = String::asHash($hash[self::PARAMS_REQUIRED_FIELDS]);
      array_filter($hash[self::PARAMS_REQUIRED_FIELDS]);
      $required_fields = array();
      foreach ($hash[self::PARAMS_REQUIRED_FIELDS] as $code => $value) {
        list($imprime_code, $field_code) = explode(Formulairetype::SEPARATOR_IMPRIME_FIELD_CODES, $code, 2);
        $required_fields[$imprime_code][$field_code] = $value;
      }
      unset($hash[self::PARAMS_REQUIRED_FIELDS]);
      $hash['params'][self::PARAMS_REQUIRED_FIELDS] = $required_fields;
    }
    if (!isset($hash['params']) && count($this->getAttribute('params')) < 1) {
      $hash['params'] = array(self::PARAMS_DEFAULT_VALUES => array(),
                              self::PARAMS_REQUIRED_FIELDS => array());
    }
  }

  protected function onAfterDuplicate($new_item) {
    foreach ($this->getFormulairetypes() as $ftype) {
      $commit = array('position' => $ftype->ftype_position,
                      'type' => $ftype->ftype_type,
                      'millesime_id' => $ftype->ftype_millesime_id);
      $new_item->addFormulairetype($ftype, $commit);
    }
  }

  public function getFtypeMillesime($formulairetype_id) {
    if ($formulairetype_id instanceof ActiveRecord) {
      $formulairetype_id = $formulairetype_id->getId();
    }
    $ftypes = $this->getFormulairetypes(array('filters' => array('formulairetype_id' => $formulairetype_id),
                                              'limit' => 1));
    if ($ftypes->count() < 1) {
      S('log')->error('millesime not found for Formulairetype [ID='.$formulairetype_id.'] in Dectype [ID='.$this->getId().']', __METHOD__);
      return false;
    }
    $ftype = $ftypes->first();
    return Millesime::getInstance($ftype->ftype_millesime_id);
  }

  public function isFormulairetypeRequired($ftype){
    $relation = $this->getFormulairetypes(array('filters' => array('formulairetype_id' => $ftype->getId())));
    $relation = $relation->first();
    return $relation->getAttribute('ftype_type') == Dectype::RELATION_TYPE_OBLIGATOIRE;

  }

  public function hasRequiredFormulairetypeRelation($formulairetype_id) {
    return !is_null($this->getRequiredFormulairetypeRelation($formulairetype_id));
  }

  public function getRequiredFormulairetypeRelation($formulairetype_id) {
    if ($formulairetype_id instanceof ActiveRecord) {
      $formulairetype_id = $formulairetype_id->getId();
    }
    $ftypes = $this->getFormulairetypes(array('filters' => array('formulairetype_id'             => $formulairetype_id,
                                                                 '|>|required_formulairetype_id' => 0),
                                              'limit' => 1));
    if ($ftypes->count() < 1) {
      return null;
    }

    $ftype = $ftypes->first();
    return Formulairetype::getInstance($ftype->ftype_required_formulairetype_id);
  }

}
