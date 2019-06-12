<?php


class Operation extends ActiveRecord {

  const TYPE_CALCUL = 0;
  const TYPE_CONTROLE = 1;
  const TYPE_COPY = 2;
  const TYPE_REQUIRED = 3;

  const STATUS_SUPPRIME = -1;
  const STATUS_INACTIF = 0;
  const STATUS_ACTIF = 1;

  const FLAG_NEED_OTHER_FORMULAIRE = 1;

  public static $types = array(self::TYPE_CALCUL => 'calcul',
                               self::TYPE_CONTROLE => 'controle',
                               self::TYPE_COPY => 'Copie',
                               self::TYPE_REQUIRED => 'Obligation');
  public static $method_names = array(self::TYPE_CALCUL => 'evaluate',
                                      self::TYPE_CONTROLE => 'equation',
                                      self::TYPE_COPY => 'copy',
                                      self::TYPE_REQUIRED => 'required');
  public static $statuses = array(self::STATUS_INACTIF => 'Supprimée',
                                  self::STATUS_INACTIF => 'inactif',
                                  self::STATUS_ACTIF => 'actif');

  public static $flags = array(self::FLAG_NEED_OTHER_FORMULAIRE => 'Dépend d\'autres formulaires',
  );

  public static $debug = false;

  //
  private $hook_manager;
  private $data_provider;
  private $imprime_index;
  private $imprime_code;

  //


  public function asEditHash() {
    $hash = array();
    if ($this->isLoaded()) {
      $hash['method_args_formula'] = $this->method_args['formula'];
      $hash['method_args_result'] = $this->method_args['result'];
      $hash['is_calcul'] = in_array($this->type, array(Operation::TYPE_CALCUL,
                                                       Operation::TYPE_COPY,
                                                       Operation::TYPE_REQUIRED));
    }
    return $hash;
  }

  public function asFinderHash($hash) {
    $hash['flag_need_other_formulaire'] = $this->hasFlag(self::FLAG_NEED_OTHER_FORMULAIRE) ? 'oui' : '';
    $hash['millesimes'] = implode(', ', Millesime::collect(array('filters' => array('|IN|id' => $this->millesimes)))->asSet('name'));
    return $hash;
  }

  protected function onBeforeCommit(&$hash) {
    if(isset($hash['method_args'])) {
      $hash['method_args'] = (array) $hash['method_args'];
    }
    if (isset($hash['method_args_formula'])) {
      $hash['method_args']['formula'] = $hash['method_args_formula'];
      unset($hash['method_args_formula']);
    }
    if (isset($hash['method_args_result'])) {
      $hash['method_args']['result'] = $hash['method_args_result'];
      unset($hash['method_args_result']);
    }
    if (isset($hash['type'])) {
      $hash['method_name'] = self::$method_names[$hash['type']];
    }
  }

  public function onFind($finder) {
    $coll = $finder->getCollection();
    $filters = $coll->getFilters();

    if (isset($filters['millesimes'])) {
      $filters['|REGEXP|millesimes'] = '(^|,)' . $filters['millesimes'] . '(,|$)';
      unset($filters['millesimes']);
    }

    $coll->setFilters($filters);
  }

  protected function onAfterCommit($hash) {
    if(S('req')->isBack()) {

      $method_args = $this->method_args;
      $method_args['formula'] = Operation::convertFormulaFieldCode($method_args['formula'], $this->getFormulairetype()->code);
      if (isset($method_args['result'])) {
        $method_args['result'] = Operation::convertFormulaFieldCode($method_args['result'], $this->getFormulairetype()->code);
      }
      $this->setAttribute('method_args', $method_args);

      $name = '[' . $this->method_name . '] ';
      if ($this->type != self::TYPE_CONTROLE) {
        $name .= $method_args['result'] . ' = ';
      }
      $name .= $method_args['formula'];
      $this->setAttribute('name', $name);


    }
    $this->build();
    $this->getFormulairetype()->build();
  }

