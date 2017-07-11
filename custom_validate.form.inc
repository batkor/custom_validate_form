<?php

function custom_validate_form_setting($form, &$form_state) {

  $form['new_form_id'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Form ID'),
    '#default_value' => '',
  );

  $form['add_form_setting'] = array(
    '#type'   => 'submit',
    '#value'  => t('Add form'),
    '#submit' => array('custom_validate_add_form_setting'),
  );

  $header = array(
    'id_use_form' => t('ID used forms'),
  );
  $options = array();
  $form_setting = variable_get('custom_validate_form_setting', array());

  foreach ($form_setting as $item) {
    $options[] = array(
      'id_use_form' => $item,
    );
  }

  $form['table_selected_ballon'] = array(
    '#theme'  => 'table',
    '#header' => $header,
    '#rows'   => $options,
    '#empty'  => t('No forms have been selected'),
  );

  return $form;
}

function custom_validate_add_form_setting($form, &$form_state) {
  $old_form_setting = variable_get('custom_validate_form_setting', array());
  $old_form_setting['id_use_form'] = $form_state['values']['new_form_id'];
  variable_set('custom_validate_form_setting', $old_form_setting);
}