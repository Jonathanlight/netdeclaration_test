<?php

/** Millésime 2015 **/

class DeclarationAsserter2015 extends DeclarationAsserter {

  public static function tva3519_20150101($elt, $assert, $isServi, $float, $value, $controls) {

    $CB = $elt('t_identif_CB');
    // S('log')->debug($CB, __METHOD__);
    $DC1 = $elt('tva3519_20150101_DC1');
    $DC2 = $elt('tva3519_20150101_DC2');
    $DC3 = $elt('tva3519_20150101_DC3');
    $DC4 = $elt('tva3519_20150101_DC4');
    $DC5 = $elt('tva3519_20150101_DC5');
    $DC6 = $elt('tva3519_20150101_DC6');
    $DC7 = $elt('tva3519_20150101_DC7');
    $DC8 = $elt('tva3519_20150101_DC8');
    $DC9 = $elt('tva3519_20150101_DC9');
    $DC10 = $elt('tva3519_20150101_DC10');
    $DD = $elt('tva3519_20150101_DD');
    $DE = $elt('tva3519_20150101_DE');
    $DF = $elt('tva3519_20150101_DF');
    $DG1 = $elt('tva3519_20150101_DG1');
    $DG2 = $elt('tva3519_20150101_DG2');
    $DG3 = $elt('tva3519_20150101_DG3');
    $DG4 = $elt('tva3519_20150101_DG4');
    $DH = $elt('tva3519_20150101_DH');
    $DI = $elt('tva3519_20150101_DI');
    $DJ = $elt('tva3519_20150101_DJ');
    $DK = $elt('tva3519_20150101_DK');
    $DM = $elt('tva3519_20150101_DM');
    $DN = $elt('tva3519_20150101_DN');
    $FJ = $elt('tva3519_20150101_FJ');
    $FK = $elt('tva3519_20150101_FK');
    $FL = $elt('tva3519_20150101_FL');
    $AA1 = $elt('tva3519_20150101_AA1');
    $AA2 = $elt('tva3519_20150101_AA2');
    $AA3 = $elt('tva3519_20150101_AA3');
    $AA4 = $elt('tva3519_20150101_AA4');
    $DL = $elt('tva3519_20150101_DL');

    $assert($controls['atLeastOneCheckboxChecked'], 'erreur_200', $DD, $DE, $DF);
    $assert($controls['maxOneCheckboxChecked'], 'erreur_126', $DD, $DE, $DF);
    $assert($controls['atLeastOneCheckboxChecked'], 'erreur_149', $DI, $DJ, $DK);
    $assert($controls['maxOneCheckboxChecked'], 'erreur_104', $DI, $DJ, $DK);
    $assert(!($isServi($DF) && !$isServi($DC1)), 'erreur_103', $DC1);
    $assert(!($isServi($DF) && !$isServi($DC2)), 'erreur_103', $DC2);
    $assert(!($isServi($DF) && !$isServi($DC3)), 'erreur_103', $DC3);
    $assert(!($isServi($DF) && !$isServi($DC4)), 'erreur_103', $DC4);
    $assert(!($isServi($DF) && !$isServi($DC5)), 'erreur_103', $DC5);
    $assert(!($isServi($DF) && !$isServi($DC6)), 'erreur_103', $DC6);
    $assert(!($isServi($DF) && !$isServi($DC7)), 'erreur_103', $DC7);
    $assert(!($isServi($DF) && !$isServi($DC8)), 'erreur_103', $DC8);
    $assert(!($isServi($DF) && !$isServi($DC9)), 'erreur_103', $DC9);
    $assert(!($isServi($DF) && !$isServi($DC10)), 'erreur_103', $DC10);
    $assert($isServi($DG1), 'erreur_100', $DG1);
    $assert($isServi($DG2), 'erreur_100', $DG2);
    $assert($isServi($DG3), 'erreur_100', $DG3);
    $assert($isServi($DG4), 'erreur_100', $DG4);
    $assert($isServi($DH) && $float($DH) > 0, 'erreur_219', $DH);
    $assert($isServi($DN) && $float($DN) > 0, 'erreur_219', $DN);
    $assert($float($DN) === $float($DH), 'erreur_220', $DN, $DH);
    $assert($isServi($FK) || $isServi($FL), 'erreur_221', $FK, $FL);
    $assert(!($isServi($DJ) && !$isServi($DM)), 'erreur_223', $DM);
    $assert(!($isServi($DI) && !$isServi($FJ)), 'erreur_148', $FJ);
    $assert(!($isServi($DI)
      && !$isServi($AA1)
      && !$isServi($AA2)
      && !$isServi($AA3)
      && !$isServi($AA4)
      && !$isServi($DL)),
            'Si "Premiere demande" est coché Alors "Référence bancaire" et "Création le" doivent être renseignés.',
            $AA1, $AA2, $AA3, $AA4, $DL);
    $assert(function () use ($isServi, $value, $float, $CB, $DJ, $DN) {
      if ($isServi($CB) && !$isServi($DJ)) {
        $month = explode('/', $value($CB));
        // S('log')->debug($month, __METHOD__);
        $month = $month[1];
        $minimumDN = 760;
        if ($month == 12) {
          $minimumDN = 150;
        }
        return $float($DN) >= $minimumDN;
      }
      return true;
    }, 'erreur_225', $DN);
  }

  public static function tva3519_20151020($elt, $assert, $isServi, $float, $value, $controls) {
    $CB = $elt('t_identif_CB');
    // S('log')->debug($CB, __METHOD__);
    $DC1 = $elt('tva3519_20151020_DC1');
    $DC2 = $elt('tva3519_20151020_DC2');
    $DC3 = $elt('tva3519_20151020_DC3');
    $DC4 = $elt('tva3519_20151020_DC4');
    $DC5 = $elt('tva3519_20151020_DC5');
    $DC6 = $elt('tva3519_20151020_DC6');
    $DC7 = $elt('tva3519_20151020_DC7');
    $DC8 = $elt('tva3519_20151020_DC8');
    $DC9 = $elt('tva3519_20151020_DC9');
    $DC10 = $elt('tva3519_20151020_DC10');
    $DD = $elt('tva3519_20151020_DD');
    $DE = $elt('tva3519_20151020_DE');
    $DF = $elt('tva3519_20151020_DF');
    $DG1 = $elt('tva3519_20151020_DG1');
    $DG2 = $elt('tva3519_20151020_DG2');
    $DG3 = $elt('tva3519_20151020_DG3');
    $DG4 = $elt('tva3519_20151020_DG4');
    $DH = $elt('tva3519_20151020_DH');
    $DI = $elt('tva3519_20151020_DI');
    $DJ = $elt('tva3519_20151020_DJ');
    $DK = $elt('tva3519_20151020_DK');
    $DM = $elt('tva3519_20151020_DM');
    $DN = $elt('tva3519_20151020_DN');
    $FJ = $elt('tva3519_20151020_FJ');
    $FK = $elt('tva3519_20151020_FK');
    $FL = $elt('tva3519_20151020_FL');
    $AA1 = $elt('tva3519_20151020_AA1');
    $AA2 = $elt('tva3519_20151020_AA2');
    $AA3 = $elt('tva3519_20151020_AA3');
    $AA4 = $elt('tva3519_20151020_AA4');
    $DL = $elt('tva3519_20151020_DL');

    $assert($controls['atLeastOneCheckboxChecked'], 'erreur_200', $DD, $DE, $DF);
    $assert($controls['maxOneCheckboxChecked'], 'erreur_126', $DD, $DE, $DF);
    $assert($controls['atLeastOneCheckboxChecked'], 'erreur_149', $DI, $DJ, $DK);
    $assert($controls['maxOneCheckboxChecked'], 'erreur_104', $DI, $DJ, $DK);
    $assert(!($isServi($DF) && !$isServi($DC1)), 'erreur_103', $DC1);
    $assert(!($isServi($DF) && !$isServi($DC2)), 'erreur_103', $DC2);
    $assert(!($isServi($DF) && !$isServi($DC3)), 'erreur_103', $DC3);
    $assert(!($isServi($DF) && !$isServi($DC4)), 'erreur_103', $DC4);
    $assert(!($isServi($DF) && !$isServi($DC5)), 'erreur_103', $DC5);
    $assert(!($isServi($DF) && !$isServi($DC6)), 'erreur_103', $DC6);
    $assert(!($isServi($DF) && !$isServi($DC7)), 'erreur_103', $DC7);
    $assert(!($isServi($DF) && !$isServi($DC8)), 'erreur_103', $DC8);
    $assert(!($isServi($DF) && !$isServi($DC9)), 'erreur_103', $DC9);
    $assert(!($isServi($DF) && !$isServi($DC10)), 'erreur_103', $DC10);
    $assert($isServi($DG1), 'erreur_100', $DG1);
    $assert($isServi($DG2), 'erreur_100', $DG2);
    $assert($isServi($DG3), 'erreur_100', $DG3);
    $assert($isServi($DG4), 'erreur_100', $DG4);
    $assert($isServi($DH) && $float($DH) > 0, 'erreur_219', $DH);
    $assert($isServi($DN) && $float($DN) > 0, 'erreur_219', $DN);
    $assert($float($DN) === $float($DH), 'erreur_220', $DN, $DH);
    $assert($isServi($FK) || $isServi($FL), 'erreur_221', $FK, $FL);
    $assert(!($isServi($DJ) && !$isServi($DM)), 'erreur_223', $DM);
    $assert(!($isServi($DI) && !$isServi($FJ)), 'erreur_148', $FJ);
    $assert(!($isServi($DI)
      && !$isServi($AA1)
      && !$isServi($AA2)
      && !$isServi($AA3)
      && !$isServi($AA4)
      && !$isServi($DL)),
            'Si "Premiere demande" est coché Alors "Référence bancaire" et "Création le" doivent être renseignés.',
            $AA1, $AA2, $AA3, $AA4, $DL);
    $assert(function () use ($isServi, $value, $float, $CB, $DJ, $DN) {
      if ($isServi($CB) && !$isServi($DJ)) {
        $month = explode('/', $value($CB));
        // S('log')->debug($month, __METHOD__);
        $month = $month[1];
        $minimumDN = 760;
        if ($month == 12) {
          $minimumDN = 150;
        }
        return $float($DN) >= $minimumDN;
      }
      return true;
    }, 'erreur_225', $DN);
  }

