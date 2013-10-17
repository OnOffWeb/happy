<?php

/**
 * Find user's uid with his name
 * @param  String   $name
 * @param  boolean  $object_return Set if user Object must be returned
 */
function happy_user_get_by_name($name, $object_return = FALSE){
  if($name){
    $account = db_select('users', 'U')
            ->fields('U', array('uid'))
            ->condition('name', $name, '=')
            ->execute()
            ->fetchObject();

        $return = ($account) ? ($object_return) ? user_load($account->uid) : $account->uid : FALSE;
  }
  else
    $return = FALSE;

    return $return;
}