  public function build() {
    $need_others_ftypes = false;
    $fields = Operation::getFormulaFields($this->method_args['formula']);
    $ftype_code = $this->getFormulairetype()->code;
    foreach ($fields as $field) {
      if (is_numeric($field)) continue;
      if (strpos($field, '@') !== false) continue;
      if (strpos($field, '_') === false) continue;
      list($ftype_code, $field_code) = explode(Formulairetype::SEPARATOR_IMPRIME_FIELD_CODES, $field, 2);
      if ($ftype_code == 'FIDENTIF') $ftype_code = 'F-IDENTIF';
      if ($ftype_code == 'PIDENTIF') $ftype_code = 'P-IDENTIF';
      if ($ftype_code == 'TIDENTIF') $ftype_code = 'T-IDENTIF';
      if ($ftype_code == 'AIDENTIF') $ftype_code = 'A-IDENTIF';
      if ($ftype_code == 'AIDENTIFIFU') $ftype_code = 'A-IDENTIFIFU';
      if ($ftype_code == 'AIDENTIFHON') $ftype_code = 'A-IDENTIFHON';
      if ($ftype_code == $ftype_code) continue;
      $need_others_ftypes = true;
      break;
    }
/*
    if ($need_others_ftypes) {
      $this->setFlag(self::FLAG_NEED_OTHER_FORMULAIRE);
    }
    else {
      $this->unsetFlag(self::FLAG_NEED_OTHER_FORMULAIRE);
    }
*/
  }


  public function setHookManager($hook_manager) {
    $this->hook_manager = $hook_manager;
  }

  public function hook($hook, $args) {
    if (!$this->hook_manager) return;
    if (method_exists($this->hook_manager, $hook)) {
      $this->hook_manager->{
      $hook
      }($this, $args);
    }
  }

  public function validate($data_provider, $imprime_code, $imprime_index) {
    $this->data_provider = $data_provider;
    $this->imprime_code = $imprime_code;
    $this->imprime_index = $imprime_index;

    if ($this->type == self::TYPE_CALCUL) {
      $formula = $this->method_args['formula'];
      $result_field_full_code = $this->method_args['result'];

      $result = $this->getCalculValue($formula);
      $result_real = $this->getFieldValues($result_field_full_code, 0);
      self::trace("[CALCUL] ? (" . $result_real . ' != ' . $result . ")", 0);

      list($ftype_code, $field_code) = explode(Formulairetype::SEPARATOR_IMPRIME_FIELD_CODES, $result_field_full_code, 2);
      $ftype = Formulairetype::getInstance(array('code' => $ftype_code));
      $field = Ifield::getInstance(array('formulairetype_id' => $ftype->getId(),
                                         'name' => $field_code));
      if ($field->type_segment == 'moa') {
        self::trace("(Arrondi " . $result . ' => ' . round($result) . ")", 1);
        $result = round($result);
      }

      if ($result_real != $result) {
        $e = new OperationException($formula,
          $imprime_index,
            'Valeur incorrect : Le champ ' . $result_field_full_code . ' devrait avoir pour valeur ' . $result);
        $e->addField($result_field_full_code, 0, $imprime_index);
        throw $e;
      }
    }
    elseif ($this->type == self::TYPE_CONTROLE) {
      $formula = $this->method_args['formula'];
      $result = $this->getConditionValue($formula);

      self::trace("[TYPE_CONTROLE] ? (" . ($result ? 'true' : 'false') . ")", 0);
      if (!$result) {
        $e = new OperationException($formula, $imprime_index, 'Contrôle incorrect : ' . $formula);
        foreach (self::getFormulaFields($formula) as $field_code) {
          if (substr($field_code, 0, 1) == '@') continue;
          if (strpos($formula, '#SUM(' . $field_code . ')#') !== false) {
            for ($index = 0; $index < count($this->getFieldValues($field_code)); $index++) {
              $e->addField($field_code, $index, $imprime_index);
            }
          }
          else {
            $e->addField($field_code, 0, $imprime_index);
          }
        }
        throw $e;
      }
    }
    elseif ($this->type == self::TYPE_COPY) {
      $formula = $this->method_args['formula'];
      $result_field_full_code = $this->method_args['result'];
      $result = $this->getCalculValueNotEvaluated($formula);
      $result_real = $this->getFieldValues($result_field_full_code, 0);

      self::trace("[COPY] ? (" . $result_real . ' != ' . $result . ")", 0);
      if ($result_real != $result) {
        $e = new OperationException($formula,
          $imprime_index,
            'Valeur incorrect : Le champ ' . $result_field_full_code . ' devrait avoir pour valeur ' . $result);
        $e->addField($result_field_full_code, 0, $imprime_index);
        throw $e;
      }
    }
    elseif ($this->type == self::TYPE_REQUIRED) {
      $formula = $this->method_args['formula'];
      $result_field_full_code = $this->method_args['result'];

      if (strpos($formula, 'IF') === 0) {
        $condition = $this->getCalculValue($formula);
        $result_real = trim($this->getFieldValues($result_field_full_code, 0));
        S('log')->trace("[REQUIRED] ? (" . ($condition ? 'oui' : 'non') . ' -> Valeur ' . $result_real . ")");
        self::trace("[REQUIRED] ? (" . ($condition ? 'oui' : 'non') . ' -> Valeur ' . $result_real . ")", 0);

        if (!$condition ) {
          $e = new OperationException($formula,
            $imprime_index,
              'Le champ ' . $result_field_full_code . ' est obligatoire car ' . $formula);
          $e->addField($result_field_full_code, 0, $imprime_index);
          throw $e;
        }
      }
      else {
        $condition = $this->getConditionValue($formula);
        $result_real = trim($this->getFieldValues($result_field_full_code, 0));
        S('log')->trace("[REQUIRED] ? (" . ($condition ? 'oui' : 'non') . ' -> Valeur ' . $result_real . ")");
        self::trace("[REQUIRED] ? (" . ($condition ? 'oui' : 'non') . ' -> Valeur ' . $result_real . ")", 0);
        if ($condition && empty($result_real)) {
          $e = new OperationException($formula,
            $imprime_index,
              'Le champ ' . $result_field_full_code . ' est obligatoire car ' . $formula);
          $e->addField($result_field_full_code, 0, $imprime_index);
          throw $e;
        }
      }
    }
  }


