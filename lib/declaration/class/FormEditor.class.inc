<?php

class FormEditor {

  const REGEX = "(\[.*\])";

  private $itemplate = null;

  private $form = null;
  private $content = "";
  private $imprime = null;
  private $doc = null;

  public function __construct($itemplate) {
    $this->itemplate = $itemplate;

    $this->imprime = new Imprime();
    $this->imprime->setFormulairetype($this->itemplate->getFormulairetype(), $this->itemplate->getMillesime());
    $this->form = $this->imprime->getFormulairetype();
    $this->content = $this->prepareTemplate($this->itemplate->html);
    $this->doc = new DOMDocument();
  }

  public function asHtml($opts = array()) {
    $id = 'form-editor-' . rand(1, 1000);
    $html = '<div class="form-editor">';
    $html .= '<input name="itemplate_id" type="hidden" value="' . $this->itemplate->getId() . '" />';

    $html .= '<textarea id="' . $id . '" style="display:none" name="template" >' . $this->itemplate->html . '</textarea>';
    $html .= '<div contenteditable="true" class="editor-content">' . $this->itemplate->html . '</div>';
    $html .= '<div class="editor-toolbar">';

    $html .= '<div class="editor-functions">';
    $html .= '<h2>Fonctions</h2><div>';
    $html .= '<span class="page-add" title="ajouter une page">&nbsp;</span>';
    $html .= '<hr class="separator"/>';
    $html .= '<span class="table-add" title="ajouter une table">&nbsp;</span>';
    $html .= '<span class="table-delete" title="supprimer la table">&nbsp;</span>';
    $html .= '<hr class="separator"/>';
    $html .= '<span class="add model-new" title="ajouter un modèle">&nbsp;</span>';
    $html .= '<hr class="separator"/>';
    $html .= '<span class="cell-merge" title="fusionner les cellules">&nbsp;</span>';
    $html .= '<span class="cell-split" title="scinder la cellule">&nbsp;</span>';
    $html .= '<hr class="separator"/>';
    $html .= '<span class="row-duplicate" title="dupliquer la ligne">&nbsp;</span>';
    $html .= '<span class="row-delete" title="supprimer la ligne">&nbsp;</span>';
    $html .= '<hr class="separator"/>';
    $html .= '<span class="row-extensible" title="Ligne Extensible ?">&nbsp;</span>';
    $html .= '</div></div>';

    $html .= '<div class="editor-models">';
    $html .= '<h2>Modèles</h2><div class="models-container">';
    foreach (Imodel::collectAsHash() as $model_id => $format) {
      $html .= '<div data-item="' . $model_id . '" draggable="true" class="item-model" title="ID:' . $model_id . '">' . $format . '</div>';
    }
    $html .= '</div></div>';

    $html .= '<div class="table-actions">';
    ///$html .= '<img src="/app/declaration/pix/table_delete.png" width="20px" />';
    $html .= '</div>';

    $html .= '</div>';
    $html .= '<img src="/' . PIX_PATH . '/empty.gif" onload="new declaration.Editor(\'' . $id . '\');" />';
    return $html;
  }

  public function renderTemplate() {
    $template = mb_convert_encoding($this->content, 'HTML-ENTITIES', "UTF-8");
    if ($this->doc->loadHTML($template) === false) {
      S('log')->error($this->content, __METHOD__);
    }
    $xpath = new DOMXpath($this->doc);
    $query = '//div[@class="editor-page"]';
    $pages = $xpath->query($query);
    $loop = array();
    if ($pages->length > 0) {
      foreach ($pages as $page) {
        $page->setAttribute('class', 'formulaire-page');
        $page->removeAttribute('contenteditable');
        $query = './/table';
        $tables = $xpath->query($query, $page);
        if ($tables->length > 0) {
          foreach ($tables as $table) {
            $this->renderTable($table);
          }
        }
      }
    }

    $html = $this->repairTemplate($this->doc->saveHTML());
    extract(array('imprime' => $this->imprime), EXTR_SKIP);
    ob_start();
    eval('?>' . html_entity_decode($html) . '<?php ');
    $content = ob_get_clean();
    $psp = str_replace(array('|i|', '|/i|', '|u|', '|/u|', '|b|', '|/b|', '|br|', '#line_number#'),
                       array('<i>', '</i>', '<u>', '</u>', '<b>', '</b>', '<span class="br"></span>', '<span class="line_number"><?=$index + 1?></span>'),
                             html_entity_decode($html));

    return array('html' => $content, 'code' => $html, 'psp' => $psp);
  }

