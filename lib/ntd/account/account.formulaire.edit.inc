<?php

try {

  $adherent = Adherent::getInstance(array('id' => (int) $req->adherent_id, 'user_id' => $user->getId()));
  $declaration_dectype = Dectype::getInstance((int) $req->declaration_dectype_id);
  $id = (int) $req->id;
  if ($id > 0) {
    $formulaire = Formulaire::getInstance($id);
    $formulaire_type = Formulairetype::getInstance($formulaire->formulairetype_id);
    $formulaire_data = $formulaire->data;
    $formulaire_opts = $formulaire->opts;
    $declaration = $formulaire->getDeclaration();
  }
  else {
    $formulaire = Formulaire::getInstance();
    $formulaire_type = Formulairetype::getInstance((int) $req->formulaire_type);
    $formulaire_data = Formulaire::asFormulairePreFilledHash($formulaire_type, $adherent);
    $formulaire_opts = array();
    $declaration = Declaration::getInstance();
  }

  Formulaire::initData($formulaire_type->name);
  $ctx->adherent = $adherent;
  $ctx->declaration = $declaration;
  $ctx->declaration_dectype = $declaration_dectype;
  $ctx->formulaire = $formulaire;
  $ctx->formulaire_type = $formulaire_type;
  $ctx->formulaire_code = $formulaire_type->name;
  $ctx->formulaire_title = $formulaire_type->title;
  $ctx->{$formulaire_type->name} = $formulaire_data;
  $ctx->{$formulaire_type->name . '_opts'} = $formulaire_opts;
  $ctx->occurence = $req->hasAttribute('occurence') ? $req->occurence : 0;

  $ctx->_keep_templates = true;

  $res->useTemplates(array(null, "app/ntd/templates/formulaires/formulaire.edit." . $formulaire_type->name.'.psp'));

}
catch (Exception $e) {
  $err->add($e);
}

