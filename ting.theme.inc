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
  $variables['classes_array'][] = drupal_html_class('view-mode-' . $variables['elements']['#view_mode']);
  // Helpful $content variable for templates.
  foreach (element_children($variables['elements']) as $key) {
    $variables['content'][$key] = $variables['elements'][$key];
  }

  if (isset($variables['content']['entities'])) {
    foreach ($variables['content']['entities'] as $key => $val) {
      $variables['content']['overview']['types'][] = $key;
    }
  }

  // Disable entity buttons for collection items.
  if (is_object($variables['object']) && $variables['object'] instanceof TingCollection) {
    if (count($variables['object']->getEntities()) > 1) {
      unset($variables['content']['ting_primary_object'][0]['ding_entity_buttons']);
    }
  }

  // Remove fieldset 'id' attribute.
  if (!empty($variables['content']['group_collection_object']['#id'])) {
    unset($variables['content']['group_collection_object']['#id']);
  }
  if (!empty($variables['content']['group_collection_list']['#id'])) {
    unset($variables['content']['group_collection_list']['#id']);
  }
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
