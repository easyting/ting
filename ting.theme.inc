<?php

/**
 * @file
 * Theming functions for ting.
 */

/**
 * Template preprocessor for ting objects.
 */
function template_preprocess_ting_object(&$variables) {
  $variables['object'] = $variables['elements']['#object'];

  $variables['page'] = $variables['elements']['#view_mode'] == 'full';
  // Helpful $content variable for templates.
  foreach (element_children($variables['elements']) as $key) {
    $variables['content'][$key] = $variables['elements'][$key];
  }

  if (isset($variables['content']['entities'])) {
    foreach ($variables['content']['entities'] as $key => $val) {
      $variables['content']['overview']['types'][] = $key;
    }
  }

  // Set entity 'class'.
  $class = 'ding-entity';

  // Disable entity buttons for collection items.
  if (is_object($variables['object']) && $variables['object'] instanceof TingCollection) {
    // Set collection 'class'.
    $class = 'ding-entity-collection';

    if (count($variables['object']->getEntities()) > 1) {
      unset($variables['content']['ting_primary_object'][0]['ding_entity_buttons']);
    }
  }

  // Modify 'alt' attribute for list items.
  if (!empty($variables['content']['ting_cover']) && !empty($variables['content']['group_collection_list'])) {
    $variables['content']['ting_cover'][0]['#alt'] = implode(' ', array(
      $variables['object']->title,
      $variables['object']->type,
      $variables['object']->date,
    ));
  }

  // Remove fieldset 'id' attribute.
  if (!empty($variables['content']['group_collection_object']['#id'])) {
    unset($variables['content']['group_collection_object']['#id']);
  }
  if (!empty($variables['content']['group_collection_list']['#id'])) {
    unset($variables['content']['group_collection_list']['#id']);
  }
  if (!empty($variables['content']['group_content']['#id'])) {
    unset($variables['content']['group_content']['#id']);
  }

  // Set additional classes.
  $variables['classes_array'] = array_merge($variables['classes_array'], array(
    'clearfix',
    'type-' . $class,
    drupal_html_class('view-mode-' . $variables['elements']['#view_mode']),
  ));
}

/**
 * Helper function to format abstracts from ting.
 */
function ting_format_abstract($string) {
  $string = str_replace('Indhold:', '', $string);
  $string = str_replace(' ; ', '<br/>', $string);
  $string = str_replace(' / ', '<br/>', $string);

  return $string;
}
