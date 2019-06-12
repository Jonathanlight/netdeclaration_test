<?php

function cmp($a, $b)
{
  return strcasecmp($a['label'], $b['label']);
}

try {
  
  $ctx->app_title = P('app.name');

  $ctx->admin = $admin;
  
  $ctx->files_flag = true;
  
  $ctx->iframe_main_height = UiManager::HEIGHT.'px';
  $ctx->iframe_main_width  = UiManager::WIDTH.'px';
  
  $extensions = array();

  foreach (Extension::all() as $name => $hash) {
    if (!is_array($hash['back']) || count($hash['back']) === 0) continue ;
    //    if (!$admin->hasRight($hash['id'])) continue ;
    $extensions[$name]['label'] = $hash['label'] ?: $hash['name'];
    $extensions[$name]['menu'] = array();
    foreach ($hash['back'] as $label => $link) {
      if ($link == '---') {
        $extensions[$name]['menu'][] = '---';
        continue;
      }
      if (strpos($link, '/') === false) {
        $link = '/back/'.$name.'/'.$link;
      }
      if (!$admin->hasRight($link)) continue ;
      $extensions[$name]['menu'][$label] = $link;
    }
  }

  $ctx->extensions = array();
  
  foreach ($extensions as $name => $hash) {
    if (empty($hash['menu'])) continue ;
    $ctx->extensions[$name] = $hash;
  }

  uasort($ctx->extensions, 'cmp');
  
  $res->setSeo($ctx->app_title);
  $res->useTemplate();
  
}
catch (Exception $e) {}