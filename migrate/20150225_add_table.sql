CREATE TABLE `ntd_service_dectype` (
  `service_id` INT UNSIGNED NOT NULL DEFAULT '0',
  `dectype_id` INT UNSIGNED NOT NULL DEFAULT '0',
  INDEX ( `service_id` , `dectype_id` )
) ENGINE = MYISAM ;
