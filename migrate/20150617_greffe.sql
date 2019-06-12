
/* Structure */
CREATE TABLE `ntd_greffe` (
 `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
 `content` text NOT NULL,
 `flags` int(10) unsigned NOT NULL DEFAULT '0',
 `name` varchar(255) NOT NULL,
 `status` tinyint(3) unsigned NOT NULL DEFAULT '0',
 PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ;

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

CREATE TABLE `ntd_greffe_document` (
 `greffe_id` int(11) NOT NULL,
 `type` int(11) NOT NULL,
 `register_at` datetime NOT NULL,
 `path` text NOT NULL,
 PRIMARY KEY (`greffe_id`,`type`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8

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
) ENGINE=MyISAM DEFAULT CHARSET=utf8

ALTER TABLE `ntd_adherent` ADD `greffecommune_id` INT UNSIGNED NOT NULL AFTER `adherent_id`, ADD INDEX (`greffecommune_id`) ;

ALTER TABLE `ntd_millesime` ADD `start_at` DATE NOT NULL AFTER `name`;
ALTER TABLE `ntd_millesime` ADD `end_at` DATE NOT NULL AFTER `description`;

/* Services */
CREATE TABLE `ntd_tarif_service` (
 `tarif_id` int(11) NOT NULL,
 `service_id` int(11) NOT NULL,
 PRIMARY KEY (`tarif_id`,`service_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8

/* Imports
INSERT INTO `ntd_service` (`id`, `service_id`, `servicetype_id`, `adherent_types`, `document_code`, `code`, `description_`, `flags`, `image`, `locales`, `name`, `position`, `position_catalogue`, `status`, `type`, `flags_export_adherent`, `type_doc_edi`) VALUES
(49, 0, 13, '2', 0, '', '', 16, '', 0, 'Accès Dépot de Greffe', 0, 0, 1, 0, 0, ''),
(50, 49, 13, '2', 0, '', '', 0, '', 0, 'Greffe - Dépôt des comptes annuels', 0, 0, 1, 2, 0, '');


INSERT INTO `ntd_tarif` (`id`, `service_id`, `adherent_types`, `adherent_level`, `description`, `flags`, `locales`, `name`, `price`, `price_type`, `qty_min`, `qty_max`, `status`) VALUES
(162, 49, '2', 0, '', 0, 0, 'Accès Dépot de Greffe [Autre] - Tarif forfait : 48,00 €', 48, 1, 0, 0, 1),
(163, 50, '2', 0, '', 0, 0, 'Greffe - Dépôt des comptes annuels [Autre] - Tarif SIRET : 10,00 €', 10, 3, 0, 0, 1),
(164, 50, '2', 0, '', 0, 0, 'Greffe - Dépôt des comptes annuels [Autre] - Tarif SIRET : 17,00 €', 17, 3, 0, 0, 1),
(165, 49, '2', 0, '', 0, 0, 'Accès Dépot de Greffe [Formulaire] - Tarif forfait : 0,00 €', 0, 1, 0, 0, 1),
(166, 50, '2', 0, '', 0, 0, 'Greffe - Dépôt des comptes annuels [Formulaire] - Tarif SIRET : 0,00 €', 0, 3, 0, 0, 1);

INSERT INTO `ntd_tarif_service` (`tarif_id`, `service_id`) VALUES
(163, 19),
(165, 38),
(166, 38);
*/

ALTER TABLE `ntd_greffecommune` ADD `status` INT UNSIGNED NOT NULL AFTER `name`, ADD INDEX (`status`) ;
ALTER TABLE `ntd_greffe` ADD `numero_gestion` VARCHAR(10) NOT NULL COMMENT 'YYYYLCCCCC' AFTER `name`;
ALTER TABLE `ntd_greffe` ADD `souscription_id` INT NOT NULL AFTER `send_at`, ADD INDEX (`souscription_id`) ;

/* Dossiers */
CREATE TABLE `ntd_greffedossier` (
 `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
 `name` varchar(45) NOT NULL,
 `status` tinyint(3) unsigned NOT NULL DEFAULT '0',
 PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8

ALTER TABLE `ntd_greffe` ADD `greffedossier_id` INT UNSIGNED NOT NULL AFTER `forme_juridique`, ADD INDEX (`greffedossier_id`) ;
ALTER TABLE `ntd_greffedossier` ADD `adherent_id` INT UNSIGNED NOT NULL AFTER `id`, ADD INDEX (`adherent_id`) ;
