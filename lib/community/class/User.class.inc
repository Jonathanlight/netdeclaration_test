<?php

class User extends ActiveRecord
{
  const FLAG_WOMAN = 1;
  const FLAG_IMAGE = 2;
  const FLAG_CLIENT = 4;
  const FLAG_VIP = 8;
  const FLAG_GODSON = 16;
  const FLAG_SUSPICIOUS = 32;
  const FLAG_ABUSE = 64;
  const FLAG_INTENT = 128;
  const FLAG_WELCOMED = 256;
  const FLAG_WEB = 512;
  const FLAG_ACCUSTOMED = 1024;
  const FLAG_AFFILIATE = 2048;
  const FLAG_NTD_DOMTOM = 4096;
  const FLAG_ACCESS_MODULE_DEVIS = 8192;

  public static $flags = array(self::FLAG_WOMAN => 'femme',
                               self::FLAG_IMAGE => 'avatar',
                               self::FLAG_CLIENT => 'client',
                               self::FLAG_VIP => 'VIP',
                               self::FLAG_GODSON => 'filleul',
                               self::FLAG_SUSPICIOUS => 'douteux',
                               self::FLAG_ABUSE => 'abus',
                               self::FLAG_INTENT => 'actif',
                               self::FLAG_WELCOMED => 'accueilli',
                               self::FLAG_WEB => 'origine web',
                               self::FLAG_ACCUSTOMED => 'habitué',
                               self::FLAG_AFFILIATE => 'affilié',
                               self::FLAG_NTD_DOMTOM => 'Utilisateur DOM-TOM',
                               self::FLAG_ACCESS_MODULE_DEVIS => 'Accès au module Devis');

  const STATUS_CONFIRMED = 2;
  const STATUS_PENDING = 1;
  const STATUS_CLOSED = 0;
  const STATUS_INVALID = -1;
  const STATUS_ABUSE = -2;
  const STATUS_SPAM = -3;

  public static $statuses = array(self::STATUS_CONFIRMED => 'ouvert',
                                  //self::STATUS_PENDING => 'ouvert (à confirmer)',
                                  self::STATUS_CLOSED => 'fermé',
                                  //self::STATUS_INVALID => 'fermé (invalide)',
                                  //self::STATUS_ABUSE => 'fermé (abus)',
                                  //self::STATUS_SPAM => 'fermé (spam)'
  );

  const PRIVACY_PUBLIC = 0;
  const PRIVACY_NETWORK = 1;
  const PRIVACY_PRIVATE = 2;

  public static $privacies = array(self::PRIVACY_PUBLIC => 'tout le monde',
                                   self::PRIVACY_NETWORK => 'uniquement le réseau',
                                   self::PRIVACY_PRIVATE => 'personne');

  const TABLE_INFORMATION = 'cty_user_information';
  const TABLE_PRIVILEGE = 'cty_privilege_user';

  const QUOTA_HARD = 50;
  const QUOTA_SOFT = 200;

  private $profiles = null;
  private $sponsor_id = null;

  public function asPickerRow() {
    return $this->name.' ('.$this->id.')<br/><small>'.$this->email.'</small>';
  }

  public function asView($view) {
    if ($view == 'preview') {
      return $this->email.' ('.$this->getId().')<br/>'.$this->name;
    }
    return parent::asView($view);
  }

  public function commit($hash) {
    $informations = array();
    if (!empty($hash['image'])) {
      $image = $hash['image'];
      unset($hash['image']);
    }
    $info_fields = array('quota_soft', 'quota_hard', 'birth_date', 'timezone_id');
    foreach ($info_fields as $key) {
      if (!isset($hash[$key])) continue ;
      if ($key === 'birth_date') {
        $hash[$key] = Date::toDb($hash[$key]);
      }
      $informations[$key] = $hash[$key];
      unset($hash[$key]);
    }
    parent::commit($hash);
    if (File::exists($image)) {
      try {
        $image = Img::getInstance($image);
        $image = $image->copyTo('_a.jpg', true);
        $image->moveIn($this->getPath());
        $image->setSize(36, 36);
        $this->setFlag(self::FLAG_IMAGE);
      }
      catch (Exception $e) { $this->log->error($e, __METHOD__); }
    }
    if (!empty($informations)) {
      $this->setInformations($informations);
    }
  }

