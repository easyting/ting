<?php

/**
 * @file
 * Field hook implementations.
 */

/**
 * Implements hook_field_info().
 */
function ting_field_info() {
  return array(
    // ting_object
    'ting_title' => array(
      'label' => t('Ting object title'),
      'description' => t('Ting object title'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_title_default',
      'no_ui' => TRUE,
    ),
    'ting_type' => array(
      'label' => t('Ting object type'),
      'description' => t('Ting object type'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_type_default',
      'no_ui' => TRUE,
    ),
    'ting_series' => array(
      'label' => t('Ting object series'),
      'description' => t('Ting object series'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_series_default',
      'no_ui' => TRUE,
    ),
    'ting_abstract' => array(
      'label' => t('Ting object abstract'),
      'description' => t('Ting object abstract'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_abstract_default',
      'no_ui' => TRUE,
    ),
    'ting_author' => array(
      'label' => t('Ting object author'),
      'description' => t('Ting object author'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_author_default',
      'no_ui' => TRUE,
    ),
    'ting_subjects' => array(
      'label' => t('Ting object subjects'),
      'description' => t('Ting object subjects'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_subjects_default',
      'no_ui' => TRUE,
    ),
    // ting_collection
    'ting_primary_object' => array(
      'label' => t('Ting collection primary object'),
      'description' => t('Ting collection primary object'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_primary_object_default',
      'no_ui' => TRUE,
    ),
    'ting_entities' => array(
      'label' => t('Ting collection listing'),
      'description' => t('Ting collection listing'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_entities_default',
      'no_ui' => TRUE,
    ),
    'ting_collection_types' => array(
      'label' => t('Ting collection object types'),
      'description' => t('Ting collection object types'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_collection_types_default',
      'no_ui' => TRUE,
    ),
  );
}

/**
 * Implements hook_widget_info_alter().
 */
function ting_widget_info_alter(&$info) {
  if (isset($info['hidden'])) {
    $info['hidden']['field types'] += array(
      'ting_title',
      'ting_type',
      'ting_abstract',
      'ting_author',
      'ting_subjects',
      'ting_primary_object',
      'ting_entities',
      'ting_collection_types',
    );
  }
}

/**
 * Implements hook_field_load().
 */
function ting_field_load($entity_type, $entities, $field, $instances, $langcode, &$items, $age) {
  // Transform entities into a multiple field.
  if ($field['type'] == 'ting_entities') {
    foreach ($entities as $id => $entity) {
      foreach ($entity->entities as $ent) {
        $items[$id][] = array(
          'id' => $ent->id,
        );
      }
    }
  }
  else {
    foreach ($entities as $id => $entity) {
      $items[$id][0] = array(
        'id' => $entity->id,
      );
    }
  }
}

/**
 * Implements hook_field_formatter_info().
 */
function ting_field_formatter_info() {
  return array(
    'ting_title_default' => array(
      'label' => t('Default'),
      'field types' => array(
        'ting_title',
      ),
      'settings' => array(
        'link_type' => 'none',
      ),
    ),
    'ting_type_default' => array(
      'label' => t('Default'),
      'field types' => array(
        'ting_type',
      ),
    ),
    'ting_series_default' => array(
      'label' => t('Default'),
      'field types' => array(
        'ting_series',
      ),
    ),
    'ting_abstract_default' => array(
      'label' => t('Default'),
      'field types' => array(
        'ting_abstract',
      ),
    ),
    'ting_author_default' => array(
      'label' => t('Default'),
      'field types' => array(
        'ting_author',
      ),
    ),
    'ting_subjects_default' => array(
      'label' => t('Default'),
      'field types' => array(
        'ting_subjects',
      ),
    ),
    'ting_primary_object_default' => array(
      'label' => t('Default'),
      'field types' => array(
        'ting_primary_object',
      ),
      'settings' => array(
        'view_mode' => 'teaser',
      ),
    ),
    'ting_entities_default' => array(
      'label' => t('Default'),
      'field types' => array(
        'ting_entities',
      ),
      'settings' => array(
        'hide_primary' => TRUE,
        'view_mode' => 'teaser',
      ),
    ),
    'ting_collection_types_default' => array(
      'label' => t('Default'),
      'field types' => array(
        'ting_collection_types',
      ),
    ),
  );
}

/**
 * Implements hook_field_formatter_settings_form().
 */
function ting_field_formatter_settings_form($field, $instance, $view_mode, $form, $form_state) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];
  $element = NULL;

  switch ($field['type']) {
    case 'ting_title':
      $element['link_type'] = array(
        '#type' => 'radios',
        '#title' => t('Link title to'),
        '#options' => array(
          'none' => t("Don't link"),
          'object' => t('Object'),
          'collection' => t('Collection, if part of a collection'),
        ),
        '#default_value' => $settings['link_type'],
      );
      break;
    case 'ting_entities':
      $element['hide_primary'] = array(
        '#type' => 'checkbox',
        '#title' => t('Hide primary'),
        '#description' => t("Don't show the primary object as part of the list."),
        '#default_value' => $settings['hide_primary'],
      );
    case 'ting_primary_object':
      $entity_info = entity_get_info('ting_object');
      $view_modes = array();
      foreach ($entity_info['view modes'] as $view_mode => $view_mode_info) {
        $view_modes[$view_mode] = $view_mode_info['label'];
      }

      $element['view_mode'] = array(
        '#title' => t('View mode'),
        '#type' => 'select',
        '#default_value' => $settings['view_mode'],
        '#options' => $view_modes,
      );
      break;
  }

  return $element;
}

/**
 * Implements hook_field_formatter_settings_summary().
 */
function ting_field_formatter_settings_summary($field, $instance, $view_mode) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];
  $summary = '';
  switch ($field['type']) {
    case 'ting_title':
      $summary .= t('Link type: @type', array('@type' => $settings['link_type']));
      break;
    case 'ting_entities':
      $summary .= $settings['hide_primary'] ? t("Don't show primary. ") : t("Include primary. ");
    case 'ting_primary_object':
      $view_mode = $settings['view_mode'];
      $entity_info = entity_get_info('ting_object');
      if (isset($entity_info['view modes'][$view_mode])) {
        $view_mode = $entity_info['view modes'][$view_mode]['label'];
      }

      $summary .= t('View mode @view_mode', array('@view_mode' => $view_mode));
      break;
  }

  return $summary;
}


/**
 * Implements hook_field_formatter_view().
 */
function ting_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();

  // Entity listing is a special case.
  if ($display['type'] == 'ting_entities_default') {
    $entities = $entity->entities;
    // Skip the first.
    if ($display['settings']['hide_primary']) {
      $primary = array_shift($entities);
    }

    foreach ($entity->types as $type) {
      $element[0][$type] = array(
        '#prefix' => '<h2>' . $type . '</h2><span id="' . _ting_anchor_name($type) . '"></span>',
      );
    }
    foreach ($entities as $sub_entity) {
      $element[0][$sub_entity->type][$sub_entity->id] = ting_object_view($sub_entity, $display['settings']['view_mode']);
    }

    return $element;
  }

  foreach ($items as $delta => $item) {
    switch ($display['type']) {
      case 'ting_title_default':
        /*
         * This doesn't work due to the way objects gets cached at the
         * moment. Until that is fixed, link all objects to collections when
         * requested, the page will redirect to ting/object/X if there is only
         * one.
         */
        $type = 'ting_object';
        if ($display['settings']['link_type'] == 'collection') {
        //   // Check if the cache contains an collection for this id.
        //   $x = ting_cache_get($entity->id);
        //   if ($x instanceof TingClientObjectCollection) {
          $type = 'ting_collection';
        //   }
        }
        if ($display['settings']['link_type'] != 'none') {
          $url = entity_uri($type, $entity);
          $title = l($entity->title, $url['path'], $url['options']);
        }
        else {
          $title = check_plain($entity->title);
        }
        $element[$delta] = array(
          '#prefix' => '<h2>',
          '#suffix' => '</h2>',
          '#markup' => $title,
        );
        break;
      case 'ting_type_default':
        $element[$delta] = array(
          '#theme' => 'item_list',
          '#items' => array(
            array(
              'data' => $entity->type,
              'class' => array(drupal_html_class($entity->type)),
            ),
          ),
        );
        break;
      case 'ting_series_default':
        $series = $entity->serieTitle;
        if ($series) {
          $links = '';
          $options = array('attributes' => array('class' => array('series')));
          $dc_title = variable_get('ting_admin_register_serie_title', 'dc.title');
          foreach ($series as $key => $serie) {
            $path = 'search/ting/' . $dc_title . '="' . drupal_strtolower($serie) . '"';
            $serie_number = (isset($entity->serieNumber[$key]) && !empty($entity->serieNumber[$key])) ? ' : ' . $entity->serieNumber[$key] : '';
            $links .= '<span class="series_number">' . l($serie, $path, $options) . $serie_number . '</span>';
          }
          $element[$delta] = array(
            // should use phrase.title instead of dc.title but at the moment opensearch does not support the use of phrase.title
            '#markup' => $links,
          );
        }
        break;
      case 'ting_abstract_default':
        $element[$delta] = array(
          '#markup' => check_plain($entity->abstract),
        );
        break;
      case 'ting_author_default':
        $creators = array();
        if (!isset($entity->reply->record['dc:creator']['oss:sort'])) {
          foreach ($entity->creators as $i => $creator) {
            $creators[] = l($creator, 'search/ting/dc.creator="' . $creator . '"', array('attributes' => array('class' => array('author'))));
          }
        }
        else {
          // Place dc.creator on url according to oss:sort field.
          // Use corresponing creator element for name. If this does not exist use oss:sort as name.
          foreach ($entity->reply->record['dc:creator']['oss:sort'] as $i => $creator) {
            $creators[] = l(isset($entity->creators[$i]) ? $entity->creators[$i] : $creator, 'search/ting/dc.creator="' . $creator . '"', array('attributes' => array('class' => array('author'))));
          }
        }
        $markup_string = '';
        if (count($creators)) {
          if ($entity->date != '') {
            $markup_string = t('By !author_link (@year)', array(
              '!author_link' => implode(', ', $creators),
              '@year' => $entity->date, // So wrong, but appears to be the way the data is.
            ));
          }
          else {
            $markup_string = t('By !author_link', array(
              '!author_link' => implode(', ', $creators),
            ));
          }
        }
        elseif ($entity->date != '') {
          $markup_string = t('(@year)', array('@year' => $entity->date));
        }
        $element[$delta] = array(
          '#markup' => $markup_string,
        );
        break;
      case 'ting_subjects_default':
        if (count($entity->subjects) == TRUE) {
          $subjects = array();
          foreach ($entity->subjects as $subject) {
            $subjects[] = l($subject, 'search/ting/dc.subject="' . $subject . '"', array('attributes' => array('class' => array('subject'))));
          }
          $element[$delta] = array(
            '#markup' => implode(' ', $subjects),
          );
        }
        break;
      case 'ting_primary_object_default':
        $element[$delta] = ting_object_view($entity->primary_object, $display['settings']['view_mode']);
        break;
      case 'ting_collection_types_default':
        $types = array();
        foreach ($entity->types as $type) {
          $types[] = array(
            'data' => $type,
            'class' => array(drupal_html_class($type)),
          );
        }
        $element[$delta] = array(
          '#theme' => 'item_list',
          '#items' => $types,
        );
        break;
    }
  }

  return $element;
}
