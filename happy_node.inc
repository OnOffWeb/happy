<?php

/**
 * Get node type
 * @param  int $nid [description]
 * @return [type]      [description]
 */
function rca_utils_get_type($nid){
    $query = db_select('node', 'R');
    $query->addField('R', 'type');
    $query->condition('nid', $nid);
    $result = $query->execute()->fetchAll();

    return $result[0]->$type;
}
