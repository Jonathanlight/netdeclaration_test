# Import des champs

- Nettoyer le dictionnaire de données fournit par Netdeclaration. Reprendre le format de doc/kernix/imports/ifields_liasse_2019.csv

!! Attention !!

Dans la colonne codification EDI => passer la dernière valeur sur 1 chiffre. Exemple : 
"AB:C108:4440:01:" devient "AB:C108:4440:1:"

- Ajouter la notion "extensible" pour les ifields:

Requête SQL pour récupérer les IDs des ifields présent dans les formulaires de l'année courrante qui étaient extensibles 
l'année précédente (ici im.millesime_id = 12 correspond à 2018 et fm.millesime_id = 13):

SELECT id 
FROM ntd_ifield i
JOIN ntd_ifield_millesime im ON (im.ifield_id = i.id)
WHERE im.millesime_id = 12
AND im.is_extensible = 1
AND i.formulairetype_id 
IN (SELECT id
FROM `ntd_formulairetype` f 
JOIN `ntd_formulairetype_millesime` fm ON (fm.formulairetype_id = f.id) 
WHERE f.name LIKE 'tdfc%'
AND fm.millesime_id = 13)

Il est impossible de faire un "UPDATE" avec dans l'une des conditions, la table qui est mise à jour. Il faut donc exporter les résultats de la requête précédente et faire un update:
UPDATE ntd_ifield_millesime SET is_extensible = 1 WHERE millesime_id = 13 AND ifield_id IN ([RESULTAT DE L'EXPORT])

- Ajouter la notion "extensible" à la main pour les nouveaux champs

- Penser à supprimer le millesime de l'année en cours pour les champs "supprimés"


# FORMULAIRES

- Ajouter la notion "repetable" pour les formulairetype

Requête SQL pour récupérer les IDs des formulairetype de l'année courrante qui étaient répétables 
l'année précédente:

SELECT id 
FROM ntd_formulairetype f
JOIN ntd_formulairetype_millesime fm ON (fm.formulairetype_id = f.id)
WHERE fm.millesime_id = 12
AND fm.is_repetable = 1
AND f.id 
IN (SELECT id
FROM `ntd_formulairetype` f 
JOIN `ntd_formulairetype_millesime` fm ON (fm.formulairetype_id = f.id) 
WHERE f.name LIKE 'tdfc%'
AND fm.millesime_id = 13)
