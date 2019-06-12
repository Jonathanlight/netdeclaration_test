<?php

try {  

  S('app')->hook('onUserValidate');

  if (!$req->hasValidCaptcha()) {
    throw new Exception(l('error.captcha'));
  }

  $record = (array) $req->user;

  $password = $record['password'];
  unset($record['password']);

  $password_confirm = $record['password_confirm'];
  unset($record['password_confirm']);

  if ($password != $password_confirm) {
    throw new Exception(l('error.password.different'));
  }

  $gender = $record['gender'];
  unset($record['gender']);

  $birth_date = $record['birth_date'];
  unset($record['birth_date']);

  if (isset($birth_date) && Date::isNull($birth_date)) {
    throw new Exception(l('error.fields.required'));
  }

  if (!User::isValidUser($record)) {
    throw new Exception(l('error.fields.required'));
  }

  if (!Email::isValid($record['email'], true)) {
    throw new Exception(l('error.email.invalid'));
  }

  if (empty($record['name'])) {
    list ($record['name'], ) = explode('@', $record['email']);
  }

  $ret = $dbo->fetchValue('SELECT COUNT(*)'
                          .' FROM '.T('user')
                          .' WHERE email=:email:',
                          array(':email:' => $record['email']));
  if ($ret >= 1) {
    throw new Exception(l('error.email.used'));
  }

  if (strlen($password) < 8 || strlen($password) > 20) {
    throw new Exception(l('error.password.size'));
  }

  //$record['status'] = User::STATUS_PENDING;
  $record['status'] = User::STATUS_CONFIRMED;
  $record['locale'] = $res->getLocale();


  $user = User::getInstance();
  $user->commit($record);
  $user->setPassword($password);
  $user->setVisit($req);

  $informations = array('recipient_id' => Email::asId($record['email']),
                        'auth_at' => Date::now(),
                        'birth_date' => $birth_date);
  if ($req->origin_id >= 1 && Item::exists('origin', $req->origin_id)) {
    $informations['origin_id'] = $req->origin_id;
  }
  $user->setInformations($informations);

  if ($gender > 0) {
    $user->setFlag(User::FLAG_WOMAN);
  }

  if (Model::exists('movement')) {
    Movement::trigger($user, 'user.signup');
  }

  $cookie = $req->getCookie();

  if (Extension::exists('push')) {
    Base::addUser($user);
  }

  if (Extension::exists('share')) {
    try {
      $tkr_cookie = $req->getCookie(Tracker::COOKIE_NAME);
      $sponsorship_id = (int) $tkr_cookie->getAttribute('sponsorship_id');//$cookie->sponsorship_id;
      if ($sponsorship_id >= 1) {
        $sponsorship = Sponsorship::getInstance($sponsorship_id);
        if ($sponsorship->godson_id < 1) {
          $sponsorship->setAttribute('godson_id', $user->getId());
          $user->setFlag(User::FLAG_GODSON);
        }
        $tkr_cookie->removeAttribute('sponsorship_id'); //$cookie->removeAttribute('sponsorship_id');
      }
    }
    catch (Exception $e) {}
    if (is_array($req->godsons)) {
      $godsons = array_unique($req->godsons);
      foreach ($godsons as $email) {
        Sponsorship::deliver($user, $email);
      }
    }
  }


  try {
    if (is_array($req->notices)) {
      foreach ($req->notices as $notice_id => $null) {
        $notice = Notice::getInstance($notice_id);
        if (!$notice->hasFlag(Notice::FLAG_SIGNUP)) continue ;
        $user->setFlag($notice, 'notices');
      }
    }
  }
  catch (Exception $e) {}


  try {
    S('app')->hook('onUserCreate', array('user' => $user));
  }
  catch (Exception $e) {
    $log->error($e);
  }

  if ($user->status <= User::STATUS_PENDING && !$user->hasFlag(User::FLAG_WELCOMED)) {
    Letter::send('signup.confirm', $user,
                 array('email' => $user->email,
                       'name' => $user->name,
                       'password' => $password,
                       'link' => $user->confirmUrl()));
    //$user->setFlag(User::FLAG_WELCOMED);
  }
  $user->setFlag(User::FLAG_WELCOMED);

  $user->convert();

  AuthManager::onUserAuth($user);

  $attributes = array('user_id' => $user->getId());
  if (P('auth.sso') === true) {
    $attributes['user_secret'] = substr($user->password, 2, 8);
  }

  $cookie->setAttributes($attributes);

  $ctx->user_id = $user->getId();

}
catch (Exception $e) {
  $req->track('signup', Tracker::CATEGORY_ERROR);
  $ctx->_auth_errors = $e->getMessage();
  $err->add($e);
}

if (!$req->isXhr()) {
  $args = null;
  if ($ctx->hasAttribute('form_errors')) {
    $args = array('errors' => $ctx->form_errors,
                  'fields' => $ctx->form_fields);
    $res->sendRedirect($req->onerror, $args);
  }
  else {
    $args = array('fields' => $ctx->form_fields);
    $res->sendRedirect($req->onsuccess, $args);
  }
}
