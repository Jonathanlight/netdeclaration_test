# Formulaires TS 2016

> Mise à jour des formulaires pour le millésime 2017
> Corrections sur 2016 (nouvelle version)

## Millésime 2016

### 2502

```bash
# Génération des action/template
php init.php ntd/formulaire.duplicate.v1 name="ts2502_201512" new_name="ts2502_201512_b"
```

- Ajouter le millésime 2015, 2016 sur le Fomulairetype `ts2502_201512_b` et modifier les informations
- Dupliquer le Dectype `TS 2502 2015 version b` ( 172 ) en `TS 2502 2015 version c` ( 248 )
- Ajouter le Dectype au service lié


## Millésime 2017

```sql
INSERT INTO `ntd_millesime` (`id`, `content`, `description`, `end_at`, `flags`, `image`, `name`, `start_at`, `status`) VALUES (NULL, '', '', '2017-12-31', '0', '', '2017', '2017-01-01', '1');
```


### 2501
Aucun changements


### 2502

```bash
# Génération des action/template
php init.php ntd/formulaire.duplicate.v1 name=ts2502_201512 new_name=ts2502_201610
```

- Ajouter le millésime 2017 sur le Fomulairetype `ts2502_201610` et modifier les informations
- Dupliquer le Dectype `TS 2502 2015 version b` ( 172 ) en `TS 2502 2017` ( 247 )
- Ajouter le Dectype au service lié
