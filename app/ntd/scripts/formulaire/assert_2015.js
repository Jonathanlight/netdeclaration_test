/** Millésime 2015 **/

asserts.functions.tva3519_20150101 = function($elt,
                                              $assert,
                                              $controls,
                                              $isServi,
                                              $float,
                                              $value,
                                              $readonly,
                                              $isSiren,
                                              $XOR) {

  var $CB = $elt(NTD.Identif.tField('CB'));
  var $DC1 = $elt('tva3519_20150101_DC1');
  var $DC2 = $elt('tva3519_20150101_DC2');
  var $DC3 = $elt('tva3519_20150101_DC3');
  var $DC4 = $elt('tva3519_20150101_DC4');
  var $DC5 = $elt('tva3519_20150101_DC5');
  var $DC6 = $elt('tva3519_20150101_DC6');
  var $DC7 = $elt('tva3519_20150101_DC7');
  var $DC8 = $elt('tva3519_20150101_DC8');
  var $DC9 = $elt('tva3519_20150101_DC9');
  var $DC10 = $elt('tva3519_20150101_DC10');
  var $DD = $elt('tva3519_20150101_DD');
  var $DE = $elt('tva3519_20150101_DE');
  var $DF = $elt('tva3519_20150101_DF');
  var $DG1 = $elt('tva3519_20150101_DG1');
  var $DG2 = $elt('tva3519_20150101_DG2');
  var $DG3 = $elt('tva3519_20150101_DG3');
  var $DG4 = $elt('tva3519_20150101_DG4');
  var $DH = $elt('tva3519_20150101_DH');
  var $DI = $elt('tva3519_20150101_DI');
  var $DJ = $elt('tva3519_20150101_DJ');
  var $DK = $elt('tva3519_20150101_DK');
  var $DM = $elt('tva3519_20150101_DM');
  var $DN = $elt('tva3519_20150101_DN');
  var $FJ = $elt('tva3519_20150101_FJ');
  var $FK = $elt('tva3519_20150101_FK');
  var $FL = $elt('tva3519_20150101_FL');
  var $AA1 = $elt('tva3519_20150101_AA1');
  var $AA2 = $elt('tva3519_20150101_AA2');
  var $AA3 = $elt('tva3519_20150101_AA3');
  var $AA4 = $elt('tva3519_20150101_AA4');
  var $DL = $elt('tva3519_20150101_DL');

  // --- Hide Paiement Box in F-Identif
  NTD.Identif.t("hidePaiement", []);


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
  $assert(function() {
            if ($isServi($CB) && !$isServi($DJ)) {
              var month = $value($CB).split('/');
              month = month[1];
              var minimumDN = 760;
              if (month == 12) {
                minimumDN = 150;
              }
              return $float($DN) >= minimumDN;
            }
            return true;
          }(),
          'erreur_225', $DN);
};

asserts.functions.tva3514_20150101 = function($elt,
                                              $assert,
                                              $controls,
                                              $isServi,
                                              $float,
                                              $value,
                                              $readonly,
                                              $isSiren,
                                              $XOR,
                                              $addition,
                                              $soustraction,
                                              $percent) {


  var $HA = $elt('tva3514_20150101_HA');
  var $HB = $elt('tva3514_20150101_HB');
  var $HC = $elt('tva3514_20150101_HC');
  var $DE = $elt('tva3514_20150101_DE');
  var $IA = $elt('tva3514_20150101_IA');
  var $IB = $elt('tva3514_20150101_IB');
  var $IC = $elt('tva3514_20150101_IC');
  var $ID = $elt('tva3514_20150101_ID');
  var $CA = $elt('tva3514_20150101_CA');
  var $CB = $elt('tva3514_20150101_CB');
  var $CC = $elt('tva3514_20150101_CC');


  // ---- Control
  if ($isServi($HA) || $isServi($HB) || $isServi($DE)) {
    $readonly($IA, true).setValue('');
    $readonly($IB, true).setValue('');
    $readonly($ID, true).setValue('');

    $readonly($HA, false);
    $readonly($HB, false);
    $readonly($DE, false);
  }
  else if ($isServi($IA) || $isServi($IB) || $isServi($ID)) {
    $readonly($HA, true).setValue('');
    $readonly($HB, true).setValue('');
    $readonly($DE, true);
    $DE.checked = false;

    $readonly($IA, false);
    $readonly($IB, false);
    $readonly($ID, false);
  }
  else {
    $readonly($HA, false);
    $readonly($HB, false);
    $readonly($DE, false);
    $readonly($IA, false);
    $readonly($IB, false);
    $readonly($ID, false);
  }

  // --- IC = IB - IA
  $readonly($elt($IC), true);
  $soustraction($IC, $IB, $IA);


  // --- HC = HA - HB
  $readonly($elt($HC), true);
  $soustraction($HC, $HA, $HB);


  // --- show Tidenf form
  NTD.Identif.t("hidePaiement", []);
  if ($float($HC) > 0) {
    NTD.Identif.t("showPaiement", [$float($HC)]);
  }
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
  $assert([$HA, $HB, $HC, $DE, $IA, $IB, $IC, $ID, $CA, $CB, $CC].some(function(elt) {
    return $isServi(elt);
  }), 'erreur_201', $HA, $HB, $HC, $DE, $IA, $IB, $IC, $ID, $CA, $CB, $CC);

};

asserts.functions.tva3515sd_20150101 = function($elt,
                                                $assert,
                                                $controls,
                                                $isServi,
                                                $float,
                                                $value,
                                                $readonly,
                                                $isSiren,
                                                $XOR) {


  var $AA = $elt('tva3515sd_20150101_AA');
  var $AB = $elt('tva3515sd_20150101_AB');
  var $BA = $elt('tva3515sd_20150101_BA');
  var $BB = $elt('tva3515sd_20150101_BB');
  var $BC = $elt('tva3515sd_20150101_BC');
  var $BD = $elt('tva3515sd_20150101_BD');
  var $CA = $elt('tva3515sd_20150101_CA');
  var $CB = $elt('tva3515sd_20150101_CB');
  var $DA = $elt('tva3515sd_20150101_DA');
  var $DB = $elt('tva3515sd_20150101_DB');
  var $DC = $elt('tva3515sd_20150101_DC');
  var $DD = $elt('tva3515sd_20150101_DD');
  var $EA = $elt('tva3515sd_20150101_EA');
  var $EB = $elt('tva3515sd_20150101_EB');


  $assert(!($isServi($CA) && $isServi($BD) && !($float($CA) >= $float($BD))),
          'erreur_115', $CA, $BD);

  $assert(!($isServi($EB)
          && !$isServi($EA)),
          'erreur_128', $EA, $EB);


};

asserts.functions.tva3517ddr_20150101 = function($elt,
                                                 $assert,
                                                 $controls,
                                                 $isServi,
                                                 $float,
                                                 $value,
                                                 $readonly,
                                                 $isSiren,
                                                 $XOR) {


  var $AA = $elt('tva3517ddr_20150101_AA');
  var $AB = $elt('tva3517ddr_20150101_AB');
  var $AC = $elt('tva3517ddr_20150101_AC');
  var $AD = $elt('tva3517ddr_20150101_AD');
  var $AE = $elt('tva3517ddr_20150101_AE');
  var $AF1 = $elt('tva3517ddr_20150101_AF1');
  var $AH = $elt('tva3517ddr_20150101_AH');
  var $AJ = $elt('tva3517ddr_20150101_AJ');
  var $BA = $elt('tva3517ddr_20150101_BA');
  var $BB = $elt('tva3517ddr_20150101_BB');


  NTD.Identif.t("hidePaiement", []);

  if ($isServi($AA) && $isServi($AB)) {
    $value($AC, Math.max(0, $float($AA) + $float($AB)));
  }

  if ($isServi($AA)) {
    if ($isServi($AC) && $isServi($AD)) {
      $value($AE, Math.max(0, $float($AC) - $float($AD)));
    } else {
      $value($AE, '');
    }
  }


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
};

asserts.functions.tva3525bis_20150101 = function($elt,
                                                 $assert,
                                                 $controls,
                                                 $isServi,
                                                 $float,
                                                 $value,
                                                 $readonly,
                                                 $isSiren,
                                                 $XOR) {


  var $BB = $elt('tva3525bis_20150101_BB');
  var $BC = $elt('tva3525bis_20150101_BC');
  var $BD = $elt('tva3525bis_20150101_BD');
  var $BE = $elt('tva3525bis_20150101_BE');
  var $AC = $elt('tva3525bis_20150101_AC');
  var $AD = $elt('tva3525bis_20150101_AD');
  var $DA = $elt('tva3525bis_20150101_DA');

  if ($isServi($BB) && $isServi($BC)) {
    $value($BD, Math.max(0, $float($BB) - $float($BC)));
  }
  if ($isServi($BE)) {
    $readonly($BB, true).setValue('');
    $readonly($BC, true).setValue('');
    $readonly($BD, true).setValue('');
  }
  else {
    $readonly($BB, false);
    $readonly($BC, false);
    $readonly($BD, false);
  }

  NTD.Identif.t("hidePaiement", []);
  if ($isServi($BD) && $float($BD) > 0) {
    NTD.Identif.t("showPaiement", [$float($BD)]);
  }

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


};

