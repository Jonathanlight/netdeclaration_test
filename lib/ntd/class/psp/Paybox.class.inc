<?php

/***
Numéro Carte Bleue de Test : 1111222233334444 (+ utiliser date valide et bien mettre 3 chiffres)
LANG = FRA, GBR, ESP, ITA, DEU, NLD, SWE
array('site' => '1999888',
'rang' => '99',
'identifiant' => '2')
 ***/

class Paybox {

    private static function config() {
        $config = P('shop.psp');
        $config = $config['paybox'];
        return $config;
    }

    public static function request($payment) {

        $amount = $payment->amount;
        $method = $payment->getMethod();
        $facture = $payment->getFactures()->first();
        $options = String::asHash($method->options);

        $config = self::config();
        $params = $config['params'];

        $user = $facture->getAdherent()->getUser();

        $amount = number_format($amount, 2, '.', '');
        $amount = (int) ($amount * 10 * 10);

        $h = array();

        $response_url = $config['payment.response'] ?: '/middle/payment.response';
        $cancel_url = $config['payment.cancel'] ?: '/middle/payment.cancel';
        $args = array('item' => $facture->getKey());

        $h['site']        = $params['site'];
        $h['rang']        = $params['rang'];
        $h['identifiant'] = $params['identifiant'];
        //$h['mode']        = 4;
        $h['total']       = $amount;
        $h['devise']      = 978;
        $h['cmd']         = $facture->getId(). 'x' . $payment->getId();
        $h['lang']        = self::locale2lang($user->locale);
        $h['porteur']     = $user->email;
        $h['retour']      = 'pbxm:M;pbxr:R;pbxa:A;pbxt:T;pbxb:B;pbxp:P;pbxc:C;pbxs:S;pbxe:E;pbxf:F;pbxi:I';
        $h['effectue']    = H::url($response_url, $args);
        $h['refuse']      = H::url($cancel_url, $args);
        $h['annule']      = H::url($cancel_url, $args);
        //$h['txt']         = '';
        //$h['wait']        = 0;
        //$h['boutpi']      = 'nul';
        //$h['output']      = 'C';
        $h['3ds']         = 'N';
        $h['repondre_a']  = H::url('/ntd/paiement.callback/-/psp/paybox');

        if ($options['features'] === 'direct+') {
            $h['retour'] .= ';pbxu:U';
        }

        if ($options['iframe'] === true) {
            if ($config['mode'] === 'test') {
                $url = 'https://preprod-tpeweb.paybox.com/cgi/MYframepagepaiement_ip.cgi';
            }
            else {
                $url = 'https://tpeweb.paybox.com/cgi/MYframepagepaiement_ip.cgi';
                if (!self::isServerOnline('tpeweb.paybox.com')) {
                    $url = 'https://tpeweb1.paybox.com/cgi/MYframepagepaiement_ip.cgi';
                }
            }
        }
        else {
            if ($config['mode'] === 'test') {
                $url = 'https://preprod-tpeweb.paybox.com/cgi/MYchoix_pagepaiement.cgi';
            }
            else {
                $url = 'https://tpeweb.paybox.com/cgi/MYchoix_pagepaiement.cgi';
                if (!self::isServerOnline('tpeweb.paybox.com')) {
                    $url = 'https://tpeweb1.paybox.com/cgi/MYchoix_pagepaiement.cgi';
                }
            }
        }

        if (isset($options['typepaiement'])) {
            $h['typepaiement'] = $options['typepaiement'];
        }

        if (isset($options['typecarte'])) {
            $h['typecarte'] = $options['typecarte'];
        }

        foreach (array('effectue', 'refuse', 'annule') as $key) {
            if (!isset($options[$key])) continue ;
            $h[$key] = $options[$key];
        }

        if ($options['nbpaie'] > 1) {
            $nbpaie = (int) $options['nbpaie'];
            $prelevement = floor($amount / $nbpaie);
            $h['total'] = $prelevement + ($amount % $nbpaie);
            $h['datevalmax'] = date('ym', strtotime('+'.($nbpaie - 1).' months'));
            $h['cmd'] .= 'x';
            $h['cmd'] .= 'IBS_2MONT'.sprintf('%010s', $prelevement);
            $h['cmd'] .= 'IBS_NBPAIE'.sprintf('%02s', ($nbpaie - 1));
            $h['cmd'] .= 'IBS_FREQ'.'01'.'IBS_QUAND'.'00';
            $h['refabonne'] = $facture->getId();
        }

        $h['time'] = date('c');
        $h['hash'] = 'SHA512';
        $keys = array_keys($h);
        $parts = array();
        foreach ($keys as $key) {
            $parts[] = 'PBX_'.strtoupper($key).'='.$h[$key];
        }
        $hmac = hash_hmac('sha512', join('&', $parts), pack('H*', $params['cle']));
        $keys[] = 'hmac';
        $h['hmac'] = strtoupper($hmac);
        $form = array();
        $form[] = '<form method="POST" action="'.$url.'">';
        foreach ($keys as $key) {
            $form[] = '<input type="hidden" name="PBX_'.strtoupper($key).'" value="'.$h[$key].'">';
        }
        $form[] = '<input id="paybox-button" type="submit" value="accéder au paiement" class="button" style="display:none;">'."\n";
        $form[] = '</form>';
        $html = join("\n", $form);
        $html .= '<img src="/app/core/pix/empty.gif" onload="$(\'paybox-button\').form.submit()" />';

        if ($config['trace'] === true) {
            S('log')->debug($html);
        }

        return $html;
    }