  protected function onBeforeCommit(&$hash) {
    if (isset($hash['email'])) {
      $id = $this->isLoaded() ? $this->getId() : 0;
      $ret = $this->dbo->fetchValue('SELECT COUNT(*)'
                                    .' FROM '.T('user')
                                    .' WHERE email=:email:'
                                    .  ' AND id<>'.$id,
                                    array(':email:' => $hash['email']));
      if ($ret >= 1) {
        $this->log->trace('email already used ['.$hash['email'].']',
                          __METHOD__);
        throw new Exception(l('error.login.used'));
      }
    }
    if (!$this->isLoaded()) {
      if (empty($hash['password'])) {
        $hash['password'] = String::password();
      }
      if (!isset($hash['status'])) {
        $hash['status'] = self::STATUS_CONFIRMED;
      }
    }
    if (isset($hash['md5'])) {
      $hash['password'] = $hash['md5'];
      unset($hash['md5']);
    }
    elseif (isset($hash['password'])) {
      if (empty($hash['password'])) {
        unset($hash['password']);
      }
      elseif (strlen($hash['password']) < 32) {
        $hash['password'] = hash('md5', $hash['password']);
      }
    }
  }

  public function asFinderHash($hash) {
    if ($this->status <= self::STATUS_CLOSED) $color = 'red';
    elseif ($this->status == self::STATUS_PENDING) $color = 'yellow';
    else $color = 'green';
    $hash['_color'] = $color;
    return $hash;
  }

  protected function onAfterCreate() {
    $this->getPath();
    foreach (Notice::collect('notice') as $notice) {
      if (!$notice->hasFlag(Notice::FLAG_DEFAULT)) continue ;
      $this->setFlag($notice, 'notices');
    }
  }

  public function onAfterStore() {
    $hash = S('req')->getAttributes();
    if (is_array($hash['profiles'])) {
      foreach ($hash['profiles'] as $name => $attributes) {
        if (!Model::exists($name)) continue ;
        $this->setProfile($attributes, $name);
      }
    }
  }

  public function onRelationCreate($item) {
    if (Model::isProfile($item)) {
      $this->setProfiles();
    }
  }

  public function onRelationUpdate($item) {
    if (Model::isProfile($item)) {
      $this->setProfiles();
    }
  }

  public function onRelationDestroy($item) {
    if (Model::isProfile($item)) {
      $this->setProfiles();
    }
  }

  private function setProfiles() {
    $bits = 0;
    foreach (P('profiles') as $bit => $model) {
      if (!Model::exists($model)) continue ;
      $status = !in_array('status', M($model, 'fields')) ?: ' AND status>0';
      $id = $this->dbo->fetchValue('SELECT id'
                                   .' FROM '.T($model)
                                   .' WHERE user_id='.$this->getId()
                                   .$status);
      if ($id < 1) continue ;
      $bits += $bit;
    }
    $this->commit(array('profiles' => $bits));
  }

