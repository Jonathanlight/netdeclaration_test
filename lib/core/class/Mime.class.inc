<?php

class Mime 
{
  public static function getIcon($filename) {
    $parts = explode('.', $filename);
    $type = self::$registry[array_pop($parts)];
    return $type === null ? 'file.png' : $type['icon'];
  }
  
  public static function getContentType($filename) {
    $parts_arr = explode('.', $filename);
    $type = self::$registry[array_pop($parts_arr)];
    return $type === null ? 'application/octet-stream' : $type['mime'];
  }
  
  public static $registry = array('pdf' => array('mime' => 'application/pdf',              
                                                 'icon' => 'pdf.png', 
                                                 'magic' => "\\x25\\x50\\x44\\x46\\x2D"),
                                  'rss' => array('mime' => 'text/xml',
                                                 'icon' => 'xml.png'),
                                  'xml' => array('mime' => 'text/xml',
                                                 'icon' => 'xml.png'),
                                  'gif' => array('mime' => 'image/gif',
                                                 'icon' => 'img.png'),
                                  'jpg' => array('mime' => 'image/jpg',
                                                 'icon' => 'img.png'),
                                  'jpeg' => array('mime' => 'image/jpeg',
                                                  'icon' => 'img.png'),
                                  'png' => array('mime' => 'image/png',
                                                 'icon' => 'img.png'),
                                  'tiff' => array('mime' => 'image/tiff',
                                                  'icon' => 'img.png'),
                                  'bmp' => array('mime' => 'image/bmp',
                                                 'icon' => 'img.png'),
                                  //                                  'csv' => array('mime' => 'application/vnd.ms-excel',
                                  'csv' => array('mime' => 'text/csv',
                                                 'icon' => 'csv.png'),
                                  'xls' => array('mime' => 'application/vnd.ms-excel',
                                                 'icon' => 'csv.png'),
                                  'xlsx' => array('mime' => 'application/vnd.openxmlformats-officedocument.spreadsheetml.sheet',
                                                  'icon' => 'csv.png'),
                                  'doc' => array('mime' => 'application/vnd.ms-word',
                                                 'icon' => 'doc.png'),
                                  'docx' => array('mime' => 'application/vnd.openxmlformats-officedocument.wordprocessingml.document',
                                                  'icon' => 'doc.png'),
                                  'ppt' => array('mime' => 'application/ms-powerpoint',
                                                 'icon' => 'doc.png'),
                                  'pptx' => array('mime' => 'application/vnd.openxmlformats-officedocument.presentationml.presentation',
                                                  'icon' => 'doc.png'),
                                  'rtf' => array('mime' => 'text/rtf',
                                                 'icon' => 'doc.png'),
                                  'css' => array('mime' => 'text/css',
                                                 'icon' => 'html.png'),
                                  'txt' => array('mime' => 'text/plain',
                                                 'icon' => 'file.png'),
                                  'fla' => array('mime' => 'text/plain',
                                                 'icon' => 'flash.png'),
                                  'html' => array('mime' => 'text/html',
                                                  'icon' => 'html.png'),
                                  'java' => array('mime' => 'text/plain',
                                                  'icon' => 'java.png'),
                                  'class' => array('mime' => 'application/octet-stream',
                                                   'icon' => 'java.png'),
                                  'php' => array('mime' => 'text/plain',
                                                 'icon' => 'psp.png'),
                                  'psp' => array('mime' => 'text/plain',
                                                 'icon' => 'psp.png'),
                                  'zip' => array('mime' => 'application/zip',
                                                 'icon' => 'compress.png'),
                                  'rar' => array('mime' => 'application/x-rar-compressed',
                                                 'icon' => 'compress.png'),
                                  'gz'  => array('mime' => 'application/x-gzip',
                                                 'icon' => 'compress.png'),
                                  'tgz' => array('mime' => 'application/x-gzip',
                                                 'icon' => 'compress.png'),
                                  'avi' => array('mime' => 'video/x-msvideo',
                                                 'icon' => 'video.png'),
                                  'mpg' => array('mime' => 'video/mpeg',
                                                 'icon' => 'video.png'),
                                  'mpeg' => array('mime' => 'video/mpeg',
                                                  'icon' => 'video.png'),
                                  'mov' => array('mime' => 'video/quicktime',
                                                 'icon' => 'video.png'),
                                  'mp3' => array('mime' => 'audio/mpeg',
                                                 'icon' => 'video.png'),
                                  'wav' => array('mime' => 'audio/x-wav',
                                                 'icon' => 'video.png'),
                                  'eml' => array('mime' => 'message/rfc822',
                                                 'icon' => 'email.png'),
                                  'emlx' => array('mime' => 'message/rfc822',
                                                  'icon' => 'email.png'),
                                  'msg' => array('mime' => 'message/rfc822',
                                                 'icon' => 'email.png'),
                                  'ico' => array('mime' => 'image/vnd.microsoft.icon',
                                                 'icon' => 'img.png'),
                                  'js'  => array('mime' => 'application/javascript',
                                                 'icon' => 'html.png'),
                                  'svg' => array('mime' => 'image/svg+xml',
                                                 'icon' => 'xml.png'),
                                  'swf' => array('mime' => 'application/x-shockwave-flash',
                                                 'icon' => 'flash.png'),
                                  'xul' => array('mime' => 'application/vnd.mozilla.xul+xml',
                                                 'icon' => 'xml.png'),
                                  'xbl' => array('mime' => 'text/xml',
                                                 'icon' => 'xml.png'),
                                  'emf' => array('mime' => 'image/x-emf',
                                                 'icon' => 'image.png'),
                                  'wmf' => array('mime' => 'image/x-wmf',
                                                 'icon' => 'image.png')
                                  );
                                  
                                  /*  public static function isPDF($file_path) {
    $PDF_MAGIC = "\\x25\\x50\\x44\\x46\\x2D";
    return (file_get_contents($file_path, false, null, 0, strlen($PDF_MAGIC)) === $PDF_MAGIC);
  }*/

}