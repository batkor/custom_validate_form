<?php

function custom_validate_form_setting($form, &$form_state) {

  $form['custom_validate_form_setting'] = array(
    '#type'  => 'textfield',
    '#title' => t('Form ID'),
    '#default_value' => variable_get('custom_validate_form_setting','')
  );

  return system_settings_form($form);
}