  /* ----- STATIC METHODS ----- */

  public static function convertFormulaFieldCode($formula, $imprime_code, $depth = 0) {
    // TODO : Evolution de cette méthode : protection des champs
    self::trace("-> convertCalculFieldCode(" . var_export($formula, true) . ")", $depth);

    $fields = self::getFormulaFields($formula, $depth + 1);

    $formula = str_replace(array('IF(', 'IFCOND(', 'SAISIE(', 'SUM(', 'MAX(', 'MIN(', 'OPEOR(', 'FORM('),
                           array('if(', 'ifcond(', 'saisie(', 'sum(', 'max(', 'min(', 'opeor(', 'form('),
                           $formula);

    foreach ($fields as $field_code) {
      if (substr($field_code, 0, 1) == '@') continue;
      if (strpos($field_code, '_') !== false) continue;
      if (is_numeric($field_code) !== false) continue;
      $formula = str_replace($field_code,
                             $imprime_code . '_' . $field_code,
                             $formula);
    }

    $formula = str_replace(array('if(', 'ifcond(', 'saisie(', 'sum(', 'max(', 'min(', 'opeor(', 'form('),
                           array('IF(', 'IFCOND(', 'SAISIE(', 'SUM(', 'MAX(', 'MIN(', 'OPEOR(', 'FORM('),
                           $formula);
    self::trace("<- " . $formula, $depth);

    return $formula;
  }



  public static function getFormulaFields($formula, $depth = 0) {
    self::trace("-> getFormulaFields(" . var_export($formula, true) . ")", $depth);
    // TODO : proteger les fields

    $formula = str_replace(array('IF(', 'SUM(', 'MAX(', 'MIN(', 'OPEOR(', 'FORM(', 'F-IDENTIF', 'P-IDENTIF', 'T-IDENTIF', 'A-IDENTIF', 'A-IDENTIFIFU', 'A-IDENTIFHON'),
                           array('if(', 'sum(', 'max(', 'min(', 'opeor(', 'form(', 'FIDENTIF', 'PIDENTIF', 'TIDENTIF', 'AIDENTIF', 'AIDENTIFIFU', 'AIDENTIFHON'),
                           $formula);
    $fields = preg_split('/[\+\-\*\/\(\)\#><=;]|(if)|(sum)|(max)|(min)|(opeor)|(form)/',
                         $formula,
                         null,
                         PREG_SPLIT_NO_EMPTY);
    $fields = array_unique($fields);
    self::trace("<- " . var_export($fields, true), $depth);
    return $fields;
  }

