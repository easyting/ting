<?php
// $Id$
/**
 * @file ting_object.tpl.php
 *
 * Template to render objects from the Ting database.
 *
 * Available variables:
 * - $object: The TingEntity or TingCollection instance we're rendering.
 * - $content: Render array of content.
 */
$class = isset($object->entities) && count($object->entities) > 1 ? 'ding-entity-collection' : 'ding-entity';

// Dirty hack to prevent duplicate 'class' attribute.
$attributes = str_replace('class="', 'class="clearfix type-' . $class . ' ', $attributes);

// Remove 'id' attribute for fieldset.
$html = render($content);
$html = str_replace('id="ting_object_ting_object_collection_primary_group_collection_object"', '', $html);
$html = str_replace('id="ting_object_ting_object_collection_list_group_collection_list"', '', $html);
?>
<div<?php print $attributes; ?>>
  <?php echo $html; ?>
</div>
