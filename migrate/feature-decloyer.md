# Decloyer

> Évolution du webservice adherent
> - Ajout du Decloyer dans "gestion" et "services"
> - Ajout de l'information "reception"


## SQL

```sql
ALTER TABLE `ntd_adherent` ADD `gestion_decloyer` TINYINT UNSIGNED NOT NULL AFTER `gestion_dsn`;
```

```sql
ALTER TABLE `ntd_service` ADD `flags_export_adherent_reception` MEDIUMINT(9) NOT NULL AFTER `flags_export_adherent`;
```
