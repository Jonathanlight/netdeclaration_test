<?php

$n = $dbo->fetchValue('SELECT COUNT(*) FROM tkr_visitor');
$res->write('Nbre de visiteurs : '.$n."\n");

$n = $dbo->fetchValue('SELECT COUNT(*) FROM tkr_visit');
$res->write('Nbre de visites : '.$n."\n");

$n = $dbo->fetchValue('SELECT COUNT(*) FROM '.Tracker::TABLE_HIT);
$res->write('Nbre d\'évènements : '.$n."\n");

