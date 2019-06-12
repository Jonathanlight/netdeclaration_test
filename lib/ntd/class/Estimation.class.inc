<?php

class Estimation extends ActiveRecord {

  const PATH_PDF = 'doc/devis';

  const FLAG_DOMTOM = 1;
  const FLAG_DISABLED_ACCES_EDI = 2;

  public static $flags = array(
    self::FLAG_DOMTOM => 'DOM-TOM',
  );

  public function addTarif(Tarif $tarif, $quantity = 1, $tarif_price = null) {
    if (is_null($tarif_price)) {
      $tarif_price = $tarif->price;
    }
    parent::addTarif($tarif,
                     array(
                       'quantity' => $quantity,
                       'amount_unitary' => $tarif_price,
                       'amount_total' => $tarif_price * $quantity
                     ));
    $this->calculate();
  }

  public function getPdfPath() {
    return self::PATH_PDF . '/' . $this->getId() . '.pdf';
  }

  public function generatePdf() {

    if (!Folder::exists(self::PATH_PDF)) {
      Folder::create(self::PATH_PDF, true);
    }

    $path_target = $this->getPdfPath();
    $path_source = str_replace('.pdf', '.html', $path_target);

    $fp = fopen($path_source, 'w');
    fwrite($fp, H::get('/middle/core/devis.print', array('id' => $this->getId())));
    fclose($fp);

    // TODO : use H::inc
    $header = H::url('/skeleton.pdf.header',
                     array('domtom' => $this->hasFlag(Estimation::FLAG_DOMTOM),
                           'head_title' => base64_encode('Devis N°' . $this->getId())));
    $footer = H::url('/skeleton.pdf.footer',
                     array('domtom' => $this->hasFlag(Estimation::FLAG_DOMTOM)));


    $options = array('--header-html' => "'" . $header . "'",
                     '--footer-html' => "'" . $footer . "'",
                     '--username' => P('auth.login') ?: '',
                     '--password' => P('auth.password') ?: '',
                     '--page-size' => 'A4',
                     '--margin-top' => '34',
                     '--margin-left' => '0',
                     '--margin-right' => '0',
                     '--margin-bottom ' => '20',
                     '--header-spacing' => '0',
                     '--footer-spacing' => '0',
                     '--outline-depth' => '0');

    $cmd = '/bin/bash -c "export DISPLAY=127.0.0.1:123; /etc/kernix/bin/wkhtmltopdf '
      . NetDeclaration::asShellParams($options)
      . " '"
      . $path_source
      . "' '"
      . $path_target
      . '\'"';
    S('log')->debug($cmd, __METHOD__);
    system($cmd);

    return $path_target;
  }

  public function calculate() {

    if (!Country::exists($this->country_id)) {
      S('log')->error('country [' . $this->country_id . '] not exists', __METHOD__);
      return false;
    }
    $country = Country::getInstance($this->country_id);

    $total_amount_ht = 0;
    foreach ($this->getTarifs() as $tarif) {
      $total_amount_ht += $tarif->estimation_amount_total;
    }
    $tax_percent = $country->taxes;
    $tax_amount = $total_amount_ht * $tax_percent;
    $total_amount_ttc = $total_amount_ht + $tax_amount;

    $this->commit(array(
                    'tax_amount' => $tax_amount,
                    'tax_percent' => $tax_percent,
                    'total_amount_ht' => $total_amount_ht,
                    'total_amount_ttc' => $total_amount_ttc
                  ));
    return true;
  }

}