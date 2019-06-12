<?php

$opts = array('filters' => array('status' => Campaign::STATUS_SCHEDULED,
                                 '|<=|scheduled_at' => Date::now()));

$campaigns = Campaign::collect($opts);

foreach ($campaigns as $campaign) {
  $campaign->send();
  sleep(2);
}