  /* ----- getValue Methods ----- */

  public function getOperandeValue($operande, $depth = 0) {
    self::trace("-> getOperandeValue(" . $operande . ")", $depth);

    $value = null;
    if (substr($operande, 0, 6) == 'IFCOND') {
      $if_parts = self::parseIfcond($operande, $depth + 1);
      $formula = $this->getConditionValue($if_parts['condition'], $depth + 1) ? $if_parts['condition_yes'] : $if_parts['condition_no'];
      $value = $this->getConditionValue($formula, $depth + 1);
    }
    elseif (substr($operande, 0, 2) == 'IF') {
      $if_parts = self::parseIf($operande, $depth + 1);
      $formula = $this->getConditionValue($if_parts['condition'], $depth + 1) ? $if_parts['calcul_yes'] : $if_parts['calcul_no'];
      $value = $this->getCalculValue($formula, $depth + 1);
    }
    elseif (substr($operande, 0, 4) == '#SUM') {
      $field_code = self::parseSum($operande, $depth + 1);
      $values = $this->getFieldValues($field_code);
      $value = array_sum($values);
    }
    elseif (substr($operande, 0, 4) == '#MAX') {
      $field_codes = self::parseMax($operande, $depth + 1);
      $values = array();
      foreach ($field_codes as $field_code) {
        $values[] = $this->getOperandeValue($field_code, $depth + 1);
      }
      $value = max($values);
    }
    elseif (substr($operande, 0, 4) == '#MIN') {
      $field_codes = self::parseMin($operande, $depth + 1);
      $values = array();
      foreach ($field_codes as $field_code) {
        $values[] = $this->getOperandeValue($field_code, $depth + 1);
      }
      $value = min($values);
    }
    elseif (substr($operande, 0, 1) == '(') {
      $operande = trim($operande, '()');
      $value = $this->getCalculValue($operande, $depth + 1);
    }
    elseif (!is_numeric($operande)) {
      $value = $this->getFieldValues($operande, 0);
      if ($value[0] == '-') {
        $value = '(' . $value . ')';
      }
    }
    else {
      $value = $operande;
    }
    self::trace("<- Resultat : [" . $value . "]", $depth);
    return $value;
  }

  public function getCalculValue($formula, $depth = 0) {
    self::trace("-> getCalculValue(" . $formula . ")", $depth);
    $operandes = self::parseCalcul($formula, $depth + 1);
    $formula_ready = $formula;
    foreach ($operandes as $operande) {
      $formula_ready = str_replace($operande,
                                   $this->getOperandeValue($operande, $depth + 1),
                                   $formula_ready);
    }
    //self::trace("formula_ready [$formula_ready]", $depth + 1);

    $this->hook('onBeforeEval', $formula_ready);
    $result = eval('return ' . $formula_ready . ';');
    self::trace("<- Résultat : [" . $result . "]", $depth);
    return $result;
  }

  public function getCalculValueNotEvaluated($formula, $depth = 0) {
    self::trace("-> getCalculValueNotEvaluated(" . $formula . ")", $depth);
    $operandes = self::parseCalcul($formula, $depth + 1);
    $formula_ready = $formula;
    foreach ($operandes as $operande) {
      $formula_ready = str_replace($operande,
                                   $this->getOperandeValue($operande, $depth + 1),
                                   $formula_ready);
    }
    //self::trace("formula_ready [$formula_ready]", $depth + 1);
    $this->hook('onBeforeEval', $formula_ready);
    $result = $formula_ready;
    self::trace("<- Résultat : [" . $result . "]", $depth);
    return $result;
  }