  protected function onAfterCommit($hash) {
    if (isset($hash['privileges'])) {
      $hash['privileges'] = empty($hash['privileges'])
                          ? array()
                          : $hash['privileges'];
      $old = (int) $this->prior('privileges');
      $new = $hash['privileges'];
      if ($old != array_sum($new)) {
        $bits = array();
        for ($i = 0; $i <= 31; $i++) {
          $n = pow(2, $i);
          if ($n > $old) break ;
          if ($old & $n) $bits[] = $n;
        }
        $old = $bits;
        $diff = array_diff($old, $new);
        foreach ($diff as $priv) {
          S('app')->hook('onPrivilegeRemove',
                             array('user' => $this,
                                   'privilege' => strlen(decbin($priv))));
          //          S('log')->debug('remove ('.$priv.')');
        }
        $diff = array_diff($new, $old);
        foreach ($diff as $priv) {
          S('app')->hook('onPrivilegeAdd',
                             array('user' => $this,
                                   'privilege' => strlen(decbin($priv))));
          //          S('log')->debug('add ('.$priv.')');
        }
      }
    }
    if (!empty($hash['email']) && !$this->isNew()) {
      $email = $this->prior('email');
      if (!empty($email) && $email != $this->email) {
        $from_id = Email::asId($email);
        $to_id = Email::asId($this->email);
        S('app')->hook('onEmailChange',
                           array('user' => $this,
                                 'from' => $from_id,
                                 'to' => $to_id));
        if (Extension::exists('push')) {
          Base::onEmailChange($from_id, $to_id);
        }
        Subscription::onEmailChange($from_id, $to_id);
      }
    }
  }

  public function getConversionWorth($opts) {
    return 1;
  }

  public function getInformation($key) {
    return $this->dbo->fetchValue('SELECT '.$key
                                  .' FROM '.self::TABLE_INFORMATION
                                  .' WHERE user_id='.$this->getId());
  }

  public function setInformation($key, $value) {
    $this->setInformations(array($key => $value));
  }

  public function setInformations($attributes) {
    if (!is_array($attributes) || empty($attributes)) return ;
    $opts = array('filters' => array('user_id' => $this->getId()),
                  'limit' => 1);
    $attributes['user_id'] = $this->getId();
    $this->dbo->update(self::TABLE_INFORMATION, $attributes, $opts);
    if ($this->dbo->matchedRows() < 1) {
      $this->dbo->insert(self::TABLE_INFORMATION, $attributes);
    }
  }

  public function hasSponsor() {
    if ($this->sponsor_id === null) {
      $this->sponsor_id = (int) $this->dbo->fetchValue('SELECT user_id'
                                                       .' FROM '.T('sponsorship')
                                                       .' WHERE godson_id='.$this->getId());
    }
    if ($this->sponsor_id >= 1) return true;
  }

  public function getSponsorID() {
    if (!$this->hasSponsor()) return 0;
    return $this->sponsor_id;
   }

  public function getSponsor() {
    if (!$this->hasSponsor()) return null;
    try {
      return User::getInstance($this->sponsor_id);
    }
    catch (Exception $e) {}
    return null;
  }

  public function asIdentityHash($locale, $type=null, $options=null) {
    $hash = array('name' => $this->name,
                  'description' => $this->description);
    if ($this->hasFlag(self::FLAG_IMAGE)) {
      $hash['image'] = '/'.$this->getPath().'_a.jpg';
    }
    return $hash;
  }

  public function asEditHash() {
    $h = array();
    if ($this->isItem()) {
      if ($this->hasFlag(self::FLAG_IMAGE)) {
        $h['image'] = '/'.$this->getPath().'_a.jpg';
      }
      $h['quota_hard'] = $this->getInformation('quota_hard');
      $h['quota_soft'] = $this->getInformation('quota_soft');
      $h['birth_date'] = $this->getInformation('birth_date');
      $h['profiles']['person'] = array();
      if ($this->hasProfile('person')) {
        $person = $this->getProfile('person');
        $h['profiles']['person'] = $person->getAttributes();
      }
      if ($this->hasProfile('adherent')) {
        $adherent = $this->getProfile('adherent');
        $h['profiles']['adherent'] = $adherent->getAttributes();
      }
    }
    else {
      $h['quota_hard'] = P('user.quota.hard') ?: self::QUOTA_HARD;
      $h['quota_soft'] = P('user.quota.soft') ?: self::QUOTA_SOFT;
    }
    return $h;
  }

