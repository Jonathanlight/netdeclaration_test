<?php

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
    print "Temps moyen : " . number_format($this->cluster * $this->average_time, 3) . ' secondes' . "\n";
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
