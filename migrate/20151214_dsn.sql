ALTER TABLE `ntd_adherent` ADD `gestion_dsn` TINYINT UNSIGNED NOT NULL AFTER `gestion_ir`;

ALTER TABLE `ntd_adherent` ADD `netentreprise_first_name` VARCHAR(255) NOT NULL AFTER `forme_juridique`,
                           ADD `netentreprise_last_name` VARCHAR(255) NOT NULL AFTER `netentreprise_first_name`,
                           ADD `netentreprise_siret` CHAR(14) NOT NULL AFTER `netentreprise_last_name`;