  public function getDetails() {
    $h = array('chemin' => '/'.$this->getPath(),
               'espace utilisé' => $this->getUsedSpace().' M / '.$this->getQuota().' M',
               'source' => '-');
    $origin_id = $this->getInformation('origin_id');
    if ($origin_id >= 1) {
      try {
        $h['source'] = ucwords(Origin::getInstance($origin_id));
      }
      catch (Exception $e) {}
    }
    $dates = $this->dbo->asSet('SELECT created_at'
                               .' FROM '.Intent::TABLE
                               .' WHERE type='.Intent::TYPE_AUTH
                               .  ' AND model_id='.$this->getModelId()
                               .  ' AND record_id='.$this->getId()
                               .' ORDER BY created_at DESC'
                               .' LIMIT 10');
    $dates = join('<br/>', $dates);
    $h += array('nombre d’authentification(s)' => $this->getInformation('auth_count'),
                'dernière(s) authentification(s)' => $dates);
    if (Model::exists('conversion')) {
      $conversions = array();
      $rs = $this->dbo->query('SELECT *'
                              .' FROM '.T('conversion')
                              .' WHERE user_id='.$this->getId()
                              .' ORDER BY created_at DESC'
                              .' LIMIT 20');
      foreach ($rs as $row) {
        $conversion = $row['created_at'].' - ';
        try {
          $item = Item::getInstance($row['model_id'], $row['record_id'],
                                    array('ignore' => true));
          $conversion .= $item->asConversionName();
        }
        catch (Exception $e) {
          $conversion .= Model::label($row['model_id']).' ('.$row['record_id'].')';
        }
        $conversions[] = $conversion;
      }
      if (!empty($conversions)) {
        $conversions = join('<br/>', $conversions);
        $h += array('dernière(s) conversion(s)' => $conversions);
      }
    }
    if (Model::exists('alert')) {
      $filters = array('user_id' => $this->getId(), 
                       'status' => Alert::STATUS_ONLINE,
                       'model_id' => I('keyword'));
      $alerts = Alert::collect(array('filters' => $filters));
      $html = '<ul>';
      $opts = array('on' => array('click' => 'kwo.ux.onExec(this)'),
                    'data' => array('action' => '/back/core/item.disable',
                                    'args' => array('item' => ''),
                                    'confirm' => 'êtes-vous sûr ?',
                                    'model' => 'user',
                                    'callback' => 'hide.up'));
      foreach ($alerts as $alert) {
        $opts['data']['args']['item'] = $alert->getKey();
        $content = H::elt('a', 'supprimer', $opts);
        $content = $alert->asString().' '.$content;
        $html .= H::elt('li', $content);
      };
      $html .= '</ul>';
      if ($alerts->count() >= 1) {
        $h += array('alerte(s)' => $html);
      }
    }

    $url ='http://';
    if(strlen(P('auth.password')) > 2) {
      $url.=P('auth.login').':'.P('auth.password').'@';
    }
    $url.=  P('app.domain').'?credential='.$this->getCredential();
    $h['credential'] = '<a href="'.$url.'" target="_blank">Authentifier</a>';

    return $h;
  }

  public function hasNotice($notice_id) {
    return $this->hasFlag(B($notice_id), 'notices');
  }

  public function getNotices() {
    return $this->getMask('notices', true);
  }

  public function getPrivileges() {
    return $this->getMask('privileges', true);
  }

  public function addPrivilege($privilege_id, $opts=null) {
    if (!is_null($opts)) {
      $privilege = Privilege::getInstance($privilege_id);
      $privilege->grantTo($this, $opts);
    }
    if ($this->hasPrivilege($privilege_id)) return ;
    $this->setFlag(B($privilege_id), 'privileges');
    S('app')->hook('onPrivilegeAdd',
                   array('user' => $this,
                         'privilege' => $privilege_id));
  }

