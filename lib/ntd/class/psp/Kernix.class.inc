<?php

class Kernix {
  
  private static function config() {
    $config = P('shop.psp');
    $config = $config['check'] ? $config['check'] : array();
    return $config;
  }
  
  public static function request($payment) { 

    $method = $payment->getMethod();
    $facture = $payment->getFacture();

    $config = self::config();
    $response_url = $config['payment.response'] ?: '/middle/payment.response';

    $html  = '<form method="post" target="_top" action="'.$response_url.'" id="kernix-payment-form">'."\n"; 
    $html .= ' <input type="hidden" name="item" value="'.$facture->getKey().'" />'."\n"; 
    $html .= '</form>'."\n"; 
    $html .= '<img src="/app/core/pix/empty.gif" onload="$(\'kernix-payment-form\').submit()" />';

    return $html;
  }

  public static function callback() {}

  public static function response() {}
  
}