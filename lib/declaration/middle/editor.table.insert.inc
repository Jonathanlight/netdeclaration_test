<?php

try {
  
  $cols = $req->cols ? $req->cols : 1;
  $rows = $req->rows ? $req->rows : 1;
  $extensible_lines = $req->num_rows ? explode(',', $req->num_rows) : array($rows); 
  
  $html = '<tbody>';  

  for ($i=0; $i< $rows; $i++) {
    $html .= '<tr '.(in_array($i+1, $extensible_lines) && $req->extensible ? 'row_options="extensible"' : '').'>';
    if (in_array($i+1, $extensible_lines) && $req->extensible) {
      $html .= '<td '.($cols > 1 ? 'colspan="'.($cols+1).'"' : '').' ><br type="_moz"></td>';
    }
    else {
      for ($j=0; $j < $cols; $j++) {
        $html .= '<td><br type="_moz"></td>';
      }
      if ($req->extensible && $i == 0) {
        $html .= '<td class="empty" '.($extensible_lines[0] > 1 ? 'rowspan="'.($extensible_lines[0]-1).'"' : '').' ></td>';
      }
      elseif ($req->extensible && ($i+1) > $extensible_lines[0]) {
        $html .= '<td class="empty"></td>';
      }
    }
    $html .= '</tr>';
  }   
  $html .= '</tbody>';
  
  $ctx->body = $html;
  
  $ctx->extensible = $req->extensible ? 1 : 0;

}
catch (Exception $e) {
  $err->add($e);
}