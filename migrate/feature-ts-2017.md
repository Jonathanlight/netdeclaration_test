# Formulaires TS 2018

> Mise à jour des formulaires pour le millésime 2018

## Millésime 2018

### Création du millésime

```sql
INSERT INTO `ntd`.`ntd_millesime` (`id`, `content`, `description`, `end_at`, `flags`, `image`, `name`, `start_at`, `status`) VALUES (NULL, '', '', '2018-12-31', '0', '', '2018', '2018-01-01', '1');
```


## Déclarations

### TS 2501

```bash
# Génération des action/template
php init.php ntd/formulaire.duplicate.v1 name="ts2501_201512" new_name="ts2501_201810"
```

- Ajouter le millésime 2018 sur le Formulairetype `ts2501_201810` et modifier les informations
- Ajouter le millésime 2018 sur le Formulairetype `p_identif_20151020`
- Dupliquer le Dectype `TS 2501 2015 version b` ( 171 ) en `TS 2501 2017` ( 311 )
  - Operations > Dupliquer
- Remplacer le Formulairetype `ts2501_201512` par `ts2501_201810` avec le millésime `2018` sur le Dectype
- Modifier le millésime du Formulairetype `p_identif_20151020` par `2018`
- Ajouter le Dectype au service lié


### TS 2502

```bash
# Génération des action/template
php init.php ntd/formulaire.duplicate.v1 name="ts2502_201610" new_name="ts2502_201810"
```

- Ajouter le millésime 2018 sur le Formulairetype `ts2502_201810` et modifier les informations
- Ajouter le millésime 2018 sur le Formulairetype `p_identif_20151020`
- Dupliquer le Dectype `TS 2502 2017` ( 247 ) en `TS 2502 2018` ( 312 )
  - Operations > Dupliquer
- Remplacer le Formulairetype `ts2502_201610` par `ts2502_201810` avec le millésime `2018` sur le Dectype
- Modifier le millésime du Formulairetype `p_identif_20151020` par `2018`
- Ajouter le Dectype au service lié
