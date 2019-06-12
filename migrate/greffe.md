# Dépôt de greffe

## Phrases
- go.back.greffe.list
- greffe.declarer
- greffe.declarer.purchase
- greffe.depot.btn.save
- greffe.depot.btn.valid
- greffe.depot.none
- greffe.document.edit
- greffe.document.validate
- greffe.edit
- greffe.folder.new
- greffe.folder.open
- greffe.service.btn.check
- greffe.service.check.eligibility
- greffe.service.eligibility.fail
- greffe.service.eligibility.success
- greffe.status.accepted
- greffe.status.collecting
- greffe.status.completed
- greffe.status.pending
- greffe.status.refused
- greffe.status.sended
- greffe.status.valid
- greffe.validate

## Fragments
- greffe.depot
- greffe.depot.validate
- greffe.depot.validated
- greffe.document.mandat
- greffe.document.reponse
- greffe.folder
- greffe.resume.infos
- greffe.tooltip.cloture_compte
- greffe.tooltip.numero_gestion
- middle.page.services.purchasable (edit)

## Services
Création de deux services
- **Accès Greffe**
  - Type: Adhésion
  - Adhérents associés:
    - Cabinet Expertise Comptable
    - Entreprise
    - Organisme de Gestion Agréé
  - Catégorie de service: Greffe
  - **Tarifs**
    - Accès Greffe [Adhésion] - Tarif forfait : 17,00 €
      - Type de l'adhérents
        - Cabinet Expertise Comptable
        - Entreprise
        - Organisme de Gestion Agréé
      - Niveau de l'adhérent: Les deux
      - Type de prix: Prix par dépôt de greffe
      - Seuil Maximum: 1
    - Accès Greffe [Adhésion] - Tarif forfait : 10,00 €
      - Type de l'adhérents
        - Cabinet Expertise Comptable
        - Entreprise
        - Organisme de Gestion Agréé
      - Niveau de l'adhérent: Les deux
      - Type de prix: Prix par dépôt de greffe
      - Services requis: EDI TDFC
      - Seuil Maximum: 1
    - Accès Greffe [Adhésion] - Tarif forfait : 0,00 €
      - Type de l'adhérents
        - Cabinet Expertise Comptable
        - Entreprise
        - Organisme de Gestion Agréé
      - Niveau de l'adhérent: Les deux
      - Type de prix: Prix par dépôt de greffe
      - Services requis: E-Liasse Fiscal
      - Seuil Maximum: 1


- **Greffe - Dépôt de comptes**
  - Type: Autres
  - Adhérents associés:
    - Cabinet Expertise Comptable
    - Entreprise
    - Organisme de Gestion Agréé
  - Catégorie de service: Greffe
  - Service requis: Accès Greffe
  - **Tarifs**
    - Greffe - Dépôt de comptes [Formulaire] - Tarif forfait : 48,65 €
      - Type de l'adhérents
        - Cabinet Expertise Comptable
        - Entreprise
        - Organisme de Gestion Agréé
      - Niveau de l'adhérent: Les deux
      - Type de prix: Prix par dépôt de greffe
      - Seuil Maximum: 1
    - Greffe - Dépôt de comptes [Formulaire] - Tarif forfait : 28,65 €
      - Type de l'adhérents
        - Cabinet Expertise Comptable
        - Entreprise
        - Organisme de Gestion Agréé
      - Niveau de l'adhérent: Les deux
      - Type de prix: Prix par dépôt de greffe
      - Seuil Minimum: 2
      - Seuil Maximum: 1000000000

## BDD

### Structures
```sql
CREATE TABLE `ntd_greffe` (
 `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
 `content` text NOT NULL,
 `flags` int(10) unsigned NOT NULL DEFAULT '0',
 `name` varchar(255) NOT NULL,
 `status` tinyint(3) unsigned NOT NULL DEFAULT '0',
 PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
