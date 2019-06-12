<?php

class FormulaireErrors {

public static function displayErrors($errors) {
    foreach ($errors as $k => $error) {
      switch ($error['status']) {
        case 'correct':
            $errors[$k] = array(
                'code' => $error['code'],
                'name' => 'error-required',
                'msg' => 'Erreur ! resultat attendu : ' . $error['result'] . '');
            break;
        case 'error':
            $errors[$k] = array(
                'code' => $error['code'],
                'name' => 'error-required',
                'msg' => 'Erreur ! résultat attendu :' . $error['result'] . '');
            break;
        case 'generic_error':
          $errors[$k] = array(
              'code' => $error['code'],
              'name' => 'error-missingField',
              'msg' => 'Erreur');
          break;
        case 'integrity':
          $errors[$k] = array(
              'code' => $error['code'],
              'name' => 'error-missingField',
              'msg' => 'Ce champs doit être présent');
          break;
        case 'needed':
          $errors[$k] = array(
              'code' => $error['code'],
              'name' => 'error-missingField',
              'msg' => 'Au moins un de ces champs doit être rempli');
          break;
        case 'uneeded':
          $errors[$k] = array(
              'code' => $error['code'],
              'name' => 'error-missingField',
              'msg' => 'Au moins un de ces champs doit être vide');
          break;
        case 'required':
          $errors[$k] = array(
              'code' => $error['code'],
              'name' => 'error-required',
              'msg' => 'Ce champs est requis');
          break;
        case 'not_percent':
          $errors[$k] = array(
              'code' => $error['code'],
              'name' => 'error-not-numeric',
              'msg' => 'La valeur doit être comprise entre 0 et 100');
          break;
        case 'not_numeric':
          $errors[$k] = array(
              'code' => $error['code'],
              'name' => 'error-not-numeric',
              'msg' => 'Ce champs doit être un nombre');
          break;
        case 'not_positiv_or_zero_integer':
          $errors[$k] = array(
              'code' => $error['code'],
              'name' => 'error-not-integer',
              'msg' => 'Ce champs doit être un nombre sans décimales');
          break;
        case 'not_negatif':
          $errors[$k] = array(
              'code' => $error['code'],
              'name' => 'error-not-negatif',
              'msg' => 'Ce champs ne doit pas être inférieur à 0');
          break;
        case 'not_empty_because_checked':
          $errors[$k] = array(
              'code' => $error['code'],
              'name' => 'error-not-empty',
              'msg' => 'Ce champs ne doit pas être rempli, car '.$error['operand'].' est cochée');
          break;
        case 'not_empty_no_reason':
          $errors[$k] = array(
              'code' => $error['code'],
              'name' => 'error-not-empty',
              'msg' => 'Ce champs ne doit pas être rempli');
          break;
        case 'not_empty':
          $errors[$k] = array(
              'code' => $error['code'],
              'name' => 'error-not-empty',
              'msg' => $error['field2'].' doit être vide, car '.$error['field1'].' est rempli');
          break;
        case 'empty':
          $errors[$k] = array(
              'code' => $error['code'],
              'name' => 'error-empty',
              'msg' => 'Ce champs a des dépendances');
          break;
        case 'bad_result':
          $errors[$k] = array(
              'code' => $error['code'],
              'name' => 'bad-result',
              'msg' => 'Erreur de calcul');
          break;
        case 'not_positiv':
          $errors[$k] = array(
              'code' => $error['code'],
              'name' => 'error-required',
              'msg' => 'Cette valeur doit être supérieure a 0');
          break;

         case 'not_iban':
          $errors[$k] = array(
              'code' => $error['code'],
              'name' => 'error-required',
              'msg' => 'IBAN incorrect');
          break;
          case 'not_bic':
          $errors[$k] = array(
              'code' => $error['code'],
              'name' => 'error-required',
              'msg' => 'BIC incorrect');
          break;


         case 'not_positiv_or_zero':
          $errors[$k] = array(
              'code' => $error['code'],
              'name' => 'error-required',
              'msg' => $error['field1'].' doit être supérieure ou égale a 0');
          break;
        case 'must_be_strictly_inferior':
          $errors[$k] = array(
                'code' => $error['code'],
                'name' => 'error-required',
                'msg' => ''.$error['field1'].' doit être strictement inférieur à '.$error['field2'].'');
            break;
        case 'must_be_strictly_superior':
          $errors[$k] = array(
                'code' => $error['code'],
                'name' => 'error-required',
                'msg' => ''.$error['field1'].' doit être strictement supérieur à '.$error['field2'].'');
            break;
        case 'must_be_inferior_or_egal':
          $errors[$k] = array(
                'code' => $error['code'],
                'name' => 'error-required',
                'msg' => ''.$error['field1'].' doit être inférieur ou égal à '.$error['field2'].'');
            break;
        case 'must_be_superior_or_egal':
          $errors[$k] = array(
                'code' => $error['code'],
                'name' => 'error-required',
                'msg' => ''.$error['field1'].' doit être supérieur ou égal à '.$error['field2'].'');
            break;
        case 'not_empty_choice':
           $errors[$k] = array(
              'code' => $error['code'],
              'name' => 'error-not-empty',
              'msg' => 'Un seul des 2 champs'.$error['field1'].' ou '.$error['field2'].' doit être rempli');
            break;
        case 'has_to_be_filled':
           $errors[$k] = array(
              'code' => $error['code'],
              'name' => 'error-not-empty',
              'msg' => $error['field2'].' ne peut pas être vide, car '.$error['field1'].' est rempli');
            break;
        case 'has_to_be_filled_zero':
           $errors[$k] = array(
              'code' => $error['code'],
              'name' => 'error-not-empty',
              'msg' => $error['field2'].' doit être rempli et > à 0, car '.$error['field1'].' est supérieur ou égal à 0');
            break;
        case 'must_be_zero':
           $errors[$k] = array(
              'code' => $error['code'],
              'name' => 'error-not-empty',
              'msg' => $error['field1'].' doit valoir 0');
            break;
        case 'must_be_zero_or_empty':
           $errors[$k] = array(
              'code' => $error['code'],
              'name' => 'error-not-empty',
              'msg' => $error['field1'].' doit valoir 0 ou être vide');
            break;
        case 'must_be_same_result':
           $errors[$k] = array(
              'code' => $error['code'],
              'name' => 'error-not-empty',
              'msg' => 'Ce champs doit avoir la même valeur que '.$error['operand'].'');
            break;
        case 'sup_or_egal_150':
           $errors[$k] = array(
              'code' => $error['code'],
              'name' => 'error-not-empty',
              'msg' => ''.$error['operand'].' doit être supérieur ou égal à 150');
            break;
        case 'not_egal':
           $errors[$k] = array(
              'code' => $error['code'],
              'name' => 'error-not-empty',
              'msg' => 'La somme des champs doit être égale');
            break;
        case 'do_not_check':
           $errors[$k] = array(
              'code' => $error['code'],
              'name' => 'error-not-empty',
              'msg' => 'Cette case ne doit pas être cochée');
            break;
        case 'error_length_date':
           $errors[$k] = array(
              'code' => $error['code'],
              'name' => 'error-not-empty',
              'msg' => 'Respectez le format MMAAAA');
            break;
        case 'error_value_date':
           $errors[$k] = array(
              'code' => $error['code'],
              'name' => 'error-not-empty',
              'msg' => 'Les valeurs entrées ne peuvent pas être correctes');
            break;
        case 'error_value_email':
          $errors[$k] = array(
             'code' => $error['code'],
             'name' => 'error-not-empty',
             'msg' => 'Le format de l\'email est invalide');
           break;
        case 'integrity_ea':
           $errors[$k] = array(
              'code' => $error['code'],
              'name' => 'error-not-empty',
              'msg' => 'L\'intégrité du champe EA n\'est pas valide');
            break;
        case 'integrity_equation_error':
           $errors[$k] = array(
              'code' => $error['code'],
              'name' => 'error-not-empty',
              'msg' => 'La somme des champs '.$error['left'].' doit être '.$error['operator'].' à la somme des champs '.$error['right'].'');
            break;


          /***** Erreurs spécifiques *****/

          // Ca3
        case 'must_be_strictly_superior_210':
          $errors[$k] = array(
                'code' => $error['code'],
                'name' => 'error-required',
                'msg' => ''.$error['field1'].' doit être strictement supérieur à '.$error['field2'].' * 2.10 %');
            break;
        case 'must_be_strictly_inferior_1960':
          $errors[$k] = array(
                'code' => $error['code'],
                'name' => 'error-required',
                'msg' => ''.$error['field1'].' doit être strictement inférieur à '.$error['field2'].' * 19.60 %');
            break;
        case 'must_be_strictly_inferior_20':
          $errors[$k] = array(
                'code' => $error['code'],
                'name' => 'error-required',
                'msg' => ''.$error['field1'].' doit être strictement inférieur à '.$error['field2'].' * 20 %');
            break;
        case 'result_must_be_superior':
          $errors[$k] = array(
                'code' => $error['code'],
                'name' => 'error-required',
                'msg' => $error['field1'].' + '.$error['field2'].' doit être strictement supérieur à '.$error['field3']);
            break;
        case 'result_must_be_inferior_or_egal':
          $errors[$k] = array(
                'code' => $error['code'],
                'name' => 'error-required',
                'msg' => $error['field1'].' + '.$error['field2'].' doit être inférieur ou égal à '.$error['field3']);
            break;
        case 'result_must_be_inferior':
          $errors[$k] = array(
                'code' => $error['code'],
                'name' => 'error-required',
                'msg' => $error['field1'].' doit être strictement inférieur à '.$error['field2'].' + '.$error['field3'].' + '.$error['field4']);
            break;
        case 'should_be_checked':
          $errors[$k] = array(
                'code' => $error['code'],
                'name' => 'error-required',
                'msg' => $error['field2'].' doit être cochée car '.$error['field1'].' n\'est pas vide');
            break;

        // 3514
        case 'integrity_gc_3514':
        $errors[$k] = array(
              'code' => $error['code'],
              'name' => 'error-required',
              'msg' => $error['field2'].' doit être cochée car '.$error['field1'].' n\'est pas vide');
          break;
        case 'integrity_dd_3514':
        $errors[$k] = array(
              'code' => $error['code'],
              'name' => 'error-required',
              'msg' => 'DF doit être remplie car DD est cochée');
          break;
        case 'integrity_dg_3514':
        $errors[$k] = array(
              'code' => $error['code'],
              'name' => 'error-required',
              'msg' => 'DG doit être remplie car DW est cochée');
          break;

        // 3515sd
        case 'report_BC_BD':
        $errors[$k] = array(
              'code' => $error['code'],
              'name' => 'error-required',
              'msg' => 'Erreur, égalité impossible');
          break;

        // 3519
        case 'integrity_3519_fg_1':
        $errors[$k] = array(
              'code' => $error['code'],
              'name' => 'error-required',
              'msg' => 'FG doit être égal au plus petit montant des deux montants 3519_FE ou 3519_FF');
          break;
        case 'integrity_3519_fg_2':
        $errors[$k] = array(
              'code' => $error['code'],
              'name' => 'error-required',
              'msg' => 'Si 3519_FG >= 0 alors 3519_FG = 3519_DH ');
          break;
        case 'need_iban_if_amount':
        $errors[$k] = array(
              'code' => $error['code'],
              'name' => 'error-required',
              'msg' => 'Veuillez sélectionner un IBAN car le montant est > 0');
          break;
        case 'integrity_3514':
          $errors[$k] = array(
              'code' => $error['code'],
              'name' => 'error-required',
              'msg' => 'SI au moins un des champs '.implode(', ', $error['fields_1']).' n\'est pas vide ALORS tous les champs '.implode(', ', $error['fields_2']).' doivent être vides.');
          break;

        case 'integrity_3517ddr_ae':
          $errors[$k] = array(
              'code' => $error['code'],
              'name' => 'error-required',
              'msg' => 'Si 3517DDR_AA servie alors 3517DDR_AE = 3517DDR_AC - 3517DDR_AD ET SI 3517DDR_AA est vide alors 3517DDR_AE + 3517DDR_AD - 3517DDR_AC < 150');
          break;
        case 'integrity_3517ddr_ah_aj':
          $errors[$k] = array(
              'code' => $error['code'],
              'name' => 'error-required',
              'msg' => '3517DDR_AH ou 3517DDR_AJ doit être servie');
          break;
        case 'integrity_3519':
          $errors[$k] = array(
              'code' => $error['code'],
              'name' => 'error-required',
              'msg' => 'DN doit être égal à DH');
          break;
      }
    }
    return $errors;
  }
}
