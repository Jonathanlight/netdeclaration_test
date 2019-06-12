<?php

try {
  $form = (array) $req->form;

  if($form['sign_cgu'] == 'yes') {

      $h = array('host' => $req->getClient('host'),
                 'ip' => long2ip($req->getClient('ip')),
                 'date' => Date::now(),
                 'cgu_version' => P('cgu.version'));
      $attrs = array('cgu_sign_key' => Adherent::generateKey($h),
                     'cgu_sign_infos' => serialize($h),
                     'last_cgu_sign_infos' => $ctx->_current_adherent->cgu_sign_infos);

      $ctx->_current_adherent->commit($attrs);
  }

  $res->sendRedirect('/middle/home');

}
catch (Exception $e) {
  $err->add($e);
}