asserts.functions.tva3310ca3_20150101 = function($elt,
                                                 $assert,
                                                 $controls,
                                                 $isServi,
                                                 $float,
                                                 $value,
                                                 $readonly,
                                                 $isSiren,
                                                 $XOR) {


  var $BA = $elt('tva3310ca3_20150101_BA');
  var $BB = $elt('tva3310ca3_20150101_BB');
  var $BC = $elt('tva3310ca3_20150101_BC');

  var $CA = $elt('tva3310ca3_20150101_CA');
  var $CB = $elt('tva3310ca3_20150101_CB');
  var $CC = $elt('tva3310ca3_20150101_CC');
  var $CD = $elt('tva3310ca3_20150101_CD');
  var $CE = $elt('tva3310ca3_20150101_CE');
  var $CF = $elt('tva3310ca3_20150101_CF');
  var $CG = $elt('tva3310ca3_20150101_CG');

  var $DA = $elt('tva3310ca3_20150101_DA');
  var $DB = $elt('tva3310ca3_20150101_DB');
  var $DC = $elt('tva3310ca3_20150101_DC');
  var $DD = $elt('tva3310ca3_20150101_DD');
  var $DE = $elt('tva3310ca3_20150101_DE');
  var $DF = $elt('tva3310ca3_20150101_DF');
  var $DG = $elt('tva3310ca3_20150101_DG');

  var $FB = $elt('tva3310ca3_20150101_FB');
  var $FC = $elt('tva3310ca3_20150101_FC');
  var $FD = $elt('tva3310ca3_20150101_FD');
  var $FG = $elt('tva3310ca3_20150101_FG');
  var $FH = $elt('tva3310ca3_20150101_FH');
  var $FJ = $elt('tva3310ca3_20150101_FJ');
  var $FK = $elt('tva3310ca3_20150101_FK');
  var $FM = $elt('tva3310ca3_20150101_FM');
  var $FN = $elt('tva3310ca3_20150101_FN');
  var $FP = $elt('tva3310ca3_20150101_FP');
  var $FR = $elt('tva3310ca3_20150101_FR');

  var $GB = $elt('tva3310ca3_20150101_GB');
  var $GC = $elt('tva3310ca3_20150101_GC');
  var $GD = $elt('tva3310ca3_20150101_GD');
  var $GG = $elt('tva3310ca3_20150101_GG');
  var $GH = $elt('tva3310ca3_20150101_GH');
  var $GJ = $elt('tva3310ca3_20150101_GJ');
  var $GK = $elt('tva3310ca3_20150101_GK');
  var $GM = $elt('tva3310ca3_20150101_GM');
  var $GN = $elt('tva3310ca3_20150101_GN');
  var $GP = $elt('tva3310ca3_20150101_GP');
  var $GR = $elt('tva3310ca3_20150101_GR');

  var $HA = $elt('tva3310ca3_20150101_HA');
  var $HB = $elt('tva3310ca3_20150101_HB');
  var $HC = $elt('tva3310ca3_20150101_HC');
  var $HD = $elt('tva3310ca3_20150101_HD');
  var $HE = $elt('tva3310ca3_20150101_HE');
  var $HG = $elt('tva3310ca3_20150101_HG');
  var $HH = $elt('tva3310ca3_20150101_HH');
  var $HJ = $elt('tva3310ca3_20150101_HJ');

  var $KA = $elt('tva3310ca3_20150101_KA');
  var $KB = $elt('tva3310ca3_20150101_KB');
  var $KE = $elt('tva3310ca3_20150101_KE');
  var $KF = $elt('tva3310ca3_20150101_KF');
  var $KG = $elt('tva3310ca3_20150101_KG');
  var $KH = $elt('tva3310ca3_20150101_KH');
  var $KJ = $elt('tva3310ca3_20150101_KJ');
  var $KL = $elt('tva3310ca3_20150101_KL');
  var $KR = $elt('tva3310ca3_20150101_KR');
  var $KS = $elt('tva3310ca3_20150101_KS');
  var $KT = $elt('tva3310ca3_20150101_KT');
  var $KU = $elt('tva3310ca3_20150101_KU');

  var $JA = $elt('tva3310ca3_20150101_JA');
  var $JB = $elt('tva3310ca3_20150101_JB');
  var $JC = $elt('tva3310ca3_20150101_JC');


  $readonly($FG, true);
  $readonly($FH, true);
  $readonly($FJ, true);
  $readonly($FK, true);


  var editableFields = [$CA, $CB, $CC, $CD, $CE, $CF, $CG, $DA, $DB, $DC, $DD,
                        $DE, $DF, $DG, $FB, $FC, $FD, $FM, $FN,
                        $FP, $FR, $GB, $GC, $GD, $GG, $GH, $GJ, $GK, $GM, $GN, $GP,
                        $GR, $HA, $HB, $HC, $HD, $HG, $HH, $KA, $KB, $KE, $KJ,
                        $KG, $KH, $KL, $KR, $KS, $KT, $KU, $JA, $JB, $JC];
  if ($isServi($KF)) {
    for (var i = 0; i < editableFields.length; i++) {
      $readonly(editableFields[i], true).setValue('');
    }
  }
  else {
    for (var i = 0; i < editableFields.length; i++) {
      $readonly(editableFields[i], false);
    }
  }
  $readonly($GP, true);
  $readonly($GB, true);
  $readonly($GR, true);
  $readonly($GM, true);
  $readonly($GN, true);

  $readonly($GH, true);
  var GHValue = 0;
  [$GP, $GB, $FH, $GM, $GN, $FK, $GC, $GD, $GG, $GR, $KS].each(function(elt) {
    if ($float(elt) > 0) {
      GHValue += $float(elt);
    }
  });
  $value($GH, GHValue);

  $readonly($HG, true);
  var HGValue = 0;
  [$HA, $HB, $HC, $HD, $KU].each(function(elt) {
    if ($float(elt) > 0) {
      HGValue += $float(elt);
    }
  });
  $value($HG, HGValue);

  $readonly($JA, true);
  var JAValue = ($isServi($HG) ? $float($HG) : 0) - ($isServi($GH) ? $float($GH) : 0);
  $value($JA, Math.max(0, JAValue));

  $readonly($JC, true);
  var JCValue = ($isServi($JA) ? $float($JA) : 0);
  JCValue -= ($isServi($JB) ? $float($JB) : 0);
  JCValue -= ($isServi($KJ) ? $float($KJ) : 0);
  $value($JC, JCValue);

  $readonly($KA, true);
  var KAValue = ($isServi($GH) ? $float($GH) : 0) - ($isServi($HG) ? $float($HG) : 0);
  $value($KA, Math.max(0, KAValue));

  $readonly($KE, true);
  var KEValue = ($isServi($KA) ? $float($KA) : 0) + ($isServi($KB) ? $float($KB) : 0) - ($isServi($KL) ? $float($KL) : 0);
  $value($KE, KEValue);
  NTD.Identif.t("hidePaiement", []);
  if (KEValue > 0) {
    NTD.Identif.t("showPaiement", [KEValue]);
  }


  $assert(!(($isServi($FD) || $isServi($GD)) && !$isServi($elt('tva3310a_20150101_HB'))),
          'erreur_013',
          $GD, $FD);
  $assert(!($isServi($CC) && $isServi($CD) && $float($CD) > 0 && !($float($CD) <= $float($CC))),
          'erreur_136',
          $CC, $CD);
  $assert(!($isServi($FC) && $float($FC) > 0 && !($isServi($GC) && $float($GC) > 0)), 'erreur_111', $FC, $GC);
  $assert(!($isServi($FC) && $isServi($GC) && !(    ($float($FC) * 0.021) <= $float($GC) && $float($GC) <= ($float($FC) * 0.206)       )),
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

  $assert(!($isServi($CC) && $isServi($GJ) && !(Math.round($float($CC) * 0.021) <= $float($GJ) && $float($GJ) <= Math.round($float($CC) * 0.20))),
          'erreur_117', $CC, $GJ);

  $assert(!($isServi($KR) && $isServi($KT) && !(Math.round($float($KR) * 0.021) <= $float($KT) && $float($KT) <= Math.round($float($KR) * 0.20))),
          'erreur_117', $KR, $KT);

  $assert(!( $isServi($GH) && $isServi($GJ) && $isServi($GK) && $isServi($KT) && !( $float($GJ) + $float($GK) + $float($KT) <= $float($GH) )),
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

  for (var i = 0; i < editableFields.length; i++) {
    //$assert(!(!$isServi($KF) && !($isServi(editableFields[i]) && $float(editableFields[i]) >= 0)), 'erreur_049', $KF, editableFields[i]);
  }

};


asserts.functions.tva3310a_20150101 = function($elt,
                                               $assert,
                                               $controls,
                                               $isServi,
                                               $float,
                                               $value,
                                               $readonly,
                                               $isSiren,
                                               $XOR) {

  var $AE = $elt('tva3310a_20150101_AE');
  var $AF = $elt('tva3310a_20150101_AF');
  var $BA = $elt('tva3310a_20150101_BA');
  var $BB = $elt('tva3310a_20150101_BB');
  var $BC = $elt('tva3310a_20150101_BC');
  var $BE = $elt('tva3310a_20150101_BE');
  var $BF = $elt('tva3310a_20150101_BF');
  var $BK = $elt('tva3310a_20150101_BK');
  var $BM = $elt('tva3310a_20150101_BM');
  var $BN = $elt('tva3310a_20150101_BN');
  var $BP = $elt('tva3310a_20150101_BP');
  var $BQ = $elt('tva3310a_20150101_BQ');
  var $BR = $elt('tva3310a_20150101_BR');
  var $BS = $elt('tva3310a_20150101_BS');
  var $CA = $elt('tva3310a_20150101_CA');
  var $CB = $elt('tva3310a_20150101_CB');
  var $CC = $elt('tva3310a_20150101_CC');
  var $CE = $elt('tva3310a_20150101_CE');
  var $CF = $elt('tva3310a_20150101_CF');
  var $CK = $elt('tva3310a_20150101_CK');
  var $CM = $elt('tva3310a_20150101_CM');
  var $CN = $elt('tva3310a_20150101_CN');
  var $CP = $elt('tva3310a_20150101_CP');
  var $CQ = $elt('tva3310a_20150101_CQ');
  var $CR = $elt('tva3310a_20150101_CR');
  var $CS = $elt('tva3310a_20150101_CS');
  var $DA = $elt('tva3310a_20150101_DA');
  var $DB = $elt('tva3310a_20150101_DB');
  var $FA = $elt('tva3310a_20150101_FA');
  var $FB = $elt('tva3310a_20150101_FB');
  var $FE = $elt('tva3310a_20150101_FE');
  var $FF = $elt('tva3310a_20150101_FF');
  var $FG = $elt('tva3310a_20150101_FG');
  var $FJ = $elt('tva3310a_20150101_FJ');
  var $FR = $elt('tva3310a_20150101_FR');
  var $FT = $elt('tva3310a_20150101_FT');
  var $FV = $elt('tva3310a_20150101_FV');
  var $HB = $elt('tva3310a_20150101_HB');
  var $HE = $elt('tva3310a_20150101_HE');
  var $HF = $elt('tva3310a_20150101_HF');
  var $HI = $elt('tva3310a_20150101_HI');
  var $JA = $elt('tva3310a_20150101_JA');
  var $JB = $elt('tva3310a_20150101_JB');
  var $JC = $elt('tva3310a_20150101_JC');
  var $JD = $elt('tva3310a_20150101_JD');
  var $JE = $elt('tva3310a_20150101_JE');
  var $JF = $elt('tva3310a_20150101_JF');
  var $JG = $elt('tva3310a_20150101_JG');
  var $JH = $elt('tva3310a_20150101_JH');
  var $JJ = $elt('tva3310a_20150101_JJ');
  var $JK = $elt('tva3310a_20150101_JK');
  var $JL = $elt('tva3310a_20150101_JL');
  var $JM = $elt('tva3310a_20150101_JM');
  var $JN = $elt('tva3310a_20150101_JN');
  var $JP = $elt('tva3310a_20150101_JP');
  var $KA = $elt('tva3310a_20150101_KA');
  var $KB = $elt('tva3310a_20150101_KB');
  var $KC = $elt('tva3310a_20150101_KC');
  var $KD = $elt('tva3310a_20150101_KD');
  var $KE = $elt('tva3310a_20150101_KE');
  var $KF = $elt('tva3310a_20150101_KF');
  var $KG = $elt('tva3310a_20150101_KG');
  var $KJ = $elt('tva3310a_20150101_KJ');
  var $KL = $elt('tva3310a_20150101_KL');
  var $KN = $elt('tva3310a_20150101_KN');
  var $KP = $elt('tva3310a_20150101_KP');
  var $KQ = $elt('tva3310a_20150101_KQ');
  var $KS = $elt('tva3310a_20150101_KS');
  var $KT = $elt('tva3310a_20150101_KT');
  var $KU = $elt('tva3310a_20150101_KU');
  var $KW = $elt('tva3310a_20150101_KW');
  var $KX = $elt('tva3310a_20150101_KX');
  var $KY = $elt('tva3310a_20150101_KY');
  var $KZ = $elt('tva3310a_20150101_KZ');
  var $LA = $elt('tva3310a_20150101_LA');
  var $LB = $elt('tva3310a_20150101_LB');


  $readonly($KA, true);
  $readonly($KB, true);
  $readonly($KC, true);
  $readonly($KD, true);
  $readonly($KE, true);

  $value($CB, ($isServi($BB) && $float($BB) > 0) ? Math.round($float($BB) * 0.021) : '');
  $value($CF, ($isServi($BF) && $float($BF) > 0) ? Math.round($float($BF) * 0.021) : '');
  $value($CE, ($isServi($BE) && $float($BE) > 0) ? Math.round($float($BE) * 0.009) : '');
  $value($CS, ($isServi($BS) && $float($BS) > 0) ? Math.round($float($BS) * 0.100) : '');
  $value($CK, ($isServi($BK) && $float($BK) > 0) ? Math.round($float($BK) * 0.130) : '');
  $value($CP, ($isServi($BP) && $float($BP) > 0) ? Math.round($float($BP) * 0.0105) : '');
  $value($CQ, ($isServi($BQ) && $float($BQ) > 0) ? Math.round($float($BQ) * 0.0175) : '');


  var CNValue = 0;
  [$CA, $CB, $CC, $AF, $CE, $CF, $CS, $CK, $CM, $CP, $CQ, $CR].each(function(elt) {
    if ($float(elt) > 0) {
      CNValue += $float(elt);
    }
  });
  $value($CN, CNValue);


  var BNValue = 0;
  [$BA, $BB, $BC, $AE, $BE, $BF, $BS, $BK, $BM, $BP, $BQ, $BR].each(function(elt) {
    if ($float(elt) > 0) {
      BNValue += $float(elt);
    }
  });
  $value($BN, BNValue);

  var HBValue = 0;
  [$FA, $FB, $HE, $FE, $FF, $FG, $JD, $FJ, $JB, $JC, $JE, $JF,
   $HF, $FR, $KF, $FT, $KG, $FV, $HI, $KA, $KB,
   $KC, $KD, $KE, $KJ, $KL, $KS, $KN, $KP, $KQ,
   $KT, $KU, $JG, $JJ, $JK, $JL, $JM, $JN, $JP, $JH,
   $KW, $KX, $KY, $KZ, $LA, $LB].each(function(elt) {
                                        if ($float(elt) > 0) {
                                          HBValue += $float(elt);
                                        }
                                      });
  $value($HB, HBValue);


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

  $value($elt('tva3310ca3_20150101_FD'), $float($BN));
  $value($elt('tva3310ca3_20150101_GD'), $float($CN));
  $value($elt('tva3310ca3_20150101_KB'), $float($HB));
  try {
    //$elt('tva3310ca3_20150101_KB').onchange();
  }
  catch (error) {
    //console.log(error);
  }

};


asserts.functions.tva3310ter_20150101 = function($elt,
                                                 $assert,
                                                 $controls,
                                                 $isServi,
                                                 $float,
                                                 $value,
                                                 $readonly,
                                                 $isSiren,
                                                 $XOR,
                                                 $addition,
                                                 $soustraction) {


  var $AA = $elt('tva3310ter_20150101_AA');
  var $AB = $elt('tva3310ter_20150101_AB');
  var $AC = $elt('tva3310ter_20150101_AC');
  var $BA = $elt('tva3310ter_20150101_BA');
  var $BB = $elt('tva3310ter_20150101_BB');
  var $BC = $elt('tva3310ter_20150101_BC');
  var $BD = $elt('tva3310ter_20150101_BD');
  var $BE = $elt('tva3310ter_20150101_BE');
  var $BF = $elt('tva3310ter_20150101_BF');
  var $BG = $elt('tva3310ter_20150101_BG');
  var $BH = $elt('tva3310ter_20150101_BH');
  var $BJ = $elt('tva3310ter_20150101_BJ');
  var $BK = $elt('tva3310ter_20150101_BK');
  var $CA = $elt('tva3310ter_20150101_CA');
  var $CB = $elt('tva3310ter_20150101_CB');
  var $CC = $elt('tva3310ter_20150101_CC');
  var $CD = $elt('tva3310ter_20150101_CD');
  var $CE = $elt('tva3310ter_20150101_CE');
  var $CF = $elt('tva3310ter_20150101_CF');
  var $CG = $elt('tva3310ter_20150101_CG');
  var $CH = $elt('tva3310ter_20150101_CH');
  var $CJ = $elt('tva3310ter_20150101_CJ');
  var $CK = $elt('tva3310ter_20150101_CK');
  var $DA = $elt('tva3310ter_20150101_DA');
  var $DB = $elt('tva3310ter_20150101_DB');
  var $DC = $elt('tva3310ter_20150101_DC');
  var $DD = $elt('tva3310ter_20150101_DD');
  var $DE = $elt('tva3310ter_20150101_DE');
  var $DF = $elt('tva3310ter_20150101_DF');
  var $DG = $elt('tva3310ter_20150101_DG');
  var $DH = $elt('tva3310ter_20150101_DH');
  var $DJ = $elt('tva3310ter_20150101_DJ');
  var $DK = $elt('tva3310ter_20150101_DK');
  var $DL = $elt('tva3310ter_20150101_DL');
  var $EA = $elt('tva3310ter_20150101_EA');
  var $EB = $elt('tva3310ter_20150101_EB');
  var $EC = $elt('tva3310ter_20150101_EC');
  var $ED = $elt('tva3310ter_20150101_ED');
  var $EE = $elt('tva3310ter_20150101_EE');
  var $EF = $elt('tva3310ter_20150101_EF');
  var $EG = $elt('tva3310ter_20150101_EG');
  var $EH = $elt('tva3310ter_20150101_EH');
  var $EJ = $elt('tva3310ter_20150101_EJ');
  var $EK = $elt('tva3310ter_20150101_EK');
  var $EL = $elt('tva3310ter_20150101_EL');
  var $FA = $elt('tva3310ter_20150101_FA');
  var $FB = $elt('tva3310ter_20150101_FB');
  var $FC = $elt('tva3310ter_20150101_FC');
  var $FD = $elt('tva3310ter_20150101_FD');
  var $FE = $elt('tva3310ter_20150101_FE');
  var $FF = $elt('tva3310ter_20150101_FF');
  var $FG = $elt('tva3310ter_20150101_FG');
  var $FH = $elt('tva3310ter_20150101_FH');
  var $FJ = $elt('tva3310ter_20150101_FJ');
  var $FK = $elt('tva3310ter_20150101_FK');
  var $FL = $elt('tva3310ter_20150101_FL');
  var $GA = $elt('tva3310ter_20150101_GA');
  var $GB = $elt('tva3310ter_20150101_GB');
  var $GC = $elt('tva3310ter_20150101_GC');
  var $GD = $elt('tva3310ter_20150101_GD');
  var $GE = $elt('tva3310ter_20150101_GE');
  var $GF = $elt('tva3310ter_20150101_GF');
  var $GG = $elt('tva3310ter_20150101_GG');
  var $GH = $elt('tva3310ter_20150101_GH');
  var $GJ = $elt('tva3310ter_20150101_GJ');
  var $GK = $elt('tva3310ter_20150101_GK');
  var $GL = $elt('tva3310ter_20150101_GL');
  var $HA = $elt('tva3310ter_20150101_HA');
  var $HB = $elt('tva3310ter_20150101_HB');
  var $HC = $elt('tva3310ter_20150101_HC');
  var $HD = $elt('tva3310ter_20150101_HD');
  var $HE = $elt('tva3310ter_20150101_HE');
  var $HF = $elt('tva3310ter_20150101_HF');
  var $HG = $elt('tva3310ter_20150101_HG');
  var $HH = $elt('tva3310ter_20150101_HH');
  var $HJ = $elt('tva3310ter_20150101_HJ');
  var $HK = $elt('tva3310ter_20150101_HK');
  var $HL = $elt('tva3310ter_20150101_HL');
  var $JA = $elt('tva3310ter_20150101_JA');
  var $JB = $elt('tva3310ter_20150101_JB');
  var $JC = $elt('tva3310ter_20150101_JC');
  var $JD = $elt('tva3310ter_20150101_JD');
  var $JE = $elt('tva3310ter_20150101_JE');
  var $JF = $elt('tva3310ter_20150101_JF');
  var $JG = $elt('tva3310ter_20150101_JG');
  var $JH = $elt('tva3310ter_20150101_JH');
  var $JJ = $elt('tva3310ter_20150101_JJ');
  var $JK = $elt('tva3310ter_20150101_JK');
  var $JL = $elt('tva3310ter_20150101_JL');
  var $KA = $elt('tva3310ter_20150101_KA');
  var $KB = $elt('tva3310ter_20150101_KB');
  var $KC = $elt('tva3310ter_20150101_KC');
  var $KD = $elt('tva3310ter_20150101_KD');
  var $KE = $elt('tva3310ter_20150101_KE');
  var $KF = $elt('tva3310ter_20150101_KF');
  var $KG = $elt('tva3310ter_20150101_KG');
  var $KH = $elt('tva3310ter_20150101_KH');
  var $KJ = $elt('tva3310ter_20150101_KJ');
  var $KK = $elt('tva3310ter_20150101_KK');
  var $KL = $elt('tva3310ter_20150101_KL');
  var $LA = $elt('tva3310ter_20150101_LA');
  var $LB = $elt('tva3310ter_20150101_LB');
  var $LC = $elt('tva3310ter_20150101_LC');
  var $LD = $elt('tva3310ter_20150101_LD');
  var $LE = $elt('tva3310ter_20150101_LE');
  var $LF = $elt('tva3310ter_20150101_LF');
  var $LG = $elt('tva3310ter_20150101_LG');
  var $LH = $elt('tva3310ter_20150101_LH');
  var $LJ = $elt('tva3310ter_20150101_LJ');
  var $LK = $elt('tva3310ter_20150101_LK');
  var $LL = $elt('tva3310ter_20150101_LL');
  var $MA = $elt('tva3310ter_20150101_MA');
  var $MB = $elt('tva3310ter_20150101_MB');
  var $MC = $elt('tva3310ter_20150101_MC');
  var $MD = $elt('tva3310ter_20150101_MD');
  var $ME = $elt('tva3310ter_20150101_ME');
  var $MF = $elt('tva3310ter_20150101_MF');
  var $MG = $elt('tva3310ter_20150101_MG');
  var $MH = $elt('tva3310ter_20150101_MH');
  var $MJ = $elt('tva3310ter_20150101_MJ');
  var $MK = $elt('tva3310ter_20150101_MK');
  var $ML = $elt('tva3310ter_20150101_ML');
  var $NA = $elt('tva3310ter_20150101_NA');
  var $NB = $elt('tva3310ter_20150101_NB');
  var $NC = $elt('tva3310ter_20150101_NC');
  var $ND = $elt('tva3310ter_20150101_ND');
  var $NE = $elt('tva3310ter_20150101_NE');
  var $NF = $elt('tva3310ter_20150101_NF');
  var $NG = $elt('tva3310ter_20150101_NG');
  var $NH = $elt('tva3310ter_20150101_NH');
  var $NJ = $elt('tva3310ter_20150101_NJ');
  var $NK = $elt('tva3310ter_20150101_NK');
  var $NL = $elt('tva3310ter_20150101_NL');
  var $PA = $elt('tva3310ter_20150101_PA');
  var $PB = $elt('tva3310ter_20150101_PB');
  var $PC = $elt('tva3310ter_20150101_PC');
  var $PD = $elt('tva3310ter_20150101_PD');
  var $PE = $elt('tva3310ter_20150101_PE');
  var $PF = $elt('tva3310ter_20150101_PF');
  var $PG = $elt('tva3310ter_20150101_PG');
  var $PH = $elt('tva3310ter_20150101_PH');
  var $PJ = $elt('tva3310ter_20150101_PJ');
  var $PK = $elt('tva3310ter_20150101_PK');
  var $PL = $elt('tva3310ter_20150101_PL');
  var $QA = $elt('tva3310ter_20150101_QA');
  var $QB = $elt('tva3310ter_20150101_QB');
  var $QC = $elt('tva3310ter_20150101_QC');
  var $QD = $elt('tva3310ter_20150101_QD');
  var $QE = $elt('tva3310ter_20150101_QE');
  var $QF = $elt('tva3310ter_20150101_QF');
  var $QG = $elt('tva3310ter_20150101_QG');
  var $QH = $elt('tva3310ter_20150101_QH');
  var $QJ = $elt('tva3310ter_20150101_QJ');
  var $QK = $elt('tva3310ter_20150101_QK');
  var $QL = $elt('tva3310ter_20150101_QL');
  var $QM = $elt('tva3310ter_20150101_QM');
  var $RA = $elt('tva3310ter_20150101_RA');
  var $RB = $elt('tva3310ter_20150101_RB');
  var $RC = $elt('tva3310ter_20150101_RC');
  var $RD = $elt('tva3310ter_20150101_RD');
  var $RE = $elt('tva3310ter_20150101_RE');
  var $RF = $elt('tva3310ter_20150101_RF');
  var $RG = $elt('tva3310ter_20150101_RG');
  var $RH = $elt('tva3310ter_20150101_RH');
  var $RJ = $elt('tva3310ter_20150101_RJ');
  var $RK = $elt('tva3310ter_20150101_RK');
  var $RL = $elt('tva3310ter_20150101_RL');
  var $RM = $elt('tva3310ter_20150101_RM');


  // ENSEMBLE DES SECTEURS
  $addition($DL, $DA, $DB, $DC, $DD, $DE, $DF, $DG, $DH, $DJ, $DK);
  $addition($EL, $EA, $EB, $EC, $ED, $EE, $EF, $EG, $EH, $EJ, $EK);

  // TVA BRUTE : Total (col. 1 + 2)
  $addition($FA, $DA, $EA);
  $addition($FB, $DB, $EB);
  $addition($FC, $DC, $EC);
  $addition($FD, $DD, $ED);
  $addition($FE, $DE, $EE);
  $addition($FF, $DF, $EF);
  $addition($FG, $DG, $EG);
  $addition($FH, $DH, $EH);
  $addition($FJ, $DJ, $EJ);
  $addition($FK, $DK, $EK);
  $addition($FL, $DL, $EL);


  $addition($GL, $GA, $GB, $GC, $GD, $GE, $GF, $GG, $GH, $GJ, $GK);
  $addition($HL, $HA, $HB, $HC, $HD, $HE, $HF, $HG, $HH, $HJ, $HK);
  // Total (col 4 + 5)
  $addition($JA, $GA, $HA);
  $addition($JB, $GB, $HB);
  $addition($JC, $GC, $HC);
  $addition($JD, $GD, $HD);
  $addition($JE, $GE, $HE);
  $addition($JG, $GG, $HG);
  $addition($JH, $GH, $HH);
  $addition($JF, $GF, $HF);
  $addition($JJ, $GJ, $HJ);
  $addition($JK, $GK, $HK);
  $addition($JL, $GL, $HL);


  $addition($KL, $KA, $KB, $KC, $KD, $KE, $KF, $KG, $KH, $KJ, $KK);
  $addition($LL, $LA, $LB, $LC, $LD, $LE, $LF, $LG, $LH, $LJ, $LK);
  // Total (col 7 + 8)
  $addition($MA, $KA, $LA);
  $addition($MB, $KB, $LB);
  $addition($MC, $KC, $LC);
  $addition($MD, $KD, $LD);
  $addition($ME, $KE, $LE);
  $addition($MF, $KF, $LF);
  $addition($MG, $KG, $LG);
  $addition($MH, $KH, $LH);
  $addition($MJ, $KJ, $LJ);
  $addition($MK, $KK, $LK);
  $addition($ML, $KL, $LL);

  //[ligne 21 et/ou 22]
  $addition($NL, $NA, $NB, $NC, $ND, $NE, $NF, $NG, $NH, $NJ, $NK);


  $addition($PA, $JA, $MA, $NA);
  $addition($PB, $JB, $MB, $NB);
  $addition($PC, $JC, $MC, $NC);
  $addition($PD, $JD, $MD, $ND);
  $addition($PE, $JE, $ME, $NE);
  $addition($PF, $JF, $MF, $NF);
  $addition($PG, $JG, $MG, $NG);
  $addition($PH, $JH, $MH, $NH);
  $addition($PJ, $JJ, $MJ, $NJ);
  $addition($PK, $JK, $MK, $NK);
  $addition($PL, $PA, $PB, $PC, $PD, $PE, $PF, $PG, $PH, $PJ, $PK);


  $soustraction($QA, $FA, $PA);
  $soustraction($QB, $FB, $PB);
  $soustraction($QC, $FC, $PC);
  $soustraction($QD, $FD, $PD);
  $soustraction($QE, $FE, $PE);
  $soustraction($QF, $FF, $PF);
  $soustraction($QG, $FG, $PG);
  $soustraction($QH, $FH, $PH);
  $soustraction($QJ, $FJ, $PJ);
  $soustraction($QK, $FK, $PK);
  $addition($QL, $QA, $QB, $QC, $QD, $QE, $QF, $QG, $QH, $QJ, $QK);


  $soustraction($RA, $PA, $FA);
  $soustraction($RB, $PB, $FB);
  $soustraction($RC, $PC, $FC);
  $soustraction($RD, $PD, $FD);
  $soustraction($RE, $PE, $FE);
  $soustraction($RF, $PF, $FF);
  $soustraction($RG, $PG, $FG);
  $soustraction($RH, $PH, $FH);
  $soustraction($RJ, $PJ, $FJ);
  $soustraction($RK, $PK, $PK);
  $addition($RL, $RA, $RB, $RC, $RD, $RE, $RF, $RG, $RH, $RJ, $RK);


  $soustraction($QM, $QL, $RL);
  $soustraction($RM, $RL, $QL);

  $assert(!($isServi($AC)
          && !$isServi($AA)),
          'erreur_128', $AC, $AA);

  $assert($isServi($AB) && !(($isServi($QM) || $isServi($RM)) && !(0 < $float($AB) && $float($AB) <= 100) ),
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


};


asserts.functions.tva3310ca3g_20150101 = function($elt,
                                                  $assert,
                                                  $controls,
                                                  $isServi,
                                                  $float,
                                                  $value,
                                                  $readonly,
                                                  $isSiren,
                                                  $XOR,
                                                  $addition,
                                                  $soustraction) {


  var $BA = $elt('tva3310ca3g_20150101_BA');
  var $BB = $elt('tva3310ca3g_20150101_BB');
  var $BC = $elt('tva3310ca3g_20150101_BC');
  var $DA = $elt('tva3310ca3g_20150101_DA');
  var $DB = $elt('tva3310ca3g_20150101_DB');
  var $DC = $elt('tva3310ca3g_20150101_DC');
  var $EA = $elt('tva3310ca3g_20150101_EA');
  var $EB = $elt('tva3310ca3g_20150101_EB');
  var $EC = $elt('tva3310ca3g_20150101_EC');
  var $FA = $elt('tva3310ca3g_20150101_FA');
  var $FB = $elt('tva3310ca3g_20150101_FB');
  var $FE = $elt('tva3310ca3g_20150101_FE');
  var $GA = $elt('tva3310ca3g_20150101_GA');
  var $GB = $elt('tva3310ca3g_20150101_GB');
  var $GD = $elt('tva3310ca3g_20150101_GD');
  var $GE = $elt('tva3310ca3g_20150101_GE');
  var $GF = $elt('tva3310ca3g_20150101_GF');
  var $GH = $elt('tva3310ca3g_20150101_GH');
  var $GJ = $elt('tva3310ca3g_20150101_GJ');
  var $GK = $elt('tva3310ca3g_20150101_GK');
  var $GL = $elt('tva3310ca3g_20150101_GL');
  var $GM = $elt('tva3310ca3g_20150101_GM');
  var $GO = $elt('tva3310ca3g_20150101_GO');
  var $GP = $elt('tva3310ca3g_20150101_GP');
  var $GQ = $elt('tva3310ca3g_20150101_GQ');
  var $GR = $elt('tva3310ca3g_20150101_GR');
  var $GS = $elt('tva3310ca3g_20150101_GS');
  var $GT = $elt('tva3310ca3g_20150101_GT');
  var $GU = $elt('tva3310ca3g_20150101_GU');
  var $GV = $elt('tva3310ca3g_20150101_GV');
  var $GX = $elt('tva3310ca3g_20150101_GX');
  var $GZ = $elt('tva3310ca3g_20150101_GZ');
  var $HB = $elt('tva3310ca3g_20150101_HB');
  var $HC = $elt('tva3310ca3g_20150101_HC');
  var $HE = $elt('tva3310ca3g_20150101_HE');
  var $HF = $elt('tva3310ca3g_20150101_HF');
  var $HK = $elt('tva3310ca3g_20150101_HK');
  var $HL = $elt('tva3310ca3g_20150101_HL');
  var $HM = $elt('tva3310ca3g_20150101_HM');
  var $HN = $elt('tva3310ca3g_20150101_HN');
  var $HO = $elt('tva3310ca3g_20150101_HO');
  var $HP = $elt('tva3310ca3g_20150101_HP');
  var $HQ = $elt('tva3310ca3g_20150101_HQ');
  var $HR = $elt('tva3310ca3g_20150101_HR');
  var $HS = $elt('tva3310ca3g_20150101_HS');
  var $HT = $elt('tva3310ca3g_20150101_HT');
  var $HU = $elt('tva3310ca3g_20150101_HU');
  var $KH = $elt('tva3310ca3g_20150101_KH');
  var $KJ = $elt('tva3310ca3g_20150101_KJ');
  var $KK = $elt('tva3310ca3g_20150101_KK');
  var $KL = $elt('tva3310ca3g_20150101_KL');
  var $KM = $elt('tva3310ca3g_20150101_KM');
  var $KN = $elt('tva3310ca3g_20150101_KN');
  var $KR = $elt('tva3310ca3g_20150101_KR');
  var $LA = $elt('tva3310ca3g_20150101_LA');
  var $LB = $elt('tva3310ca3g_20150101_LB');
  var $LC = $elt('tva3310ca3g_20150101_LC');
  var $LD = $elt('tva3310ca3g_20150101_LD');
  var $LF = $elt('tva3310ca3g_20150101_LF');
  var $LG = $elt('tva3310ca3g_20150101_LG');

  $readonly($DC, true);
  $readonly($EA, true);
  $readonly($EC, true);
  $readonly($FA, true);
  $readonly($FE, true);
  $readonly($HK, true);
  $readonly($FB, true);

  $addition($DC, $DA, $DB);
  $soustraction($EA, $DC, $KR);
  $soustraction($EC, $EA, $EB);
  $soustraction($FA, $KR, $DC);
  $addition($FE, $FA, $FB);
  $addition($HK, $GA, $GB, $GD, $GE, $GF,
            $GH, $GJ, $GK, $GL, $GM,
            $GO, $GP, $GQ, $GR, $GS,
            $GT, $GU, $GV, $GX,
            $GZ,
            $HB, $HC, $HE,
            $HF, $HL, $HM, $HN, $HO, $HP,
            $HQ, $HR, $HS, $HT, $HU, $LG,
            $KH, $KJ, $KK, $KL, $KM, $KN,
            $LA, $LB, $LC, $LD, $LF);
  $value($FB, $value($HK));

  NTD.Identif.t("hidePaiement", []);
  if ($isServi($FE) && $float($FE) > 0) {
    NTD.Identif.t("showPaiement", [$float($FE)]);
  }

  $assert(!($isServi($BC) && !$isServi($BA)),
          'erreur_128', $BA, $BC);

  $assert(!$isServi($HT), 'erreur_218', $HT);
  $assert(!($isServi($EB) && $isServi($EA) && !($float($EB) <= $float($EA))),
          'erreur_131', $EA, $EB);

  $assert(($isServi($KR) && $float($KR) > 0) || ($isServi($DC) && $float($DC) > 0) || ($isServi($HK) && $float($HK) > 0),
          'erreur_212', $KR, $DC, $HK);

};

asserts.functions.tva3517sca12_20150101 = function($elt,
                                                   $assert,
                                                   $controls,
                                                   $isServi,
                                                   $float,
                                                   $value,
                                                   $readonly,
                                                   $isSiren,
                                                   $XOR,
                                                   $addition,
                                                   $soustraction,
                                                   $percent) {


  var $CA = $elt('tva3517sca12_20150101_CA');
  var $DA = $elt('tva3517sca12_20150101_DA');
  var $DB = $elt('tva3517sca12_20150101_DB');
  var $DC = $elt('tva3517sca12_20150101_DC');
  var $EA = $elt('tva3517sca12_20150101_EA');
  var $EB = $elt('tva3517sca12_20150101_EB');
  var $EC = $elt('tva3517sca12_20150101_EC');
  var $ED = $elt('tva3517sca12_20150101_ED');
  var $EF = $elt('tva3517sca12_20150101_EF');
  var $EG = $elt('tva3517sca12_20150101_EG');
  var $EH = $elt('tva3517sca12_20150101_EH');
  var $EJ = $elt('tva3517sca12_20150101_EJ');
  var $EL = $elt('tva3517sca12_20150101_EL');
  var $EM = $elt('tva3517sca12_20150101_EM');
  var $EN = $elt('tva3517sca12_20150101_EN');
  var $EP = $elt('tva3517sca12_20150101_EP');
  var $EQ = $elt('tva3517sca12_20150101_EQ');
  var $EU = $elt('tva3517sca12_20150101_EU');
  var $EV = $elt('tva3517sca12_20150101_EV');
  var $EW = $elt('tva3517sca12_20150101_EW');
  var $EX = $elt('tva3517sca12_20150101_EX');
  var $EY = $elt('tva3517sca12_20150101_EY');
  var $EZ = $elt('tva3517sca12_20150101_EZ');
  var $FA = $elt('tva3517sca12_20150101_FA');
  var $FB = $elt('tva3517sca12_20150101_FB');
  var $FC = $elt('tva3517sca12_20150101_FC');
  var $FD = $elt('tva3517sca12_20150101_FD');
  var $FE = $elt('tva3517sca12_20150101_FE');
  var $FF = $elt('tva3517sca12_20150101_FF');
  var $FG = $elt('tva3517sca12_20150101_FG');
  var $FJ = $elt('tva3517sca12_20150101_FJ');
  var $FL = $elt('tva3517sca12_20150101_FL');
  var $FM = $elt('tva3517sca12_20150101_FM');
  var $FN = $elt('tva3517sca12_20150101_FN');
  var $FP = $elt('tva3517sca12_20150101_FP');
  var $FR = $elt('tva3517sca12_20150101_FR');
  var $FU = $elt('tva3517sca12_20150101_FU');
  var $FV = $elt('tva3517sca12_20150101_FV');
  var $FW = $elt('tva3517sca12_20150101_FW');
  var $FY = $elt('tva3517sca12_20150101_FY');
  var $GA = $elt('tva3517sca12_20150101_GA');
  var $GB = $elt('tva3517sca12_20150101_GB');
  var $GC = $elt('tva3517sca12_20150101_GC');
  var $GF = $elt('tva3517sca12_20150101_GF');
  var $GH = $elt('tva3517sca12_20150101_GH');
  var $HA = $elt('tva3517sca12_20150101_HA');
  var $HB = $elt('tva3517sca12_20150101_HB');
  var $HC = $elt('tva3517sca12_20150101_HC');
  var $JA = $elt('tva3517sca12_20150101_JA');
  var $JB = $elt('tva3517sca12_20150101_JB');
  var $KA = $elt('tva3517sca12_20150101_KA');
  var $KB = $elt('tva3517sca12_20150101_KB');
  var $KD = $elt('tva3517sca12_20150101_KD');
  var $KE = $elt('tva3517sca12_20150101_KE');
  var $KF = $elt('tva3517sca12_20150101_KF');
  var $KG = $elt('tva3517sca12_20150101_KG');
  var $KH = $elt('tva3517sca12_20150101_KH');
  var $KJ = $elt('tva3517sca12_20150101_KJ');
  var $KL = $elt('tva3517sca12_20150101_KL');
  var $KM = $elt('tva3517sca12_20150101_KM');
  var $LA = $elt('tva3517sca12_20150101_LA');
  var $LB = $elt('tva3517sca12_20150101_LB');
  var $MA = $elt('tva3517sca12_20150101_MA');
  var $MD = $elt('tva3517sca12_20150101_MD');
  var $ME = $elt('tva3517sca12_20150101_ME');
  var $MF = $elt('tva3517sca12_20150101_MF');
  var $MG = $elt('tva3517sca12_20150101_MG');
  var $MH = $elt('tva3517sca12_20150101_MH');
  var $MJ = $elt('tva3517sca12_20150101_MJ');
  var $MK = $elt('tva3517sca12_20150101_MK');
  var $ML = $elt('tva3517sca12_20150101_ML');
  var $MM = $elt('tva3517sca12_20150101_MM');
  var $MN = $elt('tva3517sca12_20150101_MN');
  var $NA = $elt('tva3517sca12_20150101_NA');
  var $NB = $elt('tva3517sca12_20150101_NB');
  var $NC = $elt('tva3517sca12_20150101_NC');
  var $QA = $elt('tva3517sca12_20150101_QA');
  var $QD = $elt('tva3517sca12_20150101_QD');
  var $QE = $elt('tva3517sca12_20150101_QE');
  var $QF = $elt('tva3517sca12_20150101_QF');
  var $QH = $elt('tva3517sca12_20150101_QH');
  var $QJ = $elt('tva3517sca12_20150101_QJ');
  var $QS = $elt('tva3517sca12_20150101_QS');
  var $RA = $elt('tva3517sca12_20150101_RA');
  var $RB = $elt('tva3517sca12_20150101_RB');
  var $RC = $elt('tva3517sca12_20150101_RC');
  var $RE = $elt('tva3517sca12_20150101_RE');
  var $RF = $elt('tva3517sca12_20150101_RF');
  var $RG = $elt('tva3517sca12_20150101_RG');
  var $RH = $elt('tva3517sca12_20150101_RH');
  var $RK = $elt('tva3517sca12_20150101_RK');
  var $RL = $elt('tva3517sca12_20150101_RL');
  var $RM = $elt('tva3517sca12_20150101_RM');
  var $RN = $elt('tva3517sca12_20150101_RN');
  var $SA = $elt('tva3517sca12_20150101_SA');
  var $SB = $elt('tva3517sca12_20150101_SB');
  var $SC = $elt('tva3517sca12_20150101_SC');
  var $SD = $elt('tva3517sca12_20150101_SD');
  var $TA = $elt('tva3517sca12_20150101_TA');
  var $TB = $elt('tva3517sca12_20150101_TB');
  var $TC = $elt('tva3517sca12_20150101_TC');
  var $TD = $elt('tva3517sca12_20150101_TD');
  var $UA = $elt('tva3517sca12_20150101_UA');
  var $UB = $elt('tva3517sca12_20150101_UB');
  var $UC = $elt('tva3517sca12_20150101_UC');
  var $UD = $elt('tva3517sca12_20150101_UD');
  var $VA = $elt('tva3517sca12_20150101_VA');
  var $VC = $elt('tva3517sca12_20150101_VC');
  var $VE = $elt('tva3517sca12_20150101_VE');
  var $VF = $elt('tva3517sca12_20150101_VF');
  var $VJ = $elt('tva3517sca12_20150101_VJ');
  var $VK = $elt('tva3517sca12_20150101_VK');
  var $VL = $elt('tva3517sca12_20150101_VL');
  var $VM = $elt('tva3517sca12_20150101_VM');
  var $VN = $elt('tva3517sca12_20150101_VN');
  var $VP = $elt('tva3517sca12_20150101_VP');
  var $VQ = $elt('tva3517sca12_20150101_VQ');
  var $VS = $elt('tva3517sca12_20150101_VS');
  var $VT = $elt('tva3517sca12_20150101_VT');
  var $VV = $elt('tva3517sca12_20150101_VV');
  var $VW = $elt('tva3517sca12_20150101_VW');
  var $VX = $elt('tva3517sca12_20150101_VX');
  var $VY = $elt('tva3517sca12_20150101_VY');
  var $VZ = $elt('tva3517sca12_20150101_VZ');
  var $WA = $elt('tva3517sca12_20150101_WA');


  var $requiredFields = [
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
    $VQ, $VS, $VT, $VV, $VW, $VX, $VY, $VZ, $WA];
  var $emptiableFields = [
    $DA, $DB, $DC, $EA, $EB, $EC, $ED, $EF,
    $EG, $EH, $EJ, $EL, $EM, $EN, $EP, $EQ, $EU, $EV, $EW,
    $EX, $EY, $EZ, $FA, $FB, $FC, $FD, $FE, $FF, $FG, $FJ,
    $FL, $FM, $FN, $FP, $FR, $FU, $FV, $FW, $FY, $GA, $GB,
    $GC, $GF, $GH, $HA, $HB, $HC, $JA, $JB, $KA, $KB, $KD,
    $KL, $KM, $LA, $LB, $MA,
    $MD, $ME, $MF, $MG, $MH, $MJ, $MK, $ML, $MM, $MN, $NA,
    $NB, $NC, $QA, $QD, $QE, $QF, $QH, $QJ, $QS,
    $RA, $RB, $RC, $RE, $RF, $RG, $RH, $RK, $RL, $RM, $RN,
    $SA, $SB, $SC, $TA, $TB, $TC, $TD, $UA, $UB, $UC, $UD,
    $VA, $VC, $VE, $VF, $VJ, $VL, $VM, $VN, $VP,
    $VQ, $VS, $VT, $VV, $VW, $VX, $VY, $VZ, $WA];
  if ($isServi($SD)) {
    for (var i = 0; i < $emptiableFields.length; i++) {
      $readonly($emptiableFields[i], true);
      $value($emptiableFields[i], '');
    }
  }
  else {
    for (var i = 0; i < $emptiableFields.length; i++) {
      $readonly($emptiableFields[i], false);
    }
  }

  $readonly($FW, true);
  $readonly($GH, true);
  $readonly($FF, true);
  $readonly($FU, true);
  $readonly($FV, true);

  $readonly($FR, true);
  $readonly($SB, true);
  $readonly($HC, true);
  $readonly($VA, true);
  $readonly($GC, true);
  $readonly($KD, true);
  $readonly($MM, true);
  $readonly($MN, true);
  $readonly($MA, true);

  $readonly($LA, true);
  $readonly($LB, true);
  $readonly($NA, true);
  $readonly($NB, true);
  $readonly($NC, true);
  $readonly($SA, true);
  $readonly($SC, true);
  $readonly($RA, true);

  $readonly($KE, true);
  $readonly($KF, true);
  $readonly($KG, true);
  $readonly($KH, true);
  $readonly($KJ, true);

  $percent($FW, $EW, 20);
  $percent($GH, $GF, 10);
  $percent($FF, $EF, 5.5);
  $percent($FU, $EU, 8.5);
  $percent($FV, $EV, 2.1);
  $addition($FR, $FF, $FB, $FU, $FV, $FD, $FJ, $FG, $FY, $VP, $EZ, $FL, $FM, $FN, $FP, $FW, $GH);
  $addition($SB,
            $QA, $QS, $QD, $QE, $QF, $QH, $QJ,
            $VC, $VQ, $VJ, $VE, $VF, $KL, $KM,
            $DA, $DB, $DC,
            $RM, $RH, $RK, $RL, $RN, $RF, $RG,
            $VV, $VW, $VX, $VY, $VZ, $WA);
  $addition($HC, $HA, $HB);
  $soustraction($VA, $FR, $FL, $FM, $EQ, $HC);
  $addition($GC, $FR, $GA, $GB, $VS);
  $addition($KD, $HC, $JA, $KA, $KB, $VT);
  $addition($MM, $MD, $MF, $MH, $MK);
  if (!$isServi($MM)) {
    $value($MM, 0);
  }
  $addition($MN, $ME, $MG, $MJ, $ML);
  if (!$isServi($MN)) {
    $value($MN, 0);
  }
  $addition($MA, $MM, $MN);
  $soustraction($LA, $GC, $KD);
  $soustraction($LB, $KD, $GC);
  $soustraction($NA, $LA, $LB, $MA);
  $soustraction($NB, $MA, $LA);
  if ($isServi($NB) && $float($NB) >= 0) {
    $addition($NC, $LB, $NB);
  }
  else {
    $addition($NC, $LB, $MA);
  }
  $value($SA, $value($NA));
  $addition($SC, $SA, $SB);
  $value($RA, $value($NC));


  NTD.Identif.t("hidePaiement", []);
  if ($isServi($SC) && $float($SC) > 0) {
    NTD.Identif.t("showPaiement", [$float($SC)]);
  }

  // --- asserts
  $assert(!($isServi($VK) && !$isServi($CA)), 'erreur_128', $CA, $VK);

  $controls.erreur_111($EJ, $FJ);
  $controls.erreur_112($FJ, $EJ);
  $controls.erreur_111($EW, $FW);
  $controls.erreur_112($FW, $EW);
  $controls.erreur_111($GF, $GH);
  $controls.erreur_112($GH, $GF);
  $controls.erreur_111($EH, $EZ);
  $controls.erreur_112($EZ, $EH);
  $controls.erreur_111($EG, $FG);
  $controls.erreur_117($EG, $FG, 0.021, 0.206);
  $controls.erreur_112($FG, $EG);
  $controls.erreur_111($EY, $FY);
  $controls.erreur_112($FY, $EY);
  $controls.erreur_111($VN, $VP);
  $controls.erreur_112($VP, $VN);
  $controls.erreur_111($EH, $EZ);
  $controls.erreur_112($EZ, $EH);
  $controls.erreur_111($EL, $FL);
  $controls.erreur_112($FL, $EL);
  $controls.erreur_111($EM, $FM);
  $controls.erreur_112($FM, $EM);
  $controls.erreur_111($EN, $FN);
  $controls.erreur_112($FN, $EN);
  $controls.erreur_111($EP, $FP);
  $controls.erreur_112($FP, $EP);
  $controls.erreur_117($EP, $FP, 0.021, 0.20);


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

  var $casesAccomptesRemplies = 0;
  $casesAccomptesRemplies += ($isServi($MD) || $isServi($ME)) ? 1 : 0;
  $casesAccomptesRemplies += ($isServi($MF) || $isServi($MG)) ? 1 : 0;
  $casesAccomptesRemplies += ($isServi($MH) || $isServi($MJ)) ? 1 : 0;
  $casesAccomptesRemplies += ($isServi($MK) || $isServi($ML)) ? 1 : 0;
  var $casesCoches = 0;
  $casesCoches += $isServi($TA) ? 1 : 0;
  $casesCoches += $isServi($TB) ? 1 : 0;
  $casesCoches += $isServi($TC) ? 1 : 0;
  $casesCoches += $isServi($TD) ? 1 : 0;
  $assert(!($isServi($MA) && $float($MA) > 0 && !($casesAccomptesRemplies == $casesCoches)),
          'erreur_124', $MA, $MD, $ME, $MF, $MG, $MH, $MJ, $MK, $ML);

  $controls.erreur_129($TA, $UA);
  $controls.erreur_129($TB, $UB);
  $controls.erreur_129($TC, $UC);
  $controls.erreur_129($TD, $UD);

  $controls.erreur_134($UA, $elt(NTD.Identif.tField('CA')), $elt(NTD.Identif.tField('CB')));
  $controls.erreur_134($UB, $elt(NTD.Identif.tField('CA')), $elt(NTD.Identif.tField('CB')));
  $controls.erreur_134($UC, $elt(NTD.Identif.tField('CA')), $elt(NTD.Identif.tField('CB')));
  $controls.erreur_134($UD, $elt(NTD.Identif.tField('CA')), $elt(NTD.Identif.tField('CB')));


  $controls.erreur_042($SD, $requiredFields);
  $controls.erreur_049($SD, $requiredFields);


};


asserts.functions.tva3517bisca12_20150101 = function($elt,
                                                     $assert,
                                                     $controls,
                                                     $isServi,
                                                     $float,
                                                     $value,
                                                     $readonly,
                                                     $isSiren,
                                                     $XOR,
                                                     $addition,
                                                     $soustraction,
                                                     $percent) {


  var $AE = $elt('tva3517bisca12_20150101_AE');
  var $AF = $elt('tva3517bisca12_20150101_AF');
  var $AG = $elt('tva3517bisca12_20150101_AG');
  var $BA = $elt('tva3517bisca12_20150101_BA');
  var $DA = $elt('tva3517bisca12_20150101_DA');
  var $DB = $elt('tva3517bisca12_20150101_DB');
  var $DC = $elt('tva3517bisca12_20150101_DC');
  var $DD = $elt('tva3517bisca12_20150101_DD');
  var $DE = $elt('tva3517bisca12_20150101_DE');
  var $DH = $elt('tva3517bisca12_20150101_DH');
  var $DJ = $elt('tva3517bisca12_20150101_DJ');
  var $DK = $elt('tva3517bisca12_20150101_DK');
  var $DL = $elt('tva3517bisca12_20150101_DL');
  var $DM = $elt('tva3517bisca12_20150101_DM');
  var $DN = $elt('tva3517bisca12_20150101_DN');
  var $DP = $elt('tva3517bisca12_20150101_DP');
  var $DQ = $elt('tva3517bisca12_20150101_DQ');
  var $DR = $elt('tva3517bisca12_20150101_DR');
  var $DS = $elt('tva3517bisca12_20150101_DS');
  var $DU = $elt('tva3517bisca12_20150101_DU');
  var $DV = $elt('tva3517bisca12_20150101_DV');
  var $DY = $elt('tva3517bisca12_20150101_DY');
  var $DZ = $elt('tva3517bisca12_20150101_DZ');
  var $EA = $elt('tva3517bisca12_20150101_EA');
  var $EB = $elt('tva3517bisca12_20150101_EB');
  var $EC = $elt('tva3517bisca12_20150101_EC');
  var $ED = $elt('tva3517bisca12_20150101_ED');
  var $EE = $elt('tva3517bisca12_20150101_EE');
  var $EH = $elt('tva3517bisca12_20150101_EH');
  var $EJ = $elt('tva3517bisca12_20150101_EJ');
  var $EK = $elt('tva3517bisca12_20150101_EK');
  var $EL = $elt('tva3517bisca12_20150101_EL');
  var $EM = $elt('tva3517bisca12_20150101_EM');
  var $EN = $elt('tva3517bisca12_20150101_EN');
  var $EP = $elt('tva3517bisca12_20150101_EP');
  var $EQ = $elt('tva3517bisca12_20150101_EQ');
  var $ER = $elt('tva3517bisca12_20150101_ER');
  var $ES = $elt('tva3517bisca12_20150101_ES');
  var $EU = $elt('tva3517bisca12_20150101_EU');
  var $EV = $elt('tva3517bisca12_20150101_EV');
  var $EZ = $elt('tva3517bisca12_20150101_EZ');
  var $FA = $elt('tva3517bisca12_20150101_FA');
  var $FB = $elt('tva3517bisca12_20150101_FB');
  var $FC = $elt('tva3517bisca12_20150101_FC');
  var $FD = $elt('tva3517bisca12_20150101_FD');
  var $FF = $elt('tva3517bisca12_20150101_FF');
  var $FG = $elt('tva3517bisca12_20150101_FG');
  var $GA = $elt('tva3517bisca12_20150101_GA');
  var $GB = $elt('tva3517bisca12_20150101_GB');
  var $HA = $elt('tva3517bisca12_20150101_HA');
  var $JA = $elt('tva3517bisca12_20150101_JA');
  var $JB = $elt('tva3517bisca12_20150101_JB');
  var $JC = $elt('tva3517bisca12_20150101_JC');
  var $KA = $elt('tva3517bisca12_20150101_KA');
  var $KB = $elt('tva3517bisca12_20150101_KB');
  var $KC = $elt('tva3517bisca12_20150101_KC');
  var $KD = $elt('tva3517bisca12_20150101_KD');
  var $KF = $elt('tva3517bisca12_20150101_KF');
  var $KH = $elt('tva3517bisca12_20150101_KH');
  var $LC = $elt('tva3517bisca12_20150101_LC');
  var $LD = $elt('tva3517bisca12_20150101_LD');
  var $LF = $elt('tva3517bisca12_20150101_LF');
  var $LH = $elt('tva3517bisca12_20150101_LH');
  var $LK = $elt('tva3517bisca12_20150101_LK');
  var $LM = $elt('tva3517bisca12_20150101_LM');
  var $MA = $elt('tva3517bisca12_20150101_MA');
  var $MB = $elt('tva3517bisca12_20150101_MB');
  var $MC = $elt('tva3517bisca12_20150101_MC');
  var $NA = $elt('tva3517bisca12_20150101_NA');
  var $NB = $elt('tva3517bisca12_20150101_NB');
  var $NC = $elt('tva3517bisca12_20150101_NC');
  var $ND = $elt('tva3517bisca12_20150101_ND');
  var $RC = $elt('tva3517bisca12_20150101_RC');
  var $RD = $elt('tva3517bisca12_20150101_RD');

  var $RF = $elt('tva3517bisca12_20150101_RF');
  var $RG = $elt('tva3517bisca12_20150101_RG');
  var $RH = $elt('tva3517bisca12_20150101_RH');
  var $RJ = $elt('tva3517bisca12_20150101_RJ');
  var $RK = $elt('tva3517bisca12_20150101_RK');
  var $RL = $elt('tva3517bisca12_20150101_RL');


  $readonly($KA, true);
  $readonly($KB, true);
  $readonly($KC, true);
  $readonly($KD, true);
  $readonly($KF, true);

  $readonly($JA, true);
  $readonly($JB, true);
  $readonly($JC, true);

  $readonly($EU, true);
  $readonly($EE, true);
  $readonly($EK, true);
  $readonly($EQ, true);
  $readonly($EV, true);

  $readonly($FF, true);
  $readonly($NC, true);
  $readonly($EA, true);
  $readonly($EB, true);
  $readonly($EC, true);
  $readonly($ED, true);

  $percent($EU, $DU, 2.1);
  $percent($EE, $DE, 5.5);
  $percent($EK, $DK, 20);
  $percent($EQ, $DQ, 10);
  $percent($EV, $DV, 8.5);
  $addition($ES, $EE, $EK, $EQ, $EB, $EU, $EV, $ED, $EH, $EJ, $EZ, $DS, $EL, $EM, $EN, $EP, $ER, $RC);
  $addition($FF, $FA, $FB, $FC, $FD, $RD);
  $soustraction($GA, $ES, $FF);
  $soustraction($GB, $FF, $ES);
  $soustraction($JA, $GA, $GB, $HA);
  $soustraction($JB, $HA, $GA);
  if ($float($JA) > 0) {
    $value($JC, 0);
  }
  else if ($float($JB) > 0) {
    $addition($JC, $GB, $JB);
  }
  else {
    $addition($JC, $GB, $HA);
  }
  $addition($NB, $LF, $LC, $LD, $LK, $LH, $LM, $RF, $RG, $RH, $RJ, $RK, $RL);
  $value($NA, $value($JA));
  $addition($NC, $NA, $NB);
  $value($MA, $value($JC));
  $soustraction($MC, $MA, $MB);
  NTD.Identif.t("hidePaiement", []);
  if ($isServi($NC) && $float($NC) > 0) {
    NTD.Identif.t("showPaiement", [$float($NC)]);
  }


  // --- assert
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
  $assert($isServi($elt('tva3517bisca12_20150101[AE]-0-0')) || $isServi($elt('tva3517bisca12_20150101[AE]-0-1')),
          'Champ Obligatoire',
          $elt('tva3517bisca12_20150101[AE]-0-0'), $elt('tva3517bisca12_20150101[AE]-0-1'));
};

asserts.functions.is2571_2015 = function($elt,
                                         $assert,
                                         $controls,
                                         $isServi,
                                         $float,
                                         $value,
                                         $readonly,
                                         $isSiren,
                                         $XOR,
                                         $addition,
                                         $soustraction,
                                         $percent) {

  var $FA = $elt('is2571_2015_FA');
  var $CA = $elt('is2571_2015_CA');
  var $DA = $elt('is2571_2015_DA');
  var $FB = $elt('is2571_2015_FB');
  var $FC = $elt('is2571_2015_FC');
  var $FD = $elt('is2571_2015_FD');
  var $FE = $elt('is2571_2015_FE');
  var $FF = $elt('is2571_2015_FF');
  var $FG = $elt('is2571_2015_FG');
  var $CF = $elt('is2571_2015_CF');
  var $CC = $elt('is2571_2015_CC');
  var $CD = $elt('is2571_2015_CD');
  var $DB = $elt('is2571_2015_DB');
  var $CE = $elt('is2571_2015_CE');
  var $CG = $elt('is2571_2015_CG');
  var $CH = $elt('is2571_2015_CH');
  var $FH = $elt('is2571_2015_FH');
  var $FK = $elt('is2571_2015_FK');
  var $FM = $elt('is2571_2015_FM');
  var $FN = $elt('is2571_2015_FN');

  $readonly($CE, true);
  $addition($CE, $CA, $CC, $CD, $CF);
  $readonly($CH, true);
  $addition($CH, $CE, $CG);
  $readonly($FA, true);
  $addition($FA, $FB, $FC, $FD, $FE, $FF, $FG);
  $readonly($FN, true);
  $soustraction($FN, $CH, $FH);

  NTD.Identif.p("hidePaiement", []);
  if ($isServi($CE) && $float($CE) > 0) {
    NTD.Identif.p("showPaiement", [$float($CE)]);
  }

  $assert(!($isServi($FH) && !($isServi($FK) && $isServi($FM))), 'erreur_310', $FH);
  $assert(!($isServi($FH) && $isServi($CH) && !($float($FH) <= $float($CH))), 'erreur_311', $FH);
  $assert(!($isServi($FK) && !($isServi($FH) && $isServi($FM))), 'erreur_310', $FK);
  $assert(!($isServi($FM) && !($isServi($FH) && $isServi($FK))), 'erreur_310', $FM);

  var $PidentifKF = $elt(NTD.Identif.pField('KF'));
  var $date_FM = $value($FM).split('/');
  $date_FM = new Date($date_FM[2], $date_FM[1] - 1, $date_FM[0]);
  var $date_KF = $value($PidentifKF).split('/');
  $date_KF = new Date($date_KF[1], $date_KF[0] - 1, '01');
  var $date_KF_inf_dateFM = $date_FM.getTime() < $date_KF.getTime();

  $assert(!($isServi($FM) && $isServi($PidentifKF) && !($date_KF_inf_dateFM)), 'erreur_312', $FM);

};


asserts.functions.is2572_2015 = function($elt,
                                         $assert,
                                         $controls,
                                         $isServi,
                                         $float,
                                         $value,
                                         $readonly,
                                         $isSiren,
                                         $XOR,
                                         $addition,
                                         $soustraction,
                                         $percent) {

  var $PN = $elt('is2572_2015_PN');
  var $PQ = $elt('is2572_2015_PQ');
  var $PR = $elt('is2572_2015_PR');
  var $PS = $elt('is2572_2015_PS');
  var $PT = $elt('is2572_2015_PT');
  var $PU = $elt('is2572_2015_PU');
  var $PV = $elt('is2572_2015_PV');
  var $PW = $elt('is2572_2015_PW');
  var $AD = $elt('is2572_2015_AD');
  var $BD = $elt('is2572_2015_BD');
  var $CA = $elt('is2572_2015_CA');
  var $DA = $elt('is2572_2015_DA');
  var $EA = $elt('is2572_2015_EA');
  var $EB = $elt('is2572_2015_EB');
  var $TA = $elt('is2572_2015_TA');
  var $TB = $elt('is2572_2015_TB');
  var $GC = $elt('is2572_2015_GC');
  var $GD = $elt('is2572_2015_GD');
  var $GE = $elt('is2572_2015_GE');
  var $PM = $elt('is2572_2015_PM');
  var $IA = $elt('is2572_2015_IA');
  var $JA = $elt('is2572_2015_JA');
  var $MA = $elt('is2572_2015_MA');
  var $ME = $elt('is2572_2015_ME');
  var $MB = $elt('is2572_2015_MB');
  var $MC = $elt('is2572_2015_MC');
  var $MD = $elt('is2572_2015_MD');
  var $KA = $elt('is2572_2015_KA');
  var $NA = $elt('is2572_2015_NA');
  var $KB = $elt('is2572_2015_KB');
  var $NB = $elt('is2572_2015_NB');
  var $KC = $elt('is2572_2015_KC');
  var $NC = $elt('is2572_2015_NC');
  var $ND = $elt('is2572_2015_ND');
  var $NE = $elt('is2572_2015_NE');
  var $NF = $elt('is2572_2015_NF');
  var $NG = $elt('is2572_2015_NG');
  var $NJ = $elt('is2572_2015_NJ');
  var $NK = $elt('is2572_2015_NK');
  var $NL = $elt('is2572_2015_NL');
  var $NM = $elt('is2572_2015_NM');
  var $NN = $elt('is2572_2015_NN');
  var $OD = $elt('is2572_2015_OD');
  var $NO = $elt('is2572_2015_NO');
  var $RD = $elt('is2572_2015_RD');
  var $RE = $elt('is2572_2015_RE');
  var $RF = $elt('is2572_2015_RF');
  var $LA = $elt('is2572_2015_LA');
  var $LF = $elt('is2572_2015_LF');
  var $LE = $elt('is2572_2015_LE');
  var $OB = $elt('is2572_2015_OB');
  var $LB = $elt('is2572_2015_LB');
  var $LC = $elt('is2572_2015_LC');
  var $LD = $elt('is2572_2015_LD');
  var $OC = $elt('is2572_2015_OC');
  var $RA = $elt('is2572_2015_RA');
  var $RB = $elt('is2572_2015_RB');
  var $RC = $elt('is2572_2015_RC');
  var $RG = $elt('is2572_2015_RG');
  var $RH = $elt('is2572_2015_RH');
  var $RJ = $elt('is2572_2015_RJ');
  var $RK = $elt('is2572_2015_RK');
  var $RL = $elt('is2572_2015_RL');
  var $RM = $elt('is2572_2015_RM');
  var $RN = $elt('is2572_2015_RN');
  var $RR = $elt('is2572_2015_RR');
  var $RP = $elt('is2572_2015_RP');
  var $RS = $elt('is2572_2015_RS');
  var $RT = $elt('is2572_2015_RT');
  var $RU = $elt('is2572_2015_RU');
  var $RV = $elt('is2572_2015_RV');
  var $RX = $elt('is2572_2015_RX');
  var $RY = $elt('is2572_2015_RY');
  var $RW = $elt('is2572_2015_RW');
  var $RZ = $elt('is2572_2015_RZ');
  var $PA = $elt('is2572_2015_PA');
  var $PB = $elt('is2572_2015_PB');
  var $PC = $elt('is2572_2015_PC');
  var $PD = $elt('is2572_2015_PD');
  var $PE = $elt('is2572_2015_PE');
  var $PF = $elt('is2572_2015_PF');
  var $PG = $elt('is2572_2015_PG');
  var $PH = $elt('is2572_2015_PH');
  var $PJ = $elt('is2572_2015_PJ');
  var $PK = $elt('is2572_2015_PK');
  var $PL = $elt('is2572_2015_PL');

  $percent($TA, $RA, 100 / 3);
  $percent($TB, $RB, 15);
  $readonly($GE, true);
  $addition($GE, $TA, $TB, $GC, $GD);
  $readonly($RG, true);
  $addition($RG, $JA, $MA, $MC, $MD);
  $readonly($RH, true);
  $soustraction($RH, $GE, $RG);

  // Calcul RP
  var RPFIelds = [$LC, $RJ, $LF, $RN, $OB, $RK, $RL, $LA, $RM, $OC];
  var RPTotal = '';
  for (var i = 0; i < RPFIelds.length; i++) {
    if ($isServi(RPFIelds[i]) && $float(RPFIelds[i]) >= 0) {
      if (RPTotal === '') {
        RPTotal = 0;
      }
      RPTotal += $float(RPFIelds[i]);
    }
  }
  if ($isServi($LE) && $float($LE) >= 0) {
    if (RPTotal === '') {
      RPTotal = 0;
    }
    RPTotal -= $float($LE);
  }
  $value($RP, (RPTotal === '') ? '' : Math.max(0, RPTotal));

  $readonly($RS, true);
  $soustraction($RS, $RH, $RP);
  $readonly($RE, true);
  $addition($RE, $KA, $NA, $KB, $NC, $KC, $NC, $ND, $NE, $NF, $NG, $RC, $NJ, $NK, $NL, $NM, $NN, $OD, $NO);
  $readonly($RF, true);
  $soustraction($RF, $RS, $RE);
  $readonly($RV, true);
  $percent($RV, $RU, 10.7);
  $readonly($RX, true);
  $soustraction($RX, $RV, $ME);
  $readonly($RZ, true);
  $percent($RZ, $RW, 3.3);
  $readonly($PA, true);
  $soustraction($PA, $RZ, $MB);
  $readonly($PM, true);
  $percent($PM, $PC, 2.5);
  $readonly($PN, true);
  $soustraction($PN, $RF, $RT);
  $readonly($PQ, true);
  $soustraction($PQ, $RT, $RF);
  $readonly($PR, true);
  $soustraction($PR, $RX, $RY);
  $readonly($PS, true);
  $soustraction($PS, $RY, $RX);
  $readonly($PT, true);
  $soustraction($PT, $PA, $PB);
  $readonly($PU, true);
  $soustraction($PU, $PB, $PA);
  $readonly($PV, true);
  $soustraction($PV, $PM, $PD);
  $readonly($PW, true);
  $soustraction($PW, $PD, $PM);
  $readonly($AD, true);
  $addition($AD, $PN, $PR, $PT, $PV);
  $readonly($BD, true);
  $addition($BD, $PQ, $PS, $PU, $PW);
  $readonly($CA, true);
  $soustraction($CA, $AD, $BD);
  $readonly($DA, true);
  $soustraction($DA, $BD, $AD);
  $readonly($PL, true);
  $soustraction($PL, $CA, $PK);
  $readonly($EB, true);
  $soustraction($EB, $DA, $EA, $PG);

  NTD.Identif.p("hidePaiement", []);
  if ($isServi($CA) && $float($CA) > 0) {
    NTD.Identif.p("showPaiement", [$float($CA)]);
  }


  $assert(!($isServi($LC) && $isServi($LD) && !($float($LD) <= $float($LC))), 'erreur_316', $LD);
  $assert(!($isServi($LF) && $isServi($LE) && !($float($LE) <= $float($LF))), 'erreur_317', $LE);
  $assert(!($isServi($PH) && !($isServi($PK) && $isServi($PJ))), 'erreur_310', $PH);

  var $PidentifKF = $elt(NTD.Identif.pField('KF'));
  var $date_PJ = $value($PJ).split('/');
  $date_PJ = new Date($date_PJ[2], $date_PJ[1] - 1, $date_PJ[0]);
  var $date_KF = $value($PidentifKF).split('/');
  $date_KF = new Date($date_KF[1], $date_KF[0] - 1, '01');
  var $date_KF_inf_datePJ = $date_PJ.getTime() < $date_KF.getTime();

  $assert(!($isServi($PJ) && $isServi($PidentifKF) && !($date_KF_inf_datePJ)), 'erreur_318', $PJ);
  $assert(!($isServi($PJ) && !($isServi($PK) && $isServi($PH))), 'erreur_310', $PJ);
  $assert(!($isServi($PK) && !($isServi($PH) && $isServi($PJ))), 'erreur_310', $PK);
  $assert(!($isServi($CA) && $isServi($PK) && $float($CA) > 0 && $float($PK) > 0 && !($float($CA) >= $float($PK))), 'erreur_311', $PK);
  $assert(!($isServi($EA) && $float($EA) > 0 && !($isServi($DA) && $float($EA) <= $float($DA))), 'erreur_311', $EA);
  $assert(!($isServi($PE) && !($isServi($PG) && $isServi($PF))), 'erreur_310', $PE);
  $assert(!($isServi($PF) && !($isServi($PG) && $isServi($PE))), 'erreur_310', $PF);
  var $DAminusEA = 0;
  if ($isServi($DA)) {
    $DAminusEA = $float($DA);
  }
  if ($isServi($EA)) {
    $DAminusEA -= $float($EA);
  }
  $assert(!($isServi($DA) && $float($DA) > 0 && $isServi($PG) && $float($PG) >= 0 && !($DAminusEA >= $float($PG))), 'erreur_319', $PG);
};

asserts.functions.is2573_2015 = function($elt,
                                         $assert,
                                         $controls,
                                         $isServi,
                                         $float,
                                         $value,
                                         $readonly,
                                         $isSiren,
                                         $XOR,
                                         $addition,
                                         $soustraction,
                                         $percent) {

  var $AA = $elt('is2573_2015_AA');
  var $BA = $elt('is2573_2015_BA');
  var $CA = $elt('is2573_2015_CA');
  var $rowIndex;

  NTD.Identif.p("hidePaiement", []);

  // for each row
  $rowIndex = 1;
  while ($elt('is2573_2015_AB/' + $rowIndex)) {
    var $AB = $elt('is2573_2015_AB/'+$rowIndex);
    var $AC = $elt('is2573_2015_AC/'+$rowIndex);
    var $AF = $elt('is2573_2015_AF/'+$rowIndex);
    var $AG = $elt('is2573_2015_AG/'+$rowIndex);
    var $AH = $elt('is2573_2015_AH/'+$rowIndex);
    var $AI = $elt('is2573_2015_AI/'+$rowIndex);
    var $KA = $elt('is2573_2015_KA/'+$rowIndex);
    var $KB = $elt('is2573_2015_KB/'+$rowIndex);
    var $KC = $elt('is2573_2015_KC/'+$rowIndex);
    var $KD = $elt('is2573_2015_KD/'+$rowIndex);

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
  while ($elt('is2573_2015_BB/' + $rowIndex)) {
    var $BB = $elt('is2573_2015_BB/'+$rowIndex);
    var $BC = $elt('is2573_2015_BC/'+$rowIndex);
    var $BD = $elt('is2573_2015_BD/'+$rowIndex);
    var $BE = $elt('is2573_2015_BE/'+$rowIndex);


    $assert(!(($isServi($BB) || $isServi($BC) || $isServi($BD) || $isServi($BE))
            && !($isServi($BB) && $isServi($BC) && $isServi($BE) && $float($BE) > 0)),
            'erreur_307', $BB, $BC, $BD, $BE);
    $rowIndex++;
  }

  // for each row
  $rowIndex = 1;
  while ($elt('is2573_2015_CB/' + $rowIndex)) {
    var $CB = $elt('is2573_2015_CB/'+$rowIndex);
    var $CC = $elt('is2573_2015_CC/'+$rowIndex);
    var $CD = $elt('is2573_2015_CD/'+$rowIndex);
    var $CE = $elt('is2573_2015_CE/'+$rowIndex);
    var $CF = $elt('is2573_2015_CF/'+$rowIndex);


    $assert(!(($isServi($CB) || $isServi($CC) || $isServi($CD) || $isServi($CE) || $isServi($CF))
            && !($isServi($CB) && $isServi($CC) && $isServi($CD) && $isServi($CF) && $float($CF) > 0)),
            'erreur_308', $CB, $CC, $CD, $CF);
    $rowIndex++;
  }


};


asserts.functions.cvae1329ac_20150101 = function($elt,
                                                 $assert,
                                                 $controls,
                                                 $isServi,
                                                 $float,
                                                 $value,
                                                 $readonly,
                                                 $isSiren,
                                                 $XOR,
                                                 $addition,
                                                 $soustraction,
                                                 $percent) {
  var $AA = $elt('cvae1329ac_20150101_AA');
  var $AB = $elt('cvae1329ac_20150101_AB');
  var $AC = $elt('cvae1329ac_20150101_AC');
  var $AD = $elt('cvae1329ac_20150101_AD');
  var $BA = $elt('cvae1329ac_20150101_BA');
  var $BB = $elt('cvae1329ac_20150101_BB');
  var $BC = $elt('cvae1329ac_20150101_BC');
  var $CA = $elt('cvae1329ac_20150101_CA');
  var $CB = $elt('cvae1329ac_20150101_CB');
  var $DA = $elt('cvae1329ac_20150101_DA');
  var $DB = $elt('cvae1329ac_20150101_DB');
  var $EA = $elt('cvae1329ac_20150101_EA');
  var $EB = $elt('cvae1329ac_20150101_EB');
  var $EC = $elt('cvae1329ac_20150101_EC');
  var $ED = $elt('cvae1329ac_20150101_ED');
  var $GA = $elt('cvae1329ac_20150101_GA');
  var $GB = $elt('cvae1329ac_20150101_GB');
  var $HA = $elt('cvae1329ac_20150101_HA');
  var $KA = $elt('cvae1329ac_20150101_KA');
  var $KACheckbox = $elt('cvae1329ac_20150101_KA_checkbox');


  $readonly($BB, true);
  $value($BB, '');
  if (!$isServi($BC)) {
    if (!$isServi($AB)) {
      if ($isServi($AA) && $float($AA) <= 7600000) {
        $percent($BB, $AA, 80); // Si AB est vide et AA < = 7 600 000, alors BB = AA x 80%,
      }
      else if ($isServi($AA) && $float($AA) > 7600000) {
        $percent($BB, $AA, 85); // Sinon si AB est vide et AA > 7 600 000, alors BB = AA x 85%,
      }
    }
    else {
      if ($float($AB) <= 7600000) {
        $percent($BB, $AB, 80); // Sinon si AB rempli et AB < = 7 600 000, alors BB = AB x 80% ,
      }
      else if ($float($AB) > 7600000) {
        $percent($BB, $AB, 85); // Sinon si  AB rempli et AB > 7 600 000, alors BB = AB x 85%
      }
    }
  }

  //Si 500 000 € <= $activeField <= 3 000 000 €, alors (AC  = [0,5 x ($activeField - 500 000)] / 2 500 000
  //Sinon si 3 000 000 € < $activeField <= 10 000 000 €, alors AC  = 0,5 + [0,9 x ($activeField - 3 000 000)] / 7 000 000
  //Sinon si 10 000 000 € <$activeField  <= 50 000 000 €, alors AC = 1,4 + [0,1 x ($activeField - 10 000 000)] / 40 000 000
  //Sinon si $activeField > 50 000 000 €, alors (AC ) = 1,5
  $readonly($AC, true);
  $value($AC, '');
  var $activeField = null;
  if($isServi($AD)) {
    $activeField = $AD;
  }
  else if($isServi($AA)) {
    $activeField = $AA;
  }

  if ($activeField) {
    if ($float($activeField) < 500000) {
      $value($AC, 0);
    }
    else if (500000 <= $float($activeField) && $float($activeField) <= 3000000) {
      $value($AC, ((0.5 * ($float($activeField) - 500000)) / 2500000).toFixed(2));
    }
    else if (3000000 < $float($activeField) && $float($activeField) <= 10000000) {
      $value($AC, (0.5 + ((0.9 * ($float($activeField) - 3000000)) / 7000000)).toFixed(2));
    }
    else if (10000000 < $float($activeField) && $float($activeField) <= 50000000) {
      $value($AC, (1.4 + ((0.1 * ($float($activeField) - 10000000)) / 40000000)).toFixed(2));
    }
    else if ($float($activeField) > 50000000) {
      $value($AC, 1.5);
    }
  }

  // TODO : a confirmer
  $readonly($CA, true);
  $value($CA, '');
  if($isServi($AC)) {
    if (!$isServi($BC)) {
      if ($isServi($BB) && $isServi($BA)) {
        if($float($BA) > $float($BB)) {
          $value($CA, Math.round($float($BB) * $float($AC) / 100));
        }
        else{
          $value($CA, Math.round($float($BA) * $float($AC) / 100));
        }
      }
    }
    else {
      if ($isServi($BA)) {
        $value($CA, Math.round($float($BA) * $float($AC) / 100));
      }
    }
  }


  $readonly($CB, true);
  $value($CB, '');
  if ($isServi($AA) && $isServi($CA)) {
    if ($float($AA) < 2000000 && $float($CA) <= 1000) {
      $value($CB, 0);
    }
    else if ($float($AA) < 2000000 && $float($CA) > 1000) {
      $value($CB, Math.round(($float($CA) - 1000) * 0.50));
    }
    else if ($float($AA) >= 2000000) {
      $value($CB, Math.round($float($CA) * 0.50));
    }
  }

  $readonly($EA, true);
  $soustraction($EA, $CB, $DA, $DB);

  $readonly($ED, true);
  $value($ED, '');
  if ($isServi($EA) && $isServi($EB) && $isServi($EC)) {
    $value($ED, Math.max(0, $float($EA) + $float($EB) - $float($EC)));
  }

  $readonly($GB, true);
  $value($GB, 0);
  if(!$isServi($GA)) {
    $percent($GB, $ED, 3.93);
  }

  $readonly($HA, true);
  $value($HA, '');
  if($isServi($ED) && $isServi($GB)) {
    $value($HA, Math.round(($float($ED) + $float($GB)) / 100));
  }

  $readonly($KA, true);
  $addition($KA, $ED, $GB, $HA);

  if ($isServi($KA) && $float($KA) > 1500) {
    $KACheckbox.checked = false;
  }
  if ($isServi($KA) && $float($KA) > 0 && !$isServi($KACheckbox)) {
    NTD.Identif.p("showPaiement", [$float($KA)]);
  }
  else {
    NTD.Identif.p("hidePaiement", []);
  }

  /*if ($isServi($KACheckbox)) {
    $('row-link-KA').show();
  } else {
    $('row-link-KA').hide();
  }*/

  $assert($isServi($AA) && $float($AA) > 152500, 'cvae_erreur_202', $AA);
  $assert(!($isServi($AB) && $float($AB) > 0 && !($isServi($AA) && $float($AA) > 0)), 'cvae_erreur_205', $AB);
  $assert(!($isServi($AD) && $float($AD) > 0 && !($isServi($AA) && $float($AD) >= $float($AA))), 'cvae_erreur_206', $AD);
  $assert(!($isServi($EB) && $isServi($EC) && $float($EB) > 0 && $float($EC) > 0), 'cvae_erreur_207', $EB);
};


asserts.functions.cvae1329def_20150101 = function($elt,
                                                 $assert,
                                                 $controls,
                                                 $isServi,
                                                 $float,
                                                 $value,
                                                 $readonly,
                                                 $isSiren,
                                                 $XOR,
                                                 $addition,
                                                 $soustraction,
                                                 $percent) {
  var $AA = $elt('cvae1329def_20150101_AA');
  var $AB = $elt('cvae1329def_20150101_AB');
  var $AC = $elt('cvae1329def_20150101_AC');
  var $AD = $elt('cvae1329def_20150101_AD');
  var $BA = $elt('cvae1329def_20150101_BA');
  var $BB = $elt('cvae1329def_20150101_BB');
  var $BC = $elt('cvae1329def_20150101_BC');
  var $CA = $elt('cvae1329def_20150101_CA');
  var $CB = $elt('cvae1329def_20150101_CB');
  var $DA = $elt('cvae1329def_20150101_DA');
  var $DB = $elt('cvae1329def_20150101_DB');
  var $EA = $elt('cvae1329def_20150101_EA');
  var $EB = $elt('cvae1329def_20150101_EB');
  var $EC = $elt('cvae1329def_20150101_EC');
  var $ED = $elt('cvae1329def_20150101_ED');
  var $GA = $elt('cvae1329def_20150101_GA');
  var $GB = $elt('cvae1329def_20150101_GB');
  var $GC = $elt('cvae1329def_20150101_GC');
  var $GD = $elt('cvae1329def_20150101_GD');
  var $GE = $elt('cvae1329def_20150101_GE');
  var $HA = $elt('cvae1329def_20150101_HA');
  var $HB = $elt('cvae1329def_20150101_HB');
  var $HC = $elt('cvae1329def_20150101_HC');
  var $HD = $elt('cvae1329def_20150101_HD');
  var $JA = $elt('cvae1329def_20150101_JA');
  var $JE = $elt('cvae1329def_20150101_JE');
  var $JK = $elt('cvae1329def_20150101_JK');
  var $KA = $elt('cvae1329def_20150101_KA');
  var $KB = $elt('cvae1329def_20150101_KB');

  // TODO : ligne manquante 19


  // Si 500 000 € < = AA < = 3 000 000 €, alors AC = [0,5 x (AA - 500 000)] / 2 500 000
  // Sinon si 3 000 000 € < AA < = 10 000 000 €, alors AC = 0,5 + [0,9 x (AA - 3 000 000)] / 7 000 000
  // Sinon si 10 000 000 € < AA  < = 50 000 000 €, alors AC = 1,4 + [0,1 x (AA - 10 000 000)] / 40 000 000
  // Sinon si AA   > 50 000 000 €, alors AC = 1,5
  $readonly($AC, true);
  $value($AC, '');

  var $activeField = null;
  if($isServi($AD)) {
    $activeField = $AD;
  }
  else if($isServi($AA)) {
    $activeField = $AA;
  }

  if ($activeField) {
    if ($float($activeField) < 500000) {
      $value($AC, 0);
    }
    else if (500000 <= $float($activeField) && $float($activeField) <= 3000000) {
      $value($AC, ((0.5 * ($float($activeField) - 500000)) / 2500000).toFixed(2));
    }
    else if (3000000 < $float($activeField) && $float($activeField) <= 10000000) {
      $value($AC, (0.5 + ((0.9 * ($float($activeField) - 3000000)) / 7000000)).toFixed(2));
    }
    else if (10000000 < $float($activeField) && $float($activeField) <= 50000000) {
      $value($AC, (1.4 + ((0.1 * ($float($activeField) - 10000000)) / 40000000)).toFixed(2));
    }
    else if ($float($activeField) > 50000000) {
      $value($AC, 1.5);
    }
  }


  //"Si BC/CCI vide Alors
  //Si AB est vide et AA <= 7 600 000, alors BB = AA x 80%,
  //  Sinon si AB est vide et AA > 7 600 000, alors BB = AA x 85%,
  //  Sinon si AB rempli et AB < = 7 600 000, alors BB = AB x 80% ,
  //  Sinon si  AB rempli et AB) > 7 600 000, alors BB = AB x 85%
  //Sinon ( BC/CCI non vide) alors BB vide  "
  $readonly($BB, true);
  $value($BB, '');
  if (!$isServi($BC)) {
    if (!$isServi($AB)) {
      if ($isServi($AA) && $float($AA) <= 7600000) {
        $percent($BB, $AA, 80);
      }
      else if ($isServi($AA) && $float($AA) > 7600000) {
        $percent($BB, $AA, 85);
      }
    }
    else {
      if ($float($AB) <= 7600000) {
        $percent($BB, $AB, 80);
      }
      else if ($float($AB) > 7600000) {
        $percent($BB, $AB, 85);
      }
    }
  }

  // Si BA <= BB et BC vide alors CA = BA  x AC
  // Sinon Si BA > BB et BC vide alors CA = BB  x AC
  // Sinon Si BC = 1 alors CA = BA  x AC
  $readonly($CA, true);
  $value($CA, '');
  if ($isServi($BA) && $isServi($BB) && $float($BA) <= $float($BB) && !$isServi($BC)) {
    $value($CA, Math.round($float($BA) * $float($AC) / 100));
  }
  else if ($isServi($BA) && $isServi($BB) && $float($BA) > $float($BB) && !$isServi($BC)) {
    $value($CA, Math.round($float($BB) * $float($AC) / 100));
  }
  else if ($isServi($BC)) {
    $value($CA, Math.round($float($BA) * $float($AC) / 100));
  }

  // Si AA < 2 000 000€ et CA  <= 1 000€ alors CB  = 0
  // Sinon si AA < 2 000 000€ et CA > 1 000€ alors CB  = (CA  - 1000€)
  // Sinon Si AA >= 2 000 000€ alors CB  = CA
  $readonly($CB, true);
  $value($CB, '');
  if ($isServi($AA) && $isServi($CA)) {
    if ($float($AA) < 2000000 && $float($CA) <= 1000) {
      $value($CB, 0);
    }
    else if ($float($AA) < 2000000 && $float($CA) > 1000) {
      $value($CB, ($float($CA) - 1000));
    }
    else if ($float($AA) >= 2000000) {
      $value($CB, $float($CA));
    }
  }


  // Si [(AA > 500000) et ((CB – DA – DB) < 250)] Alors
  //   si (CB > DA + DB) ou (CB = 0 et (DA + DB = 0)) EA = 250
  //   Sinon EA = 0
  // Sinon Si [(AA <= 500000) ou ((CB – DA – DB) >=250 ) ] Alors
  //   Si ( CB – DA – DB ) >= 0 Alors
  //     EA = CB – DA – DB
  //   Sinon EA = 0
  //   Finsi
  $readonly($EA, true);
  $value($EA, '');

  if ($isServi($AA) && $isServi($CB) && $isServi($DA) && $isServi($DB)) {
    var resultCADADB = $float($CB) - $float($DA) - $float($DB);
    if ($float($AA) > 500000 && resultCADADB < 250) {
      if (($float($CB) > ($float($DA) + $float($DB)))
        || ($float($CB) == 0 && ($float($DA) + $float($DB) == 0))) {
        $value($EA, 250);
      }
      else {
        $value($EA, 0);
      }
    }
    else if ($float($AA) <= 500000 || resultCADADB >= 250) {
      if (resultCADADB >= 0) {
        $value($EA, resultCADADB);
      }
      else {
        $value($EA, 0);
      }
    }
  }


  $readonly($EC, true);
  $soustraction($EC, $EA, $EB);

  $readonly($ED, true);
  $soustraction($ED, $EB, $EA);

  $readonly($GB, true);
  if (!$isServi($GA)) {
    $percent($GB, $EA, 5.59);
  }
  else {
    $value($GB, 0);
  }


  $readonly($GD, true);
  $soustraction($GD, $GB, $GC);

  $readonly($GE, true);
  $soustraction($GE, $GC, $GB);

  $readonly($HA, true);
  $value($HA, '');
  if ($isServi($EA) && $isServi($GB)) {
    $value($HA, Math.round(0.01 * ($float($EA) + $float($GB))));
  }

  $readonly($HC, true);
  $soustraction($HC, $HA, $HB);

  $readonly($HD, true);
  $soustraction($HD, $HB, $HA);

  $readonly($JA, true);
  $addition($JA, $EB, $GC, $HB);

  $readonly($JK, true);
  $addition($JK, $EC, $GD, $HC);

  $readonly($JE, true);
  $addition($JE, $ED, $GE, $HD);

  $readonly($KA, true);
  $value($KA, '');
  $soustraction($KA, $JK, $JE);

  $readonly($KB, true);
  $soustraction($KB, $JE, $JK);

  if ($isServi($KA) && $float($KA) > 0) {
    NTD.Identif.p("showPaiement", [$float($KA)]);
  }
  else {
    NTD.Identif.p("hidePaiement", []);
  }



  $assert($isServi($AA) && $float($AA) >= 0, 'cvae_erreur_201', $AA);
  $assert(!($isServi($AB) && $float($AB) >= 0 && !$isServi($AA)), 'Vous devez saisir ligne 01 votre chiffre d\'affaires rapporté sur 12 mois. Merci de corriger', $AB);
  $assert(!($isServi($AB) && $float($AB) > 0 && !($isServi($AA) && $float($AA) > 0)), 'cvae_erreur_205', $AB);
  $assert(!($isServi($AD) && $float($AD) > 0 && !($isServi($AA) && $float($AD) >= $float($AA))), 'cvae_erreur_206', $AD);
  $assert(!($isServi($GB) && $float($GB) > 0 && !($isServi($GC) && $float($GC) > 0)), 'Présence de la taxe additionnelle sans montant d\'acompte versés.', $GC);


};