  public function getConditionValue($formula, $depth = 0) {
    self::trace("-> getConditionValue(" . $formula . ")", $depth);
    if (strpos($formula, '#FORM(') !== false) {
      $imprime_code = self::parseForm($formula, $depth + 1);
      $result = $this->data_provider->ImprimeExists($imprime_code);
    }
    elseif (strpos($formula, '#OPEOR(') !== false) {
      list($operande_left, $operande_right) = preg_split('#=#',
                                                         $formula,
                                                         null,
                                                         PREG_SPLIT_NO_EMPTY);
      self::trace("operande_left = [" . $operande_left . "]", $depth + 1);
      self::trace("operande_right = [" . $operande_right . "]", $depth + 1);
      $field_codes = self::parseOpeor($operande_right, $depth + 1);
      $values = array();
      foreach ($field_codes as $field_code) {
        $values[] = $this->getCalculValue($field_code);
      }
      $result = in_array($this->getCalculValue($operande_left), $values);
    }
    elseif (strpos($formula, 'IFCOND(') !== false) {
      $operande_left = $formula;
      self::trace("operande_left = [" . $operande_left . "]", $depth + 1);

      $operande_left = self::parseIfcond($operande_left, $depth + 1);
      self::trace(">> operande_left = [" . $operande_left . "]", $depth + 1);
      $formula = $this->getConditionValue($operande_left['condition'], $depth + 1) ? $operande_left['condition_yes'] : $operande_left['condition_no'];
      $operande_left_value = $this->getConditionValue($formula, $depth + 1);

      $formula_ready = str_replace($formula, $operande_left_value, $formula);

      self::trace("formula_ready [" . $formula_ready . "]", $depth);
      $result = eval('return ' . $formula_ready . ';');
    }
    elseif (strpos($formula, 'SAISIE(') !== false) {
      $operande_left = $formula;
      self::trace("operande_left = [" . $operande_left . "]", $depth + 1);

      $operande_left = self::parseSaisie($operande_left, $this, $depth + 1);
      self::trace(">> operande_left = [" . $operande_left . "]", $depth + 1);
      $operande_left_value = $this->getConditionValue($operande_left, $depth + 1);
      $formula_ready = str_replace($formula, $operande_left_value, $formula);

      self::trace("formula_ready [" . $formula_ready . "]", $depth);
      $result = eval('return ' . $formula_ready . ';');
    }
    else {
      list($operande_left, $operande_right) = preg_split('#[><=]#',
                                                         $formula,
                                                         null,
                                                         PREG_SPLIT_NO_EMPTY);
      self::trace("operande_left = [" . $operande_left . "]", $depth + 1);
      self::trace("operande_right = [" . $operande_right . "]", $depth + 1);

      $operande_left_value = $this->getCalculValue($operande_left, $depth + 1);
      $operande_right_value = $this->getCalculValue($operande_right, $depth + 1);
      $formula_ready = str_replace(array($operande_left, $operande_right),
                                   array($operande_left_value, $operande_right_value),
                                   $formula);
      //self::trace("formula_ready [$formula_ready]", $depth + 1);

      $this->hook('onBeforeEval', $formula_ready);
      $result = eval('return ' . $formula_ready . ';');
    }

    self::trace("<- Resultat : " . ($result ? 'vrai' : 'faux'), $depth);
    return $result;
  }

  public function getFieldValues($field_full_code, $field_index = null) {
    list($imprime_code, $field_code) = explode('_', $field_full_code, 2);

    $imprime_index = 0;
    if ($imprime_code == $this->imprime_code) {
      $imprime_index = $imprime_index;
    }

    $values = $this->data_provider->getValues($imprime_code, $imprime_index, $field_code);
    foreach ($values as &$value) {
      //$value = ltrim($value, '0');
    }
    if ($field_index !== null) {
        if (is_array($values[$field_index])) {
            return $values[$field_index]['value'];
        } else {
            return $values[$field_index];
        }
    }
    return $values;
  }



  /* ----- parse Methods ----- */

  public static function parseCalcul($formula, $depth = 0) {
    self::trace("-> parseCalcul(" . $formula . ")", $depth);
    $operandes = array();

    $open_parenthesis = 0;
    $current_operande = '';
    foreach (str_split($formula) as $char) {
      if ($open_parenthesis == 0
          && in_array($char, array('+', '-', '*', '/'))
          && !($char == '-' && in_array($current_operande, array('F', 'P', 'T', 'A')))
      ) {
        $operandes[] = $current_operande;
        $current_operande = '';
        continue;
      }
      if ($char == '(') {
        $open_parenthesis++;
      }
      elseif ($char == ')') {
        $open_parenthesis--;
      }
      $current_operande .= $char;
    }
    $operandes[] = $current_operande;
    usort($operandes, 'self::sortOperandes');
    self::trace("<- Resultat : [" . implode(', ', $operandes) . "]", $depth);
    return $operandes;
  }

