<?php

try {

    if (S('ctx')->_current_adherent->cgu_sign_infos) {
        $cguSignInfos = unserialize(S('ctx')->_current_adherent->cgu_sign_infos);
        $currentCguVersion = $cguSignInfos['cgu_version'];
    } else {
        $currentCguVersion = null;
    }


  $ctx->sign_infos = S('ctx')->_current_adherent->sign_infos;
  if (P('cgu.version') == $currentCguVersion) {
    S('res')->sendRedirect('/middle/home');
    return;
  }

  NtdMiddleManager::useTemplate();

}
catch (Exception $e) {
  $err->add($e);
}
