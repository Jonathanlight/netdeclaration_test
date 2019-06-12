# Formulairetype: Gestion des formulaires requis par context

```sql
ALTER TABLE `ntd_dectype_formulairetype` ADD `required_formulairetype_id` INT(11) UNSIGNED NOT NULL DEFAULT '0' AFTER `millesime_id`,
                                         ADD INDEX `idx_required_formulairetype_id` (`required_formulairetype_id`);
```