  public function renderTable(&$table) {
    $table->removeAttribute('_moz_resizing');
    $table->removeAttribute('height');
    $table->removeAttribute('width');
    $query = './/tr';
    $xpath = new DOMXpath($this->doc);
    $lines = $xpath->query($query, $table);
    $renders = array();
    $j = 0;
    if ($lines->length > 0) {
      while ($j < $lines->length) {
        $model_fields = array();
        $line = $lines->item($j);
        $query = './/td';
        $cells = $xpath->query($query, $line);
        $row_options = $line->getAttribute('row_options');
        $extensible = strpos($row_options, Imodel::OPT_ROW_EXTENSIBLE) !== false;
        $extensible_group = 0;
        $merge_in_one_td = strpos($row_options, Imodel::OPT_MERGE_IN_ONE_TD) !== false;
        //$extensible_code  = strpos($row_options, Imodel::OPT_ROW_EXTENSIBLE_CODE) !== false;
        $extensible_code = (int) $line->getAttribute('data-extensible_code');
        $extensible_max = (int) $line->getAttribute('data-extensible_max');

        $tds = array();
        $i = 0;
        $cols_count = 0;
        if ($cells->length > 0) {
          while ($i < $cells->length) {
            $cell = $cells->item($i);
            $cols_count += $cell->hasAttribute('colspan') ? $cell->getAttribute('colspan') : 1;
            if ($cell->nodeValue && preg_match_all('/' . self::REGEX . '/U', $cell->nodeValue, $matches)) {
              $matches = $matches[0];
              foreach ($matches as $matche) {
                list($type, $args) = explode(':', trim($matche, ' \[\]'), 2);
                $args = explode(";", $args);
                switch (strtolower($type)) {
                  case 'model':
                    if (!Imodel::exists($args[0])) break;
                    $model = Imodel::getInstance($args[0]);
                    unset($args[0]);
                    $model_fields = array_merge($model_fields, $model->getFields($args));
//                    S('log')->debug($model_fields, __METHOD__);
                    $tds[] = $this->renderHTMLModel($model, $args, count($matches) == 1 ? $cell : null, array('extensible' => $extensible));
                    break;
                }
              }
            }
            else {
              $cell_args = $cell->hasAttribute('colspan') ? '&' . Imodel::OPT_COLSPAN . '=' . $cell->getAttribute('colspan') : '';
              $cell_args .= $cell->hasAttribute('rowspan') ? '&' . Imodel::OPT_ROWSPAN . '=' . $cell->getAttribute('rowspan') : '';
              $tds[] = Imodel::renderByCode(Imodel::TYPE_EMPTY, array($cell_args), $this->imprime);
            }
            $i++;
          }
        }

        if ($merge_in_one_td) {
          $tds = $this->mergeCells($tds);
        }

        if ($extensible) {
          if (!empty($extensible_code)) {
            $extensible_group = $extensible_code;
          }
          else{
            $extensible_group = $last_extensible_index > 0 && $last_extensible_index + 1 != $j ? $extensible_group + 1 : $extensible_group;
          }

          if ($renders['extensible'] && $renders['extensible'][$extensible_group]) {
            $count = max($renders['extensible'][$extensible_group]['count'], count($model_fields));
            $fields = array_merge($model_fields, $renders['extensible'][$extensible_group]['fields']);
          }
          else {
            $count = count($model_fields);
            $fields = $model_fields;
          }

          $args = $fields && count($fields) > 0 ? '\'' . implode("','", $fields) . '\'' : '';
          $attributes = '';
          if (!empty($extensible_code)) {
            $attributes .= ' data-extensible_code="' . $extensible_code . '" ';
          }
          $head = '<tr style="display:none;"><td data-manager="ExtensibleTableManager" data-fields="' . implode(',', (array) $fields) . '" ' . $attributes . ' data-extensible_max="'.$extensible_max.'" ></td></tr>'
              . '<![CDATA[ <?php  $count = max(1, $imprime->getFieldsValuesCount(array(' . $args . '))); for ($index = 0; $index < $count; $index++) : ?>]]>';
          $foot = '<![CDATA[<?php endfor; ?>]]>'
              . '<tr class="btn-add-container"><td colspan="' . ($cols_count) . '"><a class="btn-add" data-fields="' . implode(',', (array) $fields) . '" href="javascript:void(0)">Ajouter une ligne</a></td></tr>';

          $replace = '<tr class="elt extensible-row" data-extensible-fields="((fields))" data-extensible_max="'.$extensible_max.'">'
              . implode('', $tds)
              . '</tr>';

          $renders['extensible'][$extensible_group]['lines'][] = array('line' => $line, 'html' => $replace);
          $renders['extensible'][$extensible_group]['head'] = $head;
          $renders['extensible'][$extensible_group]['foot'] = $foot;
          $renders['extensible'][$extensible_group]['fields'] = $fields;
          $renders['extensible'][$extensible_group]['count'] = $count;
          $last_extensible_index = $j;
        }
        else {
          $replace = '<tr class="elt">' . implode('', $tds) . '</tr>';
          $renders['standard']['lines'][] = array('line' => $line, 'html' => $replace);
        }
        $j++;
      }
      $this->replaceLines($table, $renders);
    }
  }