    private static function isServerOnline($server) {
        $doc = new DOMDocument();
        $doc->loadHTMLFile('https://'.$server.'/load.html');
        $elt = $doc->getElementById('server_status');
        $status = '';
        if ($elt) {
            $status = $elt->textContent;
        }
        return $status == 'OK';
    }

    public static function callback() {
        $req = S('req');

        $regex = str_replace('.', '\.', join('|', self::$range));
        $address = $req->getClient('address');
        if (!preg_match('/^('.$regex.')/', $address)) {
            throw new Exception('bad source IP ['.$address.']');
        }

        if (strlen($req->pbxr) < 3) {
            throw new Exception('no pbxr ('.$req->pbxr.')');
        }

        list ($facture_id, $payment_id, ) = explode('x', $req->pbxr);

        $error = (int) $req->pbxe;

        /*if ($req->hasAttribute('ETAT_PBX') &&
            $req->ETAT_PBX === 'PBX_RECONDUCTION') {
          $amount = $req->getAttribute('pbxm') / 100;
          if (($error == 0 || $error == 100) && $req->hasAttribute('pbxa', true)) {
            $status = Installment::STATUS_SUCCESS;
          }
          else {
            $status = Installment::STATUS_ERROR;
          }
          $code = $req->pbxs;
          // construire datas
          // ajout installment
          return ;
        }*/

        $facture = Facture::getInstance((int) $facture_id);
        if ($facture->status == Facture::STATUS_PAYE) {
            throw new Exception('facture  ('.$facture->getId().') already paid [status='.$facture->status.']');
        }
        if ($facture->status != Facture::STATUS_PENDING) {
            throw new Exception('facture ('.$facture->getId().') bad status [status='.$facture->status.']');
        }
        $payment = Payment::getInstance((int) $payment_id);
        if ($payment->isReceived()) {
            throw new Exception('payment ('.$payment->getId().') already received [order='.$facture->getId().']');
        }

        $vars = array('s' => 'num transaction',
            't' => 'id transaction',
            'a' => 'autorisation',
            'p' => 'type paiement',
            'c' => 'carte',
            'f' => '3D secure',
            'm' => 'montant',
            'e' => 'erreur',
            'i' => 'pays',
            'b' => 'num abo');

        if (($error == 0 || $error == 100) && $req->hasAttribute('pbxa', true)) {
            $description = '';
            foreach ($vars as $letter => $label) {
                $value = $req->getAttribute('pbx'.$letter);
                if ($letter === 'm') {
                    $value = substr($value, 0, strlen($value) - 2).'.'.substr($value, -2);
                }
                $description .= $label.'='.$value."\n";
            }
            $status = Payment::STATUS_RECEIVED;
        }
        else {
            $str = self::$errors[$req->pbxe];
            if ($error > 100) {
                $str = 'paiement refusé par le centre d’autorisation';
            }
            $status = Payment::STATUS_ERROR;
            $description = '('.$req->pbxe.') '.$str;
        }
        $attrs = array('code' => $req->pbxs,
            'status' => $status,
            'description' => $description,
            'datas' => $req->getAttributes(),
            'subscriber' => $req->pbxb,
            'paid_at' => Date::now());
        $payment->commit($attrs);
        $payment->sendLetter();
        $method = $payment->getMethod();
        //$facture->setStatus(Facture::STATUS_PAYE);
    }

    private static function locale2lang($locale) {
        $locale = (int) $locale;
        $lang = self::$langs[$locale];
        if (empty($lang)) {
            $lang = 'GBR';
        }
        return $lang;
    }

    public static function response() {}

    private static $langs = array(I18N::LOCALE_DE => 'DEU',
        I18N::LOCALE_EN => 'GBR',
        I18N::LOCALE_ES => 'ESP',
        I18N::LOCALE_FR => 'FRA',
        I18N::LOCALE_IT => 'ITA');

    private static $range = array('195.101.99', '194.50.38', '194.2.160', '194.2.122.158',
        '62.39.109', '192.168.0.102', '195.25.7.166',
        '194.2.122.158', '194.2.122.190', '195.25.7.166', '195.25.67.22');

    private static $errors = array(1  => 'échec connexion au centre d’autorisation',
        3  => 'erreur paybox',
        4  => 'numéro de porteur ou cryptogramme visuel invalide',
        6  => 'accès refusé ou site/rang/identifiant incorrect',
        8  => 'date de fin de validité incorrecte',
        9  => 'erreur vérification comportementale',
        10 => 'devise inconnue',
        11 => 'montant incorrect',
        15 => 'paiement déjà effectué',
        16 => 'abonné déjà existant',
        21 => 'carte non autorisée',
        29 => 'carte non conforme',
        30 => 'temps d’attente dépasé',
        31 => 'réservé',
        32 => 'réservé',
        33 => 'pays non autorisé');
}
