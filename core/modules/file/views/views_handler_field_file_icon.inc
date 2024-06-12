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
    if (array_key_exists($extension, $mapping)) {
      return $mapping[$extension];
    }
    return $extension;
  }

}