  public function removePrivilege($privilege_id) {
    if (!$this->hasPrivilege($privilege_id)) return ;
    $this->unsetFlag(B($privilege_id), 'privileges');
    S('app')->hook('onPrivilegeRemove',
                   array('user' => $this,
                         'privilege' => $privilege_id));
  }

  public function hasPrivilege($privilege_id) {
    return $this->hasFlag(B($privilege_id), 'privileges');
  }

  public function hasAnyPrivilege($privileges) {
    foreach ($privileges as $privilege_id) {
      if ($this->hasPrivilege($privilege_id)) return true;
    }
    return false;
  }

  public function isAdministrator() {
    return $this->hasPrivilege(Privilege::ADMINISTRATOR);
  }

  public function isModerator() {
    return $this->hasPrivilege(Privilege::MODERATOR);
  }

  public function isSubscriber() {
    return $this->hasPrivilege(Privilege::SUBSCRIBER);
  }

  /*  protected function onAfterDestroy() {
    $this->dbo->exec('DELETE FROM cty_privilege_user'
                     .    ' WHERE user_id='.$this->getId());
    $this->dbo->exec('DELETE FROM '.self::TABLE_INFORMATION
                     .    ' WHERE user_id='.$this->getId());
    $this->dbo->exec('DELETE FROM '.ACL::TABLE
                     .    ' WHERE user_id='.$this->getId());
    $this->dbo->exec('DELETE FROM '.T('subscription')
                     .    ' WHERE user_id='.$this->getId());
                     }*/

  public function destroy() {
    if (S('req')->isCli()) parent::destroy();
  }

  public function hasAccessTo($item, $permissions=null) {
    return ACL::checkAccess($this, $item, $permissions);
  }

  public function avatar($opts=null) {
    $opts = (array) $opts;
    $attributes = array('src' => $this->getThumbnail(),
                        'class' => 'avatar');
    if (!empty($opts['title'])) {
      $attributes['title'] = $opts['title'];
    }
    if ($opts['refresh'] === true) {
      $attributes['src'] .= '?t='.time();
    }
    return H::elt('img', null, $attributes);
  }

  public function getThumbnail() {
    $src = $this->hasFlag(self::FLAG_IMAGE)
         ? '/'.$this->getPath().'_a.jpg'
         : '/app/community/pix/avatar.gif';
    return $src;
  }

  /*** PROFILE ***/

  public function getCustomerProfile() {
    $profile = P('profile.customer') ?: P('profile.person');
    return $this->getProfile($profile);
  }

  public function hasProfile($model=null) {
    if ($model === null) {
      $model = P('profile.user') ?: 'person';
    }
    return $this->getProfileId($model) >= 1;
  }

  private function getProfileId($model=null) {
    if ($model === null) {
      $model = P('profile.user') ?: 'person';
    }
    if (!isset($this->profiles[$model])) {
      $this->profiles[$model] = 0;
      try {
        $profile = Item::getInstance($model, array('user_id' => $this->getId()),
                                     array('ignore' => true));
        $this->profiles[$model] = $profile;
      }
      catch (Exception $e) {}
    }
    return $this->profiles[$model] instanceof ActiveRecord
         ? $this->profiles[$model]->getId()
         : $this->profiles[$model];
  }

  public function getProfile($model=null) {
    if ($model === null) {
      $model = P('profile.user') ?: 'person';
    }
    $record_id = $this->getProfileId($model);
    if ($record_id < 1) {
      throw new Exception('profile unknown');
    }
    if ($this->profiles[$model] instanceof ActiveRecord) {
      return $this->profiles[$model];
    }
    $this->profiles[$model] = Item::getInstance($model, $record_id);
    return $this->profiles[$model];
  }

