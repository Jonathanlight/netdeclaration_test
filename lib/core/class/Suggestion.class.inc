<?php

class Suggestion {

  const TABLE = 'sys_suggestion';
  const TABLE_HIT = 'sys_suggestion_hit';
  
  public static function append($item) { 
    $dbo = S('dbo');
    $ht = $dbo->asHash('SELECT locale, id'
                       .' FROM '.self::TABLE
                       .' WHERE model_id='.$item->getModelId()
                       .  ' AND record_id='.$item->getId()); 
    $locales = $item->getLocales();  
    foreach ($locales as $locale) { 
      $record = $item->asSuggestionHash($locale); 
      Hash::crush($record); 
      $record['model_id'] = $item->getModelId();
      $record['record_id'] = $item->getId();
      $record['locale'] = $locale;
      $id = $ht[$locale];
      if ($id >= 1) {
        $opts = array('filters' => array('id' => $id));
        $dbo->update(self::TABLE, $record, $opts);
      }
      else { 
        $dbo->insert(self::TABLE, $record);
      }
    } 
    foreach ($ht as $locale => $id) {
      if (in_array($locale, $locales)) continue ;
      $dbo->exec('DELETE FROM '.self::TABLE
                 .    ' WHERE id='.$id
                 .    ' LIMIT 1');
    }
  }

  public static function remove($item) {
    S('dbo')->exec('DELETE FROM '.self::TABLE
                   .    ' WHERE model_id='.$item->getModelId()
                   .      ' AND record_id='.$item->getId());
  }
  
}