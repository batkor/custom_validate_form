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

  //  lang setting
  $form['lang_conteiner'] = array(
    '#type'        => 'fieldset',
    '#tree'        => TRUE,
    '#title'       => t('Language settings'),
    '#collapsible' => TRUE,
    '#collapsed'   => TRUE,
    '#description' => t('Enter the text of the error, depending on the language'),
  );


  $get_enable_langs = locale_language_list('name');
  $save_lang_setting = variable_get('custom_validate_language_setting', array('en' => 'Error'));
  foreach ($get_enable_langs as $key => $lang) {
    $form['lang_conteiner'][$key] = array(
      '#type'          => 'textfield',
      '#title'         => $lang,
      '#default_value' => $save_lang_setting[$key],
    );
  }

  $form['lang_conteiner']['save_lang_setting'] = array(
    '#type'     => 'submit',
    '#value'    => t('Save language setting'),
    '#submit'   => array('custom_validate_save_lang_setting'),
    '#validate' => array('custom_validate_save_lang_setting_validate'),
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

  $form['remove_form_setting'] = array(
    '#type'   => 'submit',
    '#value'  => t('Remove all setting'),
    '#submit' => array('custom_validate_remove_all_setting'),
  );

  return $form;
}

function custom_validate_add_form_setting($form, &$form_state) {
  $old_form_setting = variable_get('custom_validate_form_setting', array());
  $old_form_setting[] = $form_state['values']['new_form_id'];
  variable_set('custom_validate_form_setting', $old_form_setting);
}

function custom_validate_remove_all_setting($form, &$form_state) {
  variable_del('custom_validate_form_setting');
  variable_del('custom_validate_language_setting');
}

function custom_validate_save_lang_setting($form, &$form_state) {
  $lang_new_set = $form_state['values']['lang_conteiner'];
  unset($lang_new_set['save_lang_setting']);
  variable_set('custom_validate_language_setting', $lang_new_set);
}

function custom_validate_save_lang_setting_validate($form, &$form_state) {
  $lang_new_set = $form_state['values']['lang_conteiner'];
  unset($lang_new_set['save_lang_setting']);
  foreach ($lang_new_set as $key => $item) {
    if ($item == '') {
      form_set_error('lang_conteiner][' . $key, t('Please enter the error text for @lang', array('@lang' => $key)));
    }
  }
}