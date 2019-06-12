# Formulaires TS 2019

> Mise à jour des formulaires pour le millésime 2019

## Millésime 2019

### Création du millésime

```sql
INSERT INTO `ntd`.`ntd_millesime` (`id`, `content`, `description`, `end_at`, `flags`, `image`, `name`, `start_at`, `status`) VALUES (NULL, '', '', '2019-12-31', '0', '', '2019', '2019-01-01', '1');
```

## Déclarations


### TS 2502

```bash
# Génération des action/template
php init.php ntd/formulaire.duplicate.v1 name="ts2502_201811" new_name="ts2502_201901"
```

- Ajouter le millésime 2019 sur le Formulairetype `ts2502_201901` et modifier les informations
