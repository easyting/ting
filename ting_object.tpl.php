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
?>
<div class="<?php print $classes; ?> clearfix type-<?php print $class;?>"<?php print $attributes; ?>>
    <?php echo render($content); ?>
</div>
