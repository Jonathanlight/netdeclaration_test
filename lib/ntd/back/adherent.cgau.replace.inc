<?php

try {

    $record = (array) $req->record;

    $adherent = Adherent::getInstance($record['adherent_id']);

    $attrs = array(
        'cgu_sign_infos' => $adherent->last_cgu_sign_infos,
    );

    $adherent->commit($attrs);

    $res->sendMessage('Les CGAU ont bien été remplacées. Pensez à rafraichir la page.');

}
catch (Exception $e) {
    $err->add($e);
}
