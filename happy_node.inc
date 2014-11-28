<?php

/**
 * @file
 * Focus on the node elements.
 */

/**
 * Get node type.
 *
 * @param int $nid
 *   The nid of the node to retrieve its type.
 *
 * @return string
 *   The type found.
 */
function happy_get_type($nid) {
  $query = db_select('node', 'R');
  $query->addField('R', 'type');
  $query->condition('nid', $nid);
  $result = $query->execute()->fetchAll();

  return $result[0]->type;
}

/**
 * Get all views mode.
 *
 * @param string Node type
 *   The node type you wanted view mode for.
 *
 * @return array
 *   View mode found.
 */
function happy_get_views_mode($node_type = 'node') {
  $entity_info = entity_get_info($node_type);

  return(array_keys($entity_info['view modes']));
}