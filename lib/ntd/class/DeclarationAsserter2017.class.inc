<?php

/** Millésime 2017 **/

class DeclarationAsserter2017 extends DeclarationAsserter {
  public static function f_identif_20170101($elt, $assert, $isServi, $float, $value, $controls) {
    // Rien sur le millésime 2017
  }

  public static function f_identif_20170101v2($elt, $assert, $isServi, $float, $value, $controls) {
    $AA = $elt('f_identif_20170101v2_AA');
    $AA1 = $elt('f_identif_20170101v2_AA1');
    $AA13 = $elt('f_identif_20170101v2_AA13');
    $AA2 = $elt('f_identif_20170101v2_AA2');
    $AA3 = $elt('f_identif_20170101v2_AA3');
    $AA4 = $elt('f_identif_20170101v2_AA4');
    $AA5 = $elt('f_identif_20170101v2_AA5');
    $AA6 = $elt('f_identif_20170101v2_AA6');
    $AA7 = $elt('f_identif_20170101v2_AA7');
    $AA8 = $elt('f_identif_20170101v2_AA8');
    $AB = $elt('f_identif_20170101v2_AB');
    $AC13 = $elt('f_identif_20170101v2_AC13');
    $AC2 = $elt('f_identif_20170101v2_AC2');
    $AC3 = $elt('f_identif_20170101v2_AC3');
    $AC4 = $elt('f_identif_20170101v2_AC4');
    $BA = $elt('f_identif_20170101v2_BA');
    $BB = $elt('f_identif_20170101v2_BB');
    $BC = $elt('f_identif_20170101v2_BC');
    $BD = $elt('f_identif_20170101v2_BD');
    $BF = $elt('f_identif_20170101v2_BF');
    $CA = $elt('f_identif_20170101v2_CA');
    $CB = $elt('f_identif_20170101v2_CB');
    $CC = $elt('f_identif_20170101v2_CC');
    $CD = $elt('f_identif_20170101v2_CD');
    $CE = $elt('f_identif_20170101v2_CE');
    $DA = $elt('f_identif_20170101v2_DA');
    $DC = $elt('f_identif_20170101v2_DC');
    $IDOGA = $elt('f_identif_20170101v2_IDOGA');
    $KD = $elt('f_identif_20170101v2_KD');
    $OGA = $elt('f_identif_20170101v2_OGA');

    $CA_value = $isServi($CA) ? Date::toDb($value($CA)) : ''; // DD/MM/YYYY
    $CB_value = $isServi($CB) ? Date::toDb($value($CB)) : ''; // DD/MM/YYYY

    $CB_value_year = (int)date('Y', strtotime($CB_value));

    // field BF : DPR => Dépôt provisoire
    $assert(!(($isServi($CB) && Date::isValid($CB_value)) && ($value($BF) != 'DPR' && $CB_value_year < 1992)),
      'Ce millésime doit être compris entre 1992 et le millésime de l’année civile en cours',
      $CB);


    $CA_date = date_create($CA_value);
    $CB_date = date_create($CB_value);

    $diff = date_diff($CA_date, $CB_date);
    $diff_month = $diff->y * 12 + $diff->m;

    $assert(!(($isServi($CB) && Date::isValid($CB_value) && $isServi($CA) && Date::isValid($CA_value)) && ($diff_month > 24)),
      'la durée de l’exercice doit est inférieur ou égale à 24 mois',
      $CB);
  }

