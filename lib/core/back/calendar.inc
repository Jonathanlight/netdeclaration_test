<?php

parse_str($req->params,$params_arr);

$res->useTemplates('//layer');
$res->setSeo('Calendrier');

$ctx->content_style = "style='height:190px;overflow:auto;'";

if ($req->hasAttribute('date_sel')) $date_sel = $req->date_sel;
elseif (!empty($params_arr['value'])) {
  list($inputDay,$inputMonth,$inputYear) = explode('/',$params_arr['value']);
  $date_sel = $inputMonth.'/'.$inputYear;
}
else $date_sel = date("m/Y");

$now_arr = getdate(time());

list($month,$year) = explode('/',$date_sel);

$sel_date_arr = getdate(mktime(0,0,0, $month,1,$year));
if ($sel_date_arr['wday']==0) $sel_date_arr['wday'] = 7;
$dayTotal = date("t", mktime(0,0,0,$month,1,$year));

$path = $req->getUrl();

?>

<table class="calNav">
<tr>
 <th width="30">
  <a href="<?=$path?>?date_sel=<?=$sel_date_arr['mon']-1?>/<?=$sel_date_arr['year']?>&params=<?=$req->params?>"><img src="/<?=PIX_PATH?>/action/prev.png" /></a>
 </th>
 <th>
  <select id="myMonth" onChange="window.location.href='<?=$path?>?date_sel='+$F('myMonth')+'/'+$F('myYear')+'&params=<?=$req->params?>'">
<?php 
foreach (I18N::$months[I18N::LOCALE_FR]['short'] as $k => $v) {
  print("<option value='$k' ".(($k==$sel_date_arr['mon'])?'SELECTED':'').">$v</option>\n"); 
}
?>
  </select>
  <select id="myYear" onChange="window.location.href='<?=$path?>?date_sel='+$F('myMonth')+'/'+$F('myYear')+'&params=<?=$req->params?>'">
<?php 
for ($i = $sel_date_arr['year']-5; $i <= $sel_date_arr['year']+5; $i++) {
  print("<option value='$i' ".(($i==$sel_date_arr['year'])?'SELECTED':'').">$i</option>\n"); 
}
?>
  </select>
 </th>
 <th width="30">
  <a href="<?=$path?>?date_sel=<?=$sel_date_arr['mon']+1?>/<?=$sel_date_arr['year']?>&params=<?=$req->params?>"><img src="/<?=PIX_PATH?>/action/next.png" /></a>
 </th>
</tr>
</table>

<table class="calDay">

 <colgroup>
  <col/><col/><col/><col/><col/>
  <col style="background:#f9f9f9;" />
  <col style="background:#f9f9f9;" />
 </colgroup>

 <tr><?php foreach (I18N::$days[I18N::LOCALE_FR]['short'] as $k => $v) print('<th>'.$v.'</th>'); ?></tr>

<?php
for ($i = 0; $i < 6; $i++) {
  print("<tr>\n");
  for ($j = 1; $j <= 7; $j++) {
    $style = $out = '';
    $dayNum = $j + $i*7 - $sel_date_arr['wday'] + 1;
    if ($dayNum>0 && $dayNum<=$dayTotal) {
      if ($dayNum==$now_arr['mday'] && 
	  $sel_date_arr['mon']==$now_arr['mon'] && 
	  $sel_date_arr['year']==$now_arr['year']) 
	$style .= "font-weight:bolder;background:#f2f2f2;"; 
      if ($dayNum==$inputDay && $sel_date_arr['mon']==$inputMonth && 
	  $sel_date_arr['year']==$inputYear) 
	$style .= "color:red;";
      $out = str_pad($dayNum, 2, "00", STR_PAD_LEFT);
    }
    if (!empty($style)) $style = ' style="'.$style.'"';
    $link = "javascript:placeElem('".$params_arr['input_id']."','".$dayNum."/".$sel_date_arr['mon']."/".$sel_date_arr['year']."')";
    print(' <td><a href="'.$link.'"'.$style.'>'.$out.'</a></td>');
  }
  print("</tr>\n");
  if ($dayNum>=$dayTotal && $i!=6) break;
}
?>
</table>

<div style="width:auto;text-align:center;">
 <a href="javascript:placeElem('<?=$params_arr['input_id']?>','<?=date('d/m/Y')?>')">aujourd hui</a> &nbsp; 
 <a href="javascript:placeElem('<?=$params_arr['input_id']?>','')">vider</a>
</div>

