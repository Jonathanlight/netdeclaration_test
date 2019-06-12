/** Millésime 2019 **/

if (!formulaires) {
    var formulaires = {};
}

formulaires.helpers = {
    duplicate: function (form_name) {
        var target = null;
        [1, 2, 3, 4].each(function (i) {
            var className = form_name + '_0' + i + '-dynamic-row';
            if ($$('.' + className).length == 0) {
                return;
            }
            ntd.tableRowManager.addTableRow(className);
            formulaires.helpers.updateSecteurs(className);
            asserts.run(form_name);
        });
    },
    delete: function (form_name, elt) {
        var secteur = $(elt).up('tr').getAttribute('data-secteur');
        [1, 2, 3, 4].each(function (i) {
            var className = form_name + '_0' + i + '-dynamic-row';
            if ($$('.' + className).length == 0) {
                return;
            }
            var row = $$('.' + className + '[data-secteur="' + secteur + '"]').first();
            ntd.tableRowManager.removeTableRow(row, className);
            formulaires.helpers.updateSecteurs(className);
            asserts.run(form_name);
        });
    },
    updateSecteurs: function (className) {
        var rows = $$('.' + className + '[data-secteur]');
        var index = 1;
        rows.each(function (row) {
            row.setAttribute('data-secteur', index++);
        });
    }
}

