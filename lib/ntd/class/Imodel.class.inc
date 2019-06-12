<?php

class Imodel extends ActiveRecord {
  
  const TYPE_LABEL = 'LB';
  const TYPE_FIELD = 'FD';
  const TYPE_IMPOT = 'IMP';
  const TYPE_EMPTY = '#';

  const OPT_COLSPAN = 'CS';
  const OPT_ROWSPAN = 'RS';
  const OPT_CLASS   = 'CSS';

  const OPT_ROW_EXTENSIBLE = 'extensible';
  const OPT_ROW_EXTENSIBLE_CODE = 'extensible_code';
  const OPT_MERGE_IN_ONE_TD = 'merge_one_td';

  const MAX_COLS     = 30;
  const DEFAULT_COLS = 6;
  
  const FLAG_TOP = 1;
  const FLAG_EXTENSIBLE = 2;

  public static $types = array(self::TYPE_LABEL => 'Label',
                               self::TYPE_FIELD => 'Champ',
                               self::TYPE_IMPOT => 'N° Impôt',
                               self::TYPE_EMPTY => 'Cellule vide');

  public static $types_data = array(self::TYPE_LABEL => array('caption' => 'Label',  'class' => 'libelle'),
                                    self::TYPE_FIELD => array('caption' => '',       'class' => ''),
                                    self::TYPE_IMPOT => array('caption' => 'IM',     'class' => 'impot_field'),
                                    self::TYPE_EMPTY => array('caption' => '&nbsp;', 'class' => ''));                              
                                     
  public static $data_options = array(self::OPT_COLSPAN => 'col-span',
                                 self::OPT_ROWSPAN => 'row-span',
                                 self::OPT_CLASS   => 'class CSS');

  public static $row_options = array(self::OPT_ROW_EXTENSIBLE => 'Ligne répétable',
                                     self::OPT_ROW_EXTENSIBLE_CODE => 'Ligne répétable => Code',
                                     self::OPT_MERGE_IN_ONE_TD => 'Fusionner en 1 cellule (solution pour les champs NAD)');
                                 
  public static $classes = array('title' => 'Titre',
                                 'empty' => 'Vide avec fond',
                                 'ta-left' => 'Texte aligné à gauche',
                                 'ta-center' => 'Texte centré',
                                 'ta-right' => 'Texte aligné à droite',
                                 'bold' => 'Gras',
                                 'little-width' => 'Taille Petit',
                                 'medium-width' => 'Taille Moyen',
                                 'large-width' => 'Taille Grand',
                                 'small-size' => 'Petite police');
                                 
  
  public function getHtmlDescription($data=array()) {
    $cells = explode(";", $this->code);
    $description = array();
    foreach ($cells as $j => $cell) {
      $_description = "";
      $value = $data && $data[$j] ? $data[$j] : null; 
      if ($value) list($value) = explode("&", $value);
      if (strpos($cell, "&") > 0) {    
        $cell_params = self::parseStr($cell);        
        $css = $cell_params[self::OPT_CLASS] ? $cell_params[self::OPT_CLASS] : '';
        $_description .= self::renderEditorView($cell_params[0], $value, array('css' => $css));
      }
      else {
        $_description .= self::renderEditorView($cell, $value);
      }
      $description[] = $_description;
    }
    $actions = '';
    if ($data || !$this->isUsed()) {
      $actions .= '<span class="actions">';
      if (!$data) {
        $actions .= '<img class="edit-btn" src="/app/declaration/pix/edit.png" />';
      }
      $actions .= '<img class="delete-btn" src="/app/declaration/pix/delete.png" />';      
      $actions .= '</span>';
    } 
    $description[] = $actions;
    return implode('', $description);
  }
  
  public function render($args, $imprime, $opts = null) {
    return self::renderByCode($this->code, $args, $imprime, $opts);
  }
  
  public function getFields($data) {
    $fields = array();
    $values = self::parseCellsValues($this->code, $data);
    foreach ($values as $value) {
      if ($value['type'] == self::TYPE_FIELD) {
        $fields[] = $value['value'];
      }
    }
    return $fields;
  }
  
  public function isUsed() {
    return true; //Itemplate::collect(array('filters' => array('|%%|html' => '[Model:'.$this->id.';')))->count() > 0;
  }
  
  public static function renderEditorView($type, $value=null, $opts=array()) {
    $content = $type != self::TYPE_FIELD ? ($value ? $value : self::$types_data[$type]['caption']) : '<input value="'.$value.'" />';
    $html = '<span class="'.$type.' '.$opts['css'].'">'.$content.'</span>';
    return $html;
  }
                                 
  public static function renderById($id=null, $args, $imprime) {
    if (!$id || !self::exists($id)) return "";
    $model = self::getInstance($id);
    return self::renderByCode($model->code, $args, $imprime);
  }
  
  public static function renderByCode($code, $args, $imprime, $opts = null) {
    $_cells = $_args = $_params = array();
    foreach ($args as $arg) {
      //$params  = self::parseStr($arg);
      //$_args[] = $params[0];
      //unset($params[0]);            
      list($value, $params) = explode('&', $arg, 2);
      $_args[] = $value;
      parse_str((string) $params, $params);

      $_params[] = $params;
    }
    $cells = explode(";", $code);
    foreach ($cells as $i => $cell) {
      $cell_params = self::parseStr($cell);
      $type = $cell_params[0];
      unset($cell_params[0]);
      foreach ($cell_params as $k => $v) {
        if (!$_params[$i][$k]) $_params[$i][$k] = $v;
      }
      $cell = array('type'   => $type,
                    'params' => $_params[$i] ? $_params[$i] : array());
      $_cells[] = $cell;
    }    
    return Template::render('declaration:_model', array('cells' => $_cells,
                                                        'args' => $_args,
                                                        'imprime' => $imprime,
                                                        'opts' => $opts));
  }
  
  public static function parseStr($str) {
    $params = array();
    $hash   = explode("&", $str);
    foreach ($hash as $i => $item) {
      if (strpos($item, '=') > 0) {
        list($k, $v) = explode("=", $item);
        $params[$k] = $v;
      }
      else {
        $params[$i] = $item;
      }      
    }
    return $params;
  }
  
  public static function parseCellsValues($code, $args) {
    $cells = explode(";", $code);
    $values = $_values =  array();
    foreach ($args as $arg) {
      list($value) = explode('&', $arg);
      $_values[] = $value;
    }
    foreach ($cells as $i => $cell) {
      list($type) = explode('&', $cell);
      $values[] = array('type'  => $type,
                        'value' => $_values[$i]);
    }
    return $values;
  }
  
  public static function collectAsHash() {
    $hash = array();
    $models = self::collect(array('order' => array('cols_count' => 'asc'),
                                  'cols'  => array("LENGTH(code)-LENGTH(REPLACE(code, ';', ''))" => 'cols_count')));
    foreach ($models as $model) {
      $hash[$model->id] = $model->getHtmlDescription();
    }
    return $hash;
  }
  
}