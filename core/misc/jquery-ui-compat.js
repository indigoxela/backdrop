/**
 * @file
 * Sets the compatibility flag for jQuery UI to true.
 *
 * Core still uses deprecated "dialogClass" option, which is deprecated and as
 * jQuery UI version 1.14 this flag defaults to false.
 */
(function ($) {
  $.uiBackCompat = true;
})(jQuery);
