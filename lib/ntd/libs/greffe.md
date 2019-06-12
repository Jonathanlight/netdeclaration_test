# Flux de fichiers
## Status du greffe

- Qui êtes vous ?
- Collecte des pièces à fournir
- En attente de validation
- Validé, en attente d'envoi
- Envoyé
- Accepté
- Rejeté

## Cycle de vie des fichiers dans l'API
Les documents et le XML sont prêts à êtres mis en archive une fois au status "Validé, en attente d'envoi" (Le XML est d'ailleurs généré a cette étape).
L'archive est générée et mise à disposition dans le dossier "doc/amitel/demande" et le greffe n'est plus éditable.

Toutes les heures un CRON viens vérifier la présence de nouveaux ACKs dans le dossier "doc/amitel/accuse".
Le contenu du fichier ACK est alors enregistré puis supprimé ainsi que l'archive correspondante dans le dossier de demande. Le greffe passe alors au status "Envoyé".

De même que pour les ACK, un CRON viens vérifier la présence d'archives de réponse dans le dossier "doc/amitel/reponse". Pour chaque fichiers, on inspecte l'archive:

* Si l'archive contient le fichier "rejet.pdf", le greffe passe au status "Rejeté" et deviens à nouveau éditable.
* Sinon, le greffe passe au status "Accepté".

Dans les deux cas, le contenu de l'archive est déplacé et décompressé dans le dossier "doc/greffes/<clé du greffe>" pour être consultable à la fois par l'adhérent depuis le dépôt greffe mais aussi par NetDeclaration depuis le BO.

Lorsque le greffe passe au status "Accepté", les documents enregistrés pour le greffe sont supprimés.
ces fichiers sont stockés dans le dossier "doc/amitel/.greffes/<id>".
