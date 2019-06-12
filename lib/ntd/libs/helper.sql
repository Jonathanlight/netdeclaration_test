SELECT ss.destinataire_id, se.name  FROM `ntd_souscription_suivi` ss
LEFT JOIN ntd_souscription s ON (ss.souscription_id = s.id)
LEFT JOIN ntd_service se ON (se.id = s.service_id)
WHERE ss.`destinataire_id` IN (383940,257688,233109,265361,265362,245443,375420,384331,433142,473791,201470,257686,184353)
ORDER BY ss.`destinataire_id` ASC