  public static function tva3514_20150101($elt, $assert, $isServi, $float, $value, $controls) {

    $HA = $elt('tva3514_20150101_HA');
    $HB = $elt('tva3514_20150101_HB');
    $HC = $elt('tva3514_20150101_HC');
    $DE = $elt('tva3514_20150101_DE');
    $IA = $elt('tva3514_20150101_IA');
    $IB = $elt('tva3514_20150101_IB');
    $IC = $elt('tva3514_20150101_IC');
    $ID = $elt('tva3514_20150101_ID');
    $CA = $elt('tva3514_20150101_CA');
    $CB = $elt('tva3514_20150101_CB');
    $CC = $elt('tva3514_20150101_CC');

    $assert(!($isServi($HA)
      && ($isServi($IA)
        || $isServi($IB)
        || $isServi($IC)
        || $isServi($ID))),
            'erreur_217',
            $HA, $IA, $IB, $IC, $ID);
    $assert(!($isServi($HB)
      && ($isServi($IA)
        || $isServi($IB)
        || $isServi($IC)
        || $isServi($ID))),
            'erreur_217',
            $HB, $IA, $IB, $IC, $ID);
    $assert(!($isServi($DE)
      && ($isServi($IA)
        || $isServi($IB)
        || $isServi($IC)
        || $isServi($ID))),
            'erreur_217', $DE, $IA, $IB, $IC, $ID);
    $assert(!($isServi($HB) && !($isServi($HA) && ($HA <= $HB))), 'erreur_213', $HA, $HB);
    $assert(!($isServi($DE) && !($isServi($HA) && $float($HA) > 0)), 'erreur_216', $HA);
    $assert(!($isServi($IA) && $isServi($IB) && $float($IB) >= 0 && !($float($IA) < $float($IB))) && !(!$isServi($IB) && $isServi($IA)), 'erreur_214', $IA, $IB);
    $assert(!($isServi($ID) && !(760 <= $float($ID) && $float($ID) <= $float($IC))), 'erreur_215', $ID, $IC);
    $assert(!($isServi($IA)
      && ($isServi($HA)
        || $isServi($HB)
        || $isServi($HC)
        || $isServi($DE))),
            'erreur_217', $IA, $HA, $HB, $HC, $DE);
    $assert(!($isServi($IB)
      && ($isServi($HA)
        || $isServi($HB)
        || $isServi($HC)
        || $isServi($DE))),
            'erreur_217', $IB, $HA, $HB, $HC, $DE);
    $assert(!($isServi($ID)
      && ($isServi($HA)
        || $isServi($HB)
        || $isServi($HC)
        || $isServi($DE))),
            'erreur_217', $ID, $HA, $HB, $HC, $DE);
    $assert(!($isServi($CC)
      && !$isServi($CB)),
            'erreur_128', $CB, $CC);
    $atLeastOneServi = false;
    foreach (array($HA, $HB, $HC, $DE, $IA, $IB, $IC, $ID, $CA, $CB, $CC) as $field) {
      $atLeastOneServi = $atLeastOneServi || $isServi($field);
    }
    $assert($atLeastOneServi, 'erreur_201', $HA, $HB, $HC, $DE, $IA, $IB, $IC, $ID, $CA, $CB, $CC);
  }

  public static function tva3515sd_20150101($elt, $assert, $isServi, $float, $value, $controls) {
    $AA = $elt('tva3515sd_20150101_AA');
    $AB = $elt('tva3515sd_20150101_AB');
    $BA = $elt('tva3515sd_20150101_BA');
    $BB = $elt('tva3515sd_20150101_BB');
    $BC = $elt('tva3515sd_20150101_BC');
    $BD = $elt('tva3515sd_20150101_BD');
    $CA = $elt('tva3515sd_20150101_CA');
    $CB = $elt('tva3515sd_20150101_CB');
    $DA = $elt('tva3515sd_20150101_DA');
    $DB = $elt('tva3515sd_20150101_DB');
    $DC = $elt('tva3515sd_20150101_DC');
    $DD = $elt('tva3515sd_20150101_DD');
    $EA = $elt('tva3515sd_20150101_EA');
    $EB = $elt('tva3515sd_20150101_EB');

    $assert(!($isServi($CA) && $isServi($BD) && !($float($CA) >= $float($BD))),
            'erreur_115', $CA, $BD);

    $assert(!($isServi($EB)
      && !$isServi($EA)),
            'erreur_128', $EA, $EB);

  }

  public static function tva3517ddr_20150101($elt, $assert, $isServi, $float, $value, $controls) {
    $AA = $elt('tva3517ddr_20150101_AA');
    $AB = $elt('tva3517ddr_20150101_AB');
    $AC = $elt('tva3517ddr_20150101_AC');
    $AD = $elt('tva3517ddr_20150101_AD');
    $AE = $elt('tva3517ddr_20150101_AE');
    $AF1 = $elt('tva3517ddr_20150101_AF1');
    $AH = $elt('tva3517ddr_20150101_AH');
    $AJ = $elt('tva3517ddr_20150101_AJ');
    $BA = $elt('tva3517ddr_20150101_BA');
    $BB = $elt('tva3517ddr_20150101_BB');

    $assert(!(($isServi($BB) && $isServi($AA) && $float($AA) < 0) || (!$isServi($BB) && $isServi($AA) && $float($AA) < 150)),
            'erreur_225', $AA, $BB);
    $assert(!($isServi($BB) && !$isServi($BA)),
            'erreur_223', $BB, $BA);
    $assert($isServi($AD),
            'erreur_100', $AD);
    $assert($isServi($AC) && $isServi($AD) && $float($AD) <= $float($AC),
            'erreur_202', $AD);
    $assert(!($isServi($AA) && ($isServi($AC) && $isServi($AD) && $isServi($AE)) && !($float($AE) == ($float($AC) - $float($AD)))),
            'erreur_207', $AA, $AC, $AD, $AE);
    $assert(!(!$isServi($AA) && $isServi($AC) && $isServi($AD) && $isServi($AE) && !(($float($AC) + $float($AD) + $float($AE)) < 150)),
            'erreur_208', $AA, $AE, $AD, $AC);
    $assert($isServi($AF1),
            'erreur_100', $AF1);
    $assert($isServi($AH) || $isServi($AJ),
            'erreur_106', $AH, $AJ);
  }

  public static function tva3517ddr_20151020($elt, $assert, $isServi, $float, $value, $controls) {
    $AA = $elt('tva3517ddr_20151020_AA');
    $AB = $elt('tva3517ddr_20151020_AB');
    $AC = $elt('tva3517ddr_20151020_AC');
    $AD = $elt('tva3517ddr_20151020_AD');
    $AE = $elt('tva3517ddr_20151020_AE');
    $AF1 = $elt('tva3517ddr_20151020_AF1');
    $AH = $elt('tva3517ddr_20151020_AH');
    $AJ = $elt('tva3517ddr_20151020_AJ');
    $BA = $elt('tva3517ddr_20151020_BA');
    $BB = $elt('tva3517ddr_20151020_BB');

    $assert(!(($isServi($BB) && $isServi($AA) && $float($AA) < 0) || (!$isServi($BB) && $isServi($AA) && $float($AA) < 150)),
            'erreur_225', $AA, $BB);
    $assert(!($isServi($BB) && !$isServi($BA)),
            'erreur_223', $BB, $BA);
    $assert($isServi($AD),
            'erreur_100', $AD);
    $assert($isServi($AC) && $isServi($AD) && $float($AD) <= $float($AC),
            'erreur_202', $AD);
    $assert(!($isServi($AA) && ($isServi($AC) && $isServi($AD) && $isServi($AE)) && !($float($AE) == ($float($AC) - $float($AD)))),
            'erreur_207', $AA, $AC, $AD, $AE);
    $assert(!(!$isServi($AA) && $isServi($AC) && $isServi($AD) && $isServi($AE) && !(($float($AC) + $float($AD) + $float($AE)) < 150)),
            'erreur_208', $AA, $AE, $AD, $AC);
    $assert($isServi($AF1),
            'erreur_100', $AF1);
    $assert($isServi($AH) || $isServi($AJ),
            'erreur_106', $AH, $AJ);
  }

  public static function tva3525bis_20150101($elt, $assert, $isServi, $float, $value, $controls) {

    $BB = $elt('tva3525bis_20150101_BB');
    $BC = $elt('tva3525bis_20150101_BC');
    $BD = $elt('tva3525bis_20150101_BD');
    $BE = $elt('tva3525bis_20150101_BE');
    $AC = $elt('tva3525bis_20150101_AC');
    $AD = $elt('tva3525bis_20150101_AD');
    $DA = $elt('tva3525bis_20150101_DA');

    $assert(!($isServi($BC) && $isServi($BB) && !($float($BC) <= $float($BB))),
            'erreur_101', $BB, $BC);
    $assert(!($isServi($BE) && ($isServi($BB) || $isServi($BC) || $isServi($BD))),
            'erreur_042',
            $BE, $BB, $BC, $BD);
    $assert(!(!$isServi($BE) && ((!$isServi($BB) || $float($BB) <= 0) && (!$isServi($BC) || $float($BC) <= 0) && (!$isServi($BD) || $float($BD) <= 0))),
            'erreur_049',
            $BE, $BB, $BC, $BD);
    $assert(!($isServi($AD)
      && !$isServi($DA)),
            'erreur_128', $AD, $DA);
  }


