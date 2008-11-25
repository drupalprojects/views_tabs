<?php

class views_tabs_plugin_style extends views_plugin_style {

  function options(&$options) {
    parent::options($options);
    $options['tab_field'] = 'title';
  }
 
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $options = $this->options;
    $opt = array('' => t('<None>'));
    foreach ($this->display->handler->get_handlers('field') as $field => $handler) {
      if ($label = $handler->label()) {
        $opt[$field] = $label;
      }
      else {
        $opt[$field] = $handler->ui_name();
      }
    }

    $form['tab_field'] = array(
      '#title' => t('Tab field'),
      '#type'  => 'select',
      '#options' => $opt,
      '#default_value' => $options['tab_field'],
    );
  }
  
  function render() {
    $tabset = array(
      '#type' => 'tabset',
    );
   
    $tab_field = $this->view->field[$this->options['tab_field']]->field_alias;
   
    foreach ($this->view->result as $row) {
      $content = theme($this->theme_functions(), $this->view, $this->options, $row);
     
      $tab = $row->$tab_field;
      $tabset[$tab] = array(
        '#type' => 'tabpage',
        '#content' => $content,
        '#title' => $tab,
        '#attributes' => array('class' => 'node-'. $row->nid),
      );
    }
//      print_r($tabset); die;
    return tabs_render($tabset); 
  }
}