  public function setProfile($h, $model=null) {
    if ($model === null) {
      $model = P('profile.user') ?: 'person';
    }
    if (!is_array($h) || empty($h)) return ;
    unset($h['id']);
    $profile_id = (int) $this->getProfileId($model);
    $profile = Item::getInstance($model, $profile_id ?: true);
    if (!S('req')->isBack()) {
      $profile->validate($h);
    }
    $h['user_id'] = $this->getId();
    $profile->commit($h);
    $profile->setUser($this->getId());
    if (isset($h['civility'])) {
      if (($h['civility'] >= 1) !== $this->hasFlag(self::FLAG_WOMAN)) {
        if ($h['civility'] >= 1) {
          $this->setFlag(self::FLAG_WOMAN);
        }
        else {
          $this->unsetFlag(self::FLAG_WOMAN);
        }
      }
    }
    $this->profiles[$profile->getModel()] = $profile;

    return $profile;
  }

  /*** /PROFILE ***/

  public function credit($code, $bindings=null) {
    try {
      if (!Model::exists('movement')) return ;
      Movement::trigger($this, $code, $bindings);
    }
    catch (Exception $e) { $this->log->error($e, __METHOD__); }
  }

  public function getCredit() {
    $credit = (int) $this->dbo->fetchValue('SELECT SUM(amount)'
                                           .' FROM '.T('credit')
                                           .' WHERE user_id='.$this->getId()
                                           .' GROUP BY user_id');
    $debit = (int) $this->dbo->fetchValue('SELECT SUM(amount)'
                                          .' FROM '.T('debit')
                                          .' WHERE user_id='.$this->getId()
                                          .' GROUP BY user_id');
    $diff = $credit - $debit;
    $diff = $diff < 0 ? 0 : (int) $diff;
    return $diff;
  }

  public function comment(ActiveRecord $item, $content) {
    if (empty($content)) {
      throw new Exception(l('error.content.empty'));
    }
    $comment = Comment::getInstance();
    $comment->commit(array('model_id' => $item->getModelId(),
                           'record_id' => $item->getId(),
                           'content' => $content,
                           'user_id' => $this->getId()));
    try {
      $item->onComment($comment);
    }
    catch (Exception $e) { S('log')->error($e, __METHOD__); }
    $comment->setUser($this);
    $item->incrementMeta('comment');
    $item->setMetas(array('child' => $comment->getId(),
                          'updated_at' => Date::now()));
    $item->track(Intent::TYPE_COMMENT,
                 array('value' => $comment->getId()));
    return $comment;
  }

  public function getManagedResources($model) {
    $opts = array('filters' => array('|MANAGER|' => $this->getId()));
    return Item::collect($model, $opts);
  }

  public function countManagedResources($model) {
    return Item::collect($model, array());
  }

  public function setEmail($email) {
    if (!Email::isValid($email, true)) {
      $this->log->error('set_email failure ['.$email.']', __METHOD__);
      throw new Exception(l('error.email.invalid'));
    }
    $n = $this->dbo->fetchValue('SELECT COUNT(*)'
                                .' FROM '.T('user')
                                .' WHERE email=:email:'
                                .  ' AND id<>:id:',
                                array(':email:' => $email,
                                      ':id:' => $this->getId()));
    if ($n >= 1) {
      $this->log->error('email exists ['.$email.']', __METHOD__);
      throw new Exception(l('error.email.used'));
    }
    $this->commit(array('email' => $email,
                        'status' => self::STATUS_PENDING));
    return true;
  }

  public function requestEmailConfirmation() {
    Letter::send('email.confirm', $this,
                 array('email' => $this->email,
                       'name' => $this->name,
                       'link' => $this->confirmUrl()));
  }

  public function confirmUrl() {
    $url = H::url('/community/email.confirm',
                  array('id' => $this->getId(),
                        'key' => String::crypt($this->email)));
    return H::elt('a', $url, array('href' => $url));
  }

  public function setPassword($password) {
    $this->commit(array('password' => $password));
  }

  public function onInvitationAccept($invitation) {
    Network::addConnexion($invitation->user_id, $this->getId());
  }

