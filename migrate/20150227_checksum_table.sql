ALTER TABLE `declaration_checksum`
DROP `content`,
DROP `description`,
DROP `image`,
DROP `status`;
ALTER TABLE `declaration_checksum` ADD `model_id` INT UNSIGNED NOT NULL DEFAULT '0' AFTER `name` ,
ADD INDEX ( `model_id` ) ;
ALTER TABLE `declaration_checksum` ADD `record_id` INT UNSIGNED NOT NULL DEFAULT '0' AFTER `model_id` ,
ADD INDEX ( `record_id` ) ;
ALTER TABLE `declaration_checksum` ADD `checksum` VARCHAR( 255 ) NOT NULL AFTER `name` ;