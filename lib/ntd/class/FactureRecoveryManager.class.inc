<?php

class FactureRecoveryManager {

  public static function getFactureSetByAdherentToBeRecovery($args=array()) {
    $statuses = array(Facture::STATUS_NON_PAYE, Facture::STATUS_PENDING);

    $sql = 'SELECT f.adherent_id, GROUP_CONCAT(f.id ORDER BY f.id SEPARATOR ",") AS facture_list'
           .' FROM %s f'
           .' JOIN %s a ON a.id = f.adherent_id'
           .' WHERE f.status IN (%s)'
           .' AND (f.flags & %s) > 0'
           .' AND (f.flags & %s) <= 0'
           .' AND f.is_recovery = 0'
           .' AND f.price_ttc > 0';

    if (!empty($args['from'])) {
      $sql .= ' AND start_at >= "' . $args['from'] . '"';
    }

    if (!empty($args['to'])) {
      $sql .= ' AND start_at <= "' . $args['to'] . '"';
    }

    $sql .= ' GROUP BY f.adherent_id';

    $sql = sprintf($sql,
      T('facture'),
      T('adherent'),
      implode(',', $statuses),
      Facture::FLAG_RAPPEL_3,
      Facture::FLAG_RAPPEL_RESILIATED
    );

    $facture_list = Facture::collect(array('sql' => $sql))->asHash('adherent_id', 'facture_list');
    $facture_list = array_map(function($set) {
      return explode(',', $set);
    }, $facture_list);

    return $facture_list;
  }

  public static function getContentsByAdherent($args=array()) {
    $facture_list = self::getFactureSetByAdherentToBeRecovery($args);

    foreach ($facture_list as $adherent_id => $facture_set) {
      $adherent = Adherent::getInstance($adherent_id);

      $filters = array('|IN|id' => $facture_set);
      $factures = Facture::collect(array('filters' => $filters,
                                         'order'   => array('start_at' => 'DESC')));

      $data_address = $factures->first()->data_address;
      $address = $data_address['address'] . '<br />';
      $zipcode = $data_address['zipcode'];
      $city = $data_address['city'];
      $company = $data_address['company'];


      setlocale(LC_TIME, "fr_FR");
      $args = array(
        'address'               => $address,
        'zipcode'               => $zipcode,
        'city'                  => $city,
        'company'               => $company,
        'date'                  => utf8_encode(strftime('%d %B %Y')),
        'siret'                 => $adherent->siret .' / ' . $adherent->company,
        'facture_list'          => '',
        'montant_facture_total' => 0
      );

      $args['facture_list'] = array();
      foreach ($factures as $facture) {
        $price_ttc = round($facture->price_ttc, 2);

        $args['facture_list'][] = array(
          'id'      => $facture->getId(),
          'date'    => date('d/m/Y', strtotime($facture->getMeta('created_at'))),
          'siret'   => $facture->data_adherent['siret'],
          'montant' => sprintf('%.2f', $price_ttc)
        );

        $args['montant_facture_total'] += $price_ttc;
      }

      $args['montant_facture_total'] = sprintf('%.2f', $args['montant_facture_total']);
      $args['facture_list'] = self::renderFactureList($args['facture_list'], $args['montant_facture_total']);

      $letter_templates[$adherent_id] = l('snippet:template_mail_recovery_pdf', $args);
    }

    return $letter_templates;
  }

  public static function generateRecoveryPdf($args=array()) {
    if (!Folder::exists(Facture::PATH_RECOVERY_PDF)) {
      Folder::create(Facture::PATH_RECOVERY_PDF, true);
    }

    $path_target  = sprintf('%s/%s-recouvrement.pdf',
      Facture::PATH_RECOVERY_PDF,
      date('Y-m-d')
    );
    $path_source  = str_replace('.pdf', '.html', $path_target);

    $req = S('req');
    if (!$req->isAuthenticated()) {
      $user = User::getInstance(2); // Connect as hmichel
    }
    else {
      $user->$req->getUser();
    }

    $content = H::get('/middle/ntd/facture.recovery.print/-/credential/' . $user->getCredential() . '/from/' . ($args['from'] ?: 0) . '/to/' . ($args['to'] ?: 0));

    $fp = fopen($path_source, 'w');
    fwrite($fp, $content);
    fclose($fp);

    if (P('auth.login') && P('auth.password')) {
      $username = P('auth.login');
      $password = P('auth.password');
    } else {
      $username = null;
      $password = null;
    }

    $options = array('--username'       => $username,
                     '--password'       => $password,
                     '--page-size'      => 'A4',
                     '--margin-top'     => '40',
                     '--margin-left'    => '25',
                     '--margin-right'   => '25',
                     '--margin-bottom ' => '25',
                     '--header-spacing' => '0',
                     '--footer-spacing' => '0',
                     '--outline-depth'  => '0');

    system('/bin/bash -c "export DISPLAY=127.0.0.1:123; /etc/kernix/bin/wkhtmltopdf '.NetDeclaration::asShellParams($options).' \''.$path_source.'\' \''.$path_target.'\'"');
    unlink($path_source);

    // Shell::chownDir(dirname($path_target));
    $apache = System::getApacheUser();
    $apache = $apache['name'];
    if (strlen($apache) < 2) {
      S('log')->error('invalid user ['.$apache.']', __METHOD__);
      throw new Exception('invalid user ['.$apache.']');
    }
    $cmd = 'chown -R '.$apache.':'.$apache.' '.$path_target;
    system($cmd);

    return $path_target;
  }


  protected static function renderFactureList($facture_list, $montant_facture_total) {
    $str_factures = '';
    foreach ($facture_list as $facture) {
      $str_factures .= '<tr>'
                      .'  <td>' . $facture['id'] . '</td>'
                      .'  <td>' . $facture['date'] . '</td>'
                      .'  <td>' . $facture['siret'] . '</td>'
                      .'  <td class="facture-total">' . $facture['montant'] . ' &euro;</td>'
                      .'</tr>';
    }

    $str = '<table class="facture-list">'
          .'  <thead>'
          .'    <tr>'
          .'      <th>N° Facture</th>'
          .'      <th>Date</th>'
          .'      <th>Siret</th>'
          .'      <th>Montant dû TTC</th>'
          .'    </tr>'
          .'  </thead>'
          .'  <tbody>'
          .     $str_factures
          .'  </tbody>'
          .'  <tfoot>'
          .'    <tr>'
          .'      <td colspan="3" class="facture-total">Total</td>'
          .'      <td class="facture-total">'.$montant_facture_total.' &euro;</td>'
          .'    </tr>'
          .'  </tfoot>'
          .'</table>';

    return $str;
  }
}
