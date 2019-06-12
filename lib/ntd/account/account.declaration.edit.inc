<?php

try {

  $user = $req->getUser();
  $id = (int) $req->declaration_id;

  $formulairesAsArray = array();
  $formulaireTypesId = array();
  $formulairesArray = array();

  if ($id > 0) {
    $declaration = Declaration::getInstance($id);
    $declaration_dectype = $declaration->getDectype();
    $adherent = $declaration->getAdherent();
    $formulaires = $declaration->getFormulaires();
    foreach ($formulaires as $k => $formulaire) {
        $formulaireTypesId[] = $formulaire->formulairetype_id;
        $formulairesArray[$k] = array(
            'id' => $formulaire->getId(),
            'formulairetype_id' => $formulaire->formulairetype_id,
            'position' => $formulaire->position,
        );
        $formulaireType = $formulaire->getFormulairetype();
        $data = $formulaire->data;
        if ($formulaireType->document_code == Formulairetype::DOCUMENT_CODE_HON) {
            if ($formulaireType->code == Formulairetype::CODE_DAS2T) {
                $formulairesArray[$k]['companyName'] = $data['AA02'] ?: $data['AA03'];
            } else {
                $formulairesArray[$k]['companyName'] = $data['AF02'] ? $data['AF02'].' '.$data['AF03'] : $data['AE02'];
            }
        } elseif ($formulaireType->document_code == Formulairetype::DOCUMENT_CODE_IFU) {
            $formulairesArray[$k]['companyName'] = $data['AF02'] ? $data['AF02'].' '.$data['AF03'] : $data['AE02'];
        }
    }
  }
  else {
    $declaration = Declaration::getInstance();
    $declaration_dectype = Dectype::getInstance((int) $req->dectype_id);
    $adherent = Adherent::getInstance(array('user_id' => $user->getId(),
                                            'id' => (int) $req->adherent_id));
    $formulaires = array();
  }

  $ctx->formulaireTypesId = $formulaireTypesId;
  $ctx->formulairesArray = $formulairesArray;

  if (!$declaration_dectype->hasFlag(Dectype::FLAG_OLD_SYSTEM)) {
    $res->sendRedirect('/account/declaration/wrapper', array('dectype_id' => (int) $req->dectype_id,
                                                             'declaration_id' => (int) $req->declaration_id));
  }  

  $formulaires_data = array(Dectype::RELATION_TYPE_OBLIGATOIRE => array(),
                           Dectype::RELATION_TYPE_ANNEXE => array());

  foreach($declaration_dectype->getFormulairetypes(array('order' => array('ftype_position' => 'ASC'))) as $ftype) {
    $formulaires_data[$ftype->ftype_type][$ftype->getId()] = array('formulairetype' => $ftype);
    foreach ($formulairesArray as $form) {
        if ($form['formulairetype_id'] == $ftype->getId()) {
            $formulaires_data[$ftype->ftype_type][$ftype->getId()]['forms'][$form['id']]['id'] = $form['id'];
            $formulaires_data[$ftype->ftype_type][$ftype->getId()]['forms'][$form['id']]['position'] = $form['position'];
        }
    }
  }

  $ftypesForm = array();
  foreach ($declaration_dectype->getFormulairetypes(array('order' => array('ftype_position' => 'ASC'))) as $ftype) {
      $millesime = Millesime::getInstance($ftype->ftype_millesime_id);
      $ftypesForm[] = array(
          'millesime' => $millesime,
          'ftype' => $ftype,
          'repetable' => $ftype->isRepetable($millesime),
      );
  }

  $ctx->ftypesForm = $ftypesForm;

  $ctx->return_link = $req->getClient('referer') ? '/' . str_replace(H::url('/'), '', $req->getClient('referer')) : '/middle/declarer';
  $ctx->adherent = $adherent;
  $ctx->declaration = $declaration;
  $ctx->declaration_dectype = $declaration_dectype;
  $ctx->formulaires_data = $formulaires_data;  
  $ctx->formulaires = $formulaires;

  $ctx->_keep_templates = true;
  $res->useTemplates(array(null, 'skeleton.formulaire', true));
  $res->addScript('/app/ntd/scripts/repetable.v1.js');
  $res->setTitle('Déclaration ' . $declaration_dectype->name);
}
catch (Exception $e) {
  $err->add($e);
}