  public static function parseIf($formula, $depth = 0) {
    self::trace("-> parseIf(" . $formula . ")", $depth);
    //$formula = 'IF(COND1;CALCUL1;CALCUL2)';
    //$formula = 'IF(COND1;IF(COND2;IF(COND21;CALCUL_YES21;CALCUL_NO21);IF(COND22;CALCUL_YES22;CALCUL_NO22));IF(COND3;IF(COND31;CALCUL_YES31;CALCUL_NO31);CALCUL_NO3))';

    $formula = substr($formula, 3); // IF(
    $formula = substr($formula, 0, strlen($formula) - 1); // )

    $resultat = array('condition' => '',
                      'calcul_yes' => '',
                      'calcul_no' => '');
    $index = 'condition';
    $open_parenthesis = 0;
    foreach (str_split($formula) as $char) {
      if ($char == '(') {
        $open_parenthesis++;
      }
      elseif ($char == ')') {
        $open_parenthesis--;
      }
      elseif ($char == ';') {
        if ($open_parenthesis == 0) {
          if ($index == 'condition') {
            $index = 'calcul_yes';
          }
          elseif ($index == 'calcul_yes') {
            $index = 'calcul_no';
          }
          else {
            break;
          }
          continue;
        }
      }
      $resultat[$index] .= $char;
    }
    self::trace("<- Résultat : [" . $resultat['condition'] . "] ? [" . $resultat['calcul_yes'] . "] : [" . $resultat['calcul_no'] . "]", $depth);
    return $resultat;
  }

  public static function parseIfcond($formula, $depth = 0) {
    self::trace("-> parseIfcond(" . $formula . ")", $depth);
    //$formula = 'IFCOND(BA>0;BD+BF+BJ+CA>0;#SUM#AE=0)';

    $formula = substr($formula, 7); // IFCOND(
    $formula = substr($formula, 0, strlen($formula) - 1); // )

    $resultat = array(
      'condition' => '',
      'condition_yes' => '',
      'condition_no' => ''
    );
    $index = 'condition';
    $open_parenthesis = 0;
    foreach (str_split($formula) as $char) {
      if ($char == '(') {
        $open_parenthesis++;
      }
      elseif ($char == ')') {
        $open_parenthesis--;
      }
      elseif ($char == ';') {
        if ($open_parenthesis == 0) {
          if ($index == 'condition') {
            $index = 'condition_yes';
          }
          elseif ($index == 'condition_yes') {
            $index = 'condition_no';
          }
          else {
            break;
          }
          continue;
        }
      }
      $resultat[$index] .= $char;
    }
    self::trace("<- Résultat : [" . $resultat['condition'] . "] ? [" . $resultat['condition_yes'] . "] : [" . $resultat['condition_no'] . "]", $depth);
    return $resultat;
  }

  public static function parseSaisie($formula, $operation, $depth = 0) {
    self::trace("-> parseSaisie(" + $formula + ")", $depth);

    $formula = substr($formula, 7); // SAISIE(
    $formula = substr($formula, 0, strlen($formula) - 1); // )

    $field_code = $formula;
    $field_value = $operation->getFieldValues($field_code, 0);
    if (is_array($field_value)) {
        $field_value = $field_value['value'];
    }
    $resultat = (is_numeric($field_value) ? $field_code . '>0' : strlen($field_value) . '>0');

    self::trace("<- Résultat : [" . $resultat . "]", $depth);
    return $resultat;
  }

  public static function parseSum($formula, $depth = 0) {
    self::trace("-> parseSum(" . $formula . ")", $depth);
    // #SUM(field_code)#
    $matches = array();
    preg_match('/#SUM\((?P<field_code>.*)\)#/', $formula, $matches);
    $field_code = $matches['field_code'];
    self::trace("<- Résultat : [" . $field_code . "]", $depth);
    return $field_code;
  }

