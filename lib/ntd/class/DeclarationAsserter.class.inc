<?php


class DeclarationAsserter {

  public static function getClassName($millesime) {
    return get_called_class() . urlencode($millesime->name);
  }

  public static function exists($formulaire_code, $millesime) {
    return method_exists(self::getClassName($millesime), $formulaire_code);
  }

  public static function assert($formulaire_code, $declaration_data, $millesime) {
    $elt = function ($fieldName) use ($declaration_data) {
      $elt = new stdClass;
      $elt->name = $fieldName;
      $elt->value = $declaration_data[$fieldName];
      $elt->isset = isset($declaration_data[$fieldName]);
      return $elt;
    };
    $assert = function ($assertFunc, $error_code, $elts) {
      $args = func_get_args();
      $elts = array();
      for ($i = 2; $i < count($args); $i++) {
        $elts[] = $args[$i];
      }
      if (is_callable($assertFunc)) {
        $assertFunc = $assertFunc($elts);
      }
      if (!$assertFunc) {
        foreach ((array) $elts as $elt) {
          Formulaire::$errors[$elt->name . '_' . $error_code] = array('error_code' => $error_code,
                                                                      'elt' => $elt->name);
        }
      }
    };
    $isServi = function ($elt) {
      return strlen($elt->value) > 0;
    };
    $float = function ($elt) {
      return (float) $elt->value;
    };
    $value = function ($elt) {
      return $elt->value;
    };
    $controls = array(
      'maxOneCheckboxChecked' => function ($elts) {
        $checkeds = 0;
        foreach ($elts as $elt) {
          if ($elt->value > 0) {
            $checkeds++;
          }
        }
        return $checkeds <= 1;
      },
      'atLeastOneCheckboxChecked' => function ($elts) {
        foreach ($elts as $elt) {
          if ($elt->value > 0) {
            return true;
          }
        }
        return false;
      },
      "erreur_042" => function ($eltFormulaireNeant, $editableFields) use ($assert, $isServi, $float) {
        $hasOneServi = false;
        for ($i = 0; $i < count($editableFields); $i++) {
          $hasOneServi = $hasOneServi || ($isServi($editableFields[$i]) && $float($editableFields[$i]) > 0);
        }
        $assert(!($isServi($eltFormulaireNeant) && ($hasOneServi)),
                'erreur_042',
                $eltFormulaireNeant, $editableFields);
      },
      "erreur_049" => function ($eltFormulaireNeant, $editableFields) use ($assert, $isServi, $float) {
        for ($i = 0; $i < count($editableFields); $i++) {
          $assert(!(!$isServi($eltFormulaireNeant) && !($isServi($editableFields[$i]) && $float($editableFields[$i]) >= 0)),
                  'erreur_049', $eltFormulaireNeant, $editableFields[$i]);
        }
      },
      "erreur_111" => function ($fieldA, $fieldB) use ($assert, $isServi, $float) {
        $assert(!($isServi($fieldA) && $float($fieldA) > 0 && !($isServi($fieldB) && $float($fieldB) > 0)),
                'erreur_111', $fieldA, $fieldB);
      },
      "erreur_112" => function ($fieldA, $fieldB) use ($assert, $isServi, $float) {
        $assert(!($isServi($fieldA) && $float($fieldA) > 0 && !($isServi($fieldB) && $float($fieldB) > 0)),
                'erreur_112', $fieldA, $fieldB);
      },
      "erreur_116" => function ($eltA, $eltB) use ($assert, $isServi, $float) {
        $assert(!($isServi($eltA) && !($isServi($eltB) && 0 <= $float($eltB) && $float($eltB) <= 100)),
                'erreur_116', $eltA, $eltB);
      },
      "erreur_117" => function ($eltA, $eltB, $coefMin, $coefMax) use ($assert, $isServi, $float) {
        $assert(!($isServi($eltA) && $isServi($eltB)
          && !(($float($eltA) * $coefMin) <= $float($eltB) && $float($eltB) <= ($float($eltA) * $coefMax))),
                'erreur_117', $eltA, $eltB);
      },
      "erreur_129" => function ($eltCheckbox, $eltNeeded) use ($assert, $isServi, $float) {
        $assert(!($isServi($eltCheckbox) && !$isServi($eltNeeded)), 'erreur_129', $eltCheckbox, $eltNeeded);
      },
      "erreur_134" => function ($eltDate, $eltYearImpositionBegin, $eltYearImpositionEnd) use ($assert, $isServi, $float, $value) {
        $yearBegin = explode('/', $value($eltYearImpositionBegin));
        $yearEnd = explode('/', $value($eltYearImpositionEnd));
        $yearBegin = $yearBegin[2];
        $yearEnd = $yearEnd[2];
        $assert(!($isServi($eltDate) && $isServi($eltYearImpositionBegin) && $isServi($eltYearImpositionEnd) && !($float($eltDate) == $yearBegin || $float($eltDate) == $yearEnd)),
                'erreur_134', $eltDate);
      },
      "erreur_226" => function($eltNeeded, $eltCheckbox) use ($assert, $isServi, $float) {
        $assert(!(!$isServi($eltCheckbox) && $isServi($eltNeeded)), 'erreur_226', $eltCheckbox, $eltNeeded);
      },
      "erreur_112_addition" => function ($eltA, $eltB, $eltC) use ($assert, $isServi, $float) {
          $assert(!($isServi($eltA) && $float($eltA) > 0 && !($isServi($eltB) && $isServi($eltC) && $float($eltB) + $float($eltC) > 0)),
              'erreur_112', $eltA, $eltB, $eltC);
      },
    );


    call_user_func(array(self::getClassName($millesime), $formulaire_code),
                   $elt, $assert, $isServi, $float, $value, $controls);
  }
}