  public static function tva3310ca3_20150101($elt, $assert, $isServi, $float, $value, $controls) {
    $BA = $elt('tva3310ca3_20150101_BA');
    $BB = $elt('tva3310ca3_20150101_BB');
    $BC = $elt('tva3310ca3_20150101_BC');

    $CA = $elt('tva3310ca3_20150101_CA');
    $CB = $elt('tva3310ca3_20150101_CB');
    $CC = $elt('tva3310ca3_20150101_CC');
    $CD = $elt('tva3310ca3_20150101_CD');
    $CE = $elt('tva3310ca3_20150101_CE');
    $CF = $elt('tva3310ca3_20150101_CF');
    $CG = $elt('tva3310ca3_20150101_CG');

    $DA = $elt('tva3310ca3_20150101_DA');
    $DB = $elt('tva3310ca3_20150101_DB');
    $DC = $elt('tva3310ca3_20150101_DC');
    $DD = $elt('tva3310ca3_20150101_DD');
    $DE = $elt('tva3310ca3_20150101_DE');
    $DF = $elt('tva3310ca3_20150101_DF');
    $DG = $elt('tva3310ca3_20150101_DG');

    $FB = $elt('tva3310ca3_20150101_FB');
    $FC = $elt('tva3310ca3_20150101_FC');
    $FD = $elt('tva3310ca3_20150101_FD');
    $FG = $elt('tva3310ca3_20150101_FG');
    $FH = $elt('tva3310ca3_20150101_FH');
    $FJ = $elt('tva3310ca3_20150101_FJ');
    $FK = $elt('tva3310ca3_20150101_FK');
    $FM = $elt('tva3310ca3_20150101_FM');
    $FN = $elt('tva3310ca3_20150101_FN');
    $FP = $elt('tva3310ca3_20150101_FP');
    $FR = $elt('tva3310ca3_20150101_FR');

    $GB = $elt('tva3310ca3_20150101_GB');
    $GC = $elt('tva3310ca3_20150101_GC');
    $GD = $elt('tva3310ca3_20150101_GD');
    $GG = $elt('tva3310ca3_20150101_GG');
    $GH = $elt('tva3310ca3_20150101_GH');
    $GJ = $elt('tva3310ca3_20150101_GJ');
    $GK = $elt('tva3310ca3_20150101_GK');
    $GM = $elt('tva3310ca3_20150101_GM');
    $GN = $elt('tva3310ca3_20150101_GN');
    $GP = $elt('tva3310ca3_20150101_GP');
    $GR = $elt('tva3310ca3_20150101_GR');

    $HA = $elt('tva3310ca3_20150101_HA');
    $HB = $elt('tva3310ca3_20150101_HB');
    $HC = $elt('tva3310ca3_20150101_HC');
    $HD = $elt('tva3310ca3_20150101_HD');
    $HE = $elt('tva3310ca3_20150101_HE');
    $HG = $elt('tva3310ca3_20150101_HG');
    $HH = $elt('tva3310ca3_20150101_HH');
    $HJ = $elt('tva3310ca3_20150101_HJ');

    $KA = $elt('tva3310ca3_20150101_KA');
    $KB = $elt('tva3310ca3_20150101_KB');
    $KE = $elt('tva3310ca3_20150101_KE');
    $KF = $elt('tva3310ca3_20150101_KF');
    $KG = $elt('tva3310ca3_20150101_KG');
    $KH = $elt('tva3310ca3_20150101_KH');
    $KJ = $elt('tva3310ca3_20150101_KJ');
    $KL = $elt('tva3310ca3_20150101_KL');
    $KR = $elt('tva3310ca3_20150101_KR');
    $KS = $elt('tva3310ca3_20150101_KS');
    $KT = $elt('tva3310ca3_20150101_KT');
    $KU = $elt('tva3310ca3_20150101_KU');

    $JA = $elt('tva3310ca3_20150101_JA');
    $JB = $elt('tva3310ca3_20150101_JB');
    $JC = $elt('tva3310ca3_20150101_JC');

    $assert(!(($isServi($FD) || $isServi($GD)) && !$isServi($elt('tva3310a_20150101_HB'))),
            'erreur_013',
            $GD, $FD);
    $assert(!($isServi($CC) && $isServi($CD) && $float($CD) > 0 && !($float($CD) <= $float($CC))),
            'erreur_136',
            $CC, $CD);
    $assert(!($isServi($FC) && $float($FC) > 0 && !($isServi($GC) && $float($GC) > 0)), 'erreur_111', $FC, $GC);
    $assert(!($isServi($FC) && $isServi($GC) && !(($float($FC) * 0.021) <= $float($GC) && $float($GC) <= ($float($FC) * 0.206))),
            'erreur_117', $FC, $GC);
    $assert((
              ($isServi($CA) ? $float($CA) : 0)
              + ($isServi($CB) ? $float($CB) : 0)
              + ($isServi($KH) ? $float($KH) : 0)
              + ($isServi($KR) ? $float($KR) : 0)
              + ($isServi($CC) ? $float($CC) : 0)
              + ($isServi($CF) ? $float($CF) : 0)
              + ($isServi($CG) ? $float($CG) : 0)
            ) == (
        ($isServi($FP) ? $float($FP) : 0)
        + ($isServi($FB) ? $float($FB) : 0)
        + ($isServi($FR) ? $float($FR) : 0)
        + ($isServi($FM) ? $float($FM) : 0)
        + ($isServi($FN) ? $float($FN) : 0)
        + ($isServi($FC) ? $float($FC) : 0)
        + ($isServi($FD) ? $float($FD) : 0)
      )
      , 'erreur_224', $CA, $CB, $KH, $KR, $CC, $CF, $CG, $FP, $FB, $FR, $FM, $FN, $FC, $FD);

    $assert(!($isServi($CC) && $isServi($GJ) && !(round($float($CC) * 0.021) <= $float($GJ) && $float($GJ) <= round($float($CC) * 0.20))),
            'erreur_117', $CC, $GJ);

    $assert(!($isServi($KR) && $isServi($KT) && !(round($float($KR) * 0.021) <= $float($KT) && $float($KT) <= round($float($KR) * 0.20))),
            'erreur_117', $KR, $KT);

    $assert(!($isServi($GH) && $isServi($GJ) && $isServi($GK) && $isServi($KT) && !($float($GJ) + $float($GK) + $float($KT) <= $float($GH))),
            'erreur_121', $GH, $GJ, $GK, $KT);

    $assert(!(!$isServi($GJ) && $isServi($CC)), 'erreur_038', $GJ, $CC);
    $assert(!($isServi($HH) && $float($HH) > 0 && !($isServi($CE) && $float($CE) > 0)), 'erreur_140', $HH, $CE);
    $assert(!($isServi($HH) && $isServi($HC) && !($float($HH) <= $float($HC))), 'erreur_051', $HH, $HC);
    $assert(!($isServi($HE) && !(0 < $float($HE) && $float($HE) < 100)), 'erreur_116', $HE);
    $assert(!($isServi($KG) && $isServi($HG) && !($float($KG) <= $float($HG))), 'erreur_205', $KG, $HG);
    $assert(!($isServi($JB) && $isServi($JA) && $isServi($KJ) && !($float($JB) <= $float($JA) - $float($KJ))), 'erreur_131', $JA, $JB, $KJ);
    $assert(!($isServi($KB) && $float($KB) > 0 && !$isServi($elt('tva3310a_20150101_HB'))),
            'erreur_013',
            $GD, $FD);


    $assert(!($isServi($BC)
      && !$isServi($BA)),
            'erreur_128', $BC, $BA);

    $assert(
      !($isServi($KF)

        && (
          ($isServi($CA) && $float($CA) > 0)
          || ($isServi($CB) && $float($CB) > 0)
          || ($isServi($CC) && $float($CC) > 0)
          || ($isServi($CD) && $float($CD) > 0)
          || ($isServi($CE) && $float($CE) > 0)
          || ($isServi($CF) && $float($CF) > 0)
          || ($isServi($CG) && $float($CG) > 0)
          || ($isServi($DA) && $float($DA) > 0)
          || ($isServi($DB) && $float($DB) > 0)
          || ($isServi($DC) && $float($DC) > 0)
          || ($isServi($DD) && $float($DD) > 0)
          || ($isServi($DE) && $float($DE) > 0)
          || ($isServi($DF) && $float($DF) > 0)
          || ($isServi($DG) && $float($DG) > 0)
          || ($isServi($FB) && $float($FB) > 0)
          || ($isServi($FC) && $float($FC) > 0)
          || ($isServi($FD) && $float($FD) > 0)
          || ($isServi($FM) && $float($FM) > 0)
          || ($isServi($FN) && $float($FN) > 0)
          || ($isServi($FP) && $float($FP) > 0)
          || ($isServi($FR) && $float($FR) > 0)
          || ($isServi($GB) && $float($GB) > 0)
          || ($isServi($GC) && $float($GC) > 0)
          || ($isServi($GD) && $float($GD) > 0)
          || ($isServi($GG) && $float($GG) > 0)
          || ($isServi($GH) && $float($GH) > 0)
          || ($isServi($GJ) && $float($GJ) > 0)
          || ($isServi($GK) && $float($GK) > 0)
          || ($isServi($GM) && $float($GM) > 0)
          || ($isServi($GN) && $float($GN) > 0)
          || ($isServi($GP) && $float($GP) > 0)
          || ($isServi($GR) && $float($GR) > 0)
          || ($isServi($HA) && $float($HA) > 0)
          || ($isServi($HB) && $float($HB) > 0)
          || ($isServi($HC) && $float($HC) > 0)
          || ($isServi($HD) && $float($HD) > 0)
          || ($isServi($HG) && $float($HG) > 0)
          || ($isServi($HH) && $float($HH) > 0)
          || ($isServi($KA) && $float($KA) > 0)
          || ($isServi($KB) && $float($KB) > 0)
          || ($isServi($KE) && $float($KE) > 0)
          || ($isServi($KG) && $float($KG) > 0)
          || ($isServi($KH) && $float($KH) > 0)
          || ($isServi($KJ) && $float($KJ) > 0)
          || ($isServi($KL) && $float($KL) > 0)
          || ($isServi($KR) && $float($KR) > 0)
          || ($isServi($KS) && $float($KS) > 0)
          || ($isServi($KT) && $float($KT) > 0)
          || ($isServi($KU) && $float($KU) > 0)
          || ($isServi($JA) && $float($JA) > 0)
          || ($isServi($JB) && $float($JB) > 0)
          || ($isServi($JC) && $float($JC) > 0)
        )
      ), 'erreur_042',
      $KF, $CA, $CB, $CC, $CD, $CE, $CF, $CG, $DA, $DB, $DC, $DD,
      $DE, $DF, $DG, $FB, $FC, $FD, $FM, $FN,
      $FP, $FR, $GB, $GC, $GD, $GG, $GH, $GJ, $GK, $GM, $GN, $GP,
      $GR, $HA, $HB, $HC, $HD, $HG, $HH, $KA, $KB, $KE, $KJ,
      $KG, $KH, $KL, $KR, $KS, $KT, $KU, $JA, $JB, $JC);


    $editableFields = array($CA, $CB, $CC, $CD, $CE, $CF, $CG, $DA, $DB, $DC, $DD,
                            $DE, $DF, $DG, $FB, $FC, $FD, $FM, $FN,
                            $FP, $FR, $GB, $GC, $GD, $GG, $GH, $GJ, $GK, $GM, $GN, $GP,
                            $GR, $HA, $HB, $HC, $HD, $HG, $HH, $KA, $KB, $KE, $KJ,
                            $KG, $KH, $KL, $KR, $KS, $KT, $KU, $JA, $JB, $JC);
    for ($i = 0; $i < count($editableFields); $i++) {
//      $assert(!(!$isServi($KF) && !($isServi($editableFields[$i]) && $float($editableFields[$i]) >= 0)), 'erreur_049', $KF, $editableFields[$i]);
    }


  }


