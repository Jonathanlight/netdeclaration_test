<?php

class DashBoard
{
  private $blocks = null;
  private $period = null;
  private $year = null;
  private $month = null;
  private $day = null;
  private $format = '';
  private $value = '';

  public function __construct($period) {
    $this->blocks = array();
    $this->period = $period;
    list ($this->year, $this->month, $this->day) = explode('-', $this->period);
    $this->year = (int) $this->year;
    $this->month = (int) $this->month;
    $this->day = (int) $this->day;
    if ($this->year > 0) {
      $this->format .= '%Y';
      $this->value .= $this->year;
    }
    if ($this->month > 0) {
      $this->format .= '%c';
      $this->value .= $this->month;
    }
    if ($this->day > 0) {
      $this->format .= '%e';
      $this->value .= $this->day;
    }
  }
  
  public function getBlock() {
    $dbb = new DashBoardBlock();
    $this->blocks[] = $dbb;
    $dbb->dashboard = $this;
    return $dbb;
  }

  public function asHtml($locale) {
    $html = '';
    if (S('req')->match('dashboard.overview$')) {
      $html .= '<div class="hbox-label">Période : '.$this->getPeriodLabel().'</div>';
    }
    foreach ($this->blocks as $block) {
      $html .= $block->asHtml($locale)."\n";
    }
    return $html;
  }

  public function isGlobal() { return $this->year < 1; }
  public function isYear() { return $this->year >= 1 && $this->month < 1; }
  public function isMonth() { return $this->month >= 1 && $this->day < 1; }
  public function isDay() { return $this->day >= 1; }

  private function getPeriodLabel() {
    if ($this->isGlobal()) {
      return 'Global';
    }
    if ($this->isYear()) {
      return 'Année '.$this->year;
    }
    if ($this->isMonth()) {
      return I18N::$months[I18N::LOCALE_FR]['long'][$this->month].' '.$this->year;
    }
    if ($this->isDay()) {
      return $this->day.'/'.$this->month.'/'.$this->year;
    }
  }

  public function filter($column) {
    if ($this->year < 1) return ' 1';
    return ' DATE_FORMAT('.$column.', "'.$this->format.'")="'.$this->value.'"';
  }

  public static function getInstance($period=null) {
    if ($period === null) {
      $period = S('req')->getAttribute('period');
    }
    return new DashBoard($period);
  }

}

class DashBoardBlock 
{
  public $dashboard = null;

  private $columns = null;
  private $label = null;
  private $values = null;

  public function __construct() {
  }

  public function setLabel($label) {
    $this->label = $label;
  }

  public function setColumns($columns) {
    $this->columns = array();
    foreach ($columns as $key => $value) {
      $column = array('label' => null,
                      'code' => null,
                      'width' => null);
      if (is_array($value)) {
        $code = $key;
        $label = empty($value['label']) ? $code : $value['label'];
        if ($value['width']) {
          $column['width'] = $value['width'];
        }
      }
      elseif (is_int($key)) {
        $code = $value;
        $label = $value;
      }
      else {
        $code = $key;
        $label = $value;
      }
      $column['label'] = $label;
      $column['code'] = $code;
      $this->columns[] = $column;
    }
  }

  public function setValues($values) {
    $this->values = $values;
  }

  public function asHtml($locale) {
    $html = '<div class="dashboard-block">'."\n";
    if (!empty($this->label)) {
      $html .= '<div class="dashboard-block-label">'.c($this->label).'</div>';
    }
    $html .= $this->renderGrid();
//    $html .= 'coucou'; 
    $html .= '</div>';
    return $html;
  }

  private function renderGrid() { 
    $html = '<table class="grid">'."\n";
    if (!empty($this->columns)) {
      $html .= '<thead><tr>'."\n";
      foreach ($this->columns as $column) { 
        $style = '';
        if ($column['width']) {
          $style = ' style="width:'.$column['width'].'"';
        }
        $html .= '<th'.$style.'>';
        $html .= $column['label'];
        $html .= '</th>'."\n";
      }
      $html .= '</tr></thead>'."\n";
    }
    $html .= '<tbody>'."\n";
    $first = reset($this->values);
    if (is_array($first)) {
      foreach ($this->values as $row) { 
        $html .= '<tr>'."\n";
        foreach ($row as $key => $value) {
          $html .= '<td>';
          $html .= $value;
          $html .= '</td>'."\n";
        }
        $html .= '</tr>'."\n";
      }
    }
    else {
      foreach ($this->values as $key => $value) { 
        $html .= '<tr>'."\n";
        $html .= '<td>'.$key.'</td>';
        $html .= '<td>'.$value.'</td>'."\n";
        $html .= '</tr>'."\n";
      }
    }
    $html .= '</tbody>'."\n";
    $html .= '</table>'; 
    return $html;
  }

}