```

```sql
CREATE TABLE `ntd_greffe_document` (
 `greffe_id` int(11) NOT NULL,
 `type` int(11) NOT NULL,
 `register_at` datetime NOT NULL,
 `path` text NOT NULL,
 PRIMARY KEY (`greffe_id`,`type`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
```

```sql
CREATE TABLE `ntd_greffecommune` (
 `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
 `arrondissement` varchar(45) DEFAULT NULL,
 `code_greffe` int(4) unsigned zerofill NOT NULL,
 `code_insee` int(5) unsigned zerofill NOT NULL,
 `department` int(11) NOT NULL,
 `name` varchar(255) NOT NULL,
 `zipcode` int(5) unsigned zerofill NOT NULL,
 PRIMARY KEY (`id`),
 KEY `zipcode` (`zipcode`),
 KEY `code_insee` (`code_insee`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
```

```sql
CREATE TABLE `ntd_greffedossier` (
 `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
 `name` varchar(45) NOT NULL,
 `status` tinyint(3) unsigned NOT NULL DEFAULT '0',
 PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
```

```sql
CREATE TABLE `ntd_tarif_service` (
 `tarif_id` int(11) NOT NULL,
 `service_id` int(11) NOT NULL,
 PRIMARY KEY (`tarif_id`,`service_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
```


### Mises à jour
```sql
ALTER TABLE `ntd_adherent` ADD `siren` CHAR(9) NULL AFTER `forme_juridique`;

ALTER TABLE `ntd_greffe` ADD `email_deposit` VARCHAR(45) NOT NULL AFTER `content`;
ALTER TABLE `ntd_greffe` ADD `closed_at` DATE NOT NULL AFTER `id`;
ALTER TABLE `ntd_greffe` ADD `start_at` DATE NOT NULL AFTER `name`;
ALTER TABLE `ntd_greffe` ADD `compte_type` INT UNSIGNED NOT NULL AFTER `closed_at`;
ALTER TABLE `ntd_greffe` ADD `forme_juridique` INT UNSIGNED NOT NULL AFTER `flags`;
ALTER TABLE `ntd_greffe` ADD `mode_direction` INT UNSIGNED NOT NULL AFTER `forme_juridique`;
ALTER TABLE `ntd_greffe` ADD `is_public` TINYINT UNSIGNED NOT NULL AFTER `forme_juridique`;
ALTER TABLE `ntd_greffe` ADD `adherent_id` INT UNSIGNED NOT NULL AFTER `status`, ADD INDEX (`adherent_id`) ;
ALTER TABLE `ntd_greffe` ADD `is_gerant` TINYINT UNSIGNED NOT NULL AFTER `forme_juridique`;
ALTER TABLE `ntd_greffe` CHANGE `status` `status` TINYINT(3) NOT NULL;
ALTER TABLE `ntd_greffe` ADD `send_at` DATETIME NULL COMMENT 'Amitel ACK' AFTER `name`;
ALTER TABLE `ntd_greffe` ADD `response_at` DATE NULL COMMENT 'Amitel Reponse' AFTER `name`;
ALTER TABLE `ntd_greffe` ADD `documents` TEXT NULL COMMENT 'Amitel Reponse Documents' AFTER `content`;
ALTER TABLE `ntd_greffe` ADD `link_liasse_declaration` INT NOT NULL AFTER `is_public`;
ALTER TABLE `ntd_greffe` ADD `status_valid_at` DATETIME NOT NULL AFTER `status`;

ALTER TABLE `ntd_adherent` ADD `greffecommune_id` INT UNSIGNED NOT NULL AFTER `adherent_id`, ADD INDEX (`greffecommune_id`) ;

ALTER TABLE `ntd_millesime` ADD `start_at` DATE NOT NULL AFTER `name`;
ALTER TABLE `ntd_millesime` ADD `end_at` DATE NOT NULL AFTER `description`;

ALTER TABLE `ntd_greffecommune` ADD `status` INT UNSIGNED NOT NULL AFTER `name`, ADD INDEX (`status`) ;
ALTER TABLE `ntd_greffe` ADD `numero_gestion` VARCHAR(10) NOT NULL COMMENT 'YYYYLCCCCC' AFTER `name`;
ALTER TABLE `ntd_greffe` ADD `souscription_id` INT NOT NULL AFTER `send_at`, ADD INDEX (`souscription_id`) ;

ALTER TABLE `ntd_greffe` ADD `greffedossier_id` INT UNSIGNED NOT NULL AFTER `forme_juridique`, ADD INDEX (`greffedossier_id`) ;
ALTER TABLE `ntd_greffedossier` ADD `adherent_id` INT UNSIGNED NOT NULL AFTER `id`, ADD INDEX (`adherent_id`) ;
```


## Mise à jour des Millésimes
```sql
UPDATE `ntd_millesime` SET `end_at` = '2011-12-31', `start_at` = '2011-01-01' WHERE `ntd_millesime`.`id` = 6;
UPDATE `ntd_millesime` SET `end_at` = '2012-12-31', `start_at` = '2012-01-01' WHERE `ntd_millesime`.`id` = 7;
UPDATE `ntd_millesime` SET `end_at` = '2013-12-31', `start_at` = '2013-01-01' WHERE `ntd_millesime`.`id` = 1;
UPDATE `ntd_millesime` SET `end_at` = '2014-12-31', `start_at` = '2014-01-01' WHERE `ntd_millesime`.`id` = 5;
UPDATE `ntd_millesime` SET `end_at` = '2015-12-31', `start_at` = '2015-01-01' WHERE `ntd_millesime`.`id` = 8;
UPDATE `ntd_millesime` SET `end_at` = '2016-12-31', `start_at` = '2016-01-01' WHERE `ntd_millesime`.`id` = 9;
```

## importer les communes
> ntd_greffecommune.csv

## Mise à jour des prix sur le front

Tarif  Dépôt des Comptes Annuels vers GREFFE au 01/01/2016 					

| Tarif Adhésion                         | Tarif / SIRET  |
| :-------------                         | :------------- |
| Frais adhésion - Accès Dépôt de Greffe | 17,00 €        |
|	si souscription Service E-LIASSE       | Gratuit        |

|	Tarif Dépôt des Comptes Annuels        | Tarif / SIRET  |
| :-------------                         | :------------- |
| Greffe - Dépôt des comptes annuels     | 49,15 €        |
| Greffe - Dépôt des comptes annuels - Si 2ieme envoi pour complément de pièces | 28,65 € |



## Autres
```shell
# Installation de ghostscript pour les fusions de pdf
yum install ghostscript
```
