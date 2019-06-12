# Formulaires TVA 2018

## TVA

```bash
php init.php ntd/formulaire.duplicate.v1 name=tva3525bis_20170101 new_name=tva3525bis_20180101
php init.php ntd/formulaire.duplicate.v1 name=tva3519_20170101 new_name=tva3519_20180101
php init.php ntd/formulaire.duplicate.v1 name=tva3517ddr_20170101 new_name=tva3517ddr_20180101
php init.php ntd/formulaire.duplicate.v1 name=tva3310ca3g_20170101 new_name=tva3310ca3g_20180101
php init.php ntd/formulaire.duplicate.v1 name=tva3514_20170101 new_name=tva3514_20180101
php init.php ntd/formulaire.duplicate.v1 name=tva3515sd_20170101 new_name=tva3515sd_20180101
php init.php ntd/formulaire.duplicate.v1 name=tva3310ter_20170101 new_name=tva3310ter_20180101
php init.php ntd/formulaire.duplicate.v1 name=tva3310ca3_20170101 new_name=tva3310ca3_20180101
php init.php ntd/formulaire.duplicate.v1 name=tva3517bisca12_20170101 new_name=tva3517bisca12_20180101
php init.php ntd/formulaire.duplicate.v1 name=tva3310a_20170101 new_name=tva3310a_20180101
```

## Mises à jour

- `T-IDENTIF`
  - Formulairetype [ t_identif_20170101 ] ( 331 )
    - Ajout du millésime associé: 2018

- `3525BIS`
  - Formulairetype [ tva3525bis_20180101 ] ( 352 )
    - Ajout du millésime associé: 2018
  - Dectype [ TVA 3525 BIS version 2018 ] ( 316 )
    - Duplication de : - Dectype [ TVA 3525 BIS version 2017 ] ( 259 )

- `3519`
  - Formulairetype [ tva3519_20180101 ] ( 354 )
    - Ajout du millésime associé: 2018
  - Dectype [ TVA 3519 version 2017 ] ( 318 )
    - Duplication de : - Dectype [ TVA 3519 version 2017 ] ( 256 )

- `3517DDR`
  - Formulairetype [ tva3517ddr_20180101 ] ( 353 )
    - Ajout du millésime associé: 2018
    - Suppression du controle de taille du champ AL/FTX
    - Ajout des controles
    - Ajout des asserters back

- `3310CA3G`
  - Formulairetype [ tva3310ca3g_20180101 ] ( 355 )
    - Ajout du millésime associé: 2018  
    - Modification de la page 2
    - Modification de la page 3 :
      - Modification du titre avant la ligne 59
      - Modification de la ligne 71, 72
      - Ajout du champ NK, NL
      - Suppression du champ HC
      - Modification des lignes 91, 92, 93, 94
      - Modification des lignes 96, 97, 98, 101, 102, 103, 111, 112
      - Modification des lignes 114, 115, titre entre les lignes 116/117
      - Ajout du champ NM
      - Ajout de la ligne 119
      - Ajout des champs NN, NP, NQ
      - Ajout des lignes 119, 120, 121
      - Ajout des champs NR, NS, NT
      - Ajout des lignes 122, 123
      - Modification de la ligne 124
      - Ajout des éléments extensibles
      - Ajout des contrôles
    - Ajout des asserters back  

- `3514`
  - Formulairetype [ tva3514_20180101 ] ( 356 )
    - Ajout du millésime associé: 2018
    - Ajout des asserters back
  - Dectype [ TVA 3514 version 2018 ] ( 320 )
    - Duplication de : - Dectype [ TVA 3514 version 2017 ] ( 253 )

- `3515SD`
  - Formulairetype [ tva3515sd_20180101 ] ( 357 )
    - Ajout du millésime associé: 2018
    - Ajout des controles   
    - Ajout des asserters back
  - ~~Dectype [ TVA 3515 SD version 2018 ] ( 321 )~~
    - ~~Création~~

- `3310TER`
  - Formulairetype [ tva3310ter_20180101 ] ( 358 )
    - Ajout du millésime associé: 2018
    - Ajout des controles
    - Ajout des asserters back
  - ~~Dectype [ TVA 3510TER version 2018 ] ( 322 )~~
    - ~~Création~~

- `3310CA3`
  - Formulairetype [ tva3310ca3_20180101 ] ( 358 )
    - Ajout du millésime associé: 2018
    - Ajout des controles
    - Ajout des asserter back
  - Dectype [ TVA 3310CA3 version 2018 ] ( 323 )
    - Duplication de : - Dectype [ TVA 3310CA3 version 2017 ] ( 252 )

- `3517BISCA12`
  - Formulairetype [ tva3517bisca12_20180101 ] ( 360 )
    - Ajout du millésime associé: 2018
    - Ajout des nouveaux champs  
    - Mise à jour page 1, 2, 3
  - Dectype [ TVA 3517 BISCA12 version 2018 ] ( 324 )
    - Duplication de : - Dectype [ TVA 3517 BISCA12 version 2017 ] ( 255 )
    
- `3517SCA12`    
  - Formulairetype [ tva3517sca12_20180101 ] ( 362 )
    - Ajout du millésime associé: 2018
    - Ajout/Suppression des champs
    - Mise à jour du formulaire
    - Mise à jour des opérations
    - Ajout des asserters back
  - Dectype [ TVA 3517 SCA12 version 2018 ] ( 326 )
    - Duplication de : - Dectype [ TVA 3517 SCA12 version 2017 ] ( 258 )  
      
- `3310A`
  - Formulairetype [ tva3310a_20180101 ] ( 361 )
    - Ajout du millésime associé: 2018
