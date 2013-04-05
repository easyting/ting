<?php
/**
 * @file ting_object.tpl.php
 *
 * Template to render objects from the Ting database.
 *
 * Available variables:
 * - $object: The TingEntity or TingCollection instance we're rendering.
 * - $content: Render array of content.
 */
?>
<div<?php print $attributes; ?>>
  <?php echo render($content); ?>
</div>
