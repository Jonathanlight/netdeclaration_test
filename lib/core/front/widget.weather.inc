<?php

//$res->useTemplates(null, '');
//$res->useTemplate();

$cookie = $req->getCookie();

$res->close();
$res->write(W::weather($req->query));