  public static function tva3310a_20170101($elt, $assert, $isServi, $float, $value, $controls) {
    // $AE = $elt('tva3310a_20170101_AE');
    // $AF = $elt('tva3310a_20170101_AF');
    $BA = $elt('tva3310a_20170101_BA');
    $BB = $elt('tva3310a_20170101_BB');
    $BC = $elt('tva3310a_20170101_BC');
    $BE = $elt('tva3310a_20170101_BE');
    $BF = $elt('tva3310a_20170101_BF');
    $BK = $elt('tva3310a_20170101_BK');
    $BM = $elt('tva3310a_20170101_BM');
    $BN = $elt('tva3310a_20170101_BN');
    $BP = $elt('tva3310a_20170101_BP');
    $BQ = $elt('tva3310a_20170101_BQ');
    $BR = $elt('tva3310a_20170101_BR');
    $BS = $elt('tva3310a_20170101_BS');
    $CA = $elt('tva3310a_20170101_CA');
    $CB = $elt('tva3310a_20170101_CB');
    $CC = $elt('tva3310a_20170101_CC');
    $CE = $elt('tva3310a_20170101_CE');
    $CF = $elt('tva3310a_20170101_CF');
    $CK = $elt('tva3310a_20170101_CK');
    $CM = $elt('tva3310a_20170101_CM');
    $CN = $elt('tva3310a_20170101_CN');
    $CP = $elt('tva3310a_20170101_CP');
    $CQ = $elt('tva3310a_20170101_CQ');
    $CR = $elt('tva3310a_20170101_CR');
    $CS = $elt('tva3310a_20170101_CS');
    $DA = $elt('tva3310a_20170101_DA');
    $DB = $elt('tva3310a_20170101_DB');
    $FA = $elt('tva3310a_20170101_FA');
    $FB = $elt('tva3310a_20170101_FB');
    $FE = $elt('tva3310a_20170101_FE');
    $FF = $elt('tva3310a_20170101_FF');
    $FG = $elt('tva3310a_20170101_FG');
    $FJ = $elt('tva3310a_20170101_FJ');
    $FR = $elt('tva3310a_20170101_FR');
    $FT = $elt('tva3310a_20170101_FT');
    $FV = $elt('tva3310a_20170101_FV');
    $HB = $elt('tva3310a_20170101_HB');
    $HE = $elt('tva3310a_20170101_HE');
    $HF = $elt('tva3310a_20170101_HF');
    $HI = $elt('tva3310a_20170101_HI');
    $JA = $elt('tva3310a_20170101_JA');
    $JB = $elt('tva3310a_20170101_JB');
    $JC = $elt('tva3310a_20170101_JC');
    $JD = $elt('tva3310a_20170101_JD');
    $JE = $elt('tva3310a_20170101_JE');
    $JF = $elt('tva3310a_20170101_JF');
    $JG = $elt('tva3310a_20170101_JG');
    $JH = $elt('tva3310a_20170101_JH');
    $JJ = $elt('tva3310a_20170101_JJ');
    $JK = $elt('tva3310a_20170101_JK');
    $JL = $elt('tva3310a_20170101_JL');
    $JM = $elt('tva3310a_20170101_JM');
    $JN = $elt('tva3310a_20170101_JN');
    $JP = $elt('tva3310a_20170101_JP');
    $JQ = $elt('tva3310a_20170101_JQ');
    $JR = $elt('tva3310a_20170101_JR');
    // $KA = $elt('tva3310a_20170101_KA');
    // $KB = $elt('tva3310a_20170101_KB');
    // $KC = $elt('tva3310a_20170101_KC');
    // $KD = $elt('tva3310a_20170101_KD');
    // $KE = $elt('tva3310a_20170101_KE');
    $KF = $elt('tva3310a_20170101_KF');
    $KG = $elt('tva3310a_20170101_KG');
    $KJ = $elt('tva3310a_20170101_KJ');
    $KL = $elt('tva3310a_20170101_KL');
    $KN = $elt('tva3310a_20170101_KN');
    $KT = $elt('tva3310a_20170101_KT');
    $KU = $elt('tva3310a_20170101_KU');
    $KX = $elt('tva3310a_20170101_KX');
    $KY = $elt('tva3310a_20170101_KY');
    $KZ = $elt('tva3310a_20170101_KZ');
    $LA = $elt('tva3310a_20170101_LA');
    $LC = $elt('tva3310a_20170101_LC');
    $LD = $elt('tva3310a_20170101_LD');
    $LE = $elt('tva3310a_20170101_LE');
    $LF = $elt('tva3310a_20170101_LF');
    $LG = $elt('tva3310a_20170101_LG');
    $LH = $elt('tva3310a_20170101_LH');
    $LJ = $elt('tva3310a_20170101_LJ');
    $LJ = $elt('tva3310a_20170101_LJ');
    $LK = $elt('tva3310a_20170101_LK');
    $LL = $elt('tva3310a_20170101_LL');
    $LM = $elt('tva3310a_20170101_LM');
    $LN = $elt('tva3310a_20170101_LN');
    $LP = $elt('tva3310a_20170101_LP');
    $LQ = $elt('tva3310a_20170101_LQ');
    $LR = $elt('tva3310a_20170101_LR');
    $LS = $elt('tva3310a_20170101_LS');
    $LT = $elt('tva3310a_20170101_LT');
    $LU = $elt('tva3310a_20170101_LU');
    $LV = $elt('tva3310a_20170101_LV');
    $LW = $elt('tva3310a_20170101_LW');
    $LX = $elt('tva3310a_20170101_LX');
    $LZ = $elt('tva3310a_20170101_LZ');
    $MA = $elt('tva3310a_20170101_MA');
    $MB = $elt('tva3310a_20170101_MB');
    $MC = $elt('tva3310a_20170101_MC');
    $MD = $elt('tva3310a_20170101_MD');
    $ME = $elt('tva3310a_20170101_ME');
    $MF = $elt('tva3310a_20170101_MF');
    $MG = $elt('tva3310a_20170101_MG');
    $MH = $elt('tva3310a_20170101_MH');
    $MJ = $elt('tva3310a_20170101_MJ');
    $MK = $elt('tva3310a_20170101_MK');
    $ML = $elt('tva3310a_20170101_ML');
    $MM = $elt('tva3310a_20170101_MM');
    $MN = $elt('tva3310a_20170101_MN');
    $MP = $elt('tva3310a_20170101_MP');
    $MQ = $elt('tva3310a_20170101_MQ');
    $MR = $elt('tva3310a_20170101_MR');
    $MS = $elt('tva3310a_20170101_MS');
    $MU = $elt('tva3310a_20170101_MU');
    $MV = $elt('tva3310a_20170101_MV');
    $MW = $elt('tva3310a_20170101_MW');
    $MX = $elt('tva3310a_20170101_MX');
    $NQ = $elt('tva3310a_20170101_NQ');
    $NR = $elt('tva3310a_20170101_NR');
    $NS = $elt('tva3310a_20170101_NS');
    $NT = $elt('tva3310a_20170101_NT');
    $NU = $elt('tva3310a_20170101_NU');
    $NV = $elt('tva3310a_20170101_NV');
    $NW = $elt('tva3310a_20170101_NW');
    $NX = $elt('tva3310a_20170101_NX');
    $NY = $elt('tva3310a_20170101_NY');
    $NZ = $elt('tva3310a_20170101_NZ');
    $PA = $elt('tva3310a_20170101_PA');
    $PB = $elt('tva3310a_20170101_PB');
    $PC = $elt('tva3310a_20170101_PC');
    $PD = $elt('tva3310a_20170101_PD');


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

  public static function tva3310ca3_20170101($elt, $assert, $isServi, $float, $value, $controls) {
    $BA = $elt('tva3310ca3_20170101_BA');
    $BB = $elt('tva3310ca3_20170101_BB');
    $BC = $elt('tva3310ca3_20170101_BC');

    $CA = $elt('tva3310ca3_20170101_CA');
    $CB = $elt('tva3310ca3_20170101_CB');
    $CC = $elt('tva3310ca3_20170101_CC');
    $CD = $elt('tva3310ca3_20170101_CD');
    $CE = $elt('tva3310ca3_20170101_CE');
    $CF = $elt('tva3310ca3_20170101_CF');
    $CG = $elt('tva3310ca3_20170101_CG');

    $DA = $elt('tva3310ca3_20170101_DA');
    $DB = $elt('tva3310ca3_20170101_DB');
    $DC = $elt('tva3310ca3_20170101_DC');
    $DD = $elt('tva3310ca3_20170101_DD');
    $DE = $elt('tva3310ca3_20170101_DE');
    $DF = $elt('tva3310ca3_20170101_DF');
    $DG = $elt('tva3310ca3_20170101_DG');
    $DH = $elt('tva3310ca3_20170101_DH');

    $FB = $elt('tva3310ca3_20170101_FB');
    $FC = $elt('tva3310ca3_20170101_FC');
    $FD = $elt('tva3310ca3_20170101_FD');
    $FG = $elt('tva3310ca3_20170101_FG');
    $FH = $elt('tva3310ca3_20170101_FH');
    $FJ = $elt('tva3310ca3_20170101_FJ');
    $FK = $elt('tva3310ca3_20170101_FK');
    $FM = $elt('tva3310ca3_20170101_FM');
    $FN = $elt('tva3310ca3_20170101_FN');
    $FP = $elt('tva3310ca3_20170101_FP');
    $FR = $elt('tva3310ca3_20170101_FR');

    $GB = $elt('tva3310ca3_20170101_GB');
    $GC = $elt('tva3310ca3_20170101_GC');
    $GD = $elt('tva3310ca3_20170101_GD');
    $GG = $elt('tva3310ca3_20170101_GG');
    $GH = $elt('tva3310ca3_20170101_GH');
    $GJ = $elt('tva3310ca3_20170101_GJ');
    $GK = $elt('tva3310ca3_20170101_GK');
    $GM = $elt('tva3310ca3_20170101_GM');
    $GN = $elt('tva3310ca3_20170101_GN');
    $GP = $elt('tva3310ca3_20170101_GP');
    $GR = $elt('tva3310ca3_20170101_GR');

    $HA = $elt('tva3310ca3_20170101_HA');
    $HB = $elt('tva3310ca3_20170101_HB');
    $HC = $elt('tva3310ca3_20170101_HC');
    $HD = $elt('tva3310ca3_20170101_HD');
    $HE = $elt('tva3310ca3_20170101_HE');
    $HG = $elt('tva3310ca3_20170101_HG');
    $HH = $elt('tva3310ca3_20170101_HH');
    $HJ = $elt('tva3310ca3_20170101_HJ');

    $KA = $elt('tva3310ca3_20170101_KA');
    $KB = $elt('tva3310ca3_20170101_KB');
    $KE = $elt('tva3310ca3_20170101_KE');
    $KF = $elt('tva3310ca3_20170101_KF');
    $KG = $elt('tva3310ca3_20170101_KG');
    $KH = $elt('tva3310ca3_20170101_KH');
    $KJ = $elt('tva3310ca3_20170101_KJ');
    $KL = $elt('tva3310ca3_20170101_KL');
    $KR = $elt('tva3310ca3_20170101_KR');
    $KS = $elt('tva3310ca3_20170101_KS');
    $KT = $elt('tva3310ca3_20170101_KT');
    $KU = $elt('tva3310ca3_20170101_KU');

    $JA = $elt('tva3310ca3_20170101_JA');
    $JB = $elt('tva3310ca3_20170101_JB');
    $JC = $elt('tva3310ca3_20170101_JC');

    // ----

    /* tva3515sd */

    $BE = $elt('tva3515sd_20170101_BE');
    $BF = $elt('tva3515sd_20170101_BF');

    // ----

    if (!$KF->isset) {
        $assert(!(($isServi($FD) || $isServi($GD)) && !$isServi($elt('tva3310a_20170101_HB'))),
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

        $assert(!(!$isServi($GJ) && $isServi($CC)), 'erreur_038', $GJ, $CC);
        $assert(!($isServi($HH) && $float($HH) > 0 && !($isServi($CE) && $float($CE) > 0)), 'erreur_140', $HH, $CE);
        $assert(!($isServi($HH) && $isServi($HC) && !($float($HH) <= $float($HC))), 'erreur_051', $HH, $HC);
        $assert(!($isServi($HE) && !(0 < $float($HE) && $float($HE) < 100)), 'erreur_116', $HE);
        $assert(!($isServi($KG) && $isServi($HG) && !($float($KG) <= $float($HG))), 'erreur_205', $KG, $HG);
        $assert(!($isServi($JB) && $isServi($JA) && $isServi($KJ) && !($float($JB) <= $float($JA) - $float($KJ))), 'erreur_131', $JA, $JB, $KJ);
        $assert(!($isServi($KB) && $float($KB) > 0 && !$isServi($elt('tva3310a_20170101_HB'))),
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
                    || ($isServi($DH) && $float($DH) > 0)
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
            $DE, $DF, $DG, $DH, $FB, $FC, $FD, $FM, $FN,
            $FP, $FR, $GB, $GC, $GD, $GG, $GH, $GJ, $GK, $GM, $GN, $GP,
            $GR, $HA, $HB, $HC, $HD, $HG, $HH, $KA, $KB, $KE, $KJ,
            $KG, $KH, $KL, $KR, $KS, $KT, $KU, $JA, $JB, $JC);

        $assert((($isServi($CA) && $float($CA) > 0)
        || ($isServi($CB) && $float($CB) > 0)
        || ($isServi($KH) && $float($KH) > 0)
        || ($isServi($KR) && $float($KR) > 0)
        || ($isServi($CC) && $float($CC) > 0)
        || ($isServi($CD) && $float($CD) > 0)
        || ($isServi($CF) && $float($CF) > 0)
        || ($isServi($CG) && $float($CG) > 0)
        || ($isServi($CE) && $float($CE) > 0)
        || ($isServi($DA) && $float($DA) > 0)
        || ($isServi($DB) && $float($DB) > 0)
        || ($isServi($DC) && $float($DC) > 0)
        || ($isServi($DF) && $float($DF) > 0)
        || ($isServi($DD) && $float($DD) > 0)
        || ($isServi($DG) && $float($DG) > 0)
        || ($isServi($DE) && $float($DE) > 0)
        || ($isServi($FP) && $float($FP) > 0)
        || ($isServi($GP) && $float($GP) > 0)
        || ($isServi($FB) && $float($FB) > 0)
        || ($isServi($GB) && $float($GB) > 0)
        || ($isServi($FR) && $float($FR) > 0)
        || ($isServi($GR) && $float($GR) > 0)
        || ($isServi($FM) && $float($FM) > 0)
        || ($isServi($GM) && $float($GM) > 0)
        || ($isServi($FN) && $float($FN) > 0)
        || ($isServi($GN) && $float($GN) > 0)
        || ($isServi($FC) && $float($FC) > 0)
        || ($isServi($GC) && $float($GC) > 0)
        || ($isServi($FD) && $float($FD) > 0)
        || ($isServi($GD) && $float($GD) > 0)
        || ($isServi($GG) && $float($GG) > 0)
        || ($isServi($KS) && $float($KS) > 0)
        || ($isServi($GH) && $float($GH) > 0)
        || ($isServi($GJ) && $float($GJ) > 0)
        || ($isServi($KT) && $float($KT) > 0)
        || ($isServi($GK) && $float($GK) > 0)
        || ($isServi($HA) && $float($HA) > 0)
        || ($isServi($HB) && $float($HB) > 0)
        || ($isServi($HC) && $float($HC) > 0)
        || ($isServi($HH) && $float($HH) > 0)
        || ($isServi($HD) && $float($HD) > 0)
        || ($isServi($KU) && $float($KU) > 0)
        || ($isServi($HG) && $float($HG) > 0)
        || ($isServi($KG) && $float($KG) > 0)
        || ($isServi($JA) && $float($JA) > 0)
        || ($isServi($JB) && $float($JB) > 0)
        || ($isServi($KJ) && $float($KJ) > 0)
        || ($isServi($JC) && $float($JC) > 0)
        || ($isServi($KA) && $float($KA) > 0)
        || ($isServi($KB) && $float($KB) > 0)
        || ($isServi($KL) && $float($KL) > 0)
        || ($isServi($KE) && $float($KE) > 0)
        || ($isServi($DH) && $float($DH) > 0)), 'erreur_049', $KF);
    }
  }

  public static function tva3310ter_20170101($elt, $assert, $isServi, $float, $value, $controls) {
    $AA = $elt('tva3310ter_20170101_AA');
    $AB = $elt('tva3310ter_20170101_AB');
    $AC = $elt('tva3310ter_20170101_AC');
    $DL = $elt('tva3310ter_20170101_DL');
    $EL = $elt('tva3310ter_20170101_EL');
    $FL = $elt('tva3310ter_20170101_FL');
    $GL = $elt('tva3310ter_20170101_GL');
    $HL = $elt('tva3310ter_20170101_HL');
    $JL = $elt('tva3310ter_20170101_JL');
    $KL = $elt('tva3310ter_20170101_KL');
    $LL = $elt('tva3310ter_20170101_LL');
    $ML = $elt('tva3310ter_20170101_ML');
    $NL = $elt('tva3310ter_20170101_NL');
    $PL = $elt('tva3310ter_20170101_PL');
    $QL = $elt('tva3310ter_20170101_QL');
    $RL = $elt('tva3310ter_20170101_RL');
    $QM = $elt('tva3310ter_20170101_QM');
    $RM = $elt('tva3310ter_20170101_RM');

    $rowIndex = 1;
    while ( $isServi($elt('tva3310ter_20170101_BM/' + $rowIndex)) || $isServi($elt('tva3310ter_20170101_CM/' + $rowIndex)) ) {
      $BM = $elt('tva3310ter_20170101_BM/' + $rowIndex);
      $CM = $elt('tva3310ter_20170101_CM/' + $rowIndex);

      $assert(!($isServi($BM) && !($isServi($CM) && 0 <= $float($CM) && $float($CM) <= 100)),
              'erreur_116', $BM, $CM);

      $rowIndex++;
    }

    $assert(!($isServi($AC)
            && !$isServi($AA)),
            'erreur_128', $AC, $AA);

    $assert($isServi($AB) && !(($isServi($QM) || $isServi($RM)) && !(0 < $float($AB) && $float($AB) <= 100) ),
            'erreur_222', $AB);
  }

  public static function tva3515sd_20170101($elt, $assert, $isServi, $float, $value, $controls) {
    $AA = $elt('tva3515sd_20170101_AA');
    $AB = $elt('tva3515sd_20170101_AB');
    $BB = $elt('tva3515sd_20170101_BB');
    $BC = $elt('tva3515sd_20170101_BC');
    $BD = $elt('tva3515sd_20170101_BD');
    $BE = $elt('tva3515sd_20170101_BE');
    $BF = $elt('tva3515sd_20170101_BF');
    $CA = $elt('tva3515sd_20170101_CA');
    $CB = $elt('tva3515sd_20170101_CB');
    $DA = $elt('tva3515sd_20170101_DA');
    $DB = $elt('tva3515sd_20170101_DB');
    $DC = $elt('tva3515sd_20170101_DC');
    $DD = $elt('tva3515sd_20170101_DD');
    $EA = $elt('tva3515sd_20170101_EA');
    $EB = $elt('tva3515sd_20170101_EB');


    $assert(!($isServi($CA) && $isServi($BD) && !($float($CA) >= $float($BD))),
            'erreur_115', $CA, $BD);

    $assert(!($isServi($EB)
            && !$isServi($EA)),
            'erreur_128', $EA, $EB);
  }

  public static function tva3310ca3g_20170101($elt, $assert, $isServi, $float, $value, $controls) {
    $BA = $elt('tva3310ca3g_20170101_BA');
    $BB = $elt('tva3310ca3g_20170101_BB');
    $BC = $elt('tva3310ca3g_20170101_BC');
    $DA = $elt('tva3310ca3g_20170101_DA');
    $DB = $elt('tva3310ca3g_20170101_DB');
    $DC = $elt('tva3310ca3g_20170101_DC');
    $EA = $elt('tva3310ca3g_20170101_EA');
    $EB = $elt('tva3310ca3g_20170101_EB');
    $EC = $elt('tva3310ca3g_20170101_EC');
    $FA = $elt('tva3310ca3g_20170101_FA');
    $FB = $elt('tva3310ca3g_20170101_FB');
    $FE = $elt('tva3310ca3g_20170101_FE');
    $GA = $elt('tva3310ca3g_20170101_GA');
    $GB = $elt('tva3310ca3g_20170101_GB');
    $GD = $elt('tva3310ca3g_20170101_GD');
    $GE = $elt('tva3310ca3g_20170101_GE');
    $GF = $elt('tva3310ca3g_20170101_GF');
    $GH = $elt('tva3310ca3g_20170101_GH');
    $GJ = $elt('tva3310ca3g_20170101_GJ');
    $GK = $elt('tva3310ca3g_20170101_GK');
    $GL = $elt('tva3310ca3g_20170101_GL');
    $GM = $elt('tva3310ca3g_20170101_GM');
    $GO = $elt('tva3310ca3g_20170101_GO');
    $GP = $elt('tva3310ca3g_20170101_GP');
    $GQ = $elt('tva3310ca3g_20170101_GQ');
    $GR = $elt('tva3310ca3g_20170101_GR');
    $GS = $elt('tva3310ca3g_20170101_GS');
    $GT = $elt('tva3310ca3g_20170101_GT');
    $GU = $elt('tva3310ca3g_20170101_GU');
    $GV = $elt('tva3310ca3g_20170101_GV');
    $GX = $elt('tva3310ca3g_20170101_GX');
    $GZ = $elt('tva3310ca3g_20170101_GZ');
    $HC = $elt('tva3310ca3g_20170101_HC');
    $HE = $elt('tva3310ca3g_20170101_HE');
    $HK = $elt('tva3310ca3g_20170101_HK');
    $HL = $elt('tva3310ca3g_20170101_HL');
    $HM = $elt('tva3310ca3g_20170101_HM');
    $HN = $elt('tva3310ca3g_20170101_HN');
    $HO = $elt('tva3310ca3g_20170101_HO');
    $HP = $elt('tva3310ca3g_20170101_HP');
    $HQ = $elt('tva3310ca3g_20170101_HQ');
    $HR = $elt('tva3310ca3g_20170101_HR');
    $HS = $elt('tva3310ca3g_20170101_HS');
    $HT = $elt('tva3310ca3g_20170101_HT');
    $HU = $elt('tva3310ca3g_20170101_HU');
    $KF = $elt('tva3310ca3g_20170101_KF');
    $KH = $elt('tva3310ca3g_20170101_KH');
    $KJ = $elt('tva3310ca3g_20170101_KJ');
    $KK = $elt('tva3310ca3g_20170101_KK');
    $KL = $elt('tva3310ca3g_20170101_KL');
    $KM = $elt('tva3310ca3g_20170101_KM');
    $KN = $elt('tva3310ca3g_20170101_KN');
    $KR = $elt('tva3310ca3g_20170101_KR');
    $KS = $elt('tva3310ca3g_20170101_KS');
    $KT = $elt('tva3310ca3g_20170101_KT');
    $KU = $elt('tva3310ca3g_20170101_KU');
    $KV = $elt('tva3310ca3g_20170101_KV');
    $KW = $elt('tva3310ca3g_20170101_KW');
    $KX = $elt('tva3310ca3g_20170101_KX');
    $KY = $elt('tva3310ca3g_20170101_KY');
    $KZ = $elt('tva3310ca3g_20170101_KZ');
    $LA = $elt('tva3310ca3g_20170101_LA');
    $LB = $elt('tva3310ca3g_20170101_LB');
    $LC = $elt('tva3310ca3g_20170101_LC');
    $LD = $elt('tva3310ca3g_20170101_LD');
    $LF = $elt('tva3310ca3g_20170101_LF');
    $LG = $elt('tva3310ca3g_20170101_LG');
    $MA = $elt('tva3310ca3g_20170101_MA');
    $MB = $elt('tva3310ca3g_20170101_MB');
    $MC = $elt('tva3310ca3g_20170101_MC');
    $MD = $elt('tva3310ca3g_20170101_MD');
    $ME = $elt('tva3310ca3g_20170101_ME');
    $MF = $elt('tva3310ca3g_20170101_MF');
    $MG = $elt('tva3310ca3g_20170101_MG');
    $MH = $elt('tva3310ca3g_20170101_MH');
    $MJ = $elt('tva3310ca3g_20170101_MJ');
    $MK = $elt('tva3310ca3g_20170101_MK');
    $ML = $elt('tva3310ca3g_20170101_ML');
    $ML = $elt('tva3310ca3g_20170101_ML');
    $MM = $elt('tva3310ca3g_20170101_MM');
    $MN = $elt('tva3310ca3g_20170101_MN');
    $MP = $elt('tva3310ca3g_20170101_MP');
    $MR = $elt('tva3310ca3g_20170101_MR');
    $MS = $elt('tva3310ca3g_20170101_MS');
    $MT = $elt('tva3310ca3g_20170101_MT');
    $MU = $elt('tva3310ca3g_20170101_MU');
    $MV = $elt('tva3310ca3g_20170101_MV');
    $MX = $elt('tva3310ca3g_20170101_MX');
    $MY = $elt('tva3310ca3g_20170101_MY');
    $MZ = $elt('tva3310ca3g_20170101_MZ');
    $NA = $elt('tva3310ca3g_20170101_NA');
    $NB = $elt('tva3310ca3g_20170101_NB');
    $NC = $elt('tva3310ca3g_20170101_NC');
    $ND = $elt('tva3310ca3g_20170101_ND');
    $NE = $elt('tva3310ca3g_20170101_NE');
    $NF = $elt('tva3310ca3g_20170101_NF');
    $NG = $elt('tva3310ca3g_20170101_NG');
    $NH = $elt('tva3310ca3g_20170101_NH');

    $assert(!($isServi($BC) && !$isServi($BA)),
            'erreur_128', $BA, $BC);

    $assert(!$isServi($HT), 'erreur_218', $HT);
    $assert(!($isServi($EB) && $isServi($EA) && !($float($EB) <= $float($EA))),
            'erreur_131', $EA, $EB);

    if (!$KF->isset) {
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
                $HO, $HC, $HP, $HL, $HM, $HQ, $HR, $HS, $HT, $HU, $LG, $KS, $KT, $KJ, $KK, $KL, $KM, $KU);
    }
  }

  public static function tva3514_20170101($elt, $assert, $isServi, $float, $value, $controls) {
    $HA = $elt('tva3514_20170101_HA');
    $HB = $elt('tva3514_20170101_HB');
    $HC = $elt('tva3514_20170101_HC');
    $DE = $elt('tva3514_20170101_DE');
    $IA = $elt('tva3514_20170101_IA');
    $IB = $elt('tva3514_20170101_IB');
    $IC = $elt('tva3514_20170101_IC');
    $ID = $elt('tva3514_20170101_ID');
    $CA = $elt('tva3514_20170101_CA');
    $CB = $elt('tva3514_20170101_CB');
    $CC = $elt('tva3514_20170101_CC');

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

  public static function tva3517bisca12_20170101($elt, $assert, $isServi, $float, $value, $controls) {
    $AE = $elt('tva3517bisca12_20170101_AE');
    $AF = $elt('tva3517bisca12_20170101_AF');
    $AG = $elt('tva3517bisca12_20170101_AG');
    $BA = $elt('tva3517bisca12_20170101_BA');
    $DA = $elt('tva3517bisca12_20170101_DA');
    $DB = $elt('tva3517bisca12_20170101_DB');
    $DC = $elt('tva3517bisca12_20170101_DC');
    $DD = $elt('tva3517bisca12_20170101_DD');
    $DE = $elt('tva3517bisca12_20170101_DE');
    $DH = $elt('tva3517bisca12_20170101_DH');
    $DJ = $elt('tva3517bisca12_20170101_DJ');
    $DK = $elt('tva3517bisca12_20170101_DK');
    $DL = $elt('tva3517bisca12_20170101_DL');
    $DM = $elt('tva3517bisca12_20170101_DM');
    $DN = $elt('tva3517bisca12_20170101_DN');
    $DP = $elt('tva3517bisca12_20170101_DP');
    $DQ = $elt('tva3517bisca12_20170101_DQ');
    $DR = $elt('tva3517bisca12_20170101_DR');
    $DS = $elt('tva3517bisca12_20170101_DS');
    $DU = $elt('tva3517bisca12_20170101_DU');
    $DV = $elt('tva3517bisca12_20170101_DV');
    $DY = $elt('tva3517bisca12_20170101_DY');
    $DZ = $elt('tva3517bisca12_20170101_DZ');
    $EA = $elt('tva3517bisca12_20170101_EA');
    $EB = $elt('tva3517bisca12_20170101_EB');
    $EC = $elt('tva3517bisca12_20170101_EC');
    $ED = $elt('tva3517bisca12_20170101_ED');
    $EE = $elt('tva3517bisca12_20170101_EE');
    $EH = $elt('tva3517bisca12_20170101_EH');
    $EJ = $elt('tva3517bisca12_20170101_EJ');
    $EK = $elt('tva3517bisca12_20170101_EK');
    $EL = $elt('tva3517bisca12_20170101_EL');
    $EM = $elt('tva3517bisca12_20170101_EM');
    $EN = $elt('tva3517bisca12_20170101_EN');
    $EP = $elt('tva3517bisca12_20170101_EP');
    $EQ = $elt('tva3517bisca12_20170101_EQ');
    $ER = $elt('tva3517bisca12_20170101_ER');
    $ES = $elt('tva3517bisca12_20170101_ES');
    $EU = $elt('tva3517bisca12_20170101_EU');
    $EV = $elt('tva3517bisca12_20170101_EV');
    $EZ = $elt('tva3517bisca12_20170101_EZ');
    $FA = $elt('tva3517bisca12_20170101_FA');
    $FB = $elt('tva3517bisca12_20170101_FB');
    $FC = $elt('tva3517bisca12_20170101_FC');
    $FD = $elt('tva3517bisca12_20170101_FD');
    $FF = $elt('tva3517bisca12_20170101_FF');
    $FG = $elt('tva3517bisca12_20170101_FG');
    $GA = $elt('tva3517bisca12_20170101_GA');
    $GB = $elt('tva3517bisca12_20170101_GB');
    $HA = $elt('tva3517bisca12_20170101_HA');
    $JA = $elt('tva3517bisca12_20170101_JA');
    $JB = $elt('tva3517bisca12_20170101_JB');
    $JC = $elt('tva3517bisca12_20170101_JC');
    $KA = $elt('tva3517bisca12_20170101_KA');
    $KB = $elt('tva3517bisca12_20170101_KB');
    $KC = $elt('tva3517bisca12_20170101_KC');
    $KD = $elt('tva3517bisca12_20170101_KD');
    $KF = $elt('tva3517bisca12_20170101_KF');
    $KH = $elt('tva3517bisca12_20170101_KH');
    $LC = $elt('tva3517bisca12_20170101_LC');
    $LD = $elt('tva3517bisca12_20170101_LD');
    $LF = $elt('tva3517bisca12_20170101_LF');
    $LH = $elt('tva3517bisca12_20170101_LH');
    $LK = $elt('tva3517bisca12_20170101_LK');
    $LM = $elt('tva3517bisca12_20170101_LM');
    $MA = $elt('tva3517bisca12_20170101_MA');
    $MB = $elt('tva3517bisca12_20170101_MB');
    $MC = $elt('tva3517bisca12_20170101_MC');
    $NA = $elt('tva3517bisca12_20170101_NA');
    $NB = $elt('tva3517bisca12_20170101_NB');
    $NC = $elt('tva3517bisca12_20170101_NC');
    $ND = $elt('tva3517bisca12_20170101_ND');
    $RC = $elt('tva3517bisca12_20170101_RC');
    $RD = $elt('tva3517bisca12_20170101_RD');
    $RG = $elt('tva3517bisca12_20170101_RG');
    $RH = $elt('tva3517bisca12_20170101_RH');
    $RJ = $elt('tva3517bisca12_20170101_RJ');
    $RK = $elt('tva3517bisca12_20170101_RK');
    $RM = $elt('tva3517bisca12_20170101_RM');
    $RN = $elt('tva3517bisca12_20170101_RN');
    $RP = $elt('tva3517bisca12_20170101_RP');
    $RQ = $elt('tva3517bisca12_20170101_RQ');
    $RR = $elt('tva3517bisca12_20170101_RR');
    $RS = $elt('tva3517bisca12_20170101_RS');
    $RT = $elt('tva3517bisca12_20170101_RT');
    $RU = $elt('tva3517bisca12_20170101_RU');
    $RV = $elt('tva3517bisca12_20170101_RV');
    $RW = $elt('tva3517bisca12_20170101_RW');
    $RX = $elt('tva3517bisca12_20170101_RX');
    $RY = $elt('tva3517bisca12_20170101_RY');
    $RZ = $elt('tva3517bisca12_20170101_RZ');
    $SA = $elt('tva3517bisca12_20170101_SA');
    $SB = $elt('tva3517bisca12_20170101_SB');
    $SC = $elt('tva3517bisca12_20170101_SC');
    $SD = $elt('tva3517bisca12_20170101_SD');
    $SE = $elt('tva3517bisca12_20170101_SE');

    if (!$ND->isset) {
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

        $assert((($isServi($DA) && $float($DA) > 0)
            || ($isServi($DB) && $float($DB) > 0)
            || ($isServi($DC) && $float($DC) > 0)
            || ($isServi($DF) && $float($DF) > 0)
            || ($isServi($DD) && $float($DD) > 0)
            || ($isServi($DY) && $float($DY) > 0)
            || ($isServi($DK) && $float($DK) > 0)
            || ($isServi($EK) && $float($EK) > 0)
            || ($isServi($DQ) && $float($DQ) > 0)
            || ($isServi($EQ) && $float($EQ) > 0)
            || ($isServi($DE) && $float($DE) > 0)
            || ($isServi($EE) && $float($EE) > 0)
            || ($isServi($EA) && $float($EA) > 0)
            || ($isServi($EB) && $float($EB) > 0)
            || ($isServi($DU) && $float($DU) > 0)
            || ($isServi($EU) && $float($EU) > 0)
            || ($isServi($DV) && $float($DV) > 0)
            || ($isServi($EV) && $float($EV) > 0)
            || ($isServi($EC) && $float($EC) > 0)
            || ($isServi($ED) && $float($ED) > 0)
            || ($isServi($DH) && $float($DH) > 0)
            || ($isServi($EH) && $float($EH) > 0)
            || ($isServi($DJ) && $float($DJ) > 0)
            || ($isServi($EJ) && $float($EJ) > 0)
            || ($isServi($DZ) && $float($DZ) > 0)
            || ($isServi($EZ) && $float($EZ) > 0)
            || ($isServi($DR) && $float($DR) > 0)
            || ($isServi($DS) && $float($DS) > 0)
            || ($isServi($DL) && $float($DL) > 0)
            || ($isServi($EL) && $float($EL) > 0)
            || ($isServi($DM) && $float($DM) > 0)
            || ($isServi($EM) && $float($EM) > 0)
            || ($isServi($DN) && $float($DN) > 0)
            || ($isServi($EN) && $float($EN) > 0)
            || ($isServi($DP) && $float($DP) > 0)
            || ($isServi($EP) && $float($EP) > 0)
            || ($isServi($ER) && $float($ER) > 0)
            || ($isServi($RC) && $float($RC) > 0)
            || ($isServi($ES) && $float($ES) > 0)
            || ($isServi($FA) && $float($FA) > 0)
            || ($isServi($FB) && $float($FB) > 0)
            || ($isServi($FC) && $float($FC) > 0)
            || ($isServi($FD) && $float($FD) > 0)
            || ($isServi($RD) && $float($RD) > 0)
            || ($isServi($FF) && $float($FF) > 0)
            || ($isServi($KH) && $float($KH) > 0)
            || ($isServi($GA) && $float($GA) > 0)
            || ($isServi($GB) && $float($GB) > 0)
            || ($isServi($HA) && $float($HA) > 0)
            || ($isServi($JA) && $float($JA) > 0)
            || ($isServi($JB) && $float($JB) > 0)
            || ($isServi($JC) && $float($JC) > 0)
            || ($isServi($LF) && $float($LF) > 0)
            || ($isServi($LC) && $float($LC) > 0)
            || ($isServi($LD) && $float($LD) > 0)
            || ($isServi($LK) && $float($LK) > 0)
            || ($isServi($LH) && $float($LH) > 0)
            || ($isServi($LM) && $float($LM) > 0)
            || ($isServi($KA) && $float($KA) > 0)
            || ($isServi($KB) && $float($KB) > 0)
            || ($isServi($KC) && $float($KC) > 0)
            || ($isServi($KD) && $float($KD) > 0)
            || ($isServi($KF) && $float($KF) > 0)
            || ($isServi($MA) && $float($MA) > 0)
            || ($isServi($MB) && $float($MB) > 0)
            || ($isServi($MC) && $float($MC) > 0)
            || ($isServi($NA) && $float($NA) > 0)
            || ($isServi($NB) && $float($NB) > 0)
            || ($isServi($NC) && $float($NC) > 0)
            || ($isServi($RM) && $float($RM) > 0)
            || ($isServi($RN) && $float($RN) > 0)
            || ($isServi($RG) && $float($RG) > 0)
            || ($isServi($RH) && $float($RH) > 0)
            || ($isServi($RJ) && $float($RJ) > 0)
            || ($isServi($RK) && $float($RK) > 0)
            || ($isServi($RP) && $float($RP) > 0)
            || ($isServi($RQ) && $float($RQ) > 0)
            || ($isServi($SA) && $float($SA) > 0)
            || ($isServi($RR) && $float($RR) > 0)
            || ($isServi($SB) && $float($SB) > 0)
            || ($isServi($RS) && $float($RS) > 0)
            || ($isServi($SC) && $float($SC) > 0)
            || ($isServi($RT) && $float($RT) > 0)
            || ($isServi($SD) && $float($SD) > 0)
            || ($isServi($RU) && $float($RU) > 0)
            || ($isServi($SE) && $float($SE) > 0)
            || ($isServi($RV) && $float($RV) > 0)
            || ($isServi($SF) && $float($SF) > 0)
            || ($isServi($RW) && $float($RW) > 0)
            || ($isServi($SG) && $float($SG) > 0)
            || ($isServi($RX) && $float($RX) > 0)
            || ($isServi($RY) && $float($RY) > 0)
            || ($isServi($RZ) && $float($RZ) > 0)), 'erreur_049' , $ND);
    }
  }

  public static function tva3517ddr_20170101($elt, $assert, $isServi, $float, $value, $controls) {
    $AA = $elt('tva3517ddr_20170101_AA');
    $AB = $elt('tva3517ddr_20170101_AB');
    $AC = $elt('tva3517ddr_20170101_AC');
    $AD = $elt('tva3517ddr_20170101_AD');
    $AE = $elt('tva3517ddr_20170101_AE');
    $AF1 = $elt('tva3517ddr_20170101_AF1');
    $AH = $elt('tva3517ddr_20170101_AH');
    $AJ = $elt('tva3517ddr_20170101_AJ');
    $AK1 = $elt('tva3517ddr_20170101_AK1');
    $AK2 = $elt('tva3517ddr_20170101_AK2');
    $AK3 = $elt('tva3517ddr_20170101_AK3');
    $AK4 = $elt('tva3517ddr_20170101_AK4');
    $BA = $elt('tva3517ddr_20170101_BA');
    $BB = $elt('tva3517ddr_20170101_BB');

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
  }

  public static function tva3517sca12_20170101($elt, $assert, $isServi, $float, $value, $controls) {
    $CA = $elt('tva3517sca12_20170101_CA');
    $CA1 = $elt('tva3517sca12_20170101_CA1');
    $CA2 = $elt('tva3517sca12_20170101_CA2');
    $CA3 = $elt('tva3517sca12_20170101_CA3');
    $CA4 = $elt('tva3517sca12_20170101_CA4');
    $CA5 = $elt('tva3517sca12_20170101_CA5');
    $DA = $elt('tva3517sca12_20170101_DA');
    $DB = $elt('tva3517sca12_20170101_DB');
    $DC = $elt('tva3517sca12_20170101_DC');
    $EA = $elt('tva3517sca12_20170101_EA');
    $EB = $elt('tva3517sca12_20170101_EB');
    $EC = $elt('tva3517sca12_20170101_EC');
    $ED = $elt('tva3517sca12_20170101_ED');
    $EE = $elt('tva3517sca12_20170101_EE');
    $EF = $elt('tva3517sca12_20170101_EF');
    $EG = $elt('tva3517sca12_20170101_EG');
    $EH = $elt('tva3517sca12_20170101_EH');
    $EJ = $elt('tva3517sca12_20170101_EJ');
    $EL = $elt('tva3517sca12_20170101_EL');
    $EM = $elt('tva3517sca12_20170101_EM');
    $EN = $elt('tva3517sca12_20170101_EN');
    $EP = $elt('tva3517sca12_20170101_EP');
    $EQ = $elt('tva3517sca12_20170101_EQ');
    $EU = $elt('tva3517sca12_20170101_EU');
    $EV = $elt('tva3517sca12_20170101_EV');
    $EW = $elt('tva3517sca12_20170101_EW');
    $EX = $elt('tva3517sca12_20170101_EX');
    $EY = $elt('tva3517sca12_20170101_EY');
    $EZ = $elt('tva3517sca12_20170101_EZ');
    $FA = $elt('tva3517sca12_20170101_FA');
    $FB = $elt('tva3517sca12_20170101_FB');
    $FC = $elt('tva3517sca12_20170101_FC');
    $FD = $elt('tva3517sca12_20170101_FD');
    $FE = $elt('tva3517sca12_20170101_FE');
    $FF = $elt('tva3517sca12_20170101_FF');
    $FG = $elt('tva3517sca12_20170101_FG');
    $FJ = $elt('tva3517sca12_20170101_FJ');
    $FL = $elt('tva3517sca12_20170101_FL');
    $FM = $elt('tva3517sca12_20170101_FM');
    $FN = $elt('tva3517sca12_20170101_FN');
    $FP = $elt('tva3517sca12_20170101_FP');
    $FR = $elt('tva3517sca12_20170101_FR');
    $FU = $elt('tva3517sca12_20170101_FU');
    $FV = $elt('tva3517sca12_20170101_FV');
    $FW = $elt('tva3517sca12_20170101_FW');
    $FY = $elt('tva3517sca12_20170101_FY');
    $GA = $elt('tva3517sca12_20170101_GA');
    $GB = $elt('tva3517sca12_20170101_GB');
    $GC = $elt('tva3517sca12_20170101_GC');
    $GF = $elt('tva3517sca12_20170101_GF');
    $GH = $elt('tva3517sca12_20170101_GH');
    $HA = $elt('tva3517sca12_20170101_HA');
    $HB = $elt('tva3517sca12_20170101_HB');
    $HC = $elt('tva3517sca12_20170101_HC');
    $JA = $elt('tva3517sca12_20170101_JA');
    $JB = $elt('tva3517sca12_20170101_JB');
    $KA = $elt('tva3517sca12_20170101_KA');
    $KB = $elt('tva3517sca12_20170101_KB');
    $KD = $elt('tva3517sca12_20170101_KD');
    $KE = $elt('tva3517sca12_20170101_KE');
    $KF = $elt('tva3517sca12_20170101_KF');
    $KG = $elt('tva3517sca12_20170101_KG');
    $KH = $elt('tva3517sca12_20170101_KH');
    $KJ = $elt('tva3517sca12_20170101_KJ');
    $KL = $elt('tva3517sca12_20170101_KL');
    $KM = $elt('tva3517sca12_20170101_KM');
    $LA = $elt('tva3517sca12_20170101_LA');
    $LB = $elt('tva3517sca12_20170101_LB');
    $MA = $elt('tva3517sca12_20170101_MA');
    $MD = $elt('tva3517sca12_20170101_MD');
    $ME = $elt('tva3517sca12_20170101_ME');
    $MF = $elt('tva3517sca12_20170101_MF');
    $MG = $elt('tva3517sca12_20170101_MG');
    $MM = $elt('tva3517sca12_20170101_MM');
    $MN = $elt('tva3517sca12_20170101_MN');
    $NA = $elt('tva3517sca12_20170101_NA');
    $NB = $elt('tva3517sca12_20170101_NB');
    $NC = $elt('tva3517sca12_20170101_NC');
    $QA = $elt('tva3517sca12_20170101_QA');
    $QD = $elt('tva3517sca12_20170101_QD');
    $QE = $elt('tva3517sca12_20170101_QE');
    $QF = $elt('tva3517sca12_20170101_QF');
    $QH = $elt('tva3517sca12_20170101_QH');
    $QJ = $elt('tva3517sca12_20170101_QJ');
    $QS = $elt('tva3517sca12_20170101_QS');
    $RA = $elt('tva3517sca12_20170101_RA');
    $RB = $elt('tva3517sca12_20170101_RB');
    $RC = $elt('tva3517sca12_20170101_RC');
    $RE = $elt('tva3517sca12_20170101_RE');
    $RF = $elt('tva3517sca12_20170101_RF');
    $RG = $elt('tva3517sca12_20170101_RG');
    $RH = $elt('tva3517sca12_20170101_RH');
    $RN = $elt('tva3517sca12_20170101_RN');
    $SA = $elt('tva3517sca12_20170101_SA');
    $SB = $elt('tva3517sca12_20170101_SB');
    $SC = $elt('tva3517sca12_20170101_SC');
    $SD = $elt('tva3517sca12_20170101_SD');
    $TB = $elt('tva3517sca12_20170101_TB');
    $TD = $elt('tva3517sca12_20170101_TD');
    $UB = $elt('tva3517sca12_20170101_UB');
    $UD = $elt('tva3517sca12_20170101_UD');
    $VA = $elt('tva3517sca12_20170101_VA');
    $VC = $elt('tva3517sca12_20170101_VC');
    $VE = $elt('tva3517sca12_20170101_VE');
    $VF = $elt('tva3517sca12_20170101_VF');
    $VJ = $elt('tva3517sca12_20170101_VJ');
    $VK = $elt('tva3517sca12_20170101_VK');
    $VL = $elt('tva3517sca12_20170101_VL');
    $VM = $elt('tva3517sca12_20170101_VM');
    $VN = $elt('tva3517sca12_20170101_VN');
    $VP = $elt('tva3517sca12_20170101_VP');
    $VS = $elt('tva3517sca12_20170101_VS');
    $VT = $elt('tva3517sca12_20170101_VT');
    $VW = $elt('tva3517sca12_20170101_VW');
    $VX = $elt('tva3517sca12_20170101_VX');
    $VY = $elt('tva3517sca12_20170101_VY');
    $VZ = $elt('tva3517sca12_20170101_VZ');
    $WB = $elt('tva3517sca12_20170101_WB');
    $WC = $elt('tva3517sca12_20170101_WC');
    $WD = $elt('tva3517sca12_20170101_WD');
    $WE = $elt('tva3517sca12_20170101_WE');
    $WF = $elt('tva3517sca12_20170101_WF');
    $WG = $elt('tva3517sca12_20170101_WG');
    $WH = $elt('tva3517sca12_20170101_WH');
    $WJ = $elt('tva3517sca12_20170101_WJ');
    $WK = $elt('tva3517sca12_20170101_WK');
    $WL = $elt('tva3517sca12_20170101_WL');
    $WM = $elt('tva3517sca12_20170101_WM');
    $WN = $elt('tva3517sca12_20170101_WN');
    $WP = $elt('tva3517sca12_20170101_WP');
    $WQ = $elt('tva3517sca12_20170101_WQ');
    $WR = $elt('tva3517sca12_20170101_WR');
    $WS = $elt('tva3517sca12_20170101_WS');
    $WT = $elt('tva3517sca12_20170101_WT');
    $WU = $elt('tva3517sca12_20170101_WU');
    $WV = $elt('tva3517sca12_20170101_WV');
    $WX = $elt('tva3517sca12_20170101_WX');
    $WY = $elt('tva3517sca12_20170101_WY');
    $WZ = $elt('tva3517sca12_20170101_WZ');
    $YK = $elt('tva3517sca12_20170101_YK');
    $YL = $elt('tva3517sca12_20170101_YL');
    $ZA = $elt('tva3517sca12_20170101_ZA');
    $ZB = $elt('tva3517sca12_20170101_ZB');
    $ZE = $elt('tva3517sca12_20170101_ZE');
    $ZF = $elt('tva3517sca12_20170101_ZF');
    $ZG = $elt('tva3517sca12_20170101_ZG');
    $ZH = $elt('tva3517sca12_20170101_ZH');
    $ZJ = $elt('tva3517sca12_20170101_ZJ');
    $ZK = $elt('tva3517sca12_20170101_ZK');
    $ZL = $elt('tva3517sca12_20170101_ZL');
    $ZM = $elt('tva3517sca12_20170101_ZM');
    $ZN = $elt('tva3517sca12_20170101_ZN');
    $ZP = $elt('tva3517sca12_20170101_ZP');

    if (!$SD->isset) {
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


        $assert(!($isServi($SC) && strlen($value($SC)) > 6), 'erreur_229', $SC);

        $assert(!($isServi($EQ) && $isServi($FP) && !($float($EQ) <= $float($FP))),
            'erreur_137', $EQ, $FP);
        $assert(!($isServi($HB) && $float($HB) > 0 && !(
                $float($HB) == 0.2 * ($float($EB) + $float($EC) + $float($EE)
                    + $float($ED) + $float($VM) + $float($EX) + $float($EF)
                    + $float($EU) + $float($EV) + $float($EJ) + $float($EG) +
                    $float($EW) + $float($GF))
            )),
            'erreur_034', $HB, $EB, $EC, $ED, $EE, $VM, $EX, $EF, $EU, $EV, $EJ, $EG, $EW, $GF);
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

        $casesCoches = 0;
        $casesCoches += $isServi($TA) ? 1 : 0;
        $casesCoches += $isServi($TB) ? 1 : 0;
        $casesCoches += $isServi($TC) ? 1 : 0;
        $casesCoches += $isServi($TD) ? 1 : 0;
        $assert(!($isServi($MA) && $float($MA) > 0 && !($casesAccomptesRemplies == $casesCoches)),
            'erreur_124', $MA, $MD, $ME, $MF, $MG);

        $controls['erreur_129']($TB, $UB);
        $controls['erreur_129']($TD, $UD);

        $controls['erreur_226']($UB, $TB);
        $controls['erreur_226']($UD, $TD);

        $controls['erreur_134']($UB, $elt('t_identif_20151020_CA'), $elt('t_identif_20151020_CB'));
        $controls['erreur_134']($UD, $elt('t_identif_20151020_CA'), $elt('t_identif_20151020_CB'));

        $requiredFields = array(
            $DA, $DB, $DC, $EA, $EB, $EC, $ED, $EF, $EE,
            $EG, $EH, $EJ, $EL, $EM, $EN, $EP, $EQ, $EU, $EV, $EW,
            $EX, $EY, $EZ, $FA, $FB, $FC, $FD, $FF, $FG, $FJ,
            $FL, $FM, $FN, $FP, $FR, $FU, $FV, $FW, $FY, $GA, $GB,
            $GC, $GF, $GH, $HA, $HB, $HC, $JA, $KA, $KB, $KD,
            $KL, $KM, $LA, $LB, $MA,
            $MM, $MN, $NA,
            $NB, $NC, $QA, $QD, $QE, $QF, $QH, $QJ, $QS,
            $RA, $RB, $RC, $RE, $RF, $RG, $RH, $RN,
            $SA, $SB, $SC,
            $VA, $VC, $VE, $VF, $VJ, $VM, $VN, $VP,
            $VS, $VT, $VW, $VX, $VY, $VZ,
            $WB, $WC
        );

        $controls['erreur_042']($SD, $requiredFields);
        $controls['erreur_049']($SD, $requiredFields);

        $assert((($isServi($EA) && $float($EA) > 0)
        || ($isServi($EB) && $float($EB) > 0)
        || ($isServi($EC) && $float($EC) > 0)
        || ($isServi($EE) && $float($EE) > 0)
        || ($isServi($ED) && $float($ED) > 0)
        || ($isServi($VM) && $float($VM) > 0)
        || ($isServi($EX) && $float($EX) > 0)
        || ($isServi($EW) && $float($EW) > 0)
        || ($isServi($FW) && $float($FW) > 0)
        || ($isServi($EF) && $float($EF) > 0)
        || ($isServi($FF) && $float($FF) > 0)
        || ($isServi($GF) && $float($GF) > 0)
        || ($isServi($GH) && $float($GH) > 0)
        || ($isServi($FA) && $float($FA) > 0)
        || ($isServi($FB) && $float($FB) > 0)
        || ($isServi($EU) && $float($EU) > 0)
        || ($isServi($FU) && $float($FU) > 0)
        || ($isServi($EV) && $float($EV) > 0)
        || ($isServi($FV) && $float($FV) > 0)
        || ($isServi($FC) && $float($FC) > 0)
        || ($isServi($FD) && $float($FD) > 0)
        || ($isServi($EJ) && $float($EJ) > 0)
        || ($isServi($FJ) && $float($FJ) > 0)
        || ($isServi($EG) && $float($EG) > 0)
        || ($isServi($FG) && $float($FG) > 0)
        || ($isServi($EY) && $float($EY) > 0)
        || ($isServi($FY) && $float($FY) > 0)
        || ($isServi($VN) && $float($VN) > 0)
        || ($isServi($VP) && $float($VP) > 0)
        || ($isServi($EH) && $float($EH) > 0)
        || ($isServi($EZ) && $float($EZ) > 0)
        || ($isServi($EL) && $float($EL) > 0)
        || ($isServi($FL) && $float($FL) > 0)
        || ($isServi($EM) && $float($EM) > 0)
        || ($isServi($FM) && $float($FM) > 0)
        || ($isServi($EN) && $float($EN) > 0)
        || ($isServi($FN) && $float($FN) > 0)
        || ($isServi($EP) && $float($EP) > 0)
        || ($isServi($FP) && $float($FP) > 0)
        || ($isServi($EQ) && $float($EQ) > 0)
        || ($isServi($FR) && $float($FR) > 0)
        || ($isServi($GA) && $float($GA) > 0)
        || ($isServi($GB) && $float($GB) > 0)
        || ($isServi($VS) && $float($VS) > 0)
        || ($isServi($GC) && $float($GC) > 0)
        || ($isServi($HA) && $float($HA) > 0)
        || ($isServi($HB) && $float($HB) > 0)
        || ($isServi($HC) && $float($HC) > 0)
        || ($isServi($JA) && $float($JA) > 0)
        || ($isServi($KA) && $float($KA) > 0)
        || ($isServi($KB) && $float($KB) > 0)
        || ($isServi($VT) && $float($VT) > 0)
        || ($isServi($KD) && $float($KD) > 0)
        || ($isServi($FE) && $float($FE) > 0)
        || ($isServi($LA) && $float($LA) > 0)
        || ($isServi($LB) && $float($LB) > 0)
        || ($isServi($MD) && $float($MD) > 0)
        || ($isServi($MF) && $float($MF) > 0)
        || ($isServi($ME) && $float($ME) > 0)
        || ($isServi($MG) && $float($MG) > 0)
        || ($isServi($MM) && $float($MM) > 0)
        || ($isServi($MN) && $float($MN) > 0)
        || ($isServi($MA) && $float($MA) > 0)
        || ($isServi($NA) && $float($NA) > 0)
        || ($isServi($NB) && $float($NB) > 0)
        || ($isServi($NC) && $float($NC) > 0)
        || ($isServi($QA) && $float($QA) > 0)
        || ($isServi($QS) && $float($QS) > 0)
        || ($isServi($ZE) && $float($ZE) > 0)
        || ($isServi($QD) && $float($QD) > 0)
        || ($isServi($ZF) && $float($ZF) > 0)
        || ($isServi($QE) && $float($QE) > 0)
        || ($isServi($QF) && $float($QF) > 0)
        || ($isServi($ZG) && $float($ZG) > 0)
        || ($isServi($RF) && $float($RF) > 0)
        || ($isServi($ZH) && $float($ZH) > 0)
        || ($isServi($RG) && $float($RG) > 0)
        || ($isServi($QH) && $float($QH) > 0)
        || ($isServi($QJ) && $float($QJ) > 0)
        || ($isServi($ZL) && $float($ZL) > 0)
        || ($isServi($VC) && $float($VC) > 0)
        || ($isServi($ZB) && $float($ZB) > 0)
        || ($isServi($VJ) && $float($VJ) > 0)
        || ($isServi($VE) && $float($VE) > 0)
        || ($isServi($VF) && $float($VF) > 0)
        || ($isServi($KL) && $float($KL) > 0)
        || ($isServi($KM) && $float($KM) > 0)
        || ($isServi($DA) && $float($DA) > 0)
        || ($isServi($RH) && $float($RH) > 0)
        || ($isServi($RN) && $float($RN) > 0)
        || ($isServi($DB) && $float($DB) > 0)
        || ($isServi($DC) && $float($DC) > 0)
        || ($isServi($WB) && $float($WB) > 0)
        || ($isServi($WC) && $float($WC) > 0)
        || ($isServi($VW) && $float($VW) > 0)
        || ($isServi($VX) && $float($VX) > 0)
        || ($isServi($VY) && $float($VY) > 0)
        || ($isServi($VZ) && $float($VZ) > 0)
        || ($isServi($WD) && $float($WD) > 0)
        || ($isServi($WE) && $float($WE) > 0)
        || ($isServi($WX) && $float($WX) > 0)
        || ($isServi($WF) && $float($WF) > 0)
        || ($isServi($WY) && $float($WY) > 0)
        || ($isServi($WG) && $float($WG) > 0)
        || ($isServi($WZ) && $float($WZ) > 0)
        || ($isServi($WH) && $float($WH) > 0)
        || ($isServi($ZA) && $float($ZA) > 0)
        || ($isServi($WJ) && $float($WJ) > 0)
        || ($isServi($ZM) && $float($ZM) > 0)
        || ($isServi($YA) && $float($YA) > 0)
        || ($isServi($YB) && $float($YB) > 0)
        || ($isServi($WK) && $float($WK) > 0)
        || ($isServi($WL) && $float($WL) > 0)
        || ($isServi($WM) && $float($WM) > 0)
        || ($isServi($WN) && $float($WN) > 0)
        || ($isServi($WP) && $float($WP) > 0)
        || ($isServi($ZN) && $float($ZN) > 0)
        || ($isServi($WQ) && $float($WQ) > 0)
        || ($isServi($WR) && $float($WR) > 0)
        || ($isServi($WS) && $float($WS) > 0)
        || ($isServi($ZP) && $float($ZP) > 0)
        || ($isServi($WT) && $float($WT) > 0)
        || ($isServi($WU) && $float($WU) > 0)
        || ($isServi($WV) && $float($WV) > 0)
        || ($isServi($YL) && $float($YL) > 0)
        || ($isServi($YK) && $float($YK) > 0)
        || ($isServi($RA) && $float($RA) > 0)
        || ($isServi($RB) && $float($RB) > 0)
        || ($isServi($RC) && $float($RC) > 0)
        || ($isServi($RE) && $float($RE) > 0)
        || ($isServi($SA) && $float($SA) > 0)
        || ($isServi($SB) && $float($SB) > 0)
        || ($isServi($SC) && $float($SC) > 0)
        || ($isServi($VA) && $float($VA) > 0)), 'erreur_049' , $SD);
    }
  }

  public static function tva3519_20170101($elt, $assert, $isServi, $float, $value, $controls) {
    $CB = $elt('t_identif_20151020_CB');
    $AA1 = $elt('tva3519_20170101_AA1');
    $AA2 = $elt('tva3519_20170101_AA2');
    $AA3 = $elt('tva3519_20170101_AA3');
    $AA4 = $elt('tva3519_20170101_AA4');
    $DC1 = $elt('tva3519_20170101_DC1');
    $DC10 = $elt('tva3519_20170101_DC10');
    $DC2 = $elt('tva3519_20170101_DC2');
    $DC3 = $elt('tva3519_20170101_DC3');
    $DC4 = $elt('tva3519_20170101_DC4');
    $DC5 = $elt('tva3519_20170101_DC5');
    $DC6 = $elt('tva3519_20170101_DC6');
    $DC7 = $elt('tva3519_20170101_DC7');
    $DC8 = $elt('tva3519_20170101_DC8');
    $DC9 = $elt('tva3519_20170101_DC9');
    $DD = $elt('tva3519_20170101_DD');
    $DE = $elt('tva3519_20170101_DE');
    $DF = $elt('tva3519_20170101_DF');
    $DG1 = $elt('tva3519_20170101_DG1');
    $DG2 = $elt('tva3519_20170101_DG2');
    $DG3 = $elt('tva3519_20170101_DG3');
    $DG4 = $elt('tva3519_20170101_DG4');
    $DH = $elt('tva3519_20170101_DH');
    $DI = $elt('tva3519_20170101_DI');
    $DJ = $elt('tva3519_20170101_DJ');
    $DK = $elt('tva3519_20170101_DK');
    $DL = $elt('tva3519_20170101_DL');
    $DM = $elt('tva3519_20170101_DM');
    $DN = $elt('tva3519_20170101_DN');
    $FJ = $elt('tva3519_20170101_FJ');
    $FK = $elt('tva3519_20170101_FK');
    $FL = $elt('tva3519_20170101_FL');


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
    $assert(strlen($float($DN)) <= 9, 'erreur_227', $DN);
    $assert($isServi($FK) || $isServi($FL), 'erreur_221', $FK, $FL);
    $assert(!($isServi($DJ) && !$isServi($DM)), 'erreur_223', $DM);
    $assert(!($isServi($DI) && !$isServi($FJ)), 'erreur_148', $FJ);
    $assert(!($isServi($DI)
            && !$isServi($AA1)
            && !$isServi($AA2)
            && !$isServi($AA3)
            && !$isServi($AA4)
            && $isServi($DL)),
            'erreur_230',
            $AA1, $AA2, $AA3, $AA4);
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
        $month = $month[1];
        $minimumDN = 760;
        if ($month == 12) {
          $minimumDN = 150;
        }
        return $float($DN) >= $minimumDN;
      }
      return true;
    }, 'erreur_225', $DN);

