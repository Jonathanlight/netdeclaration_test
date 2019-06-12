<?php

class FormulaireFunctions {

  public static $funcs = array(
    /******************************/
    /**** Fonctions génériques ****/
    /******************************/

    'data-addition' => 'NTD.Generic.addition',
    'data-soustraction' => 'NTD.Generic.soustraction',
    'data-multiplication' => 'NTD.Generic.multiplication',
    'data-check-positiv' => 'NTD.Generic.check_positiv',
    'data-check-negativ' => 'NTD.Generic.check_negativ',
    'data-check-set-unchecked' => 'NTD.Generic.check_set_unchecked',
    'data-check-integer' => 'NTD.Generic.check_integer',
    'data-check-full' => 'NTD.Generic.check_full',
    'data-check-full-set-zero' => 'NTD.Generic.check_full_set_zero',
    'data-report' => 'NTD.Generic.report',
    'data-check-positiv-set-full' => 'NTD.Generic.check_positiv_set_full',
    'data-check-null-or-zero-set-zero' => 'NTD.Generic.check_null_or_zero_set_zero',
    'data-check-null-or-zero-set-null-or-zero' => 'NTD.Generic.check_null_or_zero_set_null_or_zero',
    'data-check-positiv-zero-set-full' => 'NTD.Generic.check_positiv_zero_set_full',
    'data-check-positiv-set-empty' => 'NTD.Generic.check_positiv_set_empty',
    'data-check-positiv-zero-set-checked' => 'NTD.Generic.check_positiv_zero_set_checked',
    'data-check-set-positiv-zero' => 'NTD.Generic.check_set_positiv_zero',
    'data-check-positiv-zero' => 'NTD.Generic.check_positiv_zero',
    'data-check-positiv-zero-set-empty' => 'NTD.Generic.check_positiv_zero_set_empty',
    'data-check-percent' => 'NTD.Generic.check_percent',
    'data-check-egal-percent' => 'NTD.Generic.check_egal_percent',
    'data-check-need-and-or' => 'NTD.Generic.check_need_and_or',
    'data-check-uneed-and-or' => 'NTD.Generic.check_uneed_and_or',
    'data-check-inf-egal' => 'NTD.Generic.check_inf_egal',
    'data-check-inf' => 'NTD.Generic.check_inf',
    'data-format-mm' => 'NTD.Generic.format_mm',
    'data-format-mmaa' => 'NTD.Generic.format_mmaa',
    'data-format-jjmmaa' => 'NTD.Generic.format_jjmmaa',
    'data-format-ssaammjj' => 'NTD.Generic.format_ssaammjj',
    'data-disable' => 'NTD.Generic.disable',
    'data-check-positiv-zero-set-zero' => 'NTD.Generic.check_positiv_zero_set_zero',
    'data-check-set-empty' => 'NTD.Generic.check_set_empty',
    'data-check-positiv-set-zero' => 'NTD.Generic.check_positiv_set_zero',
    'data-check-need-and-or-input' => 'NTD.Generic.check_need_and_or_input',
    'data-check-positiv-one-item' => 'NTD.Generic.check_positiv_one_item',

    'data-format-ssaammjj' => 'NTD.Generic.format_ssaammjj',
    'data-format-mmaa' => 'NTD.Generic.format_mmaa',
    'data-format-jjmmaa' => 'NTD.Generic.format_jjmmaa',
    'data-format-mm' => 'NTD.Generic.format_mm',
    'data-format-ssaamm' => 'NTD.Generic.format_ssaamm',

    'data-check_iban' => 'NTD.Generic.check_iban',
    'data-check_bic' => 'NTD.Generic.check_bic',
    'copy-value' => 'NTD.Generic.copy_value',
    'data-empty-and-desactive' => 'NTD.Generic.empty_and_desactive',


    /**********************/
    /**** Fonctions IS ****/
    /**********************/

    'data-compare' => 'NTD.Is.compare',
    'data-soustraction-cada' => 'NTD.Is.soustraction_cada',
    'data-verification-ea' => 'NTD.Is.verification_ea',
    'data-is2571-paiement' => 'NTD.Is.is2571_paiement',
    'data-is2572-paiement' => 'NTD.Is.is2572_paiement',

    /************************/
    /**** Fonctions CVAE ****/
    /************************/

    'data-calc-b' => 'NTD.Cvae.calcB',
    //'data-frais-gestionac' => 'NTD.Cvae.fraisGestionac',
    'data-montant-total' => 'NTD.Cvae.montantTotal',
    'data-calc-d' => 'NTD.Cvae.calcD',
    'data-calc-e' => 'NTD.Cvae.calcE',
    'data-calc-f' => 'NTD.Cvae.calcF',
    'data-calc-fac' => 'NTD.Cvae.calcFac',
    'data-checkbox' => 'NTD.Cvae.checkbox',
    'data-frais-gestion' => 'NTD.Cvae.fraisGestion',
    'data-montant-cotisation' => 'NTD.Cvae.montantCotisation',
    'data-cotisation-minimum' => 'NTD.Cvae.cotisationMinimum',
    'data-cotisation-avant-reduction' => 'NTD.Cvae.cotisationAvantReduction',
    'data-accompte-a-verser' => 'NTD.Cvae.accompteAVerser',
    'data-paiement-cvae1329def' => 'NTD.Cvae.cvae1329def_paiement',

    /**********************/
    /**** Fonctions TS ****/
    /**********************/
    'data-integrity-ab-ts2501' => 'NTD.Ts.integrity_ab_ts2501',
    'data-calcul-935' => 'NTD.Ts.calcul9_35',
    'data-calcul-295' => 'NTD.Ts.calcul2_95',
    'data-calcul-255' => 'NTD.Ts.calcul2_55',
    'data-ts-value-percent' => 'NTD.Ts.ts_value_percent',
    'data-multpercent' => 'NTD.Ts.mult_percent',
    'data-franchise-decote' => 'NTD.Ts.franchise_decote',
    'data-franchise-decote-201412' => 'NTD.Ts.franchise_decote_201412',
    'data-abattement' => 'NTD.Ts.abattement',
    'data-abattement-201412' => 'NTD.Ts.abattement_201412',
    'data-taxe-nette-due' => 'NTD.Ts.taxeNetteDue',
    'data-ts2501-paiement' => 'NTD.Ts.ts2501_paiement',
    'data-ts2502-paiement' => 'NTD.Ts.ts2502_paiement',
    'data-ts2502-controlgb' => 'NTD.Ts.ts2502_controlGB',
    'data-ts2502-control-fc' => 'NTD.Ts.ts2502_controlFC',
    'data-ts2502-calcule-hb' => 'NTD.Ts.ts2502_calculeHB',
    'data-ts2502-calcule-hc' => 'NTD.Ts.ts2502_calculeHC',
    'data-ts2502-check-he-2018' => 'NTD.Ts.ts2502_checkHE_2018',

    /***********************/
    /**** Fonctions TVA ****/
    /***********************/

    // Tva générique
    'data-calcul-090' => 'NTD.Tva.calcul0_90',
    'data-calcul-105' => 'NTD.Tva.calcul1_05',
    'data-calcul-175' => 'NTD.Tva.calcul1_75',
    'data-calcul-210' => 'NTD.Tva.calcul2_10',
    'data-calcul-425' => 'NTD.Ts.calcul4_25',
    'data-calcul-1575' => 'NTD.Ts.calcul1575',
    'data-calcul-550' => 'NTD.Tva.calcul5_50',
    'data-calcul-700' => 'NTD.Tva.calcul7_00',
    'data-calcul-800' => 'NTD.Tva.calcul8_00',
    'data-calcul-850' => 'NTD.Tva.calcul8_50',
    'data-calcul-1000' => 'NTD.Tva.calcul10_00',
    'data-calcul-1300' => 'NTD.Tva.calcul13_00',
    'data-calcul-1960' => 'NTD.Tva.calcul19_60',
    'data-calcul-2000' => 'NTD.Tva.calcul20_00',
    'data-calcul-percent' => 'NTD.Tva.calcul_percent',

    // 3310 CA3
    'data-calcul-cc' => 'NTD.tva3310ca3.calcul_cc',
    'data-calcul-gh' => 'NTD.tva3310ca3.calcul_gh',
    'data-calcul-gc' => 'NTD.tva3310ca3.calcul_gc',
    'data-calcul-gj' => 'NTD.tva3310ca3.calcul_gj',
    'data-calcul-ke' => 'NTD.tva3310ca3.calcul_ke',
    'data-calcul-ke-2015' => 'NTD.tva3310ca3.calcul_ke_2015',
    'data-calcul-kc' => 'NTD.tva3310ca3.calcul_kc',
    'data-calcul-ca3-ja' => 'NTD.tva3310ca3.calcul_ja',
    'data-calcul-ca3-ka' => 'NTD.tva3310ca3.calcul_ka',
    'data-integrity-cc' => 'NTD.tva3310ca3.integrity_cc',
    'data-integrity-cd' => 'NTD.tva3310ca3.integrity_cd',
    'data-integrity-ce' => 'NTD.tva3310ca3.integrity_ce',
    'data-integrity-gc' => 'NTD.tva3310ca3.integrity_gc',
    'data-integrity-gc-2014' => 'NTD.tva3310ca3.integrity_gc_2014',
    'data-integrity-gj' => 'NTD.tva3310ca3.integrity_gj',
    'data-integrity-gj-2014' => 'NTD.tva3310ca3.integrity_gj_2014',
    'data-integrity-gj-2015' => 'NTD.tva3310ca3.integrity_gj_2015',
    'data-integrity-gk' => 'NTD.tva3310ca3.integrity_gk',
    'data-integrity-hh' => 'NTD.tva3310ca3.integrity_hh',
    'data-integrity-kc' => 'NTD.tva3310ca3.integrity_kc',
    'data-integrity-kc-2015' => 'NTD.tva3310ca3.integrity_kc_2015',
    'data-integrity-kg' => 'NTD.tva3310ca3.integrity_kg',
    'data-integrity-jb' => 'NTD.tva3310ca3.integrity_jb',
    'disable-form' => 'NTD.tva3310ca3.disable_form',
    'data-integrity-gh' => 'NTD.tva3310ca3.integrity_gh',
    'data-integrity-kt' => 'NTD.tva3310ca3.integrity_kt',

    // 3517sca
    'data-integrity-aa-sca12' => 'NTD.Tva3517sca.integrity_aa_sca12',
    'data-calcul-rd' => 'NTD.Tva3517sca.calcul_rd',
    'data-calcul-sb' => 'NTD.Tva3517sca.calcul_sb',
    'data-calcul-sb-2015' => 'NTD.Tva3517sca.calcul_sb_2015',
    'data-calcul-nc' => 'NTD.Tva3517sca.calcul_nc',
    'data-calcul-nc-2015' => 'NTD.Tva3517sca.calcul_nc_2015',
    'data-check-sup-egal-150' => 'NTD.Tva3517sca.check_sup_egal_150',
    'data-calcul-na' => 'NTD.Tva3517sca.calcul_na',
    'data-calcul-na-2015' => 'NTD.Tva3517sca.calcul_na_2015',
    'data-calcul-nb' => 'NTD.Tva3517sca.calcul_nb',
    'data-calcul-nb-2015' => 'NTD.Tva3517sca.calcul_nb_2015',
    'data-integrity-fg-3517' => 'NTD.Tva3517sca.integrity_fg_3517',
    'data-integrity-fp' => 'NTD.Tva3517sca.integrity_fp',
    'data-integrity-eq' => 'NTD.Tva3517sca.integrity_eq',
    'data-integrity-fe' => 'NTD.Tva3517sca.integrity_fe',
    'data-calcul-la-or-lb' => 'NTD.Tva3517sca.calcul_la_or_lb',
    'data-integrity-rb' => 'NTD.Tva3517sca.integrity_rb',
    'data-calcul-va' => 'NTD.Tva3517sca.calcul_va',
    'data-calcul-nj' => 'NTD.Tva3517sca.calcul_nj',
    'data-disable-all' => 'NTD.Tva3517sca.disable_all',

    // 3517bisca
    'data-integrity-ae-bisca12' => 'NTD.tva3517bisca.integrity_ae_bisca12',
    'data-calcul-dp' => 'NTD.tva3517bisca.calcul_dp',
    'data-calcul-jb' => 'NTD.tva3517bisca.calcul_jb',
    'data-calcul-ja' => 'NTD.tva3517bisca.calcul_ja',
    'data-calcul-jc-nc' => 'NTD.tva3517bisca.calcul_jc_nc',
    'data-calcul-es' => 'NTD.tva3517bisca.calcul_es',
    'data-integrity-fg-bisca12' => 'NTD.tva3517bisca.integrity_fg_bisca12',
    'data-calcul-ff-bisca12' => 'NTD.tva3517bisca.calcul_ff_bisca12',
    'data-calcul-ff-bisca12-2015' => 'NTD.tva3517bisca.calcul_ff_bisca12_2015',
    'data-calcul-ga-gb-bisca12' => 'NTD.tva3517bisca.calcul_ga_gb_bisca12',
    'data-calcul-ja-jb-jc-bisca12' => 'NTD.tva3517bisca.calcul_ja_jb_jc_bisca12',
    'data-calcul-ja-jb-jc-bisca12-2015' => 'NTD.tva3517bisca.calcul_ja_jb_jc_bisca12_2015',
    'data-report-if-150' => 'NTD.tva3517bisca.report_if_150',
    'data-calcul-nj-bisca12' => 'NTD.tva3517bisca.calcul_nj_bisca12',
    'data-integrity-mb-bisca12' => 'NTD.tva3517bisca.integrity_mb_bisca12',
    'data-disable-all-bisca12' => 'NTD.tva3517bisca.disable_all_bisca12',
    'data-integrity-ep-bisca' => 'NTD.tva3517bisca.integrity_ep_bisca',
    'data-integrity-eh-bisca' => 'NTD.tva3517bisca.integrity_eh_bisca',
    'data-report-MA-JC' => 'NTD.tva3517bisca.report_MA_JC',

    // 3514
    'data-tva3514-gf' => 'NTD.tva3514.calcul_gf',
    'data-tva3514-gg' => 'NTD.tva3514.calcul_gg',
    'data-tva3514-gc' => 'NTD.tva3514.calcul_gc',
    'data-tva3519-fg' => 'NTD.tva3519.calcul_fg',
    'data-tva3514-es' => 'NTD.tva3514.calcul_es',
    'data-disable-on-da' => 'NTD.Tva3514.disable_on_da',
    'data-disable-on-db' => 'NTD.Tva3514.disable_on_db',
    'data-integrity-dc' => 'NTD.Tva3514.integrity_dc',
    'data-integrity-db' => 'NTD.Tva3514.integrity_db',
    'data-disable-on-dc' => 'NTD.Tva3514.disable_on_dc',
    'data-disable-on-aa' => 'NTD.Tva3514.disable_on_aa',
    'data-disable-if-dd-checked' => 'NTD.Tva3514.disable_if_dd_checked',
    'data-disable-if-de-checked' => 'NTD.Tva3514.disable_if_de_checked',
    'data-calcul-ga-gb' => 'NTD.Tva3514.calcul_ga_gb',
    'data-disable-on-dg' => 'NTD.Tva3514.disable_on_dg',
    'data-integrity-gc-3514' => 'NTD.Tva3514.integrity_gc_3514',
    'data-calcul-gg-3514' => 'NTD.Tva3514.calcul_gg_3514',
    'data-integrity-gk-gl' => 'NTD.Tva3514.integrity_gk_gl',
    'data-calcul-gf' => 'NTD.Tva3514.calcul_gf',
    'data-tva3514-paiement' => 'NTD.Tva3514.paiement',
    'data-tva3514-20140101-paiement' => 'NTD.Tva3514.paiement_20140101',
    'data-check-dw-dg' => 'NTD.Tva3514.check_dw_dg',
    'data-integrity-id' => 'NTD.Tva3514.integrity_id',
    'data-general-tva3514_20150101' => 'NTD.Tva3514.general_tva3514_20150101',

    // 3310ter
    'data-check-non-egal-to-zero' => 'NTD.tva3310ter.check_non_egal_to_zero',
    'data-calcul-rm' => 'NTD.tva3310ter.calcul_rm',
    'data-calcul-qm' => 'NTD.tva3310ter.calcul_qm',
    'data-calcul-rm-2014' => 'NTD.tva3310ter.calcul_rm_2014',
    'data-calcul-qm-2014' => 'NTD.tva3310ter.calcul_qm_2014',


    // 3515sd
    'data-integrity-ca-3515sd' => 'NTD.Tva3515sd.integrity_ca_3515sd',
    'data-report-BC-BD' => 'NTD.Tva3515sd.report_BC_BD',
    'data-soustraction-da-db-3515sd' => 'NTD.Tva3515sd.soustraction_da_db_3515sd',

    // 3525bis
    'data-integrity-bc-3525bis' => 'NTD.Tva3525bis.integrity_bc_3525bis',
    'data-disable-all-3525bis' => 'NTD.Tva3525bis.disable_all_3525bis',
    'data-paiement-tva3525bis' => 'NTD.Tva3525bis.paiement_tva3525bis',

    // 3519
    'data-paiement_3519' => 'NTD.Tva3519.paiement_3519',
    'data-integrity-fg' => 'NTD.Tva3519.integrity_fg',
    'data-integrity-dj' => 'NTD.Tva3519.integrity_dj',
    'data-tva3519-export' => 'NTD.Tva3519.tva3519_export',
    'data-assert-tva3519_20150101' => 'NTD.Tva3519.assert_tva3519_20150101',

    // 3517
    'data-paiement_3517ddr' => 'NTD.Tva.paiement_3517ddr',
    'data-paiement_3517sca12' => 'NTD.Tva3517sca.paiement_3517sca12',
    'data-paiement_3517bisca12' => 'NTD.tva3517bisca.paiement_3517bisca12',


    // 3310ca3g

    'disable-forms' => 'Formulaire.tva3310ca3g.disable_forms',
    'data-paiement_3310ca3g_20130331' => 'Formulaire.tva3310ca3g.paiement_20130331'

  );
}
