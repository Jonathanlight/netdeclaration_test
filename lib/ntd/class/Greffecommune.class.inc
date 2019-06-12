<?php

class Greffecommune extends ActiveRecord {
  const STATUS_ONLINE = 1;
  const STATUS_OFFLINE = 0;

  public static $statuses = array(self::STATUS_ONLINE  => 'en ligne',
                                  self::STATUS_OFFLINE => 'hors ligne');
}
