<?php

try {
  
  $feed = 'http://es.noticias.yahoo.com/rss/internet.xml';

  $opts = array('filters' => array('guid' => 'xxx'),
                'modifiers' => array('ignore'));

  $rss = FeedReader::getInstance($feed);
  foreach ($rss as $entry) {
    if (empty($entry['guid']) && empty($entry['link'])) continue;
    if (empty($entry['title'])) continue;
    if (empty($entry['guid'])) {
      $entry['guid'] = md5($entry['link'].$entry['pubDate']);
    }
    $record = array('crc' => $entry['guid'],
                    'name' => $entry['title'],
                    'content' => $entry['description'],
                    'published_at' => $entry['pubDate'],
                    'medialink' => $entry['media:content'],
                    'link' => $entry['link']);
    $opts['filters']['guid'] = $entry['guid'];
    $dbo->update('adsl_news', $record, $opts);
    if ($dbo->affectedRows < 1) {
      $dbo->insert('adsl_news', $record, array('IGNORE'));
    }
  }
}
catch (Exception $e) { $log->trace('feed error'); }