  public static function tva3310a_20150101($elt, $assert, $isServi, $float, $value, $controls) {

    $AE = $elt('tva3310a_20150101_AE');
    $AF = $elt('tva3310a_20150101_AF');
    $BA = $elt('tva3310a_20150101_BA');
    $BB = $elt('tva3310a_20150101_BB');
    $BC = $elt('tva3310a_20150101_BC');
    $BE = $elt('tva3310a_20150101_BE');
    $BF = $elt('tva3310a_20150101_BF');
    $BK = $elt('tva3310a_20150101_BK');
    $BM = $elt('tva3310a_20150101_BM');
    $BN = $elt('tva3310a_20150101_BN');
    $BP = $elt('tva3310a_20150101_BP');
    $BQ = $elt('tva3310a_20150101_BQ');
    $BR = $elt('tva3310a_20150101_BR');
    $BS = $elt('tva3310a_20150101_BS');
    $CA = $elt('tva3310a_20150101_CA');
    $CB = $elt('tva3310a_20150101_CB');
    $CC = $elt('tva3310a_20150101_CC');
    $CE = $elt('tva3310a_20150101_CE');
    $CF = $elt('tva3310a_20150101_CF');
    $CK = $elt('tva3310a_20150101_CK');
    $CM = $elt('tva3310a_20150101_CM');
    $CN = $elt('tva3310a_20150101_CN');
    $CP = $elt('tva3310a_20150101_CP');
    $CQ = $elt('tva3310a_20150101_CQ');
    $CR = $elt('tva3310a_20150101_CR');
    $CS = $elt('tva3310a_20150101_CS');
    $DA = $elt('tva3310a_20150101_DA');
    $DB = $elt('tva3310a_20150101_DB');
    $FA = $elt('tva3310a_20150101_FA');
    $FB = $elt('tva3310a_20150101_FB');
    $FE = $elt('tva3310a_20150101_FE');
    $FF = $elt('tva3310a_20150101_FF');
    $FG = $elt('tva3310a_20150101_FG');
    $FJ = $elt('tva3310a_20150101_FJ');
    $FR = $elt('tva3310a_20150101_FR');
    $FT = $elt('tva3310a_20150101_FT');
    $FV = $elt('tva3310a_20150101_FV');
    $HB = $elt('tva3310a_20150101_HB');
    $HE = $elt('tva3310a_20150101_HE');
    $HF = $elt('tva3310a_20150101_HF');
    $HI = $elt('tva3310a_20150101_HI');
    $JA = $elt('tva3310a_20150101_JA');
    $JB = $elt('tva3310a_20150101_JB');
    $JC = $elt('tva3310a_20150101_JC');
    $JD = $elt('tva3310a_20150101_JD');
    $JE = $elt('tva3310a_20150101_JE');
    $JF = $elt('tva3310a_20150101_JF');
    $JG = $elt('tva3310a_20150101_JG');
    $JH = $elt('tva3310a_20150101_JH');
    $JJ = $elt('tva3310a_20150101_JJ');
    $JK = $elt('tva3310a_20150101_JK');
    $JL = $elt('tva3310a_20150101_JL');
    $JM = $elt('tva3310a_20150101_JM');
    $JN = $elt('tva3310a_20150101_JN');
    $JP = $elt('tva3310a_20150101_JP');
    $KA = $elt('tva3310a_20150101_KA');
    $KB = $elt('tva3310a_20150101_KB');
    $KC = $elt('tva3310a_20150101_KC');
    $KD = $elt('tva3310a_20150101_KD');
    $KE = $elt('tva3310a_20150101_KE');
    $KF = $elt('tva3310a_20150101_KF');
    $KG = $elt('tva3310a_20150101_KG');
    $KJ = $elt('tva3310a_20150101_KJ');
    $KL = $elt('tva3310a_20150101_KL');
    $KN = $elt('tva3310a_20150101_KN');
    $KP = $elt('tva3310a_20150101_KP');
    $KQ = $elt('tva3310a_20150101_KQ');
    $KS = $elt('tva3310a_20150101_KS');
    $KT = $elt('tva3310a_20150101_KT');
    $KU = $elt('tva3310a_20150101_KU');
    $KW = $elt('tva3310a_20150101_KW');
    $KX = $elt('tva3310a_20150101_KX');
    $KY = $elt('tva3310a_20150101_KY');
    $KZ = $elt('tva3310a_20150101_KZ');
    $LA = $elt('tva3310a_20150101_LA');
    $LB = $elt('tva3310a_20150101_LB');


    $assert(!($isServi($DB)
      && !$isServi($DA)),
            'erreur_128', $DA, $DB);

    $assert(!($isServi($BA) && $float($BA) > 0 && !($isServi($CA) && $float($CA) > 0)),
            'erreur_111', $BA, $CA);

    $assert(!($isServi($CA) && $float($CA) > 0 && !($isServi($BA) && $float($BA) > 0)),
            'erreur_112', $BA, $CA);

    $assert(!($isServi($BC) && $float($BC) > 0 && !($isServi($CC) && $float($CC) > 0)),
            'erreur_111', $BC, $CC);

    $assert(!($isServi($BC) && $isServi($CC) && !(($float($BC) * 0.021) <= $float($CC) && $float($CC) <= ($float($BC) * 0.206))),
            'erreur_117', $BC, $CC);

    $assert(!($isServi($BM) && $float($BM) > 0 && !($isServi($CM) && $float($CM) > 0)),
            'erreur_111', $BM, $CM);
    $assert(!($isServi($CM) && $float($CM) > 0 && !($isServi($BM) && $float($BM) > 0)),
            'erreur_112', $BM, $CM);

    $assert(!($isServi($BR) && $float($BR) > 0 && !($isServi($CR) && $float($CR) > 0)),
            'erreur_111', $BR, $CR);
    $assert(!($isServi($CR) && $float($CR) > 0 && !($isServi($BR) && $float($BR) > 0)),
            'erreur_112', $BR, $CR);

    $assert(!$isServi($JM), 'erreur_218', $JM);

  }


  public static function tva3310ter_20150101($elt, $assert, $isServi, $float, $value, $controls) {

    $AA = $elt('tva3310ter_20150101_AA');
    $AB = $elt('tva3310ter_20150101_AB');
    $AC = $elt('tva3310ter_20150101_AC');
    $BA = $elt('tva3310ter_20150101_BA');
    $BB = $elt('tva3310ter_20150101_BB');
    $BC = $elt('tva3310ter_20150101_BC');
    $BD = $elt('tva3310ter_20150101_BD');
    $BE = $elt('tva3310ter_20150101_BE');
    $BF = $elt('tva3310ter_20150101_BF');
    $BG = $elt('tva3310ter_20150101_BG');
    $BH = $elt('tva3310ter_20150101_BH');
    $BJ = $elt('tva3310ter_20150101_BJ');
    $BK = $elt('tva3310ter_20150101_BK');
    $CA = $elt('tva3310ter_20150101_CA');
    $CB = $elt('tva3310ter_20150101_CB');
    $CC = $elt('tva3310ter_20150101_CC');
    $CD = $elt('tva3310ter_20150101_CD');
    $CE = $elt('tva3310ter_20150101_CE');
    $CF = $elt('tva3310ter_20150101_CF');
    $CG = $elt('tva3310ter_20150101_CG');
    $CH = $elt('tva3310ter_20150101_CH');
    $CJ = $elt('tva3310ter_20150101_CJ');
    $CK = $elt('tva3310ter_20150101_CK');
    $DA = $elt('tva3310ter_20150101_DA');
    $DB = $elt('tva3310ter_20150101_DB');
    $DC = $elt('tva3310ter_20150101_DC');
    $DD = $elt('tva3310ter_20150101_DD');
    $DE = $elt('tva3310ter_20150101_DE');
    $DF = $elt('tva3310ter_20150101_DF');
    $DG = $elt('tva3310ter_20150101_DG');
    $DH = $elt('tva3310ter_20150101_DH');
    $DJ = $elt('tva3310ter_20150101_DJ');
    $DK = $elt('tva3310ter_20150101_DK');
    $DL = $elt('tva3310ter_20150101_DL');
    $EA = $elt('tva3310ter_20150101_EA');
    $EB = $elt('tva3310ter_20150101_EB');
    $EC = $elt('tva3310ter_20150101_EC');
    $ED = $elt('tva3310ter_20150101_ED');
    $EE = $elt('tva3310ter_20150101_EE');
    $EF = $elt('tva3310ter_20150101_EF');
    $EG = $elt('tva3310ter_20150101_EG');
    $EH = $elt('tva3310ter_20150101_EH');
    $EJ = $elt('tva3310ter_20150101_EJ');
    $EK = $elt('tva3310ter_20150101_EK');
    $EL = $elt('tva3310ter_20150101_EL');
    $FA = $elt('tva3310ter_20150101_FA');
    $FB = $elt('tva3310ter_20150101_FB');
    $FC = $elt('tva3310ter_20150101_FC');
    $FD = $elt('tva3310ter_20150101_FD');
    $FE = $elt('tva3310ter_20150101_FE');
    $FF = $elt('tva3310ter_20150101_FF');
    $FG = $elt('tva3310ter_20150101_FG');
    $FH = $elt('tva3310ter_20150101_FH');
    $FJ = $elt('tva3310ter_20150101_FJ');
    $FK = $elt('tva3310ter_20150101_FK');
    $FL = $elt('tva3310ter_20150101_FL');
    $GA = $elt('tva3310ter_20150101_GA');
    $GB = $elt('tva3310ter_20150101_GB');
    $GC = $elt('tva3310ter_20150101_GC');
    $GD = $elt('tva3310ter_20150101_GD');
    $GE = $elt('tva3310ter_20150101_GE');
    $GF = $elt('tva3310ter_20150101_GF');
    $GG = $elt('tva3310ter_20150101_GG');
    $GH = $elt('tva3310ter_20150101_GH');
    $GJ = $elt('tva3310ter_20150101_GJ');
    $GK = $elt('tva3310ter_20150101_GK');
    $GL = $elt('tva3310ter_20150101_GL');
    $HA = $elt('tva3310ter_20150101_HA');
    $HB = $elt('tva3310ter_20150101_HB');
    $HC = $elt('tva3310ter_20150101_HC');
    $HD = $elt('tva3310ter_20150101_HD');
    $HE = $elt('tva3310ter_20150101_HE');
    $HF = $elt('tva3310ter_20150101_HF');
    $HG = $elt('tva3310ter_20150101_HG');
    $HH = $elt('tva3310ter_20150101_HH');
    $HJ = $elt('tva3310ter_20150101_HJ');
    $HK = $elt('tva3310ter_20150101_HK');
    $HL = $elt('tva3310ter_20150101_HL');
    $JA = $elt('tva3310ter_20150101_JA');
    $JB = $elt('tva3310ter_20150101_JB');
    $JC = $elt('tva3310ter_20150101_JC');
    $JD = $elt('tva3310ter_20150101_JD');
    $JE = $elt('tva3310ter_20150101_JE');
    $JF = $elt('tva3310ter_20150101_JF');
    $JG = $elt('tva3310ter_20150101_JG');
    $JH = $elt('tva3310ter_20150101_JH');
    $JJ = $elt('tva3310ter_20150101_JJ');
    $JK = $elt('tva3310ter_20150101_JK');
    $JL = $elt('tva3310ter_20150101_JL');
    $KA = $elt('tva3310ter_20150101_KA');
    $KB = $elt('tva3310ter_20150101_KB');
    $KC = $elt('tva3310ter_20150101_KC');
    $KD = $elt('tva3310ter_20150101_KD');
    $KE = $elt('tva3310ter_20150101_KE');
    $KF = $elt('tva3310ter_20150101_KF');
    $KG = $elt('tva3310ter_20150101_KG');
    $KH = $elt('tva3310ter_20150101_KH');
    $KJ = $elt('tva3310ter_20150101_KJ');
    $KK = $elt('tva3310ter_20150101_KK');
    $KL = $elt('tva3310ter_20150101_KL');
    $LA = $elt('tva3310ter_20150101_LA');
    $LB = $elt('tva3310ter_20150101_LB');
    $LC = $elt('tva3310ter_20150101_LC');
    $LD = $elt('tva3310ter_20150101_LD');
    $LE = $elt('tva3310ter_20150101_LE');
    $LF = $elt('tva3310ter_20150101_LF');
    $LG = $elt('tva3310ter_20150101_LG');
    $LH = $elt('tva3310ter_20150101_LH');
    $LJ = $elt('tva3310ter_20150101_LJ');
    $LK = $elt('tva3310ter_20150101_LK');
    $LL = $elt('tva3310ter_20150101_LL');
    $MA = $elt('tva3310ter_20150101_MA');
    $MB = $elt('tva3310ter_20150101_MB');
    $MC = $elt('tva3310ter_20150101_MC');
    $MD = $elt('tva3310ter_20150101_MD');
    $ME = $elt('tva3310ter_20150101_ME');
    $MF = $elt('tva3310ter_20150101_MF');
    $MG = $elt('tva3310ter_20150101_MG');
    $MH = $elt('tva3310ter_20150101_MH');
    $MJ = $elt('tva3310ter_20150101_MJ');
    $MK = $elt('tva3310ter_20150101_MK');
    $ML = $elt('tva3310ter_20150101_ML');
    $NA = $elt('tva3310ter_20150101_NA');
    $NB = $elt('tva3310ter_20150101_NB');
    $NC = $elt('tva3310ter_20150101_NC');
    $ND = $elt('tva3310ter_20150101_ND');
    $NE = $elt('tva3310ter_20150101_NE');
    $NF = $elt('tva3310ter_20150101_NF');
    $NG = $elt('tva3310ter_20150101_NG');
    $NH = $elt('tva3310ter_20150101_NH');
    $NJ = $elt('tva3310ter_20150101_NJ');
    $NK = $elt('tva3310ter_20150101_NK');
    $NL = $elt('tva3310ter_20150101_NL');
    $PA = $elt('tva3310ter_20150101_PA');
    $PB = $elt('tva3310ter_20150101_PB');
    $PC = $elt('tva3310ter_20150101_PC');
    $PD = $elt('tva3310ter_20150101_PD');
    $PE = $elt('tva3310ter_20150101_PE');
    $PF = $elt('tva3310ter_20150101_PF');
    $PG = $elt('tva3310ter_20150101_PG');
    $PH = $elt('tva3310ter_20150101_PH');
    $PJ = $elt('tva3310ter_20150101_PJ');
    $PK = $elt('tva3310ter_20150101_PK');
    $PL = $elt('tva3310ter_20150101_PL');
    $QA = $elt('tva3310ter_20150101_QA');
    $QB = $elt('tva3310ter_20150101_QB');
    $QC = $elt('tva3310ter_20150101_QC');
    $QD = $elt('tva3310ter_20150101_QD');
    $QE = $elt('tva3310ter_20150101_QE');
    $QF = $elt('tva3310ter_20150101_QF');
    $QG = $elt('tva3310ter_20150101_QG');
    $QH = $elt('tva3310ter_20150101_QH');
    $QJ = $elt('tva3310ter_20150101_QJ');
    $QK = $elt('tva3310ter_20150101_QK');
    $QL = $elt('tva3310ter_20150101_QL');
    $QM = $elt('tva3310ter_20150101_QM');
    $RA = $elt('tva3310ter_20150101_RA');
    $RB = $elt('tva3310ter_20150101_RB');
    $RC = $elt('tva3310ter_20150101_RC');
    $RD = $elt('tva3310ter_20150101_RD');
    $RE = $elt('tva3310ter_20150101_RE');
    $RF = $elt('tva3310ter_20150101_RF');
    $RG = $elt('tva3310ter_20150101_RG');
    $RH = $elt('tva3310ter_20150101_RH');
    $RJ = $elt('tva3310ter_20150101_RJ');
    $RK = $elt('tva3310ter_20150101_RK');
    $RL = $elt('tva3310ter_20150101_RL');
    $RM = $elt('tva3310ter_20150101_RM');

    $assert(!($isServi($AC)
      && !$isServi($AA)),
            'erreur_128', $AC, $AA);

    $assert($isServi($AB) && !(($isServi($QM) || $isServi($RM)) && !(0 < $float($AB) && $float($AB) <= 100)),
            'erreur_222', $AB);

    $assert(!($isServi($BA) && !($isServi($CA) && 0 <= $float($CA) && $float($CA) <= 100)), 'erreur_116', $BA, $CA);
    $assert(!($isServi($BB) && !($isServi($CB) && 0 <= $float($CB) && $float($CB) <= 100)), 'erreur_116', $BB, $CB);
    $assert(!($isServi($BC) && !($isServi($CC) && 0 <= $float($CC) && $float($CC) <= 100)), 'erreur_116', $BC, $CC);
    $assert(!($isServi($BD) && !($isServi($CD) && 0 <= $float($CD) && $float($CD) <= 100)), 'erreur_116', $BD, $CD);
    $assert(!($isServi($BE) && !($isServi($CE) && 0 <= $float($CE) && $float($CE) <= 100)), 'erreur_116', $BE, $CE);
    $assert(!($isServi($BF) && !($isServi($CF) && 0 <= $float($CF) && $float($CF) <= 100)), 'erreur_116', $BF, $CF);
    $assert(!($isServi($BG) && !($isServi($CG) && 0 <= $float($CG) && $float($CG) <= 100)), 'erreur_116', $BG, $CG);
    $assert(!($isServi($BH) && !($isServi($CH) && 0 <= $float($CH) && $float($CH) <= 100)), 'erreur_116', $BH, $CH);
    $assert(!($isServi($BJ) && !($isServi($CJ) && 0 <= $float($CJ) && $float($CJ) <= 100)), 'erreur_116', $BJ, $CJ);
    $assert(!($isServi($BK) && !($isServi($CK) && 0 <= $float($CK) && $float($CK) <= 100)), 'erreur_116', $BK, $CK);


  }

