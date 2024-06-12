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
  }

  /**
   * {@inheritdoc}
   */
  public function render($values) {
    $value = $this->get_value($values);

    // If there is an extension.
    if ($extension = pathinfo($value, PATHINFO_EXTENSION)) {
      $options = array(
        'attributes' => array(
          'width' => $this->options['icon_size'],
          'height' => $this->options['icon_size'],
        ),
      );
      $icon_name = 'file-' . $this->mapExtension($extension);
      $icon = icon($icon_name, $options);
      // Fall back to generic file icon.
      if (strpos($icon, '<!-- ') === 0) {
        $icon = icon('file', $options);
      }
      return $icon;
    }
  }

  /**
   * Map file extensions to Phosphor icons.
   *
   * @param string $extension
   *   The original file extension.
   *
   * @return string
   */
  protected function mapExtension($extension) {
    // If there's no 1:1 icon name match for the extension, map to one.
    $mapping = array(
      'gif' => 'image',
      'jpeg' => 'jpg',
      'docx' => 'doc',
      'xlsx' => 'xls',
      'pptx' => 'ppt',
      'odt' => 'text',
      'mp3' => 'audio',
      'mov' => 'video',
      'mp4' => 'video',
      'm4a' => 'audio',
      'm4v' => 'video',
      'mpeg' => 'video',
      'avi' => 'video',
      'ogg' => 'video',
      'oga' => 'audio',
      'ogv' => 'video',
      'weba' => 'audio',
      'webp' => 'image',
      'webm' => 'video',
      'tif' => 'image',
      'tiff' => 'image',
      'gz' => 'archive',
      'tar' => 'archive',
    );
    if (array_key_exists($extension, $mapping)) {
      return $mapping[$extension];
    }
    return $extension;
  }

}
