<?php

$table_edi_credits = array(
  ''    => '----',
  'APR' => 'APR : Apprentissage',
  'ART' => 'ART : Métiers d\'art',
  'AUD' => 'AUD : Formats audiovisuels',
  'BIO' => 'BIO : Agriculture biologique',
  'CAI' => 'CAI : Intéressement',
  'CCI' => 'CCI : Cinéma international',
  'CIC' => 'CIC : Compétitivité des entreprises',
  'CIN' => 'CIN : Cinéma',
  'CIO' => 'CIO : Outre Mer secteur productif',
  'CIR' => 'CIR : Recherche',
  'CJV' => 'CJV : Création de jeux vidéo',
  'COL' => 'COL : Outre Mer logement social',
  'COR' => 'COR : Investissements réalisés et exploités en Corse',
  'CPE' => 'CPE : Eco-PTZ',
  'CSV' => 'CSV : Spectacle vivant',
  'EXP' => 'EXP : Dépenses de prospection commerciale',
  'FAM' => 'FAM : Famille',
  'FOR' => 'FOR : Dépenses de formation des dirigeants',
  'MAI' => 'MAI : Maîtres restaurateurs',
  'PHO' => 'PHO : Production d\'œuvres phonographiques',
  'PTR' => 'PTR : Prêt à taux "plus"',
  'PTZ' => 'PTZ : Prêt à taux zéro',
  'RAC' => 'RAC : Rachat d\'une entreprise par ses salariés',
  'RAD' => 'RAD : Report en arrière de déficits'
);

$table_edi_credits_wo_RAD = $table_edi_credits;
unset($table_edi_credits_wo_RAD['RAD']);

$table_edi_procedures = array(
  ''   => '----',
  'CL' => 'CL : Conciliation',
  'LJ' => 'LJ : Liquidation judiciaire',
  'RJ' => 'RJ : Redressement judiciaire',
  'SV' => 'SV : Jugement de sauvegarde'
);

$table_edi_motifs = array(
  ''    => '----',
  'ENN' => 'ENN : entreprise nouvelle',
  'JEI' => 'JEI : Jeune entreprise innovante',
  'PME' => 'PME : PME au sens communautaire'
);

$table_edi_codes = array(
  ''    => '----',
  'FPC' => 'FPC : Formation Professionnelle continue',
  'PEC' => 'PEC : Participation des employeurs à l\'effort de construction',
  'TA'  => 'TA : Taxe d\'apprentissage',
  'TS'  => 'TS : Taxe sur les salaires',
  'TVA' => 'TVA : TVA',
  'TVS' => 'TVS : Taxe sur les véhicules de sociétés'
);


$form['is2573_2018'] = array(
  'AA' => array('type' => 'checkbox'),
  'AB' => array('type' => 'select', 'options' => $table_edi_credits),
  'AC' => array('type' => 'date-ssaa', 'range' => 13),
  'AF' => array('type' => 'number', 'length' => 15),
  'AG' => array('type' => 'number', 'length' => 15),
  'AH' => array('type' => 'select', 'options' => $table_edi_procedures),
  'AI' => array('type' => 'date-ssaammjj'),
  'AJ' => array('type' => 'number', 'length' => 15),
  'BA' => array('length' => 9, 'type' => 'alphabetic'),
  'BB' => array('type' => 'date-ssaammjj'),
  'BC' => array('type' => 'date-ssaammjj'),
  'BD' => array('length' => 9, 'type' => 'alphabetic'),
  'BE' => array('type' => 'number', 'length' => 15),
  'BF' => array('type' => 'number', 'length' => 15),
  'CA' => array('length' => 9, 'type' => 'alphabetic'),
  'CB' => array('type' => 'select', 'options' => $table_edi_credits_wo_RAD),
  'CC' => array('type' => 'date-ssaammjj'),
  'CD' => array('type' => 'date-ssaammjj'),
  'CE' => array('length' => 9, 'type' => 'alphabetic'),
  'CF' => array('type' => 'number', 'length' => 15),
  'CG' => array('type' => 'number', 'length' => 15),
  'KA' => array('type' => 'select', 'options' => $table_edi_motifs),
  'KB' => array('type' => 'select', 'options' => $table_edi_codes),
  'KC' => array('type' => 'date-ssaammjj'),
  'KD' => array('type' => 'number', 'length' => 15),
);


foreach ($form["is2573_2018"] as $fieldname => $data) {
  $form["is2573_2018"][$fieldname]['operations'][]['assert'] = 'is2573_2018';
}
