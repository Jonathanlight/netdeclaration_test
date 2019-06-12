<?php

$table_edi_credits = array(
  ''    => '----',
  'APR' => 'APR : Crédit d\'impôt en faveur de l\'apprentissage',
  'ART' => 'ART : Crédit d\'impôt en faveur des métiers d\'art',
  'AUD' => 'AUD : Crédit d\'impôt pour dépenses de productions déléguées d\'œuvres cinématographiques et audiovisuelles',
  'BIO' => 'BIO : Crédit d\'impôt en faveur de l\'agriculture biologique',
  'CAI' => 'CAI : Crédit d\'impôt en faveur de l\'intéressement',
  'CCI' => 'CCI : Crédit d\'impôt cinéma international',
  'CIC' => 'CIC : Crédit d\'impôt pour la compétitivité et l\'emploi',
  'CIN' => 'CIN : Crédit d\'impôt pour dépenses de production d\'œuvres cinématographiques ou audiovisuelles',
  'CIO' => 'CIO : Crédit d\'impôt pour investissement Outre Mer dans le secteur productif',
  'CIR' => 'CIR : Crédit d\'impôt en faveur de la recherche',
  'CJV' => 'CJV : Crédit d\'impôt en faveur des créateurs de jeux vidéo',
  'COL' => 'COL : Crédit d\'impôt pour investissement Outre Mer dans le secteur du logement social',
  'COR' => 'COR : Crédit impôt pour certains investissements réalisés et exploités en Corse',
  'CPE' => 'CPE : Crédit d\'impôt sur les avances remboursables pour travaux d\'amélioration de la performance énergétique',
  'CSV' => 'CSV : Crédit d\'impôt spectacle vivant',
  'EXP' => 'EXP : Crédit d\'impôt pour dépenses de prospection commerciale',
  'FAM' => 'FAM : Crédit d\'impôt famille',
  'FOR' => 'FOR : Crédit d\'impôt formation des dirigeants d\'entreprise',
  'MAI' => 'MAI : Crédit d\'impôt en faveur des maîtres restaurateurs',
  'PHO' => 'PHO : Crédit d\'impôt pour dépenses de production d\'œuvres phonographiques',
  'PTR' => 'PTR : Crédit d\'impôt prêt à taux 0 renforcé PTZ+',
  'PTZ' => 'PTZ : Crédit d\'impôt en faveur de la première accession à la propriété',
  'RAC' => 'RAC : Crédit pour le rachat d\'une entreprise par ses salariés',
  'RAD' => 'Report en arrière de déficits'
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


$form['is2573_2017'] = array(
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


foreach ($form["is2573_2017"] as $fieldname => $data) {
  $form["is2573_2017"][$fieldname]['operations'][]['assert'] = 'is2573_2017';
}