  public function onInvitationRefuse($invitation) {

  }

  public function onInvitationSend(Invitation $invitation) {
    $user = $invitation->getUser();
    $recipient = $invitation->getRecipient();
    $link = '/account/social/invitation.list';
    Letter::send('invitation.user', $recipient,
                 array('user' => $user->name,
                       'link' => $link),
                 array('locale' => $recipient->locale));
  }

  public function asInvitationSnippet($invitation) {
    $msg = '<strong>'.$invitation->getUser().'</strong>';
    $msg .= ' vous propose de rejoindre son réseau.';
    return $msg;
  }

  public function modify($h) {
    unset($h['id']);
    if (!User::isValidUser($h)) {
      throw new Exception(l('error.fields.required'));
    }
    if (isset($h['name'])) {
      $h['name'] = strip_tags($h['name']);
      $h['name'] = String::stripAccents($h['name']);
      $h['name'] = preg_replace('/[^a-zA-Z0-9@\.-]/u', '_', $h['name']);
      $h['name'] = preg_replace('/(_){2,}/u', '_', $h['name']);
      $h['name'] = trim($h['name'], ' _');
    }
    $this->commit($h);
  }

  public function getPath() {
    $path = $this->path;
    if (empty($path)) {
      $path = self::getHash($this->getId());
      $this->setAttribute('path', $path);
    }
    return USR_PATH.'/'.$this->path.'/';
  }

  public function asUrl() {
    return '/community/profile?id='.$this->getId();
  }

  public function hasHomeDirectory() {
    return is_dir($this->getPath());
  }

  public function createHomeDirectory() {
    $path = $this->getPath();
    if (is_dir($path)) return true;
    $ret = Folder::create($path, true);
    if ($ret === false) {
      S('log')->error('home directory creation failure ['.$path.'] ('.$this->getId().')',
                      __METHOD__);
      throw new Exception('home directory creation failure');
    }
    return $ret;
  }

  public function getFiles() {
    if (!$this->hasHomeDirectory()) {
      return array();
    }
    $h = array();
    $files = glob($this->getPath().'*.*');
    if (!is_array($files) || count($files) < 1) {
      return $h;
    }
    foreach ($files as $file) {
      $filename = basename($file);
      if ($filename[0] != '_') {
        $h[] = array('name' => $filename,
                        'path' => $file);
      }
    }
    return $h;
  }

  public function hasFile($name) {
    $name = trim($name);
    $name = basename($name);
    if (empty($name)) return false;
    return file_exists($this->getPath().$name);
  }

  public function removeFile($name) {
    if (!$this->hasFile($name)) return ;
    $file = $this->getFile($name);
    return $file->unlink();
  }

  public function getFile($name) {
    $name = trim($name);
    $name = basename($name);
    return File::getInstance($this->getPath().$name);
  }

  public function getUsedSpace() {
    return $this->hasHomeDirectory()
         ? Folder::getInstance($this->getPath())->getUsedSpace()
         : 0;
  }

  public function getQuota() {
    $quota = $this->getInformation('quota_hard');
    $quota = $quota > 0 ? $quota : P('user.quota.hard');
    $quota = $quota > 0 ? $quota : self::QUOTA_HARD;
    return $quota;
  }

  public function hasAvailableSpace($type='both') {
    if ($type === 'hard' || $type === 'both') {
      if ($this->getUsedSpace() > $this->getQuota()) return false;
    }
    else {
      $quota = $this->getInformation('quota_soft');
      $quota = $quota > 0 ? $quota : P('user.quota.soft');
      $quota = $quota > 0 ? $quota : self::QUOTA_SOFT;
      if (count($this->getFiles()) > $quota) return false;
    }
    return true;
  }

