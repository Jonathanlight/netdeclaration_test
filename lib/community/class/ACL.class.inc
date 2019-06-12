<?php

class ACL {

  const TABLE = 'cty_acl';

  const PERM_FULL = 1;
  const PERM_READ = 2;
  const PERM_WRITE = 4;

  public static function checkAccess($user, $item, $permissions=null) {
    $permissions = $permissions ? $permissions : self::PERM_FULL;
    if ($user->isAdministrator()) return true;
    if ($item->hasAttribute('user_id') && $item->user_id == $user->getId()) {
      return true;
    }
    if (method_exists($item, 'onAccess')) {
      return $item->onAccess($user, $permissions);
    }
    $row = array('model_id' => $item->getModelId(),
                 'record_id' => $item->getId(),
                 'user_id' => $user->getId());
    return S('dbo')->getTable(self::TABLE)->hasRow($row);
  }

  public static function grantAccess($user, $item, $permissions=null) {
    $permissions = $permissions ? $permissions : self::PERM_FULL;
    $row = array('model_id' => $item->getModelId(),
                 'record_id' => $item->getId(),
                 'user_id' => $user->getId(),
                 'permissions' => $permissions);
    S('dbo')->insert(self::TABLE, $row);
  }

  public static function removeAccess($user, $item, $permissions=null) {
    $permissions = $permissions ? $permissions : self::PERM_FULL;
    S('dbo')->exec('DELETE FROM '.self::TABLE
                   .' WHERE model_id='.$item->getModelId()
                   .  ' AND record_id='.$item->getId()
                   .  ' AND user_id='.$user->getId()
                   .' LIMIT 1');
  }

}