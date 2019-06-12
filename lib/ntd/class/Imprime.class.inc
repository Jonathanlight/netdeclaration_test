<?php


class Imprime implements OperationDataProvider {

  private $formulairetype = null;
  private $millesime = null;
  private $formulaire = null;
  private $index = -1;

  private $fields = array();
  private $operations = array();


  public function asTradeXpressExportHash() {
    $data = array();

    foreach ($this->fields as $field) {
      if (!$field->hasFlag(Ifield::FLAG_EXPORTABLE)) {
        continue;
      }
      $key = $field->name;
      if ($field->isExtensible($this->getMillesime())) {
          for ($index = 0; $index < $field->maxIndex() + 1; $index++) {
          $data[$key . '/' . ($index + 1)] = $field->asTradeXpressExportHash($index);
        }
      }
      else {
        $data[$key] = $field->asTradeXpressExportHash(0); //$field->getValue(0);
      }
    }
    return $data;
  }

  public function getFieldsNotRendered() {
    S('log')->trace($this->getCode());
  }

  public function renderField($name, $index = 0) {
    $field = $this->getField($name);
    if (!$field) {
      S('log')->error('field not exist [' . $name . '][' . $index . ']', __METHOD__);
      return ''.$name.'';
    }
    $this->field_rendereds[$name]++;
    return $field->renderHTML($index);
  }

  public function getFieldsValuesCount($names) {
    $max_count = 0;
    foreach ($names as $name) {
      if (empty($name)) continue;
      $field = $this->getField($name);
      if ($field) {
          if ($field->type_segment == 'cci') {
              $max_count = max($max_count, $field->maxIndex()+1);
          } else {
            $max_count = max($max_count, $field->getValuesCount());
          }
      }
    }
    return $max_count;
  }


  /* ----- GETTER ----- */
  public function getFormulairetype() {
    return $this->formulairetype;
  }

  public function getMillesime() {
    return $this->millesime;
  }

  public function getFormulaire() {
    return $this->formulaire;
  }

  public function getCode() {
    return $this->formulairetype->code;
  }

  public function getOperations() {
    return $this->operations;
  }

  public function getField($name) {
    $field = $this->fields[$name];
    if (!$field) {
      S('log')->trace('Field not exists [' . $this->getCode() . '][' . $name . ']', __METHOD__);
    }
    return $field;
  }

  public function getFields() {
    return $this->fields;
  }

  public function getIndex() {
    return $this->index;
  }

  public function getFieldsValues() {
    $fields_values = array();
    foreach ($this->getFields() as $name => $field) {
      $fields_values[$name] = $field->getValues();
    }
    return $fields_values;
  }

  /* ----- SETTER ----- */
  public function setFormulairetype(Formulairetype $formulairetype, Millesime $millesime) {
    $this->formulairetype = $formulairetype;
    $this->millesime = $millesime;

    $this->fields = $formulairetype->getIfieldsByMillesime($millesime)->asHash('name');
    foreach ($this->fields as $field) {
      $field->setImprime($this);
    }
    $this->operations = $formulairetype->getOperations(array('filters' => array('status' => Operation::STATUS_ACTIF,
                                                                                '|REGEXP|millesimes' => '(^|,)' . $millesime->getId() . '(,|$)')))->asHash('id');
  }

  public function setFormulaire(Formulaire $formulaire, Millesime $millesime) {
    $this->formulaire = $formulaire;
    $this->index = $formulaire->position;
    $this->setFormulairetype($formulaire->getFormulairetype(), $millesime);
    $this->setFieldValues($this->formulaire->fields_values);
  }

  public function setFieldValues($fields_values) {
    foreach ($fields_values as $name => $field_values) {
      $field = $this->getField($name);
      if ($field) {
        $maxlength = (int)$field->maxlength;
        if ($field->hasFlag(Ifield::FLAG_PAD_VALUE) && $maxlength > 0) {
          foreach ($field_values as &$value) {
            $value = str_pad($value, $maxlength, '0', STR_PAD_LEFT);
          }
        }
        $this->getField($name)->setValues((array) $field_values);
      }
    }
  }

  public function setIndex($index) {
    $this->index = $index;
  }


  /* -----  Validate methods ----- */
  public function validateFields() {
    $exceptions = array();
    foreach ($this->fields as $field) {
      for ($index = 0; $index < $field->getValuesCount(); $index++) {
        try {
          if (substr($field->code, 0, 12) == 'F-IDENTIF_CB') {
              foreach ($this->fields as $_field) {
                  if (substr($_field->code, 0, 12) == 'F-IDENTIF_CA') {
                      $fidentif_ca = $_field;
                  }
              }
              $field->validate($index, $fidentif_ca);
          }
          $field->validate($index);
        }
        catch (FieldException $e) {
          $exceptions[] = $e;
        }
      }
    }
    return $exceptions;
  }

  public function validateOperations($include_interformulaire_operation = true, $data_provider = null) {
    if ($data_provider === null) {
      $data_provider = $this;
    }
    $exceptions = array();
    foreach ($this->getOperations() as $operation) {
      if (!$include_interformulaire_operation
          && $operation->hasFlag(Operation::FLAG_NEED_OTHER_FORMULAIRE)) {
        continue;
      }
      try {
        $operation->validate($data_provider, $this->getCode(), $this->getIndex());
      }
      catch (OperationException $e) {
        $exceptions[] = $e;
      }
    }
    return $exceptions;
  }

  public function getValues($imprime_code, $imprime_index, $field_code) {
    $field = $this->getField($field_code);
    if (!$field) {
      S('log')->debug($imprime_code . '#' . $imprime_index . '_' . $field_code, __METHOD__);
      return array();
    }
    return $field->getValues();
  }

  public function ImprimeExists($imprime_code) {
    return $imprime_code == $this->getCode();
  }

  public function getFieldFormulaireNeant() {
    foreach ($this->getFields() as $ifield) {
      if ($ifield->hasFlag(Ifield::FLAG_DEPOSE_NEANT)) {
        return $ifield;
      }
    }
    return null;
  }

}


final class FieldException extends Exception {

  private $field;
  private $index;
  private $imprime_index;

  public function __construct($field, $index, $imprime_index = 0, $msg = '', $code = 0) {
    $this->field = $field;
    $this->index = $index;
    $this->imprime_index = $imprime_index;
    parent::__construct($msg, $code);
  }

  public function getField() {
    return $this->field;
  }

  public function getIndex() {
    return $this->index;
  }

  public function getImprimeIndex() {
    return $this->imprime_index;
  }

}