  public static function tva3310ca3g_20150101($elt, $assert, $isServi, $float, $value, $controls) {

    $BA = $elt('tva3310ca3g_20150101_BA');
    $BB = $elt('tva3310ca3g_20150101_BB');
    $BC = $elt('tva3310ca3g_20150101_BC');
    $DA = $elt('tva3310ca3g_20150101_DA');
    $DB = $elt('tva3310ca3g_20150101_DB');
    $DC = $elt('tva3310ca3g_20150101_DC');
    $EA = $elt('tva3310ca3g_20150101_EA');
    $EB = $elt('tva3310ca3g_20150101_EB');
    $EC = $elt('tva3310ca3g_20150101_EC');
    $FA = $elt('tva3310ca3g_20150101_FA');
    $FB = $elt('tva3310ca3g_20150101_FB');
    $FE = $elt('tva3310ca3g_20150101_FE');
    $GA = $elt('tva3310ca3g_20150101_GA');
    $GB = $elt('tva3310ca3g_20150101_GB');
    $GD = $elt('tva3310ca3g_20150101_GD');
    $GE = $elt('tva3310ca3g_20150101_GE');
    $GF = $elt('tva3310ca3g_20150101_GF');
    $GH = $elt('tva3310ca3g_20150101_GH');
    $GJ = $elt('tva3310ca3g_20150101_GJ');
    $GK = $elt('tva3310ca3g_20150101_GK');
    $GL = $elt('tva3310ca3g_20150101_GL');
    $GM = $elt('tva3310ca3g_20150101_GM');
    $GO = $elt('tva3310ca3g_20150101_GO');
    $GP = $elt('tva3310ca3g_20150101_GP');
    $GQ = $elt('tva3310ca3g_20150101_GQ');
    $GR = $elt('tva3310ca3g_20150101_GR');
    $GS = $elt('tva3310ca3g_20150101_GS');
    $GT = $elt('tva3310ca3g_20150101_GT');
    $GU = $elt('tva3310ca3g_20150101_GU');
    $GV = $elt('tva3310ca3g_20150101_GV');
    $GX = $elt('tva3310ca3g_20150101_GX');
    $GZ = $elt('tva3310ca3g_20150101_GZ');
    $HB = $elt('tva3310ca3g_20150101_HB');
    $HC = $elt('tva3310ca3g_20150101_HC');
    $HE = $elt('tva3310ca3g_20150101_HE');
    $HF = $elt('tva3310ca3g_20150101_HF');
    $HK = $elt('tva3310ca3g_20150101_HK');
    $HL = $elt('tva3310ca3g_20150101_HL');
    $HM = $elt('tva3310ca3g_20150101_HM');
    $HN = $elt('tva3310ca3g_20150101_HN');
    $HO = $elt('tva3310ca3g_20150101_HO');
    $HP = $elt('tva3310ca3g_20150101_HP');
    $HQ = $elt('tva3310ca3g_20150101_HQ');
    $HR = $elt('tva3310ca3g_20150101_HR');
    $HS = $elt('tva3310ca3g_20150101_HS');
    $HT = $elt('tva3310ca3g_20150101_HT');
    $HU = $elt('tva3310ca3g_20150101_HU');
    $KH = $elt('tva3310ca3g_20150101_KH');
    $KJ = $elt('tva3310ca3g_20150101_KJ');
    $KK = $elt('tva3310ca3g_20150101_KK');
    $KL = $elt('tva3310ca3g_20150101_KL');
    $KM = $elt('tva3310ca3g_20150101_KM');
    $KN = $elt('tva3310ca3g_20150101_KN');
    $KR = $elt('tva3310ca3g_20150101_KR');
    $LA = $elt('tva3310ca3g_20150101_LA');
    $LB = $elt('tva3310ca3g_20150101_LB');
    $LC = $elt('tva3310ca3g_20150101_LC');
    $LD = $elt('tva3310ca3g_20150101_LD');
    $LF = $elt('tva3310ca3g_20150101_LF');
    $LG = $elt('tva3310ca3g_20150101_LG');

    $assert(!($isServi($BC) && !$isServi($BA)),
            'erreur_128', $BA, $BC);

    $assert(!$isServi($HT), 'erreur_218', $HT);
    $assert(!($isServi($EB) && $isServi($EA) && !($float($EB) <= $float($EA))),
            'erreur_131', $EA, $EB);

    $assert(($isServi($KR) && $float($KR) > 0) || ($isServi($DC) && $float($DC) > 0) || ($isServi($HK) && $float($HK) > 0),
            'erreur_212', $KR, $DC, $HK);
  }

