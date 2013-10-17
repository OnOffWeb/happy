<?php

/**
 * happy_taxonomy_get_children_all
 * Return node's nid of all elements tagged with incoming term and children of this term (recursively)
 * @param  int $tid [description]
 * @return array      [array of TID dependent for incoming TID]
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


/**
 * Implement D6 function taxonomy_node_get_terms
 * Find all terms associated with the given node
 * @param  object $node [description]
 * @param  int $vid  [description]
 * @param  string $key  [description]
 * @return array       [description]
 */
function happy_taxonomy_node_get_terms($node, $vid = null, $key = 'tid') {
static $terms;
  if (!isset($terms[$node->vid][$key])) {
    $query = db_select('taxonomy_index', 'r');
    $t_alias = $query->join('taxonomy_term_data', 't', 'r.tid = t.tid');
    $v_alias = $query->join('taxonomy_vocabulary', 'v', 't.vid = v.vid');
    $query->fields( $t_alias );
    $query->condition("r.nid", $node->nid);
    if($vid)
        $query->condition("v.vid", $vid);
    $result = $query->execute();
    $terms[$node->vid][$key] = array();
    foreach ($result as $term) {
      $terms[$node->vid][$key][$term->$key] = $term;
      }
  }
return $terms[$node->vid][$key];
}
