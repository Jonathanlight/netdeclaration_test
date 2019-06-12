# Upgrade Form V2

```sql
-- Increase "value" size 10 => 255
ALTER TABLE `ntd_dicoedi` CHANGE `value` `value` VARCHAR(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL;
```
