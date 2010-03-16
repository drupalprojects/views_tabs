<?php
// $Id$

class views_tabs_plugin_style extends views_plugin_style {

  function options(&$options) {
    parent::options($options);
  }
  
  function render() {
    $tabset = array(
      '#type' => 'tabset',
    );
 
    foreach ($this->view->result as $row) {
      $content = theme($this->theme_functions(), $this->view, $this->options, $row);
      $tab = $row->node_title;
      $tabset[$tab] = array(
        '#type' => 'tabpage',
        '#content' => $content,
        '#title' => $tab,
        '#attributes' => array('class' => 'node-'. $row->nid),
      );
    }
     // print_r($tabset); die;
    return tabs_render($tabset); 
  }
}
