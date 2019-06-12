
CREATE TABLE `ntd_estimation` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `adherent_address` varchar(255) NOT NULL,
  `adherent_level` varchar(255) NOT NULL,
  `adherent_name` varchar(255) NOT NULL,
  `adherent_type` varchar(255) NOT NULL,
  `country_id` int(10) unsigned NOT NULL default '0',
  `demandeur_name` varchar(255) NOT NULL,
  `demandeur_details` text NOT NULL,
  `expire_at` date NOT NULL,
  `flags` int(10) unsigned NOT NULL default '0',
  `name` varchar(255) NOT NULL,
  `tax_amount` double NOT NULL default '0',
  `tax_percent` double NOT NULL default '0',
  `total_amount_ht` double NOT NULL default '0',
  `total_amount_ttc` double NOT NULL default '0',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8;



CREATE TABLE `ntd_estimation_tarif` (
  `estimation_id` int(10) unsigned NOT NULL default '0',
  `tarif_id` int(10) unsigned NOT NULL default '0',
  `quantity` int(10) unsigned NOT NULL default '0',
  `amount_unitary` double NOT NULL default '0',
  `amount_total` double NOT NULL default '0',
  KEY `estimation_id` (`estimation_id`,`tarif_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;