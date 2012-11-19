<?php


/**
 * [user_happy_get_by_role description]
 * @param  [mixed]  $role          [description]
 * @param  boolean $object_return [description]
 * @param  boolean $intersect     [description]
 * @return [type]                 [description]
 */
function happy_user_get_by_role($role, $object_return = FALSE, $intersect = TRUE){
  $return = NULL;
  $condition = array();
  $state = array();
  $user_list = array();

  if($role){

    if(is_array($role)){
      foreach($role as $r)
        $condition[] = (is_int($r)) ? $r : user_role_load_by_name($r)->rid;
     }// if()
    else
        $condition[] = (is_int($role)) ? $role : user_role_load_by_name($role)->rid;

      foreach ($condition as $c) {
         // Create SelectQuery object
        $request = db_select('users_roles', 'UR')
        ->fields('UR', array('uid'))
        ->condition('rid', $c, '=');

        $result = $request->execute();

        while($unit = $result->fetchObject())
          $state[$c][$unit->uid] = $unit->uid;

        if(empty($user_list))
          $user_list = $state[$c];
        else
          ($intersect) ? $user_list = array_intersect($user_list, $state[$c]) : array_merge($user_list, $state[$c]);
      }// foreach()

    if($object_return){
      foreach ($user_list as $uid => $account)
        $user_list[$uid] = user_load($uid);
    }// if()

    $return = $user_list;
  }// if()
  else
    $return = FALSE;

  // Output
  return $return;
}// user_happy_get_by_role()