  public static function parseForm($formula, $depth = 0) {
    self::trace("-> parseForm(" . $formula . ")", $depth);
    // #FORM(@imprime_code)#
    $matches = array();
    preg_match('/#FORM\(@(?P<imprime_code>.*)\)#/', $formula, $matches);
    $imprime_code = $matches['imprime_code'];
    self::trace("<- Résultat : [" . $imprime_code . "]", $depth);
    return $imprime_code;
  }

  public static function parseMax($formula, $depth = 0) {
    self::trace("-> parseMax(" . $formula . ")", $depth);
    // #MAX(field_code1;field_code2, ...)#
    $matches = array();
    preg_match('/#MAX\((?P<field_codes>.*)\)#/', $formula, $matches);
    $field_codes = explode(';', $matches['field_codes']);
    self::trace("<- Résultat : [" . $field_codes . "]", $depth);
    return $field_codes;
  }

  public static function parseMin($formula, $depth = 0) {
    self::trace("-> parseMin(" . $formula . ")", $depth);
    // #MIN(field_code1;field_code2, ...)#
    $matches = array();
    preg_match('/#MIN\((?P<field_codes>.*)\)#/', $formula, $matches);
    $field_codes = explode(';', $matches['field_codes']);
    self::trace("<- Résultat : [" . $field_codes . "]", $depth);
    return $field_codes;
  }

  public static function parseOpeor($formula, $depth = 0) {
    self::trace("-> parseOpeor(" . $formula . ")", $depth);
    // #OPEOR(field_code1;field_code2, ...)#
    $matches = array();
    preg_match('/#OPEOR\((?P<field_codes>.*)\)#/', $formula, $matches);
    $field_codes = explode(';', $matches['field_codes']);
    self::trace("<- Résultat : [" . $field_codes . "]", $depth);
    return $field_codes;
  }



  /* ----- Utils METHODS ----- */

  public static function trace($msg, $depth = 0) {
    if (!self::$debug) return;
    $_print = "";
    $_print .= str_repeat(" ", $depth * 4);
    if (!is_string($msg)) {
      $msg = var_export($msg, true);
    }
    $_print .= $msg;
    if (S('req')->isCli()) {
      print $_print . "\n";
    }
    else {
      S('log')->trace($_print, __METHOD__);
    }
  }

  public static function sortOperandes($a, $b) {
    //Operation::trace('sortOperandes([' . $a . '], [' . $b . '])');
    if (strcmp($a, $b) == 0) {
      return 0;
    }

      if (in_array(substr($a, 0, 3),
              array('IF(', '#SU'))
          || in_array(substr($a, 0, 6),
              array('IFCOND('))) {
      return -1;
    }
    elseif (in_array(substr($b, 0, 3),
                     array('IF(', '#SU'))
         || in_array(substr($b, 0, 6),
            array('IFCOND('))) {
      return 1;
    }
    return ($a < $b) ? -1 : 1;
  }



}


// IF (CONDITION;CALCUL;CALCUL) => RESULTAT
// CHAMP => RESULTAT

// CALCUL : OPERANDE (+|-|*|/) OPERANDE
// OPERANDE : IF() OU CHAMP
// CONDITION : CALCUL (<|<=|==|>=|>) CALCUL => boolean

// CONTROLE : CONDITION

// CALCUL : pour chaque OPERANDE, get RESULTAT


final class OperationException extends Exception {

  private $operation_name;
  private $imprime_index;
  private $fields;

  public function __construct($operation_name = '', $imprime_index = 0, $msg = '', $code = 0) {
    parent::__construct($msg, $code);
    $this->operation_name = $operation_name;
    $this->imprime_index = $imprime_index;
    $this->fields = array();
  }

  public function addField($field_fullcode, $index, $imprime_index) {
    $this->fields[] = array('code' => $field_fullcode,
                            'index' => $index,
                            'imprime_index' => $imprime_index);
  }

  public function getFieldFullCodes() {
    return $this->fields;
  }

  public function getOperationName() {
    return $this->operation_name;
  }

  public function getImprimeIndex() {
    return $this->imprime_index;
  }
}
