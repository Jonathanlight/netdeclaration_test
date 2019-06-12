/** Millésime 2016 **/

asserts.functions.tva3310a_20160101 = function($elt,
                                               $assert,
                                               $controls,
                                               $isServi,
                                               $float,
                                               $value,
                                               $readonly,
                                               $isSiren,
                                               $XOR) {

  // var $AE = $elt('tva3310a_20160101_AE');
  // var $AF = $elt('tva3310a_20160101_AF');
  var $BA = $elt('tva3310a_20160101_BA');
  var $BB = $elt('tva3310a_20160101_BB');
  var $BC = $elt('tva3310a_20160101_BC');
  var $BE = $elt('tva3310a_20160101_BE');
  var $BF = $elt('tva3310a_20160101_BF');
  var $BK = $elt('tva3310a_20160101_BK');
  var $BM = $elt('tva3310a_20160101_BM');
  var $BN = $elt('tva3310a_20160101_BN');
  var $BP = $elt('tva3310a_20160101_BP');
  var $BQ = $elt('tva3310a_20160101_BQ');
  var $BR = $elt('tva3310a_20160101_BR');
  var $BS = $elt('tva3310a_20160101_BS');
  var $CA = $elt('tva3310a_20160101_CA');
  var $CB = $elt('tva3310a_20160101_CB');
  var $CC = $elt('tva3310a_20160101_CC');
  var $CE = $elt('tva3310a_20160101_CE');
  var $CF = $elt('tva3310a_20160101_CF');
  var $CK = $elt('tva3310a_20160101_CK');
  var $CM = $elt('tva3310a_20160101_CM');
  var $CN = $elt('tva3310a_20160101_CN');
  var $CP = $elt('tva3310a_20160101_CP');
  var $CQ = $elt('tva3310a_20160101_CQ');
  var $CR = $elt('tva3310a_20160101_CR');
  var $CS = $elt('tva3310a_20160101_CS');
  var $DA = $elt('tva3310a_20160101_DA');
  var $DB = $elt('tva3310a_20160101_DB');
  var $FA = $elt('tva3310a_20160101_FA');
  var $FB = $elt('tva3310a_20160101_FB');
  var $FE = $elt('tva3310a_20160101_FE');
  var $FF = $elt('tva3310a_20160101_FF');
  var $FG = $elt('tva3310a_20160101_FG');
  var $FJ = $elt('tva3310a_20160101_FJ');
  var $FR = $elt('tva3310a_20160101_FR');
  var $FT = $elt('tva3310a_20160101_FT');
  var $FV = $elt('tva3310a_20160101_FV');
  var $HB = $elt('tva3310a_20160101_HB');
  var $HE = $elt('tva3310a_20160101_HE');
  var $HF = $elt('tva3310a_20160101_HF');
  var $HI = $elt('tva3310a_20160101_HI');
  var $JA = $elt('tva3310a_20160101_JA');
  var $JB = $elt('tva3310a_20160101_JB');
  var $JC = $elt('tva3310a_20160101_JC');
  var $JD = $elt('tva3310a_20160101_JD');
  var $JE = $elt('tva3310a_20160101_JE');
  var $JF = $elt('tva3310a_20160101_JF');
  var $JG = $elt('tva3310a_20160101_JG');
  var $JH = $elt('tva3310a_20160101_JH');
  var $JJ = $elt('tva3310a_20160101_JJ');
  var $JK = $elt('tva3310a_20160101_JK');
  var $JL = $elt('tva3310a_20160101_JL');
  var $JM = $elt('tva3310a_20160101_JM');
  var $JN = $elt('tva3310a_20160101_JN');
  var $JP = $elt('tva3310a_20160101_JP');
  var $JQ = $elt('tva3310a_20160101_JQ');
  var $JR = $elt('tva3310a_20160101_JR');
  // var $KA = $elt('tva3310a_20160101_KA');
  // var $KB = $elt('tva3310a_20160101_KB');
  // var $KC = $elt('tva3310a_20160101_KC');
  // var $KD = $elt('tva3310a_20160101_KD');
  // var $KE = $elt('tva3310a_20160101_KE');
  var $KF = $elt('tva3310a_20160101_KF');
  var $KG = $elt('tva3310a_20160101_KG');
  var $KJ = $elt('tva3310a_20160101_KJ');
  var $KL = $elt('tva3310a_20160101_KL');
  var $KN = $elt('tva3310a_20160101_KN');
  var $KQ = $elt('tva3310a_20160101_KQ');
  var $KT = $elt('tva3310a_20160101_KT');
  var $KU = $elt('tva3310a_20160101_KU');
  var $KX = $elt('tva3310a_20160101_KX');
  var $KY = $elt('tva3310a_20160101_KY');
  var $KZ = $elt('tva3310a_20160101_KZ');
  var $LA = $elt('tva3310a_20160101_LA');
  var $LC = $elt('tva3310a_20160101_LC');
  var $LD = $elt('tva3310a_20160101_LD');
  var $LE = $elt('tva3310a_20160101_LE');
  var $LF = $elt('tva3310a_20160101_LF');
  var $LG = $elt('tva3310a_20160101_LG');
  var $LH = $elt('tva3310a_20160101_LH');
  var $LJ = $elt('tva3310a_20160101_LJ');
  var $LJ = $elt('tva3310a_20160101_LJ');
  var $LK = $elt('tva3310a_20160101_LK');
  var $LL = $elt('tva3310a_20160101_LL');
  var $LM = $elt('tva3310a_20160101_LM');
  var $LN = $elt('tva3310a_20160101_LN');
  var $LP = $elt('tva3310a_20160101_LP');
  var $LQ = $elt('tva3310a_20160101_LQ');
  var $LR = $elt('tva3310a_20160101_LR');
  var $LS = $elt('tva3310a_20160101_LS');
  var $LT = $elt('tva3310a_20160101_LT');
  var $LU = $elt('tva3310a_20160101_LU');
  var $LV = $elt('tva3310a_20160101_LV');
  var $LW = $elt('tva3310a_20160101_LW');
  var $LX = $elt('tva3310a_20160101_LX');
  var $LZ = $elt('tva3310a_20160101_LZ');
  var $MA = $elt('tva3310a_20160101_MA');
  var $MB = $elt('tva3310a_20160101_MB');
  var $MC = $elt('tva3310a_20160101_MC');
  var $MD = $elt('tva3310a_20160101_MD');
  var $ME = $elt('tva3310a_20160101_ME');
  var $MF = $elt('tva3310a_20160101_MF');
  var $MG = $elt('tva3310a_20160101_MG');

  $readonly($BN, true);
  $readonly($CN, true);
  $readonly($HB, true);

  // $readonly($KA, true);
  // $readonly($KB, true);
  // $readonly($KC, true);
  // $readonly($KD, true);
  // $readonly($KE, true);

  $value($CB, ($isServi($BB) && $float($BB) > 0) ? Math.round($float($BB) * 0.021) : '');
  $value($CF, ($isServi($BF) && $float($BF) > 0) ? Math.round($float($BF) * 0.021) : '');
  $value($CE, ($isServi($BE) && $float($BE) > 0) ? Math.round($float($BE) * 0.009) : '');
  $value($CS, ($isServi($BS) && $float($BS) > 0) ? Math.round($float($BS) * 0.100) : '');
  $value($CK, ($isServi($BK) && $float($BK) > 0) ? Math.round($float($BK) * 0.130) : '');
  $value($CP, ($isServi($BP) && $float($BP) > 0) ? Math.round($float($BP) * 0.0105) : '');
  $value($CQ, ($isServi($BQ) && $float($BQ) > 0) ? Math.round($float($BQ) * 0.0175) : '');


  var CNValue = 0;
  [$CA, $CB, $CC/*, $AF*/, $CE, $CF, $CS, $CK, $CM, $CP, $CQ, $CR].each(function(elt) {
    if ($float(elt) > 0) {
      CNValue += $float(elt);
    }
  });
  $value($CN, CNValue);

  var BNValue = 0;
  [$BA, $BB, $BC/*, $AE*/, $BE, $BF, $BS, $BK, $BM, $BP, $BQ, $BR].each(function(elt) {
    if ($float(elt) > 0) {
      BNValue += $float(elt);
    }
  });
  $value($BN, BNValue);

  var HBValue = 0;
  [$FA, $FB, $FE, $FF, $FG, $FJ, $FR, $FT, $FV,
   $HE, $HF, $HI,
   $JB, $JC, $JD, $JE, $JF, $JG, $JH, $JJ, $JK, $JL, $JM, $JN, $JP, $JQ, $JR,
   $KF, $KG, $KJ, $KL, $KN, $KQ, $KT, $KU, $KX, $KY, $KZ,
   $LA, $LC, $LD, $LE, $LF, $LG, $LH, $LJ, $LK, $LL, $LM, $LN, $LP, $LQ, $LR, $LS, $LT, $LU, $LV, $LW, $LX, $LZ,
   $MA].each(function(elt) {
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

  $value($elt('tva3310ca3_20160101_FD'), $float($BN));
  $value($elt('tva3310ca3_20160101_GD'), $float($CN));
  $value($elt('tva3310ca3_20160101_KB'), $float($HB));
};

asserts.functions.tva3310ca3_20160101 = function($elt,
                                                 $assert,
                                                 $controls,
                                                 $isServi,
                                                 $float,
                                                 $value,
                                                 $readonly,
                                                 $isSiren,
                                                 $XOR) {


  var $BA = $elt('tva3310ca3_20160101_BA');
  var $BB = $elt('tva3310ca3_20160101_BB');
  var $BC = $elt('tva3310ca3_20160101_BC');

  var $CA = $elt('tva3310ca3_20160101_CA');
  var $CB = $elt('tva3310ca3_20160101_CB');
  var $CC = $elt('tva3310ca3_20160101_CC');
  var $CD = $elt('tva3310ca3_20160101_CD');
  var $CE = $elt('tva3310ca3_20160101_CE');
  var $CF = $elt('tva3310ca3_20160101_CF');
  var $CG = $elt('tva3310ca3_20160101_CG');

  var $DA = $elt('tva3310ca3_20160101_DA');
  var $DB = $elt('tva3310ca3_20160101_DB');
  var $DC = $elt('tva3310ca3_20160101_DC');
  var $DD = $elt('tva3310ca3_20160101_DD');
  var $DE = $elt('tva3310ca3_20160101_DE');
  var $DF = $elt('tva3310ca3_20160101_DF');
  var $DG = $elt('tva3310ca3_20160101_DG');

  var $FB = $elt('tva3310ca3_20160101_FB');
  var $FC = $elt('tva3310ca3_20160101_FC');
  var $FD = $elt('tva3310ca3_20160101_FD');
  var $FG = $elt('tva3310ca3_20160101_FG');
  var $FH = $elt('tva3310ca3_20160101_FH');
  var $FJ = $elt('tva3310ca3_20160101_FJ');
  var $FK = $elt('tva3310ca3_20160101_FK');
  var $FM = $elt('tva3310ca3_20160101_FM');
  var $FN = $elt('tva3310ca3_20160101_FN');
  var $FP = $elt('tva3310ca3_20160101_FP');
  var $FR = $elt('tva3310ca3_20160101_FR');

  var $GB = $elt('tva3310ca3_20160101_GB');
  var $GC = $elt('tva3310ca3_20160101_GC');
  var $GD = $elt('tva3310ca3_20160101_GD');
  var $GG = $elt('tva3310ca3_20160101_GG');
  var $GH = $elt('tva3310ca3_20160101_GH');
  var $GJ = $elt('tva3310ca3_20160101_GJ');
  var $GK = $elt('tva3310ca3_20160101_GK');
  var $GM = $elt('tva3310ca3_20160101_GM');
  var $GN = $elt('tva3310ca3_20160101_GN');
  var $GP = $elt('tva3310ca3_20160101_GP');
  var $GR = $elt('tva3310ca3_20160101_GR');

  var $HA = $elt('tva3310ca3_20160101_HA');
  var $HB = $elt('tva3310ca3_20160101_HB');
  var $HC = $elt('tva3310ca3_20160101_HC');
  var $HD = $elt('tva3310ca3_20160101_HD');
  var $HE = $elt('tva3310ca3_20160101_HE');
  var $HG = $elt('tva3310ca3_20160101_HG');
  var $HH = $elt('tva3310ca3_20160101_HH');
  var $HJ = $elt('tva3310ca3_20160101_HJ');

  var $KA = $elt('tva3310ca3_20160101_KA');
  var $KB = $elt('tva3310ca3_20160101_KB');
  var $KE = $elt('tva3310ca3_20160101_KE');
  var $KF = $elt('tva3310ca3_20160101_KF');
  var $KG = $elt('tva3310ca3_20160101_KG');
  var $KH = $elt('tva3310ca3_20160101_KH');
  var $KJ = $elt('tva3310ca3_20160101_KJ');
  var $KL = $elt('tva3310ca3_20160101_KL');
  var $KR = $elt('tva3310ca3_20160101_KR');
  var $KS = $elt('tva3310ca3_20160101_KS');
  var $KT = $elt('tva3310ca3_20160101_KT');
  var $KU = $elt('tva3310ca3_20160101_KU');

  var $JA = $elt('tva3310ca3_20160101_JA');
  var $JB = $elt('tva3310ca3_20160101_JB');
  var $JC = $elt('tva3310ca3_20160101_JC');

  // ----

  /* tva3515sd */

  var $CA_sd = $elt('tva3515sd_20160101_CA');
  var $CB_sd = $elt('tva3515sd_20160101_CB');
  var $BC_sd = $elt('tva3515sd_20160101_BC');
  var $BD_sd = $elt('tva3515sd_20160101_BD');

  var $BE_sd = $elt('tva3515sd_20160101_BE');
  var $BF_sd = $elt('tva3515sd_20160101_BF');

  if ($float($KA) > 0) {
    var BEValue = ($float($KA) - $float($KS)) + $float($KU);
    $value($BE_sd, (isNaN(BEValue) ? 0 : BEValue));
  }
  else {
    var BEValue = ($float($KA) - $float($KS));
      $value($BE_sd, (isNaN(BEValue) ? 0 : BEValue));
  }

  var KBValue = $float($KB);
  $value($BF_sd, (isNaN(KBValue) ? 0 : KBValue));

  asserts.run('tva3515sd_20160101');

  // ----

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
  NTD.Identif.p("hidePaiement", []);
  if (KEValue > 0) {
    NTD.Identif.p("showPaiement", [KEValue]);
  }


  $assert(!(($isServi($FD) || $isServi($GD)) && !$isServi($elt('tva3310a_20160101_HB'))),
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

  $assert(!(!$isServi($GJ) && $isServi($CC)), 'erreur_038', $GJ, $CC);
  $assert(!($isServi($HH) && $float($HH) > 0 && !($isServi($CE) && $float($CE) > 0)), 'erreur_140', $HH, $CE);
  $assert(!($isServi($HH) && $isServi($HC) && !($float($HH) <= $float($HC))), 'erreur_051', $HH, $HC);
  $assert(!($isServi($HE) && !(0 < $float($HE) && $float($HE) < 100)), 'erreur_116', $HE);
  $assert(!($isServi($KG) && $isServi($HG) && !($float($KG) <= $float($HG))), 'erreur_205', $KG, $HG);
  $assert(!($isServi($JB) && $isServi($JA) && $isServi($KJ) && !($float($JB) <= $float($JA) - $float($KJ))), 'erreur_131', $JA, $JB, $KJ);
  $assert(!($isServi($KB) && $float($KB) > 0 && !$isServi($elt('tva3310a_20160101_HB'))),
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

asserts.functions.tva3310ter_20160101 = function($elt,
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

  var $AA = $elt('tva3310ter_20160101_AA');
  var $AB = $elt('tva3310ter_20160101_AB');
  var $AC = $elt('tva3310ter_20160101_AC');
  var $BA = $elt('tva3310ter_20160101_BA');
  var $BB = $elt('tva3310ter_20160101_BB');
  var $BC = $elt('tva3310ter_20160101_BC');
  var $BD = $elt('tva3310ter_20160101_BD');
  var $BE = $elt('tva3310ter_20160101_BE');
  var $BF = $elt('tva3310ter_20160101_BF');
  var $BG = $elt('tva3310ter_20160101_BG');
  var $BH = $elt('tva3310ter_20160101_BH');
  var $BJ = $elt('tva3310ter_20160101_BJ');
  var $BK = $elt('tva3310ter_20160101_BK');
  var $CA = $elt('tva3310ter_20160101_CA');
  var $CB = $elt('tva3310ter_20160101_CB');
  var $CC = $elt('tva3310ter_20160101_CC');
  var $CD = $elt('tva3310ter_20160101_CD');
  var $CE = $elt('tva3310ter_20160101_CE');
  var $CF = $elt('tva3310ter_20160101_CF');
  var $CG = $elt('tva3310ter_20160101_CG');
  var $CH = $elt('tva3310ter_20160101_CH');
  var $CJ = $elt('tva3310ter_20160101_CJ');
  var $CK = $elt('tva3310ter_20160101_CK');
  var $DA = $elt('tva3310ter_20160101_DA');
  var $DB = $elt('tva3310ter_20160101_DB');
  var $DC = $elt('tva3310ter_20160101_DC');
  var $DD = $elt('tva3310ter_20160101_DD');
  var $DE = $elt('tva3310ter_20160101_DE');
  var $DF = $elt('tva3310ter_20160101_DF');
  var $DG = $elt('tva3310ter_20160101_DG');
  var $DH = $elt('tva3310ter_20160101_DH');
  var $DJ = $elt('tva3310ter_20160101_DJ');
  var $DK = $elt('tva3310ter_20160101_DK');
  var $DL = $elt('tva3310ter_20160101_DL');
  var $EA = $elt('tva3310ter_20160101_EA');
  var $EB = $elt('tva3310ter_20160101_EB');
  var $EC = $elt('tva3310ter_20160101_EC');
  var $ED = $elt('tva3310ter_20160101_ED');
  var $EE = $elt('tva3310ter_20160101_EE');
  var $EF = $elt('tva3310ter_20160101_EF');
  var $EG = $elt('tva3310ter_20160101_EG');
  var $EH = $elt('tva3310ter_20160101_EH');
  var $EJ = $elt('tva3310ter_20160101_EJ');
  var $EK = $elt('tva3310ter_20160101_EK');
  var $EL = $elt('tva3310ter_20160101_EL');
  var $FA = $elt('tva3310ter_20160101_FA');
  var $FB = $elt('tva3310ter_20160101_FB');
  var $FC = $elt('tva3310ter_20160101_FC');
  var $FD = $elt('tva3310ter_20160101_FD');
  var $FE = $elt('tva3310ter_20160101_FE');
  var $FF = $elt('tva3310ter_20160101_FF');
  var $FG = $elt('tva3310ter_20160101_FG');
  var $FH = $elt('tva3310ter_20160101_FH');
  var $FJ = $elt('tva3310ter_20160101_FJ');
  var $FK = $elt('tva3310ter_20160101_FK');
  var $FL = $elt('tva3310ter_20160101_FL');
  var $GA = $elt('tva3310ter_20160101_GA');
  var $GB = $elt('tva3310ter_20160101_GB');
  var $GC = $elt('tva3310ter_20160101_GC');
  var $GD = $elt('tva3310ter_20160101_GD');
  var $GE = $elt('tva3310ter_20160101_GE');
  var $GF = $elt('tva3310ter_20160101_GF');
  var $GG = $elt('tva3310ter_20160101_GG');
  var $GH = $elt('tva3310ter_20160101_GH');
  var $GJ = $elt('tva3310ter_20160101_GJ');
  var $GK = $elt('tva3310ter_20160101_GK');
  var $GL = $elt('tva3310ter_20160101_GL');
  var $HA = $elt('tva3310ter_20160101_HA');
  var $HB = $elt('tva3310ter_20160101_HB');
  var $HC = $elt('tva3310ter_20160101_HC');
  var $HD = $elt('tva3310ter_20160101_HD');
  var $HE = $elt('tva3310ter_20160101_HE');
  var $HF = $elt('tva3310ter_20160101_HF');
  var $HG = $elt('tva3310ter_20160101_HG');
  var $HH = $elt('tva3310ter_20160101_HH');
  var $HJ = $elt('tva3310ter_20160101_HJ');
  var $HK = $elt('tva3310ter_20160101_HK');
  var $HL = $elt('tva3310ter_20160101_HL');
  var $JA = $elt('tva3310ter_20160101_JA');
  var $JB = $elt('tva3310ter_20160101_JB');
  var $JC = $elt('tva3310ter_20160101_JC');
  var $JD = $elt('tva3310ter_20160101_JD');
  var $JE = $elt('tva3310ter_20160101_JE');
  var $JF = $elt('tva3310ter_20160101_JF');
  var $JG = $elt('tva3310ter_20160101_JG');
  var $JH = $elt('tva3310ter_20160101_JH');
  var $JJ = $elt('tva3310ter_20160101_JJ');
  var $JK = $elt('tva3310ter_20160101_JK');
  var $JL = $elt('tva3310ter_20160101_JL');
  var $KA = $elt('tva3310ter_20160101_KA');
  var $KB = $elt('tva3310ter_20160101_KB');
  var $KC = $elt('tva3310ter_20160101_KC');
  var $KD = $elt('tva3310ter_20160101_KD');
  var $KE = $elt('tva3310ter_20160101_KE');
  var $KF = $elt('tva3310ter_20160101_KF');
  var $KG = $elt('tva3310ter_20160101_KG');
  var $KH = $elt('tva3310ter_20160101_KH');
  var $KJ = $elt('tva3310ter_20160101_KJ');
  var $KK = $elt('tva3310ter_20160101_KK');
  var $KL = $elt('tva3310ter_20160101_KL');
  var $LA = $elt('tva3310ter_20160101_LA');
  var $LB = $elt('tva3310ter_20160101_LB');
  var $LC = $elt('tva3310ter_20160101_LC');
  var $LD = $elt('tva3310ter_20160101_LD');
  var $LE = $elt('tva3310ter_20160101_LE');
  var $LF = $elt('tva3310ter_20160101_LF');
  var $LG = $elt('tva3310ter_20160101_LG');
  var $LH = $elt('tva3310ter_20160101_LH');
  var $LJ = $elt('tva3310ter_20160101_LJ');
  var $LK = $elt('tva3310ter_20160101_LK');
  var $LL = $elt('tva3310ter_20160101_LL');
  var $MA = $elt('tva3310ter_20160101_MA');
  var $MB = $elt('tva3310ter_20160101_MB');
  var $MC = $elt('tva3310ter_20160101_MC');
  var $MD = $elt('tva3310ter_20160101_MD');
  var $ME = $elt('tva3310ter_20160101_ME');
  var $MF = $elt('tva3310ter_20160101_MF');
  var $MG = $elt('tva3310ter_20160101_MG');
  var $MH = $elt('tva3310ter_20160101_MH');
  var $MJ = $elt('tva3310ter_20160101_MJ');
  var $MK = $elt('tva3310ter_20160101_MK');
  var $ML = $elt('tva3310ter_20160101_ML');
  var $NA = $elt('tva3310ter_20160101_NA');
  var $NB = $elt('tva3310ter_20160101_NB');
  var $NC = $elt('tva3310ter_20160101_NC');
  var $ND = $elt('tva3310ter_20160101_ND');
  var $NE = $elt('tva3310ter_20160101_NE');
  var $NF = $elt('tva3310ter_20160101_NF');
  var $NG = $elt('tva3310ter_20160101_NG');
  var $NH = $elt('tva3310ter_20160101_NH');
  var $NJ = $elt('tva3310ter_20160101_NJ');
  var $NK = $elt('tva3310ter_20160101_NK');
  var $NL = $elt('tva3310ter_20160101_NL');
  var $PA = $elt('tva3310ter_20160101_PA');
  var $PB = $elt('tva3310ter_20160101_PB');
  var $PC = $elt('tva3310ter_20160101_PC');
  var $PD = $elt('tva3310ter_20160101_PD');
  var $PE = $elt('tva3310ter_20160101_PE');
  var $PF = $elt('tva3310ter_20160101_PF');
  var $PG = $elt('tva3310ter_20160101_PG');
  var $PH = $elt('tva3310ter_20160101_PH');
  var $PJ = $elt('tva3310ter_20160101_PJ');
  var $PK = $elt('tva3310ter_20160101_PK');
  var $PL = $elt('tva3310ter_20160101_PL');
  var $QA = $elt('tva3310ter_20160101_QA');
  var $QB = $elt('tva3310ter_20160101_QB');
  var $QC = $elt('tva3310ter_20160101_QC');
  var $QD = $elt('tva3310ter_20160101_QD');
  var $QE = $elt('tva3310ter_20160101_QE');
  var $QF = $elt('tva3310ter_20160101_QF');
  var $QG = $elt('tva3310ter_20160101_QG');
  var $QH = $elt('tva3310ter_20160101_QH');
  var $QJ = $elt('tva3310ter_20160101_QJ');
  var $QK = $elt('tva3310ter_20160101_QK');
  var $QL = $elt('tva3310ter_20160101_QL');
  var $QM = $elt('tva3310ter_20160101_QM');
  var $RA = $elt('tva3310ter_20160101_RA');
  var $RB = $elt('tva3310ter_20160101_RB');
  var $RC = $elt('tva3310ter_20160101_RC');
  var $RD = $elt('tva3310ter_20160101_RD');
  var $RE = $elt('tva3310ter_20160101_RE');
  var $RF = $elt('tva3310ter_20160101_RF');
  var $RG = $elt('tva3310ter_20160101_RG');
  var $RH = $elt('tva3310ter_20160101_RH');
  var $RJ = $elt('tva3310ter_20160101_RJ');
  var $RK = $elt('tva3310ter_20160101_RK');
  var $RL = $elt('tva3310ter_20160101_RL');
  var $RM = $elt('tva3310ter_20160101_RM');


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

asserts.functions.tva3515sd_20160101 = function($elt,
                                                $assert,
                                                $controls,
                                                $isServi,
                                                $float,
                                                $value,
                                                $readonly,
                                                $isSiren,
                                                $XOR) {

  var $AA = $elt('tva3515sd_20160101_AA');
  var $AB = $elt('tva3515sd_20160101_AB');
  var $BB = $elt('tva3515sd_20160101_BB');
  var $BC = $elt('tva3515sd_20160101_BC');
  var $BD = $elt('tva3515sd_20160101_BD');
  var $BE = $elt('tva3515sd_20160101_BE');
  var $BF = $elt('tva3515sd_20160101_BF');
  var $CA = $elt('tva3515sd_20160101_CA');
  var $CB = $elt('tva3515sd_20160101_CB');
  var $DA = $elt('tva3515sd_20160101_DA');
  var $DB = $elt('tva3515sd_20160101_DB');
  var $DC = $elt('tva3515sd_20160101_DC');
  var $DD = $elt('tva3515sd_20160101_DD');
  var $EA = $elt('tva3515sd_20160101_EA');
  var $EB = $elt('tva3515sd_20160101_EB');


  $readonly($BE, true);
  $readonly($BF, true);
  $readonly($BE, true);

  $readonly($BC, true);
  $readonly($BD, true);

  $readonly($DA, true);
  $readonly($DB, true);
  $readonly($DC, true);
  $readonly($DD, true);


  if ($float($BE) + $float($BF) >= $float($BB)) {
    var BCValue = ($float($BE) + $float($BF)) - $float($BB);
    $value($BC, BCValue);
  }
  else if ($float($BE) + $float($BF) < $float($BB)) {
    $value($BC, 0);
  }

  if ($float($BB) > $float($BE) + $float($BF)) {
    $value($BD, ($float($BB) - ($float($BE) + $float($BF))));
  }
  else {
    $value($BD, 0);
  }


  // if ($float($CA) < $float($BD)) {
    $value($CA, $float($BD));
  // }


  $value($CB, $float($CA) + $float($BC) - $float($BD));

  $value($DA, $float($CB));
  $value($DB, $float($BE) + $float($BF));

  if (($float($DA) - $float($DB)) > 0) {
    $value($DC, ($float($DA) - $float($DB)));
    $value($DD, 0);
  }
  else {
    $value($DC, 0);
    $value($DD, Math.abs($float($DA) - $float($DB)));
  }

  $assert(!($isServi($CA) && $isServi($BD) && !($float($CA) >= $float($BD))),
          'erreur_115', $CA, $BD);

  $assert(!($isServi($EB)
          && !$isServi($EA)),
          'erreur_128', $EA, $EB);


};


asserts.functions.tva3310ca3g_20160101 = function($elt,
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

  var $BA = $elt('tva3310ca3g_20160101_BA');
  var $BB = $elt('tva3310ca3g_20160101_BB');
  var $BC = $elt('tva3310ca3g_20160101_BC');
  var $DA = $elt('tva3310ca3g_20160101_DA');
  var $DB = $elt('tva3310ca3g_20160101_DB');
  var $DC = $elt('tva3310ca3g_20160101_DC');
  var $EA = $elt('tva3310ca3g_20160101_EA');
  var $EB = $elt('tva3310ca3g_20160101_EB');
  var $EC = $elt('tva3310ca3g_20160101_EC');
  var $FA = $elt('tva3310ca3g_20160101_FA');
  var $FB = $elt('tva3310ca3g_20160101_FB');
  var $FE = $elt('tva3310ca3g_20160101_FE');
  var $GA = $elt('tva3310ca3g_20160101_GA');
  var $GB = $elt('tva3310ca3g_20160101_GB');
  var $GD = $elt('tva3310ca3g_20160101_GD');
  var $GE = $elt('tva3310ca3g_20160101_GE');
  var $GF = $elt('tva3310ca3g_20160101_GF');
  var $GH = $elt('tva3310ca3g_20160101_GH');
  var $GJ = $elt('tva3310ca3g_20160101_GJ');
  var $GK = $elt('tva3310ca3g_20160101_GK');
  var $GL = $elt('tva3310ca3g_20160101_GL');
  var $GM = $elt('tva3310ca3g_20160101_GM');
  var $GO = $elt('tva3310ca3g_20160101_GO');
  var $GP = $elt('tva3310ca3g_20160101_GP');
  var $GQ = $elt('tva3310ca3g_20160101_GQ');
  var $GR = $elt('tva3310ca3g_20160101_GR');
  var $GS = $elt('tva3310ca3g_20160101_GS');
  var $GT = $elt('tva3310ca3g_20160101_GT');
  var $GU = $elt('tva3310ca3g_20160101_GU');
  var $GV = $elt('tva3310ca3g_20160101_GV');
  var $GX = $elt('tva3310ca3g_20160101_GX');
  var $GZ = $elt('tva3310ca3g_20160101_GZ');
  var $HC = $elt('tva3310ca3g_20160101_HC');
  var $HE = $elt('tva3310ca3g_20160101_HE');
  var $HF = $elt('tva3310ca3g_20160101_HF');
  var $HK = $elt('tva3310ca3g_20160101_HK');
  var $HL = $elt('tva3310ca3g_20160101_HL');
  var $HM = $elt('tva3310ca3g_20160101_HM');
  var $HN = $elt('tva3310ca3g_20160101_HN');
  var $HO = $elt('tva3310ca3g_20160101_HO');
  var $HP = $elt('tva3310ca3g_20160101_HP');
  var $HQ = $elt('tva3310ca3g_20160101_HQ');
  var $HR = $elt('tva3310ca3g_20160101_HR');
  var $HS = $elt('tva3310ca3g_20160101_HS');
  var $HT = $elt('tva3310ca3g_20160101_HT');
  var $HU = $elt('tva3310ca3g_20160101_HU');
  var $KF = $elt('tva3310ca3g_20160101_KF');
  var $KH = $elt('tva3310ca3g_20160101_KH');
  var $KJ = $elt('tva3310ca3g_20160101_KJ');
  var $KK = $elt('tva3310ca3g_20160101_KK');
  var $KL = $elt('tva3310ca3g_20160101_KL');
  var $KM = $elt('tva3310ca3g_20160101_KM');
  var $KN = $elt('tva3310ca3g_20160101_KN');
  var $KR = $elt('tva3310ca3g_20160101_KR');
  var $KS = $elt('tva3310ca3g_20160101_KS');
  var $KT = $elt('tva3310ca3g_20160101_KT');
  var $KU = $elt('tva3310ca3g_20160101_KU');
  var $KV = $elt('tva3310ca3g_20160101_KV');
  var $KW = $elt('tva3310ca3g_20160101_KW');
  var $KX = $elt('tva3310ca3g_20160101_KX');
  var $KY = $elt('tva3310ca3g_20160101_KY');
  var $KZ = $elt('tva3310ca3g_20160101_KZ');
  var $LA = $elt('tva3310ca3g_20160101_LA');
  var $LB = $elt('tva3310ca3g_20160101_LB');
  var $LC = $elt('tva3310ca3g_20160101_LC');
  var $LD = $elt('tva3310ca3g_20160101_LD');
  var $LF = $elt('tva3310ca3g_20160101_LF');
  var $LG = $elt('tva3310ca3g_20160101_LG');
  var $MA = $elt('tva3310ca3g_20160101_MA');
  var $MB = $elt('tva3310ca3g_20160101_MB');
  var $MC = $elt('tva3310ca3g_20160101_MC');
  var $MD = $elt('tva3310ca3g_20160101_MD');
  var $ME = $elt('tva3310ca3g_20160101_ME');
  var $MF = $elt('tva3310ca3g_20160101_MF');
  var $MG = $elt('tva3310ca3g_20160101_MG');
  var $MH = $elt('tva3310ca3g_20160101_MH');
  var $MJ = $elt('tva3310ca3g_20160101_MJ');
  var $MK = $elt('tva3310ca3g_20160101_MK');
  var $ML = $elt('tva3310ca3g_20160101_ML');
  var $ML = $elt('tva3310ca3g_20160101_ML');
  var $MN = $elt('tva3310ca3g_20160101_MN');
  var $MM = $elt('tva3310ca3g_20160101_MM');
  var $MP = $elt('tva3310ca3g_20160101_MP');
  var $MR = $elt('tva3310ca3g_20160101_MR');
  var $MS = $elt('tva3310ca3g_20160101_MS');
  var $MT = $elt('tva3310ca3g_20160101_MT');
  var $MU = $elt('tva3310ca3g_20160101_MU');
  var $MV = $elt('tva3310ca3g_20160101_MV');
  var $MX = $elt('tva3310ca3g_20160101_MX');
  var $MY = $elt('tva3310ca3g_20160101_MY');
  var $MZ = $elt('tva3310ca3g_20160101_MZ');

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
  $addition($HK,
            $GA, $GB, $GD, $GE, $GF, $GH, $GJ, $GK, $GL, $GM, $GO, $GP, $GQ, $GR, $GS, $GT, $GU, $GV, $GX, $GZ,
            $HC, $HF, $HL, $HM, $HN, $HO, $HP, $HQ, $HR, $HS, $HT, $HU,
            $KJ, $KK, $KL, $KM, $KS, $KT, $KU, $KV, $KW, $KX, $KY, $KZ,
            $LG,
            $MA, $MB, $MC, $MD, $ME, $MF, $MG, $MH, $MJ, $MK, $ML, $MM, $MN, $MP, $MR, $MS);
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

  if (!$KF.checked) {
    $assert(($isServi($KR) && $float($KR) > 0) || ($isServi($DC) && $float($DC) > 0) || ($isServi($HK) && $float($HK) > 0),
            'erreur_212', $KR, $DC, $HK);

    $assert(!(!$isServi($KR) &&
              !$isServi($DA) &&
              !$isServi($DB) &&
              !$isServi($DC) &&
              !$isServi($EA) &&
              !$isServi($EB) &&
              !$isServi($EC) &&
              !$isServi($FA) &&
              !$isServi($FB) &&
              !$isServi($FE) &&
              !$isServi($GA) &&
              !$isServi($GB) &&
              !$isServi($HN) &&
              !$isServi($GD) &&
              !$isServi($GE) &&
              !$isServi($GF) &&
              !$isServi($GH) &&
              !$isServi($GJ) &&
              !$isServi($GK) &&
              !$isServi($GL) &&
              !$isServi($GM) &&
              !$isServi($GO) &&
              !$isServi($GP) &&
              !$isServi($GQ) &&
              !$isServi($GR) &&
              !$isServi($GS) &&
              !$isServi($GT) &&
              !$isServi($GU) &&
              !$isServi($GV) &&
              !$isServi($GX) &&
              !$isServi($GZ) &&
              !$isServi($HO) &&
              !$isServi($HC) &&
              !$isServi($HF) &&
              !$isServi($HP) &&
              !$isServi($HL) &&
              !$isServi($HM) &&
              !$isServi($HQ) &&
              !$isServi($HR) &&
              !$isServi($HS) &&
              !$isServi($HT) &&
              !$isServi($HU) &&
              !$isServi($LG) &&
              !$isServi($KS) &&
              !$isServi($KT) &&
              !$isServi($KJ) &&
              !$isServi($KK) &&
              !$isServi($KL) &&
              !$isServi($KM) &&
              !$isServi($KU)),
              "erreur_049",
              $KR, $DA, $DB, $DC, $EA, $EB, $EC, $FA, $FB, $FE, $GA, $GB, $HN, $GD, $GE, $GF, $GH, $GJ, $GK, $GL, $GM, $GO, $GP, $GQ, $GR, $GS, $GT, $GU, $GV, $GX, $GZ,
              $HO, $HC, $HF, $HP, $HL, $HM, $HQ, $HR, $HS, $HT, $HU, $LG, $KS, $KT, $KJ, $KK, $KL, $KM, $KU);
  }
};

asserts.functions.tva3514_20160101 = function($elt,
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


  var $HA = $elt('tva3514_20160101_HA');
  var $HB = $elt('tva3514_20160101_HB');
  var $HC = $elt('tva3514_20160101_HC');
  var $DE = $elt('tva3514_20160101_DE');
  var $IA = $elt('tva3514_20160101_IA');
  var $IB = $elt('tva3514_20160101_IB');
  var $IC = $elt('tva3514_20160101_IC');
  var $ID = $elt('tva3514_20160101_ID');
  var $CA = $elt('tva3514_20160101_CA');
  var $CB = $elt('tva3514_20160101_CB');
  var $CC = $elt('tva3514_20160101_CC');


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

asserts.functions.tva3517bisca12_20160101 = function($elt,
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

  var $AE = $elt('tva3517bisca12_20160101_AE');
  var $AF = $elt('tva3517bisca12_20160101_AF');
  var $AG = $elt('tva3517bisca12_20160101_AG');
  var $BA = $elt('tva3517bisca12_20160101_BA');
  var $DA = $elt('tva3517bisca12_20160101_DA');
  var $DB = $elt('tva3517bisca12_20160101_DB');
  var $DC = $elt('tva3517bisca12_20160101_DC');
  var $DD = $elt('tva3517bisca12_20160101_DD');
  var $DE = $elt('tva3517bisca12_20160101_DE');
  var $DH = $elt('tva3517bisca12_20160101_DH');
  var $DJ = $elt('tva3517bisca12_20160101_DJ');
  var $DK = $elt('tva3517bisca12_20160101_DK');
  var $DL = $elt('tva3517bisca12_20160101_DL');
  var $DM = $elt('tva3517bisca12_20160101_DM');
  var $DN = $elt('tva3517bisca12_20160101_DN');
  var $DP = $elt('tva3517bisca12_20160101_DP');
  var $DQ = $elt('tva3517bisca12_20160101_DQ');
  var $DR = $elt('tva3517bisca12_20160101_DR');
  var $DS = $elt('tva3517bisca12_20160101_DS');
  var $DU = $elt('tva3517bisca12_20160101_DU');
  var $DV = $elt('tva3517bisca12_20160101_DV');
  var $DY = $elt('tva3517bisca12_20160101_DY');
  var $DZ = $elt('tva3517bisca12_20160101_DZ');
  var $EA = $elt('tva3517bisca12_20160101_EA');
  var $EB = $elt('tva3517bisca12_20160101_EB');
  var $EC = $elt('tva3517bisca12_20160101_EC');
  var $ED = $elt('tva3517bisca12_20160101_ED');
  var $EE = $elt('tva3517bisca12_20160101_EE');
  var $EH = $elt('tva3517bisca12_20160101_EH');
  var $EJ = $elt('tva3517bisca12_20160101_EJ');
  var $EK = $elt('tva3517bisca12_20160101_EK');
  var $EL = $elt('tva3517bisca12_20160101_EL');
  var $EM = $elt('tva3517bisca12_20160101_EM');
  var $EN = $elt('tva3517bisca12_20160101_EN');
  var $EP = $elt('tva3517bisca12_20160101_EP');
  var $EQ = $elt('tva3517bisca12_20160101_EQ');
  var $ER = $elt('tva3517bisca12_20160101_ER');
  var $ES = $elt('tva3517bisca12_20160101_ES');
  var $EU = $elt('tva3517bisca12_20160101_EU');
  var $EV = $elt('tva3517bisca12_20160101_EV');
  var $EZ = $elt('tva3517bisca12_20160101_EZ');
  var $FA = $elt('tva3517bisca12_20160101_FA');
  var $FB = $elt('tva3517bisca12_20160101_FB');
  var $FC = $elt('tva3517bisca12_20160101_FC');
  var $FD = $elt('tva3517bisca12_20160101_FD');
  var $FF = $elt('tva3517bisca12_20160101_FF');
  var $FG = $elt('tva3517bisca12_20160101_FG');
  var $GA = $elt('tva3517bisca12_20160101_GA');
  var $GB = $elt('tva3517bisca12_20160101_GB');
  var $HA = $elt('tva3517bisca12_20160101_HA');
  var $JA = $elt('tva3517bisca12_20160101_JA');
  var $JB = $elt('tva3517bisca12_20160101_JB');
  var $JC = $elt('tva3517bisca12_20160101_JC');
  var $KA = $elt('tva3517bisca12_20160101_KA');
  var $KB = $elt('tva3517bisca12_20160101_KB');
  var $KC = $elt('tva3517bisca12_20160101_KC');
  var $KD = $elt('tva3517bisca12_20160101_KD');
  var $KF = $elt('tva3517bisca12_20160101_KF');
  var $KH = $elt('tva3517bisca12_20160101_KH');
  var $LC = $elt('tva3517bisca12_20160101_LC');
  var $LD = $elt('tva3517bisca12_20160101_LD');
  var $LF = $elt('tva3517bisca12_20160101_LF');
  var $LH = $elt('tva3517bisca12_20160101_LH');
  var $LK = $elt('tva3517bisca12_20160101_LK');
  var $LM = $elt('tva3517bisca12_20160101_LM');
  var $MA = $elt('tva3517bisca12_20160101_MA');
  var $MB = $elt('tva3517bisca12_20160101_MB');
  var $MC = $elt('tva3517bisca12_20160101_MC');
  var $NA = $elt('tva3517bisca12_20160101_NA');
  var $NB = $elt('tva3517bisca12_20160101_NB');
  var $NC = $elt('tva3517bisca12_20160101_NC');
  var $ND = $elt('tva3517bisca12_20160101_ND');
  var $RC = $elt('tva3517bisca12_20160101_RC');
  var $RD = $elt('tva3517bisca12_20160101_RD');
  var $RG = $elt('tva3517bisca12_20160101_RG');
  var $RH = $elt('tva3517bisca12_20160101_RH');
  var $RJ = $elt('tva3517bisca12_20160101_RJ');
  var $RK = $elt('tva3517bisca12_20160101_RK');
  var $RM = $elt('tva3517bisca12_20160101_RM');
  var $RN = $elt('tva3517bisca12_20160101_RN');
  var $RP = $elt('tva3517bisca12_20160101_RP');
  var $RQ = $elt('tva3517bisca12_20160101_RQ');
  var $RR = $elt('tva3517bisca12_20160101_RR');
  var $RS = $elt('tva3517bisca12_20160101_RS');
  var $RT = $elt('tva3517bisca12_20160101_RT');
  var $RU = $elt('tva3517bisca12_20160101_RU');
  var $RV = $elt('tva3517bisca12_20160101_RV');
  var $RW = $elt('tva3517bisca12_20160101_RW');
  var $RX = $elt('tva3517bisca12_20160101_RX');
  var $RY = $elt('tva3517bisca12_20160101_RY');
  var $RZ = $elt('tva3517bisca12_20160101_RZ');
  var $SA = $elt('tva3517bisca12_20160101_SA');
  var $SB = $elt('tva3517bisca12_20160101_SB');
  var $SC = $elt('tva3517bisca12_20160101_SC');
  var $SD = $elt('tva3517bisca12_20160101_SD');

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
  $addition($NB, $LF, $LC, $LD, $LK, $LH, $LM, $RG, $RH, $RJ, $RK, $RM, $RN, $RP, $RQ, $RR, $RS, $RT, $RU, $RV, $RW, $RX, $RY, $RZ);
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
  $assert($isServi($elt('tva3517bisca12_20160101[AE]-0-0')) || $isServi($elt('tva3517bisca12_20160101[AE]-0-1')),
          'Champ Obligatoire',
          $elt('tva3517bisca12_20160101[AE]-0-0'), $elt('tva3517bisca12_20160101[AE]-0-1'));
};

asserts.functions.tva3517ddr_20160101 = function($elt,
                                                 $assert,
                                                 $controls,
                                                 $isServi,
                                                 $float,
                                                 $value,
                                                 $readonly,
                                                 $isSiren,
                                                 $XOR) {


  var $AA = $elt('tva3517ddr_20160101_AA');
  var $AB = $elt('tva3517ddr_20160101_AB');
  var $AC = $elt('tva3517ddr_20160101_AC');
  var $AD = $elt('tva3517ddr_20160101_AD');
  var $AE = $elt('tva3517ddr_20160101_AE');
  var $AF1 = $elt('tva3517ddr_20160101_AF1');
  var $AH = $elt('tva3517ddr_20160101_AH');
  var $AJ = $elt('tva3517ddr_20160101_AJ');
  var $AK1 = $elt('tva3517ddr_20160101_AK1');
  var $AK2 = $elt('tva3517ddr_20160101_AK2');
  var $AK3 = $elt('tva3517ddr_20160101_AK3');
  var $AK4 = $elt('tva3517ddr_20160101_AK4');
  var $BA = $elt('tva3517ddr_20160101_BA');
  var $BB = $elt('tva3517ddr_20160101_BB');


  NTD.Identif.t("hidePaiement", []);

  $readonly($AC, true);
  $readonly($AE, true);

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

  $assert(!($isServi($AK1) && !$isServi($AK3)),
          'Attention ! Veuillez préalablement servir la ligne "nom du titulaire du compte"',
          $AK1, $AK3);

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

asserts.functions.tva3517sca12_20160101 = function($elt,
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

  var $BR = $elt('tva3517sca12_20160101_BR');
  var $BT = $elt('tva3517sca12_20160101_BT');
  var $CA = $elt('tva3517sca12_20160101_CA');
  var $DA = $elt('tva3517sca12_20160101_DA');
  var $DB = $elt('tva3517sca12_20160101_DB');
  var $DC = $elt('tva3517sca12_20160101_DC');
  var $EA = $elt('tva3517sca12_20160101_EA');
  var $EB = $elt('tva3517sca12_20160101_EB');
  var $EC = $elt('tva3517sca12_20160101_EC');
  var $ED = $elt('tva3517sca12_20160101_ED');
  var $EF = $elt('tva3517sca12_20160101_EF');
  var $EG = $elt('tva3517sca12_20160101_EG');
  var $EH = $elt('tva3517sca12_20160101_EH');
  var $EJ = $elt('tva3517sca12_20160101_EJ');
  var $EL = $elt('tva3517sca12_20160101_EL');
  var $EM = $elt('tva3517sca12_20160101_EM');
  var $EN = $elt('tva3517sca12_20160101_EN');
  var $EP = $elt('tva3517sca12_20160101_EP');
  var $EQ = $elt('tva3517sca12_20160101_EQ');
  var $EU = $elt('tva3517sca12_20160101_EU');
  var $EV = $elt('tva3517sca12_20160101_EV');
  var $EW = $elt('tva3517sca12_20160101_EW');
  var $EX = $elt('tva3517sca12_20160101_EX');
  var $EY = $elt('tva3517sca12_20160101_EY');
  var $EZ = $elt('tva3517sca12_20160101_EZ');
  var $FA = $elt('tva3517sca12_20160101_FA');
  var $FB = $elt('tva3517sca12_20160101_FB');
  var $FC = $elt('tva3517sca12_20160101_FC');
  var $FD = $elt('tva3517sca12_20160101_FD');
  var $FE = $elt('tva3517sca12_20160101_FE');
  var $FF = $elt('tva3517sca12_20160101_FF');
  var $FG = $elt('tva3517sca12_20160101_FG');
  var $FJ = $elt('tva3517sca12_20160101_FJ');
  var $FL = $elt('tva3517sca12_20160101_FL');
  var $FM = $elt('tva3517sca12_20160101_FM');
  var $FN = $elt('tva3517sca12_20160101_FN');
  var $FP = $elt('tva3517sca12_20160101_FP');
  var $FR = $elt('tva3517sca12_20160101_FR');
  var $FU = $elt('tva3517sca12_20160101_FU');
  var $FV = $elt('tva3517sca12_20160101_FV');
  var $FW = $elt('tva3517sca12_20160101_FW');
  var $FY = $elt('tva3517sca12_20160101_FY');
  var $GA = $elt('tva3517sca12_20160101_GA');
  var $GB = $elt('tva3517sca12_20160101_GB');
  var $GC = $elt('tva3517sca12_20160101_GC');
  var $GF = $elt('tva3517sca12_20160101_GF');
  var $GH = $elt('tva3517sca12_20160101_GH');
  var $HA = $elt('tva3517sca12_20160101_HA');
  var $HB = $elt('tva3517sca12_20160101_HB');
  var $HC = $elt('tva3517sca12_20160101_HC');
  var $JA = $elt('tva3517sca12_20160101_JA');
  var $JB = $elt('tva3517sca12_20160101_JB');
  var $KA = $elt('tva3517sca12_20160101_KA');
  var $KB = $elt('tva3517sca12_20160101_KB');
  var $KD = $elt('tva3517sca12_20160101_KD');
  var $KE = $elt('tva3517sca12_20160101_KE');
  var $KF = $elt('tva3517sca12_20160101_KF');
  var $KG = $elt('tva3517sca12_20160101_KG');
  var $KH = $elt('tva3517sca12_20160101_KH');
  var $KJ = $elt('tva3517sca12_20160101_KJ');
  var $KL = $elt('tva3517sca12_20160101_KL');
  var $KM = $elt('tva3517sca12_20160101_KM');
  var $LA = $elt('tva3517sca12_20160101_LA');
  var $LB = $elt('tva3517sca12_20160101_LB');
  var $MA = $elt('tva3517sca12_20160101_MA');
  var $MB = $elt('tva3517sca12_20160101_MB');
  var $MD = $elt('tva3517sca12_20160101_MD');
  var $ME = $elt('tva3517sca12_20160101_ME');
  var $MF = $elt('tva3517sca12_20160101_MF');
  var $MG = $elt('tva3517sca12_20160101_MG');
  var $MH = $elt('tva3517sca12_20160101_MH');
  var $MJ = $elt('tva3517sca12_20160101_MJ');
  var $MK = $elt('tva3517sca12_20160101_MK');
  var $ML = $elt('tva3517sca12_20160101_ML');
  var $MM = $elt('tva3517sca12_20160101_MM');
  var $MN = $elt('tva3517sca12_20160101_MN');
  var $NA = $elt('tva3517sca12_20160101_NA');
  var $NB = $elt('tva3517sca12_20160101_NB');
  var $NC = $elt('tva3517sca12_20160101_NC');
  var $NL = $elt('tva3517sca12_20160101_NL');
  var $NM = $elt('tva3517sca12_20160101_NM');
  var $QA = $elt('tva3517sca12_20160101_QA');
  var $QD = $elt('tva3517sca12_20160101_QD');
  var $QE = $elt('tva3517sca12_20160101_QE');
  var $QF = $elt('tva3517sca12_20160101_QF');
  var $QH = $elt('tva3517sca12_20160101_QH');
  var $QJ = $elt('tva3517sca12_20160101_QJ');
  var $QS = $elt('tva3517sca12_20160101_QS');
  var $RA = $elt('tva3517sca12_20160101_RA');
  var $RB = $elt('tva3517sca12_20160101_RB');
  var $RC = $elt('tva3517sca12_20160101_RC');
  var $RE = $elt('tva3517sca12_20160101_RE');
  var $RF = $elt('tva3517sca12_20160101_RF');
  var $RG = $elt('tva3517sca12_20160101_RG');
  var $RH = $elt('tva3517sca12_20160101_RH');
  var $RL = $elt('tva3517sca12_20160101_RL');
  var $RN = $elt('tva3517sca12_20160101_RN');
  var $SA = $elt('tva3517sca12_20160101_SA');
  var $SB = $elt('tva3517sca12_20160101_SB');
  var $SC = $elt('tva3517sca12_20160101_SC');
  var $SD = $elt('tva3517sca12_20160101_SD');
  var $TA = $elt('tva3517sca12_20160101_TA');
  var $TB = $elt('tva3517sca12_20160101_TB');
  var $TC = $elt('tva3517sca12_20160101_TC');
  var $TD = $elt('tva3517sca12_20160101_TD');
  var $UA = $elt('tva3517sca12_20160101_UA');
  var $UB = $elt('tva3517sca12_20160101_UB');
  var $UC = $elt('tva3517sca12_20160101_UC');
  var $UD = $elt('tva3517sca12_20160101_UD');
  var $VA = $elt('tva3517sca12_20160101_VA');
  var $VC = $elt('tva3517sca12_20160101_VC');
  var $VE = $elt('tva3517sca12_20160101_VE');
  var $VF = $elt('tva3517sca12_20160101_VF');
  var $VG = $elt('tva3517sca12_20160101_VG');
  var $VH = $elt('tva3517sca12_20160101_VH');
  var $VJ = $elt('tva3517sca12_20160101_VJ');
  var $VK = $elt('tva3517sca12_20160101_VK');
  var $VL = $elt('tva3517sca12_20160101_VL');
  var $VM = $elt('tva3517sca12_20160101_VM');
  var $VN = $elt('tva3517sca12_20160101_VN');
  var $VP = $elt('tva3517sca12_20160101_VP');
  var $VS = $elt('tva3517sca12_20160101_VS');
  var $VT = $elt('tva3517sca12_20160101_VT');
  var $VW = $elt('tva3517sca12_20160101_VW');
  var $VX = $elt('tva3517sca12_20160101_VX');
  var $VY = $elt('tva3517sca12_20160101_VY');
  var $VZ = $elt('tva3517sca12_20160101_VZ');
  var $WB = $elt('tva3517sca12_20160101_WB');
  var $WC = $elt('tva3517sca12_20160101_WC');
  var $WD = $elt('tva3517sca12_20160101_WD');
  var $WE = $elt('tva3517sca12_20160101_WE');
  var $WF = $elt('tva3517sca12_20160101_WF');
  var $WG = $elt('tva3517sca12_20160101_WG');
  var $WH = $elt('tva3517sca12_20160101_WH');
  var $WJ = $elt('tva3517sca12_20160101_WJ');
  var $WK = $elt('tva3517sca12_20160101_WK');
  var $WL = $elt('tva3517sca12_20160101_WL');
  var $WM = $elt('tva3517sca12_20160101_WM');
  var $WN = $elt('tva3517sca12_20160101_WN');
  var $WP = $elt('tva3517sca12_20160101_WP');
  var $WQ = $elt('tva3517sca12_20160101_WQ');
  var $WR = $elt('tva3517sca12_20160101_WR');
  var $WS = $elt('tva3517sca12_20160101_WS');
  var $WT = $elt('tva3517sca12_20160101_WT');
  var $WU = $elt('tva3517sca12_20160101_WU');
  var $WV = $elt('tva3517sca12_20160101_WV');
  var $WX = $elt('tva3517sca12_20160101_WX');
  var $WY = $elt('tva3517sca12_20160101_WY');
  var $WZ = $elt('tva3517sca12_20160101_WZ');
  var $ZA = $elt('tva3517sca12_20160101_ZA');
  var $ZB = $elt('tva3517sca12_20160101_ZB');


  var $requiredFields = [
    $DA, $DB, $DC, $EA, $EB, $EC, $ED, $EF,
    $EG, $EH, $EJ, $EL, $EM, $EN, $EP, $EQ, $EU, $EV, $EW,
    $EX, $EY, $EZ, $FA, $FB, $FC, $FD, $FF, $FG, $FJ,
    $FL, $FM, $FN, $FP, $FR, $FU, $FV, $FW, $FY, $GA, $GB,
    $GC, $GF, $GH, $HA, $HB, $HC, $JA, $KA, $KB, $KD,
    $KL, $KM, $LA, $LB, $MA,
    $MM, $MN, $NA,
    $NB, $NC, $QA, $QD, $QE, $QF, $QH, $QJ, $QS,
    $RA, $RB, $RC, $RE, $RF, $RG, $RH, $RL, $RN,
    $SA, $SB, $SC,
    $VA, $VC, $VE, $VF, $VJ, $VM, $VN, $VP,
    $VS, $VT, $VW, $VX, $VY, $VZ];
  var $emptiableFields = [
    $DA, $DB, $DC, $EA, $EB, $EC, $ED, $EF,
    $EG, $EH, $EJ, $EL, $EM, $EN, $EP, $EQ, $EU, $EV, $EW,
    $EX, $EY, $EZ, $FA, $FB, $FC, $FD, $FE, $FF, $FG, $FJ,
    $FL, $FM, $FN, $FP, $FR, $FU, $FV, $FW, $FY, $GA, $GB,
    $GC, $GF, $GH, $HA, $HB, $HC, $JA, $JB, $KA, $KB, $KD,
    $KL, $KM, $LA, $LB, $MA,
    $MD, $ME, $MF, $MG, $MH, $MJ, $MK, $ML, $MM, $MN, $NA,
    $NB, $NC, $QA, $QD, $QE, $QF, $QH, $QJ, $QS,
    $RA, $RB, $RC, $RE, $RF, $RG, $RH, $RL, $RN,
    $SA, $SB, $SC, $TA, $TB, $TC, $TD, $UA, $UB, $UC, $UD,
    $VA, $VC, $VE, $VF, $VJ, $VL, $VM, $VN, $VP,
    $VS, $VT, $VW, $VX, $VY, $VZ];
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
            $DA, $DB, $DC,
            $KL, $KM,
            $QA, $QD, $QE, $QF, $QH, $QJ, $QS,
            $RF, $RG, $RH, $RL, $RN,
            $VC, $VE, $VF, $VJ, $VW, $VX, $VY, $VZ,
            $WB, $WC, $WD, $WE, $WF, $WG, $WH, $WJ, $WK, $WL, $WM, $WN, $WP, $WQ, $WR, $WS, $WT, $WU, $WV,
            $ZB);

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

  $controls.erreur_226($UA, $TA);
  $controls.erreur_226($UB, $TB);
  $controls.erreur_226($UC, $TC);
  $controls.erreur_226($UD, $TD);

  $controls.erreur_134($UA, $elt(NTD.Identif.tField('CA')), $elt(NTD.Identif.tField('CB')));
  $controls.erreur_134($UB, $elt(NTD.Identif.tField('CA')), $elt(NTD.Identif.tField('CB')));
  $controls.erreur_134($UC, $elt(NTD.Identif.tField('CA')), $elt(NTD.Identif.tField('CB')));
  $controls.erreur_134($UD, $elt(NTD.Identif.tField('CA')), $elt(NTD.Identif.tField('CB')));


  $controls.erreur_042($SD, $requiredFields);
  $controls.erreur_049($SD, $requiredFields);
};

asserts.functions.tva3519_20160101 = function($elt,
                                              $assert,
                                              $controls,
                                              $isServi,
                                              $float,
                                              $value,
                                              $readonly,
                                              $isSiren,
                                              $XOR) {

  var $CB = $elt(NTD.Identif.tField('CB'));
  var $AA1 = $elt('tva3519_20160101_AA1');
  var $AA2 = $elt('tva3519_20160101_AA2');
  var $AA3 = $elt('tva3519_20160101_AA3');
  var $AA4 = $elt('tva3519_20160101_AA4');
  var $DC1 = $elt('tva3519_20160101_DC1');
  var $DC10 = $elt('tva3519_20160101_DC10');
  var $DC2 = $elt('tva3519_20160101_DC2');
  var $DC3 = $elt('tva3519_20160101_DC3');
  var $DC4 = $elt('tva3519_20160101_DC4');
  var $DC5 = $elt('tva3519_20160101_DC5');
  var $DC6 = $elt('tva3519_20160101_DC6');
  var $DC7 = $elt('tva3519_20160101_DC7');
  var $DC8 = $elt('tva3519_20160101_DC8');
  var $DC9 = $elt('tva3519_20160101_DC9');
  var $DD = $elt('tva3519_20160101_DD');
  var $DE = $elt('tva3519_20160101_DE');
  var $DF = $elt('tva3519_20160101_DF');
  var $DG1 = $elt('tva3519_20160101_DG1');
  var $DG2 = $elt('tva3519_20160101_DG2');
  var $DG3 = $elt('tva3519_20160101_DG3');
  var $DG4 = $elt('tva3519_20160101_DG4');
  var $DH = $elt('tva3519_20160101_DH');
  var $DI = $elt('tva3519_20160101_DI');
  var $DJ = $elt('tva3519_20160101_DJ');
  var $DK = $elt('tva3519_20160101_DK');
  var $DL = $elt('tva3519_20160101_DL');
  var $DM = $elt('tva3519_20160101_DM');
  var $DN = $elt('tva3519_20160101_DN');
  var $FJ = $elt('tva3519_20160101_FJ');
  var $FK = $elt('tva3519_20160101_FK');
  var $FL = $elt('tva3519_20160101_FL');

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

  $assert(!($isServi($AA1) && !$isServi($AA2)), 'Vous devez saisir l\'IBAN', $AA1, $AA2);
  $assert(!($isServi($AA2) && !$isServi($AA3)), 'Attention ! Veuillez préalablement servir la ligne "nom du titulaire du compte"', $AA2, $AA3);


  var $assert_DC1_DC4 = ($isServi($DC1) || $isServi($DC4))
                        && (!$isServi($DC2) || !$isServi($DC3) || !$isServi($DC6) || !$isServi($DC7) || !$isServi($DC8) || !$isServi($DC9) || !$isServi($DC10));

  var $assert_DC1_DC4_message = 'Attention ! Veuillez renseigner le cadre "Adresse de correspondance", '
                                + 'si celle-ci est différente de celle de l’établissement principal ou si la demande est effectuée par un représentant fiscal ou '
                                + 'le mandataire-liquidateur de l’entreprise';

  $assert(!($assert_DC1_DC4),
          $assert_DC1_DC4_message,
          $DC1, $DC2, $DC3, $DC4, $DC6, $DC7, $DC8, $DC9, $DC10);
};

asserts.functions.tva3525bis_20160101 = function($elt,
                                                 $assert,
                                                 $controls,
                                                 $isServi,
                                                 $float,
                                                 $value,
                                                 $readonly,
                                                 $isSiren,
                                                 $XOR) {

  var $AC = $elt('tva3525bis_20160101_AC');
  var $AD = $elt('tva3525bis_20160101_AD');
  var $BB = $elt('tva3525bis_20160101_BB');
  var $BC = $elt('tva3525bis_20160101_BC');
  var $BD = $elt('tva3525bis_20160101_BD');
  var $BE = $elt('tva3525bis_20160101_BE');
  var $DA = $elt('tva3525bis_20160101_DA');

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


asserts.functions.is2571_2016 = function($elt,
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

  var $FA = $elt('is2571_2016_FA');
  var $CA = $elt('is2571_2016_CA');
  var $DA = $elt('is2571_2016_DA');
  var $FB = $elt('is2571_2016_FB');
  var $FC = $elt('is2571_2016_FC');
  var $FD = $elt('is2571_2016_FD');
  var $FE = $elt('is2571_2016_FE');
  var $FF = $elt('is2571_2016_FF');
  var $FG = $elt('is2571_2016_FG');
  var $CF = $elt('is2571_2016_CF');
  var $CC = $elt('is2571_2016_CC');
  var $CD = $elt('is2571_2016_CD');
  var $DB = $elt('is2571_2016_DB');
  var $CE = $elt('is2571_2016_CE');
  var $CG = $elt('is2571_2016_CG');
  var $CH = $elt('is2571_2016_CH');
  var $FH = $elt('is2571_2016_FH');
  var $FK = $elt('is2571_2016_FK');
  var $FM = $elt('is2571_2016_FM');
  var $FN = $elt('is2571_2016_FN');

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

asserts.functions.is2572_2016 = function($elt,
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

  var $AD = $elt('is2572_2016_AD');
  var $BD = $elt('is2572_2016_BD');
  var $CA = $elt('is2572_2016_CA');
  var $DA = $elt('is2572_2016_DA');
  var $EA = $elt('is2572_2016_EA');
  var $EB = $elt('is2572_2016_EB');
  var $GC = $elt('is2572_2016_GC');
  var $GD = $elt('is2572_2016_GD');
  var $GE = $elt('is2572_2016_GE');
  var $IA = $elt('is2572_2016_IA');
  var $JA = $elt('is2572_2016_JA');
  var $KA = $elt('is2572_2016_KA');
  var $KB = $elt('is2572_2016_KB');
  var $KC = $elt('is2572_2016_KC');
  var $KD = $elt('is2572_2016_KD');
  var $LA = $elt('is2572_2016_LA');
  var $LB = $elt('is2572_2016_LB');
  var $LC = $elt('is2572_2016_LC');
  var $LD = $elt('is2572_2016_LD');
  var $LE = $elt('is2572_2016_LE');
  var $LF = $elt('is2572_2016_LF');
  var $MA = $elt('is2572_2016_MA');
  var $MB = $elt('is2572_2016_MB');
  var $MC = $elt('is2572_2016_MC');
  var $MD = $elt('is2572_2016_MD');
  var $ME = $elt('is2572_2016_ME');
  var $NA = $elt('is2572_2016_NA');
  var $NB = $elt('is2572_2016_NB');
  var $NC = $elt('is2572_2016_NC');
  var $ND = $elt('is2572_2016_ND');
  var $NE = $elt('is2572_2016_NE');
  var $NF = $elt('is2572_2016_NF');
  var $NG = $elt('is2572_2016_NG');
  var $NJ = $elt('is2572_2016_NJ');
  var $NK = $elt('is2572_2016_NK');
  var $NL = $elt('is2572_2016_NL');
  var $NM = $elt('is2572_2016_NM');
  var $NN = $elt('is2572_2016_NN');
  var $NO = $elt('is2572_2016_NO');
  var $OB = $elt('is2572_2016_OB');
  var $OC = $elt('is2572_2016_OC');
  var $OD = $elt('is2572_2016_OD');
  var $OE = $elt('is2572_2016_OE');
  var $OF = $elt('is2572_2016_OF');
  var $OG = $elt('is2572_2016_OG');
  var $OH = $elt('is2572_2016_OH');
  var $OJ = $elt('is2572_2016_OJ');
  var $PA = $elt('is2572_2016_PA');
  var $PB = $elt('is2572_2016_PB');
  var $PC = $elt('is2572_2016_PC');
  var $PD = $elt('is2572_2016_PD');
  var $PE = $elt('is2572_2016_PE');
  var $PF = $elt('is2572_2016_PF');
  var $PG = $elt('is2572_2016_PG');
  var $PH = $elt('is2572_2016_PH');
  var $PJ = $elt('is2572_2016_PJ');
  var $PK = $elt('is2572_2016_PK');
  var $PL = $elt('is2572_2016_PL');
  var $PM = $elt('is2572_2016_PM');
  var $PN = $elt('is2572_2016_PN');
  var $PQ = $elt('is2572_2016_PQ');
  var $PR = $elt('is2572_2016_PR');
  var $PS = $elt('is2572_2016_PS');
  var $PT = $elt('is2572_2016_PT');
  var $PU = $elt('is2572_2016_PU');
  var $PV = $elt('is2572_2016_PV');
  var $PW = $elt('is2572_2016_PW');
  var $RA = $elt('is2572_2016_RA');
  var $RB = $elt('is2572_2016_RB');
  var $RC = $elt('is2572_2016_RC');
  var $RD = $elt('is2572_2016_RD');
  var $RE = $elt('is2572_2016_RE');
  var $RF = $elt('is2572_2016_RF');
  var $RG = $elt('is2572_2016_RG');
  var $RH = $elt('is2572_2016_RH');
  var $RJ = $elt('is2572_2016_RJ');
  var $RK = $elt('is2572_2016_RK');
  var $RL = $elt('is2572_2016_RL');
  var $RM = $elt('is2572_2016_RM');
  var $RN = $elt('is2572_2016_RN');
  var $RP = $elt('is2572_2016_RP');
  var $RR = $elt('is2572_2016_RR');
  var $RS = $elt('is2572_2016_RS');
  var $RT = $elt('is2572_2016_RT');
  var $RU = $elt('is2572_2016_RU');
  var $RV = $elt('is2572_2016_RV');
  var $RW = $elt('is2572_2016_RW');
  var $RX = $elt('is2572_2016_RX');
  var $RY = $elt('is2572_2016_RY');
  var $RZ = $elt('is2572_2016_RZ');
  var $TA = $elt('is2572_2016_TA');
  var $TB = $elt('is2572_2016_TB');

  $percent($TA, $RA, 100 / 3);
  $percent($TB, $RB, 15);
  $readonly($GE, true);
  $addition($GE, $TA, $TB, $GC, $GD);
  $readonly($RG, true);
  $addition($RG, $JA, $MA, $MC, $MD);
  $readonly($RH, true);
  $soustraction($RH, $GE, $RG);


  // Calcul RP
  $readonly($RP, true);
  var RPFIelds = [$LC, $RJ, $LF, $OH, $RN, $OB, $RK, $RL, $LA, $RM, $OC];
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
    var value = ($float($LE) <= $float($LF)) ? $float($LE) : $float($LF);
    value = isNaN(value) ? 0 : value;
    RPTotal -= value;
  }
  if ($isServi($OJ) && $float($OJ) >= 0) {
    if (RPTotal === '') {
      RPTotal = 0;
    }
    var value = ($float($OJ) <= $float($OH)) ? $float($OJ) : $float($OH);
    value = isNaN(value) ? 0 : value;
    RPTotal -= value;
  }
  $value($RP, (RPTotal === '') ? '' : Math.max(0, RPTotal));


  // Calcul RE
  $readonly($RE, true);
  var REFIelds = [$KA, $NA, $KB, $NC, $KC, $NC, $ND, $NE, $NF, $NG, $RC, $NJ, $NK, $NL, $NM, $NN, $OD, $KD, $OF, $NO];
  var RETotal = '';
  for (var i = 0; i < REFIelds.length; i++) {
    if ($isServi(REFIelds[i]) && $float(REFIelds[i]) >= 0) {
      if (RETotal === '') {
        RETotal = 0;
      }
      RETotal += $float(REFIelds[i]);
    }
  }
  if ($isServi($OE) && $float($OE) >= 0) {
    if (RETotal === '') {
      RETotal = 0;
    }
    var value = ($float($OE) <= $float($KD)) ? $float($OE) : $float($KD);
    value = isNaN(value) ? 0 : value;
    RETotal -= value;
  }
  if ($isServi($OG) && $float($OG) >= 0) {
    if (RETotal === '') {
      RETotal = 0;
    }
    var value = ($float($OG) <= $float($OF)) ? $float($OG) : $float($OF);
    value = isNaN(value) ? 0 : value;
    RETotal -= value;
  }
  $value($RE, (RETotal === '') ? '' : Math.max(0, RETotal));


  $readonly($RS, true);
  $soustraction($RS, $RH, $RP);

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


  var $PidentifKF = $elt(NTD.Identif.pField('KF'));
  var $date_PJ = $value($PJ).split('/');
  $date_PJ = new Date($date_PJ[2], $date_PJ[1] - 1, $date_PJ[0]);
  var $date_KF = $value($PidentifKF).split('/');
  $date_KF = new Date($date_KF[1], $date_KF[0] - 1, '01');
  var $date_KF_inf_datePJ = $date_PJ.getTime() < $date_KF.getTime();

  $assert(!($isServi($PJ) && $isServi($PidentifKF) && !($date_KF_inf_datePJ)), 'erreur_318', $PJ);


  $isServi_PH_PK_PJ = ( $isServi($PH) && (!$isServi($PK) || !$isServi($PJ)) )
                      || ( $isServi($PK) && (!$isServi($PH) || !$isServi($PJ)) )
                      || ( $isServi($PJ) && (!$isServi($PH) || !$isServi($PK)) );

  $assert(!$isServi_PH_PK_PJ, 'erreur_310', $PH, $PK, $PJ);

  $isServi_PE_PG_PF = ( $isServi($PE) && (!$isServi($PG) || !$isServi($PF)) )
                      || ( $isServi($PG) && (!$isServi($PE) || !$isServi($PF)) )
                      || ( $isServi($PF) && (!$isServi($PE) || !$isServi($PG)) );

  $assert(!$isServi_PE_PG_PF, 'erreur_310', $PE, $PG, $PF);


  $assert(!($isServi($LC) && $isServi($LD) && !($float($LD) <= $float($LC))), 'erreur_316', $LD);
  $assert(!($isServi($CA) && $isServi($PK) && $float($CA) > 0 && $float($PK) > 0 && !($float($CA) >= $float($PK))), 'erreur_311', $PK);
  $assert(!($isServi($EA) && $float($EA) > 0 && !($isServi($DA) && $float($EA) <= $float($DA))), 'erreur_311', $EA);

  var $DAminusEA = 0;
  if ($isServi($DA)) {
    $DAminusEA = $float($DA);
  }
  if ($isServi($EA)) {
    $DAminusEA -= $float($EA);
  }
  $assert(!($isServi($DA) && $float($DA) > 0 && $isServi($PG) && $float($PG) >= 0 && !($DAminusEA >= $float($PG))), 'erreur_319', $PG);
};

asserts.functions.is2573_2016 = function($elt,
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

  var $AA = $elt('is2573_2016_AA');
  var $BA = $elt('is2573_2016_BA');
  var $CA = $elt('is2573_2016_CA');
  var $rowIndex;

  NTD.Identif.p("hidePaiement", []);

  // for each row
  $rowIndex = 1;
  while ($elt('is2573_2016_AB/' + $rowIndex)) {
    var $AB = $elt('is2573_2016_AB/'+$rowIndex);
    var $AC = $elt('is2573_2016_AC/'+$rowIndex);
    var $AF = $elt('is2573_2016_AF/'+$rowIndex);
    var $AG = $elt('is2573_2016_AG/'+$rowIndex);
    var $AH = $elt('is2573_2016_AH/'+$rowIndex);
    var $AI = $elt('is2573_2016_AI/'+$rowIndex);
    var $KA = $elt('is2573_2016_KA/'+$rowIndex);
    var $KB = $elt('is2573_2016_KB/'+$rowIndex);
    var $KC = $elt('is2573_2016_KC/'+$rowIndex);
    var $KD = $elt('is2573_2016_KD/'+$rowIndex);

    $assert($value($AB) != 'REL' && $value($AB) != 'RES', 'erreur_309', $AB);
    $assert(!(($isServi($AB) || $isServi($AC) || $isServi($AF) || $isServi($AG) || $isServi($AH) || $isServi($AI))
            && !($isServi($AB) && $isServi($AC) && $isServi($AG) && $float($AG) > 0)),
            'erreur_315', $AB, $AC, $AF, $AG, $AH, $AI);
    $assert(!($isServi($AF) && !($value($AB) == 'RAD' && $isServi($AH))), 'erreur_313', $AF, $AB, $AH);
    $assert(!($isServi($AH) && !$isServi($AI)), 'erreur_305', $AI);
    $assert(!($isServi($AI) && !$isServi($AH)), 'erreur_305', $AH);

    var $date_KC = $value($KC).split('/');
    $date_KC = new Date($date_KC[2] + '-' + $date_KC[1] + '-' + $date_KC[0] + 'T23:59:59');
    $assert(!( $isServi($KC) && ($date_KC < new Date()) ), 'erreur_320', $KC);

    $isServi_KB_KC_KD = ( $isServi($KB) && (!$isServi($KC) || !$isServi($KD)) )
                        || ( $isServi($KC) && (!$isServi($KB) || !$isServi($KD)) )
                        || ( $isServi($KD) && (!$isServi($KB) || !$isServi($KC)) );

    $assert(!$isServi_KB_KC_KD, 'erreur_321', $KB, $KC, $KD);

    $assert(!($isServi($KD) && $isServi($AG) && !($float($KD) <= $float($AG))), 'erreur_314', $KD);
    $rowIndex++;
  }

  // for each row
  $rowIndex = 1;
  while ($elt('is2573_2016_BB/' + $rowIndex)) {
    var $BB = $elt('is2573_2016_BB/'+$rowIndex);
    var $BC = $elt('is2573_2016_BC/'+$rowIndex);
    var $BD = $elt('is2573_2016_BD/'+$rowIndex);
    var $BE = $elt('is2573_2016_BE/'+$rowIndex);


    $assert(!(($isServi($BB) || $isServi($BC) || $isServi($BD) || $isServi($BE))
            && !($isServi($BB) && $isServi($BC) && $isServi($BE) && $float($BE) > 0)),
            'erreur_307', $BB, $BC, $BD, $BE);
    $rowIndex++;
  }

  // for each row
  $rowIndex = 1;
  while ($elt('is2573_2016_CB/' + $rowIndex)) {
    var $CB = $elt('is2573_2016_CB/'+$rowIndex);
    var $CC = $elt('is2573_2016_CC/'+$rowIndex);
    var $CD = $elt('is2573_2016_CD/'+$rowIndex);
    var $CE = $elt('is2573_2016_CE/'+$rowIndex);
    var $CF = $elt('is2573_2016_CF/'+$rowIndex);


    $assert(!(($isServi($CB) || $isServi($CC) || $isServi($CD) || $isServi($CE) || $isServi($CF))
            && !($isServi($CB) && $isServi($CC) && $isServi($CD) && $isServi($CF) && $float($CF) > 0)),
            'erreur_308', $CB, $CC, $CD, $CF);
    $rowIndex++;
  }
};


asserts.functions.cvae1329ac_20160101 = function($elt,
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
  var $AA = $elt('cvae1329ac_20160101_AA');
  var $AB = $elt('cvae1329ac_20160101_AB');
  var $AC = $elt('cvae1329ac_20160101_AC');
  var $AD = $elt('cvae1329ac_20160101_AD');
  var $BA = $elt('cvae1329ac_20160101_BA');
  var $BB = $elt('cvae1329ac_20160101_BB');
  var $BC = $elt('cvae1329ac_20160101_BC');
  var $CA = $elt('cvae1329ac_20160101_CA');
  var $CB = $elt('cvae1329ac_20160101_CB');
  var $DA = $elt('cvae1329ac_20160101_DA');
  var $DB = $elt('cvae1329ac_20160101_DB');
  var $EA = $elt('cvae1329ac_20160101_EA');
  var $EB = $elt('cvae1329ac_20160101_EB');
  var $EC = $elt('cvae1329ac_20160101_EC');
  var $ED = $elt('cvae1329ac_20160101_ED');
  var $GA = $elt('cvae1329ac_20160101_GA');
  var $GB = $elt('cvae1329ac_20160101_GB');
  var $HA = $elt('cvae1329ac_20160101_HA');
  var $KA = $elt('cvae1329ac_20160101_KA');
  var $KACheckbox = $elt('cvae1329ac_20160101_KA_checkbox');
  var $KF_month = $elt(NTD.Identif.pField('KF')+'-month');



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

  $readonly($CA, true);
  $value($CA, '');

  if ($isServi($AC)) {
    if ($float($BA) <= $float($BB) && !$isServi($BC)) {
      $value($CA, Math.round(($float($BA) * $float($AC)) / 100));
    }
    else if ($float($BA) > $float($BB) && !$isServi($BC)) {
      $value($CA, Math.round(($float($BB) * $float($AC)) / 100));
    }
    else if ($isServi($BC)) {
      $value($CA, Math.round(($float($BA) * $float($AC)) / 100));
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
  else if ($isServi($EA) && !$isServi($EB) && !$isServi($EC)) {
    $value($ED, Math.max(0, $float($EA)));
  }

  $readonly($GB, true);
  $value($GB, 0);
  if(!$isServi($GA)) {
    $percent($GB, $ED, 3.22);
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

  $assert($isServi($AA) && $float($AA) >= 152500, 'cvae_erreur_202', $AA);
  $assert(!($isServi($AB) && $float($AB) > 0 && !($isServi($AA) && $float($AA) > 0)), 'cvae_erreur_205', $AB);
  $assert(!($isServi($AD) && $float($AD) > 0 && !($isServi($AA) && $float($AD) >= $float($AA))), 'cvae_erreur_206', $AD);
  $assert(!($isServi($EB) && $isServi($EC) && $float($EB) > 0 && $float($EC) > 0), 'cvae_erreur_207', $EB, $EC);

  $KF_month_value = parseInt($value($KF_month));
  $assert(!($KF_month_value == 6  && ($isServi($EB) || $isServi($EC))), 'cvae_erreur_208', $EB, $EC);
};

asserts.functions.cvae1329def_20160101 = function($elt,
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
  var $AA = $elt('cvae1329def_20160101_AA');
  var $AB = $elt('cvae1329def_20160101_AB');
  var $AC = $elt('cvae1329def_20160101_AC');
  var $AD = $elt('cvae1329def_20160101_AD');
  var $BA = $elt('cvae1329def_20160101_BA');
  var $BB = $elt('cvae1329def_20160101_BB');
  var $BC = $elt('cvae1329def_20160101_BC');
  var $CA = $elt('cvae1329def_20160101_CA');
  var $CB = $elt('cvae1329def_20160101_CB');
  var $DA = $elt('cvae1329def_20160101_DA');
  var $DB = $elt('cvae1329def_20160101_DB');
  var $EA = $elt('cvae1329def_20160101_EA');
  var $EB = $elt('cvae1329def_20160101_EB');
  var $EC = $elt('cvae1329def_20160101_EC');
  var $ED = $elt('cvae1329def_20160101_ED');
  var $GA = $elt('cvae1329def_20160101_GA');
  var $GB = $elt('cvae1329def_20160101_GB');
  var $GC = $elt('cvae1329def_20160101_GC');
  var $GD = $elt('cvae1329def_20160101_GD');
  var $GE = $elt('cvae1329def_20160101_GE');
  var $HA = $elt('cvae1329def_20160101_HA');
  var $HB = $elt('cvae1329def_20160101_HB');
  var $HC = $elt('cvae1329def_20160101_HC');
  var $HD = $elt('cvae1329def_20160101_HD');
  var $JA = $elt('cvae1329def_20160101_JA');
  var $JE = $elt('cvae1329def_20160101_JE');
  var $JK = $elt('cvae1329def_20160101_JK');
  var $KA = $elt('cvae1329def_20160101_KA');
  var $KB = $elt('cvae1329def_20160101_KB');

  // TODO : ligne manquante 19


  $readonly($AC, true);
  $value($AC, '');


  // Si  AD est valorisé et >0
  //     Si 0 < AD < 500 000 Alors AC=0
  //     Sinon si 500 000 € < = AD < = 3 000 000 €, alors (AC = [0,5 x (AD) - 500 000)] / 2 500 000
  //     Sinon si 3 000 000 € < AD) < = 10 000 000 €, alors AC = 0,5 + [0,9 x AD - 3 000 000)] / 7 000 000
  //     Sinon si 10 000 000 € < AD < = 50 000 000 €, alors (AC) = 1,4 + [0,1 x (AD) - 10 000 000) / 40 000 000
  //     Sinon si AD > 50 000 000 €, alors AC = 1,5
  // Sinon  AD est valorisé à zéro ou vide Alors
  //     Si AA<152500 Alors AC=0
  //     Si 500 000 € < =AA < = 3 000 000 €, alors (AC = [0,5 x (AA - 500 000) / 2 500 000
  //     Sinon si 3 000 000 € < AA < = 10 000 000 €,
  //          alors AC = 0,5 + [0,9 x (AA - 3 000 000] / 7 000 000
  //     Sinon si 10 000 000 € < AA< = 50 000 000 €,
  //          alors (AC) = 1,4 + [0,1 x (AA - 10 000 000)] / 40 000 000
  //     Sinon si AA > 50 000 000 €, alors (AC) = 1,5

  $AC_value = 0;
  if ($float($AA) < 152500) {
    $AC_value = 0;
  }
  else {
    if ($isServi($AD) && $float($AD) > 0) {
      if ($float($AD) > 0 && $float($AD) < 500000) {
        $AC_value = 0;
      }
      else if (500000 <= $float($AD) && $float($AD) <= 3000000) {
        $AC_value = (0.5 * (($float($AD) - 500000) / 2500000)).toFixed(2);
      }
      else if (3000000 < $float($AD) && $float($AD) <= 10000000) {
        $AC_value = (0.5 + 0.9 * (($float($AD) - 3000000) / 7000000)).toFixed(2);
      }
      else if (10000000 < $float($AD) && $float($AD) <= 50000000) {
        $AC_value = (1.4 + 0.1 * (($float($AD) - 10000000) / 40000000)).toFixed(2);
      }
      else if ($float($AD) > 50000000) {
        $AC_value = 1.5;
      }
    }

    else {
      if ($float($AA) < 152500) {
        $AC_value = 0;
      }
      else if (500000 <= $float($AA) && $float($AA) <= 3000000) {
        $AC_value = (0.5 * (($float($AA) - 500000) / 2500000)).toFixed(2);
      }
      else if (3000000 < $float($AA) && $float($AA) <= 10000000) {
        $AC_value = (0.5 + 0.9 * (($float($AA) - 3000000) / 7000000)).toFixed(2);
      }
      else if (10000000 < $float($AA) && $float($AA) <= 50000000) {
        $AC_value = (1.4 + 0.1 * (($float($AA) - 10000000) / 40000000)).toFixed(2);
      }
      else if ($float($AA) > 50000000) {
        $AC_value = 1.5;
      }
    }
  }
  $value($AC, $AC_value);


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
    $percent($GB, $EA, 3.93);
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