  public static function tva3517sca12_20150101($elt, $assert, $isServi, $float, $value, $controls) {

    $CA = $elt('tva3517sca12_20150101_CA');
    $DA = $elt('tva3517sca12_20150101_DA');
    $DB = $elt('tva3517sca12_20150101_DB');
    $DC = $elt('tva3517sca12_20150101_DC');
    $EA = $elt('tva3517sca12_20150101_EA');
    $EB = $elt('tva3517sca12_20150101_EB');
    $EC = $elt('tva3517sca12_20150101_EC');
    $ED = $elt('tva3517sca12_20150101_ED');
    $EF = $elt('tva3517sca12_20150101_EF');
    $EG = $elt('tva3517sca12_20150101_EG');
    $EH = $elt('tva3517sca12_20150101_EH');
    $EJ = $elt('tva3517sca12_20150101_EJ');
    $EL = $elt('tva3517sca12_20150101_EL');
    $EM = $elt('tva3517sca12_20150101_EM');
    $EN = $elt('tva3517sca12_20150101_EN');
    $EP = $elt('tva3517sca12_20150101_EP');
    $EQ = $elt('tva3517sca12_20150101_EQ');
    $EU = $elt('tva3517sca12_20150101_EU');
    $EV = $elt('tva3517sca12_20150101_EV');
    $EW = $elt('tva3517sca12_20150101_EW');
    $EX = $elt('tva3517sca12_20150101_EX');
    $EY = $elt('tva3517sca12_20150101_EY');
    $EZ = $elt('tva3517sca12_20150101_EZ');
    $FA = $elt('tva3517sca12_20150101_FA');
    $FB = $elt('tva3517sca12_20150101_FB');
    $FC = $elt('tva3517sca12_20150101_FC');
    $FD = $elt('tva3517sca12_20150101_FD');
    $FE = $elt('tva3517sca12_20150101_FE');
    $FF = $elt('tva3517sca12_20150101_FF');
    $FG = $elt('tva3517sca12_20150101_FG');
    $FJ = $elt('tva3517sca12_20150101_FJ');
    $FL = $elt('tva3517sca12_20150101_FL');
    $FM = $elt('tva3517sca12_20150101_FM');
    $FN = $elt('tva3517sca12_20150101_FN');
    $FP = $elt('tva3517sca12_20150101_FP');
    $FR = $elt('tva3517sca12_20150101_FR');
    $FU = $elt('tva3517sca12_20150101_FU');
    $FV = $elt('tva3517sca12_20150101_FV');
    $FW = $elt('tva3517sca12_20150101_FW');
    $FY = $elt('tva3517sca12_20150101_FY');
    $GA = $elt('tva3517sca12_20150101_GA');
    $GB = $elt('tva3517sca12_20150101_GB');
    $GC = $elt('tva3517sca12_20150101_GC');
    $GF = $elt('tva3517sca12_20150101_GF');
    $GH = $elt('tva3517sca12_20150101_GH');
    $HA = $elt('tva3517sca12_20150101_HA');
    $HB = $elt('tva3517sca12_20150101_HB');
    $HC = $elt('tva3517sca12_20150101_HC');
    $JA = $elt('tva3517sca12_20150101_JA');
    $JB = $elt('tva3517sca12_20150101_JB');
    $KA = $elt('tva3517sca12_20150101_KA');
    $KB = $elt('tva3517sca12_20150101_KB');
    $KD = $elt('tva3517sca12_20150101_KD');
    $KE = $elt('tva3517sca12_20150101_KE');
    $KF = $elt('tva3517sca12_20150101_KF');
    $KG = $elt('tva3517sca12_20150101_KG');
    $KH = $elt('tva3517sca12_20150101_KH');
    $KJ = $elt('tva3517sca12_20150101_KJ');
    $KL = $elt('tva3517sca12_20150101_KL');
    $KM = $elt('tva3517sca12_20150101_KM');
    $LA = $elt('tva3517sca12_20150101_LA');
    $LB = $elt('tva3517sca12_20150101_LB');
    $MA = $elt('tva3517sca12_20150101_MA');
    $MD = $elt('tva3517sca12_20150101_MD');
    $ME = $elt('tva3517sca12_20150101_ME');
    $MF = $elt('tva3517sca12_20150101_MF');
    $MG = $elt('tva3517sca12_20150101_MG');
    $MH = $elt('tva3517sca12_20150101_MH');
    $MJ = $elt('tva3517sca12_20150101_MJ');
    $MK = $elt('tva3517sca12_20150101_MK');
    $ML = $elt('tva3517sca12_20150101_ML');
    $MM = $elt('tva3517sca12_20150101_MM');
    $MN = $elt('tva3517sca12_20150101_MN');
    $NA = $elt('tva3517sca12_20150101_NA');
    $NB = $elt('tva3517sca12_20150101_NB');
    $NC = $elt('tva3517sca12_20150101_NC');
    $QA = $elt('tva3517sca12_20150101_QA');
    $QD = $elt('tva3517sca12_20150101_QD');
    $QE = $elt('tva3517sca12_20150101_QE');
    $QF = $elt('tva3517sca12_20150101_QF');
    $QH = $elt('tva3517sca12_20150101_QH');
    $QJ = $elt('tva3517sca12_20150101_QJ');
    $QS = $elt('tva3517sca12_20150101_QS');
    $RA = $elt('tva3517sca12_20150101_RA');
    $RB = $elt('tva3517sca12_20150101_RB');
    $RC = $elt('tva3517sca12_20150101_RC');
    $RE = $elt('tva3517sca12_20150101_RE');
    $RF = $elt('tva3517sca12_20150101_RF');
    $RG = $elt('tva3517sca12_20150101_RG');
    $RH = $elt('tva3517sca12_20150101_RH');
    $RK = $elt('tva3517sca12_20150101_RK');
    $RL = $elt('tva3517sca12_20150101_RL');
    $RM = $elt('tva3517sca12_20150101_RM');
    $RN = $elt('tva3517sca12_20150101_RN');
    $SA = $elt('tva3517sca12_20150101_SA');
    $SB = $elt('tva3517sca12_20150101_SB');
    $SC = $elt('tva3517sca12_20150101_SC');
    $SD = $elt('tva3517sca12_20150101_SD');
    $TA = $elt('tva3517sca12_20150101_TA');
    $TB = $elt('tva3517sca12_20150101_TB');
    $TC = $elt('tva3517sca12_20150101_TC');
    $TD = $elt('tva3517sca12_20150101_TD');
    $UA = $elt('tva3517sca12_20150101_UA');
    $UB = $elt('tva3517sca12_20150101_UB');
    $UC = $elt('tva3517sca12_20150101_UC');
    $UD = $elt('tva3517sca12_20150101_UD');
    $VA = $elt('tva3517sca12_20150101_VA');
    $VC = $elt('tva3517sca12_20150101_VC');
    $VE = $elt('tva3517sca12_20150101_VE');
    $VF = $elt('tva3517sca12_20150101_VF');
    $VJ = $elt('tva3517sca12_20150101_VJ');
    $VK = $elt('tva3517sca12_20150101_VK');
    $VL = $elt('tva3517sca12_20150101_VL');
    $VM = $elt('tva3517sca12_20150101_VM');
    $VN = $elt('tva3517sca12_20150101_VN');
    $VP = $elt('tva3517sca12_20150101_VP');
    $VQ = $elt('tva3517sca12_20150101_VQ');
    $VS = $elt('tva3517sca12_20150101_VS');
    $VT = $elt('tva3517sca12_20150101_VT');
    $VV = $elt('tva3517sca12_20150101_VV');
    $VW = $elt('tva3517sca12_20150101_VW');
    $VX = $elt('tva3517sca12_20150101_VX');
    $VY = $elt('tva3517sca12_20150101_VY');
    $VZ = $elt('tva3517sca12_20150101_VZ');
    $WA = $elt('tva3517sca12_20150101_WA');


    $assert(!($isServi($VK) && !$isServi($CA)), 'erreur_128', $CA, $VK);

    $controls['erreur_111']($EJ, $FJ);
    $controls['erreur_112']($FJ, $EJ);
    $controls['erreur_111']($EW, $FW);
    $controls['erreur_112']($FW, $EW);
    $controls['erreur_111']($GF, $GH);
    $controls['erreur_112']($GH, $GF);
    $controls['erreur_111']($EH, $EZ);
    $controls['erreur_112']($EZ, $EH);
    $controls['erreur_111']($EG, $FG);
    $controls['erreur_117']($EG, $FG, 0.021, 0.206);
    $controls['erreur_112']($FG, $EG);
    $controls['erreur_111']($EY, $FY);
    $controls['erreur_112']($FY, $EY);
    $controls['erreur_111']($VN, $VP);
    $controls['erreur_112']($VP, $VN);
    $controls['erreur_111']($EH, $EZ);
    $controls['erreur_112']($EZ, $EH);
    $controls['erreur_111']($EL, $FL);
    $controls['erreur_112']($FL, $EL);
    $controls['erreur_111']($EM, $FM);
    $controls['erreur_112']($FM, $EM);
    $controls['erreur_111']($EN, $FN);
    $controls['erreur_112']($FN, $EN);
    $controls['erreur_111']($EP, $FP);
    $controls['erreur_112']($FP, $EP);
    $controls['erreur_117']($EP, $FP, 0.021, 0.20);


    $assert(!($isServi($EQ) && $isServi($FP) && !($float($EQ) <= $float($FP))),
            'erreur_137', $EQ, $FP);
    $assert(!($isServi($HB) && $float($HB) > 0 && !(
        $float($HB) == 0.2 * ($float($EB) + $float($EC)
          + $float($ED) + $float($VM) + $float($EX) + $float($EF)
          + $float($EU) + $float($EV) + $float($EJ) + $float($EG) +
          $float($EW) + $float($GF))
      )),
            'erreur_034', $HB, $EB, $EC, $ED, $VM, $EX, $EF, $EU, $EV, $EJ, $EG, $EW, $GF);
    $assert(!($isServi($JB) && $float($JB) >= 0 && !(0 < $float($JB) && $float($JB) <= 100)), 'erreur_116', $JB);
    $assert(!($isServi($FE) && $isServi($KD) && !($float($FE) < $float($KD))),
            'erreur_205', $FE, $KD);
    $assert(!($isServi($RA) && $float($RA) >= 0 && !($float($RA) == $float($RB) + $float($RC) + $float($RE)))
      , 'erreur_204', $RA, $RB, $RC, $RE);
    $assert(!($isServi($RA) && $isServi($RB) && !($float($RB) <= $float($RA))),
            'erreur_132', $RA, $RB);

    $casesAccomptesRemplies = 0;
    $casesAccomptesRemplies += ($isServi($MD) || $isServi($ME)) ? 1 : 0;
    $casesAccomptesRemplies += ($isServi($MF) || $isServi($MG)) ? 1 : 0;
    $casesAccomptesRemplies += ($isServi($MH) || $isServi($MJ)) ? 1 : 0;
    $casesAccomptesRemplies += ($isServi($MK) || $isServi($ML)) ? 1 : 0;
    $casesCoches = 0;
    $casesCoches += $isServi($TA) ? 1 : 0;
    $casesCoches += $isServi($TB) ? 1 : 0;
    $casesCoches += $isServi($TC) ? 1 : 0;
    $casesCoches += $isServi($TD) ? 1 : 0;
    $assert(!($isServi($MA) && $float($MA) > 0 && !($casesAccomptesRemplies == $casesCoches)),
            'erreur_124', $MA, $MD, $ME, $MF, $MG, $MH, $MJ, $MK, $ML);

    $controls['erreur_129']($TA, $UA);
    $controls['erreur_129']($TB, $UB);
    $controls['erreur_129']($TC, $UC);
    $controls['erreur_129']($TD, $UD);
    $controls['erreur_134']($UA, $elt('t_identif_CA'), $elt('t_identif_CB'));
    $controls['erreur_134']($UB, $elt('t_identif_CA'), $elt('t_identif_CB'));
    $controls['erreur_134']($UC, $elt('t_identif_CA'), $elt('t_identif_CB'));
    $controls['erreur_134']($UD, $elt('t_identif_CA'), $elt('t_identif_CB'));

    $requiredFields = array(
      $DA, $DB, $DC, $EA, $EB, $EC, $ED, $EF,
      $EG, $EH, $EJ, $EL, $EM, $EN, $EP, $EQ, $EU, $EV, $EW,
      $EX, $EY, $EZ, $FA, $FB, $FC, $FD, $FF, $FG, $FJ,
      $FL, $FM, $FN, $FP, $FR, $FU, $FV, $FW, $FY, $GA, $GB,
      $GC, $GF, $GH, $HA, $HB, $HC, $JA, $KA, $KB, $KD,
      $KL, $KM, $LA, $LB, $MA,
      $MM, $MN, $NA,
      $NB, $NC, $QA, $QD, $QE, $QF, $QH, $QJ, $QS,
      $RA, $RB, $RC, $RE, $RF, $RG, $RH, $RK, $RL, $RM, $RN,
      $SA, $SB, $SC,
      $VA, $VC, $VE, $VF, $VJ, $VM, $VN, $VP,
      $VQ, $VS, $VT, $VV, $VW, $VX, $VY, $VZ, $WA);

    $controls['erreur_042']($SD, $requiredFields);
    $controls['erreur_049']($SD, $requiredFields);
  }

