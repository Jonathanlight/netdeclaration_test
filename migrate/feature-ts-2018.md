# Formulaires TS 2018

> Mise à jour des formulaires pour le millésime 2018

## Millésime 2019

### Création du millésime

```sql
INSERT INTO `ntd`.`ntd_millesime` (`id`, `content`, `description`, `end_at`, `flags`, `image`, `name`, `start_at`, `status`) VALUES (NULL, '', '', '2018-12-31', '0', '', '2018', '2018-11-01', '1');
```

## Déclarations


### TS 2502

```bash
# Génération des action/template
php init.php ntd/formulaire.duplicate.v1 name="ts2502_201810" new_name="ts2502_201811"
```

- Ajouter le millésime 2018 sur le Formulairetype `ts2502_201811` et modifier les informations
