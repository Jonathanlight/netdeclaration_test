<?php

try {

/*
  $total_found_rows = 0;

  //S('dbo')->query("UPDATE `ntd_suivi` SET `adherent_id` = '0'");
  //S('dbo')->query("TRUNCATE `ntd_destinataire_adherent`");

  $filters = array('|#|destinataire_id' => T('destinataire') . '.id NOT IN (SELECT da.destinataire_id FROM ntd_destinataire_adherent AS da)');
  $opts = array('filters' => $filters,
                'order' => array(T('destinataire') . '.id' => 'ASC'),
                'include' => array('suivi'));
  $destinataires = Destinataire::collect($opts);
  $progress = new CliUIProgress(__FILE__, $destinataires->count(), 1000);
  foreach ($destinataires as $destinataire) {
    if (!empty($destinataire->suivi_siret_decl) && ($adherent_id = Adherent::exists(array('siret' => $destinataire->suivi_siret_decl)))) {
      S('dbo')->insert(Destinataire::TABLE_ADHERENT_DESTINATAIRE, array('destinataire_id' => $destinataire->id,
                                                                        'adherent_id' => $adherent_id,
                                                                        'type' => Destinataire::ADHERENT_TYPE_DECLARANT));
    }
    if (!empty($destinataire->suivi_siret_emetteur) && ($adherent_id = Adherent::exists(array('siret' => $destinataire->suivi_siret_emetteur)))) {
      S('dbo')->insert(Destinataire::TABLE_ADHERENT_DESTINATAIRE, array('destinataire_id' => $destinataire->id,
                                                                        'adherent_id' => $adherent_id,
                                                                        'type' => Destinataire::ADHERENT_TYPE_EMETTEUR));
    }
    if (!empty($destinataire->siret) && ($adherent_id = Adherent::exists(array('siret' => $destinataire->siret)))) {
      S('dbo')->insert(Destinataire::TABLE_ADHERENT_DESTINATAIRE, array('destinataire_id' => $destinataire->id,
                                                                        'adherent_id' => $adherent_id,
                                                                        'type' => Destinataire::ADHERENT_TYPE_DESTINATAIRE));
    }
    $progress->iterate();

  }
*/
  print 'Terminé ';
  return;

  foreach (Adherent::collect() as $adherent) {
    print $adherent->getId() . ' : ';

    $sirets_declarants = $adherent->getAllSirets();
    $sirets_declarants = array_unique($sirets_declarants);

    $opts_form = array();
    $filters = array( //0 => $opts_form,
                      1 => array('OR' => $opts_form),
                      //                 2 => array('OR' => $opts_form)
    );
    //$filters[0]['|IN|' . T('suivi') . '.siret_decl'] = $sirets_declarants;
    $filters[1]['OR']['|IN|' . T('suivi') . '.siret_emetteur'] = $sirets_declarants;
    //$filters[2]['OR']['|IN|' . T('destinataire') . '.siret'] = $sirets_declarants;


    // DESTINATAIRES
    $opts = array('filters' => $filters,
                  //'order' => array(T('suivi') . '.date_depot' => 'DESC'),
                  'include' => array('suivi'));
    $destinataires = Destinataire::collect($opts);
    $destinataires->trace();


    $suivis = Suivi::collect(array('filters' => array('|IN|siret_emetteur' => $sirets_declarants)));
    $found_rows = $suivis->foundRows();
    //if($found_rows > 100) {
    print $found_rows . "\n";
    $total_found_rows += $found_rows;
    //}
    print "Traitement : ";
    foreach ($suivis as $suivi) {
      if ($suivi->adherent_id > 0) {
        $adherent_id = 99999999;
      }
      else {
        $adherent_id = $adherent->getId();
      }
      $suivi->setAttribute('adherent_id', $adherent_id);
    }
    print "OK\n";

    /*$found_rows = $destinataires->foundRows();
    //if($found_rows > 100) {
    print $found_rows . "\n";
    $total_found_rows += $found_rows;
    //}
    print "Traitement : ";
    foreach ($destinataires as $destinataire) {
      $suivi = $destinataire->getSuivi();
      if ($suivi->adherent_id > 0) {
        $adherent_id = 9999999999;
      }
      else {
        $adherent_id = $adherent->getId();
      }
      $suivi->setAttribute('adherent_id', $adherent_id);
    }
    print "OK\n";      */

    /*continue;
   // SUIVI
   $opts = array('filters' => array('|IN|id' => $destinataires->asHash('suivi_id', 'suivi_id')),
                 'offset' => $offset,
                 'limit' => $limit,
                 'order' => array('date_depot' => 'DESC'));
   $suivis = Suivi::collect($opts);

   // FORM FILTERS
   $fields_options = array('siret_emetteur' => array(),
                           'siret_decl' => array(),
                           'type_doc' => array(),
                           'type_decl' => array());
   $sql = 'SELECT SQL_CACHE #field# FROM #table# WHERE id IN ([suivis_id]) GROUP BY #field# ORDER BY #field#';
   $bindings = array('#table#' => T('suivi'),
                     '[suivis_id]' => $suivis->asHash('id', 'id'));

   foreach ($fields_options as $field => $options) {
     $bindings['#field#'] = $field;
     $fields_options[$field] = S('dbo')->query($sql, $bindings)->asHash($field, $field);
   }


   $ctx->current_adherent = $current_adherent;
   $ctx->suivis = $suivis;
   $ctx->destinataires_founds = Destinataire::collect(array('filters' => array('|IN|suivi_id' => $suivis->asHash('id', 'id'))));

   $ctx->fields_options = $fields_options;
    */
  }

  print 'Total found rows : ' . $total_found_rows . "\n";
  print 'Terminé !';


}
catch (Exception $e) {
  print $e->getMessage();
}