  public function receive($opts=null) {
    if (!$this->hasHomeDirectory()) {
      $this->createHomeDirectory();
    }
    if (!$this->hasAvailableSpace('hard')) {
      $this->log->error('hard quota limit ('.$this->getId().')', __METHOD__);
      throw new Exception(l('error.upload.quota.hard'));
    }
    if (!$this->hasAvailableSpace('soft')) {
      $this->log->error('soft quota limit ('.$this->getId().')', __METHOD__);
      throw new Exception(l('error.upload.quota.soft'));
    }
    $opts = $opts === null ? array('img' => true) : $opts;
    $files = array();
    foreach ($_FILES as $name => $null) {
      if (strlen($_FILES[$name]['name']) < 4) continue ;
      $file = null;
      try {
        $file = UploadManager::user($this, $name);
        $files[] = $file;
      }
      catch (Exception $e) {
        if ($file instanceof File) {
          $file->unlink();
          throw new Exception('Veuillez envoyer une image valide /'
                            .' Please send a valid image');
        }
      }
    }
    //S('app')->hook('onFileUpload', $files);
    return $files;
  }

  public function getCredential() {
    $time = time();
    $ret  = hash('md5', $this->getId().$this->password.$time);
    $ret .= '-'.$this->getId();
    $ret .= '-'.$time;
    return $ret;
  }


  //-- STATIC -----------------------------------------------------------------

  public static function signup($opts=array(), $return_string=false) {
    $req = S('req');
    $res = S('res');
    $ctx = S('ctx');
    if ($req->isXhr() && $req->getHeader('x-kwo-request') === 'exec') {
      S('err')->add(l('error.auth'), Error::CODE_AUTH_FAILURE);
      return ;
    }
    if (isset($opts['callback'])) {
      $ctx->setAttribute('callback', $opts['callback']);
    }
    $opts = array('filters' => array('|&|flags' => Notice::FLAG_SIGNUP));
    $ctx->setAttribute('_notices', Notice::collect($opts));
    $opts = array('filters' => array('|>|status' => 0),
                  'order' => array('position'),
                  'properties' => array('label'));
    $ctx->setAttribute('_origins', Origin::collect($opts));
    $ctx->setAttribute('_mode', $req->mode === 'signup' ? 'signup' : 'login');
    $templates = P('front.templates');
    $template = $templates['community']['signup'] ?: 'community:signup';
    if ($return_string === false) {
      $res->useTemplates($template);
      $res->setSeo(l('login'));
      return ;
    }
    return Template::render($template, true);
  }

  public static function isValidUser($h) {
    $protected = array('flags', 'locale', 'notices', 'password', 'path',
                       'privileges', 'profiles', 'status', 'md5',
                       'quota_soft', 'quota_hard');
    if (count(array_intersect(array_keys($h), $protected)) >= 1) {
      S('log')->debug($h, 'protected fields');
      return false;
    }
    $columns = array_merge(S('dbo')->getTable(T('user'))->getFields(),
                           S('dbo')->getTable(self::TABLE_INFORMATION)->getFields());

    $diff = array_diff(array_keys($h), $columns);
    if (!empty($diff)) {
      S('log')->debug($diff, __METHOD__);
      return false;
    }
    return true;
  }

  public static function getHash($id) {
    if ($id < 1) {
      S('log')->error('invalid uid ('.$id.')', __METHOD__);
      throw new Exception('invalid uid');
    }
    $index = '0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ';
    $out = '';
    $length = strlen($index);
    $t = floor(log10($id) / log10($length));
    do {
      $b = pow($length, $t);
      $a = floor($id / $b);
      $id -= ($a * $b);
      $out .= $index[$a].'/';
      --$t;
    } while ($t >= 0);
    return trim($out, '/');
  }

  public static function clean() {
    if (!defined('USR_PATH') || strlen(USR_PATH) < 2 || !is_dir(USR_PATH)) {
      S('log')->error('failure ['.USR_PATH.']', __METHOD__);
      return ;
    }
    Shell::removeDir(USR_PATH);
  }

}