    $assert(!($isServi($AA1) && !$isServi($AA2)), 'Vous devez saisir l\'IBAN', $AA1, $AA2);
    $assert(!($isServi($AA2) && !$isServi($AA3)), 'Attention ! Veuillez préalablement servir la ligne "nom du titulaire du compte"', $AA2, $AA3);



    $assert_DC1_DC4 = ($isServi($DC1) || $isServi($DC4))
                          && (!$isServi($DC2) || !$isServi($DC3) || !$isServi($DC6) || !$isServi($DC7) || !$isServi($DC8) || !$isServi($DC9) || !$isServi($DC10));

    $assert_DC1_DC4_message = 'Attention ! Veuillez renseigner le cadre "Adresse de correspondance", '
                              . 'si celle-ci est différente de celle de l’établissement principal ou si la demande est effectuée par un représentant fiscal ou '
                              . 'le mandataire-liquidateur de l’entreprise';

    $assert(!($assert_DC1_DC4),
            $assert_DC1_DC4_message,
            $DC1, $DC2, $DC3, $DC4, $DC6, $DC7, $DC8, $DC9, $DC10);
  }

  public static function tva3525bis_20170101($elt, $assert, $isServi, $float, $value, $controls) {
    $AC = $elt('tva3525bis_20170101_AC');
    $AD = $elt('tva3525bis_20170101_AD');
    $BB = $elt('tva3525bis_20170101_BB');
    $BC = $elt('tva3525bis_20170101_BC');
    $BD = $elt('tva3525bis_20170101_BD');
    $BE = $elt('tva3525bis_20170101_BE');
    $DA = $elt('tva3525bis_20170101_DA');

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


  public static function is2571_2017($elt, $assert, $isServi, $float, $value, $controls) {
    $CA = $elt('is2571_2017_CA');
    $CC = $elt('is2571_2017_CC');
    $CD = $elt('is2571_2017_CD');
    $CE = $elt('is2571_2017_CE');
    $CG = $elt('is2571_2017_CG');
    $CL = $elt('is2571_2017_CL');
    $CH = $elt('is2571_2017_CH');
    $DA = $elt('is2571_2017_DA');
    $DB = $elt('is2571_2017_DB');
    $FA = $elt('is2571_2017_FA');
    $FB = $elt('is2571_2017_FB');
    $FC = $elt('is2571_2017_FC');
    $FD = $elt('is2571_2017_FD');
    $FE = $elt('is2571_2017_FE');
    $FF = $elt('is2571_2017_FF');
    $FG = $elt('is2571_2017_FG');
    $FH = $elt('is2571_2017_FH');
    $FK = $elt('is2571_2017_FK');
    $FM = $elt('is2571_2017_FM');
    $FN = $elt('is2571_2017_FN');

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

  public static function is2572_2017($elt, $assert, $isServi, $float, $value, $controls) {
    $AD = $elt('is2572_2017_AD');
    $BD = $elt('is2572_2017_BD');
    $CA = $elt('is2572_2017_CA');
    $DA = $elt('is2572_2017_DA');
    $EA = $elt('is2572_2017_EA');
    $EB = $elt('is2572_2017_EB');
    $GC = $elt('is2572_2017_GC');
    $GD = $elt('is2572_2017_GD');
    $GE = $elt('is2572_2017_GE');
    $IA = $elt('is2572_2017_IA');
    $JA = $elt('is2572_2017_JA');
    $KA = $elt('is2572_2017_KA');
    $KB = $elt('is2572_2017_KB');
    $KC = $elt('is2572_2017_KC');
    $KD = $elt('is2572_2017_KD');
    $LA = $elt('is2572_2017_LA');
    $LB = $elt('is2572_2017_LB');
    $LC = $elt('is2572_2017_LC');
    $LD = $elt('is2572_2017_LD');
    $LE = $elt('is2572_2017_LE');
    $LF = $elt('is2572_2017_LF');
    $MA = $elt('is2572_2017_MA');
    $MB = $elt('is2572_2017_MB');
    $MD = $elt('is2572_2017_MD');
    $ME = $elt('is2572_2017_ME');
    $MH = $elt('is2572_2017_MH');
    $NA = $elt('is2572_2017_NA');
    $NB = $elt('is2572_2017_NB');
    $NC = $elt('is2572_2017_NC');
    $ND = $elt('is2572_2017_ND');
    $NE = $elt('is2572_2017_NE');
    $NF = $elt('is2572_2017_NF');
    $NG = $elt('is2572_2017_NG');
    $NJ = $elt('is2572_2017_NJ');
    $NK = $elt('is2572_2017_NK');
    $NL = $elt('is2572_2017_NL');
    $NM = $elt('is2572_2017_NM');
    $NN = $elt('is2572_2017_NN');
    $NO = $elt('is2572_2017_NO');
    $OB = $elt('is2572_2017_OB');
    $OC = $elt('is2572_2017_OC');
    $OD = $elt('is2572_2017_OD');
    $OE = $elt('is2572_2017_OE');
    $OF = $elt('is2572_2017_OF');
    $OG = $elt('is2572_2017_OG');
    $OH = $elt('is2572_2017_OH');
    $OJ = $elt('is2572_2017_OJ');
    $OK = $elt('is2572_2017_OK');
    $PA = $elt('is2572_2017_PA');
    $PB = $elt('is2572_2017_PB');
    $PC = $elt('is2572_2017_PC');
    $PD = $elt('is2572_2017_PD');
    $PE = $elt('is2572_2017_PE');
    $PF = $elt('is2572_2017_PF');
    $PG = $elt('is2572_2017_PG');
    $PH = $elt('is2572_2017_PH');
    $PJ = $elt('is2572_2017_PJ');
    $PK = $elt('is2572_2017_PK');
    $PL = $elt('is2572_2017_PL');
    $PM = $elt('is2572_2017_PM');
    $PN = $elt('is2572_2017_PN');
    $PQ = $elt('is2572_2017_PQ');
    $PR = $elt('is2572_2017_PR');
    $PS = $elt('is2572_2017_PS');
    $PT = $elt('is2572_2017_PT');
    $PU = $elt('is2572_2017_PU');
    $PV = $elt('is2572_2017_PV');
    $PW = $elt('is2572_2017_PW');
    $RA = $elt('is2572_2017_RA');
    $RB = $elt('is2572_2017_RB');
    $RC = $elt('is2572_2017_RC');
    $RD = $elt('is2572_2017_RD');
    $RE = $elt('is2572_2017_RE');
    $RF = $elt('is2572_2017_RF');
    $RG = $elt('is2572_2017_RG');
    $RH = $elt('is2572_2017_RH');
    $RJ = $elt('is2572_2017_RJ');
    $RK = $elt('is2572_2017_RK');
    $RL = $elt('is2572_2017_RL');
    $RM = $elt('is2572_2017_RM');
    $RN = $elt('is2572_2017_RN');
    $RP = $elt('is2572_2017_RP');
    $RR = $elt('is2572_2017_RR');
    $RS = $elt('is2572_2017_RS');
    $RT = $elt('is2572_2017_RT');
    $RU = $elt('is2572_2017_RU');
    $RV = $elt('is2572_2017_RV');
    $RW = $elt('is2572_2017_RW');
    $RX = $elt('is2572_2017_RX');
    $RY = $elt('is2572_2017_RY');
    $RZ = $elt('is2572_2017_RZ');
    $TA = $elt('is2572_2017_TA');
    $TB = $elt('is2572_2017_TB');


    $PidentifKF = $elt('p_identif_20151020_KF');
    $date_PJ = explode('/', $value($PJ));
    $date_PJ = strtotime($date_PJ[0] . '-' . $date_PJ[1] . '-' . $date_PJ[0]);
    $date_KF = explode('/', $value($PidentifKF));
    $date_KF = strtotime('01-'.$date_KF[0].'-'. $date_KF[1]);
    $date_KF_inf_datePJ = $date_PJ < $date_KF ;

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

    $DAminusEA = 0;
    if ($isServi($DA)) {
      $DAminusEA = $float($DA);
    }
    if ($isServi($EA)) {
      $DAminusEA -= $float($EA);
    }
    $assert(!($isServi($DA) && $float($DA) > 0 && $isServi($PG) && $float($PG) >= 0 && !($DAminusEA >= $float($PG))), 'erreur_319', $PG);

    $LE_value = !is_numeric($value($LE)) ? '' : $float($LE);
    $LF_value = !is_numeric($value($LF)) ? '' : $float($LF);
    $assert(!( ($isServi($LE) && !$isServi($LF)) || ( ($isServi($LE) && $isServi($LF)) && ($LE_value == '' || $LF_value == '')) ),
            'erreur_322', $LE, $LF);

    $OJ_value = !is_numeric($value($OJ)) ? '' : $float($OJ);
    $OH_value = !is_numeric($value($OH)) ? '' : $float($OH);
    $assert(!( ($isServi($OJ) && !$isServi($OH)) || ( ($isServi($OJ) && $isServi($OH)) && ($OJ_value == '' || $OH_value == '')) ),
            'erreur_322', $OJ, $OH);

    $OE_value = !is_numeric($value($OE)) ? '' : $float($OE);
    $KD_value = !is_numeric($value($KD)) ? '' : $float($KD);
    $assert(!( ($isServi($OE) && !$isServi($KD)) || ( ($isServi($OE) && $isServi($KD)) && ($OE_value == '' || $KD_value == '')) ),
            'erreur_322', $OE, $KD);

    $OG_value = !is_numeric($value($OG)) ? '' : $float($OG);
    $OF_value = !is_numeric($value($OF)) ? '' : $float($OF);
    $assert(!( ($isServi($OG) && !$isServi($OF)) || ( ($isServi($OG) && $isServi($OF)) && ($OG_value == '' || $OF_value == '')) ),
            'erreur_322', $OG, $OF);

    $CA = $elt('p_identif_20151020_CA');
    $CB = $elt('p_identif_20151020_CB');
    $valid_CB = false;

    $CA_date = explode('/', $value($CA));
    $CA_date = strtotime($CA_date[2] . '-' . $CA_date[1] . '-' . $CA_date[0]);
    $CB_date = explode('/', $value($CB));
    $CB_date = strtotime($CB_date[2] . '-' . $CB_date[1] . '-' . $CB_date[0]);
    $month_diff = ($CB_date - $CA_date) / 2628000;

    if (date('d/m', $CB_date) == '31/12' && $month_diff > 12) {
      $valid_CB = true;
    }

    $assert(!( ($isServi($OJ) || $isServi($OH)) && !$valid_CB),
            'erreur_323', $OJ, $OH);
  }

  public static function is2573_2017($elt, $assert, $isServi, $float, $value, $controls) {
    $AA = $elt('is2573_2017_AA');
    $AJ = $elt('is2573_2017_AJ');
    $BA = $elt('is2573_2017_BA');
    $BF = $elt('is2573_2017_BF');
    $CA = $elt('is2573_2017_CA');
    $CG = $elt('is2573_2017_CG');


    // for each row
    $rowIndex = 1;
    while ($elt('is2573_2017_AB/' . $rowIndex)->isset) {
      $AB = $elt('is2573_2017_AB/'.$rowIndex);
      $AC = $elt('is2573_2017_AC/'.$rowIndex);
      $AF = $elt('is2573_2017_AF/'.$rowIndex);
      $AG = $elt('is2573_2017_AG/'.$rowIndex);
      $AH = $elt('is2573_2017_AH/'.$rowIndex);
      $AI = $elt('is2573_2017_AI/'.$rowIndex);
      $KA = $elt('is2573_2017_KA/'.$rowIndex);
      $KB = $elt('is2573_2017_KB/'.$rowIndex);
      $KC = $elt('is2573_2017_KC/'.$rowIndex);
      $KD = $elt('is2573_2017_KD/'.$rowIndex);

      $assert($value($AB) != 'REL' && $value($AB) != 'RES', 'erreur_309', $AB);
      $assert(!(($isServi($AB) || $isServi($AC) || $isServi($AF) || $isServi($AG) || $isServi($AH) || $isServi($AI))
        && !($isServi($AB) && $isServi($AC) && $isServi($AG) && $float($AG) > 0)),
              'erreur_315', $AB, $AC, $AF, $AG, $AH, $AI);
      $assert(!($isServi($AF) && !($value($AB) == 'RAD' && $isServi($AH))), 'erreur_313', $AF, $AB, $AH);
      $assert(!($isServi($AH) && !$isServi($AI)), 'erreur_305', $AI);
      $assert(!($isServi($AI) && !$isServi($AH)), 'erreur_305', $AH);

      $date_KC = explode('/', $value($KC));
      $date_KC = strtotime($date_KC[2] . '-' . $date_KC[1] . '-' . $date_KC[0] . 'T23:59:59');
      $assert(!( $isServi($KC) && ($date_KC < time()) ), 'erreur_320', $KC);

      $isServi_KB_KC_KD = ( $isServi($KB) && (!$isServi($KC) || !$isServi($KD)) )
                          || ( $isServi($KC) && (!$isServi($KB) || !$isServi($KD)) )
                          || ( $isServi($KD) && (!$isServi($KB) || !$isServi($KC)) );

      $assert(!$isServi_KB_KC_KD, 'erreur_321', $KB, $KC, $KD);

      $assert(!($isServi($KD) && $isServi($AG) && !($float($KD) <= $float($AG))), 'erreur_314', $KD);
      $rowIndex++;
    }

    // for each row
    $rowIndex = 1;
    while ($elt('is2573_2017_BB/' . $rowIndex)->isset) {
      $BB = $elt('is2573_2017_BB/'.$rowIndex);
      $BC = $elt('is2573_2017_BC/'.$rowIndex);
      $BD = $elt('is2573_2017_BD/'.$rowIndex);
      $BE = $elt('is2573_2017_BE/'.$rowIndex);


      $assert(!(($isServi($BB) || $isServi($BC) || $isServi($BD) || $isServi($BE))
        && !($isServi($BB) && $isServi($BC) && $isServi($BE) && $float($BE) > 0)),
              'erreur_307', $BB, $BC, $BD, $BE);
      $rowIndex++;
    }

    // for each row
    $rowIndex = 1;
    while ($elt('is2573_2017_CB/' . $rowIndex)->isset) {
      $CB = $elt('is2573_2017_CB/'.$rowIndex);
      $CC = $elt('is2573_2017_CC/'.$rowIndex);
      $CD = $elt('is2573_2017_CD/'.$rowIndex);
      $CE = $elt('is2573_2017_CE/'.$rowIndex);
      $CF = $elt('is2573_2017_CF/'.$rowIndex);


      $assert(!(($isServi($CB) || $isServi($CC) || $isServi($CD) || $isServi($CE) || $isServi($CF))
        && !($isServi($CB) && $isServi($CC) && $isServi($CD) && $isServi($CF) && $float($CF) > 0)),
              'erreur_308', $CB, $CC, $CD, $CF);
      $rowIndex++;
    }
  }


  public static function cvae1329ac_20170101($elt, $assert, $isServi, $float, $value, $controls) {
    $AA = $elt('cvae1329ac_20170101_AA');
    $AB = $elt('cvae1329ac_20170101_AB');
    $AC = $elt('cvae1329ac_20170101_AC');
    $AD = $elt('cvae1329ac_20170101_AD');
    $AE = $elt('cvae1329ac_20170101_AE');
    $BA = $elt('cvae1329ac_20170101_BA');
    $BB = $elt('cvae1329ac_20170101_BB');
    $BC = $elt('cvae1329ac_20170101_BC');
    $CA = $elt('cvae1329ac_20170101_CA');
    $CB = $elt('cvae1329ac_20170101_CB');
    $DA = $elt('cvae1329ac_20170101_DA');
    $DB = $elt('cvae1329ac_20170101_DB');
    $EA = $elt('cvae1329ac_20170101_EA');
    $EB = $elt('cvae1329ac_20170101_EB');
    $EC = $elt('cvae1329ac_20170101_EC');
    $ED = $elt('cvae1329ac_20170101_ED');
    $GA = $elt('cvae1329ac_20170101_GA');
    $GB = $elt('cvae1329ac_20170101_GB');
    $HA = $elt('cvae1329ac_20170101_HA');
    $KA = $elt('cvae1329ac_20170101_KA');
    $KF_month = $elt('p_identif_20151020_KF');

    $AE_value = $value($AE);
    $assert(!($isServi($AE) && !Valid::isSiren($AE_value)), 'cvae_erreur_209', $AE);
    $assert(!($isServi($AD) && !$isServi($AE)), 'cvae_erreur_210', $AD, $AE);
    $assert(!($isServi($AE) && !$isServi($AD)), 'cvae_erreur_211', $AD, $AE);

    $assert($isServi($AA) && $float($AA) >= 152500, 'cvae_erreur_202', $AA);
    $assert(!($isServi($AB) && $float($AB) > 0 && !($isServi($AA) && $float($AA) > 0)), 'cvae_erreur_205', $AB);
    $assert(!($isServi($AD) && $float($AD) > 0 && !($isServi($AA) && $float($AD) >= $float($AA))), 'cvae_erreur_206', $AD);
    $assert(!($isServi($EB) && $isServi($EC) && $float($EB) > 0 && $float($EC) > 0), 'cvae_erreur_207', $EB, $EC);

    $KF_month_value = (int)substr($value($KF_month), 0, 2);
    $assert(!($KF_month_value == 6  && ($isServi($EB) || $isServi($EC))), 'cvae_erreur_208', $EB, $EC);
  }

  public static function cvae1329def_20170101($elt, $assert, $isServi, $float, $value, $controls) {
    $AA = $elt('cvae1329def_20170101_AA');
    $AB = $elt('cvae1329def_20170101_AB');
    $AC = $elt('cvae1329def_20170101_AC');
    $AD = $elt('cvae1329def_20170101_AD');
    $AE = $elt('cvae1329def_20170101_AE');
    $BA = $elt('cvae1329def_20170101_BA');
    $BB = $elt('cvae1329def_20170101_BB');
    $BC = $elt('cvae1329def_20170101_BC');
    $CA = $elt('cvae1329def_20170101_CA');
    $CB = $elt('cvae1329def_20170101_CB');
    $DA = $elt('cvae1329def_20170101_DA');
    $DB = $elt('cvae1329def_20170101_DB');
    $EA = $elt('cvae1329def_20170101_EA');
    $EB = $elt('cvae1329def_20170101_EB');
    $EC = $elt('cvae1329def_20170101_EC');
    $ED = $elt('cvae1329def_20170101_ED');
    $GA = $elt('cvae1329def_20170101_GA');
    $GB = $elt('cvae1329def_20170101_GB');
    $GC = $elt('cvae1329def_20170101_GC');
    $GD = $elt('cvae1329def_20170101_GD');
    $GE = $elt('cvae1329def_20170101_GE');
    $HA = $elt('cvae1329def_20170101_HA');
    $HB = $elt('cvae1329def_20170101_HB');
    $HC = $elt('cvae1329def_20170101_HC');
    $HD = $elt('cvae1329def_20170101_HD');
    $JA = $elt('cvae1329def_20170101_JA');
    $JE = $elt('cvae1329def_20170101_JE');
    $JK = $elt('cvae1329def_20170101_JK');
    $KA = $elt('cvae1329def_20170101_KA');
    $KB = $elt('cvae1329def_20170101_KB');

    $AE_value = $value($AE);
    $assert(!($isServi($AE) && !Valid::isSiren($AE_value)), 'cvae_erreur_209', $AE);
    $assert(!($isServi($AD) && !$isServi($AE)), 'cvae_erreur_210', $AD, $AE);
    $assert(!($isServi($AE) && !$isServi($AD)), 'cvae_erreur_211', $AD, $AE);

    $assert($isServi($AA) && $float($AA) >= 0, 'cvae_erreur_201', $AA);
    $assert(!($isServi($AB) && $float($AB) >= 0 && !$isServi($AA)), 'Vous devez saisir ligne 01 votre chiffre d\'affaires rapporté sur 12 mois. Merci de corriger', $AB);
    $assert(!($isServi($AB) && $float($AB) > 0 && !($isServi($AA) && $float($AA) > 0)), 'cvae_erreur_205', $AB);
    $assert(!($isServi($AD) && $float($AD) > 0 && !($isServi($AA) && $float($AD) >= $float($AA))), 'cvae_erreur_206', $AD);
  }
}
