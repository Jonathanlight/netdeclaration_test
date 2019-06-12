<?php

try {

  $declaration = Declaration::getInstance((int) $req->declaration_id);
  $formulaires = $declaration->getFormulaires();
  $decType = $declaration->getDectype();
  $currentMillesime = $decType->getMillesime();
  $nextMillesimeAttrs = array('start_at' => date('Y-m-d', strtotime(date("Y-m-d", strtotime("+1 years", strtotime($currentMillesime->start_at))))));

  $newDecTypeExists = false;

  if (Millesime::exists($nextMillesimeAttrs)) {
      $nextMillesime = Millesime::getInstance($nextMillesimeAttrs);
      $decTypeAttrs = array('code' => $decType->code, 'millesime_id' => $nextMillesime->getId());
      if (Dectype::exists($decTypeAttrs)) {
          $nextYearDecType = Dectype::getInstance($decTypeAttrs);
          $newDecTypeExists = true;
      }
  }

  if (!$newDecTypeExists && $req->hasAttribute('next_year')) {
      throw new Exception(c(l('account.declarer.duplicate.error')) . ' ' . date('Y', strtotime('+1 year')));
  }

  $declaration_duplicated = Declaration::getInstance();
  $declaration_commit = $declaration->getAttributes();
  unset($declaration_commit['suivi_id']);
  $declaration_commit['status'] = Declaration::STATUS_EDITABLE;
  if (isset($nextYearDecType)) {
      $declaration_commit['dectype_id'] = $nextYearDecType->getId();
  }
  $declaration_duplicated->commit($declaration_commit);

  foreach($formulaires as $formulaire) {
    $formulaire_duplicated = Formulaire::getInstance();
    $formulaire_commit = $formulaire->getAttributes();
    $formulaire_commit['declaration_id'] = $declaration_duplicated->getId();
    $formulaire_duplicated->commit($formulaire_commit);
  }

  $ctx->declaration_id = $declaration_duplicated->getId();

}
catch (Exception $e) {
  $err->add($e);
}
