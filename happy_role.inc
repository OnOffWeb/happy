<?php

/**
 * @file
 * Focus on the role elements.
 */

/**
 * Get all users according to a role.
 *
 * @param mixed $role
 *   An array of roles or a role name.
 * @param boolean $object_return
 *   TRUE of complete object users must be returne, FALSE otherwise
 * @param boolean $intersect
 *
 * @return mixed
 *   An array of user if all is OK, FALSE otherwise.
 */
function happy_role_get_by_role($role, $object_return = FALSE, $intersect = TRUE) {

  // Initialize variables.
  $return = NULL;
  $condition = array();
  $state = array();
  $user_list = array();

  // If a role is defined.
  if (!$role) {
    return FALSE;
  }

  // If there is further role to test.
  if (is_array($role)) {

    // Add rid of each role into a list.
    foreach($role as $r) {
      $condition[] = (is_int($r)) ? $r : user_role_load_by_name($r)->rid;
    }
  }
  else {
    $condition[] = (is_int($role)) ? $role : user_role_load_by_name($role)->rid;
  }

  // For each condition defined.
  foreach ($condition as $rid) {

    // Get user associated to.
    $request = db_select('users_roles', 'UR')
      ->fields('UR', array('uid'))
      ->condition('rid', $rid, '=');
    $result = $request->execute();

    while($unit = $result->fetchObject()) {
      $state[$rid][$unit->uid] = $unit->uid;
    }

    if(empty($user_list)) {
      $user_list = $state[$rid];
    }
    else {
      ($intersect) ? $user_list = array_intersect($user_list, $state[$rid]) : array_merge($user_list, $state[$rid]);
    }
  }

  if ($object_return) {
    foreach ($user_list as $uid => $account) {
      $user_list[$uid] = user_load($uid);
    }
  }

  // Return output;
  return $user_list;
}
