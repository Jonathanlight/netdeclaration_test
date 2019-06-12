<?php

try {
  $form = (array) $req->form;

  if($form['sign'] == 'yes') {
    if ($ctx->_current_adherent->status == Adherent::STATUS_SUBSCRIPTION_PENDING) {
      $ctx->_current_adherent->setStatus(Adherent::STATUS_SUBSCRIPTION_SIGNATURE);
    }
    elseif ($ctx->_current_adherent->status == Adherent::STATUS_SUBSCRIPTION_SIGNATURE) {
      $h = array('host' => $req->getClient('host'),
                 'ip' => long2ip($req->getClient('ip')),
                 'date' => Date::now(),
                 'cgu_version' => P('cgu.version'));
      $attrs = array('status' => Adherent::STATUS_SUBSCRIPTION_VALIDE,
                     'sign_at' => Date::now(),
                     'sign_key' => Adherent::generateKey($h),
                     'sign_infos' => $h);

      $ctx->_current_adherent->commit($attrs);

      if ($ctx->_current_adherent->adherent_id < 1) {
        Letter::send(
              'adherent.status.activated',
              $ctx->_current_adherent->getEmail(),
              array('adherent.first_name' => $ctx->_current_primary_adherent->first_name,
                    'adherent.last_name' => $ctx->_current_primary_adherent->last_name,
                    'footer' => NetDeclaration::getMailFooter()));
      }
      else {
        Letter::send(
              'adherent.secondary.status.activated',
              $ctx->_current_adherent->getEmail(),
              array('adherent.first_name' => $ctx->_current_primary_adherent->first_name,
                    'adherent.last_name' => $ctx->_current_primary_adherent->last_name,
                    'adherent.secondary.first_name' => $ctx->_current_adherent->first_name,
                    'adherent.secondary.last_name' => $ctx->_current_adherent->last_name,
                    'footer' => NetDeclaration::getMailFooter()));
      }
    }
  }

  $res->sendRedirect('/middle/home');

}
catch (Exception $e) {
  $err->add($e);
}
