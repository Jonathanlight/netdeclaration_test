<?php

/** Millésime 2019 **/

class DeclarationAsserter2019 extends DeclarationAsserter
{
    public static function f_identif_20180219($elt, $assert, $isServi, $float, $value, $controls)
    {
        $AA = $elt('f_identif_20180219_AA');
        $AA1 = $elt('f_identif_20180219_AA1');
        $AA13 = $elt('f_identif_20180219_AA13');
        $AA2 = $elt('f_identif_20180219_AA2');
        $AA3 = $elt('f_identif_20180219_AA3');
        $AA4 = $elt('f_identif_20180219_AA4');
        $AA5 = $elt('f_identif_20180219_AA5');
        $AA6 = $elt('f_identif_20180219_AA6');
        $AA7 = $elt('f_identif_20180219_AA7');
        $AA8 = $elt('f_identif_20180219_AA8');
        $AB = $elt('f_identif_20180219_AB');
        $AC13 = $elt('f_identif_20180219_AC13');
        $AC2 = $elt('f_identif_20180219_AC2');
        $AC3 = $elt('f_identif_20180219_AC3');
        $AC4 = $elt('f_identif_20180219_AC4');
        $BA = $elt('f_identif_20180219_BA');
        $BB = $elt('f_identif_20180219_BB');
        $BC = $elt('f_identif_20180219_BC');
        $BD = $elt('f_identif_20180219_BD');
        $BF = $elt('f_identif_20180219_BF');
        $CA = $elt('f_identif_20180219_CA');
        $CB = $elt('f_identif_20180219_CB');
        $CC = $elt('f_identif_20180219_CC');
        $CD = $elt('f_identif_20180219_CD');
        $CE = $elt('f_identif_20180219_CE');
        $DA = $elt('f_identif_20180219_DA');
        $DC = $elt('f_identif_20180219_DC');
        $IDOGA = $elt('f_identif_20180219_IDOGA');
        $KD = $elt('f_identif_20180219_KD');
        $OGA = $elt('f_identif_20180219_OGA');

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

    public static function ts2502_201810($elt, $assert, $isServi, $float, $value, $controls)
    {
        $AA = $elt('ts2502_201810_AA');
        $AB = $elt('ts2502_201810_AB');
        $AC = $elt('ts2502_201810_AC');
        $AD = $elt('ts2502_201810_AD');
        $AE = $elt('ts2502_201810_AE');
        $AF = $elt('ts2502_201810_AF');
        $AG = $elt('ts2502_201810_AG');
        $AH = $elt('ts2502_201810_AH');
        $AI = $elt('ts2502_201810_AI');
        $AJ = $elt('ts2502_201810_AJ');
        $AK = $elt('ts2502_201810_AK');
        $AL = $elt('ts2502_201810_AL');
        $AM = $elt('ts2502_201810_AM');
        $AN = $elt('ts2502_201810_AN');
        $AO = $elt('ts2502_201810_AO');
        $BA = $elt('ts2502_201810_BA');
        $BB = $elt('ts2502_201810_BB');
        $BC = $elt('ts2502_201810_BC');
        $BD = $elt('ts2502_201810_BD');
        $BE = $elt('ts2502_201810_BE');
        $BF = $elt('ts2502_201810_BF');
        $BG = $elt('ts2502_201810_BG');
        $BH = $elt('ts2502_201810_BH');
        $BI = $elt('ts2502_201810_BI');
        $BJ = $elt('ts2502_201810_BJ');
        $BK = $elt('ts2502_201810_BK');
        $BL = $elt('ts2502_201810_BL');
        $BM = $elt('ts2502_201810_BM');
        $BN = $elt('ts2502_201810_BN');
        $BO = $elt('ts2502_201810_BO');
        $CA = $elt('ts2502_201810_CA');
        $CB = $elt('ts2502_201810_CB');
        $CC = $elt('ts2502_201810_CC');
        $CD = $elt('ts2502_201810_CD');
        $CE = $elt('ts2502_201810_CE');
        $CF = $elt('ts2502_201810_CF');
        $CG = $elt('ts2502_201810_CG');
        $CH = $elt('ts2502_201810_CH');
        $CI = $elt('ts2502_201810_CI');
        $CJ = $elt('ts2502_201810_CJ');
        $CK = $elt('ts2502_201810_CK');
        $CL = $elt('ts2502_201810_CL');
        $CM = $elt('ts2502_201810_CM');
        $CN = $elt('ts2502_201810_CN');
        $CO = $elt('ts2502_201810_CO');
        $DA = $elt('ts2502_201810_DA');
        $DB = $elt('ts2502_201810_DB');
        $DC = $elt('ts2502_201810_DC');
        $DD = $elt('ts2502_201810_DD');
        $DE = $elt('ts2502_201810_DE');
        $DF = $elt('ts2502_201810_DF');
        $DG = $elt('ts2502_201810_DG');
        $DH = $elt('ts2502_201810_DH');
        $DI = $elt('ts2502_201810_DI');
        $DJ = $elt('ts2502_201810_DJ');
        $DK = $elt('ts2502_201810_DK');
        $DL = $elt('ts2502_201810_DL');
        $DM = $elt('ts2502_201810_DM');
        $DN = $elt('ts2502_201810_DN');
        $DO = $elt('ts2502_201810_DO');
        $EF = $elt('ts2502_201810_EF');
        $EG = $elt('ts2502_201810_EG');
        $EH = $elt('ts2502_201810_EH');
        $EI = $elt('ts2502_201810_EI');
        $EJ = $elt('ts2502_201810_EJ');
        $EK = $elt('ts2502_201810_EK');
        $EM = $elt('ts2502_201810_EM');
        $EO = $elt('ts2502_201810_EO');
        $FA = $elt('ts2502_201810_FA');
        $FB = $elt('ts2502_201810_FB');
        $FC = $elt('ts2502_201810_FC');
        $FD = $elt('ts2502_201810_FD');
        $FE = $elt('ts2502_201810_FE');
        $GA = $elt('ts2502_201810_GA');
        $GB = $elt('ts2502_201810_GB');
        $GC = $elt('ts2502_201810_GC');
        $GD = $elt('ts2502_201810_GD');
        $GE = $elt('ts2502_201810_GE');
        $GF = $elt('ts2502_201810_GF');
        $GH = $elt('ts2502_201810_GH');
        $HA = $elt('ts2502_201810_HA');
        $HB = $elt('ts2502_201810_HB');
        $HC = $elt('ts2502_201810_HC');
        $HD = $elt('ts2502_201810_HD');
        $HE = $elt('ts2502_201810_HE');
        $JA = $elt('ts2502_201810_JA');
        $JB = $elt('ts2502_201810_JB');

        $CB_identif = $elt('p_identif_20151020_CB');
        $KF_identif = $elt('p_identif_20151020_KF');


        // ts2502_controlGB
        $amount = $float($GC);
        $amount += $float($GD);
        $amount += $float($GE);

        if (($float($GB) > 0 || $float($GC) > 0 || $float($GD) > 0 || $float($GE) > 0)) {
            $assert(($amount <= $float($GB)),
                'erreur_405', $GB, $GC, $GD, $GE
            );
        }

        if ($float($GB) > 0) {
            $assert(($float($GC) > 0 || $float($GD) > 0 || $float($GE) > 0),
                'erreur_407', $GC, $GD, $GE
            );
        }


        // ts2502_controlFC
        $amount_EM = $float($EM);
        $amount_FA = $float($FA);
        $amount_FB = $float($FB);

        $amount = $amount_EM - ($amount_FA + $amount_FB);
        $seuil = 20304;

        if ($float($EM) > 0 || $float($FA) > 0 || $float($FB) > 0 || $float($FC) > 0) {
            $assert((($float($FC) == 0 || ($float($FC) < $seuil && $float($FC) == $amount) || ($float($FC) == $seuil && $amount >= $seuil))),
                'erreur_403', $EM, $FA, $FB, $FC
            );
        }


        // ts2502_checkHE
        $CB_date = Date::toDb($value($CB_identif)); // DD/MM/YYYY
        $KF_date = Date::toDb('01/' . $value($KF_identif)); // MM/YYYY
        $date = date('2018-01-01');

        if ($isServi($HE)) {
            $assert(!($float($HE) > 0 && ((Date::isValid($CB_date) && (strtotime($CB_date) - strtotime($date)) < 0) || (Date::isValid($KF_date) && (strtotime($KF_date) - strtotime($date)) < 0))),
                'erreur_408', $HE
            );
        }
    }

    public static function cvae1330sd_20190101($elt, $assert, $isServi, $float, $value)
    {
        $AC = $elt('cvae1330sd_20190101_AC');
        $assert(!(!$isServi($AC) || $float($AC) < 152500), 'Votre chiffre d\'affaires doit être supérieur à 152 500 euros.', $AC);
    }

    public static function cvae1329ac_20190101($elt, $assert, $isServi, $float, $value, $controls)
    {
        $AA = $elt('cvae1329ac_20190101_AA');
        $AB = $elt('cvae1329ac_20190101_AB');
        $AC = $elt('cvae1329ac_20190101_AC');
        $AD = $elt('cvae1329ac_20190101_AD');
        $BA = $elt('cvae1329ac_20190101_BA');
        $BB = $elt('cvae1329ac_20190101_BB');
        $BC = $elt('cvae1329ac_20190101_BC');
        $CA = $elt('cvae1329ac_20190101_CA');
        $CB = $elt('cvae1329ac_20190101_CB');
        $DA = $elt('cvae1329ac_20190101_DA');
        $DB = $elt('cvae1329ac_20190101_DB');
        $EA = $elt('cvae1329ac_20190101_EA');
        $EB = $elt('cvae1329ac_20190101_EB');
        $EC = $elt('cvae1329ac_20190101_EC');
        $ED = $elt('cvae1329ac_20190101_ED');
        $GA = $elt('cvae1329ac_20190101_GA');
        $GB = $elt('cvae1329ac_20190101_GB');
        $HA = $elt('cvae1329ac_20190101_HA');
        $KA = $elt('cvae1329ac_20190101_KA');
        $KF_month = $elt('p_identif_20151020_KF');

        $assert($isServi($AA) && $float($AA) >= 152500, 'cvae_erreur_202', $AA);
        $assert(!($isServi($AB) && $float($AB) > 0 && !($isServi($AA) && $float($AA) > 0)), 'cvae_erreur_205', $AB);
        $assert(!($isServi($AD) && $float($AD) > 0 && !($isServi($AA) && $float($AD) >= $float($AA))), 'cvae_erreur_206', $AD);
        $assert(!($isServi($EB) && $isServi($EC) && $float($EB) > 0 && $float($EC) > 0), 'cvae_erreur_207', $EB, $EC);

        $assert(!($isServi($AD) && $float($AD) > 0 && $float($AD) < 7630000), 'cvae_erreur_215', $AD);
        $assert(!(!$isServi($BA) || $float($BA) < 0), 'cvae_erreur_214', $BA);

        $KF_month_value = (int)substr($value($KF_month), 0, 2);
        $assert(!($KF_month_value == 6 && ($isServi($EB) || $isServi($EC))), 'cvae_erreur_208', $EB, $EC);
    }

    public static function cvae1329def_20190101($elt, $assert, $isServi, $float, $value, $controls)
    {
        $AA = $elt('cvae1329def_20190101_AA');
        $AB = $elt('cvae1329def_20190101_AB');
        $AC = $elt('cvae1329def_20190101_AC');
        $AD = $elt('cvae1329def_20190101_AD');
        $BA = $elt('cvae1329def_20190101_BA');
        $BB = $elt('cvae1329def_20190101_BB');
        $BC = $elt('cvae1329def_20190101_BC');
        $CA = $elt('cvae1329def_20190101_CA');
        $CB = $elt('cvae1329def_20190101_CB');
        $DA = $elt('cvae1329def_20190101_DA');
        $DB = $elt('cvae1329def_20190101_DB');
        $EA = $elt('cvae1329def_20190101_EA');
        $EB = $elt('cvae1329def_20190101_EB');
        $EC = $elt('cvae1329def_20190101_EC');
        $ED = $elt('cvae1329def_20190101_ED');
        $GA = $elt('cvae1329def_20190101_GA');
        $GB = $elt('cvae1329def_20190101_GB');
        $GC = $elt('cvae1329def_20190101_GC');
        $GD = $elt('cvae1329def_20190101_GD');
        $GE = $elt('cvae1329def_20190101_GE');
        $HA = $elt('cvae1329def_20190101_HA');
        $HB = $elt('cvae1329def_20190101_HB');
        $HC = $elt('cvae1329def_20190101_HC');
        $HD = $elt('cvae1329def_20190101_HD');
        $JA = $elt('cvae1329def_20190101_JA');
        $JE = $elt('cvae1329def_20190101_JE');
        $JK = $elt('cvae1329def_20190101_JK');
        $KA = $elt('cvae1329def_20190101_KA');
        $KB = $elt('cvae1329def_20190101_KB');

        $assert($isServi($AA) && $float($AA) >= 0, 'cvae_erreur_201', $AA);
        $assert(!($isServi($AB) && $float($AB) >= 0 && !$isServi($AA)), 'Vous devez saisir ligne 01 votre chiffre d\'affaires rapporté sur 12 mois. Merci de corriger', $AB);
        $assert(!($isServi($AB) && $float($AB) > 0 && !($isServi($AA) && $float($AA) > 0)), 'cvae_erreur_205', $AB);
        $assert(!($isServi($AD) && $float($AD) > 0 && !($isServi($AA) && $float($AD) >= $float($AA))), 'cvae_erreur_206', $AD);

        $assert(!(!$isServi($BA) || $float($BA) < 0), 'cvae_erreur_214', $BA);
        $assert(!($isServi($AD) && $float($AD) > 0 && $float($AD) < 7630000), 'cvae_erreur_215', $AD);

        $cvae_erreur_214 = "Vous déclarez un chiffre d'affaires inférieur à 500 000 € et vous n'avez pas versé d'acomptes, alors vous n'avez pas de déclaration 1329-DEF à souscrire.";
        $assert(!(!$isServi($AA) || ($isServi($AA) && $float($AA) < 500000 && (!$isServi($AD) || $float($AD) == 0) && (!$isServi($JA) || $float($JA) == 0))), $cvae_erreur_214, $AA);
    }

    public static function a_identif_ifu_20190101($elt, $assert, $isServi, $float, $value, $controls)
    {
        $AA01 = $elt('a_identif_ifu_20190101_AA01');
        $AA02 = $elt('a_identif_ifu_20190101_AA02');
        $AA03 = $elt('a_identif_ifu_20190101_AA03');
        $AA05 = $elt('a_identif_ifu_20190101_AA05');
        $AA06 = $elt('a_identif_ifu_20190101_AA06');
        $AA08 = $elt('a_identif_ifu_20190101_AA08');
        $AA09 = $elt('a_identif_ifu_20190101_AA09');
        $AA11 = $elt('a_identif_ifu_20190101_AA11');
        $AA12 = $elt('a_identif_ifu_20190101_AA12');
        $AA13 = $elt('a_identif_ifu_20190101_AA13');
        $AA14 = $elt('a_identif_ifu_20190101_AA14');
        $AA15 = $elt('a_identif_ifu_20190101_AA15');
        $AA16 = $elt('a_identif_ifu_20190101_AA16');
        $AA17 = $elt('a_identif_ifu_20190101_AA17');
        $BA = $elt('a_identif_ifu_20190101_BA');
        $BB = $elt('a_identif_ifu_20190101_BB');
        $BC = $elt('a_identif_ifu_20190101_BC');
        $BD = $elt('a_identif_ifu_20190101_BD');
        $CB = $elt('a_identif_ifu_20190101_CB');
        $CC = $elt('a_identif_ifu_20190101_CC');
        $DA = $elt('a_identif_ifu_20190101_DA');

        // $readonly($AA15, true);
        if ($isServi($AA08)) {
            $value($AA15, $value($AA08));
        }
    }

    public static function ifu2561_20190101($elt, $assert, $isServi, $float, $value, $controls)
    {
        $AA01 = $elt('ifu2561_20190101_AA01');
        $AA03 = $elt('ifu2561_20190101_AA03');
        $AA02 = $elt('ifu2561_20190101_AA02');
        $AB = $elt('ifu2561_20190101_AB');
        $AC = $elt('ifu2561_20190101_AC');
        $AD = $elt('ifu2561_20190101_AD');
        $AE02 = $elt('ifu2561_20190101_AE02');
        $AE03 = $elt('ifu2561_20190101_AE03');
        $AE04 = $elt('ifu2561_20190101_AE04');
        $AE14_1 = $elt('ifu2561_20190101_AE14_1');
        $AE14_2 = $elt('ifu2561_20190101_AE14_2');
        $AE15 = $elt('ifu2561_20190101_AE15');
        $AF01 = $elt('ifu2561_20190101_AF01');
        $AF02 = $elt('ifu2561_20190101_AF02');
        $AG05 = $elt('ifu2561_20190101_AG05');
        $AG06 = $elt('ifu2561_20190101_AG06');
        $AG08 = $elt('ifu2561_20190101_AG08');
        $AG09 = $elt('ifu2561_20190101_AG09');
        $AG14_1 = $elt('ifu2561_20190101_AG14_1');
        $AG14_2 = $elt('ifu2561_20190101_AG14_2');
        $AG15 = $elt('ifu2561_20190101_AG15');
        $AG16 = $elt('ifu2561_20190101_AG16');
        $AG17 = $elt('ifu2561_20190101_AG17');
        $AH = $elt('ifu2561_20190101_AH');
        $AJ = $elt('ifu2561_20190101_AJ');
        $AK = $elt('ifu2561_20190101_AK');
        $AL = $elt('ifu2561_20190101_AK');
        $AM = $elt('ifu2561_20190101_AM');
        $AN = $elt('ifu2561_20190101_AN');
        $AP = $elt('ifu2561_20190101_AP');
        $BA = $elt('ifu2561_20190101_BA');
        $BB = $elt('ifu2561_20190101_BB');
        $BC = $elt('ifu2561_20190101_BC');
        $BE = $elt('ifu2561_20190101_BE');
        $BF = $elt('ifu2561_20190101_BF');
        $BG = $elt('ifu2561_20190101_BG');
        $BH = $elt('ifu2561_20190101_BH');
        $BJ = $elt('ifu2561_20190101_BJ');
        $BK = $elt('ifu2561_20190101_BK');
        $BN = $elt('ifu2561_20190101_BN');
        $BP = $elt('ifu2561_20190101_BP');
        $BR = $elt('ifu2561_20190101_BR');
        $BS = $elt('ifu2561_20190101_BS');
        $BT = $elt('ifu2561_20190101_BT');
        $BU = $elt('ifu2561_20190101_BU');
        $BV = $elt('ifu2561_20190101_BV');
        $CA = $elt('ifu2561_20190101_CA');
        $CB = $elt('ifu2561_20190101_CB');
        $CC = $elt('ifu2561_20190101_CC');
        $CD = $elt('ifu2561_20190101_CD');
        $CF = $elt('ifu2561_20190101_CF');
        $CG = $elt('ifu2561_20190101_CG');
        $CH = $elt('ifu2561_20190101_CH');
        $CJ = $elt('ifu2561_20190101_CJ');
        $CK = $elt('ifu2561_20190101_CK');
        $CL = $elt('ifu2561_20190101_CL');
        $CM = $elt('ifu2561_20190101_CM');
        $CN = $elt('ifu2561_20190101_CN');
        $CP = $elt('ifu2561_20190101_CP');
        $CR = $elt('ifu2561_20190101_CR');
        $CS = $elt('ifu2561_20190101_CS');
        $CT = $elt('ifu2561_20190101_CT');
        $CU = $elt('ifu2561_20190101_CU');
        $CV = $elt('ifu2561_20190101_CV');
        $CW = $elt('ifu2561_20190101_CW');
        $CX = $elt('ifu2561_20190101_CX');
        $CY = $elt('ifu2561_20190101_CY');
        $CZ = $elt('ifu2561_20190101_CZ');
        $DA = $elt('ifu2561_20190101_DA');
        $DB = $elt('ifu2561_20190101_DB');
        $DC = $elt('ifu2561_20190101_DC');
        $DD = $elt('ifu2561_20190101_DD');
        $DE = $elt('ifu2561_20190101_DE');
        $DF = $elt('ifu2561_20190101_DF');
        $DG = $elt('ifu2561_20190101_DG');
        $DH = $elt('ifu2561_20190101_DH');
        $DI = $elt('ifu2561_20190101_DI');
        $DJ = $elt('ifu2561_20190101_DJ');
        $DK = $elt('ifu2561_20190101_DK');
        $DL = $elt('ifu2561_20190101_DL');
        $DM = $elt('ifu2561_20190101_DM');
        $DN = $elt('ifu2561_20190101_DN');
        $DP = $elt('ifu2561_20190101_DP');
        $EA = $elt('ifu2561_20190101_EA');
        $EB = $elt('ifu2561_20190101_EB');
        $EC = $elt('ifu2561_20190101_EC');
        $ED = $elt('ifu2561_20190101_ED');
        $EE = $elt('ifu2561_20190101_EE');
        $EF = $elt('ifu2561_20190101_EF');
        $EG = $elt('ifu2561_20190101_EG');
        $EH = $elt('ifu2561_20190101_EH');
        $EJ = $elt('ifu2561_20190101_EJ');
        $EK = $elt('ifu2561_20190101_EK');
        $EL = $elt('ifu2561_20190101_EL');
        $EM = $elt('ifu2561_20190101_EM');
        $EN = $elt('ifu2561_20190101_EN');
        $EP = $elt('ifu2561_20190101_EP');
        $ER = $elt('ifu2561_20190101_ER');
        $ES = $elt('ifu2561_20190101_ES');
        $ET = $elt('ifu2561_20190101_ET');
        $EU = $elt('ifu2561_20190101_EU');
        $EV = $elt('ifu2561_20190101_EV');
        $EW = $elt('ifu2561_20190101_EW');
        $EX = $elt('ifu2561_20190101_EX');
        $EY = $elt('ifu2561_20190101_EY');
        $FA = $elt('ifu2561_20190101_FA');
        $FB = $elt('ifu2561_20190101_FB');
        $FC = $elt('ifu2561_20190101_FC');
        $FD = $elt('ifu2561_20190101_FD');
        $FE = $elt('ifu2561_20190101_FE');
        $FF = $elt('ifu2561_20190101_FF');
        $FG = $elt('ifu2561_20190101_FG');
        $FH = $elt('ifu2561_20190101_FH');
        $FJ = $elt('ifu2561_20190101_FJ');
        $FK = $elt('ifu2561_20190101_FK');
        $FL = $elt('ifu2561_20190101_FL');
        $FM = $elt('ifu2561_20190101_FM');
        $FP = $elt('ifu2561_20190101_FP');
        $FR = $elt('ifu2561_20190101_FR');
        $FS = $elt('ifu2561_20190101_FS');
        $FN = $elt('ifu2561_20190101_FN');
        $ZZ1 = $elt('ifu2561_20190101_ZZ1');
        $ZZ2 = $elt('ifu2561_20190101_ZZ2');

        $assert($isServi($AD), 'erreur_required', $AD);
        $assert($isServi($AN), 'erreur_required', $AN);
        $assert($isServi($AP), 'erreur_required', $AP);
        $assert($isServi($AB), 'erreur_required', $AB);
        $assert($isServi($AC), 'erreur_required', $AC);
        $assert($isServi($AG16), 'erreur_required', $AG16);
        $assert($isServi($AG05), 'erreur_required', $AG05);
        $assert($isServi($AG08), 'erreur_required', $AG08);
        $assert($isServi($AG09), 'erreur_required', $AG09);

        if ($isServi($AE02)) {
            $assert($isServi($AH), 'erreur_required', $AH);
        }

        if ($isServi($AF02)) {
            $assert($isServi($AF01), 'erreur_required', $AF01);
        }

        if ($isServi($AE02) || $isServi($AE03)) { // Si Cas n°1 Personne physique
            $assert($isServi($AE15), 'erreur_required', $AE15);
            if ($isServi($ZZ1) && $float($ZZ1)) {
                $assert($isServi($AE14_1), 'erreur_required', $AE14_1);
            } else {
                $assert($isServi($AE14_2), 'erreur_required', $AE14_2);
            }
            $assert($isServi($AJ), 'erreur_required', $AJ);
        } else {
            $assert(!$isServi($AE15), 'erreur_required', $AE15);
        }

        if ($isServi($AF02)) { // Si Cas n°2 Personne morale
            if ($isServi($ZZ1) && $float($ZZ1)) {
                $assert(!$isServi($AE14_1), 'erreur_not_required', $AE14_1);
            } else {
                $assert(!$isServi($AE14_2), 'erreur_not_required', $AE14_2);
            }
            $assert(!$isServi($AJ), 'erreur_required', $AJ);
        }

        if ($isServi($AF02)) { // Si Cas n°2 Personne morale
            if ($isServi($ZZ1) && $float($ZZ1)) {
                $assert(!$isServi($AE14_2), 'erreur_not_required', $AE14_2);
            } else {
                $assert(!$isServi($AE14_1), 'erreur_not_required', $AE14_1);
            }
            $assert(!$isServi($AJ), 'erreur_not_required', $AJ);
        }

        $value($AG15, $value($AG08));

        $assert(($isServi($AE02) || $isServi($AF02) || $isServi($AE04)),
            'erreur_112_ifu',
            $AE02, $AF02, $AE04);
        $assert(!($isServi($AE02) && $isServi($AF02)),
            'erreur_113_ifu',
            $AE02, $AF02);
        $assert(!($isServi($AF02) && $isServi($AE03)),
            'erreur_113_ifu',
            $AF02, $AE03);
        $assert(!($isServi($AE02) && !$isServi($AE03)),
            'erreur_114_ifu',
            $AE03);

        if ($isServi($BT)) {
            $assert(($isServi($BF) || $isServi($BJ) || $isServi($BH) || $isServi($CA) || $isServi($CB) || $isServi($CC) || $isServi($CD) || $isServi($CT) || $isServi($CW) || $isServi($CX) || $isServi($CZ)),
                'erreur_125_ifu',
                $BT, $BF, $BJ, $BH, $CA, $CB, $CC, $CD, $CT, $CW, $CX, $CZ);
        }

        if ($isServi($BU)) {
            $assert(($isServi($BF) || $isServi($BJ) || $isServi($CA)),
                'erreur_126_ifu',
                $BU, $BF, $BJ, $CA);
        }

        if ($isServi($BV)) {
            $assert(($isServi($CT) || $isServi($CX)),
                'erreur_127_ifu',
                $BV, $CT, $CX);
        }

        $assert(!($isServi($DP) && $isServi($DM)),
            'erreur_129_ifu',
            $DP, $DM);

        $assert(!($isServi($DP) && $isServi($DN)),
            'erreur_129_ifu',
            $DP, $DN);

        if ($isServi($CV)) {
            $assert(($isServi($CU)), 'erreur_133_ifu', $CV, $CU);
        }

        if ($isServi($FL)) {
            $assert(($isServi($FK)), 'erreur_144_ifu', $FL, $FK);
        }

        if ($isServi($FP)) {
            $assert(($isServi($FM)), 'erreur_145_ifu', $FP, $FM);
        }

        if ($isServi($FR)) {
            $assert(($isServi($FJ)), 'erreur_145_ifu', $FR, $FJ);
        }

        $assert(($isServi($BE) || $isServi($BF) || $isServi($BG) || $isServi($BH) || $isServi($BJ) || $isServi($BK) || $isServi($BN)
            || $isServi($BP) || $isServi($BR) || $isServi($BS) || $isServi($BV) || $isServi($CA) || $isServi($CB) || $isServi($CC)
            || $isServi($CD) || $isServi($CT) || $isServi($CU) || $isServi($CW) || $isServi($CX) || $isServi($CY) || $isServi($CZ)
            || $isServi($CF) || $isServi($CG) || $isServi($CJ) || $isServi($CK) || $isServi($CL) || $isServi($CM) || $isServi($DB)
            || $isServi($CN) || $isServi($DE) || $isServi($DF) || $isServi($DG) || $isServi($DC) || $isServi($CP) || $isServi($CR)
            || $isServi($CS) || $isServi($DH) || $isServi($DJ) || $isServi($DD) || $isServi($EB) || $isServi($EC) || $isServi($ED)
            || $isServi($EE) || $isServi($EF) || $isServi($EG) || $isServi($EH) || $isServi($FB) || $isServi($FC) || $isServi($FJ) || $isServi($FK) || $isServi($FM) || $isServi($FN) || $isServi($FD) || $isServi($FD)
            || $isServi($FE) || $isServi($FF) || $isServi($FG) || $isServi($FH) || $isServi($EJ) || $isServi($EK) || $isServi($DL)
            || $isServi($DM) || $isServi($DN) || $isServi($DP) || $isServi($EM) || $isServi($EN) || $isServi($EP) || $isServi($ER)
            || $isServi($ES) || $isServi($ET) || $isServi($EU) || $isServi($EV) || $isServi($EW) || $isServi($EX)),
            'erreur_130_ifu',
            $BE, $BF, $BG, $BH, $BJ, $BK, $BN, $BP, $BR, $BS, $BV, $CA, $CB, $CC, $CD, $CT, $CU, $CW, $CX, $CY, $CZ, $CF, $CG,
            $CJ, $CK, $CL, $CM, $DB, $CN, $DE, $DF, $DG, $DC, $CP, $CR, $CS, $DH, $DJ, $DD, $EB, $EC, $ED, $EE, $EF, $EG, $EH,
            $FB, $FC, $FJ, $FK, $FM, $FN, $FD, $FE, $FF, $FG, $FH, $EJ, $EK, $DL, $DM, $DN, $DP, $EM, $EN, $EP, $ER, $ES, $ET, $EU, $EV, $EW, $EX);

        if ($isServi($BA)) {
            $assert(($isServi($CT) || $isServi($BF) || $isServi($BJ) || $isServi($CA)),
                'erreur_216_ifu',
                $BA, $CT, $BF, $BJ, $CA);
        }

        if ($isServi($BC)) {
            $assert(($isServi($BF) || $isServi($BH) || $isServi($BJ) || $isServi($CA) || $isServi($CB) || $isServi($CC) || $isServi($CD) || $isServi($CT) || $isServi($CW) || $isServi($CX) || $isServi($CZ)),
                'erreur_217_ifu',
                $BF, $BH, $BJ, $CA, $CB, $CC, $CD, $CT, $CW, $CX, $CZ);
        }

        $assert(!($isServi($BP) && !$isServi($BN)),
            'erreur_218_ifu',
            $BP, $BN);

        if ($isServi($CR)) {
            $assert(($isServi($DE) || $isServi($DF) || $isServi($DG) || $isServi($DC) || $isServi($CP)),
                'erreur_219_ifu',
                $DE, $DF, $DG, $DC, $CP);
        }

        if ($isServi($DH) || $isServi($DJ)) {
            $assert(($isServi($DD)), 'erreur_220_ifu', $DH, $DJ, $DD);
        }

        if ($isServi($DA)) {
            $assert(($isServi($DB) || $isServi($DD)),
                'erreur_221_ifu',
                $DA, $DB, $DD);
        }

        $assert(!($isServi($EB) && !$isServi($EA)),
            'erreur_222_ifu',
            $EB, $EA);

        if ($isServi($EC) || $isServi($ED) || $isServi($EE) || $isServi($EF) || $isServi($EG) || $isServi($EH)) {
            $assert(($isServi($EA) && $isServi($EB)),
                'erreur_223_ifu',
                $EC, $ED, $EE, $EF, $EG, $EH, $EA, $EB);
        }

        $assert(!($isServi($ED) && !$isServi($EE)),
            'erreur_224_ifu',
            $ED, $EE);

        $assert(!($isServi($EE) && !$isServi($ED)),
            'erreur_224_ifu',
            $ED, $EE);

        if ($isServi($EH)) {
            $assert(($isServi($EF) || $isServi($EG)),
                'erreur_225_ifu',
                $EH, $EF, $EG);
        }

        if ($isServi($FC) || $isServi($FD) || $isServi($FE) || $isServi($FF) || $isServi($FG) || $isServi($FH)) {
            $assert(($isServi($FA) && $isServi($FB)),
                'erreur_223_ifu',
                $FC, $FD, $FE, $FF, $FG, $FH, $FA, $FB);
        }

        $assert(!($isServi($FB) && !$isServi($FA)),
            'erreur_227_ifu',
            $FB, $FA);

        $assert(!($isServi($FD) && !$isServi($FE)),
            'erreur_228_ifu',
            $FD, $FE);

        $assert(!($isServi($FE) && !$isServi($FD)),
            'erreur_228_ifu',
            $FD, $FE);


        if ($isServi($EY)) {
            $assert(($isServi($EM) || $isServi($EX)),
                'erreur_231_ifu',
                $EY, $EM, $EX);
        }

        if ($isServi($AE14_2)) {
            $assert((substr($value($AE14_2), 0, 2) == 99), 'erreur_ifu_etranger', $AE14_2);
        }

        if ($isServi($AG14_2)) {
            $assert((substr($value($AG14_2), 0, 2) == 99), 'erreur_ifu_etranger', $AG14_2);
        }

        if ($isServi($FH)) {
            $assert(($isServi($FF) || $isServi($FG)),
                'erreur_229_ifu',
                $FH, $FF, $FG);
        }

        $assert(!($isServi($DL) && !$isServi($DK)),
            'erreur_230_ifu',
            $DL, $DK);

        if ($isServi($EY)) {
            $assert(($isServi($EM) || $isServi($EX)),
                'erreur_231_ifu',
                $EY, $EM, $EX);
        }
    }

    public static function a_identif_hon_20190101($elt, $assert, $isServi, $float, $value, $controls)
    {
        // Variables
        $AA01 = $elt('a_identif_hon_20190101_AA01');
        $AA02 = $elt('a_identif_hon_20190101_AA02');
        $AA05 = $elt('a_identif_hon_20190101_AA05');
        $AA06 = $elt('a_identif_hon_20190101_AA06');
        $AA08 = $elt('a_identif_hon_20190101_AA08');
        $AA09 = $elt('a_identif_hon_20190101_AA09');
        $AA11 = $elt('a_identif_hon_20190101_AA11');
        $AA12 = $elt('a_identif_hon_20190101_AA12');
        $AA13 = $elt('a_identif_hon_20190101_AA13');
        $AA14 = $elt('a_identif_hon_20190101_AA14');
        $AA15 = $elt('a_identif_hon_20190101_AA15');
        $AA16 = $elt('a_identif_hon_20190101_AA16');
        $AA17 = $elt('a_identif_hon_20190101_AA17');
        $AB01 = $elt('a_identif_hon_20190101_AB01');
        $AB05 = $elt('a_identif_hon_20190101_AB05');
        $AB06 = $elt('a_identif_hon_20190101_AB06');
        $AB08 = $elt('a_identif_hon_20190101_AB08');
        $AB09 = $elt('a_identif_hon_20190101_AB09');
        $AB14 = $elt('a_identif_hon_20190101_AB14');
        $AB15 = $elt('a_identif_hon_20190101_AB15');
        $AB16 = $elt('a_identif_hon_20190101_AB16');
        $AB17 = $elt('a_identif_hon_20190101_AB17');
        $BA = $elt('a_identif_hon_20190101_BA');
        $BD = $elt('a_identif_hon_20190101_BD');
        $BB = $elt('a_identif_hon_20190101_BB');
        $BC = $elt('a_identif_hon_20190101_BC');
        $CA = $elt('a_identif_hon_20190101_CA');
        $CB = $elt('a_identif_hon_20190101_CB');
        $DA = $elt('a_identif_hon_20190101_DA');

        $value($AB01, $value($AA01));
        $value($AB05, $value($AA05));
        $value($AB06, $value($AA06));
        $value($AB08, $value($AA08));
        $value($AB09, $value($AA09));
        $value($AB16, $value($AA16));
        $value($AB17, $value($AA17));

        $assert($isServi($AA01), 'erreur_required', $AA01);
        $assert($isServi($AA02), 'erreur_required', $AA02);
        $assert($isServi($AA05), 'erreur_required', $AA05);
        $assert($isServi($AA08), 'erreur_required', $AA08);
        $assert($isServi($AA09), 'erreur_required', $AA09);
        $assert($isServi($AA11), 'erreur_required', $AA11);
        $assert($isServi($AA12), 'erreur_required', $AA12);
        $assert($isServi($AA13), 'erreur_required', $AA13);
        $assert($isServi($AA16), 'erreur_required', $AA16);
        $assert($isServi($AB05), 'erreur_required', $AB05);
        $assert($isServi($AB08), 'erreur_required', $AB08);
        $assert($isServi($AB09), 'erreur_required', $AB09);
        $assert($isServi($AB14), 'erreur_required', $AB14);
        $assert($isServi($AB16), 'erreur_required', $AB16);

        $assert($isServi($BA), 'erreur_required', $BA);
        $assert($isServi($BB), 'erreur_required', $BB);
        $assert($isServi($BC), 'erreur_required', $BC);

        $assert($isServi($CA), 'erreur_required', $CA);

        if ($isServi($AA08)) {
            $value($AA15, $value($AA08));
        }

        if ($isServi($AB08)) {
            $value($AB15, $value($AB08));
        }
    }

    public static function das2t_20190101($elt, $assert, $isServi, $float, $value, $controls)
    {
        $rowIndex = 1;
        $natureUsed = array();

        while ($elt('das2t_20190101_UA/' . $rowIndex)->isset) {
            $UA = $elt('das2t_20190101_UA/' . $rowIndex);
            $TA = $elt('das2t_20190101_TA/' . $rowIndex);

            if ($isServi($UA)) {
                $assert(!in_array($value($UA), $natureUsed), 'erreur_das_multiple_ua', $UA);
                $natureUsed[] = $value($UA);
            }


            $rowIndex++;
        }
    }

    public static function das2tv_20190101($elt, $assert, $isServi, $float, $value, $controls) {
      /** Variables */
      /*$AD = $elt('das2tv_20190101_AD');
      $AE02 = $elt('das2tv_20190101_AE02');
      $AE03 = $elt('das2tv_20190101_AE03');
      $AF01 = $elt('das2tv_20190101_AF01');
      $AF02 = $elt('das2tv_20190101_AF02');
      $AF03 = $elt('das2tv_20190101_AF03');
      $AG05 = $elt('das2tv_20190101_AG05');
      $AG06 = $elt('das2tv_20190101_AG06');
      $AG08 = $elt('das2tv_20190101_AG08');
      $AG09 = $elt('das2tv_20190101_AG09');
      $AG14_1 = $elt('das2tv_20190101_AG14_1');
      $AG14_2 = $elt('das2tv_20190101_AG14_2');
      $AG15 = $elt('das2tv_20190101_AG15');
      $AG16 = $elt('das2tv_20190101_AG16');
      $AG17 = $elt('das2tv_20190101_AG17');
      $AH = $elt('das2tv_20190101_AH');

      // B..
      $BB = $elt('das2tv_20190101_BB');
      $BC = $elt('das2tv_20190101_BC');
      $BD = $elt('das2tv_20190101_BD');
      $BE = $elt('das2tv_20190101_BE');

      // C..
      $CA = $elt('das2tv_20190101_CA-1');
      $CB = $elt('das2tv_20190101_CB');
      $CC = $elt('das2tv_20190101_CC');
      $CD = $elt('das2tv_20190101_CD');

      $ZZ1 = $elt('das2tv_20190101_ZZ1');

      /** Controls */
      /*$assert($isServi($AE02) || $isServi($AF02), 'erreur_310_das2', $AF02, $AE02);

      if ($isServi($AF03)) {
          $assert($isServi($AF02), 'erreur_310_das2', $AF03, $AF02);
      }

      if ($isServi($AE02)) {
          $assert($isServi($AE03), 'erreur_311_das2', $AE03);
      }

      if ($isServi($AG08)) {
          $value($AG15, $value($AG08));
      }

      if ($float($ZZ1)) {
          $assert($isServi($AG14_1), 'erreur_required', $AG14_1);
      } else {
          $assert($isServi($AG14_2), 'erreur_required', $AG14_2);
          $assert((substr($value($AG14_2), 0, 2) == 99 && substr($value($AG09), 0, 2) == 99), 'erreur_das_etranger', $AG09, $AG14_2);
      }

      $rowIndex = 1;
      while ($elt('das2tv_20190101_BA/' . $rowIndex)->isset) {
          $BA = $elt('das2tv_20190101_BA/' . $rowIndex);
          $CA = $elt('das2tv_20190101_CA/' . $rowIndex);
          $assert($isServi($BA) || $isServi($BB) || $isServi($BC), 'erreur_316_das2', $BA, $BB, $BC);

          if ($isServi($BA)) {
              $assert($isServi($CA), 'erreur_317_das2', $CA, $BA);
          }

          $rowIndex++;
      }

      if ($isServi($BB)) {
          $assert($isServi($CB), 'erreur_318_das2', $CB, $BB);
      }

      if ($isServi($BC)) {
          $assert($isServi($CC), 'erreur_319_das2', $CC, $BC);
      }

      if ($isServi($BD)) {
          $assert($isServi($CD), 'erreur_320_das2', $CD, $BD);
      }*/
    }

    public static function tva3519_20190101($elt, $assert, $isServi, $float, $value, $controls)
    {
        $CB = $elt('t_identif_20151020_CB');
        $AA1 = $elt('tva3519_20190101_AA1');
        $AA2 = $elt('tva3519_20190101_AA2');
        $AA3 = $elt('tva3519_20190101_AA3');
        $AA4 = $elt('tva3519_20190101_AA4');
        $DC1 = $elt('tva3519_20190101_DC1');
        $DC10 = $elt('tva3519_20190101_DC10');
        $DC2 = $elt('tva3519_20190101_DC2');
        $DC3 = $elt('tva3519_20190101_DC3');
        $DC4 = $elt('tva3519_20190101_DC4');
        $DC5 = $elt('tva3519_20190101_DC5');
        $DC6 = $elt('tva3519_20190101_DC6');
        $DC7 = $elt('tva3519_20190101_DC7');
        $DC8 = $elt('tva3519_20190101_DC8');
        $DC9 = $elt('tva3519_20190101_DC9');
        $DD = $elt('tva3519_20190101_DD');
        $DE = $elt('tva3519_20190101_DE');
        $DF = $elt('tva3519_20190101_DF');
        $DG1 = $elt('tva3519_20190101_DG1');
        $DG2 = $elt('tva3519_20190101_DG2');
        $DG3 = $elt('tva3519_20190101_DG3');
        $DG4 = $elt('tva3519_20190101_DG4');
        $DI = $elt('tva3519_20190101_DI');
        $DJ = $elt('tva3519_20190101_DJ');
        $DK = $elt('tva3519_20190101_DK');
        $DL = $elt('tva3519_20190101_DL');
        $DM = $elt('tva3519_20190101_DM');
        $DN = $elt('tva3519_20190101_DN');
        $FJ = $elt('tva3519_20190101_FJ');
        $FK = $elt('tva3519_20190101_FK');
        $FL = $elt('tva3519_20190101_FL');


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
        $assert($isServi($DN) && $float($DN) > 0, 'erreur_219', $DN);
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

    public static function tva3310ca3g_20190101($elt, $assert, $isServi, $float, $value, $controls)
    {
        $BA = $elt('tva3310ca3g_20190101_BA');
        $BB = $elt('tva3310ca3g_20190101_BB');
        $BC = $elt('tva3310ca3g_20190101_BC');
        $DA = $elt('tva3310ca3g_20190101_DA');
        $DB = $elt('tva3310ca3g_20190101_DB');
        $DC = $elt('tva3310ca3g_20190101_DC');
        $DD = $elt('tva3310ca3g_20190101_DD');
        $EA = $elt('tva3310ca3g_20190101_EA');
        $EB = $elt('tva3310ca3g_20190101_EB');
        $EC = $elt('tva3310ca3g_20190101_EC');
        $FA = $elt('tva3310ca3g_20190101_FA');
        $FB = $elt('tva3310ca3g_20190101_FB');
        $FE = $elt('tva3310ca3g_20190101_FE');
        $GA = $elt('tva3310ca3g_20190101_GA');
        $GB = $elt('tva3310ca3g_20190101_GB');
        $GD = $elt('tva3310ca3g_20190101_GD');
        $GH = $elt('tva3310ca3g_20190101_GH');
        $GJ = $elt('tva3310ca3g_20190101_GJ');
        $GK = $elt('tva3310ca3g_20190101_GK');
        $GL = $elt('tva3310ca3g_20190101_GL');
        $GM = $elt('tva3310ca3g_20190101_GM');
        $GO = $elt('tva3310ca3g_20190101_GO');
        $GP = $elt('tva3310ca3g_20190101_GP');
        $GQ = $elt('tva3310ca3g_20190101_GQ');
        $GR = $elt('tva3310ca3g_20190101_GR');
        $GS = $elt('tva3310ca3g_20190101_GS');
        $GT = $elt('tva3310ca3g_20190101_GT');
        $GU = $elt('tva3310ca3g_20190101_GU');
        $GV = $elt('tva3310ca3g_20190101_GV');
        $GX = $elt('tva3310ca3g_20190101_GX');
        $GZ = $elt('tva3310ca3g_20190101_GZ');
        $HE = $elt('tva3310ca3g_20190101_HE');
        $HK = $elt('tva3310ca3g_20190101_HK');
        $HL = $elt('tva3310ca3g_20190101_HL');
        $HN = $elt('tva3310ca3g_20190101_HN');
        $HO = $elt('tva3310ca3g_20190101_HO');
        $HP = $elt('tva3310ca3g_20190101_HP');
        $HQ = $elt('tva3310ca3g_20190101_HQ');
        $HR = $elt('tva3310ca3g_20190101_HR');
        $HS = $elt('tva3310ca3g_20190101_HS');
        $HT = $elt('tva3310ca3g_20190101_HT');
        $HU = $elt('tva3310ca3g_20190101_HU');
        $KF = $elt('tva3310ca3g_20190101_KF');
        $KH = $elt('tva3310ca3g_20190101_KH');
        $KJ = $elt('tva3310ca3g_20190101_KJ');
        $KK = $elt('tva3310ca3g_20190101_KK');
        $KL = $elt('tva3310ca3g_20190101_KL');
        $KM = $elt('tva3310ca3g_20190101_KM');
        $KN = $elt('tva3310ca3g_20190101_KN');
        $KR = $elt('tva3310ca3g_20190101_KR');
        $KS = $elt('tva3310ca3g_20190101_KS');
        $KT = $elt('tva3310ca3g_20190101_KT');
        $KU = $elt('tva3310ca3g_20190101_KU');
        $KV = $elt('tva3310ca3g_20190101_KV');
        $KW = $elt('tva3310ca3g_20190101_KW');
        $KX = $elt('tva3310ca3g_20190101_KX');
        $KY = $elt('tva3310ca3g_20190101_KY');
        $KZ = $elt('tva3310ca3g_20190101_KZ');
        $LA = $elt('tva3310ca3g_20190101_LA');
        $LB = $elt('tva3310ca3g_20190101_LB');
        $LC = $elt('tva3310ca3g_20190101_LC');
        $LD = $elt('tva3310ca3g_20190101_LD');
        $LF = $elt('tva3310ca3g_20190101_LF');
        $LG = $elt('tva3310ca3g_20190101_LG');
        $MA = $elt('tva3310ca3g_20190101_MA');
        $MB = $elt('tva3310ca3g_20190101_MB');
        $MC = $elt('tva3310ca3g_20190101_MC');
        $MD = $elt('tva3310ca3g_20190101_MD');
        $ME = $elt('tva3310ca3g_20190101_ME');
        $MF = $elt('tva3310ca3g_20190101_MF');
        $MG = $elt('tva3310ca3g_20190101_MG');
        $MH = $elt('tva3310ca3g_20190101_MH');
        $MJ = $elt('tva3310ca3g_20190101_MJ');
        $MK = $elt('tva3310ca3g_20190101_MK');
        $ML = $elt('tva3310ca3g_20190101_ML');
        $MN = $elt('tva3310ca3g_20190101_MN');
        $MP = $elt('tva3310ca3g_20190101_MP');
        $MS = $elt('tva3310ca3g_20190101_MS');
        $NA = $elt('tva3310ca3g_20190101_NA');
        $NB = $elt('tva3310ca3g_20190101_NB');
        $NC = $elt('tva3310ca3g_20190101_NC');
        $ND = $elt('tva3310ca3g_20190101_ND');
        $NE = $elt('tva3310ca3g_20190101_NE');
        $NF = $elt('tva3310ca3g_20190101_NF');
        $NG = $elt('tva3310ca3g_20190101_NG');
        $NH = $elt('tva3310ca3g_20190101_NH');
        $NK = $elt('tva3310ca3g_20190101_NK');
        $NL = $elt('tva3310ca3g_20190101_NL');
        $NM = $elt('tva3310ca3g_20190101_NM');
        $NQ = $elt('tva3310ca3g_20190101_NQ');
        $NU = $elt('tva3310ca3g_20190101_NU');
        $NV = $elt('tva3310ca3g_20190101_NV');
        $NX = $elt('tva3310ca3g_20190101_NX');
        $NY = $elt('tva3310ca3g_20190101_NY');
        $NZ = $elt('tva3310ca3g_20190101_NZ');
        $PC = $elt('tva3310ca3g_20190101_PC');

        $rowIndex = 1;
        while ($elt('tva3310ca3g_20190101_NN/' . $rowIndex)->isset) {
            $NP = $elt('tva3310ca3g_20190101_NP/' . $rowIndex);
            $NN = $elt('tva3310ca3g_20190101_NN/' . $rowIndex);

            $assert(!(($isServi($NP) || $isServi($NN)) && !($isServi($NP) && $isServi($NN))),
                'erreur_212', $NP, $NN);

            $rowIndex++;
        }

        $rowIndex = 1;
        while ($elt('tva3310ca3g_20190101_PB/' . $rowIndex)->isset) {
            $PB = $elt('tva3310ca3g_20190101_PB/' . $rowIndex);
            $PA = $elt('tva3310ca3g_20190101_PA/' . $rowIndex);

            $assert(!(($isServi($PB) || $isServi($PA)) && !($isServi($PB) && $isServi($PA))),
                'erreur_233_tva_ca3g', $PB, $PA);

            $rowIndex++;
        }

        $assert(!($isServi($BC) && !$isServi($BA)),
            'erreur_128', $BA, $BC);
        $assert(!($isServi($EB) && $isServi($EA) && !($float($EB) <= $float($EA))),
            'erreur_131', $EA, $EB);
        if (!$value($KF)) {
            $assert(($isServi($KR) && $float($KR) > 0) || ($isServi($DC) && $float($DC) > 0) || ($isServi($HK) && $float($HK) > 0),
                'erreur_212', $KR, $DC, $HK);

            $assert(!(!$isServi($KR) &&
                !$isServi($DA) &&
                !$isServi($DB) &&
                !$isServi($DC) &&
                !$isServi($DD) &&
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
                !$isServi($HP) &&
                !$isServi($HL) &&
                !$isServi($HQ) &&
                !$isServi($HR) &&
                !$isServi($HS) &&
                !$isServi($HU) &&
                !$isServi($LG) &&
                !$isServi($KS) &&
                !$isServi($KT) &&
                !$isServi($KJ) &&
                !$isServi($KK) &&
                !$isServi($KL) &&
                !$isServi($KM) &&
                !$isServi($KU) &&
                !$isServi($KV) &&
                !$isServi($KW) &&
                !$isServi($KX) &&
                !$isServi($KY) &&
                !$isServi($KZ) &&
                !$isServi($MA) &&
                !$isServi($MB) &&
                !$isServi($MC) &&
                !$isServi($MD) &&
                !$isServi($ME) &&
                !$isServi($MF) &&
                !$isServi($MG) &&
                !$isServi($MH) &&
                !$isServi($MJ) &&
                !$isServi($MK) &&
                !$isServi($ML) &&
                !$isServi($MN) &&
                !$isServi($MP) &&
                !$isServi($MS) &&
                !$isServi($NA) &&
                !$isServi($NB) &&
                !$isServi($NC) &&
                !$isServi($ND) &&
                !$isServi($NE) &&
                !$isServi($NF) &&
                !$isServi($NG) &&
                !$isServi($NH) &&
                !$isServi($NK) &&
                !$isServi($NL) &&
                !$isServi($NM) &&
                !$isServi($NN) &&
                !$isServi($NU) &&
                !$isServi($NV) &&
                !$isServi($NX) &&
                !$isServi($NY) &&
                !$isServi($NZ)),
                "erreur_049",
                $DA, $DB, $DC, $DD, $EA, $EB, $EC, $FA, $FB, $FE, $GA, $GB, $HN, $GF, $GH, $GJ, $GK, $GL, $GM, $GO, $GP, $GQ, $GR, $GS, $GT, $GU, $GU, $GV, $GX, $GZ,
                $HO, $HP, $HL, $HQ, $HR, $HS, $HU, $LG, $KS, $KT, $KJ, $KK, $KL, $KM, $KR, $KU, $KV, $KW, $KX, $KY, $KZ,
                $MA, $MB, $MC, $MD, $ME, $MF, $MG, $MH, $MJ, $MK, $ML, $MN, $MP, $MS,
                $NA, $NB, $NC, $ND, $NE, $NF, $NG, $NH, $NK, $NL, $NM, $NN, $NU, $NV, $NX, $NY, $NZ);
        }
    }

    public static function tva3310ca3_20190101($elt, $assert, $isServi, $float, $value, $controls)
    {
        $BA = $elt('tva3310ca3_20190101_BA');
        $BB = $elt('tva3310ca3_20190101_BB');
        $BC = $elt('tva3310ca3_20190101_BC');

        $CA = $elt('tva3310ca3_20190101_CA');
        $CB = $elt('tva3310ca3_20190101_CB');
        $CC = $elt('tva3310ca3_20190101_CC');
        $CD = $elt('tva3310ca3_20190101_CD');
        $CE = $elt('tva3310ca3_20190101_CE');
        $CF = $elt('tva3310ca3_20190101_CF');
        $CG = $elt('tva3310ca3_20190101_CG');

        $DA = $elt('tva3310ca3_20190101_DA');
        $DB = $elt('tva3310ca3_20190101_DB');
        $DC = $elt('tva3310ca3_20190101_DC');
        $DD = $elt('tva3310ca3_20190101_DD');
        $DE = $elt('tva3310ca3_20190101_DE');
        $DF = $elt('tva3310ca3_20190101_DF');
        $DG = $elt('tva3310ca3_20190101_DG');
        $DH = $elt('tva3310ca3_20190101_DH');

        $FB = $elt('tva3310ca3_20190101_FB');
        $FC = $elt('tva3310ca3_20190101_FC');
        $FD = $elt('tva3310ca3_20190101_FD');
        $FG = $elt('tva3310ca3_20190101_FG');
        $FH = $elt('tva3310ca3_20190101_FH');
        $FJ = $elt('tva3310ca3_20190101_FJ');
        $FK = $elt('tva3310ca3_20190101_FK');
        $FM = $elt('tva3310ca3_20190101_FM');
        $FN = $elt('tva3310ca3_20190101_FN');
        $FP = $elt('tva3310ca3_20190101_FP');
        $FR = $elt('tva3310ca3_20190101_FR');

        $GB = $elt('tva3310ca3_20190101_GB');
        $GC = $elt('tva3310ca3_20190101_GC');
        $GD = $elt('tva3310ca3_20190101_GD');
        $GG = $elt('tva3310ca3_20190101_GG');
        $GH = $elt('tva3310ca3_20190101_GH');
        $GJ = $elt('tva3310ca3_20190101_GJ');
        $GK = $elt('tva3310ca3_20190101_GK');
        $GM = $elt('tva3310ca3_20190101_GM');
        $GN = $elt('tva3310ca3_20190101_GN');
        $GP = $elt('tva3310ca3_20190101_GP');
        $GR = $elt('tva3310ca3_20190101_GR');

        $HA = $elt('tva3310ca3_20190101_HA');
        $HB = $elt('tva3310ca3_20190101_HB');
        $HC = $elt('tva3310ca3_20190101_HC');
        $HD = $elt('tva3310ca3_20190101_HD');
        $HE = $elt('tva3310ca3_20190101_HE');
        $HF = $elt('tva3310ca3_20190101_HF');
        $HG = $elt('tva3310ca3_20190101_HG');
        $HH = $elt('tva3310ca3_20190101_HH');
        $HJ = $elt('tva3310ca3_20190101_HJ');

        $KA = $elt('tva3310ca3_20190101_KA');
        $KB = $elt('tva3310ca3_20190101_KB');
        $KE = $elt('tva3310ca3_20190101_KE');
        $KF = $elt('tva3310ca3_20190101_KF');
        $KH = $elt('tva3310ca3_20190101_KH');
        $KJ = $elt('tva3310ca3_20190101_KJ');
        $KL = $elt('tva3310ca3_20190101_KL');
        $KR = $elt('tva3310ca3_20190101_KR');
        $KS = $elt('tva3310ca3_20190101_KS');
        $KT = $elt('tva3310ca3_20190101_KT');
        $KU = $elt('tva3310ca3_20190101_KU');

        $JA = $elt('tva3310ca3_20190101_JA');
        $JB = $elt('tva3310ca3_20190101_JB');
        $JC = $elt('tva3310ca3_20190101_JC');

        // ----

        /* tva3515sd */

        $CA_sd = $elt('tva3515sd_20190101_CA');
        $CB_sd = $elt('tva3515sd_20190101_CB');
        $BC_sd = $elt('tva3515sd_20190101_BC');
        $BD_sd = $elt('tva3515sd_20190101_BD');

        $BE_sd = $elt('tva3515sd_20190101_BE');
        $BF_sd = $elt('tva3515sd_20190101_BF');
        $DD_sd = $elt('tva3515sd_20190101_DD');
        $GD_sd = $elt('tva3515sd_20190101_DD');

        if ($isServi($GD_sd) && $float($GD_sd) > 0) {
            $assert(!($float($KS) >= $float($GD_sd)), 'erreur_sd', $KS);
        }


        $assert(!((($isServi($FD) && $float($FD) > 0) || ($isServi($GD) && $float($GD) > 0)) && !$isServi($elt('tva3310a_20190101_HB'))),
            'erreur_013',
            $GD, $FD);
        if (!$KF->isset) {

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
            $assert(!($isServi($HF) && $isServi($HG) && !($float($HF) <= $float($HG))), 'erreur_205', $HF, $HG);
            $assert(!($isServi($JB) && $isServi($JA) && $isServi($KJ) && !($float($JB) <= $float($JA) - $float($KJ))), 'erreur_131', $JA, $JB, $KJ);


            $assert(!($isServi($KB) && $float($KB) > 0 && !$isServi($elt('tva3310a_20190101_HB'))),
                'erreur_013',
                $KB);

            $GH_control_value = $float($GJ) + $float($GK) + $float($KT);
            $assert(!($GH_control_value > $float($GH)),
                'erreur_121',
                $GJ, $GK, $KT);

            $GH_control_value = $float($GJ) + $float($GK) + $float($KT);
            $assert(!($GH_control_value > $float($GH)),
                'erreur_121',
                $GJ, $GK, $KT);

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
                        || ($isServi($HF) && $float($HF) > 0)
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
                $HF, $KH, $KL, $KR, $KS, $KT, $KU, $JA, $JB, $JC);

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
                || ($isServi($HF) && $float($HF) > 0)
                || ($isServi($JA) && $float($JA) > 0)
                || ($isServi($JB) && $float($JB) > 0)
                || ($isServi($KJ) && $float($KJ) > 0)
                || ($isServi($JC) && $float($JC) > 0)
                || ($isServi($KA) && $float($KA) > 0)
                || ($isServi($KB) && $float($KB) > 0)
                || ($isServi($KL) && $float($KL) > 0)
                || ($isServi($KE) && $float($KE) > 0)
                || ($isServi($DH) && $float($DH) > 0)), "erreur_049", $KF);
        }
    }

    public static function tva3310ter_20190101($elt, $assert, $isServi, $float, $value, $controls)
    {
        $AA = $elt('tva3310ter_20190101_AA');
        $AB = $elt('tva3310ter_20190101_AB');
        $AC = $elt('tva3310ter_20190101_AC');
        $DL = $elt('tva3310ter_20190101_DL');
        $EL = $elt('tva3310ter_20190101_EL');
        $FL = $elt('tva3310ter_20190101_FL');
        $GL = $elt('tva3310ter_20190101_GL');
        $HL = $elt('tva3310ter_20190101_HL');
        $JL = $elt('tva3310ter_20190101_JL');
        $KL = $elt('tva3310ter_20190101_KL');
        $LL = $elt('tva3310ter_20190101_LL');
        $ML = $elt('tva3310ter_20190101_ML');
        $NL = $elt('tva3310ter_20190101_NL');
        $PL = $elt('tva3310ter_20190101_PL');
        $QL = $elt('tva3310ter_20190101_QL');
        $RL = $elt('tva3310ter_20190101_RL');
        $QM = $elt('tva3310ter_20190101_QM');
        $RM = $elt('tva3310ter_20190101_RM');

        // ---

        $rowIndex = 1;
        while ($elt('tva3310ter_20190101_BM/' . $rowIndex)->isset) {
            $BM = $elt('tva3310ter_20190101_BM/' . $rowIndex);
            $CM = $elt('tva3310ter_20190101_CM/' . $rowIndex);

            $assert(!($isServi($BM) && !($isServi($CM) && 0 <= $float($CM) && $float($CM) <= 100)),
                'erreur_116', $BM, $CM);

            $rowIndex++;
        }

        $assert(!($isServi($AC)
            && !$isServi($AA)),
            'erreur_128', $AC, $AA);

        $assert($isServi($AB) && !(($isServi($QM) || $isServi($RM)) && !(0 < $float($AB) && $float($AB) <= 100)),
            'erreur_222', $AB);
    }

    public static function tva3515sd_20190101($elt, $assert, $isServi, $float, $value, $controls)
    {
        $AA = $elt('tva3515sd_20190101_AA');
        $AB = $elt('tva3515sd_20190101_AB');
        $BB = $elt('tva3515sd_20190101_BB');
        $BC = $elt('tva3515sd_20190101_BC');
        $BD = $elt('tva3515sd_20190101_BD');
        $BE = $elt('tva3515sd_20190101_BE');
        $BF = $elt('tva3515sd_20190101_BF');
        $CA = $elt('tva3515sd_20190101_CA');
        $CB = $elt('tva3515sd_20190101_CB');
        $DA = $elt('tva3515sd_20190101_DA');
        $DB = $elt('tva3515sd_20190101_DB');
        $DC = $elt('tva3515sd_20190101_DC');
        $DD = $elt('tva3515sd_20190101_DD');
        $EA = $elt('tva3515sd_20190101_EA');
        $EB = $elt('tva3515sd_20190101_EB');

        $assert(!($isServi($CA) && $isServi($BD) && !($float($CA) >= $float($BD))),
            'erreur_115', $CA, $BD);

        $assert(!($isServi($EB)
            && !$isServi($EA)),
            'erreur_128', $EA, $EB);
    }

    public static function tva3310a_20190101($elt, $assert, $isServi, $float, $value, $controls)
    {
        $BA = $elt('tva3310a_20190101_BA');
        $BB = $elt('tva3310a_20190101_BB');
        $BC = $elt('tva3310a_20190101_BC');
        $BE = $elt('tva3310a_20190101_BE');
        $BF = $elt('tva3310a_20190101_BF');
        $BK = $elt('tva3310a_20190101_BK');
        $BM = $elt('tva3310a_20190101_BM');
        $BN = $elt('tva3310a_20190101_BN');
        $BP = $elt('tva3310a_20190101_BP');
        $BQ = $elt('tva3310a_20190101_BQ');
        $BR = $elt('tva3310a_20190101_BR');
        $BS = $elt('tva3310a_20190101_BS');
        $CA = $elt('tva3310a_20190101_CA');
        $CB = $elt('tva3310a_20190101_CB');
        $CC = $elt('tva3310a_20190101_CC');
        $CE = $elt('tva3310a_20190101_CE');
        $CF = $elt('tva3310a_20190101_CF');
        $CK = $elt('tva3310a_20190101_CK');
        $CM = $elt('tva3310a_20190101_CM');
        $CN = $elt('tva3310a_20190101_CN');
        $CP = $elt('tva3310a_20190101_CP');
        $CQ = $elt('tva3310a_20190101_CQ');
        $CR = $elt('tva3310a_20190101_CR');
        $CS = $elt('tva3310a_20190101_CS');
        $DA = $elt('tva3310a_20190101_DA');
        $DB = $elt('tva3310a_20190101_DB');
        $FA = $elt('tva3310a_20190101_FA');
        $FB = $elt('tva3310a_20190101_FB');
        $FG = $elt('tva3310a_20190101_FG');
        $FJ = $elt('tva3310a_20190101_FJ');
        $FR = $elt('tva3310a_20190101_FR');
        $FT = $elt('tva3310a_20190101_FT');
        $FV = $elt('tva3310a_20190101_FV');
        $HB = $elt('tva3310a_20190101_HB');
        $HE = $elt('tva3310a_20190101_HE');
        $HF = $elt('tva3310a_20190101_HF');
        $HI = $elt('tva3310a_20190101_HI');
        $JA = $elt('tva3310a_20190101_JA');
        $JB = $elt('tva3310a_20190101_JB');
        $JC = $elt('tva3310a_20190101_JC');
        $JD = $elt('tva3310a_20190101_JD');
        $JE = $elt('tva3310a_20190101_JE');
        $JF = $elt('tva3310a_20190101_JF');
        $JG = $elt('tva3310a_20190101_JG');
        $JH = $elt('tva3310a_20190101_JH');
        $JJ = $elt('tva3310a_20190101_JJ');
        $JK = $elt('tva3310a_20190101_JK');
        $JL = $elt('tva3310a_20190101_JL');
        $JM = $elt('tva3310a_20190101_JM');
        $JN = $elt('tva3310a_20190101_JN');
        $JP = $elt('tva3310a_20190101_JP');
        $JQ = $elt('tva3310a_20190101_JQ');
        $JR = $elt('tva3310a_20190101_JR');
        $KF = $elt('tva3310a_20190101_KF');
        $KG = $elt('tva3310a_20190101_KG');
        $KJ = $elt('tva3310a_20190101_KJ');
        $KL = $elt('tva3310a_20190101_KL');
        $KT = $elt('tva3310a_20190101_KT');
        $KX = $elt('tva3310a_20190101_KX');
        $KY = $elt('tva3310a_20190101_KY');
        $KZ = $elt('tva3310a_20190101_KZ');
        $LA = $elt('tva3310a_20190101_LA');
        $LC = $elt('tva3310a_20190101_LC');
        $LD = $elt('tva3310a_20190101_LD');
        $LE = $elt('tva3310a_20190101_LE');
        $LF = $elt('tva3310a_20190101_LF');
        $LG = $elt('tva3310a_20190101_LG');
        $LH = $elt('tva3310a_20190101_LH');
        $LJ = $elt('tva3310a_20190101_LJ');
        $LJ = $elt('tva3310a_20190101_LJ');
        $LK = $elt('tva3310a_20190101_LK');
        $LL = $elt('tva3310a_20190101_LL');
        $LM = $elt('tva3310a_20190101_LM');
        $LN = $elt('tva3310a_20190101_LN');
        $LP = $elt('tva3310a_20190101_LP');
        $LQ = $elt('tva3310a_20190101_LQ');
        $LR = $elt('tva3310a_20190101_LR');
        $LS = $elt('tva3310a_20190101_LS');
        $LT = $elt('tva3310a_20190101_LT');
        $LU = $elt('tva3310a_20190101_LU');
        $LW = $elt('tva3310a_20190101_LW');
        $LX = $elt('tva3310a_20190101_LX');
        $MA = $elt('tva3310a_20190101_MA');
        $MB = $elt('tva3310a_20190101_MB');
        $MC = $elt('tva3310a_20190101_MC');
        $MD = $elt('tva3310a_20190101_MD');
        $ME = $elt('tva3310a_20190101_ME');
        $MF = $elt('tva3310a_20190101_MF');
        $MG = $elt('tva3310a_20190101_MG');
        $MK = $elt('tva3310a_20190101_MK');
        $ML = $elt('tva3310a_20190101_ML');
        $MM = $elt('tva3310a_20190101_MM');
        $MN = $elt('tva3310a_20190101_MN');
        $MP = $elt('tva3310a_20190101_MP');
        $MQ = $elt('tva3310a_20190101_MQ');
        $MR = $elt('tva3310a_20190101_MR');
        $MS = $elt('tva3310a_20190101_MS');
        $MU = $elt('tva3310a_20190101_MU');
        $MV = $elt('tva3310a_20190101_MV');
        $MW = $elt('tva3310a_20190101_MW');
        $MX = $elt('tva3310a_20190101_MX');
        $MY = $elt('tva3310a_20190101_MY');
        $MZ = $elt('tva3310a_20190101_MZ');
        $NA = $elt('tva3310a_20190101_NA');
        $NB = $elt('tva3310a_20190101_NB');
        $NC = $elt('tva3310a_20190101_NC');
        $ND = $elt('tva3310a_20190101_ND');
        $NE = $elt('tva3310a_20190101_NE');
        $NF = $elt('tva3310a_20190101_NF');
        $NG = $elt('tva3310a_20190101_NG');
        $NH = $elt('tva3310a_20190101_NH');
        $NJ = $elt('tva3310a_20190101_NJ');
        $NK = $elt('tva3310a_20190101_NK');
        $NL = $elt('tva3310a_20190101_NL');
        $NN = $elt('tva3310a_20190101_NN');
        $NP = $elt('tva3310a_20190101_NP');
        $NQ = $elt('tva3310a_20190101_NQ');
        $NR = $elt('tva3310a_20190101_NR');
        $NS = $elt('tva3310a_20190101_NS');
        $NT = $elt('tva3310a_20190101_NT');
        $NU = $elt('tva3310a_20190101_NU');
        $NV = $elt('tva3310a_20190101_NV');
        $NW = $elt('tva3310a_20190101_NW');
        $NX = $elt('tva3310a_20190101_NX');
        $NY = $elt('tva3310a_20190101_NY');
        $NZ = $elt('tva3310a_20190101_NZ');
        $PA = $elt('tva3310a_20190101_PA');
        $PB = $elt('tva3310a_20190101_PB');
        $PC = $elt('tva3310a_20190101_PC');
        $PD = $elt('tva3310a_20190101_PD');
        $PE = $elt('tva3310a_20190101_PE');
        $PF = $elt('tva3310a_20190101_PF');
        $PG = $elt('tva3310a_20190101_PG');
        $PK = $elt('tva3310a_20190101_PK');
        $PN = $elt('tva3310a_20190101_PN');
        $PP = $elt('tva3310a_20190101_PP');
        $PQ = $elt('tva3310a_20190101_PQ');
        $PR = $elt('tva3310a_20190101_PR');
        $PS = $elt('tva3310a_20190101_PS');
        $PU = $elt('tva3310a_20190101_PU');
        $PW = $elt('tva3310a_20190101_PW');
        $PX = $elt('tva3310a_20190101_PX');
        $PY = $elt('tva3310a_20190101_PY');
        $PZ = $elt('tva3310a_20190101_PZ');
        $QA = $elt('tva3310a_20190101_QA');
        $QB = $elt('tva3310a_20190101_QB');
        $QC = $elt('tva3310a_20190101_QC');
        $QD = $elt('tva3310a_20190101_QD');
        $QE = $elt('tva3310a_20190101_QE');

        $assert(!($isServi($DB) && !$isServi($DA)),
            'erreur_128', $DA, $DB);

        $assert(!($isServi($BA) && $float($BA) > 0 && !($isServi($CA) && $float($CA) > 0)),
            'erreur_111', $BA, $CA);

        $assert(!($isServi($CA) && $float($CA) > 0 && !($isServi($BA) && $float($BA) > 0)),
            'erreur_112', $BA, $CA);

        $assert(!($isServi($BC) && $isServi($CC) && !(($float($BC) * 0.021) <= $float($CC) && $float($CC) <= ($float($BC) * 0.206))),
            'erreur_117', $BC, $CC);

        $assert(!($isServi($NG) && $float($NG) > 0 && !($isServi($JE) && $float($JE) > 0)),
            'erreur_111', $NG, $JE);
        $assert(!($isServi($JE) && $float($JE) > 0 && !($isServi($NG) && $float($NG) > 0)),
            'erreur_112', $JE, $NG);

        $assert(!($isServi($MM) && $float($MM) > 0 && !($isServi($FT) && $float($FT) > 0)),
            'erreur_111', $MM, $FT);
        $assert(!($isServi($FT) && $float($FT) > 0 && !($isServi($MM) && $float($MM) > 0)),
            'erreur_112', $FT, $MM);

        $assert(!($isServi($MN) && $float($MN) > 0 && !($isServi($FV) && $float($FV) > 0)),
            'erreur_111', $MN, $FV);
        $assert(!($isServi($FV) && $float($FV) > 0 && !($isServi($MN) && $float($MN) > 0)),
            'erreur_112', $FV, $MN);

        $assert(!($isServi($NL) && $float($NL) > 0 && !($isServi($JH) && $float($JH) > 0)),
            'erreur_111', $NL, $JH);
        $assert(!($isServi($JH) && $float($JH) > 0 && !($isServi($NL) && $float($NL) > 0)),
            'erreur_112', $JH, $NL);

        $assert(!($isServi($PE) && $float($PE) > 0 && !($isServi($KZ) && $float($KZ) > 0)),
            'erreur_111', $PE, $KZ);
        $assert(!($isServi($KZ) && $float($KZ) > 0 && !($isServi($PE) && $float($PE) > 0)),
            'erreur_112', $KZ, $PE);

        $assert(!($isServi($MD) && $float($MD) > 0 && !($isServi($LE) && $float($LE) > 0)),
            'erreur_111', $MD, $LE);
        $assert(!($isServi($LE) && $float($LE) > 0 && !($isServi($MD) && $float($MD) > 0)),
            'erreur_112', $LE, $MD);

        $assert(!($isServi($ME) && $float($ME) > 0 && !($isServi($LF) && $float($LF) > 0)),
            'erreur_111', $ME, $LF);
        $assert(!($isServi($LF) && $float($LF) > 0 && !($isServi($ME) && $float($ME) > 0)),
            'erreur_112', $LF, $ME);

        $assert(!($isServi($MQ) && $float($MQ) > 0 && !($isServi($LK) && $float($LK) > 0)),
            'erreur_111', $MQ, $LK);
        $assert(!($isServi($LK) && $float($LK) > 0 && !($isServi($MQ) && $float($MQ) > 0)),
            'erreur_112', $LK, $MQ);

        $assert(!($isServi($MZ) && $float($MZ) > 0 && !($isServi($LL) && $float($LL) > 0)),
            'erreur_111', $MZ, $LL);
        $assert(!($isServi($LL) && $float($LL) > 0 && !($isServi($MZ) && $float($MZ) > 0)),
            'erreur_112', $LL, $MZ);

        $assert(!($isServi($NA) && $float($NA) > 0 && !($isServi($LM) && $float($LM) > 0)),
            'erreur_111', $NA, $LM);
        $assert(!($isServi($LM) && $float($LM) > 0 && !($isServi($NA) && $float($NA) > 0)),
            'erreur_112', $LM, $NA);

        $assert(!($isServi($NT) && $float($NT) > 0 && !($isServi($NZ) && $float($NZ) > 0)),
            'erreur_111', $NT, $NZ);
        $assert(!($isServi($NZ) && $float($NZ) > 0 && !($isServi($NT) && $float($NT) > 0)),
            'erreur_112', $NZ, $NT);

        $assert(!($isServi($NU) && $float($NU) > 0 && !($isServi($PA) && $float($PA) > 0)),
            'erreur_111', $NU, $PA);
        $assert(!($isServi($PA) && $float($PA) > 0 && !($isServi($NU) && $float($NU) > 0)),
            'erreur_112', $PA, $NU);

        $assert(!($isServi($NV) && $float($NV) > 0 && !($isServi($PB) && $float($PB) > 0)),
            'erreur_111', $NV, $PB);
        $assert(!($isServi($PB) && $float($PB) > 0 && !($isServi($NV) && $float($NV) > 0)),
            'erreur_112', $PB, $NV);

        $assert(!($isServi($NW) && $float($NW) > 0 && !($isServi($PC) && $float($PC) > 0)),
            'erreur_111', $NW, $PC);
        $assert(!($isServi($PC) && $float($PC) > 0 && !($isServi($NW) && $float($NW) > 0)),
            'erreur_112', $PC, $NW);

        $assert(!($isServi($NX) && $float($NX) > 0 && !($isServi($PD) && $float($PD) > 0)),
            'erreur_111', $NX, $PD);
        $assert(!($isServi($PD) && $float($PD) > 0 && !($isServi($NX) && $float($NX) > 0)),
            'erreur_112', $PD, $NX);

        $assert(!($isServi($MU) && $float($MU) > 0 && !($isServi($NR) && $float($NR) > 0)),
            'erreur_111', $MU, $NR);
        $assert(!($isServi($NR) && $float($NR) > 0 && !($isServi($MU) && $float($MU) > 0)),
            'erreur_112', $NR, $MU);

        $assert(!($isServi($MW) && $float($MW) > 0 && !($isServi($NS) && $float($NS) > 0)),
            'erreur_111', $MW, $NS);
        $assert(!($isServi($NS) && $float($NS) > 0 && !($isServi($MW) && $float($MW) > 0)),
            'erreur_112', $NS, $MW);

        $assert(!($isServi($PG) && $float($PG) > 0 && !($isServi($NC) && $float($NC) > 0)),
            'erreur_111', $PG, $NC);
        $assert(!($isServi($NC) && $float($NC) > 0 && !($isServi($PG) && $float($PG) > 0)),
            'erreur_112', $NC, $PG);

        $assert(!(($isServi($MR) || $isServi($LQ) || $isServi($LR) || $isServi($LS)) && !($isServi($MR) && $isServi($LQ) && $isServi($LR) && $isServi($LS))),
            'erreur_231', $MR, $LQ, $LR, $LS);

        $assert(!(($isServi($MS) || $isServi($LT) || $isServi($LU)) && !($isServi($MS) && $isServi($LT) && $isServi($LU))),
            'erreur_232', $MS, $LT, $LU);


        $PJ = null;
        $PH = null;

        $rowIndex = 1;
        while ($elt('tva3310a_20190101_PJ/' . $rowIndex)->isset) {
            $PJ = $elt('tva3310a_20190101_PJ/' . $rowIndex);
            $PH = $elt('tva3310a_20190101_PH/' . $rowIndex);

            $assert(!(($isServi($PJ) xor $isServi($PH)) || $float($PH) === 0),
                'erreur_233', $PJ, $PH);

            $rowIndex++;
        }
    }

    public static function tva3517sca12_20190101($elt, $assert, $isServi, $float, $value, $controls)
    {
        $AB = $elt('tva3517sca12_20190101_AB');
        $AD = $elt('tva3517sca12_20190101_AD');
        $AB = $elt('tva3517sca12_20190101_AB');
        $AE = $elt('tva3517sca12_20190101_AE');
        $CA1 = $elt('tva3517sca12_20190101_CA1');
        $CA2 = $elt('tva3517sca12_20190101_CA2');
        $CA3 = $elt('tva3517sca12_20190101_CA3');
        $CA4 = $elt('tva3517sca12_20190101_CA4');
        $CA5 = $elt('tva3517sca12_20190101_CA5');
        $CA = $elt('tva3517sca12_20190101_CA');
        $DA = $elt('tva3517sca12_20190101_DA');
        $DB = $elt('tva3517sca12_20190101_DB');
        $DC = $elt('tva3517sca12_20190101_DC');
        $EA = $elt('tva3517sca12_20190101_EA');
        $EB = $elt('tva3517sca12_20190101_EB');
        $EC = $elt('tva3517sca12_20190101_EC');
        $ED = $elt('tva3517sca12_20190101_ED');
        $EE = $elt('tva3517sca12_20190101_EE');
        $EF = $elt('tva3517sca12_20190101_EF');
        $EG = $elt('tva3517sca12_20190101_EG');
        $EH = $elt('tva3517sca12_20190101_EH');
        $EJ = $elt('tva3517sca12_20190101_EJ');
        $EL = $elt('tva3517sca12_20190101_EL');
        $EM = $elt('tva3517sca12_20190101_EM');
        $EN = $elt('tva3517sca12_20190101_EN');
        $EP = $elt('tva3517sca12_20190101_EP');
        $EQ = $elt('tva3517sca12_20190101_EQ');
        $EU = $elt('tva3517sca12_20190101_EU');
        $EV = $elt('tva3517sca12_20190101_EV');
        $EW = $elt('tva3517sca12_20190101_EW');
        $EX = $elt('tva3517sca12_20190101_EX');
        $EY = $elt('tva3517sca12_20190101_EY');
        $EZ = $elt('tva3517sca12_20190101_EZ');
        //        $FA = $elt('tva3517sca12_20190101_FA');
        //        $FB = $elt('tva3517sca12_20190101_FB');
        //        $FC = $elt('tva3517sca12_20190101_FC');
        //        $FD = $elt('tva3517sca12_20190101_FD');
        $FF = $elt('tva3517sca12_20190101_FF');
        $FG = $elt('tva3517sca12_20190101_FG');
        $FJ = $elt('tva3517sca12_20190101_FJ');
        $FL = $elt('tva3517sca12_20190101_FL');
        $FM = $elt('tva3517sca12_20190101_FM');
        $FN = $elt('tva3517sca12_20190101_FN');
        $FP = $elt('tva3517sca12_20190101_FP');
        $FR = $elt('tva3517sca12_20190101_FR');
        $FU = $elt('tva3517sca12_20190101_FU');
        $FV = $elt('tva3517sca12_20190101_FV');
        $FW = $elt('tva3517sca12_20190101_FW');
        $FY = $elt('tva3517sca12_20190101_FY');
        $GA = $elt('tva3517sca12_20190101_GA');
        $GB = $elt('tva3517sca12_20190101_GB');
        $GC = $elt('tva3517sca12_20190101_GC');
        $GF = $elt('tva3517sca12_20190101_GF');
        $GH = $elt('tva3517sca12_20190101_GH');
        $HA = $elt('tva3517sca12_20190101_HA');
        $HB = $elt('tva3517sca12_20190101_HB');
        $HC = $elt('tva3517sca12_20190101_HC');
        $JA = $elt('tva3517sca12_20190101_JA');
        $JB = $elt('tva3517sca12_20190101_JB');
        $KA = $elt('tva3517sca12_20190101_KA');
        $KB = $elt('tva3517sca12_20190101_KB');
        $KD = $elt('tva3517sca12_20190101_KD');
        //        $KE = $elt('tva3517sca12_20190101_KE');
        //        $KF = $elt('tva3517sca12_20190101_KF');
        //        $KG = $elt('tva3517sca12_20190101_KG');
        //        $KH = $elt('tva3517sca12_20190101_KH');
        //        $KJ = $elt('tva3517sca12_20190101_KJ');
        $KL = $elt('tva3517sca12_20190101_KL');
        $KM = $elt('tva3517sca12_20190101_KM');
        $LA = $elt('tva3517sca12_20190101_LA');
        $LB = $elt('tva3517sca12_20190101_LB');
        $MA = $elt('tva3517sca12_20190101_MA');
        $MD = $elt('tva3517sca12_20190101_MD');
        $ME = $elt('tva3517sca12_20190101_ME');
        $MF = $elt('tva3517sca12_20190101_MF');
        $MG = $elt('tva3517sca12_20190101_MG');
        $MM = $elt('tva3517sca12_20190101_MM');
        $MN = $elt('tva3517sca12_20190101_MN');
        $NA = $elt('tva3517sca12_20190101_NA');
        $NB = $elt('tva3517sca12_20190101_NB');
        $NC = $elt('tva3517sca12_20190101_NC');
        $QA = $elt('tva3517sca12_20190101_QA');
        $QD = $elt('tva3517sca12_20190101_QD');
        $QE = $elt('tva3517sca12_20190101_QE');
        $QF = $elt('tva3517sca12_20190101_QF');
        $QH = $elt('tva3517sca12_20190101_QH');
        $QJ = $elt('tva3517sca12_20190101_QJ');
        $QS = $elt('tva3517sca12_20190101_QS');
        $RA = $elt('tva3517sca12_20190101_RA');
        $RB = $elt('tva3517sca12_20190101_RB');
        $RC = $elt('tva3517sca12_20190101_RC');
        $RE = $elt('tva3517sca12_20190101_RE');
        $RD = $elt('tva3517sca12_20190101_RD');
        $RF = $elt('tva3517sca12_20190101_RF');
        $RG = $elt('tva3517sca12_20190101_RG');
        $RN = $elt('tva3517sca12_20190101_RN');
        $SA = $elt('tva3517sca12_20190101_SA');
        $SB = $elt('tva3517sca12_20190101_SB');
        $SC = $elt('tva3517sca12_20190101_SC');
        $SD = $elt('tva3517sca12_20190101_SD');
        $SH = $elt('tva3517sca12_20190101_SH');
        $SM = $elt('tva3517sca12_20190101_SM');
        $SN = $elt('tva3517sca12_20190101_SN');
        $SP = $elt('tva3517sca12_20190101_SP');
        $ST = $elt('tva3517sca12_20190101_ST');
        $SQ = $elt('tva3517sca12_20190101_SQ');
        $SS = $elt('tva3517sca12_20190101_SS');
        $SR = $elt('tva3517sca12_20190101_SR');
        $SV = $elt('tva3517sca12_20190101_SV');
        $SW = $elt('tva3517sca12_20190101_SW');
        $SX = $elt('tva3517sca12_20190101_SX');
        $TB = $elt('tva3517sca12_20190101_TB');
        $TD = $elt('tva3517sca12_20190101_TD');
        $UB = $elt('tva3517sca12_20190101_UB');
        $UD = $elt('tva3517sca12_20190101_UD');
        $VA = $elt('tva3517sca12_20190101_VA');
        $VC = $elt('tva3517sca12_20190101_VC');
        $VE = $elt('tva3517sca12_20190101_VE');
        $VF = $elt('tva3517sca12_20190101_VF');
        $VJ = $elt('tva3517sca12_20190101_VJ');
        $VK = $elt('tva3517sca12_20190101_VK');
        $VL = $elt('tva3517sca12_20190101_VL');
        $VM = $elt('tva3517sca12_20190101_VM');
        $VN = $elt('tva3517sca12_20190101_VN');
        $VP = $elt('tva3517sca12_20190101_VP');
        $VS = $elt('tva3517sca12_20190101_VS');
        $VT = $elt('tva3517sca12_20190101_VT');
        $VW = $elt('tva3517sca12_20190101_VW');
        $VX = $elt('tva3517sca12_20190101_VX');
        $VY = $elt('tva3517sca12_20190101_VY');
        $VZ = $elt('tva3517sca12_20190101_VZ');
        $WB = $elt('tva3517sca12_20190101_WB');
        $WC = $elt('tva3517sca12_20190101_WC');
        $WD = $elt('tva3517sca12_20190101_WD');
        $WE = $elt('tva3517sca12_20190101_WE');
        $WF = $elt('tva3517sca12_20190101_WF');
        $WG = $elt('tva3517sca12_20190101_WG');
        $WH = $elt('tva3517sca12_20190101_WH');
        $WJ = $elt('tva3517sca12_20190101_WJ');
        $WK = $elt('tva3517sca12_20190101_WK');
        $WL = $elt('tva3517sca12_20190101_WL');
        $WM = $elt('tva3517sca12_20190101_WM');
        $WN = $elt('tva3517sca12_20190101_WN');
        $WP = $elt('tva3517sca12_20190101_WP');
        $WQ = $elt('tva3517sca12_20190101_WQ');
        $WR = $elt('tva3517sca12_20190101_WR');
        $WS = $elt('tva3517sca12_20190101_WS');
        $WT = $elt('tva3517sca12_20190101_WT');
        $WU = $elt('tva3517sca12_20190101_WU');
        $WV = $elt('tva3517sca12_20190101_WV');
        $WZ = $elt('tva3517sca12_20190101_WZ');
        $XA = $elt('tva3517sca12_20190101_XA');
        $XB = $elt('tva3517sca12_20190101_XB');
        $YA = $elt('tva3517sca12_20190101_YA');
        $YB = $elt('tva3517sca12_20190101_YB');
        $YC = $elt('tva3517sca12_20190101_YC');
        $YK = $elt('tva3517sca12_20190101_YK');
        $YL = $elt('tva3517sca12_20190101_YL');
        $ZA = $elt('tva3517sca12_20190101_ZA');
        $ZB = $elt('tva3517sca12_20190101_ZB');
        $ZE = $elt('tva3517sca12_20190101_ZE');
        $ZF = $elt('tva3517sca12_20190101_ZF');
        $ZG = $elt('tva3517sca12_20190101_ZG');
        $ZH = $elt('tva3517sca12_20190101_ZH');
        $ZJ = $elt('tva3517sca12_20190101_ZJ');
        $ZK = $elt('tva3517sca12_20190101_ZK');
        $ZL = $elt('tva3517sca12_20190101_ZL');
        $ZM = $elt('tva3517sca12_20190101_ZM');
        $ZN = $elt('tva3517sca12_20190101_ZN');
        $ZP = $elt('tva3517sca12_20190101_ZP');
        $ZR = $elt('tva3517sca12_20190101_ZR');
        $ZS = $elt('tva3517sca12_20190101_ZS');
        $ZT = $elt('tva3517sca12_20190101_ZT');
        $ZU = $elt('tva3517sca12_20190101_ZU');
        $ZW = $elt('tva3517sca12_20190101_ZW');
        $ZX = $elt('tva3517sca12_20190101_ZX');
        $ZZ = $elt('tva3517sca12_20190101_ZZ');

        if (!$SD->isset) {
            // --- asserts
            $assert(!($isServi($VK) && !$isServi($CA)), 'erreur_128', $CA, $VK);

            $controls['erreur_111']($EG, $FG);
            $controls['erreur_111']($EH, $EZ);
            $controls['erreur_111']($EJ, $FJ);
            $controls['erreur_111']($EL, $FL);
            $controls['erreur_111']($EM, $FM);
            $controls['erreur_111']($EN, $FN);
            $controls['erreur_111']($EP, $FP);
            $controls['erreur_111']($EW, $FW);
            $controls['erreur_111']($EY, $FY);

            $controls['erreur_111']($GF, $GH);

            $controls['erreur_111']($SN, $VY);

            $controls['erreur_111']($VN, $VP);

            $controls['erreur_111']($YA, $WL);
            $controls['erreur_111']($YB, $WM);
            $controls['erreur_111']($YC, $WG);

            $controls['erreur_111']($ZM, $WK);
            $controls['erreur_111']($ZZ, $WF);

            $controls['erreur_111']($SW, $SV);
            $controls['erreur_111']($XA, $SX);
            $controls['erreur_111']($XB, $RD);


            $controls['erreur_112']($EZ, $EH);

            $controls['erreur_112']($FG, $EG);
            $controls['erreur_112']($FJ, $EJ);
            $controls['erreur_112']($FL, $EL);
            $controls['erreur_112']($FM, $EM);
            $controls['erreur_112']($FN, $EN);
            $controls['erreur_112']($FP, $EP);
            $controls['erreur_112']($FW, $EW);
            $controls['erreur_112']($FY, $EY);

            $controls['erreur_112']($GH, $GF);

            $controls['erreur_112']($VP, $VN);
            $controls['erreur_112']($VY, $SN);

            $controls['erreur_112']($WF, $ZZ);
            $controls['erreur_112']($SV, $SW);
            $controls['erreur_112']($SX, $XA);
            $controls['erreur_112']($RD, $XB);

            $controls['erreur_112']($WK, $ZM);
            $controls['erreur_112']($WL, $YA);
            $controls['erreur_112']($WM, $YB);

            $controls['erreur_117']($EG, $FG, 0.021, 0.206);
            $controls['erreur_117']($EP, $FP, 0.021, 0.20);


            $assert(!(($isServi($ZN) || $isServi($WQ) || $isServi($WR) || $isServi($WS)) && !($isServi($ZN) && $isServi($WQ) && $isServi($WR) && $isServi($WS))),
                'erreur_231', $ZN, $WQ, $WR, $WS);

            $assert(!(($isServi($ZP) || $isServi($WT) || $isServi($WU)) && !($isServi($ZP) && $isServi($WT) && $isServi($WU))),
                'erreur_232', $ZP, $WT, $WU);

            $rowIndex = 1;
            while ($elt('tva3517sca12_20190101_SF/' . $rowIndex)->isset) {
                $SF = $elt('tva3517sca12_20190101_SF/' . $rowIndex);
                $SE = $elt('tva3517sca12_20190101_SE/' . $rowIndex);

                $assert(!(($isServi($SF) || $isServi($SE)) && !($isServi($SF) && $isServi($SE) && ($float($SE) > 0))),
                    'erreur_233', $SF, $SE);

                $rowIndex++;
            }

            $rowIndex = 1;
            while ($elt('tva3517sca12_20190101_AD/' . $rowIndex)->isset) {
                $AD = $elt('tva3517sca12_20190101_AD/' . $rowIndex);
                $AC = $elt('tva3517sca12_20190101_AC/' . $rowIndex);
                $AB = $elt('tva3517sca12_20190101_AB/' . $rowIndex);

                $assert(!(($isServi($AD) || $isServi($AB) || $isServi($AC)) && !($isServi($AD) && $isServi($AB) && $isServi($AC)) && $float($AB) > 0),
                    'erreur_233', $AD, $AB, $AC);

                $rowIndex++;
            }

            $assert(!($isServi($SC) && strlen((string)$value($SC)) > 6), 'erreur_229', $SC);

            $assert(!($isServi($EQ) && $isServi($FP) && !($float($EQ) <= $float($FP))),
                'erreur_137', $EQ, $FP);
            $assert(!($isServi($HB) && $float($HB) > 0 && !(
                    $float($HB) == round(0.002 * ($float($EB) + $float($EC) + $float($EE)
                            + $float($ED) + $float($VM) + $float($EX) + $float($EF)
                            + $float($EU) + $float($EV) + $float($EJ) + $float($EG) +
                            $float($EW) + $float($GF)))
                )),
                'erreur_034', $HB, $EB, $EC, $ED, $EE, $VM, $EX, $EF, $EU, $EV, $EJ, $EG, $EW, $GF);
            $assert(!($isServi($JB) && $float($JB) >= 0 && !(0 < $float($JB) && $float($JB) <= 100)), 'erreur_116', $JB);

            $assert(!($isServi($RA) && $float($RA) >= 0 && !($float($RA) == $float($RB) + $float($RC) + $float($RE)))
                , 'erreur_204', $RA, $RB, $RC, $RE);
            $assert(!($isServi($RA) && $isServi($RB) && !($float($RB) <= $float($RA))),
                'erreur_132', $RA, $RB);

            $casesAccomptesRemplies = 0;
            $casesAccomptesRemplies += ($isServi($MD) || $isServi($ME)) ? 1 : 0;
            $casesAccomptesRemplies += ($isServi($MF) || $isServi($MG)) ? 1 : 0;
            $casesCoches = 0;
            $casesCoches += $isServi($TB) ? 1 : 0;
            $casesCoches += $isServi($TD) ? 1 : 0;
            $assert(!($isServi($MA) && $float($MA) > 0 && !($casesAccomptesRemplies == $casesCoches)),
                'erreur_124', $MA, $MD, $ME, $MF, $MG);

            $controls['erreur_129']($TB, $UB);
            $controls['erreur_129']($TD, $UD);

            $controls['erreur_226']($UB, $TB);
            $controls['erreur_226']($UD, $TD);

            $controls['erreur_134']($UB, $elt('t_identif_20170101_CA'), $elt('t_identif_20170101_CB'));
            $controls['erreur_134']($UD, $elt('t_identif_20170101_CA'), $elt('t_identif_20170101_CB'));

            $requiredFields = array(
                $DA, $DB,
                $EA, $EB, $EC, $ED, $EF, $EE, $EG, $EH, $EJ, $EL, $EM, $EN, $EP, $EQ, $EU, $EV, $EW, $EX, $EY, $EZ,
                /*$FA, $FB, $FC, $FD,*/
                $FF, $FG, $FJ, $FL, $FM, $FN, $FP, $FR, $FU, $FV, $FW, $FY,
                $GA, $GB, $GC, $GF, $GH,
                $HA, $HB, $HC,
                $JA,
                $KA, $KB, $KD, $KL, $KM,
                $LA, $LB,
                $MA, $MM, $MN,
                $NA, $NB, $NC,
                $QD, $QE, $QF, $QH, $QJ, $QS,
                $RA, $RB, $RC, $RE, $RF, $RG, $RN,
                $SA, $SB, $SC, $SM, $SN, $SP,
                $VA, $VC, $VE, $VF, $VJ, $VM, $VN, $VP, $VS, $VT, $VW, $VX, $VY,
                $WB, $WC, $WF, $WG, $WK, $WL, $WM, $WQ, $WR, $WS,
                $YC,
                $ZR, $ZS, $ZT, $ZU, $ZZ
            );
            $controls['erreur_042']($SD, $requiredFields);
            $controls['erreur_049']($SD, $requiredFields);

            $assert((($isServi($EB) && $float($EB) > 0)
                || ($isServi($EC) && $float($EC) > 0)
                || ($isServi($ED) && $float($ED) > 0)
                || ($isServi($EF) && $float($EF) > 0)
                || ($isServi($FF) && $float($FF) > 0)
                || ($isServi($EG) && $float($EG) > 0)
                || ($isServi($FG) && $float($FG) > 0)
                || ($isServi($EJ) && $float($EJ) > 0)
                || ($isServi($FJ) && $float($FJ) > 0)
                || ($isServi($HA) && $float($HA) > 0)
                || ($isServi($HB) && $float($HB) > 0)
                || ($isServi($HC) && $float($HC) > 0)
                || ($isServi($NB) && $float($NB) > 0)
                || ($isServi($JA) && $float($JA) > 0)
                || ($isServi($NA) && $float($NA) > 0)
                || ($isServi($LB) && $float($LB) > 0)
                || ($isServi($MA) && $float($MA) > 0)
                || ($isServi($NC) && $float($NC) > 0)
                || ($isServi($LA) && $float($LA) > 0)
                || ($isServi($EA) && $float($EA) > 0)
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
                || ($isServi($GC) && $float($GC) > 0)
                || ($isServi($KA) && $float($KA) > 0)
                || ($isServi($KB) && $float($KB) > 0)
                || ($isServi($KD) && $float($KD) > 0)
                || ($isServi($QA) && $float($QA) > 0)
                || ($isServi($QE) && $float($QE) > 0)
                || ($isServi($QF) && $float($QF) > 0)
                || ($isServi($QH) && $float($QH) > 0)
                || ($isServi($QJ) && $float($QJ) > 0)
                || ($isServi($RA) && $float($RA) > 0)
                || ($isServi($RB) && $float($RB) > 0)
                || ($isServi($RC) && $float($RC) > 0)
                || ($isServi($SA) && $float($SA) > 0)
                || ($isServi($SB) && $float($SB) > 0)
                || ($isServi($SC) && $float($SC) > 0)
                || ($isServi($VA) && $float($VA) > 0)
                || ($isServi($QD) && $float($QD) > 0)
                || ($isServi($EU) && $float($EU) > 0)
                || ($isServi($FU) && $float($FU) > 0)
                || ($isServi($EV) && $float($EV) > 0)
                || ($isServi($FV) && $float($FV) > 0)
                || ($isServi($MD) && $float($MD) > 0)
                || ($isServi($MF) && $float($MF) > 0)
                || ($isServi($ME) && $float($ME) > 0)
                || ($isServi($MG) && $float($MG) > 0)
                || ($isServi($MM) && $float($MM) > 0)
                || ($isServi($MN) && $float($MN) > 0)
                || ($isServi($RE) && $float($RE) > 0)
                || ($isServi($QS) && $float($QS) > 0)
                || ($isServi($EX) && $float($EX) > 0)
                || ($isServi($EY) && $float($EY) > 0)
                || ($isServi($FY) && $float($FY) > 0)
                || ($isServi($VC) && $float($VC) > 0)
                || ($isServi($VE) && $float($VE) > 0)
                || ($isServi($VF) && $float($VF) > 0)
                || ($isServi($VM) && $float($VM) > 0)
                || ($isServi($VN) && $float($VN) > 0)
                || ($isServi($VP) && $float($VP) > 0)
                || ($isServi($VJ) && $float($VJ) > 0)
                //                || ($isServi($KE) && $float($KE) > 0)
                //                || ($isServi($KF) && $float($KF) > 0)
                //                || ($isServi($KG) && $float($KG) > 0)
                //                || ($isServi($KH) && $float($KH) > 0)
                //                || ($isServi($KJ) && $float($KJ) > 0)
                //                || ($isServi($FA) && $float($FA) > 0)
                //                || ($isServi($FB) && $float($FB) > 0)
                //                || ($isServi($FC) && $float($FC) > 0)
                //                || ($isServi($FD) && $float($FD) > 0)
                || ($isServi($KM) && $float($KM) > 0)
                || ($isServi($KL) && $float($KL) > 0)
                || ($isServi($EH) && $float($EH) > 0)
                || ($isServi($EZ) && $float($EZ) > 0)
                || ($isServi($RG) && $float($RG) > 0)
                || ($isServi($RF) && $float($RF) > 0)
                || ($isServi($RN) && $float($RN) > 0)
                || ($isServi($EW) && $float($EW) > 0)
                || ($isServi($FW) && $float($FW) > 0)
                || ($isServi($GF) && $float($GF) > 0)
                || ($isServi($GH) && $float($GH) > 0)
                || ($isServi($DA) && $float($DA) > 0)
                || ($isServi($DB) && $float($DB) > 0)
                || ($isServi($DC) && $float($DC) > 0)
                || ($isServi($VW) && $float($VW) > 0)
                || ($isServi($VX) && $float($VX) > 0)
                || ($isServi($VY) && $float($VY) > 0)
                || ($isServi($VZ) && $float($VZ) > 0)
                || ($isServi($VS) && $float($VS) > 0)
                || ($isServi($VT) && $float($VT) > 0)
                || ($isServi($WB) && $float($WB) > 0)
                || ($isServi($WC) && $float($WC) > 0)
                || ($isServi($WD) && $float($WD) > 0)
                || ($isServi($WE) && $float($WE) > 0)
                || ($isServi($WF) && $float($WF) > 0)
                || ($isServi($WG) && $float($WG) > 0)
                || ($isServi($WH) && $float($WH) > 0)
                || ($isServi($WJ) && $float($WJ) > 0)
                || ($isServi($WK) && $float($WK) > 0)
                || ($isServi($WL) && $float($WL) > 0)
                || ($isServi($WM) && $float($WM) > 0)
                || ($isServi($WN) && $float($WN) > 0)
                || ($isServi($WP) && $float($WP) > 0)
                || ($isServi($WQ) && $float($WQ) > 0)
                || ($isServi($WR) && $float($WR) > 0)
                || ($isServi($WS) && $float($WS) > 0)
                || ($isServi($WT) && $float($WT) > 0)
                || ($isServi($WU) && $float($WU) > 0)
                || ($isServi($WV) && $float($WV) > 0)
                || ($isServi($WZ) && $float($WZ) > 0)
                || ($isServi($ZA) && $float($ZA) > 0)
                || ($isServi($ZB) && $float($ZB) > 0)
                || ($isServi($ZE) && $float($ZE) > 0)
                || ($isServi($ZF) && $float($ZF) > 0)
                || ($isServi($ZR) && $float($ZR) > 0)
                || ($isServi($ZG) && $float($ZG) > 0)
                || ($isServi($ZS) && $float($ZS) > 0)
                || ($isServi($ZH) && $float($ZH) > 0)
                || ($isServi($ZT) && $float($ZT) > 0)
                || ($isServi($ZU) && $float($ZU) > 0)
                || ($isServi($ZL) && $float($ZL) > 0)
                || ($isServi($ZW) && $float($ZW) > 0)
                || ($isServi($ZX) && $float($ZX) > 0)
                || ($isServi($ZZ) && $float($ZZ) > 0)
                || ($isServi($YA) && $float($YA) > 0)
                || ($isServi($ZM) && $float($ZM) > 0)
                || ($isServi($YB) && $float($YB) > 0)
                || ($isServi($ZN) && $float($ZN) > 0)
                || ($isServi($YC) && $float($YC) > 0)
                || ($isServi($ZP) && $float($ZP) > 0)
                || ($isServi($EE) && $float($EE) > 0)
                || ($isServi($YK) && $float($YK) > 0)
                || ($isServi($YL) && $float($YL) > 0)
                || ($isServi($SE) && $float($SE) > 0)
                || ($isServi($SH) && $float($SH) > 0)
                || ($isServi($SM) && $float($SM) > 0)), 'erreur_049', $SD);
        }
    }

    public static function tva3514_20190101($elt, $assert, $isServi, $float, $value, $controls)
    {
        $HA = $elt('tva3514_20190101_HA');
        $HB = $elt('tva3514_20190101_HB');
        $HC = $elt('tva3514_20190101_HC');
        $DE = $elt('tva3514_20190101_DE');
        $IA = $elt('tva3514_20190101_IA');
        $IB = $elt('tva3514_20190101_IB');
        $IC = $elt('tva3514_20190101_IC');
        $ID = $elt('tva3514_20190101_ID');
        $CA = $elt('tva3514_20190101_CA');
        $CB = $elt('tva3514_20190101_CB');
        $CC = $elt('tva3514_20190101_CC');

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


        $assert(!(!$isServi($HA) && !$isServi($HB) && !$isServi($HC) && !$isServi($DE) && !$isServi($IA) && !$isServi($IB)
            && !$isServi($IC) && !$isServi($ID) && !$isServi($CA) && !$isServi($CB) && !$isServi($CC)),
            'erreur_201', $HA, $HB, $HC, $DE, $IA, $IB, $IC, $ID, $CA, $CB, $CC);

    }

    public static function tva3517ddr_20190101($elt, $assert, $isServi, $float, $value, $controls)
    {
        $AA = $elt('tva3517ddr_20190101_AA');
        $AB = $elt('tva3517ddr_20190101_AB');
        $AC = $elt('tva3517ddr_20190101_AC');
        $AD = $elt('tva3517ddr_20190101_AD');
        $AE = $elt('tva3517ddr_20190101_AE');
        $AF1 = $elt('tva3517ddr_20190101_AF1');
        $AH = $elt('tva3517ddr_20190101_AH');
        $AJ = $elt('tva3517ddr_20190101_AJ');
        $AK1 = $elt('tva3517ddr_20190101_AK1');
        $AK2 = $elt('tva3517ddr_20190101_AK2');
        $AK3 = $elt('tva3517ddr_20190101_AK3');
        $AK4 = $elt('tva3517ddr_20190101_AK4');
        $BA = $elt('tva3517ddr_20190101_BA');
        $BB = $elt('tva3517ddr_20190101_BB');

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

    public static function tva3525bis_20190101($elt, $assert, $isServi, $float, $value, $controls)
    {
        $AC = $elt('tva3525bis_20190101_AC');
        $AD = $elt('tva3525bis_20190101_AD');
        $BB = $elt('tva3525bis_20190101_BB');
        $BC = $elt('tva3525bis_20190101_BC');
        $BD = $elt('tva3525bis_20190101_BD');
        $BE = $elt('tva3525bis_20190101_BE');
        $DA = $elt('tva3525bis_20190101_DA');

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

    public static function tva3517bisca12_20190101($elt, $assert, $isServi, $float, $value, $controls)
    {
        $AE = $elt('tva3517bisca12_20190101_AE');
        $AF = $elt('tva3517bisca12_20190101_AF');
        $AG = $elt('tva3517bisca12_20190101_AG');
        $BA = $elt('tva3517bisca12_20190101_BA');
        $DA = $elt('tva3517bisca12_20190101_DA');
        $DB = $elt('tva3517bisca12_20190101_DB');
        $DC = $elt('tva3517bisca12_20190101_DC');
        $DD = $elt('tva3517bisca12_20190101_DD');
        $DE = $elt('tva3517bisca12_20190101_DE');
        $DF = $elt('tva3517bisca12_20190101_DF');
        $DH = $elt('tva3517bisca12_20190101_DH');
        $DJ = $elt('tva3517bisca12_20190101_DJ');
        $DK = $elt('tva3517bisca12_20190101_DK');
        $DL = $elt('tva3517bisca12_20190101_DL');
        $DM = $elt('tva3517bisca12_20190101_DM');
        $DN = $elt('tva3517bisca12_20190101_DN');
        $DP = $elt('tva3517bisca12_20190101_DP');
        $DQ = $elt('tva3517bisca12_20190101_DQ');
        $DR = $elt('tva3517bisca12_20190101_DR');
        $DS = $elt('tva3517bisca12_20190101_DS');
        $DU = $elt('tva3517bisca12_20190101_DU');
        $DV = $elt('tva3517bisca12_20190101_DV');
        $DY = $elt('tva3517bisca12_20190101_DY');
        $DZ = $elt('tva3517bisca12_20190101_DZ');
//        $EA = $elt('tva3517bisca12_20190101_EA');
//        $EB = $elt('tva3517bisca12_20190101_EB');
//        $EC = $elt('tva3517bisca12_20190101_EC');
//        $ED = $elt('tva3517bisca12_20190101_ED');
        $EE = $elt('tva3517bisca12_20190101_EE');
        $EH = $elt('tva3517bisca12_20190101_EH');
        $EJ = $elt('tva3517bisca12_20190101_EJ');
        $EK = $elt('tva3517bisca12_20190101_EK');
        $EL = $elt('tva3517bisca12_20190101_EL');
        $EM = $elt('tva3517bisca12_20190101_EM');
        $EN = $elt('tva3517bisca12_20190101_EN');
        $EP = $elt('tva3517bisca12_20190101_EP');
        $EQ = $elt('tva3517bisca12_20190101_EQ');
        $ER = $elt('tva3517bisca12_20190101_ER');
        $ES = $elt('tva3517bisca12_20190101_ES');
        $EU = $elt('tva3517bisca12_20190101_EU');
        $EV = $elt('tva3517bisca12_20190101_EV');
        $EZ = $elt('tva3517bisca12_20190101_EZ');
        $FA = $elt('tva3517bisca12_20190101_FA');
        $FB = $elt('tva3517bisca12_20190101_FB');
        $FC = $elt('tva3517bisca12_20190101_FC');
        $FD = $elt('tva3517bisca12_20190101_FD');
        $FF = $elt('tva3517bisca12_20190101_FF');
        $FG = $elt('tva3517bisca12_20190101_FG');
        $GA = $elt('tva3517bisca12_20190101_GA');
        $GB = $elt('tva3517bisca12_20190101_GB');
        $HA = $elt('tva3517bisca12_20190101_HA');
        $JA = $elt('tva3517bisca12_20190101_JA');
        $JB = $elt('tva3517bisca12_20190101_JB');
        $JC = $elt('tva3517bisca12_20190101_JC');
        $KA = $elt('tva3517bisca12_20190101_KA');
        $KB = $elt('tva3517bisca12_20190101_KB');
        $KC = $elt('tva3517bisca12_20190101_KC');
        $KD = $elt('tva3517bisca12_20190101_KD');
        $KF = $elt('tva3517bisca12_20190101_KF');
        $LC = $elt('tva3517bisca12_20190101_LC');
        $LD = $elt('tva3517bisca12_20190101_LD');
        $LF = $elt('tva3517bisca12_20190101_LF');
        $LH = $elt('tva3517bisca12_20190101_LH');
        $LK = $elt('tva3517bisca12_20190101_LK');
        $LM = $elt('tva3517bisca12_20190101_LM');
        $MA = $elt('tva3517bisca12_20190101_MA');
        $MB = $elt('tva3517bisca12_20190101_MB');
        $MC = $elt('tva3517bisca12_20190101_MC');
        $NA = $elt('tva3517bisca12_20190101_NA');
        $NB = $elt('tva3517bisca12_20190101_NB');
        $NC = $elt('tva3517bisca12_20190101_NC');
        $ND = $elt('tva3517bisca12_20190101_ND');
        $RC = $elt('tva3517bisca12_20190101_RC');
        $RD = $elt('tva3517bisca12_20190101_RD');
        $RG = $elt('tva3517bisca12_20190101_RG');
        $RH = $elt('tva3517bisca12_20190101_RH');
        $RJ = $elt('tva3517bisca12_20190101_RJ');
        $RK = $elt('tva3517bisca12_20190101_RK');
        $RM = $elt('tva3517bisca12_20190101_RM');
        $RN = $elt('tva3517bisca12_20190101_RN');
        $RP = $elt('tva3517bisca12_20190101_RP');
        $RQ = $elt('tva3517bisca12_20190101_RQ');
        $RR = $elt('tva3517bisca12_20190101_RR');
        $RS = $elt('tva3517bisca12_20190101_RS');
        $RT = $elt('tva3517bisca12_20190101_RT');
        $RU = $elt('tva3517bisca12_20190101_RU');
        $RV = $elt('tva3517bisca12_20190101_RV');
        $RW = $elt('tva3517bisca12_20190101_RW');
        $RX = $elt('tva3517bisca12_20190101_RX');
        $RY = $elt('tva3517bisca12_20190101_RY');
        $RZ = $elt('tva3517bisca12_20190101_RZ');
        $SC = $elt('tva3517bisca12_20190101_SC');
        $SD = $elt('tva3517bisca12_20190101_SD');
        $SE = $elt('tva3517bisca12_20190101_SE');
        $SF = $elt('tva3517bisca12_20190101_SF');
        $SG = $elt('tva3517bisca12_20190101_SG');
        $SH = $elt('tva3517bisca12_20190101_SH');
        $SJ = $elt('tva3517bisca12_20190101_SJ');
        $SK = $elt('tva3517bisca12_20190101_SK');
        $SL = $elt('tva3517bisca12_20190101_SL');
        $SM = $elt('tva3517bisca12_20190101_SM');

        if (!$ND->isset) {
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

            $assert(!($isServi($DP) && $float($DP) && !(($isServi($FA) && $float($FA) > 0) || ($isServi($FB) && $float($FB) > 0) || ($isServi($FD) && $float($FD) > 0))),
                'erreur_135', $DP, $FA, $FB, $FD);

            $controls['erreur_117']($DP, $EP, 0.021, 0.20);
            $controls['erreur_116']($FG, $FG);

            $assert(!($isServi($MA) && $isServi($MB) && !($float($MB) <= $float($MA))),
                'erreur_131', $MA, $MB);

            $assert($isServi($AE), 'Champ Obligatoire', $AE);

            $assert(!($isServi($SL) && $float($SL) > 0 && !($isServi($RJ) && $float($RJ) > 0)),
                'erreur_111', $SL, $RJ);
            $assert(!($isServi($RJ) && $float($RJ) > 0 && !($isServi($SL) && $float($SL) > 0)),
                'erreur_112', $RJ, $SL);

            $assert(!($isServi($SH) && $float($SH) > 0 && !($isServi($RR) && $float($RR) > 0)),
                'erreur_111', $SH, $RR);
            $assert(!($isServi($RR) && $float($RR) > 0 && !($isServi($SH) && $float($SH) > 0)),
                'erreur_112', $RR, $SH);

            $assert(!($isServi($SK) && $float($SK) > 0 && !($isServi($RS) && $float($RS) > 0)),
                'erreur_111', $SK, $RS);
            $assert(!($isServi($RS) && $float($RS) > 0 && !($isServi($SK) && $float($SK) > 0)),
                'erreur_112', $RS, $SK);

            $assert(!($isServi($SE) && $float($SE) > 0 && !($isServi($RV) && $float($RV) > 0)),
                'erreur_111', $SE, $RV);
            $assert(!($isServi($RV) && $float($RV) > 0 && !($isServi($SE) && $float($SE) > 0)),
                'erreur_112', $RV, $SE);

            $assert(!($isServi($SF) && $float($SF) > 0 && !($isServi($RW) && $float($RW) > 0)),
                'erreur_111', $SF, $RW);
            $assert(!($isServi($RW) && $float($RW) > 0 && !($isServi($SF) && $float($SF) > 0)),
                'erreur_112', $RW, $SF);

            $assert(!($isServi($SG) && $float($SG) > 0 && !($isServi($SF) && $float($SF) > 0)),
                'erreur_111', $SG, $SF);
            $assert(!($isServi($SF) && $float($SF) > 0 && !($isServi($SG) && $float($SG) > 0)),
                'erreur_112', $SF, $SG);

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
//                || ($isServi($EA) && $float($EA) > 0)
//                || ($isServi($EB) && $float($EB) > 0)
                || ($isServi($DU) && $float($DU) > 0)
                || ($isServi($EU) && $float($EU) > 0)
                || ($isServi($DV) && $float($DV) > 0)
                || ($isServi($EV) && $float($EV) > 0)
//                || ($isServi($EC) && $float($EC) > 0)
//                || ($isServi($ED) && $float($ED) > 0)
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
                || ($isServi($GA) && $float($GA) > 0)
                || ($isServi($GB) && $float($GB) > 0)
                || ($isServi($HA) && $float($HA) > 0)
                || ($isServi($JA) && $float($JA) > 0)
                || ($isServi($JB) && $float($JB) > 0)
                || ($isServi($JC) && $float($JC) > 0)
                || ($isServi($LF) && $float($LF) > 0)
                || ($isServi($LC) && $float($LC) > 0)
                || ($isServi($SJ) && $float($SJ) > 0)
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
                || ($isServi($SH) && $float($SH) > 0)
                || ($isServi($RR) && $float($RR) > 0)
                || ($isServi($SK) && $float($SK) > 0)
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
                || ($isServi($RZ) && $float($RZ) > 0)), 'erreur_049', $ND);
        }
    }

    public static function rcm2777_20190101($elt, $assert, $isServi, $float, $value, $controls)
    {
        $EB = $elt('rcm2777_20190101_EB');
        $EC = $elt('rcm2777_20190101_EC');
        $FJ = $elt('rcm2777_20190101_FJ');
        $FK = $elt('rcm2777_20190101_FK');
        $FL = $elt('rcm2777_20190101_FL');
        $FM = $elt('rcm2777_20190101_FM');
        $FN = $elt('rcm2777_20190101_FN');
        $FP = $elt('rcm2777_20190101_FP');
        $FQ = $elt('rcm2777_20190101_FQ');
        $FR = $elt('rcm2777_20190101_FR');
        $FS = $elt('rcm2777_20190101_FS');
        $FT = $elt('rcm2777_20190101_FT');
        $FU = $elt('rcm2777_20190101_FU');
        $FV = $elt('rcm2777_20190101_FV');
        $FX = $elt('rcm2777_20190101_FX');
        $FY = $elt('rcm2777_20190101_FY');
        $FZ = $elt('rcm2777_20190101_FZ');
        $GJ = $elt('rcm2777_20190101_GJ');
        $GK = $elt('rcm2777_20190101_GK');
        $GL = $elt('rcm2777_20190101_GL');
        $GM = $elt('rcm2777_20190101_GM');
        $GN = $elt('rcm2777_20190101_GN');
        $GP = $elt('rcm2777_20190101_GP');
        $GQ = $elt('rcm2777_20190101_GQ');
        $GR = $elt('rcm2777_20190101_GR');
        $GS = $elt('rcm2777_20190101_GS');
        $GT = $elt('rcm2777_20190101_GT');
        $GU = $elt('rcm2777_20190101_GU');
        $GV = $elt('rcm2777_20190101_GV');
        $GX = $elt('rcm2777_20190101_GX');
        $GY = $elt('rcm2777_20190101_GY');
        $GZ = $elt('rcm2777_20190101_GZ');
        $IA = $elt('rcm2777_20190101_IA');
        $NA = $elt('rcm2777_20190101_NA');
        $OA = $elt('rcm2777_20190101_OA');
        $RA = $elt('rcm2777_20190101_RA');
        $RB = $elt('rcm2777_20190101_RB');
        $RC = $elt('rcm2777_20190101_RC');
        $RF = $elt('rcm2777_20190101_RF');
        $RG = $elt('rcm2777_20190101_RG');
        $RH = $elt('rcm2777_20190101_RH');
        $RI = $elt('rcm2777_20190101_RI');
        $RJ = $elt('rcm2777_20190101_RJ');
        $RK = $elt('rcm2777_20190101_RK');
        $RL = $elt('rcm2777_20190101_RL');
        $RM = $elt('rcm2777_20190101_RM');
        $RN = $elt('rcm2777_20190101_RN');
        $RO = $elt('rcm2777_20190101_RO');
        $RP = $elt('rcm2777_20190101_RP');
        $RQ = $elt('rcm2777_20190101_RQ');
        $RR = $elt('rcm2777_20190101_RR');
        $RS = $elt('rcm2777_20190101_RS');
        $RT = $elt('rcm2777_20190101_RT');
        $RU = $elt('rcm2777_20190101_RU');
        $RV = $elt('rcm2777_20190101_RV');

        $KF_Identif_month = (float)substr($value($elt('p_identif_20151020_KF')), 0, 2);
        $KF_Identif = $elt('p_identif_20151020_KF');

        $rowIndex = 1;
        while ($elt('rcm2777_20190101_AG/' . $rowIndex)->isset) {
            $AG = $elt('rcm2777_20190101_AG/' . $rowIndex);
            $HB = $elt('rcm2777_20190101_HB/' . $rowIndex);

            $assert(!($float($AG) > 0 && $float($HB) == 0),
                'rcm2777_01',
                $AG, $HB);

            $assert(!($float($AG) == 0 && $float($HB) > 0),
                'rcm2777_21',
                $AG, $HB);

            $assert(!($float($HB) > 0 && ($float($HB) > 75)),
                'rcm2777_02',
                $HB);

            $rowIndex++;
        }

        $rowIndex = 1;
        while ($elt('rcm2777_20190101_JB/' . $rowIndex)->isset) {
            $FB = $elt('rcm2777_20190101_FB/' . $rowIndex);
            $HA = $elt('rcm2777_20190101_HA/' . $rowIndex);

            $assert(!($float($HA) > 0 && ($float($HA) > 100)),
                'rcm2777_03',
                $HA);

            $assert(!($float($FB) > 0 && $float($HA) == 0),
                'rcm2777_01',
                $FB, $HA);

            $assert(!($float($FB) == 0 && $float($HA) > 0),
                'rcm2777_21',
                $FB, $HA);

            $rowIndex++;
        }

        $rowIndex = 1;
        while ($elt('rcm2777_20190101_JF/' . $rowIndex)->isset) {
            $FF = $elt('rcm2777_20190101_FF/' . $rowIndex);
            $HC = $elt('rcm2777_20190101_HC/' . $rowIndex);

            $assert(!($float($FF) > 0 && $float($HC) == 0),
                'rcm2777_01',
                $FF, $HC);

            $assert(!($float($FF) == 0 && $float($HC) > 0),
                'rcm2777_21',
                $FF, $HC);

            $assert(!($float($HC) > 0 && ($float($HC) > 100)),
                'rcm2777_03',
                $HC);

            $rowIndex++;
        }

        $rowIndex = 1;
        while ($elt('rcm2777_20190101_FO/' . $rowIndex)->isset) {
            $FO = $elt('rcm2777_20190101_FO/' . $rowIndex);
            $HD = $elt('rcm2777_20190101_HD/' . $rowIndex);

            $assert(!($float($FO) > 0 && $float($HD) == 0),
                'rcm2777_01',
                $FO, $HD);

            $assert(!($float($FO) == 0 && $float($HD) > 0),
                'rcm2777_21',
                $FO, $HD);

            $assert(!($float($HD) > 0 && ($float($HD) > 100)),
                'rcm2777_03',
                $HD);

            $rowIndex++;
        }

        $rowIndex = 1;
        while ($elt('rcm2777_20190101_FW/' . $rowIndex)->isset) {
            $FW = $elt('rcm2777_20190101_FW/' . $rowIndex);
            $HE = $elt('rcm2777_20190101_HE/' . $rowIndex);

            $assert(!($float($FW) > 0 && $float($HE) == 0),
                'rcm2777_01',
                $FW, $HE);

            $assert(!($float($FW) == 0 && $float($HE) > 0),
                'rcm2777_21',
                $FW, $HE);

            $assert(!($float($HE) > 0 && ($float($HE) > 100)),
                'rcm2777_03',
                $HE);

            $rowIndex++;
        }

        $assert(!($float($FY) < ($float($FK) + $float($FN))),
            'rcm2777_04',
            $FY, $FK, $FN);

        $assert(!($float($GY) < ($float($GK) + $float($GN))),
            'rcm2777_22',
            $GY, $GK, $GN);

        $assert(!(($float($FJ) + $float($FK) + $float($FL) + $float($FM) + $float($FN) + $float($FP) + $float($FQ) + $float($FR) + $float($FS) + $float($FT) + $float($FU) + $float($FV) + $float($FX) > 0) && $float($FY) + $float($FZ) == 0),
            'rcm2777_05',
            $FJ, $FK, $FL, $FM, $FN, $FP, $FQ, $FR, $FS, $FT, $FU, $FV, $FX, $FY, $FZ);

        $assert(!(($float($GJ) + $float($GK) + $float($GL) + $float($GM) + $float($GN) + $float($GP) + $float($GQ) + $float($GR) + $float($GS) + $float($GT) + $float($GU) + $float($GV) + $float($GX) > 0) && $float($GY) + $float($GZ) == 0),
            'rcm2777_23',
            $GJ, $GK, $GL, $GM, $GN, $GP, $GQ, $GR, $GS, $GT, $GU, $GV, $GX, $GY, $GZ);

        $assert(!($float($FZ) < ($float($FJ) + $float($FL) + $float($FM))),
            'rcm2777_06',
            $FZ, $FJ, $FL, $FM);

        $assert(!($float($GZ) < ($float($GJ) + $float($GL) + $float($GM))),
            'rcm2777_06',
            $GZ, $GJ, $GL, $GM);

        $assert(!($float($NA) > 0 && ($float($NA) != $float($FJ) + $float($FK) + $float($FL) + $float($FM) + $float($FN) + $float($FP) + $float($FQ) + $float($FR) + $float($FS) + $float($FT) + $float($FU) + $float($FV) + $float($FX))),
            'rcm2777_07',
            $NA, $FJ, $FK, $FK, $FM, $FN, $FP, $FQ, $FR, $FS, $FT, $FU, $FV, $FX);

        $assert(!($float($OA) > 0 && ($float($OA) != $float($GJ) + $float($GK) + $float($GL) + $float($GM) + $float($GN) + $float($GP) + $float($GQ) + $float($GR) + $float($GS) + $float($GT) + $float($GU) + $float($GV) + $float($GX))),
            'rcm2777_24',
            $NA, $GJ, $GK, $GK, $GM, $GN, $GP, $GQ, $GR, $GS, $GT, $GU, $GV, $GX);

        $assert(!($float($IA) > 0 && $KF_Identif_month == 2),
            'rcm2777_08',
            $IA);

        if ($isServi($KF_Identif)) {
            $splittedKF = explode('/', $value($KF_Identif));
            $formattedKF = $splittedKF[1] . '-' . $splittedKF[0];
            $dateKF = new DateTime($formattedKF);
        }

        $rowIndex = 1;
        while ($elt('rcm2777_20190101_IB/' . $rowIndex)->isset) {
            $IB = $elt('rcm2777_20190101_IB/' . $rowIndex);
            $IE = $elt('rcm2777_20190101_IE/' . $rowIndex);

            if ($isServi($IB)) {
                $splittedIB = explode('/', $value($IB));
                $formattedIB = $splittedIB[1] . '-' . $splittedIB[0];
                $dateIB = new DateTime($formattedIB);


                $assert(!(($isServi($IB) && !$isServi($KF_Identif)) || $dateKF < $dateIB),
                    'rcm2777_09',
                    $IB, $KF_Identif);

                $assert(!($isServi($IB) && $float($IE) == 0),
                    'rcm2777_10',
                    $IB, $IE);

                $assert(!($float($IE) > 0 && !$isServi($IB)),
                    'rcm2777_20',
                    $IB, $IE);
            }

            $rowIndex++;
        }

        //Verifications mois d'imposition
        //September
        $isSeptember = false;
        if ($KF_Identif_month == 10) {
            $isSeptember = true;
        }

        $assert(!($float($RC) > 0 && !$isSeptember),
            'rcm2777_11',
            $RC);

        $assert(!($float($RF) > 0 && !$isSeptember),
            'rcm2777_12',
            $RF);

        $assert(!($float($RA) > 0 && !$isSeptember),
            'rcm2777_11',
            $RA);

        $assert(!($float($RG) > 0 && !$isSeptember),
            'rcm2777_12',
            $RG);

        $assert(!($float($RB) > 0 && !$isSeptember),
            'rcm2777_11',
            $RB);

        $assert(!($float($RH) > 0 && !$isSeptember),
            'rcm2777_12',
            $RH);

        //December
        $isDecember = false;
        if ($KF_Identif_month == 1) {
            $isDecember = true;
        }
        $assert(!($float($RT) > 0 && !$isDecember),
            'rcm2777_13',
            $RT);
        $assert(!($float($RU) > 0 && !$isDecember),
            'rcm2777_13',
            $RU);

        $assert(!($float($RI) > 0 && !$isDecember),
            'rcm2777_14',
            $RI);

        $assert(!($float($RJ) > 0 && !$isDecember),
            'rcm2777_14',
            $RJ);

        $assert(!($float($RK) > 0 && !$isDecember),
            'rcm2777_14',
            $RK);

        $assert(!($float($RL) > 0 && !$isDecember),
            'rcm2777_14',
            $RL);

        $assert(!($float($RM) > 0 && !$isDecember),
            'rcm2777_14',
            $RM);

        $assert(!($float($RN) > 0 && !$isDecember),
            'rcm2777_14',
            $RN);

        //January
        $isJanuary = false;

        if ($KF_Identif_month == 2) {
            $isJanuary = true;
        }

        $assert(!($float($RV) > 0 && !$isJanuary),
            'rcm2777_15',
            $RV);

        $assert(!($float($RO) > 0 && !$isJanuary),
            'rcm2777_16',
            $RO);

        $assert(!($float($RP) > 0 && !$isJanuary),
            'rcm2777_16',
            $RP);

        $assert(!($float($RQ) > 0 && !$isJanuary),
            'rcm2777_17',
            $RQ);

        $assert(!($float($RR) > 0 && !$isJanuary),
            'rcm2777_16',
            $RR);

        $assert(!($float($RS) > 0 && !$isJanuary),
            'rcm2777_16',
            $RS);

        $assert(!($isServi($EC) && $float($EB) == 0),
            'rcm2777_18',
            $EC, $EB);

        $assert(!(($float($EB) > 0 && $isJanuary) && !$isServi($EC)),
            'rcm2777_19',
            $EB, $EC);
    }

    public static function is2571_2019($elt, $assert, $isServi, $float, $value, $controls)
    {
        $CA = $elt('is2571_2019_CA');
        $CC = $elt('is2571_2019_CC');
        $CD = $elt('is2571_2019_CD');
        $CE = $elt('is2571_2019_CE');
        $CH = $elt('is2571_2019_CH');
        $CL = $elt('is2571_2019_CL');
        $CM = $elt('is2571_2019_CM');
        $CN = $elt('is2571_2019_CN');
        $DA = $elt('is2571_2019_DA');
        $DB = $elt('is2571_2019_DB');
        $FA = $elt('is2571_2019_FA');
        $FB = $elt('is2571_2019_FB');
        $FC = $elt('is2571_2019_FC');
        $FD = $elt('is2571_2019_FD');
        $FE = $elt('is2571_2019_FE');
        $FF = $elt('is2571_2019_FF');
        $FG = $elt('is2571_2019_FG');
        $FH = $elt('is2571_2019_FH');
        $FK = $elt('is2571_2019_FK');
        $FM = $elt('is2571_2019_FM');
        $FN = $elt('is2571_2019_FN');

        $assert(!($isServi($FH) && !($isServi($FK) && $isServi($FM))), 'erreur_310', $FH);
        $assert(!($isServi($FH) && $isServi($CH) && !($float($FH) <= $float($CH))), 'erreur_311', $FH);
        $assert(!($isServi($FK) && !($isServi($FH) && $isServi($FM))), 'erreur_310', $FK);
        $assert(!($isServi($FM) && !($isServi($FH) && $isServi($FK))), 'erreur_310', $FM);

        $assert(!($isServi($CM)), 'erreur_324', $CM);
        $assert(!($isServi($CN)), 'erreur_324', $CN);

        $PidentifKF = $elt('p_identif_KF');
        $date_FM = explode('/', $value($FM));
        $date_FM = strtotime($date_FM[0] . '-' . $date_FM[1] . '-' . $date_FM[2]);
        $date_KF = explode('/', $value($PidentifKF));
        $date_KF = strtotime('01-' . $date_KF[0] . '-' . $date_KF[1]);
        $date_KF_inf_dateFM = $date_FM < $date_KF;

        $assert(!($isServi($FM) && $isServi($PidentifKF) && !($date_KF_inf_dateFM)), 'erreur_312', $FM);
    }

    public static function is2572_2019($elt, $assert, $isServi, $float, $value, $controls)
    {
        $AD = $elt('is2572_2019_AD');
        $BD = $elt('is2572_2019_BD');
        $CA = $elt('is2572_2019_CA');
        $DA = $elt('is2572_2019_DA');
        $EA = $elt('is2572_2019_EA');
        $EB = $elt('is2572_2019_EB');
        $GC = $elt('is2572_2019_GC');
        $GD = $elt('is2572_2019_GD');
        $GE = $elt('is2572_2019_GE');
        $IA = $elt('is2572_2019_IA');
        $JA = $elt('is2572_2019_JA');
        $KA = $elt('is2572_2019_KA');
        $KB = $elt('is2572_2019_KB');
        $KC = $elt('is2572_2019_KC');
        $KD = $elt('is2572_2019_KD');
        $LA = $elt('is2572_2019_LA');
        $LB = $elt('is2572_2019_LB');
        $LC = $elt('is2572_2019_LC');
        $LD = $elt('is2572_2019_LD');
        $LE = $elt('is2572_2019_LE');
        $LF = $elt('is2572_2019_LF');
        $MA = $elt('is2572_2019_MA');
        $MB = $elt('is2572_2019_MB');
        $MD = $elt('is2572_2019_MD');
        $MH = $elt('is2572_2019_MH');
        $NA = $elt('is2572_2019_NA');
        $NB = $elt('is2572_2019_NB');
        $ND = $elt('is2572_2019_ND');
        $NE = $elt('is2572_2019_NE');
        $NF = $elt('is2572_2019_NF');
        $NG = $elt('is2572_2019_NG');
        $NJ = $elt('is2572_2019_NJ');
        $NK = $elt('is2572_2019_NK');
        $NM = $elt('is2572_2019_NM');
        $NN = $elt('is2572_2019_NN');
        $NO = $elt('is2572_2019_NO');
        $OB = $elt('is2572_2019_OB');
        $OC = $elt('is2572_2019_OC');
        $OD = $elt('is2572_2019_OD');
        $OE = $elt('is2572_2019_OE');
        $OF = $elt('is2572_2019_OF');
        $OG = $elt('is2572_2019_OG');
        $OH = $elt('is2572_2019_OH');
        $OJ = $elt('is2572_2019_OJ');
        $OK = $elt('is2572_2019_OK');
        $PA = $elt('is2572_2019_PA');
        $PB = $elt('is2572_2019_PB');
        $PC = $elt('is2572_2019_PC');
        $PD = $elt('is2572_2019_PD');
        $PE = $elt('is2572_2019_PE');
        $PF = $elt('is2572_2019_PF');
        $PG = $elt('is2572_2019_PG');
        $PH = $elt('is2572_2019_PH');
        $PJ = $elt('is2572_2019_PJ');
        $PK = $elt('is2572_2019_PK');
        $PL = $elt('is2572_2019_PL');
        $PM = $elt('is2572_2019_PM');
        $PN = $elt('is2572_2019_PN');
        $PQ = $elt('is2572_2019_PQ');
        $PT = $elt('is2572_2019_PT');
        $PU = $elt('is2572_2019_PU');
        $PV = $elt('is2572_2019_PV');
        $PW = $elt('is2572_2019_PW');
        $RA = $elt('is2572_2019_RA');
        $RB = $elt('is2572_2019_RB');
        $RC = $elt('is2572_2019_RC');
        $RD = $elt('is2572_2019_RD');
        $RE = $elt('is2572_2019_RE');
        $RF = $elt('is2572_2019_RF');
        $RG = $elt('is2572_2019_RG');
        $RH = $elt('is2572_2019_RH');
        $RJ = $elt('is2572_2019_RJ');
        $RK = $elt('is2572_2019_RK');
        $RL = $elt('is2572_2019_RL');
        $RM = $elt('is2572_2019_RM');
        $RN = $elt('is2572_2019_RN');
        $RP = $elt('is2572_2019_RP');
        $RR = $elt('is2572_2019_RR');
        $RS = $elt('is2572_2019_RS');
        $RT = $elt('is2572_2019_RT');
        $RW = $elt('is2572_2019_RW');
        $RZ = $elt('is2572_2019_RZ');
        $SA = $elt('is2572_2019_SA');
        $TA = $elt('is2572_2019_TA');
        $TB = $elt('is2572_2019_TB');
        $TC = $elt('is2572_2019_TC');

        $PidentifKF = $elt('p_identif_20151020_KF');
        $date_PJ = explode('/', $value($PJ));
        $date_PJ = strtotime($date_PJ[0] . '-' . $date_PJ[1] . '-' . $date_PJ[0]);
        $date_KF = explode('/', $value($PidentifKF));
        $date_KF = strtotime('01-' . $date_KF[0] . '-' . $date_KF[1]);
        $date_KF_inf_datePJ = $date_PJ < $date_KF;


        //$assert(!($isServi($PJ) && $isServi($PidentifKF) && !($date_KF_inf_datePJ)), 'erreur_318', $PJ);


        $isServi_PH_PK_PJ = ($isServi($PH) && (!$isServi($PK) || !$isServi($PJ)))
            || ($isServi($PK) && (!$isServi($PH) || !$isServi($PJ)))
            || ($isServi($PJ) && (!$isServi($PH) || !$isServi($PK)));

        $assert(!$isServi_PH_PK_PJ, 'erreur_310', $PH, $PK, $PJ);

        $isServi_PE_PG_PF = ($isServi($PE) && (!$isServi($PG) || !$isServi($PF)))
            || ($isServi($PG) && (!$isServi($PE) || !$isServi($PF)))
            || ($isServi($PF) && (!$isServi($PE) || !$isServi($PG)));

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
        $assert(!(($isServi($LE) && !$isServi($LF)) || (($isServi($LE) && $isServi($LF)) && ($LE_value == '' || $LF_value == ''))),
            'erreur_322', $LE, $LF);

        $OJ_value = !is_numeric($value($OJ)) ? '' : $float($OJ);
        $OH_value = !is_numeric($value($OH)) ? '' : $float($OH);
        $assert(!(($isServi($OJ) && !$isServi($OH)) || (($isServi($OJ) && $isServi($OH)) && ($OJ_value == '' || $OH_value == ''))),
            'erreur_322', $OJ, $OH);

        $OE_value = !is_numeric($value($OE)) ? '' : $float($OE);
        $KD_value = !is_numeric($value($KD)) ? '' : $float($KD);
        $assert(!(($isServi($OE) && !$isServi($KD)) || (($isServi($OE) && $isServi($KD)) && ($OE_value == '' || $KD_value == ''))),
            'erreur_322', $OE, $KD);

        $OG_value = !is_numeric($value($OG)) ? '' : $float($OG);
        $OF_value = !is_numeric($value($OF)) ? '' : $float($OF);
        $assert(!(($isServi($OG) && !$isServi($OF)) || (($isServi($OG) && $isServi($OF)) && ($OG_value == '' || $OF_value == ''))),
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

        $assert(!(($isServi($OJ) || $isServi($OH)) && !$valid_CB),
            'erreur_323', $OJ, $OH);
    }

    public static function is2573_2019($elt, $assert, $isServi, $float, $value, $controls)
    {
        $AA = $elt('is2573_2019_AA');
        $AJ = $elt('is2573_2019_AJ');
        $BA = $elt('is2573_2019_BA');
        $BF = $elt('is2573_2019_BF');
        $CA = $elt('is2573_2019_CA');
        $CG = $elt('is2573_2019_CG');

        $BA_value = $value($BA);
        $assert(!($isServi($BA) && !Valid::isSiren($BA_value)), 'Vous devez saisir un SIREN valide', $BA);
        $CA_value = $value($CA);
        $assert(!($isServi($CA) && !Valid::isSiren($CA_value)), 'Vous devez saisir un SIREN valide', $CA);

        // for each row
        $rowIndex = 1;
        while ($elt('is2573_2019_AB/' . $rowIndex)->isset) {
            $AB = $elt('is2573_2019_AB/' . $rowIndex);
            $AC = $elt('is2573_2019_AC/' . $rowIndex);
            $AF = $elt('is2573_2019_AF/' . $rowIndex);
            $AG = $elt('is2573_2019_AG/' . $rowIndex);
            $AH = $elt('is2573_2019_AH/' . $rowIndex);
            $AI = $elt('is2573_2019_AI/' . $rowIndex);
            $KA = $elt('is2573_2019_KA/' . $rowIndex);
            $KB = $elt('is2573_2019_KB/' . $rowIndex);
            $KC = $elt('is2573_2019_KC/' . $rowIndex);
            $KD = $elt('is2573_2019_KD/' . $rowIndex);

            $assert($value($AB) != 'REL' && $value($AB) != 'RES', 'erreur_325', $AB, $AC);

            if ($value($AB) == 'EXP' || $value($AB) == 'CAI') {
                $assert(!($value($AC) >= '2018'), 'erreur_325', $AB, $AC);
            }

            $assert($value($AB) != 'REL' && $value($AB) != 'RES', 'erreur_309', $AB);

            $assert(!($isServi($BA) && !($value($AB) == 'RAD' && $isServi($AH))), 'erreur_313', $AF, $AB, $AH);

            $assert(!(($isServi($AB) || $isServi($AC) || $isServi($AF) || $isServi($AG) || $isServi($AH) || $isServi($AI))
                && !($isServi($AB) && $isServi($AC) && $isServi($AG) && $float($AG) > 0)),
                'erreur_315', $AB, $AC, $AF, $AG, $AH, $AI);
            $assert(!($isServi($AF) && !($value($AB) == 'RAD' && $isServi($AH))), 'erreur_313', $AF, $AB, $AH);
            $assert(!($isServi($AH) && !$isServi($AI)), 'erreur_305', $AI);
            $assert(!($isServi($AI) && !$isServi($AH)), 'erreur_305', $AH);

            $date_KC = explode('/', $value($KC));
            $date_KC = strtotime($date_KC[2] . '-' . $date_KC[1] . '-' . $date_KC[0] . 'T23:59:59');
            $assert(!($isServi($KC) && ($date_KC < time())), 'erreur_320', $KC);

            $isServi_KB_KC_KD = ($isServi($KB) && (!$isServi($KC) || !$isServi($KD)))
                || ($isServi($KC) && (!$isServi($KB) || !$isServi($KD)))
                || ($isServi($KD) && (!$isServi($KB) || !$isServi($KC)));

            $assert(!$isServi_KB_KC_KD, 'erreur_321', $KB, $KC, $KD);

            $assert(!($isServi($KD) && $isServi($AG) && !($float($KD) <= $float($AG))), 'erreur_314', $KD);
            $rowIndex++;
        }

        // for each row
        $rowIndex = 1;
        while ($elt('is2573_2019_BB/' . $rowIndex)->isset) {
            $BB = $elt('is2573_2019_BB/' . $rowIndex);
            $BC = $elt('is2573_2019_BC/' . $rowIndex);
            $BD = $elt('is2573_2019_BD/' . $rowIndex);
            $BE = $elt('is2573_2019_BE/' . $rowIndex);

            $BD_value = $value($BD);
            $assert(!($isServi($BD) && !Valid::isSiren($BD_value)), 'Vous devez saisir un SIREN valide', $BD);

            $assert(!(($isServi($BB) || $isServi($BC) || $isServi($BD) || $isServi($BE))
                && !($isServi($BB) && $isServi($BC) && $isServi($BE) && $float($BE) > 0)),
                'erreur_307', $BB, $BC, $BD, $BE);
            $rowIndex++;
        }

        // for each row
        $rowIndex = 1;
        while ($elt('is2573_2019_CB/' . $rowIndex)->isset) {
            $CB = $elt('is2573_2019_CB/' . $rowIndex);
            $CC = $elt('is2573_2019_CC/' . $rowIndex);
            $CD = $elt('is2573_2019_CD/' . $rowIndex);
            $CE = $elt('is2573_2019_CE/' . $rowIndex);
            $CF = $elt('is2573_2019_CF/' . $rowIndex);

            $CE_value = $value($CE);
            $assert(!($isServi($CE) && !Valid::isSiren($CE_value)), 'Vous devez saisir un SIREN valide', $CE);

            $assert(!(($isServi($CB) || $isServi($CC) || $isServi($CD) || $isServi($CE) || $isServi($CF))
                && !($isServi($CB) && $isServi($CC) && $isServi($CD) && $isServi($CF) && $float($CF) > 0)),
                'erreur_308', $CB, $CC, $CD, $CF);

            $rowIndex++;
        }
    }
}