  public function mergeCells($trs, $span = 2) {
    //return $trs;
    $new_tr = array();
    foreach ($trs as $tr) {
      $new_td = array();
      $i = 0;
      preg_match_all('/<td[^>]*\s>\s(.*)\s<\/td>/Uu', preg_replace('/\s{2,}/', ' ', $tr), $new_tds, PREG_SET_ORDER);
      foreach ($new_tds as $td) {
        $new_td[] = $td[1];
        $i++;
        if ($i % $span === 0 && $i) {
          $new_tr[] = '<div class="merged_td">' . implode('', $new_td) . '</div>';
          $new_td = array();
        }
      }
      if ($i % $span === 0 && $i && count($new_td)) {
        $new_tr[] = '<div class="merged_td">' . implode('', $new_td) . '</div>';
      }
    }
    return array('<td class="merged_tds">' . implode('', $new_tr) . '</td>');
    /*
        $tds = array('<td class="merged-tds">'
                  . implode('', str_replace(array('<td', '</td>'),
                                            array('<div', '</div>'),
                                            $tds))
                  . '</td>');
        return $tds;
    */
  }

  public function replaceLines(&$table, $renders) {

    $tbody = $table->firstChild;
    if ($renders['standard']) {
      foreach ($renders['standard']['lines'] as $render) {
        $line = $this->doc->createDocumentFragment();
        $line->appendXML($render['html']);
        $tbody->replaceChild($line, $render['line']);
      }
    }
    if ($renders['extensible']) {
      foreach ($renders['extensible'] as $group) {
        foreach ($group['lines'] as $key => $render) {
          if ($key == 0) {
            $remove_btn = '<td class="btn-remove-container" rowspan="' . count($group['lines']) . '"><a href="javascript:void(0)" class="btn-remove" title="Supprimer la ligne"></a></td>';
            $html = str_replace('</tr>', $remove_btn . '</tr>', $render['html']);
            $html = $group['head'] . $html;
          }
          else {
            $html = $render['html'];
          }
          $html = str_replace('((fields))', implode(',', (array) $group['fields']), $html);
          $html = $key + 1 == count($group['lines']) ? $html . $group['foot'] : $html;
          $line = $this->doc->createDocumentFragment();
          $line->appendXML($html);
          $tbody->replaceChild($line, $render['line']);
        }
      }
    }
  }

  public function prepareTemplate($html) {
    return '<div>' . str_replace(array('<br type="_moz">', ' selected'), array('', ''), $html) . '</div>';
  }

  public function repairTemplate($html) {
    $config = array('indent' => true,
                    'output-xhtml' => true,
                    'wrap' => 200);
    $tidy = new tidy;
    $tidy->parseString($html, $config, 'utf8');
    $tidy->cleanRepair();
    return str_replace(array("<body>\n", "</body>"), array('', ''), tidy_get_body($tidy));
  }

  public function renderHTMLModel($model, $args, $cell, $opts = null) {
    if (count(explode(";", $model->code)) == 1 && $cell && !$opts['extensible']
        && ($cell->getAttribute('rowspan') || $cell->getAttribute('colspan'))) {
      $args[1] .= $cell->hasAttribute('colspan') && $cell->getAttribute('colspan') > 1 ? '&' . Imodel::OPT_COLSPAN . '=' . $cell->getAttribute('colspan') : '';
      $args[1] .= $cell->hasAttribute('rowspan') && $cell->getAttribute('rowspan') > 1 ? '&' . Imodel::OPT_ROWSPAN . '=' . $cell->getAttribute('rowspan') : '';
    }
    return $model->render($args, $this->imprime, $opts);
  }

  public function getUsedFields() {
    $fields = array();
    $content = $this->content;
    if (preg_match_all('/' . self::REGEX . '/U', $content, $matches)) {
      $matches = $matches[0];
      rsort($matches);
      foreach ($matches as $matche) {
        list($type, $args) = explode(':', trim($matche, ' \[\]'));
        $args = explode(";", $args);
        $fields = array_merge($fields, $args);
      }
    }
    return $fields;
  }

  public function getFields() {
    return $this->itemplate->getIfields();
  }

  public static function getInstance($itemplate) {
    return new FormEditor($itemplate);
  }



}
