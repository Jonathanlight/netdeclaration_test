# Newsletter

## Phrases
| Code | Nom |
| :------------- | :------------- |
| signup.step.newsletter | Inscription à la newsletter |
| signup.step.newsletter.description | Souscrivez à la newsletter |
| account.newsletter | Newsletter |
| alert.newsletter.changed | Les informations de newsletter ont bien été mises à jour |

## Fragments
| Code | Nom |
| :------------- | :------------- |
| account.page.newsletter | Newsletter |


## SQL
```sql
-- Purge de l'extension Push
TRUNCATE TABLE `psh_act`;
TRUNCATE TABLE `psh_base`;
TRUNCATE TABLE `psh_base_email`;
TRUNCATE TABLE `psh_body`;
TRUNCATE TABLE `psh_campaign`;
TRUNCATE TABLE `psh_mailing`;
TRUNCATE TABLE `psh_mailing_item`;
TRUNCATE TABLE `psh_newsletter`;
TRUNCATE TABLE `psh_queue`;
TRUNCATE TABLE `psh_smtp`;

DELETE FROM `sys_item_meta` WHERE `model` IN (800, 801, 803, 805, 804);
```

## Scripts
```bash
# Création des Bases newsletter
php init.php ntd/tool.newsletter.init
```