// ---- Controls IFU 2561 ---- //
asserts.functions.ifu2561_20190101 = function ($elt,
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

    var formOccurences = $$('.formulaire-block.ifu2561 .page-form')
    if (!formOccurences.length) {
        formOccurences = $$('.formulaire-visibility.ifu2561 .page-form');
    }

    for (var occurence = 0; occurence < formOccurences.length; occurence++) {

        // Page 1
        var $AA01 = $elt('ifu2561_20190101_AA01', formOccurences[occurence]);
        var $AA02 = $elt('ifu2561_20190101_AA02', formOccurences[occurence]);
        var $AA03 = $elt('ifu2561_20190101_AA03', formOccurences[occurence]);
        var $AB = $elt('ifu2561_20190101_AB', formOccurences[occurence]);
        var $AC = $elt('ifu2561_20190101_AC', formOccurences[occurence]);
        var $AD = $elt('ifu2561_20190101_AD', formOccurences[occurence]);
        var $AE02 = $elt('ifu2561_20190101_AE02', formOccurences[occurence]);
        var $AE03 = $elt('ifu2561_20190101_AE03', formOccurences[occurence]);
        var $AE04 = $elt('ifu2561_20190101_AE04', formOccurences[occurence]);
        var $AE14_1 = $elt('ifu2561_20190101_AE14_1', formOccurences[occurence]);
        var $AE14_2 = $elt('ifu2561_20190101_AE14_2', formOccurences[occurence]);
        var $AE15 = $elt('ifu2561_20190101_AE15', formOccurences[occurence]);
        var $AF01 = $elt('ifu2561_20190101_AF01', formOccurences[occurence]);
        var $AF02 = $elt('ifu2561_20190101_AF02', formOccurences[occurence]);
        var $AG05 = $elt('ifu2561_20190101_AG05', formOccurences[occurence]);
        var $AG06 = $elt('ifu2561_20190101_AG06', formOccurences[occurence]);
        var $AG08 = $elt('ifu2561_20190101_AG08', formOccurences[occurence]);
        var $AG09 = $elt('ifu2561_20190101_AG09', formOccurences[occurence]);
        var $AG14_1 = $elt('ifu2561_20190101_AG14_1', formOccurences[occurence]);
        var $AG14_2 = $elt('ifu2561_20190101_AG14_2', formOccurences[occurence]);
        var $AG15 = $elt('ifu2561_20190101_AG15', formOccurences[occurence]);
        var $AG16 = $elt('ifu2561_20190101_AG16', formOccurences[occurence]);
        var $AG17 = $elt('ifu2561_20190101_AG17', formOccurences[occurence]);
        var $AH = $elt('ifu2561_20190101_AH', formOccurences[occurence]);
        var $AJ = $elt('ifu2561_20190101_AJ', formOccurences[occurence]);
        var $AK = $elt('ifu2561_20190101_AK', formOccurences[occurence]);
        var $AL = $elt('ifu2561_20190101_AK', formOccurences[occurence]);
        var $AM = $elt('ifu2561_20190101_AM', formOccurences[occurence]);
        var $AN = $elt('ifu2561_20190101_AN', formOccurences[occurence]);
        var $AP = $elt('ifu2561_20190101_AP', formOccurences[occurence]);
        var $BE = $elt('ifu2561_20190101_BE', formOccurences[occurence]);
        var $BF = $elt('ifu2561_20190101_BF', formOccurences[occurence]);
        var $BG = $elt('ifu2561_20190101_BG', formOccurences[occurence]);
        var $BH = $elt('ifu2561_20190101_BH', formOccurences[occurence]);
        var $BJ = $elt('ifu2561_20190101_BJ', formOccurences[occurence]);
        var $BK = $elt('ifu2561_20190101_BK', formOccurences[occurence]);
        var $BN = $elt('ifu2561_20190101_BN', formOccurences[occurence]);
        var $BP = $elt('ifu2561_20190101_BP', formOccurences[occurence]);
        var $BR = $elt('ifu2561_20190101_BR', formOccurences[occurence]);
        var $BS = $elt('ifu2561_20190101_BS', formOccurences[occurence]);
        var $BT = $elt('ifu2561_20190101_BT', formOccurences[occurence]);
        var $BV = $elt('ifu2561_20190101_BV', formOccurences[occurence]);
        var $CA = $elt('ifu2561_20190101_CA', formOccurences[occurence]);
        var $CB = $elt('ifu2561_20190101_CB', formOccurences[occurence]);
        var $CC = $elt('ifu2561_20190101_CC', formOccurences[occurence]);
        var $CD = $elt('ifu2561_20190101_CD', formOccurences[occurence]);
        var $CH = $elt('ifu2561_20190101_CH', formOccurences[occurence]);
        var $EA = $elt('ifu2561_20190101_EA', formOccurences[occurence]);
        var $EB = $elt('ifu2561_20190101_EB', formOccurences[occurence]);
        var $EC = $elt('ifu2561_20190101_EC', formOccurences[occurence]);
        var $ED = $elt('ifu2561_20190101_ED', formOccurences[occurence]);
        var $EE = $elt('ifu2561_20190101_EE', formOccurences[occurence]);
        var $EF = $elt('ifu2561_20190101_EF', formOccurences[occurence]);
        var $EG = $elt('ifu2561_20190101_EG', formOccurences[occurence]);
        var $EH = $elt('ifu2561_20190101_EH', formOccurences[occurence]);
        var $EJ = $elt('ifu2561_20190101_EJ', formOccurences[occurence]);
        var $EK = $elt('ifu2561_20190101_EK', formOccurences[occurence]);
        var $EL = $elt('ifu2561_20190101_EL', formOccurences[occurence]);
        var $ZZ1 = $elt('ifu2561_20190101_ZZ1', formOccurences[occurence]);
        var $ZZ2 = $elt('ifu2561_20190101_ZZ2', formOccurences[occurence]);

        // Page 2
        var $BA = $elt('ifu2561_20190101_BA', formOccurences[occurence]);
        var $BB = $elt('ifu2561_20190101_BB', formOccurences[occurence]);
        var $BC = $elt('ifu2561_20190101_BC', formOccurences[occurence]);
        var $BU = $elt('ifu2561_20190101_BU', formOccurences[occurence]);
        var $CF = $elt('ifu2561_20190101_CF', formOccurences[occurence]);
        var $CG = $elt('ifu2561_20190101_CG', formOccurences[occurence]);
        var $CJ = $elt('ifu2561_20190101_CJ', formOccurences[occurence]);
        var $CK = $elt('ifu2561_20190101_CK', formOccurences[occurence]);
        var $CL = $elt('ifu2561_20190101_CL', formOccurences[occurence]);
        var $CM = $elt('ifu2561_20190101_CM', formOccurences[occurence]);
        var $CN = $elt('ifu2561_20190101_CN', formOccurences[occurence]);
        var $CP = $elt('ifu2561_20190101_CP', formOccurences[occurence]);
        var $CR = $elt('ifu2561_20190101_CR', formOccurences[occurence]);
        var $CS = $elt('ifu2561_20190101_CS', formOccurences[occurence]);
        var $CT = $elt('ifu2561_20190101_CT', formOccurences[occurence]);
        var $CU = $elt('ifu2561_20190101_CU', formOccurences[occurence]);
        var $CV = $elt('ifu2561_20190101_CV', formOccurences[occurence]);
        var $CW = $elt('ifu2561_20190101_CW', formOccurences[occurence]);
        var $CX = $elt('ifu2561_20190101_CX', formOccurences[occurence]);
        var $CY = $elt('ifu2561_20190101_CY', formOccurences[occurence]);
        var $CZ = $elt('ifu2561_20190101_CZ', formOccurences[occurence]);
        var $DA = $elt('ifu2561_20190101_DA', formOccurences[occurence]);
        var $DB = $elt('ifu2561_20190101_DB', formOccurences[occurence]);
        var $DC = $elt('ifu2561_20190101_DC', formOccurences[occurence]);
        var $DD = $elt('ifu2561_20190101_DD', formOccurences[occurence]);
        var $DE = $elt('ifu2561_20190101_DE', formOccurences[occurence]);
        var $DF = $elt('ifu2561_20190101_DF', formOccurences[occurence]);
        var $DG = $elt('ifu2561_20190101_DG', formOccurences[occurence]);
        var $DH = $elt('ifu2561_20190101_DH', formOccurences[occurence]);
        var $DI = $elt('ifu2561_20190101_DI', formOccurences[occurence]);
        var $DJ = $elt('ifu2561_20190101_DJ', formOccurences[occurence]);
        var $DK = $elt('ifu2561_20190101_DK', formOccurences[occurence]);
        var $DL = $elt('ifu2561_20190101_DL', formOccurences[occurence]);
        var $DM = $elt('ifu2561_20190101_DM', formOccurences[occurence]);
        var $DN = $elt('ifu2561_20190101_DN', formOccurences[occurence]);
        var $DP = $elt('ifu2561_20190101_DP', formOccurences[occurence]);
        var $EM = $elt('ifu2561_20190101_EM', formOccurences[occurence]);
        var $EN = $elt('ifu2561_20190101_EN', formOccurences[occurence]);
        var $EP = $elt('ifu2561_20190101_EP', formOccurences[occurence]);
        var $ER = $elt('ifu2561_20190101_ER', formOccurences[occurence]);
        var $ES = $elt('ifu2561_20190101_ES', formOccurences[occurence]);
        var $ET = $elt('ifu2561_20190101_ET', formOccurences[occurence]);
        var $EU = $elt('ifu2561_20190101_EU', formOccurences[occurence]);
        var $EV = $elt('ifu2561_20190101_EV', formOccurences[occurence]);
        var $EW = $elt('ifu2561_20190101_EW', formOccurences[occurence]);
        var $EX = $elt('ifu2561_20190101_EX', formOccurences[occurence]);
        var $EY = $elt('ifu2561_20190101_EY', formOccurences[occurence]);
        var $FA = $elt('ifu2561_20190101_FA', formOccurences[occurence]);
        var $FB = $elt('ifu2561_20190101_FB', formOccurences[occurence]);
        var $FC = $elt('ifu2561_20190101_FC', formOccurences[occurence]);
        var $FD = $elt('ifu2561_20190101_FD', formOccurences[occurence]);
        var $FE = $elt('ifu2561_20190101_FE', formOccurences[occurence]);
        var $FF = $elt('ifu2561_20190101_FF', formOccurences[occurence]);
        var $FG = $elt('ifu2561_20190101_FG', formOccurences[occurence]);
        var $FH = $elt('ifu2561_20190101_FH', formOccurences[occurence]);
        var $FJ = $elt('ifu2561_20190101_FJ', formOccurences[occurence]);
        var $FK = $elt('ifu2561_20190101_FK', formOccurences[occurence]);
        var $FL = $elt('ifu2561_20190101_FL', formOccurences[occurence]);
        var $FM = $elt('ifu2561_20190101_FM', formOccurences[occurence]);
        var $FP = $elt('ifu2561_20190101_FP', formOccurences[occurence]);
        var $FR = $elt('ifu2561_20190101_FR', formOccurences[occurence]);
        var $FS = $elt('ifu2561_20190101_FS', formOccurences[occurence]);
        var $FN = $elt('ifu2561_20190101_FN', formOccurences[occurence]);

        $readonly($AG15, true);

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

        if ($isServi($AE14_2)) {
            $assert(($value($AE14_2).substr(0, 2) == 99), 'erreur_ifu_etranger', $AE14_2);
        }

        if ($isServi($AG14_2)) {
            $assert(($value($AG14_2).substr(0, 2) == 99), 'erreur_ifu_etranger', $AG14_2);
        }

        if ($isServi($AF02)) { // Si Cas n°2 Personne morale
            if ($isServi($ZZ1) && $float($ZZ1)) {
                $assert(!$isServi($AE14_1), 'erreur_not_required', $AE14_1);
            } else {
                $assert(!$isServi($AE14_2), 'erreur_not_required', $AE14_2);
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
        if ($isServi($AF02)) {
            $assert($isServi($AF01), 'erreur_required', $AF01);
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

        $assert(($isServi($BE) || $isServi($BF) || $isServi($BG) || $isServi($BH) || $isServi($BJ) || $isServi($BK) || $isServi($BN) ||
                $isServi($BP) || $isServi($BR) || $isServi($BS) || $isServi($BV) || $isServi($CA) || $isServi($CB) || $isServi($CC) ||
                $isServi($CD) || $isServi($CT) || $isServi($CU) || $isServi($CW) || $isServi($CX) || $isServi($CY) || $isServi($CZ) ||
                $isServi($CF) || $isServi($CG) || $isServi($CJ) || $isServi($CK) || $isServi($CL) || $isServi($CM) || $isServi($DB) ||
                $isServi($CN) || $isServi($DE) || $isServi($DF) || $isServi($DG) || $isServi($DC) || $isServi($CP) || $isServi($CR) ||
                $isServi($CS) || $isServi($DH) || $isServi($DJ) || $isServi($DD) || $isServi($EB) || $isServi($EC) || $isServi($ED) ||
                $isServi($EE) || $isServi($EF) || $isServi($EG) || $isServi($EH) || $isServi($FB) || $isServi($FC) || $isServi($FJ) || $isServi($FK) || $isServi($FM) || $isServi($FN) || $isServi($FD) ||
                $isServi($FE) || $isServi($FF) || $isServi($FG) || $isServi($FH) || $isServi($EJ) || $isServi($EK) || $isServi($DL) ||
                $isServi($DM) || $isServi($DN) || $isServi($DP) || $isServi($EM) || $isServi($EN) || $isServi($EP) || $isServi($ER) ||
                $isServi($ES) || $isServi($ET) || $isServi($EU) || $isServi($EV) || $isServi($EW) || $isServi($EX)),
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

        if ($isServi($FJ)) {
            $assert(($isServi($FM)), 'erreur_234_ifu', $FM, $FJ);
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

        if ($isServi($ZZ1) && $float($ZZ1)) {
            $readonly($AE14_2);
            $value($AE14_2, '');
            if (!$AE14_2.hasClassName('hidden')) {
                $AE14_2.addClassName('hidden');
            }
            $AE14_1.removeClassName('hidden');
        } else {
            $readonly($AE14_1);
            $value($AE14_1, '');
            if (!$AE14_1.hasClassName('hidden')) {
                $AE14_1.addClassName('hidden');
            }
            $AE14_2.removeClassName('hidden')
        }

        if ($isServi($ZZ2) && $float($ZZ2)) {
            $readonly($AG14_2);
            $value($AG14_2, '');
            if (!$AG14_2.hasClassName('hidden')) {
                $AG14_2.addClassName('hidden');
            }
            $AG14_1.removeClassName('hidden');
        } else {
            $readonly($AG14_1);
            $value($AG14_1, '');
            if (!$AG14_1.hasClassName('hidden')) {
                $AG14_1.addClassName('hidden');
            }
            $AG14_2.removeClassName('hidden')
        }

        /** Controls */
        $AG09.observe('keyup', function (event) {
            $AG14_1.innerHTML = "";
        });
        if ($isServi($AG09) && !$isServi($AG14_1)) {
            gouv.api.requestCodeInseeByPostalCode($AG14_1, $value($AG09))
        }

        $AE15.observe('keyup', function (event) {
            $AE14_1.innerHTML = "";
        });
        if ($isServi($AE15) && !$isServi($AE14_1)) {
            gouv.api.requestCodeInseeByCity($AE14_1, $value($AE15))
        }
    }
}

// ------ Controls A-IDENTIF-HON, DAS2-T, DAS2-TV ----- //
asserts.functions.a_identif_hon_20190101 = function ($elt,
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
    /** Variables */
    var $AA01 = $elt('a_identif_hon_20190101_AA01');
    var $AA02 = $elt('a_identif_hon_20190101_AA02');
    var $AA05 = $elt('a_identif_hon_20190101_AA05');
    var $AA06 = $elt('a_identif_hon_20190101_AA06');
    var $AA08 = $elt('a_identif_hon_20190101_AA08');
    var $AA09 = $elt('a_identif_hon_20190101_AA09');
    var $AA11 = $elt('a_identif_hon_20190101_AA11');
    var $AA12 = $elt('a_identif_hon_20190101_AA12');
    var $AA13 = $elt('a_identif_hon_20190101_AA13');
    var $AA14 = $elt('a_identif_hon_20190101_AA14');
    var $AA15 = $elt('a_identif_hon_20190101_AA15');
    var $AA16 = $elt('a_identif_hon_20190101_AA16');
    var $AA17 = $elt('a_identif_hon_20190101_AA17');
    var $AB01 = $elt('a_identif_hon_20190101_AB01');
    var $AB05 = $elt('a_identif_hon_20190101_AB05');
    var $AB06 = $elt('a_identif_hon_20190101_AB06');
    var $AB08 = $elt('a_identif_hon_20190101_AB08');
    var $AB09 = $elt('a_identif_hon_20190101_AB09');
    var $AB14 = $elt('a_identif_hon_20190101_AB14');
    var $AB15 = $elt('a_identif_hon_20190101_AB15');
    var $AB16 = $elt('a_identif_hon_20190101_AB16');
    var $AB17 = $elt('a_identif_hon_20190101_AB17');
    var $BA = $elt('a_identif_hon_20190101_BA');
    var $BD = $elt('a_identif_hon_20190101_BD');
    var $BB = $elt('a_identif_hon_20190101_BB');
    var $BC = $elt('a_identif_hon_20190101_BC');
    var $CA = $elt('a_identif_hon_20190101_CA');
    var $CB = $elt('a_identif_hon_20190101_CB');
    var $DA = $elt('a_identif_hon_20190101_DA');

    $readonly($AB15, true);

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

    /** Controls */
    $assert(($isServi($AA02)), 'erreur_307_das2', $AA02);

    $AA09.observe('keyup', function (event) {
        $AA14.innerHTML = "";
    });

    if ($isServi($AA09) && !$isServi($AA14)) {
        gouv.api.requestCodeInseeByPostalCode($AA14, $value($AA09))
    }

    $AB09.observe('keyup', function (event) {
        $AB14.innerHTML = "";
    });

    if ($isServi($AB09) && !$isServi($AB14)) {
        gouv.api.requestCodeInseeByPostalCode($AB14, $value($AB09))
    }
}

asserts.functions.a_identif_ifu_20190101 = function ($elt,
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
    var $AA01 = $elt('a_identif_ifu_20190101_AA01');
    var $AA02 = $elt('a_identif_ifu_20190101_AA02');
    var $AA03 = $elt('a_identif_ifu_20190101_AA03');
    var $AA04 = $elt('a_identif_ifu_20190101_AA04');
    var $AA05 = $elt('a_identif_ifu_20190101_AA05');
    var $AA06 = $elt('a_identif_ifu_20190101_AA06');
    var $AA08 = $elt('a_identif_ifu_20190101_AA08');
    var $AA09 = $elt('a_identif_ifu_20190101_AA09');
    var $AA11 = $elt('a_identif_ifu_20190101_AA11');
    var $AA12 = $elt('a_identif_ifu_20190101_AA12');
    var $AA13 = $elt('a_identif_ifu_20190101_AA13');
    var $AA14 = $elt('a_identif_ifu_20190101_AA14');
    var $AA15 = $elt('a_identif_ifu_20190101_AA15');
    var $AA16 = $elt('a_identif_ifu_20190101_AA16');
    var $AA17 = $elt('a_identif_ifu_20190101_AA17');

    var $BA = $elt('a_identif_ifu_20190101_BA');
    var $BB = $elt('a_identif_ifu_20190101_BB');
    var $BC = $elt('a_identif_ifu_20190101_BC');
    var $BD = $elt('a_identif_ifu_20190101_BD');

    var $CB = $elt('a_identif_ifu_20190101_CB');
    var $CC = $elt('a_identif_ifu_20190101_CC');

    var $DA = $elt('a_identif_ifu_20190101_DA');

    $assert($isServi($AA01), 'erreur_required', $AA01);
    $assert($isServi($AA02), 'erreur_required', $AA02);
    $assert($isServi($AA05), 'erreur_required', $AA05);
    $assert($isServi($AA08), 'erreur_required', $AA08);
    $assert($isServi($AA09), 'erreur_required', $AA09);
    $assert($isServi($AA14), 'erreur_required', $AA14);
    $assert($isServi($AA15), 'erreur_required', $AA15);
    $assert($isServi($AA16), 'erreur_required', $AA16);
    $assert($isServi($BA), 'erreur_required', $BA);
    $assert($isServi($BB), 'erreur_required', $BB);
    $assert($isServi($BC), 'erreur_required', $BC);
    $assert($isServi($BD), 'erreur_required', $BD);
    $assert($isServi($CC), 'erreur_required', $CC);
    $assert($isServi($DA), 'erreur_required', $DA);
    $assert($isServi($AA11), 'erreur_required', $AA11);
    $assert($isServi($AA12), 'erreur_required', $AA12);
    $assert($isServi($AA13), 'erreur_required', $AA13);

    /** Controls */
    if ($isServi($AA08)) {
        $value($AA15, $value($AA08));
    }

    $AA09.observe('keyup', function (event) {
        $AA14.innerHTML = "";
    });
    if ($isServi($AA09) && !$isServi($AA14)) {
        gouv.api.requestCodeInseeByPostalCode($AA14, $value($AA09))
    }

}

asserts.functions.das2t_20190101 = function ($elt,
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

    var formOccurences = $$('.formulaire-block.DAS2T .page-form')
    if (!formOccurences.length) {
        formOccurences = $$('.formulaire-visibility.DAS2T .page-form');
    }

    for (var occurence = 0; occurence < formOccurences.length; occurence++) {
        //**  Variables */
        // A..
        var $AA01 = $elt('das2t_20190101_AA01', formOccurences[occurence]);
        var $AA02 = $elt('das2t_20190101_AA02', formOccurences[occurence]);
        var $AA02 = $elt('das2t_20190101_AA02', formOccurences[occurence]);
        var $AA05 = $elt('das2t_20190101_AA05', formOccurences[occurence]);
        var $AA06 = $elt('das2t_20190101_AA06', formOccurences[occurence]);
        var $AA08 = $elt('das2t_20190101_AA08', formOccurences[occurence]);
        var $AA09 = $elt('das2t_20190101_AA09', formOccurences[occurence]);
        var $AA16 = $elt('das2t_20190101_AA16', formOccurences[occurence]);
        var $AA14 = $elt('das2t_20190101_AA14', formOccurences[occurence]);
        var $AA15 = $elt('das2t_20190101_AA15', formOccurences[occurence]);
        var $AA17 = $elt('das2t_20190101_AA17', formOccurences[occurence]);
        var $AD = $elt('das2t_20190101_AD', formOccurences[occurence]);
        var $AB = $elt('das2t_20190101_AB', formOccurences[occurence]);
        var $AC = $elt('das2t_20190101_AC', formOccurences[occurence]);
        var $AE = $elt('das2t_20190101_AE', formOccurences[occurence]);

        // U..
        var $UA = $elt('das2t_20190101_UA', formOccurences[occurence]);

        // T..
        var $TA = $elt('das2t_20190101_TA', formOccurences[occurence]);
        var $TB = $elt('das2t_20190101_TB', formOccurences[occurence]);
        var $TC = $elt('das2t_20190101_TC', formOccurences[occurence]);
        var $TD = $elt('das2t_20190101_TD', formOccurences[occurence]);


        var $AA01_identif = $('a_identif_hon_20190101_AA01'); // Siret
        var $AA02_identif = $('a_identif_hon_20190101_AA02'); // Raison sociale
        var $AA05_identif = $('a_identif_hon_20190101_AA05'); // rue
        var $AA06_identif = $('a_identif_hon_20190101_AA06'); // complément d'adresse
        var $AA08_identif = $('a_identif_hon_20190101_AA08'); // Ville
        var $AA09_identif = $('a_identif_hon_20190101_AA09'); // CP
        var $AA16_identif = $('a_identif_hon_20190101_AA16'); // N° rue
        var $AA17_identif = $('a_identif_hon_20190101_AA17'); // Suffixe
        var $CA_identif = $('a_identif_hon_20190101_CA'); // APE

        $value($AA01, $value($AA01_identif));
        $value($AA02, $value($AA02_identif));
        $value($AA05, $value($AA05_identif));
        $value($AA06, $value($AA06_identif));
        $value($AA08, $value($AA08_identif));

        if (!$isServi($AA09)) {
            $value($AA09, $value($AA09_identif));
        }

        $value($AA16, $value($AA16_identif));
        $value($AA17, $value($AA17_identif));
        $value($AB, $value($CA_identif));

        $assert($isServi($AA01), 'erreur_required', $AA01);
        $assert($isServi($AA02), 'erreur_required', $AA02);
        $assert($isServi($AA05), 'erreur_required', $AA05);
        $assert($isServi($AA08), 'erreur_required', $AA08);
        $assert($isServi($AA09), 'erreur_required', $AA09);
        $assert($isServi($AA14), 'erreur_required', $AA14);
        $assert($isServi($AA15), 'erreur_required', $AA15);
        $assert($isServi($AA16), 'erreur_required', $AA16);
        $assert($isServi($AB), 'erreur_required', $AB);

        var $rowIndex = 1;
        var natureUsed = [];

        while ($elt('das2t_20190101_UA/' + $rowIndex, formOccurences[occurence])) {
            var $UA = $elt('das2t_20190101_UA/' + $rowIndex, formOccurences[occurence])
            var $TA = $elt('das2t_20190101_TA/' + $rowIndex, formOccurences[occurence])

            if ($isServi($UA)) {
                $assert(!natureUsed.includes($value($UA)), 'erreur_das_multiple_ua', $UA);
                natureUsed.push($value($UA));
            }


            $rowIndex++;
        }

        /** Controls */

        if ($isServi($AA08)) {
            $value($AA15, $value($AA08));
        }

        $AA09.observe('keyup', function (event) {
            $AA14.innerHTML = "";
        });

        if ($isServi($AA09) && !$isServi($AA14)) {
            gouv.api.requestCodeInseeByPostalCode($AA14, $value($AA09))
        }
    }
}

asserts.functions.das2tv_20190101 = function ($elt,
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
    var formOccurences = $$('.formulaire-block.DAS2TV .page-form')
    if (!formOccurences.length) {
        formOccurences = $$('.formulaire-visibility.DAS2TV .page-form');
    }

    for (var occurence = 0; occurence < formOccurences.length; occurence++) {
        /** Variables */
        // A..
        var $AD = $elt('das2tv_20190101_AD', formOccurences[occurence]);
        var $AE02 = $elt('das2tv_20190101_AE02', formOccurences[occurence]);
        var $AE03 = $elt('das2tv_20190101_AE03', formOccurences[occurence]);
        var $AF01 = $elt('das2tv_20190101_AF01', formOccurences[occurence]);
        var $AF02 = $elt('das2tv_20190101_AF02', formOccurences[occurence]);
        var $AF03 = $elt('das2tv_20190101_AF03', formOccurences[occurence]);
        var $AG05 = $elt('das2tv_20190101_AG05', formOccurences[occurence]);
        var $AG06 = $elt('das2tv_20190101_AG06', formOccurences[occurence]);
        var $AG08 = $elt('das2tv_20190101_AG08', formOccurences[occurence]);
        var $AG09 = $elt('das2tv_20190101_AG09', formOccurences[occurence]);
        var $AG14_1 = $elt('das2tv_20190101_AG14_1', formOccurences[occurence]);
        var $AG14_2 = $elt('das2tv_20190101_AG14_2', formOccurences[occurence]);
        var $AG15 = $elt('das2tv_20190101_AG15', formOccurences[occurence]);
        var $AG16 = $elt('das2tv_20190101_AG16', formOccurences[occurence]);
        var $AG17 = $elt('das2tv_20190101_AG17', formOccurences[occurence]);
        var $AH = $elt('das2tv_20190101_AH', formOccurences[occurence]);

        // B..
        var $BB = $elt('das2tv_20190101_BB', formOccurences[occurence]);
        var $BC = $elt('das2tv_20190101_BC', formOccurences[occurence]);
        var $BD = $elt('das2tv_20190101_BD', formOccurences[occurence]);
        var $BE = $elt('das2tv_20190101_BE', formOccurences[occurence]);

        // C..
        var $CA = $elt('das2tv_20190101_CA-1', formOccurences[occurence]);
        var $CB = $elt('das2tv_20190101_CB', formOccurences[occurence]);
        var $CC = $elt('das2tv_20190101_CC', formOccurences[occurence]);
        var $CD = $elt('das2tv_20190101_CD', formOccurences[occurence]);

        var $ZZ1 = $elt('das2tv_20190101_ZZ1', formOccurences[occurence]);

        var $AA01_identif = $('a_identif_hon_20190101_AA01');

        if (!$isServi($AD)) {
            $value($AD, $value($AA01_identif));
        }

        $assert($isServi($AD), 'erreur_required', $AD);
        $assert($isServi($AG05), 'erreur_required', $AG05);
        $assert($isServi($AG08), 'erreur_required', $AG08);
        $assert($isServi($AG09), 'erreur_required', $AG09);
        $assert($isServi($AG15), 'erreur_required', $AG15);
        $assert($isServi($AG16), 'erreur_required', $AG16);

        /** Controls */
        $assert($isServi($AE02) || $isServi($AF02), 'erreur_310_das2', $AF02, $AE02);

        if ($isServi($AE02)) {
            $assert($isServi($AE03), 'erreur_required', $AE03);
        }

        if ($isServi($AF03)) {
            $assert($isServi($AF02), 'erreur_310_das2', $AF03, $AF02);
        }

        if ($isServi($AE02)) {
            $assert($isServi($AE03), 'erreur_311_das2', $AE03);
        }

        if ($float($ZZ1)) {
            $readonly($AG14_2);
            $value($AG14_2, '');
            $AG14_2.removeClassName('has-error')
            if (!$AG14_2.hasClassName('hidden')) {
                $AG14_2.addClassName('hidden');
            }
            $AG14_1.removeClassName('hidden');
            $elt('tooltip-das2tv-zz1', formOccurences[occurence]).addClassName('hidden')
        } else {
            $readonly($AG14_1);
            $value($AG14_1, '');
            $AG14_1.removeClassName('has-error')
            if (!$AG14_1.hasClassName('hidden')) {
                $AG14_1.addClassName('hidden');
            }
            $AG14_2.removeClassName('hidden')
            $elt('tooltip-das2tv-zz1', formOccurences[occurence]).removeClassName('hidden')

            if ($isServi($AG09)) {
                $value($AG14_2, $value($AG09));

                $assert(($value($AG14_2).substr(0, 2) == 99 && $value($AG09).substr(0, 2) == 99), 'erreur_das_etranger', $AG09, $AG14_2);
            }
        }

        if ($float($ZZ1)) {
            $assert($isServi($AG14_1), 'erreur_required', $AG14_1)

            $AG09.observe('keyup', function (event) {
                $AG14_1.innerHTML = "";
            });

            if ($isServi($AG09) && !$isServi($AG14_1)) {
                gouv.api.requestCodeInseeByPostalCode($AG14_1, $value($AG09))
            }
        } else {
            $assert($isServi($AG14_2), 'erreur_required', $AG14_2)
        }

        $readonly($AG15, true);
        if ($isServi($AG08)) {
            $value($AG15, $value($AG08));
        }

        var $rowIndex = 1;

        while ($elt('das2tv_20190101_BA-' + $rowIndex, formOccurences[occurence])) {
            $BA = $elt('das2tv_20190101_BA-' + $rowIndex, formOccurences[occurence]);
            $CA = $elt('das2tv_20190101_CA-' + $rowIndex, formOccurences[occurence]);

            $assert($isServi($BA) || $isServi($BB) || $isServi($BC), 'erreur_316_das2', $BA, $BB, $BC);

            if ($isServi($BA)) {
                $assert($isServi($CA), 'erreur_317_das2', $CA);
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
        }

        if ($isServi($AG09)) {
            $AG09.removeClassName('has-error');
        }
    }
}

asserts.functions.tva3519_20190101 = function ($elt,
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

    var $CB = $elt(NTD.Identif.tField('CB'));
    var $AA1 = $elt('tva3519_20190101_AA1');
    var $AA2 = $elt('tva3519_20190101_AA2');
    var $AA3 = $elt('tva3519_20190101_AA3');
    var $AA4 = $elt('tva3519_20190101_AA4');
    var $DC1 = $elt('tva3519_20190101_DC1');
    var $DC10 = $elt('tva3519_20190101_DC10');
    var $DC2 = $elt('tva3519_20190101_DC2');
    var $DC3 = $elt('tva3519_20190101_DC3');
    var $DC4 = $elt('tva3519_20190101_DC4');
    var $DC5 = $elt('tva3519_20190101_DC5');
    var $DC6 = $elt('tva3519_20190101_DC6');
    var $DC7 = $elt('tva3519_20190101_DC7');
    var $DC8 = $elt('tva3519_20190101_DC8');
    var $DC9 = $elt('tva3519_20190101_DC9');
    var $DD = $elt('tva3519_20190101_DD');
    var $DE = $elt('tva3519_20190101_DE');
    var $DF = $elt('tva3519_20190101_DF');
    var $DG1 = $elt('tva3519_20190101_DG1');
    var $DG2 = $elt('tva3519_20190101_DG2');
    var $DG3 = $elt('tva3519_20190101_DG3');
    var $DG4 = $elt('tva3519_20190101_DG4');
    var $DI = $elt('tva3519_20190101_DI');
    var $DJ = $elt('tva3519_20190101_DJ');
    var $DK = $elt('tva3519_20190101_DK');
    var $DL = $elt('tva3519_20190101_DL');
    var $DM = $elt('tva3519_20190101_DM');
    var $DN = $elt('tva3519_20190101_DN');
    var $FJ = $elt('tva3519_20190101_FJ');
    var $FK = $elt('tva3519_20190101_FK');
    var $FL = $elt('tva3519_20190101_FL');

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
    $assert($isServi($DN) && $float($DN) > 0, 'erreur_219', $DN);
    $assert($float($DN).toString().length <= 9, 'erreur_227', $DN);
    $assert($isServi($FK) || $isServi($FL), 'erreur_221', $FK, $FL);
    $assert(!($isServi($DJ) && !$isServi($DM)), 'erreur_223', $DM);
    $assert(!($isServi($DI) && !$isServi($FJ)), 'erreur_148', $FJ);
    $assert(!($isServi($DI) &&
            !$isServi($AA1) &&
            !$isServi($AA2) &&
            !$isServi($AA3) &&
            !$isServi($AA4) &&
            $isServi($DL)),
        'erreur_230',
        $AA1, $AA2, $AA3, $AA4);
    $assert(!($isServi($DI) &&
            !$isServi($AA1) &&
            !$isServi($AA2) &&
            !$isServi($AA3) &&
            !$isServi($AA4) &&
            !$isServi($DL)),
        'Si "Premiere demande" est coché Alors "Référence bancaire" et "Création le" doivent être renseignés.',
        $AA1, $AA2, $AA3, $AA4, $DL);
    $assert(function () {
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


    var $assert_DC1_DC4 = ($isServi($DC1) || $isServi($DC4)) &&
        (!$isServi($DC2) || !$isServi($DC3) || !$isServi($DC6) || !$isServi($DC7) || !$isServi($DC8) || !$isServi($DC9) || !$isServi($DC10));

    var $assert_DC1_DC4_message = 'Attention ! Veuillez renseigner le cadre "Adresse de correspondance", ' +
        'si celle-ci est différente de celle de l’établissement principal ou si la demande est effectuée par un représentant fiscal ou ' +
        'le mandataire-liquidateur de l’entreprise';

    $assert(!($assert_DC1_DC4),
        $assert_DC1_DC4_message,
        $DC1, $DC2, $DC3, $DC4, $DC6, $DC7, $DC8, $DC9, $DC10);
};

asserts.functions.tva3310ca3g_20190101 = function ($elt,
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
    var $BA = $elt('tva3310ca3g_20190101_BA');
    var $BB = $elt('tva3310ca3g_20190101_BB');
    var $BC = $elt('tva3310ca3g_20190101_BC');
    var $DA = $elt('tva3310ca3g_20190101_DA');
    var $DB = $elt('tva3310ca3g_20190101_DB');
    var $DC = $elt('tva3310ca3g_20190101_DC');
    var $DD = $elt('tva3310ca3g_20190101_DD');
    var $EA = $elt('tva3310ca3g_20190101_EA');
    var $EB = $elt('tva3310ca3g_20190101_EB');
    var $EC = $elt('tva3310ca3g_20190101_EC');
    var $FA = $elt('tva3310ca3g_20190101_FA');
    var $FB = $elt('tva3310ca3g_20190101_FB');
    var $FE = $elt('tva3310ca3g_20190101_FE');
    var $GA = $elt('tva3310ca3g_20190101_GA');
    var $GB = $elt('tva3310ca3g_20190101_GB');
    var $GD = $elt('tva3310ca3g_20190101_GD');
    var $GH = $elt('tva3310ca3g_20190101_GH');
    var $GJ = $elt('tva3310ca3g_20190101_GJ');
    var $GK = $elt('tva3310ca3g_20190101_GK');
    var $GL = $elt('tva3310ca3g_20190101_GL');
    var $GM = $elt('tva3310ca3g_20190101_GM');
    var $GO = $elt('tva3310ca3g_20190101_GO');
    var $GP = $elt('tva3310ca3g_20190101_GP');
    var $GQ = $elt('tva3310ca3g_20190101_GQ');
    var $GR = $elt('tva3310ca3g_20190101_GR');
    var $GS = $elt('tva3310ca3g_20190101_GS');
    var $GT = $elt('tva3310ca3g_20190101_GT');
    var $GU = $elt('tva3310ca3g_20190101_GU');
    var $GV = $elt('tva3310ca3g_20190101_GV');
    var $GX = $elt('tva3310ca3g_20190101_GX');
    var $GZ = $elt('tva3310ca3g_20190101_GZ');
    var $HE = $elt('tva3310ca3g_20190101_HE');
    var $HK = $elt('tva3310ca3g_20190101_HK');
    var $HL = $elt('tva3310ca3g_20190101_HL');
    var $HN = $elt('tva3310ca3g_20190101_HN');
    var $HO = $elt('tva3310ca3g_20190101_HO');
    var $HP = $elt('tva3310ca3g_20190101_HP');
    var $HQ = $elt('tva3310ca3g_20190101_HQ');
    var $HR = $elt('tva3310ca3g_20190101_HR');
    var $HS = $elt('tva3310ca3g_20190101_HS');
    var $HT = $elt('tva3310ca3g_20190101_HT');
    var $HU = $elt('tva3310ca3g_20190101_HU');
    var $KF = $elt('tva3310ca3g_20190101_KF');
    var $KH = $elt('tva3310ca3g_20190101_KH');
    var $KJ = $elt('tva3310ca3g_20190101_KJ');
    var $KK = $elt('tva3310ca3g_20190101_KK');
    var $KL = $elt('tva3310ca3g_20190101_KL');
    var $KM = $elt('tva3310ca3g_20190101_KM');
    var $KN = $elt('tva3310ca3g_20190101_KN');
    var $KR = $elt('tva3310ca3g_20190101_KR');
    var $KS = $elt('tva3310ca3g_20190101_KS');
    var $KT = $elt('tva3310ca3g_20190101_KT');
    var $KU = $elt('tva3310ca3g_20190101_KU');
    var $KV = $elt('tva3310ca3g_20190101_KV');
    var $KW = $elt('tva3310ca3g_20190101_KW');
    var $KX = $elt('tva3310ca3g_20190101_KX');
    var $KY = $elt('tva3310ca3g_20190101_KY');
    var $KZ = $elt('tva3310ca3g_20190101_KZ');
    var $LA = $elt('tva3310ca3g_20190101_LA');
    var $LB = $elt('tva3310ca3g_20190101_LB');
    var $LC = $elt('tva3310ca3g_20190101_LC');
    var $LD = $elt('tva3310ca3g_20190101_LD');
    var $LF = $elt('tva3310ca3g_20190101_LF');
    var $LG = $elt('tva3310ca3g_20190101_LG');
    var $MA = $elt('tva3310ca3g_20190101_MA');
    var $MB = $elt('tva3310ca3g_20190101_MB');
    var $MC = $elt('tva3310ca3g_20190101_MC');
    var $MD = $elt('tva3310ca3g_20190101_MD');
    var $ME = $elt('tva3310ca3g_20190101_ME');
    var $MF = $elt('tva3310ca3g_20190101_MF');
    var $MG = $elt('tva3310ca3g_20190101_MG');
    var $MH = $elt('tva3310ca3g_20190101_MH');
    var $MJ = $elt('tva3310ca3g_20190101_MJ');
    var $MK = $elt('tva3310ca3g_20190101_MK');
    var $ML = $elt('tva3310ca3g_20190101_ML');
    var $MN = $elt('tva3310ca3g_20190101_MN');
    var $MP = $elt('tva3310ca3g_20190101_MP');
    var $MS = $elt('tva3310ca3g_20190101_MS');
    var $NA = $elt('tva3310ca3g_20190101_NA');
    var $NB = $elt('tva3310ca3g_20190101_NB');
    var $ND = $elt('tva3310ca3g_20190101_ND');
    var $NE = $elt('tva3310ca3g_20190101_NE');
    var $NF = $elt('tva3310ca3g_20190101_NF');
    var $NG = $elt('tva3310ca3g_20190101_NG');
    var $NH = $elt('tva3310ca3g_20190101_NH');
    var $NK = $elt('tva3310ca3g_20190101_NK');
    var $NM = $elt('tva3310ca3g_20190101_NM');
    var $NQ = $elt('tva3310ca3g_20190101_NQ');
    var $NU = $elt('tva3310ca3g_20190101_NU');
    var $NV = $elt('tva3310ca3g_20190101_NV');
    var $NX = $elt('tva3310ca3g_20190101_NX');
    var $NY = $elt('tva3310ca3g_20190101_NY');
    var $NZ = $elt('tva3310ca3g_20190101_NZ');
    var $PC = $elt('tva3310ca3g_20190101_PC');

    $readonly($DC, true);
    $readonly($EA, true);
    $readonly($EC, true);
    $readonly($FA, true);
    $readonly($FE, true);
    $readonly($HK, true);
    $readonly($FB, true);
    $addition($DC, $DA, $DB);
    $soustraction($EA, $DC, $KR, $DD);
    $soustraction($EC, $EA, $EB);
    if ($float($KR) - $float($DC) + $float($DD) >= 0) {
        var $result = $float($KR) - $float($DC) + $float($DD);
        $value($FA, $result);
    }
    $addition($FE, $FA, $FB);
    var $total = 0;
    $rowIndex = 1;
    while ($elt('tva3310ca3g_20190101_NN/' + $rowIndex)) {
        var $NP = $elt('tva3310ca3g_20190101_NP/' + $rowIndex);
        var $NN = $elt('tva3310ca3g_20190101_NN/' + $rowIndex);

        $assert(!($XOR($isServi($NP), $isServi($NN)) || $float($NN) == 0),
            'erreur_212', $NP, $NN);

        if ($isServi($NN)) {
            $total += $float($NN);
        }

        $rowIndex++;
    }
    $value($NQ, $total);

    $total = 0;
    $rowIndex = 1;
    while ($elt('tva3310ca3g_20190101_PB/' + $rowIndex)) {
        var $PB = $elt('tva3310ca3g_20190101_PB/' + $rowIndex);
        var $PA = $elt('tva3310ca3g_20190101_PA/' + $rowIndex);

        $assert(!($XOR($isServi($PB), $isServi($PA)) || $float($PA) == 0),
            'erreur_233_tva_ca3g', $PB, $PA);

        if ($isServi($PA)) {
            $total += $float($PA);
        }

        $rowIndex++;
    }
    $value($PC, $total);

    $addition($HK,
        $GA, $GB, $GD, $GH, $GJ, $GK, $GL, $GM, $GO, $GP, $GQ, $GR, $GS, $GT, $GU, $GV, $GX, $GZ,
        $HL, $HN, $HO, $HP, $HQ, $HR, $HS, $HT, $HU,
        $KJ, $KK, $KL, $KM, $KS, $KT, $KU, $KV, $KW, $KX, $KY, $KZ,
        $LG,
        $MA, $MB, $MC, $MD, $ME, $MF, $MG, $MH, $MJ, $MK, $ML, $MN, $MP, $MS,
        $NA, $NB, $ND, $NE, $NF, $NG, $NH, $NK, $NM, $NQ, $NU, $NV, $NX, $NY, $NZ, $PC);

    $value($FB, $value($HK));
    NTD.Identif.t("hidePaiement", []);
    if ($isServi($FE) && $float($FE) > 0) {
        NTD.Identif.t("showPaiement", [$float($FE)]);
    }
    $assert(!($isServi($BC) && !$isServi($BA)),
        'erreur_128', $BA, $BC);
    $assert(!($isServi($EB) && $isServi($EA) && !($float($EB) <= $float($EA))),
        'erreur_131', $EA, $EB);
    if (!$KF.checked) {
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
                !$isServi($ND) &&
                !$isServi($NE) &&
                !$isServi($NF) &&
                !$isServi($NG) &&
                !$isServi($NH) &&
                !$isServi($NK) &&
                !$isServi($NM) &&
                !$isServi($NN) &&
                !$isServi($NU) &&
                !$isServi($NV) &&
                !$isServi($NX) &&
                !$isServi($NY) &&
                !$isServi($NZ)),
            "erreur_049",
            $DA, $DB, $DC, $DD, $EA, $EB, $EC, $FA, $FB, $FE, $GA, $GB, $HN, $GF, $GH, $GJ, $GK, $GL, $GM, $GO, $GP, $GQ, $GR, $GS, $GT, $GU, $GV, $GX, $GZ,
            $HO, $HP, $HL, $HQ, $HR, $HS, $HU, $LG, $KS, $KT, $KJ, $KK, $KL, $KM, $KR, $KU, $KV, $KW, $KX, $KY, $KZ,
            $MA, $MB, $MC, $MD, $ME, $MF, $MG, $MH, $MJ, $MK, $ML, $MN, $MP, $MS,
            $NA, $NB, $ND, $NE, $NF, $NG, $NH, $NK, $NM, $NN, $NU, $NV, $NX, $NY, $NZ);
    }
};

asserts.functions.tva3310ca3_20190101 = function ($elt,
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

    var $BA = $elt('tva3310ca3_20190101_BA');
    var $BB = $elt('tva3310ca3_20190101_BB');
    var $BC = $elt('tva3310ca3_20190101_BC');

    var $CA = $elt('tva3310ca3_20190101_CA');
    var $CB = $elt('tva3310ca3_20190101_CB');
    var $CC = $elt('tva3310ca3_20190101_CC');
    var $CD = $elt('tva3310ca3_20190101_CD');
    var $CE = $elt('tva3310ca3_20190101_CE');
    var $CF = $elt('tva3310ca3_20190101_CF');
    var $CG = $elt('tva3310ca3_20190101_CG');

    var $DA = $elt('tva3310ca3_20190101_DA');
    var $DB = $elt('tva3310ca3_20190101_DB');
    var $DC = $elt('tva3310ca3_20190101_DC');
    var $DD = $elt('tva3310ca3_20190101_DD');
    var $DE = $elt('tva3310ca3_20190101_DE');
    var $DF = $elt('tva3310ca3_20190101_DF');
    var $DG = $elt('tva3310ca3_20190101_DG');
    var $DH = $elt('tva3310ca3_20190101_DH');

    var $FB = $elt('tva3310ca3_20190101_FB');
    var $FC = $elt('tva3310ca3_20190101_FC');
    var $FD = $elt('tva3310ca3_20190101_FD');
    var $FG = $elt('tva3310ca3_20190101_FG');
    var $FH = $elt('tva3310ca3_20190101_FH');
    var $FJ = $elt('tva3310ca3_20190101_FJ');
    var $FK = $elt('tva3310ca3_20190101_FK');
    var $FM = $elt('tva3310ca3_20190101_FM');
    var $FN = $elt('tva3310ca3_20190101_FN');
    var $FP = $elt('tva3310ca3_20190101_FP');
    var $FR = $elt('tva3310ca3_20190101_FR');

    var $GB = $elt('tva3310ca3_20190101_GB');
    var $GC = $elt('tva3310ca3_20190101_GC');
    var $GD = $elt('tva3310ca3_20190101_GD');
    var $GG = $elt('tva3310ca3_20190101_GG');
    var $GH = $elt('tva3310ca3_20190101_GH');
    var $GJ = $elt('tva3310ca3_20190101_GJ');
    var $GK = $elt('tva3310ca3_20190101_GK');
    var $GM = $elt('tva3310ca3_20190101_GM');
    var $GN = $elt('tva3310ca3_20190101_GN');
    var $GP = $elt('tva3310ca3_20190101_GP');
    var $GR = $elt('tva3310ca3_20190101_GR');

    var $HA = $elt('tva3310ca3_20190101_HA');
    var $HB = $elt('tva3310ca3_20190101_HB');
    var $HC = $elt('tva3310ca3_20190101_HC');
    var $HD = $elt('tva3310ca3_20190101_HD');
    var $HE = $elt('tva3310ca3_20190101_HE');
    var $HG = $elt('tva3310ca3_20190101_HG');
    var $HH = $elt('tva3310ca3_20190101_HH');
    var $HJ = $elt('tva3310ca3_20190101_HJ');

    var $KA = $elt('tva3310ca3_20190101_KA');
    var $KB = $elt('tva3310ca3_20190101_KB');
    var $KE = $elt('tva3310ca3_20190101_KE');
    var $KF = $elt('tva3310ca3_20190101_KF');
    var $HF = $elt('tva3310ca3_20190101_HF');
    var $KH = $elt('tva3310ca3_20190101_KH');
    var $KJ = $elt('tva3310ca3_20190101_KJ');
    var $KL = $elt('tva3310ca3_20190101_KL');
    var $KR = $elt('tva3310ca3_20190101_KR');
    var $KS = $elt('tva3310ca3_20190101_KS');
    var $KT = $elt('tva3310ca3_20190101_KT');
    var $KU = $elt('tva3310ca3_20190101_KU');

    var $JA = $elt('tva3310ca3_20190101_JA');
    var $JB = $elt('tva3310ca3_20190101_JB');
    var $JC = $elt('tva3310ca3_20190101_JC');

    // ----

    /* tva3515sd */

    var $CA_sd = $elt('tva3515sd_20190101_CA');
    var $CB_sd = $elt('tva3515sd_20190101_CB');
    var $BC_sd = $elt('tva3515sd_20190101_BC');
    var $BD_sd = $elt('tva3515sd_20190101_BD');

    var $BE_sd = $elt('tva3515sd_20190101_BE');
    var $BF_sd = $elt('tva3515sd_20190101_BF');
    var $DD_sd = $elt('tva3515sd_20190101_DD');
    var $GD_sd = $elt('tva3515sd_20190101_DD');

    var BEValue = $float($KA);
    $value($BE_sd, (isNaN(BEValue) ? 0 : BEValue));

    var KBValue = $float($KB);
    $value($BF_sd, (isNaN(KBValue) ? 0 : KBValue));

    if ($isServi($GD_sd) && $float($GD_sd) > 0) {
        $assert(!($float($KS) >= $float($GD_sd)), 'erreur_sd', $KS);
    }

    asserts.run('tva3515sd_20190101');

    // ----

    $readonly($FG, true);
    $readonly($FH, true);
    $readonly($FJ, true);
    $readonly($FK, true);


    var editableFields = [$CA, $CB, $CC, $CD, $CE, $CF, $CG, $DA, $DB, $DC, $DD,
        $DE, $DF, $DG, $DH, $FB, $FC, $FD, $FM, $FN,
        $FP, $FR, $GB, $GC, $GD, $GG, $GH, $GJ, $GK, $GM, $GN, $GP,
        $GR, $HA, $HB, $HC, $HD, $HG, $HH, $KA, $KB, $KE, $KJ,
        $HF, $KH, $KL, $KR, $KS, $KT, $KU, $JA, $JB, $JC
    ];
    if ($isServi($KF)) {
        for (var i = 0; i < editableFields.length; i++) {
            $readonly(editableFields[i], true).setValue('');
        }
    } else {
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
    [$GP, $GB, $FH, $GM, $GN, $FK, $GC, $GD, $GG, $GR, $KS].each(function (elt) {
        if ($float(elt) > 0) {
            GHValue += $float(elt);
        }
    });
    $value($GH, GHValue);

    $readonly($HG, true);
    var HGValue = 0;
    [$HA, $HB, $HC, $HD, $KU].each(function (elt) {
        if ($float(elt) > 0) {
            HGValue += $float(elt);
        }
    });
    $value($HG, HGValue);

    $readonly($JA, true);
    var JAValue = ($isServi($HG) && $isServi($GH)) && ($float($HG) <= $float($GH)) ? 0 : $float($HG) - $float($GH);
    $value($JA, Math.max(0, JAValue));

    $readonly($JC, true);
    var JCValue = ($isServi($JA) ? $float($JA) : 0);
    JCValue -= ($isServi($JB) ? $float($JB) : 0);
    JCValue -= ($isServi($KJ) ? $float($KJ) : 0);
    $value($JC, JCValue);

    $readonly($KA, true);
    var KAValue = ($isServi($HG) && $isServi($GH)) && ($float($HG) <= $float($GH)) ? $float($GH) - $float($HG) : 0;
    $value($KA, Math.max(0, KAValue));

    $readonly($KE, true);
    var KEValue = ($isServi($KA) ? $float($KA) : 0) + ($isServi($KB) ? $float($KB) : 0) - ($isServi($KL) ? $float($KL) : 0);
    $value($KE, KEValue);
    NTD.Identif.p("hidePaiement", []);
    if (KEValue > 0) {
        NTD.Identif.p("showPaiement", [KEValue]);
    }

    $assert(!((($isServi($FD) && $float($FD) > 0) || ($isServi($GD) && $float($GD) > 0)) && !$isServi($elt('tva3310a_20190101_HB'))),
        'erreur_013',
        $GD, $FD);
    $assert(!($isServi($CC) && $isServi($CD) && $float($CD) > 0 && !($float($CD) <= $float($CC))),
        'erreur_136',
        $CC, $CD);
    $assert(!($isServi($FC) && $float($FC) > 0 && !($isServi($GC) && $float($GC) > 0)), 'erreur_111', $FC, $GC);
    $assert(!($isServi($FC) && $isServi($GC) && !(($float($FC) * 0.021) <= $float($GC) && $float($GC) <= ($float($FC) * 0.206))),
        'erreur_117', $FC, $GC);
    $assert((
        ($isServi($CA) ? $float($CA) : 0) +
        ($isServi($CB) ? $float($CB) : 0) +
        ($isServi($KH) ? $float($KH) : 0) +
        ($isServi($KR) ? $float($KR) : 0) +
        ($isServi($CC) ? $float($CC) : 0) +
        ($isServi($CF) ? $float($CF) : 0) +
        ($isServi($CG) ? $float($CG) : 0)
    ) == (
        ($isServi($FP) ? $float($FP) : 0) +
        ($isServi($FB) ? $float($FB) : 0) +
        ($isServi($FR) ? $float($FR) : 0) +
        ($isServi($FM) ? $float($FM) : 0) +
        ($isServi($FN) ? $float($FN) : 0) +
        ($isServi($FC) ? $float($FC) : 0) +
        ($isServi($FD) ? $float($FD) : 0)
    ), 'erreur_224', $CA, $CB, $KH, $KR, $CC, $CF, $CG, $FP, $FB, $FR, $FM, $FN, $FC, $FD);

    $assert(!($isServi($CC) && $isServi($GJ) && !(Math.round($float($CC) * 0.021) <= $float($GJ) && $float($GJ) <= Math.round($float($CC) * 0.20))),
        'erreur_117', $CC, $GJ);

    $assert(!($isServi($KR) && $isServi($KT) && !(Math.round($float($KR) * 0.021) <= $float($KT) && $float($KT) <= Math.round($float($KR) * 0.20))),
        'erreur_117', $KR, $KT);

    $assert(!($isServi($GH) && $isServi($GJ) && $isServi($GK) && $isServi($KT) && !($float($GJ) + $float($GK) + $float($KT) <= $float($GH))),
        'erreur_121', $GH, $GJ, $GK, $KT);

    $assert(!(!$isServi($GJ) && $isServi($CC)), 'erreur_038', $GJ, $CC);
    $assert(!($isServi($HH) && $float($HH) > 0 && !($isServi($CE) && $float($CE) > 0)), 'erreur_140', $HH, $CE);
    $assert(!($isServi($HH) && $isServi($HC) && !($float($HH) <= $float($HC))), 'erreur_051', $HH, $HC);
    $assert(!($isServi($HE) && !(0 < $float($HE) && $float($HE) < 100)), 'erreur_116', $HE);
    $assert(!($isServi($HF) && $isServi($HG) && !($float($HF) <= $float($HG))), 'erreur_205', $HF, $HG);
    $assert(!($isServi($JB) && $isServi($JA) && $isServi($KJ) && !($float($JB) <= $float($JA) - $float($KJ))), 'erreur_131', $JA, $JB, $KJ);
    $assert(!($isServi($KB) && $float($KB) > 0 && !$isServi($elt('tva3310a_20190101_HB'))),
        'erreur_013',
        $KB);

    var $GH_control_value = $float($GJ) + $float($GK) + $float($KT);
    $assert(!($GH_control_value > $float($GH)),
        'erreur_121',
        $GJ, $GK, $KT);

    $assert(!($isServi($BC) &&
            !$isServi($BA)),
        'erreur_128', $BC, $BA);

    $assert(
        !($isServi($KF) &&
            (
                ($isServi($CA) && $float($CA) > 0) ||
                ($isServi($CB) && $float($CB) > 0) ||
                ($isServi($CC) && $float($CC) > 0) ||
                ($isServi($CD) && $float($CD) > 0) ||
                ($isServi($CE) && $float($CE) > 0) ||
                ($isServi($CF) && $float($CF) > 0) ||
                ($isServi($CG) && $float($CG) > 0) ||
                ($isServi($DA) && $float($DA) > 0) ||
                ($isServi($DB) && $float($DB) > 0) ||
                ($isServi($DC) && $float($DC) > 0) ||
                ($isServi($DD) && $float($DD) > 0) ||
                ($isServi($DE) && $float($DE) > 0) ||
                ($isServi($DF) && $float($DF) > 0) ||
                ($isServi($DG) && $float($DG) > 0) ||
                ($isServi($DH) && $float($DH) > 0) ||
                ($isServi($FB) && $float($FB) > 0) ||
                ($isServi($FC) && $float($FC) > 0) ||
                ($isServi($FD) && $float($FD) > 0) ||
                ($isServi($FM) && $float($FM) > 0) ||
                ($isServi($FN) && $float($FN) > 0) ||
                ($isServi($FP) && $float($FP) > 0) ||
                ($isServi($FR) && $float($FR) > 0) ||
                ($isServi($GB) && $float($GB) > 0) ||
                ($isServi($GC) && $float($GC) > 0) ||
                ($isServi($GD) && $float($GD) > 0) ||
                ($isServi($GG) && $float($GG) > 0) ||
                ($isServi($GH) && $float($GH) > 0) ||
                ($isServi($GJ) && $float($GJ) > 0) ||
                ($isServi($GK) && $float($GK) > 0) ||
                ($isServi($GM) && $float($GM) > 0) ||
                ($isServi($GN) && $float($GN) > 0) ||
                ($isServi($GP) && $float($GP) > 0) ||
                ($isServi($GR) && $float($GR) > 0) ||
                ($isServi($HA) && $float($HA) > 0) ||
                ($isServi($HB) && $float($HB) > 0) ||
                ($isServi($HC) && $float($HC) > 0) ||
                ($isServi($HD) && $float($HD) > 0) ||
                ($isServi($HG) && $float($HG) > 0) ||
                ($isServi($HH) && $float($HH) > 0) ||
                ($isServi($KA) && $float($KA) > 0) ||
                ($isServi($KB) && $float($KB) > 0) ||
                ($isServi($KE) && $float($KE) > 0) ||
                ($isServi($HF) && $float($HF) > 0) ||
                ($isServi($KH) && $float($KH) > 0) ||
                ($isServi($KJ) && $float($KJ) > 0) ||
                ($isServi($KL) && $float($KL) > 0) ||
                ($isServi($KR) && $float($KR) > 0) ||
                ($isServi($KS) && $float($KS) > 0) ||
                ($isServi($KT) && $float($KT) > 0) ||
                ($isServi($KU) && $float($KU) > 0) ||
                ($isServi($JA) && $float($JA) > 0) ||
                ($isServi($JB) && $float($JB) > 0) ||
                ($isServi($JC) && $float($JC) > 0)
            )
        ), 'erreur_042',
        $KF, $CA, $CB, $CC, $CD, $CE, $CF, $CG, $DA, $DB, $DC, $DD,
        $DE, $DF, $DG, $DH, $FB, $FC, $FD, $FM, $FN,
        $FP, $FR, $GB, $GC, $GD, $GG, $GH, $GJ, $GK, $GM, $GN, $GP,
        $GR, $HA, $HB, $HC, $HD, $HG, $HH, $KA, $KB, $KE, $KJ,
        $HF, $KH, $KL, $KR, $KS, $KT, $KU, $JA, $JB, $JC);

    $assert(!($isServi($CC) && $float($CC) > 0 && (!$isServi($GJ) || !$float($GJ) > 0)), 'erreur_042', $GJ, $CC);

    for (var i = 0; i < editableFields.length; i++) {
        //$assert(!(!$isServi($KF) && !($isServi(editableFields[i]) && $float(editableFields[i]) >= 0)), 'erreur_049', $KF, editableFields[i]);
    }

};


asserts.functions.tva3310ter_20190101 = function ($elt,
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

    var $rowIndex = 0;

    var $AA = $elt('tva3310ter_20190101_AA');
    var $AB = $elt('tva3310ter_20190101_AB');
    var $AC = $elt('tva3310ter_20190101_AC');
    var $DL = $elt('tva3310ter_20190101_DL');
    var $EL = $elt('tva3310ter_20190101_EL');
    var $FL = $elt('tva3310ter_20190101_FL');
    var $GL = $elt('tva3310ter_20190101_GL');
    var $HL = $elt('tva3310ter_20190101_HL');
    var $JL = $elt('tva3310ter_20190101_JL');
    var $KL = $elt('tva3310ter_20190101_KL');
    var $LL = $elt('tva3310ter_20190101_LL');
    var $ML = $elt('tva3310ter_20190101_ML');
    var $PL = $elt('tva3310ter_20190101_PL');
    var $QL = $elt('tva3310ter_20190101_QL');
    var $RL = $elt('tva3310ter_20190101_RL');
    var $QM = $elt('tva3310ter_20190101_QM');
    var $RM = $elt('tva3310ter_20190101_RM');

    // ---

    $rowIndex = 1;
    while ($elt('tva3310ter_20190101_BM/' + $rowIndex)) {
        var $BM = $elt('tva3310ter_20190101_BM/' + $rowIndex);
        var $CM = $elt('tva3310ter_20190101_CM/' + $rowIndex);

        $assert(!($isServi($BM) && !($isServi($CM) && 0 <= $float($CM) && $float($CM) <= 100)),
            'erreur_116', $BM, $CM);

        $rowIndex++;
    }

    // --- TVA BRUTE

    var $DM_sum = 0;
    var $EM_sum = 0;
    var $FM_sum = 0;

    $rowIndex = 1;
    while ($elt('tva3310ter_20190101_DM/' + $rowIndex)) {
        var $DM = $elt('tva3310ter_20190101_DM/' + $rowIndex);
        var $EM = $elt('tva3310ter_20190101_EM/' + $rowIndex);
        var $FM = $elt('tva3310ter_20190101_FM/' + $rowIndex);

        $addition($FM, $DM, $EM);

        $DM_sum += $float($DM) ? $float($DM) : 0;
        $EM_sum += $float($EM) ? $float($EM) : 0;
        $FM_sum += $float($FM) ? $float($FM) : 0;

        $rowIndex++;
    }

    $value($DL, $DM_sum);
    $value($EL, $EM_sum);
    $value($FL, $FM_sum);

    // --- DÉTERMINATION DE LA TVA DÉDUCTIBLE

    var $GM_sum = 0;
    var $HM_sum = 0;
    var $JM_sum = 0;
    var $KM_sum = 0;
    var $LM_sum = 0;
    var $MM_sum = 0;

    $rowIndex = 1;
    while ($elt('tva3310ter_20190101_GM/' + $rowIndex)) {
        var $GM = $elt('tva3310ter_20190101_GM/' + $rowIndex);
        var $HM = $elt('tva3310ter_20190101_HM/' + $rowIndex);
        var $JM = $elt('tva3310ter_20190101_JM/' + $rowIndex);
        var $KM = $elt('tva3310ter_20190101_KM/' + $rowIndex);
        var $LM = $elt('tva3310ter_20190101_LM/' + $rowIndex);
        var $MM = $elt('tva3310ter_20190101_MM/' + $rowIndex);

        $addition($JM, $GM, $HM);
        $addition($MM, $KM, $LM);

        $GM_sum += $float($GM) ? $float($GM) : 0;
        $HM_sum += $float($HM) ? $float($HM) : 0;
        $JM_sum += $float($JM) ? $float($JM) : 0;
        $KM_sum += $float($KM) ? $float($KM) : 0;
        $LM_sum += $float($LM) ? $float($LM) : 0;
        $MM_sum += $float($MM) ? $float($MM) : 0;

        $rowIndex++;
    }

    $value($GL, $GM_sum);
    $value($HL, $HM_sum);
    $value($JL, $JM_sum);
    $value($KL, $KM_sum);
    $value($LL, $LM_sum);
    $value($ML, $MM_sum);

    // ---

    var $NM_sum = 0;
    var $PM_sum = 0;
    var $QN_sum = 0;
    var $RN_sum = 0;

    $rowIndex = 1;
    while ($elt('tva3310ter_20190101_NM/' + $rowIndex)) {
        var $NM = $elt('tva3310ter_20190101_NM/' + $rowIndex);
        var $PM = $elt('tva3310ter_20190101_PM/' + $rowIndex);
        var $QN = $elt('tva3310ter_20190101_QN/' + $rowIndex);
        var $RN = $elt('tva3310ter_20190101_RN/' + $rowIndex);

        var $JM = $elt('tva3310ter_20190101_JM/' + $rowIndex);
        var $MM = $elt('tva3310ter_20190101_MM/' + $rowIndex);

        var $FM = $elt('tva3310ter_20190101_FM/' + $rowIndex);

        $addition($PM, $JM, $MM, $NM);
        $soustraction($QN, $FM, $PM);
        $soustraction($RN, $PM, $FM);

        $NM_sum += $float($NM) ? $float($NM) : 0;
        $PM_sum += $float($PM) ? $float($PM) : 0;
        $QN_sum += $float($QN) ? $float($QN) : 0;
        $RN_sum += $float($RN) ? $float($RN) : 0;

        $rowIndex++;
    }

    $value($PL, $PM_sum);
    $value($QL, $QN_sum);
    $value($RL, $RN_sum);

    $soustraction($QM, $QL, $RL);
    $soustraction($RM, $RL, $QL);

    $assert(!($isServi($AC) &&
            !$isServi($AA)),
        'erreur_128', $AC, $AA);

    $assert($isServi($AB) && !(($isServi($QM) || $isServi($RM)) && !(0 < $float($AB) && $float($AB) <= 100)),
        'erreur_222', $AB);
};


asserts.functions.tva3515sd_20190101 = function ($elt,
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

    var $AA = $elt('tva3515sd_20190101_AA');
    var $AB = $elt('tva3515sd_20190101_AB');
    var $BB = $elt('tva3515sd_20190101_BB');
    var $BC = $elt('tva3515sd_20190101_BC');
    var $BD = $elt('tva3515sd_20190101_BD');
    var $BE = $elt('tva3515sd_20190101_BE');
    var $BF = $elt('tva3515sd_20190101_BF');
    var $CA = $elt('tva3515sd_20190101_CA');
    var $CB = $elt('tva3515sd_20190101_CB');
    var $DA = $elt('tva3515sd_20190101_DA');
    var $DB = $elt('tva3515sd_20190101_DB');
    var $DC = $elt('tva3515sd_20190101_DC');
    var $DD = $elt('tva3515sd_20190101_DD');
    var $EA = $elt('tva3515sd_20190101_EA');
    var $EB = $elt('tva3515sd_20190101_EB');


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
    } else if ($float($BE) + $float($BF) < $float($BB)) {
        $value($BC, 0);
    }

    if ($float($BB) > $float($BE) + $float($BF)) {
        $value($BD, ($float($BB) - ($float($BE) + $float($BF))));
    } else {
        $value($BD, 0);
    }

    $value($CA, $float($BD));


    $value($CB, $float($CA) + $float($BC) - $float($BD));

    $value($DA, $float($CB));
    $value($DB, $float($BE) + $float($BF));


    if ($float($CB) >= ($float($BE) + $float($BF))) {
        $value($DC, $float($CB) - ($float($BE) + $float($BF)));
        $value($DD, 0);
    } else {
        $value($DC, 0);
        $value($DD, ($float($BE) + $float($BF)) - $float($CB));
    }

    $assert(!($isServi($CA) && $isServi($BD) && !($float($CA) >= $float($BD))),
        'erreur_115', $CA, $BD);

    $assert(!($isServi($EB) &&
            !$isServi($EA)),
        'erreur_128', $EA, $EB);

    if (!isNaN($float($elt('tva3310ca3_20190101_KB')))) {
        $value($BF, $float($elt('tva3310ca3_20190101_KB')));
    } else {
        $value($BF, 0);
    }

    if (!isNaN($float($elt('tva3310ca3_20190101_KA')))) {
        $value($BE, $float($elt('tva3310ca3_20190101_KA')));
    } else {
        $value($BE, 0);
    }

};


asserts.functions.tva3310a_20190101 = function ($elt,
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

    var $BA = $elt('tva3310a_20190101_BA');
    var $BB = $elt('tva3310a_20190101_BB');
    var $BC = $elt('tva3310a_20190101_BC');
    var $BE = $elt('tva3310a_20190101_BE');
    var $BF = $elt('tva3310a_20190101_BF');
    var $BK = $elt('tva3310a_20190101_BK');
    var $BM = $elt('tva3310a_20190101_BM');
    var $BN = $elt('tva3310a_20190101_BN');
    var $BP = $elt('tva3310a_20190101_BP');
    var $BQ = $elt('tva3310a_20190101_BQ');
    var $BR = $elt('tva3310a_20190101_BR');
    var $BS = $elt('tva3310a_20190101_BS');
    var $CA = $elt('tva3310a_20190101_CA');
    var $CB = $elt('tva3310a_20190101_CB');
    var $CC = $elt('tva3310a_20190101_CC');
    var $CE = $elt('tva3310a_20190101_CE');
    var $CF = $elt('tva3310a_20190101_CF');
    var $CK = $elt('tva3310a_20190101_CK');
    var $CM = $elt('tva3310a_20190101_CM');
    var $CN = $elt('tva3310a_20190101_CN');
    var $CP = $elt('tva3310a_20190101_CP');
    var $CQ = $elt('tva3310a_20190101_CQ');
    var $CR = $elt('tva3310a_20190101_CR');
    var $CS = $elt('tva3310a_20190101_CS');
    var $DA = $elt('tva3310a_20190101_DA');
    var $DB = $elt('tva3310a_20190101_DB');
    var $FA = $elt('tva3310a_20190101_FA');
    var $FB = $elt('tva3310a_20190101_FB');
    var $FG = $elt('tva3310a_20190101_FG');
    var $FJ = $elt('tva3310a_20190101_FJ');
    var $FR = $elt('tva3310a_20190101_FR');
    var $FT = $elt('tva3310a_20190101_FT');
    var $FV = $elt('tva3310a_20190101_FV');
    var $HB = $elt('tva3310a_20190101_HB');
    var $HE = $elt('tva3310a_20190101_HE');
    var $HF = $elt('tva3310a_20190101_HF');
    var $HI = $elt('tva3310a_20190101_HI');
    var $JA = $elt('tva3310a_20190101_JA');
    var $JB = $elt('tva3310a_20190101_JB');
    var $JC = $elt('tva3310a_20190101_JC');
    var $JD = $elt('tva3310a_20190101_JD');
    var $JE = $elt('tva3310a_20190101_JE');
    var $JF = $elt('tva3310a_20190101_JF');
    var $JG = $elt('tva3310a_20190101_JG');
    var $JH = $elt('tva3310a_20190101_JH');
    var $JJ = $elt('tva3310a_20190101_JJ');
    var $JK = $elt('tva3310a_20190101_JK');
    var $JL = $elt('tva3310a_20190101_JL');
    var $JM = $elt('tva3310a_20190101_JM');
    var $JN = $elt('tva3310a_20190101_JN');
    var $JP = $elt('tva3310a_20190101_JP');
    var $JQ = $elt('tva3310a_20190101_JQ');
    var $JR = $elt('tva3310a_20190101_JR');
    var $KG = $elt('tva3310a_20190101_KG');
    var $KF = $elt('tva3310a_20190101_KF');
    var $KJ = $elt('tva3310a_20190101_KJ');
    var $KL = $elt('tva3310a_20190101_KL');
    var $KT = $elt('tva3310a_20190101_KT');
    var $KX = $elt('tva3310a_20190101_KX');
    var $KY = $elt('tva3310a_20190101_KY');
    var $KZ = $elt('tva3310a_20190101_KZ');
    var $LA = $elt('tva3310a_20190101_LA');
    var $LC = $elt('tva3310a_20190101_LC');
    var $LD = $elt('tva3310a_20190101_LD');
    var $LE = $elt('tva3310a_20190101_LE');
    var $LF = $elt('tva3310a_20190101_LF');
    var $LG = $elt('tva3310a_20190101_LG');
    var $LH = $elt('tva3310a_20190101_LH');
    var $LJ = $elt('tva3310a_20190101_LJ');
    var $LJ = $elt('tva3310a_20190101_LJ');
    var $LK = $elt('tva3310a_20190101_LK');
    var $LL = $elt('tva3310a_20190101_LL');
    var $LM = $elt('tva3310a_20190101_LM');
    var $LN = $elt('tva3310a_20190101_LN');
    var $LP = $elt('tva3310a_20190101_LP');
    var $LQ = $elt('tva3310a_20190101_LQ');
    var $LR = $elt('tva3310a_20190101_LR');
    var $LS = $elt('tva3310a_20190101_LS');
    var $LT = $elt('tva3310a_20190101_LT');
    var $LU = $elt('tva3310a_20190101_LU');
    var $LW = $elt('tva3310a_20190101_LW');
    var $LX = $elt('tva3310a_20190101_LX');
    var $MA = $elt('tva3310a_20190101_MA');
    var $MB = $elt('tva3310a_20190101_MB');
    var $MC = $elt('tva3310a_20190101_MC');
    var $MD = $elt('tva3310a_20190101_MD');
    var $ME = $elt('tva3310a_20190101_ME');
    var $MF = $elt('tva3310a_20190101_MF');
    var $MG = $elt('tva3310a_20190101_MG');
    var $MK = $elt('tva3310a_20190101_MK');
    var $ML = $elt('tva3310a_20190101_ML');
    var $MM = $elt('tva3310a_20190101_MM');
    var $MN = $elt('tva3310a_20190101_MN');
    var $MP = $elt('tva3310a_20190101_MP');
    var $MQ = $elt('tva3310a_20190101_MQ');
    var $MR = $elt('tva3310a_20190101_MR');
    var $MS = $elt('tva3310a_20190101_MS');
    var $MU = $elt('tva3310a_20190101_MU');
    var $MV = $elt('tva3310a_20190101_MV');
    var $MW = $elt('tva3310a_20190101_MW');
    var $MX = $elt('tva3310a_20190101_MX');
    var $MY = $elt('tva3310a_20190101_MY');
    var $MZ = $elt('tva3310a_20190101_MZ');
    var $NA = $elt('tva3310a_20190101_NA');
    var $NB = $elt('tva3310a_20190101_NB');
    var $ND = $elt('tva3310a_20190101_ND');
    var $NE = $elt('tva3310a_20190101_NE');
    var $NF = $elt('tva3310a_20190101_NF');
    var $NG = $elt('tva3310a_20190101_NG');
    var $NH = $elt('tva3310a_20190101_NH');
    var $NJ = $elt('tva3310a_20190101_NJ');
    var $NK = $elt('tva3310a_20190101_NK');
    var $NN = $elt('tva3310a_20190101_NN');
    var $NP = $elt('tva3310a_20190101_NP');
    var $NQ = $elt('tva3310a_20190101_NQ');
    var $NR = $elt('tva3310a_20190101_NR');
    var $NS = $elt('tva3310a_20190101_NS');
    var $NT = $elt('tva3310a_20190101_NT');
    var $NU = $elt('tva3310a_20190101_NU');
    var $NV = $elt('tva3310a_20190101_NV');
    var $NW = $elt('tva3310a_20190101_NW');
    var $NX = $elt('tva3310a_20190101_NX');
    var $NY = $elt('tva3310a_20190101_NY');
    var $NZ = $elt('tva3310a_20190101_NZ');
    var $PA = $elt('tva3310a_20190101_PA');
    var $PB = $elt('tva3310a_20190101_PB');
    var $PC = $elt('tva3310a_20190101_PC');
    var $PD = $elt('tva3310a_20190101_PD');
    var $PE = $elt('tva3310a_20190101_PE');
    var $PF = $elt('tva3310a_20190101_PF');
    var $PG = $elt('tva3310a_20190101_PG');
    var $PK = $elt('tva3310a_20190101_PK');
    var $PP = $elt('tva3310a_20190101_PP');
    var $PQ = $elt('tva3310a_20190101_PQ');
    var $PR = $elt('tva3310a_20190101_PR');
    var $PS = $elt('tva3310a_20190101_PS');
    var $PU = $elt('tva3310a_20190101_PU');
    var $PW = $elt('tva3310a_20190101_PW');
    var $PX = $elt('tva3310a_20190101_PX');
    var $PY = $elt('tva3310a_20190101_PY');
    var $PZ = $elt('tva3310a_20190101_PZ');
    var $QA = $elt('tva3310a_20190101_QA');
    var $QB = $elt('tva3310a_20190101_QB');
    var $QC = $elt('tva3310a_20190101_QC');
    var $QD = $elt('tva3310a_20190101_QD');
    var $QE = $elt('tva3310a_20190101_QE');

    $readonly($CB, true);
    $readonly($CE, true);
    $readonly($CF, true);
    $readonly($PP, true);
    $readonly($PR, true);
    $readonly($CS, true);
    $readonly($CK, true);
    $readonly($CP, true);
    $readonly($CQ, true);
    $readonly($FA, true);
    $readonly($FB, true);
    $readonly($KG, true);
    $readonly($MY, true);
    $readonly($NB, true);
    $readonly($JN, true);
    $readonly($JP, true);
    $readonly($LA, true);

    $readonly($BN, true);
    $readonly($CN, true);
    $readonly($HB, true);
    $readonly($HI, true);
    $readonly($KJ, true);
    $readonly($KL, true);
    $readonly($LG, true);
    $readonly($MA, true);
    $readonly($PK, true);

    $value($CB, ($isServi($BB) && $float($BB) > 0) ? Math.round($float($BB) * 0.021) : '');
    $value($CE, ($isServi($BE) && $float($BE) > 0) ? Math.round($float($BE) * 0.009) : '');
    $value($CF, ($isServi($BF) && $float($BF) > 0) ? Math.round($float($BF) * 0.021) : '');
    $value($CK, ($isServi($BK) && $float($BK) > 0) ? Math.round($float($BK) * 0.130) : '');
    $value($CP, ($isServi($BP) && $float($BP) > 0) ? Math.round($float($BP) * 0.0105) : '');
    $value($CQ, ($isServi($BQ) && $float($BQ) > 0) ? Math.round($float($BQ) * 0.0175) : '');
    $value($CS, ($isServi($BS) && $float($BS) > 0) ? Math.round($float($BS) * 0.100) : '');
    $value($FA, ($isServi($ND) && $float($ND) > 0) ? Math.round($float($ND) * 0.01) : '');
    $value($FB, ($isServi($NE) && $float($NE) > 0) ? Math.round($float($NE) * 0.05) : '');
    $value($FJ, ($isServi($NF) && $float($NF) > 0) ? Math.round($float($NF) * 0.00732) : '');
    $value($HI, ($isServi($MP) && $float($MP) > 0) ? Math.round($float($MP) * 0.0075) : '');
    $value($JN, ($isServi($NN) && $float($NN) > 0) ? Math.round($float($NN) * 0.33) : '');
    $value($JP, ($isServi($NP) && $float($NP) > 0) ? Math.round($float($NP) * 0.000642) : '');
    $value($KG, ($isServi($NH) && $float($NH) > 0) ? Math.round($float($NH) * 0.013) : '');
    $value($KJ, ($isServi($MK) && $float($MK) > 0) ? Math.round($float($MK) * 0.02) : '');
    $value($KL, ($isServi($ML) && $float($ML) > 0) ? Math.round($float($ML) * 0.10) : '');
    $value($LA, ($isServi($PF) && $float($PF) > 0) ? Math.round($float($PF) * 125) : '');
    $value($LG, ($isServi($MF) && $float($MF) > 0) ? Math.round($float($MF) * 0.005) : '');
    $value($LH, ($isServi($MG) && $float($MG) > 0) ? Math.round($float($MG) * 0.005) : '');
    $value($MA, ($isServi($MC) && $float($MC) > 0) ? Math.round($float($MC) * 0.000363) : '');
    $value($MY, ($isServi($NJ) && $float($NJ) > 0) ? Math.round($float($NJ) * 0.004) : '');
    $value($NB, ($isServi($NK) && $float($NK) > 0) ? Math.round($float($NK) * 0.006) : '');
    $value($NQ, ($isServi($NY) && $float($NY) > 0) ? Math.round($float($NY) * 0.056) : '');
    $value($PP, ($isServi($PQ) && $float($PQ) > 0) ? Math.round($float($PQ) * 0.20) : '');
    $value($PR, ($isServi($PS) && $float($PS) > 0) ? Math.round($float($PS) * 0.10) : '');

    var $CNValue = 0;
    [$CA, $CB, $CC, $CE, $CF, $CS, $CK, $CM, $CP, $CQ, $CR].each(function (elt) {
        if ($float(elt) > 0) {
            $CNValue += $float(elt);
        }
    });
    $value($CN, $CNValue);

    var $BNValue = 0;
    [$BA, $BB, $BC, $BE, $BF, $BS, $BK, $BM, $BP, $BQ, $BR].each(function (elt) {
        if ($float(elt) > 0) {
            $BNValue += $float(elt);
        }
    });
    $value($BN, $BNValue);

    var $HBValue = 0;
    [
        $FA, $FB, $FG, $FJ, $FT, $FV, $FR,
        $HE, $HF, $HI,
        $JB, $JC, $JD, $JE, $JF, $JG, $JH, $JJ, $JK, $JL, $JM, $JN, $JP, $JQ, $JR, $KF, $KG, $KJ, $KL, $KT, $KX, $KY, $KZ,
        $LA, $LC, $LD, $LE, $LF, $LG, $LH, $LJ, $LK, $LL, $LM, $LN, $LP, $LQ, $LR, $LS, $LT, $LU, $LW, $LX,
        $MA, $MY,
        $NB, $NQ, $NR, $NS, $NZ,
        $PA, $PB, $PC, $PD, $PK, $PP, $PR, $PU, $PX, $PZ, $QE
    ].each(function (elt) {
        if ($float(elt) > 0) {
            $HBValue += $float(elt);
        }
    });
    $value($HB, $HBValue);

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

    $assert(!(($isServi($MR) || $isServi($LQ) || $isServi($LR) || $isServi($LS)) && !($isServi($MR) && $isServi($LQ) && $isServi($LR) && $isServi($LS))),
        'erreur_231', $MR, $LQ, $LR, $LS);

    $assert(!(($isServi($MS) || $isServi($LT) || $isServi($LU)) && !($isServi($MS) && $isServi($LT) && $isServi($LU))),
        'erreur_232', $MS, $LT, $LU);

    var $PJ = null;
    var $PH = null;
    var $PK_value = 0;

    $rowIndex = 1;
    while ($elt('tva3310a_20190101_PJ/' + $rowIndex)) {
        $PJ = $elt('tva3310a_20190101_PJ/' + $rowIndex);
        $PH = $elt('tva3310a_20190101_PH/' + $rowIndex);

        $assert(!($XOR($isServi($PJ), $isServi($PH)) || $float($PH) == 0),
            'erreur_233', $PJ, $PH);

        if (!isNaN($float($PH))) {
            $PK_value += $float($PH);
        }

        $rowIndex++;
    }
    $value($PK, $PK_value);

    var $QD = null;
    var $QB = null;
    var $QE_value = 0;

    $rowIndex = 1;
    while ($elt('tva3310a_20190101_QD/' + $rowIndex)) {
        $QD = $elt('tva3310a_20190101_QD/' + $rowIndex);
        $QB = $elt('tva3310a_20190101_QB/' + $rowIndex);
        $QC = $elt('tva3310a_20190101_QC/' + $rowIndex);

        $assert(!($XOR($isServi($QD), ($isServi($QB) || $isServi($QC))) || $float($QB) == 0 || $float($QC) == 0),
            'erreur_233_tva_3310a', $QD, $QB, $QC);

        if (!isNaN($float($QB))) {
            $QE_value += $float($QB);
        }

        $rowIndex++;
    }
    $value($QE, $QE_value);

    $value($elt('tva3310ca3_20190101_FD'), $float($BN));
    $value($elt('tva3310ca3_20190101_GD'), $float($CN));
    $value($elt('tva3310ca3_20190101_KB'), $float($HB));
    var $KE_value = 0;
    $KE_value = $float('tva3310ca3_20190101_KA') + $float('tva3310ca3_20190101_KB') - $float('tva3310ca3_20190101_KL');
    $value($elt('tva3310ca3_20190101_KE'), $KE_value);

    if ($KE_value > 0) {
        NTD.Identif.p("showPaiement", [$KE_value]);
    }

    if (!isNaN($float($elt('tva3310ca3_20190101_KB')))) {
        $value($elt('tva3515sd_20190101_BF'), $float($elt('tva3310ca3_20190101_KB')));
    } else {
        $value($elt('tva3515sd_20190101_BF'), 0);
    }
};

asserts.functions.tva3517sca12_20190101 = function ($elt,
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
    var $AB = $elt('tva3517sca12_20190101_AB');
    var $AD = $elt('tva3517sca12_20190101_AD');
    var $AB = $elt('tva3517sca12_20190101_AB');
    var $AE = $elt('tva3517sca12_20190101_AE');
    var $CA1 = $elt('tva3517sca12_20190101_CA1');
    var $CA2 = $elt('tva3517sca12_20190101_CA2');
    var $CA3 = $elt('tva3517sca12_20190101_CA3');
    var $CA4 = $elt('tva3517sca12_20190101_CA4');
    var $CA5 = $elt('tva3517sca12_20190101_CA5');
    var $CA = $elt('tva3517sca12_20190101_CA');
    var $DA = $elt('tva3517sca12_20190101_DA');
    var $DB = $elt('tva3517sca12_20190101_DB');
    var $DC = $elt('tva3517sca12_20190101_DC');
    var $EA = $elt('tva3517sca12_20190101_EA');
    var $EB = $elt('tva3517sca12_20190101_EB');
    var $EC = $elt('tva3517sca12_20190101_EC');
    var $ED = $elt('tva3517sca12_20190101_ED');
    var $EE = $elt('tva3517sca12_20190101_EE');
    var $EF = $elt('tva3517sca12_20190101_EF');
    var $EG = $elt('tva3517sca12_20190101_EG');
    var $EH = $elt('tva3517sca12_20190101_EH');
    var $EJ = $elt('tva3517sca12_20190101_EJ');
    var $EL = $elt('tva3517sca12_20190101_EL');
    var $EM = $elt('tva3517sca12_20190101_EM');
    var $EN = $elt('tva3517sca12_20190101_EN');
    var $EP = $elt('tva3517sca12_20190101_EP');
    var $EQ = $elt('tva3517sca12_20190101_EQ');
    var $EU = $elt('tva3517sca12_20190101_EU');
    var $EV = $elt('tva3517sca12_20190101_EV');
    var $EW = $elt('tva3517sca12_20190101_EW');
    var $EX = $elt('tva3517sca12_20190101_EX');
    var $EY = $elt('tva3517sca12_20190101_EY');
    var $EZ = $elt('tva3517sca12_20190101_EZ');
    // var $FA = $elt('tva3517sca12_20190101_FA');
    // var $FB = $elt('tva3517sca12_20190101_FB');
    // var $FC = $elt('tva3517sca12_20190101_FC');
    // var $FD = $elt('tva3517sca12_20190101_FD');
    var $FF = $elt('tva3517sca12_20190101_FF');
    var $FG = $elt('tva3517sca12_20190101_FG');
    var $FJ = $elt('tva3517sca12_20190101_FJ');
    var $FL = $elt('tva3517sca12_20190101_FL');
    var $FM = $elt('tva3517sca12_20190101_FM');
    var $FN = $elt('tva3517sca12_20190101_FN');
    var $FP = $elt('tva3517sca12_20190101_FP');
    var $FR = $elt('tva3517sca12_20190101_FR');
    var $FU = $elt('tva3517sca12_20190101_FU');
    var $FV = $elt('tva3517sca12_20190101_FV');
    var $FW = $elt('tva3517sca12_20190101_FW');
    var $FY = $elt('tva3517sca12_20190101_FY');
    var $GA = $elt('tva3517sca12_20190101_GA');
    var $GB = $elt('tva3517sca12_20190101_GB');
    var $GC = $elt('tva3517sca12_20190101_GC');
    var $GF = $elt('tva3517sca12_20190101_GF');
    var $GH = $elt('tva3517sca12_20190101_GH');
    var $HA = $elt('tva3517sca12_20190101_HA');
    var $HB = $elt('tva3517sca12_20190101_HB');
    var $HC = $elt('tva3517sca12_20190101_HC');
    var $JA = $elt('tva3517sca12_20190101_JA');
    var $JB = $elt('tva3517sca12_20190101_JB');
    var $KA = $elt('tva3517sca12_20190101_KA');
    var $KB = $elt('tva3517sca12_20190101_KB');
    var $KD = $elt('tva3517sca12_20190101_KD');
    // var $KE = $elt('tva3517sca12_20190101_KE');
    // var $KF = $elt('tva3517sca12_20190101_KF');
    // var $KG = $elt('tva3517sca12_20190101_KG');
    // var $KH = $elt('tva3517sca12_20190101_KH');
    // var $KJ = $elt('tva3517sca12_20190101_KJ');
    var $KL = $elt('tva3517sca12_20190101_KL');
    var $KM = $elt('tva3517sca12_20190101_KM');
    var $LA = $elt('tva3517sca12_20190101_LA');
    var $LB = $elt('tva3517sca12_20190101_LB');
    var $MA = $elt('tva3517sca12_20190101_MA');
    var $MD = $elt('tva3517sca12_20190101_MD');
    var $ME = $elt('tva3517sca12_20190101_ME');
    var $MF = $elt('tva3517sca12_20190101_MF');
    var $MG = $elt('tva3517sca12_20190101_MG');
    var $MM = $elt('tva3517sca12_20190101_MM');
    var $MN = $elt('tva3517sca12_20190101_MN');
    var $NA = $elt('tva3517sca12_20190101_NA');
    var $NB = $elt('tva3517sca12_20190101_NB');
    var $NC = $elt('tva3517sca12_20190101_NC');
    var $QA = $elt('tva3517sca12_20190101_QA');
    var $QD = $elt('tva3517sca12_20190101_QD');
    var $QE = $elt('tva3517sca12_20190101_QE');
    var $QF = $elt('tva3517sca12_20190101_QF');
    var $QH = $elt('tva3517sca12_20190101_QH');
    var $QJ = $elt('tva3517sca12_20190101_QJ');
    var $QS = $elt('tva3517sca12_20190101_QS');
    var $RA = $elt('tva3517sca12_20190101_RA');
    var $RB = $elt('tva3517sca12_20190101_RB');
    var $RC = $elt('tva3517sca12_20190101_RC');
    var $RE = $elt('tva3517sca12_20190101_RE');
    var $RD = $elt('tva3517sca12_20190101_RD');
    var $RF = $elt('tva3517sca12_20190101_RF');
    var $RG = $elt('tva3517sca12_20190101_RG');
    var $RN = $elt('tva3517sca12_20190101_RN');
    var $SA = $elt('tva3517sca12_20190101_SA');
    var $SB = $elt('tva3517sca12_20190101_SB');
    var $SC = $elt('tva3517sca12_20190101_SC');
    var $SD = $elt('tva3517sca12_20190101_SD');
    var $SH = $elt('tva3517sca12_20190101_SH');
    var $SM = $elt('tva3517sca12_20190101_SM');
    var $SN = $elt('tva3517sca12_20190101_SN');
    var $SP = $elt('tva3517sca12_20190101_SP');
    var $ST = $elt('tva3517sca12_20190101_ST');
    var $SQ = $elt('tva3517sca12_20190101_SQ');
    var $SS = $elt('tva3517sca12_20190101_SS');
    var $SR = $elt('tva3517sca12_20190101_SR');
    var $SV = $elt('tva3517sca12_20190101_SV');
    var $SW = $elt('tva3517sca12_20190101_SW');
    var $SX = $elt('tva3517sca12_20190101_SX');
    var $TB = $elt('tva3517sca12_20190101_TB');
    var $TD = $elt('tva3517sca12_20190101_TD');
    var $UB = $elt('tva3517sca12_20190101_UB');
    var $UD = $elt('tva3517sca12_20190101_UD');
    var $VA = $elt('tva3517sca12_20190101_VA');
    var $VC = $elt('tva3517sca12_20190101_VC');
    var $VE = $elt('tva3517sca12_20190101_VE');
    var $VF = $elt('tva3517sca12_20190101_VF');
    var $VJ = $elt('tva3517sca12_20190101_VJ');
    var $VK = $elt('tva3517sca12_20190101_VK');
    var $VL = $elt('tva3517sca12_20190101_VL');
    var $VM = $elt('tva3517sca12_20190101_VM');
    var $VN = $elt('tva3517sca12_20190101_VN');
    var $VP = $elt('tva3517sca12_20190101_VP');
    var $VS = $elt('tva3517sca12_20190101_VS');
    var $VT = $elt('tva3517sca12_20190101_VT');
    var $VW = $elt('tva3517sca12_20190101_VW');
    var $VX = $elt('tva3517sca12_20190101_VX');
    var $VY = $elt('tva3517sca12_20190101_VY');
    var $VZ = $elt('tva3517sca12_20190101_VZ');
    var $WB = $elt('tva3517sca12_20190101_WB');
    var $WC = $elt('tva3517sca12_20190101_WC');
    var $WD = $elt('tva3517sca12_20190101_WD');
    var $WE = $elt('tva3517sca12_20190101_WE');
    var $WF = $elt('tva3517sca12_20190101_WF');
    var $WG = $elt('tva3517sca12_20190101_WG');
    var $WH = $elt('tva3517sca12_20190101_WH');
    var $WJ = $elt('tva3517sca12_20190101_WJ');
    var $WK = $elt('tva3517sca12_20190101_WK');
    var $WL = $elt('tva3517sca12_20190101_WL');
    var $WM = $elt('tva3517sca12_20190101_WM');
    var $WN = $elt('tva3517sca12_20190101_WN');
    var $WP = $elt('tva3517sca12_20190101_WP');
    var $WQ = $elt('tva3517sca12_20190101_WQ');
    var $WR = $elt('tva3517sca12_20190101_WR');
    var $WS = $elt('tva3517sca12_20190101_WS');
    var $WT = $elt('tva3517sca12_20190101_WT');
    var $WU = $elt('tva3517sca12_20190101_WU');
    var $WV = $elt('tva3517sca12_20190101_WV');
    var $WZ = $elt('tva3517sca12_20190101_WZ');
    var $XA = $elt('tva3517sca12_20190101_XA');
    var $XB = $elt('tva3517sca12_20190101_XB');
    var $YA = $elt('tva3517sca12_20190101_YA');
    var $YB = $elt('tva3517sca12_20190101_YB');
    var $YC = $elt('tva3517sca12_20190101_YC');
    var $YK = $elt('tva3517sca12_20190101_YK');
    var $YL = $elt('tva3517sca12_20190101_YL');
    var $ZA = $elt('tva3517sca12_20190101_ZA');
    var $ZB = $elt('tva3517sca12_20190101_ZB');
    var $ZE = $elt('tva3517sca12_20190101_ZE');
    var $ZF = $elt('tva3517sca12_20190101_ZF');
    var $ZG = $elt('tva3517sca12_20190101_ZG');
    var $ZH = $elt('tva3517sca12_20190101_ZH');
    var $ZJ = $elt('tva3517sca12_20190101_ZJ');
    var $ZK = $elt('tva3517sca12_20190101_ZK');
    var $ZL = $elt('tva3517sca12_20190101_ZL');
    var $ZM = $elt('tva3517sca12_20190101_ZM');
    var $ZN = $elt('tva3517sca12_20190101_ZN');
    var $ZP = $elt('tva3517sca12_20190101_ZP');
    var $ZR = $elt('tva3517sca12_20190101_ZR');
    var $ZS = $elt('tva3517sca12_20190101_ZS');
    var $ZT = $elt('tva3517sca12_20190101_ZT');
    var $ZU = $elt('tva3517sca12_20190101_ZU');
    var $ZW = $elt('tva3517sca12_20190101_ZW');
    var $ZX = $elt('tva3517sca12_20190101_ZX');
    var $ZZ = $elt('tva3517sca12_20190101_ZZ');

    var $requiredFields = [
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
        $NA, $NB,
        $QD, $QE, $QF, $QH, $QJ, $QS,
        $RA, $RB, $RC, $RE, $RF, $RG, $RN,
        $SA, $SB, $SC, $SE, $SM, $SN, $SP,
        $VA, $VC, $VE, $VF, $VJ, $VM, $VN, $VP, $VS, $VT, $VW, $VX, $VY,
        $WB, $WC, $WF, $WG, $WK, $WL, $WM, $WQ, $WR, $WS,
        $YC,
        $ZR, $ZS, $ZT, $ZU, $ZZ
    ];
    var $emptiableFields = [
        $DA, $DB, $DC, $EA, $EB, $EC, $ED, $EF, $EE,
        $EG, $EH, $EJ, $EL, $EM, $EN, $EP, $EQ, $EU, $EV, $EW,
        $EX, $EY, $EZ, /*$FA, $FB, $FC, $FD,*/ $FF, $FG, $FJ,
        $FL, $FM, $FN, $FP, $FR, $FU, $FV, $FW, $FY, $GA, $GB,
        $GC, $GF, $GH, $HA, $HB, $HC, $JA, $JB, $KA, $KB, $KD,
        $KL, $KM, $LA, $LB, $MA,
        $MD, $ME, $MF, $MG, $MM, $MN, $NA,
        $NB, $QA, $QD, $QE, $QF, $QH, $QJ, $QS,
        $RA, $RB, $RC, $RE, $RF, $RG, $RN,
        $SA, $SB, $SC, $TB, $TD, $UB, $UD,
        $VA, $VC, $VE, $VF, $VJ, $VL, $VM, $VN, $VP,
        $VS, $VT, $VW, $VX, $VY, $VZ,
        $WB, $WC
    ];

    if ($isServi($SD)) {
        for (var i = 0; i < $emptiableFields.length; i++) {
            $readonly($emptiableFields[i], true);
            $value($emptiableFields[i], '');
        }
    } else {
        for (var i = 0; i < $emptiableFields.length; i++) {
            $readonly($emptiableFields[i], false);
        }
    }

    $readonly($DC, true);

    $readonly($FF, true);
    $readonly($FR, true);
    $readonly($FU, true);
    $readonly($FV, true);
    $readonly($FW, true);

    $readonly($GC, true);
    $readonly($GH, true);

    $readonly($HC, true);

    $readonly($KD, true);
    // $readonly($KE, true);
    // $readonly($KF, true);
    // $readonly($KG, true);
    // $readonly($KH, true);
    // $readonly($KJ, true);

    $readonly($LA, true);
    $readonly($LB, true);

    $readonly($MM, true);
    $readonly($MN, true);
    $readonly($MA, true);

    $readonly($NA, true);
    $readonly($NB, true);
    $readonly($NC, true);

    $readonly($QA, true);
    $readonly($QD, true);
    $readonly($QE, true);

    $readonly($RA, true);
    $readonly($RF, true);
    $readonly($RG, true);

    $readonly($SA, true);
    $readonly($SB, true);
    $readonly($SC, true);
    $readonly($SH, true);
    $readonly($SQ, true);
    $readonly($SS, true);

    $readonly($VA, true);
    $readonly($VC, true);
    $readonly($VZ, true);

    $readonly($WH, true);
    $readonly($WJ, true);

    $readonly($YK, true);

    $readonly($ZB, true);
    $readonly($ZW, true);
    $readonly($ZX, true);


    $value($RA, $value($NC));

    $percent($DC, $SM, 33);

    $percent($FF, $EF, 5.5);
    $percent($FU, $EU, 8.5);
    $percent($FV, $EV, 2.1);
    $percent($FW, $EW, 20);

    $percent($GH, $GF, 10);

    $percent($QA, $ZR, 5);
    $percent($QD, $ZE, 0.2);
    $percent($QE, $ZF, 3.25);

    $percent($RF, $ZG, 2);
    $percent($RG, $ZH, 10);

    $percent($SQ, $SR, 2);
    $percent($SS, $ST, 10);

    $percent($VC, $ZL, 0.75);

    $percent($WH, $WZ, 0.50);
    $percent($WJ, $ZA, 0.50);

    $percent($YK, $YL, 5.6);

    $percent($ZB, $ZS, 1);
    $percent($ZW, $ZT, 0.4);
    $percent($ZX, $ZU, 0.6);


    var VZ_value = $float($SP) * 125;
    $value($VZ, VZ_value);

    $addition($FR,
        $EZ,
        /*$FB, $FD,*/
        $FF, $FG, $FJ, $FL, $FM, $FN, $FP, $FU, $FV, $FW, $FY,
        $GH,
        $VP);

    $addition($SB, $AE,
        $DA, $DB, $DC,
        $KL, $KM,
        $QA, $QD, $QE, $QF, $QH, $QJ, $QS,
        $RF, $RG, $RN, $RD,
        $SQ, $SH, $SS, $SV, $SX,
        $VC, $VE, $VF, $VJ, $VW, $VX, $VY, $VZ,
        $WB, $WC, $WD, $WE, $WF, $WG, $WH, $WJ, $WK, $WL, $WM, $WN, $WP, $WQ, $WR, $WS, $WT, $WU, $WV,
        $YK,
        $ZB, $ZW, $ZX);

    $addition($HC, $HA, $HB);
    $soustraction($VA, $FR, $FL, $FM, $EQ, $HC);
    $addition($GC, $FR, $GA, $GB, $VS);
    $addition($KD, $HA, $HB, $JA, $KA, $KB, $VT);
    $addition($MM, $MD, $MF);
    if (!$isServi($MM)) {
        $value($MM, 0);
    }
    $addition($MN, $ME, $MG);
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

    NTD.Identif.t("hidePaiement", []);
    if ($isServi($SC) && $float($SC) > 0) {
        NTD.Identif.t("showPaiement", [$float($SC)]);
    }

    // --- asserts
    $assert(!($isServi($VK) && !$isServi($CA)), 'erreur_128', $CA, $VK);

    $controls.erreur_111($EG, $FG);
    $controls.erreur_111($EH, $EZ);
    $controls.erreur_111($EJ, $FJ);
    $controls.erreur_111($EL, $FL);
    $controls.erreur_111($EM, $FM);
    $controls.erreur_111($EN, $FN);
    $controls.erreur_111($EP, $FP);
    $controls.erreur_111($EW, $FW);
    $controls.erreur_111($EY, $FY);

    $controls.erreur_111($GF, $GH);

    $controls.erreur_111($SN, $VY);

    $controls.erreur_111($VN, $VP);

    $controls.erreur_111($YA, $WL);
    $controls.erreur_111($YB, $WM);
    $controls.erreur_111($YC, $WG);

    $controls.erreur_111($ZM, $WK);
    $controls.erreur_111($ZZ, $WF);

    $controls.erreur_111($SW, $SV);
    $controls.erreur_111($XA, $SX);
    $controls.erreur_111($XB, $RD);


    $controls.erreur_112($EZ, $EH);
    $controls.erreur_112($FG, $EG);
    $controls.erreur_112($FJ, $EJ);
    $controls.erreur_112($FL, $EL);
    $controls.erreur_112($FM, $EM);
    $controls.erreur_112($FN, $EN);
    $controls.erreur_112($FP, $EP);
    $controls.erreur_112($FW, $EW);
    $controls.erreur_112($FY, $EY);

    $controls.erreur_112($GH, $GF);

    $controls.erreur_112($VP, $VN);
    $controls.erreur_112($VY, $SN);

    $controls.erreur_112($WK, $ZM);
    $controls.erreur_112($WL, $YA);
    $controls.erreur_112($WM, $YB);

    $controls.erreur_112($WF, $ZZ);
    $controls.erreur_112($SV, $SW);
    $controls.erreur_112($SX, $XA);
    $controls.erreur_112($RD, $XB);

    $controls.erreur_117($EG, $FG, 0.021, 0.206);
    $controls.erreur_117($EP, $FP, 0.021, 0.20);

    $assert(!(($isServi($ZN) || $isServi($WQ) || $isServi($WR) || $isServi($WS)) && !($isServi($ZN) && $isServi($WQ) && $isServi($WR) && $isServi($WS))),
        'erreur_231', $ZN, $WQ, $WR, $WS);

    $assert(!(($isServi($ZP) || $isServi($WT) || $isServi($WU)) && !($isServi($ZP) && $isServi($WT) && $isServi($WU))),
        'erreur_232', $ZP, $WT, $WU);

    $rowIndex = 1;
    var $total = 0;

    while ($elt('tva3517sca12_20190101_SF/' + $rowIndex)) {
        var $SF = $elt('tva3517sca12_20190101_SF/' + $rowIndex);
        var $SE = $elt('tva3517sca12_20190101_SE/' + $rowIndex);

        $assert(!(($isServi($SF) || $isServi($SE)) && !($isServi($SF) && $isServi($SE)) && $float($SE)),
            'erreur_233', $SF, $SE);

        if (!isNaN($float($SE))) {
            $total += $float($SE);
        }

        $rowIndex++;
    }

    $value($SH, $total);

    $rowIndex = 1;
    var $total = 0;
    while ($elt('tva3517sca12_20190101_AD/' + $rowIndex)) {
        var $AD = $elt('tva3517sca12_20190101_AD/' + $rowIndex);
        var $AC = $elt('tva3517sca12_20190101_AC/' + $rowIndex);
        var $AB = $elt('tva3517sca12_20190101_AB/' + $rowIndex);

        $assert(!(($isServi($AD) || $isServi($AB) || $isServi($AC)) && !($isServi($AD) && $isServi($AB) && $isServi($AC)) && $float($AB) > 0),
            'erreur_233_tva_3517sca12', $AD, $AB, $AC);

        if (!isNaN($float($AB))) {
            $total += $float($AB);
        }

        $rowIndex++;
    }

    $value($AE, $total);

    $assert(!($isServi($SC) && String($value($SC)).length > 6), 'erreur_229', $SC);

    $assert(!($isServi($EQ) && $isServi($FP) && !($float($EQ) <= $float($FP))),
        'erreur_137', $EQ, $FP);

    $assert(!($isServi($HB) && $float($HB) > 0 && !(
            $float($HB) == Math.round(0.002 * ($float($EB) + $float($EC) + $float($EE) + $float($ED) + $float($VM) + $float($EX) + $float($EF) + $float($EU) + $float($EV) + $float($EJ) + $float($EG) + $float($EW) + $float($GF)))
        )),
        'erreur_034', $HB, $EB, $EC, $ED, $EE, $VM, $EX, $EF, $EU, $EV, $EJ, $EG, $EW, $GF);
    $assert(!($isServi($JB) && $float($JB) >= 0 && !(0 < $float($JB) && $float($JB) <= 100)), 'erreur_116', $JB);

    $assert(!($isServi($RA) && $float($RA) >= 0 && !($float($RA) == $float($RB) + $float($RC) + $float($RE))), 'erreur_204', $RA, $RB, $RC, $RE);
    $assert(!($isServi($RA) && $isServi($RB) && !($float($RB) <= $float($RA))),
        'erreur_132', $RA, $RB);

    $assert(($isServi($RB) && $float($RB) > 0),
        'La demande de remboursement doit être effectuée sur le formulaire 3517-DDR (accessible à la suite de cette déclaration). Le crédit susceptible d\'être remboursé est celui constaté au terme de l\'exercice. \n',
        $RB);

    var $casesAccomptesRemplies = 0;
    $casesAccomptesRemplies += ($isServi($MD) || $isServi($ME)) ? 1 : 0;
    $casesAccomptesRemplies += ($isServi($MF) || $isServi($MG)) ? 1 : 0;
    var $casesCoches = 0;
    $casesCoches += $isServi($TB) ? 1 : 0;
    $casesCoches += $isServi($TD) ? 1 : 0;
    $assert(!($isServi($MA) && $float($MA) > 0 && !($casesAccomptesRemplies == $casesCoches)),
        'erreur_124', $MA, $MD, $ME, $MF, $MG);

    $controls.erreur_129($TB, $UB);
    $controls.erreur_129($TD, $UD);

    $controls.erreur_226($UB, $TB);
    $controls.erreur_226($UD, $TD);

    $controls.erreur_134($UB, $elt(NTD.Identif.tField('CA')), $elt(NTD.Identif.tField('CB')));
    $controls.erreur_134($UD, $elt(NTD.Identif.tField('CA')), $elt(NTD.Identif.tField('CB')));


    $controls.erreur_042($SD, $requiredFields);
    $controls.erreur_049($SD, $requiredFields);
};


asserts.functions.tva3514_20190101 = function ($elt,
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

    var formOccurences = $$('.formulaire-block.3514 .page-form')
    if (!formOccurences.length) {
        formOccurences = $$('.formulaire-visibility.3514 .page-form');
    }
    for (var occurence = 0; occurence < formOccurences.length; occurence++) {

        var $HA = $elt('tva3514_20190101_HA', formOccurences[occurence]);
        var $HB = $elt('tva3514_20190101_HB', formOccurences[occurence]);
        var $HC = $elt('tva3514_20190101_HC', formOccurences[occurence]);
        var $DE = $elt('tva3514_20190101_DE', formOccurences[occurence]);
        var $IA = $elt('tva3514_20190101_IA', formOccurences[occurence]);
        var $IB = $elt('tva3514_20190101_IB', formOccurences[occurence]);
        var $IC = $elt('tva3514_20190101_IC', formOccurences[occurence]);
        var $ID = $elt('tva3514_20190101_ID', formOccurences[occurence]);
        var $CA = $elt('tva3514_20190101_CA', formOccurences[occurence]);
        var $CB = $elt('tva3514_20190101_CB', formOccurences[occurence]);
        var $CC = $elt('tva3514_20190101_CC', formOccurences[occurence]);


        // ---- Control
        if ($isServi($HA) || $isServi($HB) || $isServi($DE)) {
            $readonly($IA, true).setValue('');
            $readonly($IB, true).setValue('');
            $readonly($ID, true).setValue('');

            $readonly($HA, false);
            $readonly($HB, false);
            $readonly($DE, false);
        } else if ($isServi($IA) || $isServi($IB) || $isServi($ID)) {
            $readonly($HA, true).setValue('');
            $readonly($HB, true).setValue('');
            $readonly($DE, true);
            $DE.checked = false;

            $readonly($IA, false);
            $readonly($IB, false);
            $readonly($ID, false);
        } else {
            $readonly($HA, false);
            $readonly($HB, false);
            $readonly($DE, false);
            $readonly($IA, false);
            $readonly($IB, false);
            $readonly($ID, false);
        }


        // --- IC = IB - IA
        $readonly($IC, true);
        $soustraction($IC, $IB, $IA);


        // --- HC = HA - HB
        $readonly($HC, true);
        $soustraction($HC, $HA, $HB);

        // --- show Tidenf form
        NTD.Identif.t("hidePaiement", []);
        if ($float($HC) > 0) {
            NTD.Identif.t("showPaiement", [$float($HC)]);
        }

        $assert(!($isServi($HA) &&
                ($isServi($IA) ||
                    $isServi($IB) ||
                    $isServi($IC) ||
                    $isServi($ID))),
            'erreur_217',
            $HA, $IA, $IB, $IC, $ID);

        $assert(!($isServi($HB) &&
                ($isServi($IA) ||
                    $isServi($IB) ||
                    $isServi($IC) ||
                    $isServi($ID))),
            'erreur_217',
            $HB, $IA, $IB, $IC, $ID);

        $assert(!($isServi($DE) &&
                ($isServi($IA) ||
                    $isServi($IB) ||
                    $isServi($IC) ||
                    $isServi($ID))),
            'erreur_217', $DE, $IA, $IB, $IC, $ID);

        $assert(!($isServi($HB) && !($isServi($HA) && ($HA <= $HB))), 'erreur_213', $HA, $HB);

        $assert(!($isServi($DE) && !($isServi($HA) && $float($HA) > 0)), 'erreur_216', $HA);

        $assert(!($isServi($IA) && $isServi($IB) && $float($IB) >= 0 && !($float($IA) < $float($IB))) && !(!$isServi($IB) && $isServi($IA)), 'erreur_214', $IA, $IB);

        $assert(!($isServi($ID) && !(760 <= $float($ID) && $float($ID) <= $float($IC))), 'erreur_215', $ID, $IC);

        $assert(!($isServi($IA) &&
                ($isServi($HA) ||
                    $isServi($HB) ||
                    $isServi($HC) ||
                    $isServi($DE))),
            'erreur_217', $IA, $HA, $HB, $HC, $DE);

        $assert(!($isServi($IB) &&
                ($isServi($HA) ||
                    $isServi($HB) ||
                    $isServi($HC) ||
                    $isServi($DE))),
            'erreur_217', $IB, $HA, $HB, $HC, $DE);

        $assert(!($isServi($ID) &&
                ($isServi($HA) ||
                    $isServi($HB) ||
                    $isServi($HC) ||
                    $isServi($DE))),
            'erreur_217', $ID, $HA, $HB, $HC, $DE);

        $assert(!($isServi($CC) &&
                !$isServi($CB)),
            'erreur_128', $CB, $CC);

        $assert([$HA, $HB, $HC, $DE, $IA, $IB, $IC, $ID, $CA, $CB, $CC].some(function (elt) {
            return $isServi(elt);
        }), 'erreur_201', $HA, $HB, $HC, $DE, $IA, $IB, $IC, $ID, $CA, $CB, $CC);
    }

};


asserts.functions.tva3517ddr_20190101 = function ($elt,
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


    var $AA = $elt('tva3517ddr_20190101_AA');
    var $AB = $elt('tva3517ddr_20190101_AB');
    var $AC = $elt('tva3517ddr_20190101_AC');
    var $AD = $elt('tva3517ddr_20190101_AD');
    var $AE = $elt('tva3517ddr_20190101_AE');
    var $AF1 = $elt('tva3517ddr_20190101_AF1');
    var $AH = $elt('tva3517ddr_20190101_AH');
    var $AJ = $elt('tva3517ddr_20190101_AJ');
    var $AK1 = $elt('tva3517ddr_20190101_AK1');
    var $AK2 = $elt('tva3517ddr_20190101_AK2');
    var $AK3 = $elt('tva3517ddr_20190101_AK3');
    var $AK4 = $elt('tva3517ddr_20190101_AK4');
    var $BA = $elt('tva3517ddr_20190101_BA');
    var $BB = $elt('tva3517ddr_20190101_BB');


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


asserts.functions.tva3525bis_20190101 = function ($elt,
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

    var $AC = $elt('tva3525bis_20190101_AC');
    var $AD = $elt('tva3525bis_20190101_AD');
    var $BB = $elt('tva3525bis_20190101_BB');
    var $BC = $elt('tva3525bis_20190101_BC');
    var $BD = $elt('tva3525bis_20190101_BD');
    var $BE = $elt('tva3525bis_20190101_BE');
    var $DA = $elt('tva3525bis_20190101_DA');

    if ($isServi($BB) && $isServi($BC)) {
        $value($BD, Math.max(0, $float($BB) - $float($BC)));
    }
    if ($isServi($BE)) {
        $readonly($BB, true).setValue('');
        $readonly($BC, true).setValue('');
        $readonly($BD, true).setValue('');
    } else {
        $readonly($BB, false);
        $readonly($BC, false);
        $readonly($BD, false);
    }

    NTD.Identif.t("hidePaiement", []);
    if ($isServi($BD) && $float($BD) > 0) {
        NTD.Identif.t("showPaiement", [$float($BD)]);
    }

    $assert(!($isServi($BE) && ($isServi($BB) || $isServi($BC) || $isServi($BD))),
        'erreur_042',
        $BE, $BB, $BC, $BD);
    $assert(!(!$isServi($BE) && ((!$isServi($BB) || $float($BB) <= 0) && (!$isServi($BC) || $float($BC) <= 0) && (!$isServi($BD) || $float($BD) <= 0))),
        'erreur_049',
        $BE, $BB, $BC, $BD);
    $assert(!($isServi($AD) &&
            !$isServi($DA)),
        'erreur_128', $AD, $DA);

};

asserts.functions.tva3517bisca12_20190101 = function ($elt,
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

    var $AE = $elt('tva3517bisca12_20190101_AE');
    var $AF = $elt('tva3517bisca12_20190101_AF');
    var $AG = $elt('tva3517bisca12_20190101_AG');
    var $BA = $elt('tva3517bisca12_20190101_BA');
    var $DA = $elt('tva3517bisca12_20190101_DA');
    var $DB = $elt('tva3517bisca12_20190101_DB');
    var $DC = $elt('tva3517bisca12_20190101_DC');
    var $DD = $elt('tva3517bisca12_20190101_DD');
    var $DE = $elt('tva3517bisca12_20190101_DE');
    var $DF = $elt('tva3517bisca12_20190101_DF');
    var $DH = $elt('tva3517bisca12_20190101_DH');
    var $DJ = $elt('tva3517bisca12_20190101_DJ');
    var $DK = $elt('tva3517bisca12_20190101_DK');
    var $DL = $elt('tva3517bisca12_20190101_DL');
    var $DM = $elt('tva3517bisca12_20190101_DM');
    var $DN = $elt('tva3517bisca12_20190101_DN');
    var $DP = $elt('tva3517bisca12_20190101_DP');
    var $DQ = $elt('tva3517bisca12_20190101_DQ');
    var $DR = $elt('tva3517bisca12_20190101_DR');
    var $DS = $elt('tva3517bisca12_20190101_DS');
    var $DU = $elt('tva3517bisca12_20190101_DU');
    var $DV = $elt('tva3517bisca12_20190101_DV');
    var $DY = $elt('tva3517bisca12_20190101_DY');
    var $DZ = $elt('tva3517bisca12_20190101_DZ');
    // var $EA = $elt('tva3517bisca12_20190101_EA');
    // var $EB = $elt('tva3517bisca12_20190101_EB');
    // var $EC = $elt('tva3517bisca12_20190101_EC');
    // var $ED = $elt('tva3517bisca12_20190101_ED');
    var $EE = $elt('tva3517bisca12_20190101_EE');
    var $EH = $elt('tva3517bisca12_20190101_EH');
    var $EJ = $elt('tva3517bisca12_20190101_EJ');
    var $EK = $elt('tva3517bisca12_20190101_EK');
    var $EL = $elt('tva3517bisca12_20190101_EL');
    var $EM = $elt('tva3517bisca12_20190101_EM');
    var $EN = $elt('tva3517bisca12_20190101_EN');
    var $EP = $elt('tva3517bisca12_20190101_EP');
    var $EQ = $elt('tva3517bisca12_20190101_EQ');
    var $ER = $elt('tva3517bisca12_20190101_ER');
    var $ES = $elt('tva3517bisca12_20190101_ES');
    var $EU = $elt('tva3517bisca12_20190101_EU');
    var $EV = $elt('tva3517bisca12_20190101_EV');
    var $EZ = $elt('tva3517bisca12_20190101_EZ');
    var $FA = $elt('tva3517bisca12_20190101_FA');
    var $FB = $elt('tva3517bisca12_20190101_FB');
    var $FC = $elt('tva3517bisca12_20190101_FC');
    var $FD = $elt('tva3517bisca12_20190101_FD');
    var $FF = $elt('tva3517bisca12_20190101_FF');
    var $FG = $elt('tva3517bisca12_20190101_FG');
    var $GA = $elt('tva3517bisca12_20190101_GA');
    var $GB = $elt('tva3517bisca12_20190101_GB');
    var $HA = $elt('tva3517bisca12_20190101_HA');
    var $JA = $elt('tva3517bisca12_20190101_JA');
    var $JB = $elt('tva3517bisca12_20190101_JB');
    var $JC = $elt('tva3517bisca12_20190101_JC');
    var $KA = $elt('tva3517bisca12_20190101_KA');
    var $KB = $elt('tva3517bisca12_20190101_KB');
    var $KC = $elt('tva3517bisca12_20190101_KC');
    var $KD = $elt('tva3517bisca12_20190101_KD');
    var $KF = $elt('tva3517bisca12_20190101_KF');
    var $LC = $elt('tva3517bisca12_20190101_LC');
    var $LD = $elt('tva3517bisca12_20190101_LD');
    var $LF = $elt('tva3517bisca12_20190101_LF');
    var $LH = $elt('tva3517bisca12_20190101_LH');
    var $LK = $elt('tva3517bisca12_20190101_LK');
    var $LM = $elt('tva3517bisca12_20190101_LM');
    var $MA = $elt('tva3517bisca12_20190101_MA');
    var $MB = $elt('tva3517bisca12_20190101_MB');
    var $MC = $elt('tva3517bisca12_20190101_MC');
    var $NA = $elt('tva3517bisca12_20190101_NA');
    var $NB = $elt('tva3517bisca12_20190101_NB');
    var $NC = $elt('tva3517bisca12_20190101_NC');
    var $ND = $elt('tva3517bisca12_20190101_ND');
    var $RC = $elt('tva3517bisca12_20190101_RC');
    var $RD = $elt('tva3517bisca12_20190101_RD');
    var $RG = $elt('tva3517bisca12_20190101_RG');
    var $RH = $elt('tva3517bisca12_20190101_RH');
    var $RJ = $elt('tva3517bisca12_20190101_RJ');
    var $RK = $elt('tva3517bisca12_20190101_RK');
    var $RM = $elt('tva3517bisca12_20190101_RM');
    var $RN = $elt('tva3517bisca12_20190101_RN');
    var $RP = $elt('tva3517bisca12_20190101_RP');
    var $RQ = $elt('tva3517bisca12_20190101_RQ');
    var $RR = $elt('tva3517bisca12_20190101_RR');
    var $RS = $elt('tva3517bisca12_20190101_RS');
    var $RT = $elt('tva3517bisca12_20190101_RT');
    var $RU = $elt('tva3517bisca12_20190101_RU');
    var $RV = $elt('tva3517bisca12_20190101_RV');
    var $RW = $elt('tva3517bisca12_20190101_RW');
    var $RX = $elt('tva3517bisca12_20190101_RX');
    var $RY = $elt('tva3517bisca12_20190101_RY');
    var $RZ = $elt('tva3517bisca12_20190101_RZ');
    var $SC = $elt('tva3517bisca12_20190101_SC');
    var $SD = $elt('tva3517bisca12_20190101_SD');
    var $SE = $elt('tva3517bisca12_20190101_SE');
    var $SF = $elt('tva3517bisca12_20190101_SF');
    var $SG = $elt('tva3517bisca12_20190101_SG');
    var $SH = $elt('tva3517bisca12_20190101_SH');
    var $SJ = $elt('tva3517bisca12_20190101_SJ');
    var $SK = $elt('tva3517bisca12_20190101_SK');
    var $SL = $elt('tva3517bisca12_20190101_SL');
    var $SM = $elt('tva3517bisca12_20190101_SM');

    // $readonly($KA, true);
    // $readonly($KB, true);
    // $readonly($KC, true);
    // $readonly($KD, true);
    // $readonly($KF, true);

    $readonly($JA, true);
    $readonly($JB, true);
    $readonly($JC, true);

    $readonly($EU, true);
    $readonly($EE, true);
    $readonly($EK, true);
    $readonly($EQ, true);
    $readonly($EV, true);

    $readonly($FF, true);
    // $readonly($EA, true);
    // $readonly($EB, true);
    // $readonly($EC, true);
    // $readonly($ED, true);
    $readonly($ES, true);

    $readonly($GA, true);
    $readonly($GB, true);
    $readonly($LC, true);
    $readonly($RK, true);
    $readonly($RT, true);
    $readonly($RU, true);

    $readonly($MA, true);
    $readonly($MC, true);
    $readonly($NA, true);
    $readonly($NB, true);
    $readonly($NC, true);


    $percent($EE, $DE, 5.5);
    $percent($EK, $DK, 20);
    $percent($EQ, $DQ, 10);
    $percent($EU, $DU, 2.1);
    $percent($EV, $DV, 8.5);
    $percent($LC, $SJ, 1);
    $percent($RT, $SC, 0.5);
    $percent($RU, $SD, 0.5);

    if ($isServi($SM) && $float($SM) > 0) {
        $value($RK, $float($SM) * 125);
    } else {
        $value($RK, '');
    }

    // Suppression de $EB et $ED
    $addition($ES, $EE, $EK, $EQ, $EU, $EV, $EH, $EJ, $EZ, $DS, $EL, $EM, $EN, $EP, $ER, $RC);
    $addition($FF, $FA, $FB, $FC, $FD, $RD);

    if (!$isServi($FF)) {
        $value($FF, 0);
    }

    if ($float($FF) <= $float($ES)) {
        $soustraction($GA, $ES, $FF);
        $value($GB, 0);
    } else {
        $soustraction($GB, $FF, $ES);
        $value($GA, 0);
    }

    $soustraction($JA, $GA, $GB, $HA);
    $soustraction($JB, $HA, $GA);

    if ($float($JA) > 0) {
        $value($JC, 0);
    } else if ($float($JB) > 0) {
        $addition($JC, $GB, $JB);
    } else {
        $addition($JC, $GB, $HA);
    }

    $addition($NB, $LF, $LC, $LD, $LK, $LH, $LM, $RM, $RN, $RG, $RH, $RJ, $RK, $RP, $RQ, $RR, $RS, $RT, $RU, $RV, $RW, $RX, $RY, $RZ);
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

    $assert(!($isServi($DP) && $float($DP) && !(($isServi($FA) && $float($FA) > 0) || ($isServi($FB) && $float($FB) > 0) || ($isServi($FD) && $float($FD) > 0))),
        'erreur_135', $DP, $FA, $FB, $FD);

    $controls['erreur_117']($DP, $EP, 0.021, 0.20);
    $controls['erreur_116']($FG, $FG);

    $assert(!($isServi($MA) && $isServi($MB) && !($float($MB) <= $float($MA))),
        'erreur_131', $MA, $MB);

    $assert($isServi($elt('tva3517bisca12_20190101[AE]-0-0')) || $isServi($elt('tva3517bisca12_20190101[AE]-0-1')),
        'Champ Obligatoire',
        $elt('tva3517bisca12_20190101[AE]-0-0'), $elt('tva3517bisca12_20190101[AE]-0-1'));


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
};

asserts.functions.rcm2777_20190101 = function ($elt,
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

    var $AA = $elt('rcm2777_20190101_AA');
    var $AB = $elt('rcm2777_20190101_AB');
    var $AH = $elt('rcm2777_20190101_AH');
    var $AK = $elt('rcm2777_20190101_AK');
    var $AL = $elt('rcm2777_20190101_AL');
    var $AM = $elt('rcm2777_20190101_AM');
    var $AN = $elt('rcm2777_20190101_AN');
    var $AO = $elt('rcm2777_20190101_AO');
    var $AP = $elt('rcm2777_20190101_AP');
    var $AQ = $elt('rcm2777_20190101_AQ');
    var $AR = $elt('rcm2777_20190101_AR');
    var $AS = $elt('rcm2777_20190101_AS');
    var $AT = $elt('rcm2777_20190101_AT');
    var $AU = $elt('rcm2777_20190101_AU');
    var $AV = $elt('rcm2777_20190101_AV');
    var $BA = $elt('rcm2777_20190101_BA');
    var $BB = $elt('rcm2777_20190101_BB');
    var $BH = $elt('rcm2777_20190101_BH');
    var $BK = $elt('rcm2777_20190101_BK');
    var $BL = $elt('rcm2777_20190101_BL');
    var $BM = $elt('rcm2777_20190101_BM');
    var $BN = $elt('rcm2777_20190101_BN');
    var $BO = $elt('rcm2777_20190101_BO');
    var $BP = $elt('rcm2777_20190101_BP');
    var $BQ = $elt('rcm2777_20190101_BQ');
    var $BR = $elt('rcm2777_20190101_BR');
    var $BS = $elt('rcm2777_20190101_BS');
    var $BT = $elt('rcm2777_20190101_BT');
    var $BU = $elt('rcm2777_20190101_BU');
    var $BV = $elt('rcm2777_20190101_BV');
    var $CA = $elt('rcm2777_20190101_CA');
    var $CC = $elt('rcm2777_20190101_CC');
    var $CE = $elt('rcm2777_20190101_CE');
    var $CG = $elt('rcm2777_20190101_CG');
    var $CI = $elt('rcm2777_20190101_CI');
    var $CJ = $elt('rcm2777_20190101_CJ');
    var $CK = $elt('rcm2777_20190101_CK');
    var $CL = $elt('rcm2777_20190101_CL');
    var $CM = $elt('rcm2777_20190101_CM');
    var $CN = $elt('rcm2777_20190101_CN');
    var $CO = $elt('rcm2777_20190101_CO');
    var $CP = $elt('rcm2777_20190101_CP');
    var $CQ = $elt('rcm2777_20190101_CQ');
    var $CR = $elt('rcm2777_20190101_CR');
    var $CS = $elt('rcm2777_20190101_CS');
    var $CT = $elt('rcm2777_20190101_CT');
    var $CU = $elt('rcm2777_20190101_CU');
    var $CV = $elt('rcm2777_20190101_CV');
    var $CW = $elt('rcm2777_20190101_CW');
    var $CX = $elt('rcm2777_20190101_CX');
    var $CY = $elt('rcm2777_20190101_CY');
    var $CZ = $elt('rcm2777_20190101_CZ');
    var $DA = $elt('rcm2777_20190101_DA');
    var $DC = $elt('rcm2777_20190101_DC');
    var $DE = $elt('rcm2777_20190101_DE');
    var $DG = $elt('rcm2777_20190101_DG');
    var $DI = $elt('rcm2777_20190101_DI');
    var $DJ = $elt('rcm2777_20190101_DJ');
    var $DK = $elt('rcm2777_20190101_DK');
    var $DL = $elt('rcm2777_20190101_DL');
    var $DM = $elt('rcm2777_20190101_DM');
    var $DN = $elt('rcm2777_20190101_DN');
    var $DO = $elt('rcm2777_20190101_DO');
    var $DP = $elt('rcm2777_20190101_DP');
    var $DQ = $elt('rcm2777_20190101_DQ');
    var $DR = $elt('rcm2777_20190101_DR');
    var $DS = $elt('rcm2777_20190101_DS');
    var $DT = $elt('rcm2777_20190101_DT');
    var $DU = $elt('rcm2777_20190101_DU');
    var $DV = $elt('rcm2777_20190101_DV');
    var $DW = $elt('rcm2777_20190101_DW');
    var $DX = $elt('rcm2777_20190101_DX');
    var $DY = $elt('rcm2777_20190101_DY');
    var $DZ = $elt('rcm2777_20190101_DZ');
    var $EA = $elt('rcm2777_20190101_EA');
    var $EB = $elt('rcm2777_20190101_EB');
    var $EC = $elt('rcm2777_20190101_EC');
    var $ED = $elt('rcm2777_20190101_ED');
    var $EE = $elt('rcm2777_20190101_EE');
    var $EG = $elt('rcm2777_20190101_EG');
    var $EH = $elt('rcm2777_20190101_EH');
    var $EI = $elt('rcm2777_20190101_EI');
    var $EJ = $elt('rcm2777_20190101_EJ');
    var $FA = $elt('rcm2777_20190101_FA');
    var $FC = $elt('rcm2777_20190101_FC');
    var $FE = $elt('rcm2777_20190101_FE');
    var $FG = $elt('rcm2777_20190101_FG');
    var $FH = $elt('rcm2777_20190101_FH');
    var $FI = $elt('rcm2777_20190101_FI');
    var $FJ = $elt('rcm2777_20190101_FJ');
    var $FK = $elt('rcm2777_20190101_FK');
    var $FL = $elt('rcm2777_20190101_FL');
    var $FM = $elt('rcm2777_20190101_FM');
    var $FN = $elt('rcm2777_20190101_FN');
    var $FP = $elt('rcm2777_20190101_FP');
    var $FQ = $elt('rcm2777_20190101_FQ');
    var $FR = $elt('rcm2777_20190101_FR');
    var $FS = $elt('rcm2777_20190101_FS');
    var $FT = $elt('rcm2777_20190101_FT');
    var $FU = $elt('rcm2777_20190101_FU');
    var $FV = $elt('rcm2777_20190101_FV');
    var $FX = $elt('rcm2777_20190101_FX');
    var $FY = $elt('rcm2777_20190101_FY');
    var $FZ = $elt('rcm2777_20190101_FZ');
    var $GA = $elt('rcm2777_20190101_GA');
    var $GC = $elt('rcm2777_20190101_GC');
    var $GD = $elt('rcm2777_20190101_GD');
    var $GE = $elt('rcm2777_20190101_GE');
    var $GG = $elt('rcm2777_20190101_GG');
    var $GH = $elt('rcm2777_20190101_GH');
    var $GI = $elt('rcm2777_20190101_GI');
    var $GJ = $elt('rcm2777_20190101_GJ');
    var $GK = $elt('rcm2777_20190101_GK');
    var $GL = $elt('rcm2777_20190101_GL');
    var $GM = $elt('rcm2777_20190101_GM');
    var $GN = $elt('rcm2777_20190101_GN');
    var $GP = $elt('rcm2777_20190101_GP');
    var $GQ = $elt('rcm2777_20190101_GQ');
    var $GR = $elt('rcm2777_20190101_GR');
    var $GS = $elt('rcm2777_20190101_GS');
    var $GT = $elt('rcm2777_20190101_GT');
    var $GU = $elt('rcm2777_20190101_GU');
    var $GV = $elt('rcm2777_20190101_GV');
    var $GX = $elt('rcm2777_20190101_GX');
    var $GY = $elt('rcm2777_20190101_GY');
    var $GZ = $elt('rcm2777_20190101_GZ');
    var $IA = $elt('rcm2777_20190101_IA');
    var $IF = $elt('rcm2777_20190101_IF');
    var $IG = $elt('rcm2777_20190101_IG');
    var $IH = $elt('rcm2777_20190101_IH');
    var $II = $elt('rcm2777_20190101_II');
    var $IJ = $elt('rcm2777_20190101_IJ');
    var $IK = $elt('rcm2777_20190101_IK');
    var $JA = $elt('rcm2777_20190101_JA');
    var $JE = $elt('rcm2777_20190101_JE');
    var $KA = $elt('rcm2777_20190101_KA');
    var $KE = $elt('rcm2777_20190101_KE');
    var $LA = $elt('rcm2777_20190101_LA');
    var $LE = $elt('rcm2777_20190101_LE');
    var $MA = $elt('rcm2777_20190101_MA');
    var $ME = $elt('rcm2777_20190101_ME');
    var $NA = $elt('rcm2777_20190101_NA');
    var $OA = $elt('rcm2777_20190101_OA');
    var $PA = $elt('rcm2777_20190101_PA');
    var $PB = $elt('rcm2777_20190101_PB');
    var $PC = $elt('rcm2777_20190101_PC');
    var $PD = $elt('rcm2777_20190101_PD');
    var $PE = $elt('rcm2777_20190101_PE');
    var $QA = $elt('rcm2777_20190101_QA');
    var $QB = $elt('rcm2777_20190101_QB');
    var $QC = $elt('rcm2777_20190101_QC');
    var $QD = $elt('rcm2777_20190101_QD');
    var $QE = $elt('rcm2777_20190101_QE');
    var $RA = $elt('rcm2777_20190101_RA');
    var $RB = $elt('rcm2777_20190101_RB');
    var $RC = $elt('rcm2777_20190101_RC');
    var $RF = $elt('rcm2777_20190101_RF');
    var $RG = $elt('rcm2777_20190101_RG');
    var $RH = $elt('rcm2777_20190101_RH');
    var $RI = $elt('rcm2777_20190101_RI');
    var $RJ = $elt('rcm2777_20190101_RJ');
    var $RK = $elt('rcm2777_20190101_RK');
    var $RL = $elt('rcm2777_20190101_RL');
    var $RM = $elt('rcm2777_20190101_RM');
    var $RN = $elt('rcm2777_20190101_RN');
    var $RO = $elt('rcm2777_20190101_RO');
    var $RP = $elt('rcm2777_20190101_RP');
    var $RQ = $elt('rcm2777_20190101_RQ');
    var $RR = $elt('rcm2777_20190101_RR');
    var $RS = $elt('rcm2777_20190101_RS');
    var $RT = $elt('rcm2777_20190101_RT');
    var $RU = $elt('rcm2777_20190101_RU');
    var $RV = $elt('rcm2777_20190101_RV');

    var $KF_Identif_month = $elt('p_identif_20151020_KF-month');
    var $KF_Identif = $elt('p_identif_20151020_KF');

    NTD.Identif.t("hidePaiement", []);
    if ($float($EA) > 0) {
        NTD.Identif.t("showPaiement", [$float($EA)]);
    }

    $readonly($AH, true);

    $readonly($BA, false);
    $readonly($BB, true);
    $readonly($BH, true);
    $readonly($BK, true);
    $readonly($BL, true);
    $readonly($BM, true);
    $readonly($BN, true);
    $readonly($BO, true);
    $readonly($BP, true);
    $readonly($BQ, true);
    $readonly($BR, true);
    $readonly($BS, true);
    $readonly($BT, true);
    $readonly($BU, true);
    $readonly($BV, true);

    $readonly($CM, true);
    $readonly($CR, true);
    $readonly($CT, true);

    $readonly($DA, true);
    $readonly($DC, true);
    $readonly($DE, true);
    $readonly($DG, true);
    $readonly($DI, true);
    $readonly($DJ, true);
    $readonly($DK, true);
    $readonly($DL, true);
    $readonly($DM, true);
    $readonly($DN, true);
    $readonly($DO, true);
    $readonly($DP, true);
    $readonly($DQ, true);
    $readonly($DR, true);
    $readonly($DS, true);
    $readonly($DT, true);
    $readonly($DU, true);
    $readonly($DV, true);
    $readonly($DW, true);
    $readonly($DX, true);
    $readonly($DY, true);
    $readonly($DZ, true);

    $readonly($EA, true);
    $readonly($EB, true);
    $readonly($ED, true);
    $readonly($EE, true);
    $readonly($EG, true);
    $readonly($EH, true);
    $readonly($EI, true);
    $readonly($EJ, true);

    $readonly($FA, true);
    $readonly($FC, true);
    $readonly($FE, true);
    $readonly($FG, true);
    $readonly($FP, true);
    $readonly($FX, true);

    $readonly($GA, true);
    $readonly($GC, true);
    $readonly($GD, true);
    $readonly($GE, true);
    $readonly($GG, true);
    $readonly($GH, true);
    $readonly($GI, true);
    $readonly($GJ, true);
    $readonly($GK, true);
    $readonly($GL, true);
    $readonly($GM, true);
    $readonly($GN, true);
    $readonly($GP, true);
    $readonly($GQ, true);
    $readonly($GR, true);
    $readonly($GS, true);
    $readonly($GT, true);
    $readonly($GU, true);
    $readonly($GV, true);
    $readonly($GX, true);

    $readonly($IF, true);
    $readonly($IG, true);
    $readonly($IH, true);

    $readonly($NA, true);

    $readonly($OA, true);

    $readonly($PC, true);

    $readonly($QA, true);
    $readonly($QB, true);
    $readonly($QC, true);
    $readonly($QD, true);
    $readonly($QE, true);

    $readonly($RF, true);
    $readonly($RG, true);
    $readonly($RH, true);
    $readonly($RI, true);
    $readonly($RJ, true);
    $readonly($RK, true);
    $readonly($RL, true);
    $readonly($RM, true);
    $readonly($RN, true);
    $readonly($RO, true);
    $readonly($RP, true);
    $readonly($RR, true);
    $readonly($RS, true);

    $percent($BA, $AA, 12.8);
    $percent($BB, $AB, 12.8);
    $percent($BK, $AK, 5);
    $percent($BL, $AL, 35);
    $percent($BM, $AM, 15);
    $percent($BN, $AN, 7.5);
    $percent($BO, $AO, 45);
    $percent($BP, $AP, 25);
    $percent($BQ, $AQ, 15);
    $percent($BR, $AR, 7.5);
    $percent($BS, $AS, 7.5);
    $percent($BT, $AT, 12.8);
    $percent($BU, $AU, 75);
    $percent($BV, $AV, 75);

    $percent($DA, $CA, 9.9);
    $percent($DC, $CC, 4.5);
    $percent($DE, $CE, 0.3);
    $percent($DG, $CG, 2);
    $percent($DI, $CI, 0.5);
    $percent($DJ, $CJ, 3.4);
    $percent($DK, $CK, 7.5);
    $percent($DL, $CL, 8.2);
    $percent($DN, $CN, 2);
    $percent($DO, $CO, 2.2);
    $percent($DP, $CP, 3.4);
    $percent($DQ, $CQ, 5.4);
    $percent($DS, $CS, 1.1);
    $percent($DU, $CU, 0.5);
    $percent($DV, $CV, 0.5);
    $percent($DW, $CW, 0.5);
    $percent($DX, $CX, 0.5);
    $percent($DY, $CY, 0.5);
    $percent($DZ, $CZ, 0.5);

    $percent($GH, $FH, 15);
    $percent($GI, $FI, 12.8);
    $percent($GJ, $FJ, 75);
    $percent($GK, $FK, 75);
    $percent($GL, $FL, 30);
    $percent($GM, $FM, 15);
    $percent($GN, $FN, 12.8);
    $percent($GQ, $FQ, 5);
    $percent($GR, $FR, 10);
    $percent($GS, $FS, 12);
    $percent($GT, $FT, 12.5);
    $percent($GU, $FU, 15);
    $percent($GV, $FV, 20);

    $percent($QA, $PA, 0.5);
    $percent($QB, $PB, 0.5);
    $percent($QD, $PD, 9.2);
    $percent($QE, $PE, 7.5);

    var $AG_sum = 0;
    var $BG_sum = 0;

    $rowIndex = 1;
    while ($elt('rcm2777_20190101_AG/' + $rowIndex)) {
        var $AG = $elt('rcm2777_20190101_AG/' + $rowIndex);
        var $BG = $elt('rcm2777_20190101_BG/' + $rowIndex);
        var $HB = $elt('rcm2777_20190101_HB/' + $rowIndex);

        $readonly($BG, true);

        if (!$isServi($AG)) {
            $value($AG, 0);
        }

        if (!$isServi($HB)) {
            $value($HB, 0);
        }

        $assert(!($float($AG) > 0 && $float($HB) == 0),
            'rcm2777_01',
            $AG, $HB);

        $assert(!($float($AG) == 0 && $float($HB) > 0),
            'rcm2777_21',
            $AG, $HB);

        $assert(!($float($HB) > 0 && ($float($HB) > 75)),
            'rcm2777_02',
            $HB);

        $percent($BG, $AG, $float($HB));

        $AG_sum += $float($AG) ? $float($AG) : 0;
        $BG_sum += $float($BG) ? $float($BG) : 0;

        $rowIndex++;
    }
    $value($AH, $AG_sum);
    $value($BH, $BG_sum);


    var $FAValue = ($float($JA) + $float($KA)) - ($float($LA) + $float($MA));
    $FAValue > 0 ? $value($FA, $FAValue) : $value($FA, 0);

    $percent($GA, $FA, 30);

    var $FBValue = $GBValue = $FCValue = $GCValue = 0;

    $rowIndex = 1;
    while ($elt('rcm2777_20190101_JB/' + $rowIndex)) {
        var $JB = $elt('rcm2777_20190101_JB/' + $rowIndex);
        var $KB = $elt('rcm2777_20190101_KB/' + $rowIndex);
        var $LB = $elt('rcm2777_20190101_LB/' + $rowIndex);
        var $MB = $elt('rcm2777_20190101_MB/' + $rowIndex);
        var $FB = $elt('rcm2777_20190101_FB/' + $rowIndex);
        var $HA = $elt('rcm2777_20190101_HA/' + $rowIndex);
        var $GB = $elt('rcm2777_20190101_GB/' + $rowIndex);

        if (!$isServi($JB)) {
            $value($JB, 0);
        }

        if (!$isServi($KB)) {
            $value($KB, 0);
        }

        if (!$isServi($LB)) {
            $value($LB, 0);
        }

        if (!$isServi($MB)) {
            $value($MB, 0);
        }

        if (!$isServi($FB)) {
            $value($FB, 0);
        }

        if (!$isServi($HA)) {
            $value($HA, 0);
        }

        $readonly($FB, true);
        $readonly($GB, true);


        $assert(!($float($HA) > 0 && ($float($HA) > 100)),
            'rcm2777_03',
            $HA);

        $FBValue = ($float($JB) + $float($KB)) - ($float($MB) + $float($LB));

        $FBValue > 0 ? $value($FB, $FBValue) : $value($FB, 0);

        $assert(!($float($FB) > 0 && $float($HA) == 0),
            'rcm2777_01',
            $FB, $HA);

        $assert(!($float($FB) == 0 && $float($HA) > 0),
            'rcm2777_21',
            $FB, $HA);

        $percent($GB, $FB, $float($HA));

        $FCValue += $float($FB) ? $float($FB) : 0;
        $GCValue += $float($GB) ? $float($GB) : 0;

        $rowIndex++;
    }

    $value($FC, $FCValue);
    $value($GC, $GCValue);

    var $FEValue = ($float($JE) + $float($KE)) - ($float($LE) + $float($ME));
    $FEValue > 0 ? $value($FE, $FEValue) : $value($FE, 0);

    $percent($GE, $FE, 12.8);

    var $FFValue = $GFValue = $FGValue = $GGValue = 0;

    $rowIndex = 1;
    while ($elt('rcm2777_20190101_JF/' + $rowIndex)) {
        var $JF = $elt('rcm2777_20190101_JF/' + $rowIndex);
        var $KF = $elt('rcm2777_20190101_KF/' + $rowIndex);
        var $LF = $elt('rcm2777_20190101_LF/' + $rowIndex);
        var $MF = $elt('rcm2777_20190101_MF/' + $rowIndex);
        var $FF = $elt('rcm2777_20190101_FF/' + $rowIndex);
        var $HC = $elt('rcm2777_20190101_HC/' + $rowIndex);
        var $GF = $elt('rcm2777_20190101_GF/' + $rowIndex);

        if (!$isServi($JF)) {
            $value($JF, 0);
        }

        if (!$isServi($KF)) {
            $value($KF, 0);
        }

        if (!$isServi($LF)) {
            $value($LF, 0);
        }

        if (!$isServi($MF)) {
            $value($MF, 0);
        }

        if (!$isServi($FF)) {
            $value($FF, 0);
        }

        if (!$isServi($HC)) {
            $value($HC, 0);
        }

        $readonly($FF, true);
        $readonly($GF, true);

        $FFValue = ($float($JF) + $float($KF)) - ($float($MF) + $float($LF));

        $FFValue > 0 ? $value($FF, $FFValue) : $value($FF, 0);

        $assert(!($float($FF) > 0 && $float($HC) == 0),
            'rcm2777_01',
            $FF, $HC);

        $assert(!($float($FF) == 0 && $float($HC) > 0),
            'rcm2777_21',
            $FF, $HC);

        $assert(!($float($HC) > 0 && ($float($HC) > 100)),
            'rcm2777_03',
            $HC);
        $percent($GF, $FF, $float($HC));

        $FGValue += $float($FF) ? $float($FF) : 0;
        $GGValue += $float($GF) ? $float($GF) : 0;

        $rowIndex++;
    }

    $value($FG, $FGValue);
    $value($GG, $GGValue);

    var $FPValue = $GPValue = 0;

    $rowIndex = 1;
    while ($elt('rcm2777_20190101_FO/' + $rowIndex)) {
        var $FO = $elt('rcm2777_20190101_FO/' + $rowIndex);
        var $HD = $elt('rcm2777_20190101_HD/' + $rowIndex);
        var $GO = $elt('rcm2777_20190101_GO/' + $rowIndex);

        if (!$isServi($FO)) {
            $value($FO, 0);
        }

        if (!$isServi($HD)) {
            $value($HD, 0);
        }

        if (!$isServi($GO)) {
            $value($GO, 0);
        }

        $readonly($GO, true);

        $assert(!($float($FO) > 0 && $float($HD) == 0),
            'rcm2777_01',
            $FO, $HD);

        $assert(!($float($FO) == 0 && $float($HD) > 0),
            'rcm2777_21',
            $FO, $HD);

        $assert(!($float($HD) > 0 && ($float($HD) > 100)),
            'rcm2777_03',
            $HD);

        $percent($GO, $FO, $float($HD));

        $FPValue += $float($FO) ? $float($FO) : 0;
        $GPValue += $float($GO) ? $float($GO) : 0;

        $rowIndex++;
    }

    $value($FP, $FPValue);
    $value($GP, $GPValue);


    var $FXValue = $GXValue = 0;

    $rowIndex = 1;
    while ($elt('rcm2777_20190101_FW/' + $rowIndex)) {
        var $FW = $elt('rcm2777_20190101_FW/' + $rowIndex);
        var $HE = $elt('rcm2777_20190101_HE/' + $rowIndex);
        var $GW = $elt('rcm2777_20190101_GW/' + $rowIndex);

        if (!$isServi($FW)) {
            $value($FW, 0);
        }

        if (!$isServi($HE)) {
            $value($HE, 0);
        }

        if (!$isServi($GW)) {
            $value($GW, 0);
        }

        $readonly($GW, true);

        $assert(!($float($FW) > 0 && $float($HE) == 0),
            'rcm2777_01',
            $FW, $HE);

        $assert(!($float($FW) == 0 && $float($HE) > 0),
            'rcm2777_21',
            $FW, $HE);

        $assert(!($float($HE) > 0 && ($float($HE) > 100)),
            'rcm2777_03',
            $HE);

        $percent($GW, $FW, $float($HE));

        $FXValue += $float($FW) ? $float($FW) : 0;
        $GXValue += $float($GW) ? $float($GW) : 0;

        $rowIndex++;
    }

    $value($FX, $FXValue);
    $value($GX, $GXValue);


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
        $NA, $FJ, $FK, $FK, $FL, $FM, $FN, $FP, $FQ, $FR, $FS, $FT, $FU, $FV, $FX);

    $assert(!($float($OA) > 0 && ($float($OA) != $float($GJ) + $float($GK) + $float($GL) + $float($GM) + $float($GN) + $float($GP) + $float($GQ) + $float($GR) + $float($GS) + $float($GT) + $float($GU) + $float($GV) + $float($GX))),
        'rcm2777_24',
        $OA, $GJ, $GK, $GL, $GM, $GN, $GP, $GQ, $GR, $GS, $GT, $GU, $GV, $GX);

    $addition($GD, $GG, $GE, $GC, $GA);
    $addition($CM, $CJ, $CK, $CL, $CA, $PD);
    $addition($DM, $DJ, $DK, $DL, $DA, $QD);
    $addition($CR, $CN, $CO, $CP, $CQ, $CC);
    $addition($DR, $DN, $DO, $DP, $DQ, $DC);
    $addition($CT, $CS, $CG, $PE);
    $addition($DT, $DS, $DG, $QE);
    $addition($PC, $CU, $CV, $CI, $CW, $CX, $CY, $CZ, $PA, $PB);
    $addition($QC, $DU, $DV, $DI, $DW, $DX, $DY, $DZ, $QA, $QB);
    $addition($NA, $FY, $FZ);
    $addition($OA, $GY, $GZ);
    $addition($EG, $AB, $AV, $AK, $AL, $AM, $AN, $AO, $AP, $AQ, $AR, $AS, $AT, $AU, $AA, $AH, $FA, $FE, $FC, $FG, $FH, $FI, $NA);
    $addition($EH, $BB, $BV, $BK, $BL, $BM, $BN, $BO, $BP, $BQ, $BR, $BS, $BT, $BU, $BA, $BH, $GD, $GH, $GI, $OA);

    $assert(!($float($IA) > 0 && $value($KF_Identif_month) == 2),
        'rcm2777_08',
        $IA);

    $rowIndex = 1;

    var $dateKF = new Date($value($KF_Identif).replace(/(..).(....)/, "$2-$1"));

    var $IFValue = $IGValue = $IHValue = 0;

    while ($elt('rcm2777_20190101_IB/' + $rowIndex)) {
        var $IB = $elt('rcm2777_20190101_IB/' + $rowIndex);
        var $IC = $elt('rcm2777_20190101_IC/' + $rowIndex);
        var $ID = $elt('rcm2777_20190101_ID/' + $rowIndex);
        var $IE = $elt('rcm2777_20190101_IE/' + $rowIndex);

        if (!$isServi($IC)) {
            $value($IC, 0);
        }

        if (!$isServi($ID)) {
            $value($ID, 0);
        }

        if (!$isServi($IE)) {
            $value($IE, 0);
        }

        $readonly($IE, true);

        var $dateIB = new Date($value($IB).replace(/(..).(....)/, "$2-$1"));

        $assert(!($dateKF < $dateIB),
            'rcm2777_09',
            $IB, $KF_Identif);

        $addition($IE, $IC, $ID);

        $assert(!($isServi($IB) && $float($IE) == 0),
            'rcm2777_10',
            $IB, $IE);

        $assert(!($float($IE) > 0 && !$isServi($IB)),
            'rcm2777_20',
            $IE, $IB);
        $rowIndex++;

        $IFValue += $float($IC);
        $IGValue += $float($ID);
        $IHValue += $float($IE);
    }

    $value($IF, $IFValue);
    $value($IG, $IGValue);
    $value($IH, $IHValue);

    var $EIValue = $EJValue = 0;
    if (($float($EH) + $float($IK)) >= ($float($IA) + $float($IH) + $float($II) + $float($IJ))) {
        $EIValue = $float($EH) + $float($IK) - ($float($IA) + $float($IH) + $float($II) + $float($IJ));
    } else {
        $EJValue = ($float($IA) + $float($IH) + $float($II) + $float($IJ)) - $float($EH) - $float($IK);
    }
    $value($EI, $EIValue);
    $value($EJ, $EJValue);

    //Verifications mois d'imposition

    //September
    var $isSeptember = false;
    if ($value($KF_Identif_month) == 10) {
        $isSeptember = true;
    }

    $assert(!($float($RC) > 0 && !$isSeptember),
        'rcm2777_11',
        $RC);

    if ($isSeptember) {
        $percent($RF, $RC, 90);
    }

    $assert(!($float($RF) > 0 && !$isSeptember),
        'rcm2777_12',
        $RF);

    $assert(!($float($RA) > 0 && !$isSeptember),
        'rcm2777_11',
        $RA);

    if ($isSeptember && ($float($RA) > 0 || $float($RA) === 0)) {
        var $RGValue = $float($RA) * (90 / 100) * (17.2 / 100);
        $value($RG, Math.round($RGValue));
    }

    $assert(!($float($RG) > 0 && !$isSeptember),
        'rcm2777_12',
        $RG);

    $assert(!($float($RB) > 0 && !$isSeptember),
        'rcm2777_11',
        $RB);

    if ($isSeptember && ($float($RB) > 0 || $float($RB) === 0)) {
        var $RHValue = $float($RB) * (90 / 100) * (17.2 / 100);
        $value($RH, Math.round($RHValue));
    }

    $assert(!($float($RH) > 0 && !$isSeptember),
        'rcm2777_12',
        $RH);

    //December
    var $isDecember = false;
    if ($value($KF_Identif_month) == 1) {
        $isDecember = true;
    }
    $assert(!($float($RT) > 0 && !$isDecember),
        'rcm2777_13',
        $RT);
    $assert(!($float($RU) > 0 && !$isDecember),
        'rcm2777_13',
        $RU);

    var $RIValue = 0;
    if ($isDecember) {
        $RIValue = Math.round(($float($EI) - $float($EJ) + ($float($DR) + $float($DE) + $float($DT)) - $float($RT) - (7.5 / 17.2 * ($float($RU)))));
        $RIValue = $RIValue > 0 ? $RIValue : 0;
    }
    $value($RI, $RIValue);
    $assert(!($float($RI) > 0 && !$isDecember),
        'rcm2777_14',
        $RI);

    var $RJValue = 0;
    if ($isDecember) {
        $RJValue = Math.round((-1 * ($float($EI) - $float($EJ) + ($float($DR) + $float($DE) + $float($DT)) - $float($RT) - (7.5 / 17.2 * ($float($RU))))));
        $RJValue = $RJValue > 0 ? $RJValue : 0;
    }
    $value($RJ, $RJValue);
    $assert(!($float($RJ) > 0 && !$isDecember),
        'rcm2777_14',
        $RJ);

    var $RKValue = 0;
    if ($isDecember) {
        $RKValue = Math.round(($float($DM) + $float($QC) - (9.7 / 17.2 * ($float($RU)))));
        $RKValue = $RKValue > 0 ? $RKValue : 0;
    }
    $value($RK, $RKValue);
    $assert(!($float($RK) > 0 && !$isDecember),
        'rcm2777_14',
        $RK);

    var $RLValue = 0;
    if ($isDecember) {
        $RLValue = Math.round((-1 * ($float($DM) + $float($QC) - (9.7 / 17.2 * ($float($RU))))));
        $RLValue = $RLValue > 0 ? $RLValue : 0;
    }
    $value($RL, $RLValue);
    $assert(!($float($RL) > 0 && !$isDecember),
        'rcm2777_14',
        $RL);

    var $RMValue = 0;
    if ($isDecember) {
        $RMValue = ($float($RI) - $float($RJ) + $float($RK) - $float($RL));
        $RMValue = $RMValue > 0 ? $RMValue : 0;
    }
    $value($RM, $RMValue);
    $assert(!($float($RM) > 0 && !$isDecember),
        'rcm2777_14',
        $RM);

    var $RNValue = 0;
    if ($isDecember) {
        $RNValue = (-1 * ($float($RI) - $float($RJ) + $float($RK) - $float($RL)));
        $RNValue = $RNValue > 0 ? $RNValue : 0;
    }
    $value($RN, $RNValue);
    $assert(!($float($RN) > 0 && !$isDecember),
        'rcm2777_14',
        $RN);

    //January
    var $isJanuary = false;
    if ($value($KF_Identif_month) == 2) {
        $isJanuary = true;
    }
    $assert(!($float($RV) > 0 && !$isJanuary),
        'rcm2777_15',
        $RV);

    var $ROValue = 0;
    if ($isJanuary) {
        $ROValue = Math.round(($float($DM) + $float($QC) - (15.2 / 17.2 * $float($RV))));
        $ROValue = $ROValue > 0 ? $ROValue : 0;
    }
    $value($RO, $ROValue);
    $assert(!($float($RO) > 0 && !$isJanuary),
        'rcm2777_16',
        $RO);

    var $RPValue = 0;
    if ($isJanuary) {
        $RPValue = Math.round((-1 * ($float($DM) + $float($QC) - (15.2 / 17.2 * $float($RV)))));
        $RPValue = $RPValue > 0 ? $RPValue : 0;
    }
    $value($RP, $RPValue);
    $assert(!($float($RP) > 0 && !$isJanuary),
        'rcm2777_16',
        $RP);

    $assert(!($float($RQ) > 0 && !$isJanuary),
        'rcm2777_17',
        $RQ);

    var $RRValue = 0;
    if ($isJanuary) {
        $RRValue = Math.round(($float($EI) - $float($EJ) + ($float($DR) + $float($DE) + $float($DT)) + ($float($RO) - $float($RP)) - $float($RQ) - (2 / 17.2 * $float($RV))));
        $RRValue = $RRValue > 0 ? $RRValue : 0;
    }
    $value($RR, $RRValue);
    $assert(!($float($RR) > 0 && !$isJanuary),
        'rcm2777_16',
        $RR);

    var $RSValue = 0;
    if ($isJanuary) {
        $RSValue = Math.round((-1 * ($float($EI) - $float($EJ) + ($float($DR) + $float($DE) + $float($DT)) + ($float($RO) - $float($RP)) - $float($RQ) - (2 / 17.2 * $float($RV)))));
        $RSValue = $RSValue > 0 ? $RSValue : 0;
    }
    $value($RS, $RSValue);
    $assert(!($float($RS) > 0 && !$isJanuary),
        'rcm2777_16',
        $RS);

    //Total
    var $EAValue = $EBValue = 0;
    if ($isDecember) {
        $EAValue = $float($RM) - $float($RN);
        $EBValue = (-1 * ($float($RM) - $float($RN)));
    } else if ($isJanuary) {
        $EAValue = $float($RR) - $float($RS);
        $EBValue = (-1 * ($float($RR) - $float($RS)));
    } else if ($isSeptember) {
        if ($float($EJ) <= $float($DR) + $float($DE) + $float($DT)) {
            $EAValue = $float($EI) - $float($EJ) + $float($DM) + $float($DR) + $float($DE) + $float($DT) + $float($QC) + $float($RF) + $float($RG) + $float($RH);
            $EBValue = 0;
        } else {
            $EAValue = $float($DM) + $float($QC) + $float($RF) + $float($RG) + $float($RH);
            $EBValue = $float($EJ) - $float($DR) - $float($DE) - $float($DT);
        }
    } else { // February - Mars - Avril - May - Juin - Juin - Aout - Octobre - Novembre
        if ($float($EJ) <= $float($DR) + $float($DE) + $float($DT)) {
            $EAValue = $float($EI) - $float($EJ) + $float($DM) + $float($DR) + $float($DE) + $float($DT) + $float($QC);
            $EBValue = 0;
        } else {
            $EAValue = $float($DM) + $float($QC);
            $EBValue = $float($EJ) - $float($DR) - $float($DE) - $float($DT);
        }
    }

    $EAValue = $EAValue > 0 ? $EAValue : 0;
    $EBValue = $EBValue > 0 ? $EBValue : 0;

    $value($EA, $EAValue);
    $value($EB, $EBValue);

    $assert(!($isServi($EC) && $float($EB) == 0),
        'rcm2777_18',
        $EC, $EB);

    $assert(!(($float($EB) > 0 && $isJanuary) && !$isServi($EC)),
        'rcm2777_19',
        $EB, $EC);

    if ($isServi($EC)) {
        $value($ED, $float($EB));
        $value($EE, 0);
    }

    if (!$isServi($EC)) {
        $value($EE, $float($EB));
        $value($ED, 0);
    }
};

asserts.functions.is2571_2019 = function($elt,
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

    var $CA = $elt('is2571_2019_CA');
    var $CC = $elt('is2571_2019_CC');
    var $CD = $elt('is2571_2019_CD');
    var $CE = $elt('is2571_2019_CE');
    var $CH = $elt('is2571_2019_CH');
    var $CL = $elt('is2571_2019_CL');
    var $CM = $elt('is2571_2019_CM');
    var $CN = $elt('is2571_2019_CN');
    var $DA = $elt('is2571_2019_DA');
    var $DB = $elt('is2571_2019_DB');
    var $FA = $elt('is2571_2019_FA');
    var $FB = $elt('is2571_2019_FB');
    var $FC = $elt('is2571_2019_FC');
    var $FD = $elt('is2571_2019_FD');
    var $FE = $elt('is2571_2019_FE');
    var $FF = $elt('is2571_2019_FF');
    var $FG = $elt('is2571_2019_FG');
    var $FH = $elt('is2571_2019_FH');
    var $FK = $elt('is2571_2019_FK');
    var $FM = $elt('is2571_2019_FM');
    var $FN = $elt('is2571_2019_FN');

    $readonly($CE, true);
    $addition($CE, $CA, $CC, $CD, $CM);
    $readonly($CH, true);
    $addition($CH, $CE, $CN, $CL);
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

    $assert(!($isServi($CM)), 'erreur_324', $CM);
    $assert(!($isServi($CN)), 'erreur_324', $CN);

    var $PidentifKF = $elt(NTD.Identif.pField('KF'));
    var $date_FM = $value($FM).split('/');
    $date_FM = new Date($date_FM[2], $date_FM[1] - 1, $date_FM[0]);
    var $date_KF = $value($PidentifKF).split('/');
    $date_KF = new Date($date_KF[1], $date_KF[0] - 1, '01');
    var $date_KF_inf_dateFM = $date_FM.getTime() < $date_KF.getTime();

    $assert(!($isServi($FM) && $isServi($PidentifKF) && !($date_KF_inf_dateFM)), 'erreur_312', $FM);
};

asserts.functions.is2572_2019 = function($elt,
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

    var $AD = $elt('is2572_2019_AD');
    var $BD = $elt('is2572_2019_BD');
    var $CA = $elt('is2572_2019_CA');
    var $DA = $elt('is2572_2019_DA');
    var $EA = $elt('is2572_2019_EA');
    var $EB = $elt('is2572_2019_EB');
    var $GC = $elt('is2572_2019_GC');
    var $GD = $elt('is2572_2019_GD');
    var $GE = $elt('is2572_2019_GE');
    var $IA = $elt('is2572_2019_IA');
    var $JA = $elt('is2572_2019_JA');
    var $KA = $elt('is2572_2019_KA');
    var $KB = $elt('is2572_2019_KB');
    var $KC = $elt('is2572_2019_KC');
    var $KD = $elt('is2572_2019_KD');
    var $LA = $elt('is2572_2019_LA');
    var $LB = $elt('is2572_2019_LB');
    var $LC = $elt('is2572_2019_LC');
    var $LD = $elt('is2572_2019_LD');
    var $LE = $elt('is2572_2019_LE');
    var $LF = $elt('is2572_2019_LF');
    var $MA = $elt('is2572_2019_MA');
    var $MB = $elt('is2572_2019_MB');
    var $MD = $elt('is2572_2019_MD');
    var $MH = $elt('is2572_2019_MH');
    var $NA = $elt('is2572_2019_NA');
    var $NB = $elt('is2572_2019_NB');
    var $ND = $elt('is2572_2019_ND');
    var $NE = $elt('is2572_2019_NE');
    var $NF = $elt('is2572_2019_NF');
    var $NG = $elt('is2572_2019_NG');
    var $NJ = $elt('is2572_2019_NJ');
    var $NK = $elt('is2572_2019_NK');
    var $NM = $elt('is2572_2019_NM');
    var $NN = $elt('is2572_2019_NN');
    var $NO = $elt('is2572_2019_NO');
    var $OB = $elt('is2572_2019_OB');
    var $OC = $elt('is2572_2019_OC');
    var $OD = $elt('is2572_2019_OD');
    var $OE = $elt('is2572_2019_OE');
    var $OF = $elt('is2572_2019_OF');
    var $OG = $elt('is2572_2019_OG');
    var $OH = $elt('is2572_2019_OH');
    var $OJ = $elt('is2572_2019_OJ');
    var $OK = $elt('is2572_2019_OK');
    var $PA = $elt('is2572_2019_PA');
    var $PB = $elt('is2572_2019_PB');
    var $PC = $elt('is2572_2019_PC');
    var $PD = $elt('is2572_2019_PD');
    var $PE = $elt('is2572_2019_PE');
    var $PF = $elt('is2572_2019_PF');
    var $PG = $elt('is2572_2019_PG');
    var $PH = $elt('is2572_2019_PH');
    var $PJ = $elt('is2572_2019_PJ');
    var $PK = $elt('is2572_2019_PK');
    var $PL = $elt('is2572_2019_PL');
    var $PM = $elt('is2572_2019_PM');
    var $PN = $elt('is2572_2019_PN');
    var $PQ = $elt('is2572_2019_PQ');
    var $PT = $elt('is2572_2019_PT');
    var $PU = $elt('is2572_2019_PU');
    var $PV = $elt('is2572_2019_PV');
    var $PW = $elt('is2572_2019_PW');
    var $RA = $elt('is2572_2019_RA');
    var $RB = $elt('is2572_2019_RB');
    var $RC = $elt('is2572_2019_RC');
    var $RD = $elt('is2572_2019_RD');
    var $RE = $elt('is2572_2019_RE');
    var $RF = $elt('is2572_2019_RF');
    var $RG = $elt('is2572_2019_RG');
    var $RH = $elt('is2572_2019_RH');
    var $RJ = $elt('is2572_2019_RJ');
    var $RK = $elt('is2572_2019_RK');
    var $RL = $elt('is2572_2019_RL');
    var $RM = $elt('is2572_2019_RM');
    var $RN = $elt('is2572_2019_RN');
    var $RP = $elt('is2572_2019_RP');
    var $RR = $elt('is2572_2019_RR');
    var $RS = $elt('is2572_2019_RS');
    var $RT = $elt('is2572_2019_RT');
    var $RW = $elt('is2572_2019_RW');
    var $RZ = $elt('is2572_2019_RZ');
    var $SA = $elt('is2572_2019_SA');
    var $TA = $elt('is2572_2019_TA');
    var $TB = $elt('is2572_2019_TB');
    var $TC = $elt('is2572_2019_TC');

    $readonly($TA, true);
    $percent($TA, $RA, 100 / 3);

    $readonly($TB, true);
    $percent($TB, $RB, 15);

    $readonly($TC, true);
    $percent($TC, $SA, 28);

    $readonly($GE, true);
    $addition($GE, $TA, $TB, $TC, $GC, $GD);

    $readonly($RG, true);
    $addition($RG, $JA, $MA, $MD, $MH);

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
    var REFIelds = [$KA, $KB, $KC, $KD, $NA, $NB, $ND, $NE, $NF, $NG, $NJ, $NK, $NM, $NN, $NO, $OD, $OF, $RC];
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

    if ($isServi($OK) && $float($OK) >= 0) {
        if (RETotal === '') {
            RETotal = 0;
        }
        var value = $float($OK);
        value = isNaN(value) ? 0 : value;
        RETotal += value;
    }

    $value($RE, (RETotal === '') ? '' : Math.max(0, RETotal));


    $readonly($RS, true);
    $soustraction($RS, $RH, $RP);

    $readonly($RF, true);
    $soustraction($RF, $RS, $RE);

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

    $readonly($PT, true);
    $soustraction($PT, $PA, $PB);

    $readonly($PU, true);
    $soustraction($PU, $PB, $PA);

    $readonly($PV, true);
    $soustraction($PV, $PM, $PD);

    $readonly($PW, true);
    $soustraction($PW, $PD, $PM);

    $readonly($AD, true);
    $addition($AD, $PN, $PT, $PV);

    $readonly($BD, true);
    $addition($BD, $PQ, $PU, $PW);

    $readonly($CA, false);
    $soustraction($CA, $AD, $BD);

    $readonly($DA, true);
    $soustraction($DA, $BD, $AD);

    $readonly($PL, true);
    $soustraction($PL, $CA, $PK);

    $readonly($EB, true);
    $soustraction($EB, $DA, $EA, $PG);


    NTD.Identif.p("hidePaiement", []);
    if ($isServi($PL) && $float($PL) > 0) {
        NTD.Identif.p("showPaiement", [$float($PL)]);
    }

    var $PidentifKF = $elt(NTD.Identif.pField('KF'));
    var $date_PJ = $value($PJ).split('/');
    $date_PJ = new Date($date_PJ[2], $date_PJ[1] - 1, $date_PJ[0]);
    var $date_KF = $value($PidentifKF).split('/');
    $date_KF = new Date($date_KF[1], $date_KF[0] - 1, '01');
    var $date_KF_inf_datePJ = $date_PJ.getTime() < $date_KF.getTime();

    /*assert(!($isServi($PJ) && $isServi($PidentifKF) && !($date_KF_inf_datePJ)), 'erreur_318', $PJ);
    $isServi_PH_PK_PJ = ( $isServi($PH) && (!$isServi($PK) || !$isServi($PJ)) )
        || ( $isServi($PK) && (!$isServi($PH) || !$isServi($PJ)) )
        || ( $isServi($PJ) && (!$isServi($PH) || !$isServi($PK)) );
    $assert(!$isServi_PH_PK_PJ, 'erreur_310', $PH, $PK, $PJ);
    */

    //$assert(!($isServi($PJ) && $isServi($PidentifKF) && !($date_KF_inf_datePJ)), 'erreur_318', $PJ);

    $isServi_PH_PK_PJ = ( $isServi($PH) && (!$isServi($PK) || !$isServi($PJ)) )
        || ( $isServi($PK) && (!$isServi($PH) || !$isServi($PJ)) )
        || ( $isServi($PJ) && (!$isServi($PH) || !$isServi($PK)) );

    $assert(!$isServi_PH_PK_PJ, 'erreur_310', $PH, $PK);

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

    var $LE_value = isNaN($value($LE)) ? '' : $float($LE);
    var $LF_value = isNaN($value($LF)) ? '' : $float($LF);
    $assert(!( ($isServi($LE) && !$isServi($LF)) || ( ($isServi($LE) && $isServi($LF)) && ($LE_value == '' || $LF_value == '')) ),
        'erreur_322', $LE, $LF);

    var $OJ_value = isNaN($value($OJ)) ? '' : $float($OJ);
    var $OH_value = isNaN($value($OH)) ? '' : $float($OH);
    $assert(!( ($isServi($OJ) && !$isServi($OH)) || ( ($isServi($OJ) && $isServi($OH)) && ($OJ_value == '' || $OH_value == '')) ),
        'erreur_322', $OJ, $OH);

    var $OE_value = isNaN($value($OE)) ? '' : $float($OE);
    var $KD_value = isNaN($value($KD)) ? '' : $float($KD);
    $assert(!( ($isServi($OE) && !$isServi($KD)) || ( ($isServi($OE) && $isServi($KD)) && ($OE_value == '' || $KD_value == '')) ),
        'erreur_322', $OE, $KD);

    var $OG_value = isNaN($value($OG)) ? '' : $float($OG);
    var $OF_value = isNaN($value($OF)) ? '' : $float($OF);
    $assert(!( ($isServi($OG) && !$isServi($OF)) || ( ($isServi($OG) && $isServi($OF)) && ($OG_value == '' || $OF_value == '')) ),
        'erreur_322', $OG, $OF);


    var $CA = $elt(NTD.Identif.pField('CA'));
    var $CB = $elt(NTD.Identif.pField('CB'));
    var $valid_CB = false;

    var $CA_date = moment($value($CA), 'DD/MM/YYYY');
    var $CB_date = moment($value($CB), 'DD/MM/YYYY');
    var $month_diff = $CB_date.diff($CA_date, 'months', true);

    if ($CB_date.format('DD/MM') == '31/12' && $month_diff > 12) {
        $valid_CB = true;
    }

    $assert(!( ($isServi($OJ) || $isServi($OH)) && !$valid_CB),
        'erreur_323', $OJ, $OH);
};


asserts.functions.is2573_2019 = function($elt,
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

    var $AA = $elt('is2573_2019_AA');
    var $AJ = $elt('is2573_2019_AJ');
    var $BA = $elt('is2573_2019_BA');
    var $BF = $elt('is2573_2019_BF');
    var $CA = $elt('is2573_2019_CA');
    var $CG = $elt('is2573_2019_CG');
    var $rowIndex;

    NTD.Identif.p("hidePaiement", []);

    var AJ_value = 0;
    var BF_value = 0;
    var CG_value = 0;

    $readonly($AJ);
    $readonly($BF);
    $readonly($CG);

    $assert($isSiren($BA), 'Vous devez saisir un SIREN valide', $BA);
    $assert($isSiren($CA), 'Vous devez saisir un SIREN valide', $CA);

    // for each row
    $rowIndex = 1;
    while ($elt('is2573_2019_AB/' + $rowIndex)) {
        var $AB = $elt('is2573_2019_AB/' + $rowIndex);
        var $AC = $elt('is2573_2019_AC/' + $rowIndex);
        var $AF = $elt('is2573_2019_AF/' + $rowIndex);
        var $AG = $elt('is2573_2019_AG/' + $rowIndex);
        var $AH = $elt('is2573_2019_AH/' + $rowIndex);
        var $AI = $elt('is2573_2019_AI/' + $rowIndex);
        var $KA = $elt('is2573_2019_KA/' + $rowIndex);
        var $KB = $elt('is2573_2019_KB/' + $rowIndex);
        var $KC = $elt('is2573_2019_KC/' + $rowIndex);
        var $KD = $elt('is2573_2019_KD/' + $rowIndex);

        AJ_value += $isServi($AG) ? $float($AG) : 0;

        $assert($value($AB) != 'REL' && $value($AB) != 'RES', 'erreur_325', $AB, $AC);

        if ($value($AB) == 'EXP' || $value($AB) == 'CAI') {
            $assert(!($value($AC) >= '2018'), 'erreur_325', $AB, $AC)
        }

        $assert($value($AB) != 'REL' && $value($AB) != 'RES', 'erreur_309', $AB);


        $assert(!($isServi($BA) && !($value($AB) == 'RAD' && $isServi($AH))), 'erreur_313', $AF, $AB, $AH);

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

    $value($AJ, AJ_value);


    // for each row
    $rowIndex = 1;
    while ($elt('is2573_2019_BB/' + $rowIndex)) {
        var $BB = $elt('is2573_2019_BB/' + $rowIndex);
        var $BC = $elt('is2573_2019_BC/' + $rowIndex);
        var $BD = $elt('is2573_2019_BD/' + $rowIndex);
        var $BE = $elt('is2573_2019_BE/' + $rowIndex);

        BF_value += $isServi($BE) ? $float($BE) : 0;
        $assert(!($isServi($BD) && $value($BD).length != 9), 'Vous devez saisir un SIREN valide', $BD);

        $assert(!(($isServi($BB) || $isServi($BC) || $isServi($BD) || $isServi($BE))
            && !($isServi($BB) && $isServi($BC) && $isServi($BE) && $float($BE) > 0)),
            'erreur_307', $BB, $BC, $BD, $BE);
        $rowIndex++;
    }

    $value($BF, BF_value);

    // for each row
    $rowIndex = 1;
    while ($elt('is2573_2019_CB/' + $rowIndex)) {
        var $CB = $elt('is2573_2019_CB/' + $rowIndex);
        var $CC = $elt('is2573_2019_CC/' + $rowIndex);
        var $CD = $elt('is2573_2019_CD/' + $rowIndex);
        var $CE = $elt('is2573_2019_CE/' + $rowIndex);
        var $CF = $elt('is2573_2019_CF/' + $rowIndex);

        CG_value += $isServi($CF) ? $float($CF) : 0;
        $assert(!($isServi($CE) && $value($CE).length != 9), 'Vous devez saisir un SIREN valide', $CE);

        $assert(!(($isServi($CB) || $isServi($CC) || $isServi($CD) || $isServi($CE) || $isServi($CF))
            && !($isServi($CB) && $isServi($CC) && $isServi($CD) && $isServi($CF) && $float($CF) > 0)),
            'erreur_308', $CB, $CC, $CD, $CF);
        $rowIndex++;
    }

    $value($CG, CG_value);
};

asserts.functions.cvae1329ac_20190101 = function($elt,
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
    var $AA = $elt('cvae1329ac_20190101_AA');
    var $AB = $elt('cvae1329ac_20190101_AB');
    var $AC = $elt('cvae1329ac_20190101_AC');
    var $AD = $elt('cvae1329ac_20190101_AD');
    var $BA = $elt('cvae1329ac_20190101_BA');
    var $BB = $elt('cvae1329ac_20190101_BB');
    var $BC = $elt('cvae1329ac_20190101_BC');
    var $CA = $elt('cvae1329ac_20190101_CA');
    var $CB = $elt('cvae1329ac_20190101_CB');
    var $DA = $elt('cvae1329ac_20190101_DA');
    var $DB = $elt('cvae1329ac_20190101_DB');
    var $EA = $elt('cvae1329ac_20190101_EA');
    var $EB = $elt('cvae1329ac_20190101_EB');
    var $EC = $elt('cvae1329ac_20190101_EC');
    var $ED = $elt('cvae1329ac_20190101_ED');
    var $GA = $elt('cvae1329ac_20190101_GA');
    var $GB = $elt('cvae1329ac_20190101_GB');
    var $HA = $elt('cvae1329ac_20190101_HA');
    var $KA = $elt('cvae1329ac_20190101_KA');
    var $KACheckbox = $elt('cvae1329ac_20190101_KA_checkbox');
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
        $percent($GB, $ED, 1.73);
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

    $assert(!($isServi($AD) && $float($AD) > 0 && $float($AD) < 7630000), 'cvae_erreur_215', $AD);
    $assert(!(!$isServi($BA) || $float($BA) < 0), 'cvae_erreur_214', $BA);

    $KF_month_value = parseInt($value($KF_month));
    $assert(!($KF_month_value == 6  && ($isServi($EB) || $isServi($EC))), 'cvae_erreur_208', $EB, $EC);
};

asserts.functions.cvae1329def_20190101 = function($elt,
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
                                                  $percent,
                                                  $decimalAdjust) {
    var $AA = $elt('cvae1329def_20190101_AA');
    var $AB = $elt('cvae1329def_20190101_AB');
    var $AC = $elt('cvae1329def_20190101_AC');
    var $AD = $elt('cvae1329def_20190101_AD');
    var $BA = $elt('cvae1329def_20190101_BA');
    var $BB = $elt('cvae1329def_20190101_BB');
    var $BC = $elt('cvae1329def_20190101_BC');
    var $CA = $elt('cvae1329def_20190101_CA');
    var $CB = $elt('cvae1329def_20190101_CB');
    var $DA = $elt('cvae1329def_20190101_DA');
    var $DB = $elt('cvae1329def_20190101_DB');
    var $EA = $elt('cvae1329def_20190101_EA');
    var $EB = $elt('cvae1329def_20190101_EB');
    var $EC = $elt('cvae1329def_20190101_EC');
    var $ED = $elt('cvae1329def_20190101_ED');
    var $GA = $elt('cvae1329def_20190101_GA');
    var $GB = $elt('cvae1329def_20190101_GB');
    var $GC = $elt('cvae1329def_20190101_GC');
    var $GD = $elt('cvae1329def_20190101_GD');
    var $GE = $elt('cvae1329def_20190101_GE');
    var $HA = $elt('cvae1329def_20190101_HA');
    var $HB = $elt('cvae1329def_20190101_HB');
    var $HC = $elt('cvae1329def_20190101_HC');
    var $HD = $elt('cvae1329def_20190101_HD');
    var $JA = $elt('cvae1329def_20190101_JA');
    var $JE = $elt('cvae1329def_20190101_JE');
    var $JK = $elt('cvae1329def_20190101_JK');
    var $KA = $elt('cvae1329def_20190101_KA');
    var $KB = $elt('cvae1329def_20190101_KB');

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
                $AC_value = (0.5 * (($float($AD) - 500000) / 2500000));
            }
            else if (3000000 < $float($AD) && $float($AD) <= 10000000) {
                $AC_value = (0.5 + 0.9 * (($float($AD) - 3000000) / 7000000));
            }
            else if (10000000 < $float($AD) && $float($AD) <= 50000000) {
                $AC_value = (1.4 + 0.1 * (($float($AD) - 10000000) / 40000000));
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
                $AC_value = (0.5 * (($float($AA) - 500000) / 2500000));
            }
            else if (3000000 < $float($AA) && $float($AA) <= 10000000) {
                $AC_value = (0.5 + 0.9 * (($float($AA) - 3000000) / 7000000));
            }
            else if (10000000 < $float($AA) && $float($AA) <= 50000000) {
                $AC_value = (1.4 + 0.1 * (($float($AA) - 10000000) / 40000000));
            }
            else if ($float($AA) > 50000000) {
                $AC_value = 1.5;
            }
        }
    }

    $value($AC, $decimalAdjust('round', $AC_value, -2));

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

    $AA_value = $float($AA) || 0;
    $CB_value = $float($CB) || 0;
    $DA_value = $float($DA) || 0;
    $DB_value = $float($DB) || 0;

    var resultCADADB = $CB_value - $DA_value - $DB_value;
    if ($AA_value > 500000 && resultCADADB < 250) {
        if (($CB_value > ($DA_value + $DB_value))
            || ($CB_value == 0 && ($DA_value + $DB_value == 0))) {
            $value($EA, 250);
        }
        else {
            $value($EA, 0);
        }
    }
    else if ($AA_value <= 500000 || resultCADADB >= 250) {
        if (resultCADADB >= 0) {
            $value($EA, resultCADADB);
        }
        else {
            $value($EA, 0);
        }
    }

    $readonly($EC, true);
    $soustraction($EC, $EA, $EB);

    $readonly($ED, true);
    $soustraction($ED, $EB, $EA);

    $readonly($GB, true);
    if (!$isServi($GA)) {
        var $BB_P_IDENTIF = $elt('p_identif_20151020_BB');
        if ($isServi($BB_P_IDENTIF)) {
            var declarationYear = $value($BB_P_IDENTIF).substr(-4)
            if (declarationYear < 2019) {
                $percent($GB, $EA, 1.83);
            } else {
                $percent($GB, $EA, 1.73);
            }
        } else {
            $percent($GB, $EA, 1.83);
        }
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
    $assert(!($isServi($AD) && $float($AD) > 0 && $float($AD) < 7630000), 'cvae_erreur_215', $AD);

    $assert(!(!$isServi($BA) || $float($BA) < 0), 'cvae_erreur_214', $BA);

    var $cvae_erreur_214 = "Vous déclarez un chiffre d'affaires inférieur à 500 000 € et vous n'avez pas versé d'acomptes, alors vous n'avez pas de déclaration 1329-DEF à souscrire.";
    $assert(!(!$isServi($AA) || ($isServi($AA) && $float($AA) < 500000 && (!$isServi($AD) || $float($AD) == 0) && (!$isServi($JA) || $float($JA) == 0))), $cvae_erreur_214, $AA);
};

asserts.functions.cvae1330sd_20190101 = function($elt,
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

    var $AC = $elt('cvae1330sd_20190101_AC');

    $assert(!(!$isServi($AC) || $float($AC) < 152500), 'Votre chiffre d\'affaires doit être supérieur à 152 500 euros.', $AC);
};
