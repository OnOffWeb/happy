<?php

/**
 * [happy_taxonomy_get_children_all]
 * Return node's nid of all elements tagged with incoming term and children of this term (recursively)
 * @param  [int] $tid [description]
 * @return [array]      [array of TID dependent for incoming TID]
 */
function happy_taxonomy_get_children_all($tid){
  $return = array();

  $return = taxonomy_select_nodes($tid, FALSE, FALSE);

  $children = taxonomy_get_children($tid);

  if(!empty($children)){
    foreach($children as $key => $child)
      $return += happy_taxonomy_get_children_all($key);
  }

  return $return;
}
