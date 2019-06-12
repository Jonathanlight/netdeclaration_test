# Rappel Recouvrement

> Après un 3ème rappel, Netdéclaration procède à l’envoi d’un courrier AR de remise en recouvrement.
> Ceci représente une charge pour Netdéclaration: Rédaction des courriers,
> impression, remise à la poste.

> Le but sera ici de :
> - Réaliser automatiquement les lettres de recouvrement à partir d’un modèle
> - Alerte Netdéclaration chaque Vendredi si des rappels doivent ou non être envoyés, et si le cas est positif, le mail automatique fournira un lien pour télécharger les courriers (qui pourra ensuite les imprimer)


<div class="page-break"></div>

## Fragments

| Code | Valeur |
| :------------- | :------------- |
| template_mail_recovery_pdf | <table class="fixed" style="width:100%"><tbody><tr><td style="width: 50%;"><br></td><td style="width: 50%;">((company))<br>((address))<br>((zipcode)) ((city))<br><br>Montpellier le ((date))</td></tr></tbody></table><br><br>COMPTE : ((siret))<br><br><strong>OBJET: MISE EN RECOUVREMENT<br></strong><strong><br></strong><br><br>Madame, Monsieur,<br><br>Nous vous rappelons que votre paiement pour la/les facture(s) suivantes ne nous est toujours pas parvenu malgré nos trois précédentes relances par email.<br><br>((facture_list))<br><br>Si vous désirez ne plus utiliser nos services, vous devez nous transmettre une lettre RAR, comme stipulé dans l'article 7 de nos conditions générales de vente:<br><br>« Sauf dispositions spécifiques prévues aux conditions particulières, le contrat est conclu pour une période d'un an, renouvelable par tacite reconduction. Les parties auront la faculté de dénoncer la convention à l'issue de la période susvisée moyennant l'envoi d'un préavis au moins trois mois avant son échéance. La dénonce sera faite par Lettre Recommandée avec Avis de Réception »<br><br>L'envoi de la lettre RAR, n'exempt pas le paiement de la/les facture(s) citée en objet, la résiliation étant effective pour le prochain renouvellement.<br><br><strong>Sans paiement de la somme de ((montant_facture_total)) Euros sous huitaine, les services seront suspendus et le dossier sera transmis à l'Organisme de Recouvrement.</strong><br><br>Veuillez ne pas tenir compte de ce courrier si vous avez déjà envoyé votre règlement.<br><br>Dans cette attente, nous vous prions d'agréer, Madame, Monsieur, nos sincères salutations<br><br><div align="center">Service comptabilité</div> |


<div class="page-break"></div>

## Courriers

| Code | App | Sujet | Corps |
| :------------- | :------------- | :------------- | :------------- |
| alert_recovery | ntd | Alerte Recouvrement | Bonjour,<br><br>Cette alerte vous informe que :<br><br>((message))<br><br>Netdéclaration |


<div class="page-break"></div>

## SQL

```sql
ALTER TABLE `ntd_facture` ADD `recovery_at` DATE NOT NULL AFTER `price_ttc`,
                          ADD `is_recovery` TINYINT UNSIGNED NOT NULL AFTER `data_reglement`;
```
