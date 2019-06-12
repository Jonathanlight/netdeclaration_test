<?php

try {

    //@TODO à supprimer : fix du 13/04/2018
  $factures_exclude = array(53529,53530,53535,53537,53549,53551,53553,53556,53558,53567,53609,53613,53644,53654,53655,53657,
      53670,53675,53691,53700,53701,53741,53742,53743,53744,53762,53769,53770,53771,53772,53773,53774,53775,53790,53811,
      53819,53836,53852,53856,53857,53862,53883,53899,53902,53912,53913,53914,53925,53930,53931,53932,53940,53942,53975,
      53990,53991,53992,53997,54001,54002,54003,54004,54005,54006,54007,54009,54023,54024,54036,54047,54054,54055,54058,
      54063,54067,54068,54072,54074,54075,54077,54081,54089,54096,54097,54100,54101,54104,54106,54115,54116,54122,54123,
      54124,54125,54126,54135,54137,54140,54141,54142,54145,54147,54148,54153,54154,54155,54157,54158,54166,54167,54168,
      54171,54175,54176,54179,54182,54186,54188,54207,54210,54214,54215,54218,54219,54228,54237,54241,54242,54243,54244,
      54245,54248,54249,54255,54265,54268,54270,54279,54281,54287,54294,54296,54297,54298,54302,54306,54308,54312,54313,
      54314,54317,54321,54325,54327,54328,54329,54330,54331,54335,54344,54349,54350,54351,54353,54400,54403,54405,54407,
      54408,54411,54412,54418,54420,54421,54422,54423,54424,54427,54429,54442,54443,54448,54452,54453,54454,54455,54460,
      54461,54462,54464,54465,54466,54467,54470,54473,54476,54477,54478,54479,54481,54482,54484,54486,54502,54504,54507,
      54516,54519,54521,54522,54526,54527,54528,54530,54532,54533,54534,54535,54537,54541,54542,54552,54554,54570,54572,
      54574,54575,54576,54584,54594,54597,54601,54611,54614,54615,54616,54617,54625,54626,54627,54629,54631,54633,54634,
      54643,54644,54645,54650,54655,54656,54658,54666,54668,54669,54670,54671,54689,54690,54692,54694,54695,54696,54698,
      54699,54702,54703,54704,54705,54706,54707,54708,54710,54723,54726,54731,54732,54733,54735,54736,54738,54739,54741,
      54743,54745,54746,54747,54748,54749,54751,54752,54753,54756,54757,54758,54759,54762,54763,54765,54766,54767,54768,
      54780,54781,54782,54784,54785,54786,54787,54788,54791,54801,54812,54814,54815,54820,54824,54826,54828,54829,54830,
      54831,54833,54839,54859,54866,54867,54870,54874,54875,54876,54877,54878,54880,54882,54883,54884,54885,54887,54899,
      54901,54906,54907,54908,54910,54911,54913,54914,54915,54919,54920,54921,54922,54924,54930,54931,54932,54935,54936,
      54937,54939,54942,54943,54950,54952,54953,54954,54956,54958,54961,54964,54965,54966,54968,54974,54975,54978,54980,
      54981,54982,54983,54986,54987,54988,54989,54990,54991,54992,54993,54994,54995,55004,55006,55007,55014,55015,55017,
      55019,55021,55025,55026,55027,55028,55030,55032,55033,55034,55035,55036,55047,55049,55051,55052,55054,55055,55056,
      55058,55059,55060,55061,55062,55066,55067,55068,55069,55070,55071,55092,55103,55105,55106,55107,55108,55109,55110,
      55111,55113,55116,55118,55119,55120,55121,55123,55124,55125,55127,55129,55130,55131,55132,55133,55134,55135,55137,
      55138,55140,55141,55149,55150,55152,55155,55157,55158,55159,55162,55163,55166,55168,55169,55170,55172,55189,55192,
      55193,55194,55195,55200,55201,55202,55203,55204,55205,55206,55207,55209,55211,55212,55214,55215,55217,55218,55219,
      55223,55224,55225,55227,55232,55235,55236,55240,55244,55245,55249,55256,55257,55259,55261,55262,55263,55264,55265,
      55267,55268,55269,55271,55274,55275,55276,55279);

  $echeance = '-30 days';

  $adherent_types = array(
    'Entreprise' => array(
      'types' => array(Adherent::TYPE_ENTREPRISE, Adherent::TYPE_PRO_SANTE),
      'rappels' => array(
        Facture::FLAG_RAPPEL_1 => array(
          'start_at' => date('Y-m-d', strtotime($echeance . ' + 10 days')),
          'letter'   => 'facture.check.payment.day.20',
        ),
        Facture::FLAG_RAPPEL_2 => array(
          'start_at' => date('Y-m-d', strtotime($echeance)),
          'letter'   => 'facture.check.payment.day.30',
        ),
        Facture::FLAG_RAPPEL_3 => array(
          'start_at' => date('Y-m-d', strtotime($echeance . ' - 15 days')),
          'letter'   => 'facture.check.payment.day.40',
        ),
        Facture::FLAG_RAPPEL_RESILIATED => array(
          'start_at' => date('Y-m-d', strtotime($echeance . ' - 23 days')),
          'letter'   => null,
        )
      ),
    ),

    'International' => array(
      'types' => array(Adherent::TYPE_INTERNATIONAL),
      'rappels' => array(
        Facture::FLAG_RAPPEL_1 => array(
          'start_at' => date('Y-m-d', strtotime('+ 10 days')),
          'letter'   => 'facture.check.payment.day.20',
        ),
        Facture::FLAG_RAPPEL_2 => array(
          'start_at' => date('Y-m-d'),
          'letter'   => 'facture.check.payment.day.30',
        ),
        Facture::FLAG_RAPPEL_3 => array(
          'start_at' => date('Y-m-d', strtotime('- 15 days')),
          'letter'   => 'facture.check.payment.day.40',
        ),
        Facture::FLAG_RAPPEL_RESILIATED => array(
          'start_at' => date('Y-m-d', strtotime('- 23 days')),
          'letter'   => null,
        )
      ),
    ),

    'CEC' => array(
      'types' => array(Adherent::TYPE_CEC),
      'rappels' => array(
        Facture::FLAG_RAPPEL_1 => array(
          'start_at' => date('Y-m-d', strtotime($echeance . ' + 10 days')),
          'letter'   => 'facture.check.payment.day.20',
        ),
        Facture::FLAG_RAPPEL_2 => array(
          'start_at' => date('Y-m-d', strtotime($echeance)),
          'letter'   => 'facture.check.payment.day.30',
        ),
        Facture::FLAG_RAPPEL_3 => array(
          'start_at' => date('Y-m-d', strtotime($echeance . ' - 15 days')),
          'letter'   => 'facture.check.payment.day.40',
        ),
        Facture::FLAG_RAPPEL_RESILIATED => array(
          'start_at' => date('Y-m-d', strtotime($echeance . ' - 23 days')),
          'letter'   => null,
        )
      ),
    ),

    'OGA' => array(
      'types' => array(Adherent::TYPE_OGA),
      'rappels' => array(
        Facture::FLAG_RAPPEL_1 => array(
          'start_at' => date('Y-m-d', strtotime(' - 20 days')),
          'letter'   => 'facture.check.payment.day.20',
        ),
        Facture::FLAG_RAPPEL_2 => array(
          'start_at' => date('Y-m-d', strtotime(' - 30 days')),
          'letter'   => 'facture.check.payment.day.30',
        ),
        Facture::FLAG_RAPPEL_3 => array(
          'start_at' => date('Y-m-d', strtotime(' - 40 days')),
          'letter'   => 'facture.check.payment.day.40',
        ),
        Facture::FLAG_RAPPEL_RESILIATED => array(
          'start_at' => date('Y-m-d', strtotime(' - 48 days')),
          'letter'   => null,
        )
      ),
    ),
  );

  foreach ($adherent_types as $_type => $adherent_type) {

    foreach ($adherent_type['rappels'] as $flag => $rappel) {
      if ($flag != Facture::FLAG_RAPPEL_RESILIATED) {
        $opts = array(
          'include' => array('adherent'),
          'metas' => array('created_at'),
          'filters' => array(
            '|!IN|' . T('facture') . '.id' => $factures_exclude,
            '|IN|' . T('adherent') . '.type' => $adherent_type['types'],
            '|%%|md.created_at' => $rappel['start_at'],
            '|!&|flags' => $flag
          )
        );

        $factures = Facture::getUnpaiedFactures($opts);
        foreach ($factures as $facture) {
            $facture->sendLetter($rappel['letter']);
            $facture->setFlag($flag);
        }
      }
      else {
        $opts = array(
          'include' => array('adherent'),
            'metas' => array('created_at'),
            'filters' => array(
            '|!IN|' . T('facture') . '.id' => $factures_exclude,
            '|IN|' . T('adherent') . '.type' => $adherent_type['types'],
            '|<=|md.created_at' => $rappel['start_at'] . ' 23:59:59',
            '|>|md.created_at' => Date::DATE_NULL,
            '|!&|flags' => $flag
          )
        );

        $factures = Facture::getUnpaiedFactures($opts);

        if ($factures->count() > 0) {
          $souscription_filters = $factures->getFilters();

          unset($souscription_filters['|IN|' . T('adherent') . '.type']);
          unset($souscription_filters['|<=|md.created_at']);
          unset($souscription_filters['|>|md.created_at']);

          $souscription_filters['|!=|' . T('souscription') . '.status'] = Souscription::STATUS_CANCELLED;
          $souscription_filters['|<=|' . T('souscription'). '.start_at'] = $rappel['start_at'] . ' 23:59:59';
          $souscription_filters['|>|' . T('souscription'). '.start_at'] = Date::DATE_NULL;

          $souscriptions = Souscription::collect(array('include' => array('facture'),
                                                       'filters' => $souscription_filters));

          $factures_filters = $factures->getFilters();
          $factures_filters['is_renew_auto'] = 0;
          $factures->setFilters($factures_filters);
          $csv = CsvWriter::getInstance(array('fd' => File::getInstance('doc/log/factures.cancels.' . String::urlify(Date::now()) . '.csv', 'w+'),
                                              'encoding' => 'UTF-8',
                                              'columns' => array('facture_id',
                                                                 'facture_status',
                                                                 'facture_start_at',
                                                                 'adherent_id')));
          foreach ($factures as $facture) {
            $csv->append(array('facture_id' => $facture->id,
                               'facture_status' => Facture::$statuses[$souscription->facture_status],
                               'facture_start_at' => $souscription->facture_start_at,
                               'adherent_id' => $souscription->facture_adherent_id));
          }

          $csv = CsvWriter::getInstance(array('fd' => File::getInstance('doc/log/souscription.cancels.' . String::urlify(Date::now()) . '.csv', 'w+'),
                                              'encoding' => 'UTF-8',
                                              'columns' => array('facture_id',
                                                                 'souscription_id',
                                                                 'facture_status',
                                                                 'souscription_status',
                                                                 'start_at',
                                                                 'adherent_id')));
          foreach ($souscriptions as $souscription) {
            if (in_array($souscription->getAdherent()->type, $adherent_type['types'])) {
              $csv->append(array('facture_id' => $souscription->facture_id,
                                 'souscription_id' => $souscription->id,
                                 'facture_status' => Facture::$statuses[$souscription->facture_status],
                                 'souscription_status' => Souscription::$export_statuses[$souscription->status],
                                 'facture_start_at' => $souscription->facture_start_at,
                                 'adherent_id' => $souscription->facture_adherent_id));
              $souscription->setAttribute('status', Souscription::STATUS_CANCELLED);
              $souscription->setFlag(Souscription::FLAG_CANCELLED_FACTURE_NON_PAYE);
            }
          }
        }
      }

    }
  }

  print 'Terminé !';

}
catch (Exception $e) {
  $err->add($e);
}