  public static function tva3517bisca12_20150101($elt, $assert, $isServi, $float, $value, $controls) {


    $AE = $elt('tva3517bisca12_20150101_AE');
    $AF = $elt('tva3517bisca12_20150101_AF');
    $AG = $elt('tva3517bisca12_20150101_AG');
    $BA = $elt('tva3517bisca12_20150101_BA');
    $DA = $elt('tva3517bisca12_20150101_DA');
    $DB = $elt('tva3517bisca12_20150101_DB');
    $DC = $elt('tva3517bisca12_20150101_DC');
    $DD = $elt('tva3517bisca12_20150101_DD');
    $DE = $elt('tva3517bisca12_20150101_DE');
    $DH = $elt('tva3517bisca12_20150101_DH');
    $DJ = $elt('tva3517bisca12_20150101_DJ');
    $DK = $elt('tva3517bisca12_20150101_DK');
    $DL = $elt('tva3517bisca12_20150101_DL');
    $DM = $elt('tva3517bisca12_20150101_DM');
    $DN = $elt('tva3517bisca12_20150101_DN');
    $DP = $elt('tva3517bisca12_20150101_DP');
    $DQ = $elt('tva3517bisca12_20150101_DQ');
    $DR = $elt('tva3517bisca12_20150101_DR');
    $DS = $elt('tva3517bisca12_20150101_DS');
    $DU = $elt('tva3517bisca12_20150101_DU');
    $DV = $elt('tva3517bisca12_20150101_DV');
    $DY = $elt('tva3517bisca12_20150101_DY');
    $DZ = $elt('tva3517bisca12_20150101_DZ');
    $EA = $elt('tva3517bisca12_20150101_EA');
    $EB = $elt('tva3517bisca12_20150101_EB');
    $EC = $elt('tva3517bisca12_20150101_EC');
    $ED = $elt('tva3517bisca12_20150101_ED');
    $EE = $elt('tva3517bisca12_20150101_EE');
    $EH = $elt('tva3517bisca12_20150101_EH');
    $EJ = $elt('tva3517bisca12_20150101_EJ');
    $EK = $elt('tva3517bisca12_20150101_EK');
    $EL = $elt('tva3517bisca12_20150101_EL');
    $EM = $elt('tva3517bisca12_20150101_EM');
    $EN = $elt('tva3517bisca12_20150101_EN');
    $EP = $elt('tva3517bisca12_20150101_EP');
    $EQ = $elt('tva3517bisca12_20150101_EQ');
    $ER = $elt('tva3517bisca12_20150101_ER');
    $ES = $elt('tva3517bisca12_20150101_ES');
    $EU = $elt('tva3517bisca12_20150101_EU');
    $EV = $elt('tva3517bisca12_20150101_EV');
    $EZ = $elt('tva3517bisca12_20150101_EZ');
    $FA = $elt('tva3517bisca12_20150101_FA');
    $FB = $elt('tva3517bisca12_20150101_FB');
    $FC = $elt('tva3517bisca12_20150101_FC');
    $FD = $elt('tva3517bisca12_20150101_FD');
    $FF = $elt('tva3517bisca12_20150101_FF');
    $FG = $elt('tva3517bisca12_20150101_FG');
    $GA = $elt('tva3517bisca12_20150101_GA');
    $GB = $elt('tva3517bisca12_20150101_GB');
    $HA = $elt('tva3517bisca12_20150101_HA');
    $JA = $elt('tva3517bisca12_20150101_JA');
    $JB = $elt('tva3517bisca12_20150101_JB');
    $JC = $elt('tva3517bisca12_20150101_JC');
    $KA = $elt('tva3517bisca12_20150101_KA');
    $KB = $elt('tva3517bisca12_20150101_KB');
    $KC = $elt('tva3517bisca12_20150101_KC');
    $KD = $elt('tva3517bisca12_20150101_KD');
    $KF = $elt('tva3517bisca12_20150101_KF');
    $KH = $elt('tva3517bisca12_20150101_KH');
    $LC = $elt('tva3517bisca12_20150101_LC');
    $LD = $elt('tva3517bisca12_20150101_LD');
    $LF = $elt('tva3517bisca12_20150101_LF');
    $LH = $elt('tva3517bisca12_20150101_LH');
    $LK = $elt('tva3517bisca12_20150101_LK');
    $LM = $elt('tva3517bisca12_20150101_LM');
    $MA = $elt('tva3517bisca12_20150101_MA');
    $MB = $elt('tva3517bisca12_20150101_MB');
    $MC = $elt('tva3517bisca12_20150101_MC');
    $NA = $elt('tva3517bisca12_20150101_NA');
    $NB = $elt('tva3517bisca12_20150101_NB');
    $NC = $elt('tva3517bisca12_20150101_NC');
    $ND = $elt('tva3517bisca12_20150101_ND');
    $NL = $elt('tva3517bisca12_20150101_NL');
    $NM = $elt('tva3517bisca12_20150101_NM');
    $NN = $elt('tva3517bisca12_20150101_NN');
    $NO = $elt('tva3517bisca12_20150101_NO');
    $RC = $elt('tva3517bisca12_20150101_RC');
    $RD = $elt('tva3517bisca12_20150101_RD');

    $RF = $elt('tva3517bisca12_20150101_RF');
    $RG = $elt('tva3517bisca12_20150101_RG');
    $RH = $elt('tva3517bisca12_20150101_RH');
    $RJ = $elt('tva3517bisca12_20150101_RJ');
    $RK = $elt('tva3517bisca12_20150101_RK');
    $RL = $elt('tva3517bisca12_20150101_RL');

    $assert(!($isServi($AG) && !$isServi($BA)), 'erreur_128', $BA, $AG);
    $controls['erreur_111']($DH, $EH);
    $controls['erreur_117']($DH, $EH, 0.021, 0.206);
    $controls['erreur_112']($EH, $DH);
    $controls['erreur_111']($DJ, $EJ);
    $controls['erreur_112']($EJ, $DJ);
    $controls['erreur_111']($DZ, $EZ);
    $controls['erreur_112']($EZ, $DZ);
    $controls['erreur_111']($DR, $DS);
    $controls['erreur_112']($DS, $DR);
    $controls['erreur_111']($DL, $EL);
    $controls['erreur_112']($EL, $DL);
    $controls['erreur_111']($DM, $EM);
    $controls['erreur_112']($EM, $DM);
    $controls['erreur_111']($DN, $EN);
    $controls['erreur_112']($EN, $DN);
    $controls['erreur_111']($DP, $EP);
    $controls['erreur_112']($EP, $DP);
    $assert(!($isServi($DP) && $float($DP) && !(
        ($isServi($FA) && $float($FA) > 0)
        || ($isServi($FB) && $float($FB) > 0)
        || ($isServi($FD) && $float($FD) > 0)
      )), 'erreur_135', $DP, $FA, $FB, $FD);
    $controls['erreur_117']($DP, $EP, 0.021, 0.20);
    $controls['erreur_116']($FG, $FG);
    $assert(!($isServi($KH) && $isServi($FF) && !($float($KH) <= $float($FF))), 'erreur_205', $KH, $FF);
    $assert(!($isServi($MA) && $isServi($MB) && !($float($MB) <= $float($MA))), 'erreur_131', $MA, $MB);
    // manque assert 49
    // manque assert 42
    $assert($isServi($AE), 'Champ Obligatoire', $AE);
  }


  public static function is2571_2015($elt, $assert, $isServi, $float, $value, $controls) {

    $FA = $elt('is2571_2015_FA');
    $CA = $elt('is2571_2015_CA');
    $DA = $elt('is2571_2015_DA');
    $FB = $elt('is2571_2015_FB');
    $FC = $elt('is2571_2015_FC');
    $FD = $elt('is2571_2015_FD');
    $FE = $elt('is2571_2015_FE');
    $FF = $elt('is2571_2015_FF');
    $FG = $elt('is2571_2015_FG');
    $CF = $elt('is2571_2015_CF');
    $CC = $elt('is2571_2015_CC');
    $CD = $elt('is2571_2015_CD');
    $DB = $elt('is2571_2015_DB');
    $CE = $elt('is2571_2015_CE');
    $CG = $elt('is2571_2015_CG');
    $CH = $elt('is2571_2015_CH');
    $FH = $elt('is2571_2015_FH');
    $FK = $elt('is2571_2015_FK');
    $FM = $elt('is2571_2015_FM');
    $FN = $elt('is2571_2015_FN');

    $assert(!($isServi($FH) && !($isServi($FK) && $isServi($FM))), 'erreur_310', $FH);
    $assert(!($isServi($FH) && $isServi($CH) && !($float($FH) <= $float($CH))), 'erreur_311', $FH);
    $assert(!($isServi($FK) && !($isServi($FH) && $isServi($FM))), 'erreur_310', $FK);
    $assert(!($isServi($FM) && !($isServi($FH) && $isServi($FK))), 'erreur_310', $FM);

    $PidentifKF = $elt('p_identif_KF');
    $date_FM = explode('/', $value($FM));
    $date_FM = strtotime($date_FM[0] . '-' . $date_FM[1] . '-' . $date_FM[2]);
    $date_KF = explode('/', $value($PidentifKF));
    $date_KF = strtotime('01-' . $date_KF[0] . '-' . $date_KF[1]);
    $date_KF_inf_dateFM = $date_FM < $date_KF;

    $assert(!($isServi($FM) && $isServi($PidentifKF) && !($date_KF_inf_dateFM)), 'erreur_312', $FM);

  }

