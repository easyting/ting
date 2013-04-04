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
?>
<div<?php print $attributes; ?>>
  <?php echo render($content); ?>
</div>
