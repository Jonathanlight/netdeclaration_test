# Formulaires 2016

## TVA
    php init.php ntd/formulaire.duplicate.v1 name=tva3310ca3_20150101 new_name=tva3310ca3_20160101
    php init.php ntd/formulaire.duplicate.v1 name=tva3310a_20150101 new_name=tva3310a_20160101
    php init.php ntd/formulaire.duplicate.v1 name=tva3310ter_20150101 new_name=tva3310ter_20160101
    php init.php ntd/formulaire.duplicate.v1 name=tva3515sd_20150101 new_name=tva3515sd_20160101

    php init.php ntd/formulaire.duplicate.v1 name=tva3310ca3g_20150101 new_name=tva3310ca3g_20160101
    php init.php ntd/formulaire.duplicate.v1 name=tva3514_20150101 new_name=tva3514_20160101
    php init.php ntd/formulaire.duplicate.v1 name=tva3517bisca12_20150101 new_name=tva3517bisca12_20160101
    php init.php ntd/formulaire.duplicate.v1 name=tva3517ddr_20150101 new_name=tva3517ddr_20160101
    php init.php ntd/formulaire.duplicate.v1 name=tva3517sca12_20150101 new_name=tva3517sca12_20160101
    php init.php ntd/formulaire.duplicate.v1 name=tva3519_20150101 new_name=tva3519_20160101
    php init.php ntd/formulaire.duplicate.v1 name=tva3525bis_20150101 new_name=tva3525bis_20160101

    php init.php ntd/formulaire.duplicate.v1 name=t_identif new_name=t_identif_20160101

## IS
    php init.php ntd/formulaire.duplicate.v1 name=is2571_2015 new_name=is2571_2016
    php init.php ntd/formulaire.duplicate.v1 name=is2572_2015 new_name=is2572_2016
    php init.php ntd/formulaire.duplicate.v1 name=is2573_2015 new_name=is2573_2016

## RCM
- Ajout du millésime 2016 (2015 -> 2016)
  - 2777D (#192) + P_identif (#193)

---

## Mise à jour des ROF TVA
    php init.php ntd/tool.update.rof.tva

## Création SIREN
SQL

    ALTER TABLE `ntd_adherent` ADD `siren` CHAR( 9 ) NOT NULL AFTER `netentreprise_siret`;

CLI

    php init.php ntd/tool.update.siren

Modifier également le IField P-IDENTIF_AA_3039_01 [p-identif #193]
- Valeur par défaut  = ((adherent_siren))
