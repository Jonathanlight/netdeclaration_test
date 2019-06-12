ALTER TABLE `ntd_dectype` ADD `limit_deposit` VARCHAR(6) NOT NULL COMMENT 'date limite de dépot (MMAAAA)' AFTER `flags`;
ALTER TABLE `ntd_dectype` DROP `limit_deposit`;
