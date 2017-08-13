<?php

/**
 * @see custom_validate_form_menu()
 *
 * @param $form
 * @param $form_state
 *
 * @return mixed
 */
function custom_validate_form_setting($form, &$form_state) {

  $form['new_form_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Form ID'),
    '#default_value' => '',
  );

  $form['add_form_setting'] = array(
    '#type' => 'submit',
    '#value' => t('Add form'),
    '#submit' => array('custom_validate_add_form_setting'),
  );

  //  lang setting
  $form['lang_conteiner'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
    '#title' => t('Language settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => t('Enter the text of the error, depending on the language'),
  );

  //get enable language
  $get_enable_langs = locale_language_list('name');
  //get saving setting language
  $save_lang_setting = variable_get('custom_validate_language_setting', array());
  foreach ($get_enable_langs as $key => $lang) {
    $form['lang_conteiner'][$key] = array(
      '#type' => 'textfield',
      '#title' => $lang,
      '#default_value' => empty($save_lang_setting) ? '' : $save_lang_setting[$key],
    );
  }

  $form['lang_conteiner']['save_lang_setting'] = array(
    '#type' => 'submit',
    '#value' => t('Save language setting'),
    '#submit' => array('custom_validate_save_lang_setting'),
    '#validate' => array('custom_validate_save_lang_setting_validate'),
  );

  //text checked
  $form['text_checked'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
    '#title' => t('Regular expressions for validation'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => t('Setting regular expressions for validate'),
  );

  $form['text_checked']['text_checked'] = array(
    '#type' => 'textfield',
    '#title' => t('Enter regular expressions for validate'),
    '#description' => t('Supports regular expressions'),
  );

  $form['text_checked']['add_text_checked'] = array(
    '#type' => 'submit',
    '#value' => t('Add validate'),
    '#submit' => array('custom_validate_add_text_checked'),
  );

  $header = array(
    'item_validate' => t('Items validate'),
    'action' => t('Action'),
  );
  $options = array();
  $text_checked = variable_get('custom_validate_text_checked', array());

  foreach ($text_checked as $key => $item) {
    $options[] = array(
      'item_validate' => $item,
      'action' => t('<a href="@link">Remove</a>', array('@link' => 'validate_form/remove_text_checked/' . $key)),
    );
  }

  $form['text_checked']['table_selected_validate'] = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $options,
    '#empty' => t('Not text/word for validate'),
  );

  //form id list
  $header = array(
    'id_use_form' => t('ID used forms'),
  );

  $form_setting = variable_get('custom_validate_form_setting', array());
  $options = array();
  foreach ($form_setting as $item) {
    $options[] = array(
      'id_use_form' => $item,
    );
  }

  $form['table_selected_ballon'] = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $options,
    '#empty' => t('No forms have been selected'),
  );

  $form['remove_form_setting'] = array(
    '#type' => 'submit',
    '#value' => t('Remove all setting'),
    '#submit' => array('custom_validate_remove_all_setting'),
  );

  return $form;
}

/**
 * @see \custom_validate_add_form_setting()
 *
 * @param $form
 * @param $form_state
 */
function custom_validate_add_form_setting($form, &$form_state) {
  $old_form_setting = variable_get('custom_validate_form_setting', array());
  $old_form_setting[] = $form_state['values']['new_form_id'];
  variable_set('custom_validate_form_setting', $old_form_setting);
}

/**
 * @see \custom_validate_add_form_setting()
 *
 * @param $form
 * @param $form_state
 */
function custom_validate_remove_all_setting($form, &$form_state) {
  variable_del('custom_validate_form_setting');
  variable_del('custom_validate_language_setting');
  variable_del('custom_validate_text_checked');
}

/**
 * @see \custom_validate_add_form_setting()
 *
 * @param $form
 * @param $form_state
 */
function custom_validate_save_lang_setting($form, &$form_state) {
  $lang_new_set = $form_state['values']['lang_conteiner'];
  unset($lang_new_set['save_lang_setting']);
  variable_set('custom_validate_language_setting', $lang_new_set);
}

/**
 * @see \custom_validate_add_form_setting()
 *
 * @param $form
 * @param $form_state
 */
function custom_validate_save_lang_setting_validate($form, &$form_state) {
  $lang_new_set = $form_state['values']['lang_conteiner'];
  unset($lang_new_set['save_lang_setting']);
  foreach ($lang_new_set as $key => $item) {
    if ($item == '') {
      form_set_error('lang_conteiner][' . $key, t('Please enter the error text for @lang', array('@lang' => $key)));
    }
  }
}

/**
 * @see \custom_validate_form_setting()
 *
 * @param $form
 * @param $form_state
 */
function custom_validate_add_text_checked($form, &$form_state) {
  $old_text_checked = variable_get('custom_validate_text_checked', array());
  $old_text_checked[] = $form_state['values']['text_checked']['text_checked'];
  variable_set('custom_validate_text_checked', $old_text_checked);
}