  public static function is2572_2015($elt, $assert, $isServi, $float, $value, $controls) {
    $PN = $elt('is2572_2015_PN');
    $PQ = $elt('is2572_2015_PQ');
    $PR = $elt('is2572_2015_PR');
    $PS = $elt('is2572_2015_PS');
    $PT = $elt('is2572_2015_PT');
    $PU = $elt('is2572_2015_PU');
    $PV = $elt('is2572_2015_PV');
    $PW = $elt('is2572_2015_PW');
    $AD = $elt('is2572_2015_AD');
    $BD = $elt('is2572_2015_BD');
    $CA = $elt('is2572_2015_CA');
    $DA = $elt('is2572_2015_DA');
    $EA = $elt('is2572_2015_EA');
    $EB = $elt('is2572_2015_EB');
    $TA = $elt('is2572_2015_TA');
    $TB = $elt('is2572_2015_TB');
    $GC = $elt('is2572_2015_GC');
    $GD = $elt('is2572_2015_GD');
    $GE = $elt('is2572_2015_GE');
    $PM = $elt('is2572_2015_PM');
    $IA = $elt('is2572_2015_IA');
    $JA = $elt('is2572_2015_JA');
    $MA = $elt('is2572_2015_MA');
    $ME = $elt('is2572_2015_ME');
    $MB = $elt('is2572_2015_MB');
    $MC = $elt('is2572_2015_MC');
    $MD = $elt('is2572_2015_MD');
    $KA = $elt('is2572_2015_KA');
    $NA = $elt('is2572_2015_NA');
    $KB = $elt('is2572_2015_KB');
    $NB = $elt('is2572_2015_NB');
    $KC = $elt('is2572_2015_KC');
    $NC = $elt('is2572_2015_NC');
    $ND = $elt('is2572_2015_ND');
    $NE = $elt('is2572_2015_NE');
    $NF = $elt('is2572_2015_NF');
    $NG = $elt('is2572_2015_NG');
    $NJ = $elt('is2572_2015_NJ');
    $NK = $elt('is2572_2015_NK');
    $NL = $elt('is2572_2015_NL');
    $NM = $elt('is2572_2015_NM');
    $NN = $elt('is2572_2015_NN');
    $OD = $elt('is2572_2015_OD');
    $NO = $elt('is2572_2015_NO');
    $RD = $elt('is2572_2015_RD');
    $RE = $elt('is2572_2015_RE');
    $RF = $elt('is2572_2015_RF');
    $LA = $elt('is2572_2015_LA');
    $LF = $elt('is2572_2015_LF');
    $LE = $elt('is2572_2015_LE');
    $OB = $elt('is2572_2015_OB');
    $LB = $elt('is2572_2015_LB');
    $LC = $elt('is2572_2015_LC');
    $LD = $elt('is2572_2015_LD');
    $OC = $elt('is2572_2015_OC');
    $RA = $elt('is2572_2015_RA');
    $RB = $elt('is2572_2015_RB');
    $RC = $elt('is2572_2015_RC');
    $RG = $elt('is2572_2015_RG');
    $RH = $elt('is2572_2015_RH');
    $RJ = $elt('is2572_2015_RJ');
    $RK = $elt('is2572_2015_RK');
    $RL = $elt('is2572_2015_RL');
    $RM = $elt('is2572_2015_RM');
    $RN = $elt('is2572_2015_RN');
    $RR = $elt('is2572_2015_RR');
    $RP = $elt('is2572_2015_RP');
    $RS = $elt('is2572_2015_RS');
    $RT = $elt('is2572_2015_RT');
    $RU = $elt('is2572_2015_RU');
    $RV = $elt('is2572_2015_RV');
    $RX = $elt('is2572_2015_RX');
    $RY = $elt('is2572_2015_RY');
    $RW = $elt('is2572_2015_RW');
    $RZ = $elt('is2572_2015_RZ');
    $PA = $elt('is2572_2015_PA');
    $PB = $elt('is2572_2015_PB');
    $PC = $elt('is2572_2015_PC');
    $PD = $elt('is2572_2015_PD');
    $PE = $elt('is2572_2015_PE');
    $PF = $elt('is2572_2015_PF');
    $PG = $elt('is2572_2015_PG');
    $PH = $elt('is2572_2015_PH');
    $PJ = $elt('is2572_2015_PJ');
    $PK = $elt('is2572_2015_PK');
    $PL = $elt('is2572_2015_PL');


    $assert(!($isServi($LC) && $isServi($LD) && !($float($LD) <= $float($LC))), 'erreur_316', $LD);
    $assert(!($isServi($LF) && $isServi($LE) && !($float($LE) <= $float($LF))), 'erreur_317', $LE);
    $assert(!($isServi($PH) && !($isServi($PK) && $isServi($PJ))), 'erreur_310', $PH);

    $PidentifKF = $elt('p_identif_KF');
    $date_PJ = explode('/', $value($PJ));
    $date_PJ = strtotime($date_PJ[0] . '-' . $date_PJ[1] . '-' . $date_PJ[0]);
    $date_KF = explode('/', $value($PidentifKF));
    $date_KF = strtotime('01-'.$date_KF[0].'-'. $date_KF[1]);
    $date_KF_inf_datePJ = $date_PJ < $date_KF ;

    $assert(!($isServi($PJ) && $isServi($PidentifKF) && !($date_KF_inf_datePJ)), 'erreur_318', $PJ);
    $assert(!($isServi($PJ) && !($isServi($PK) && $isServi($PH))), 'erreur_310', $PJ);
    $assert(!($isServi($PK) && !($isServi($PH) && $isServi($PJ))), 'erreur_310', $PK);
    $assert(!($isServi($CA) && $isServi($PK) && $float($CA) > 0 && $float($PK) > 0 && !($float($CA) >= $float($PK))), 'erreur_311', $PK);
    $assert(!($isServi($EA) && $float($EA) > 0 && !($isServi($DA) && $float($EA) <= $float($DA))), 'erreur_311', $EA);
    $assert(!($isServi($PE) && !($isServi($PG) && $isServi($PF))), 'erreur_310', $PE);
    $assert(!($isServi($PF) && !($isServi($PG) && $isServi($PE))), 'erreur_310', $PF);

    $DAminusEA = 0;
    if ($isServi($DA)) {
      $DAminusEA = $float($DA);
    }
    if ($isServi($EA)) {
      $DAminusEA -= $float($EA);
    }
    $assert(!($isServi($DA) && $float($DA) > 0 && $isServi($PG) && $float($PG) >= 0 && !($DAminusEA >= $float($PG))), 'erreur_319', $PG);

  }

  public static function is2573_2015($elt, $assert, $isServi, $float, $value, $controls) {
    $AA = $elt('is2573_2015_AA');
    $BA = $elt('is2573_2015_BA');
    $CA = $elt('is2573_2015_CA');


    // for each row
    $rowIndex = 1;
    while ($elt('is2573_2015_AB/' . $rowIndex)->isset) {
      $AB = $elt('is2573_2015_AB/'.$rowIndex);
      $AC = $elt('is2573_2015_AC/'.$rowIndex);
      $AF = $elt('is2573_2015_AF/'.$rowIndex);
      $AG = $elt('is2573_2015_AG/'.$rowIndex);
      $AH = $elt('is2573_2015_AH/'.$rowIndex);
      $AI = $elt('is2573_2015_AI/'.$rowIndex);
      $KA = $elt('is2573_2015_KA/'.$rowIndex);
      $KB = $elt('is2573_2015_KB/'.$rowIndex);
      $KC = $elt('is2573_2015_KC/'.$rowIndex);
      $KD = $elt('is2573_2015_KD/'.$rowIndex);

      $assert($value($AB) != 'REL' && $value($AB) != 'RES', 'erreur_309', $AB);
      $assert(!(($isServi($AB) || $isServi($AC) || $isServi($AF) || $isServi($AG) || $isServi($AH) || $isServi($AI))
        && !($isServi($AB) && $isServi($AC) && $isServi($AG) && $float($AG) > 0)),
              'erreur_315', $AB, $AC, $AF, $AG, $AH, $AI);
      $assert(!($isServi($AF) && !($value($AB) == 'RAD' && $isServi($AH))), 'erreur_313', $AF, $AB, $AH);
      $assert(!($isServi($AH) && !$isServi($AI)), 'erreur_305', $AI);
      $assert(!($isServi($AI) && !$isServi($AH)), 'erreur_305', $AH);

      $assert(!($isServi($KD) && $isServi($AG) && !($float($KD) <= $float($AG))), 'erreur_314', $KD);
      $rowIndex++;
    }

    // for each row
    $rowIndex = 1;
    while ($elt('is2573_2015_BB/' . $rowIndex)->isset) {
      $BB = $elt('is2573_2015_BB/'.$rowIndex);
      $BC = $elt('is2573_2015_BC/'.$rowIndex);
      $BD = $elt('is2573_2015_BD/'.$rowIndex);
      $BE = $elt('is2573_2015_BE/'.$rowIndex);


      $assert(!(($isServi($BB) || $isServi($BC) || $isServi($BD) || $isServi($BE))
        && !($isServi($BB) && $isServi($BC) && $isServi($BE) && $float($BE) > 0)),
              'erreur_307', $BB, $BC, $BD, $BE);
      $rowIndex++;
    }

    // for each row
    $rowIndex = 1;
    while ($elt('is2573_2015_CB/' . $rowIndex)->isset) {
      $CB = $elt('is2573_2015_CB/'.$rowIndex);
      $CC = $elt('is2573_2015_CC/'.$rowIndex);
      $CD = $elt('is2573_2015_CD/'.$rowIndex);
      $CE = $elt('is2573_2015_CE/'.$rowIndex);
      $CF = $elt('is2573_2015_CF/'.$rowIndex);


      $assert(!(($isServi($CB) || $isServi($CC) || $isServi($CD) || $isServi($CE) || $isServi($CF))
        && !($isServi($CB) && $isServi($CC) && $isServi($CD) && $isServi($CF) && $float($CF) > 0)),
              'erreur_308', $CB, $CC, $CD, $CF);
      $rowIndex++;
    }
  }

  public static function cvae1329ac_20150101($elt, $assert, $isServi, $float, $value, $controls) {


    $AA = $elt('cvae1329ac_20150101_AA');
    $AB = $elt('cvae1329ac_20150101_AB');
    $AC = $elt('cvae1329ac_20150101_AC');
    $AD = $elt('cvae1329ac_20150101_AD');
    $BA = $elt('cvae1329ac_20150101_BA');
    $BB = $elt('cvae1329ac_20150101_BB');
    $BC = $elt('cvae1329ac_20150101_BC');
    $CA = $elt('cvae1329ac_20150101_CA');
    $CB = $elt('cvae1329ac_20150101_CB');
    $DA = $elt('cvae1329ac_20150101_DA');
    $DB = $elt('cvae1329ac_20150101_DB');
    $EA = $elt('cvae1329ac_20150101_EA');
    $EB = $elt('cvae1329ac_20150101_EB');
    $EC = $elt('cvae1329ac_20150101_EC');
    $ED = $elt('cvae1329ac_20150101_ED');
    $GA = $elt('cvae1329ac_20150101_GA');
    $GB = $elt('cvae1329ac_20150101_GB');
    $HA = $elt('cvae1329ac_20150101_HA');
    $KA = $elt('cvae1329ac_20150101_KA');
//    $KACheckbox = $elt('cvae1329ac_20150101_KA_checkbox');

    $assert($isServi($AA) && $float($AA) > 152500, 'cvae_erreur_202', $AA);
    $assert(!($isServi($AB) && $float($AB) > 0 && !($isServi($AA) && $float($AA) > 0)), 'cvae_erreur_205', $AB);
    $assert(!($isServi($AD) && $float($AD) > 0 && !($isServi($AA) && $float($AD) >= $float($AA))), 'cvae_erreur_206', $AD);
    $assert(!($isServi($EB) && $isServi($EC) && $float($EB) > 0 && $float($EC) > 0), 'cvae_erreur_207', $EB);
  }

  public static function cvae1329def_20150101($elt, $assert, $isServi, $float, $value, $controls) {


    $AA = $elt('cvae1329def_20150101_AA');
    $AB = $elt('cvae1329def_20150101_AB');
    $AC = $elt('cvae1329def_20150101_AC');
    $AD = $elt('cvae1329def_20150101_AD');
    $BA = $elt('cvae1329def_20150101_BA');
    $BB = $elt('cvae1329def_20150101_BB');
    $BC = $elt('cvae1329def_20150101_BC');
    $CA = $elt('cvae1329def_20150101_CA');
    $CB = $elt('cvae1329def_20150101_CB');
    $DA = $elt('cvae1329def_20150101_DA');
    $DB = $elt('cvae1329def_20150101_DB');
    $EA = $elt('cvae1329def_20150101_EA');
    $EB = $elt('cvae1329def_20150101_EB');
    $EC = $elt('cvae1329def_20150101_EC');
    $ED = $elt('cvae1329def_20150101_ED');
    $GA = $elt('cvae1329def_20150101_GA');
    $GB = $elt('cvae1329def_20150101_GB');
    $GC = $elt('cvae1329def_20150101_GC');
    $GD = $elt('cvae1329def_20150101_GD');
    $GE = $elt('cvae1329def_20150101_GE');
    $HA = $elt('cvae1329def_20150101_HA');
    $HB = $elt('cvae1329def_20150101_HB');
    $HC = $elt('cvae1329def_20150101_HC');
    $HD = $elt('cvae1329def_20150101_HD');
    $JA = $elt('cvae1329def_20150101_JA');
    $JE = $elt('cvae1329def_20150101_JE');
    $JK = $elt('cvae1329def_20150101_JK');
    $KA = $elt('cvae1329def_20150101_KA');
    $KB = $elt('cvae1329def_20150101_KB');

    $assert($isServi($AA) && $float($AA) >= 0, 'cvae_erreur_201', $AA);
    $assert(!($isServi($AB) && $float($AB) >= 0 && !$isServi($AA)), 'Vous devez saisir ligne 01 votre chiffre d\'affaires rapporté sur 12 mois. Merci de corriger', $AB);
    $assert(!($isServi($AB) && $float($AB) > 0 && !($isServi($AA) && $float($AA) > 0)), 'cvae_erreur_205', $AB);
    $assert(!($isServi($AD) && $float($AD) > 0 && !($isServi($AA) && $float($AD) >= $float($AA))), 'cvae_erreur_206', $AD);
//    $assert(!($isServi($GB) && $float($GB) > 0 && !($isServi($GC) && $float($GC) > 0)), 'Présence de la taxe additionnelle sans montant d\'acompte versés.', $GC);



  }
}
