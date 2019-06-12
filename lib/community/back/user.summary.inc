<?php

try {

  $user = User::getInstance($req->id, array('metas' => true));

  $rows = array('name' => $user->name.' ('.$user->id.')',
                'email' => $user->email,
                'statut' => User::$statuses[$user->status],
                'inscription' => Visit::url($user->visit, $user->created_at));

  if ($user->image) {
    $rows['name'] = '<img src="'.$user->image.'" style="float:right;" />'.$rows['name'];
  }

  $conversions = array();
  $rows['conversions'] = 0;
  if (Extension::exists('performance')) {
    $opts = array('filters' => array('user_id' => $user->getId()));
    $conversions = Conversion::collect($opts);
    $rows['conversions'] = $conversions->numRows();
  }
  
  $ctx->conversions = $conversions;
  $ctx->rows = $rows;
  $ctx->user = $user;

  $res->useTemplate();

}
catch (Excpetion $e) { $err->add($e); }