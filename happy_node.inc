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
 * Menu callback; Retrieve a JSON object containing autocomplete suggestions for existing users.
 */
function node_autocomplete($string = '') {
  $matches = array();
  if ($string) {
    $result = db_select('users')->fields('users', array('name'))->condition('name', db_like($string) . '%', 'LIKE')->range(0, 10)->execute();
    foreach ($result as $user) {
      $matches[$user->name] = check_plain($user->name);
    }
  }

  drupal_json_output($matches);
}