class CliUIProgress {

  private $iteration;
  private $average_time;
  private $elapsed_time;
  private $total_time;
  private $count;
  private $label;
  private $cluster;

  public function __construct($label = 'pas de label', $count = 1, $cluster = 1) {
    $this->iteration = 0;
    $this->average_time = 0;
    $this->total_time = 0;
    $this->count = $count;
    $this->cluster = $cluster;
    $this->label = $label;
    $this->begin_iterate_at = microtime(true);
  }

  public function iterate() {
    $this->iteration++;
    if (($this->iteration % $this->cluster)) return;
    $iteration_duration = (microtime(true) - $this->begin_iterate_at);
    $this->elapsed_time += $iteration_duration;
    $this->average_time = $this->elapsed_time / $this->iteration;
    $total_estimated_time = $this->average_time * $this->count;
    $left_time = $total_estimated_time - $this->elapsed_time;

    $this->begin_iterate_at = microtime(true);

    print "### $this->label #################################################################################################\n";
    print "Temps moyen : " . number_format($this->average_time, 3) . ' secondes' . "\n";
    print "Temps Total : " . $this->formatDuration((int) $this->elapsed_time) . " (" . $this->iteration . "/" . $this->count . ")\n";
    print "Temps total estimé : " . $this->formatDuration((int) $total_estimated_time) . "\n";
    print "Temps restant estimé : " . $this->formatDuration((int) $left_time) . "\n";
  }


  private function formatDuration($time) {
    $secondes = $time;
    $minutes = floor($secondes / 60);
    $secondes -= $minutes * 60;
    $heures = floor($minutes / 60);
    $minutes -= $heures * 60;
    //return $heures . 'h' . str_pad($minutes, 2, ' ', STR_PAD_LEFT). 'm' . str_pad($secondes, 2, ' ', STR_PAD_LEFT) . 's';
    return str_pad($heures, 2, ' ', STR_PAD_LEFT) . ':' . str_pad($minutes, 2, '0', STR_PAD_LEFT) . ':' . str_pad($secondes, 2, '0', STR_PAD_LEFT) . '';
  }
}