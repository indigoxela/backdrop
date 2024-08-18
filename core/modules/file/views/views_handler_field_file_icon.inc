<?php
/**
 * @file
 * Definition of views_handler_field_file_icon.
 */

/**
 * @ingroup views_field_handlers
 */
class views_handler_field_file_icon extends views_handler_field {

  /**
   * {@inheritdoc}
   */
  public function option_definition() {
    $options = parent::option_definition();
    $options['icon_size'] = array('default' => 32);
    $options['display_type'] = array('default' => 'svg');
    $options['add_alt_text'] = array('default' => TRUE);
    return $options;
  }

  /**
   * {@inheritdoc}
   */
  public function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['icon_size'] = array(
      '#type' => 'number',
      '#title' => t('Icon size'),
      '#min' => 8,
      '#max' => 300,
      '#default_value' => $this->options['icon_size'],
      '#field_suffix' => 'px',
    );
    $form['display_type'] = array(
      '#type' => 'radios',
      '#title' => t('Display type'),
      '#options' => array(
        'svg' => t('Inline SVG markup'),
        'img' => t('Regular image'),
      ),
      '#default_value' => $this->options['display_type'],
    );
    $form['add_alt_text'] = array(
      '#type' => 'checkbox',
      '#title' => t('Add alternative text'),
      '#default_value' => $this->options['add_alt_text'],
    );
  }

  /**
   * {@inheritdoc}
   */
  public function render($values) {
    $value = $this->get_value($values);

    // If there is an extension.
    if ($extension = pathinfo($value, PATHINFO_EXTENSION)) {
      $icon_name = $this->mapExtensionToName($extension);
      if ($this->options['display_type'] == 'img') {
        $icon = $this->renderImg($icon_name, $extension);
      }
      else {
        $icon = $this->renderSvg($icon_name, $extension);
      }
      return $icon;
    }
  }

  /**
   * Render the icon as svg tag.
   */
  protected function renderSvg($icon_name, $extension) {
    $options = array(
      'attributes' => array(
        'width' => $this->options['icon_size'],
        'height' => $this->options['icon_size'],
      ),
    );
    if ($this->options['add_alt_text']) {
      $options['alt'] = t('File icon for @extension extension', array(
        '@extension' => $extension,
      ));
    }
    return icon($icon_name, $options);
  }

  /**
   * Render the icon as img tag.
   */
  protected function renderImg($icon_name, $extension) {
    $attributes = array(
      'width' => $this->options['icon_size'],
      'height' => $this->options['icon_size'],
      'alt' => '',
      'src' => base_path() . icon_get_path($icon_name),
    );
    if ($this->options['add_alt_text']) {
      $attributes['alt'] = t('File icon for @extension extension', array(
        '@extension' => $extension,
      ));
    }
    return '<img ' . backdrop_attributes($attributes) . '>';
  }

  /**
   * Map file extensions to Phosphor icons.
   *
   * @param string $extension
   *   The original file extension.
   *
   * @return string
   *   The name of an icon file, as expected by icon().
   */
  protected function mapExtensionToName($extension) {
    // If there's no 1:1 icon name match for the extension, map to one. It's
    // possible that modules or themes provide additional file icons, so this
    // only acts as a fallback.
    $mapping = array(
      'avi' => 'video',
      'docx' => 'doc',
      'gif' => 'image',
      'gz' => 'archive',
      'jpeg' => 'jpg',
      'm4a' => 'audio',
      'm4v' => 'video',
      'mov' => 'video',
      'mp3' => 'audio',
      'mp4' => 'video',
      'mpeg' => 'video',
      'odt' => 'text',
      'oga' => 'audio',
      'ogg' => 'video',
      'ogv' => 'video',
      'pptx' => 'ppt',
      'tar' => 'archive',
      'tiff' => 'image',
      'tif' => 'image',
      'weba' => 'audio',
      'webm' => 'video',
      'webp' => 'image',
      'xlsx' => 'xls',
    );
    $icon_name = 'file-' . $extension;
    if (!icon_get_path($icon_name)) {
      if (array_key_exists($extension, $mapping)) {
        $icon_name = 'file-' . $mapping[$extension];
      }
      // Fall back to generic file icon.
      else {
        $icon_name = 'file';
      }
    }
    return $icon_name;
  }

}
