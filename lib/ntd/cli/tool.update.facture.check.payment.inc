<?php

try {

  $echeance = ' + 30 days';
  $today = time();

  $adherent_types = array(
    'Entreprise' => array(
      'types' => array(Adherent::TYPE_ENTREPRISE, Adherent::TYPE_PRO_SANTE),
      'rappels' => array(
        Facture::FLAG_RAPPEL_1 => array(
          'start_at' => ' - 10 days',
          'letter'   => 'facture.check.payment.day.20',
        ),
        Facture::FLAG_RAPPEL_2 => array(
          'start_at' => '',
          'letter'   => 'facture.check.payment.day.30',
        ),
        Facture::FLAG_RAPPEL_3 => array(
          'start_at' => ' + 15 days',
          'letter'   => 'facture.check.payment.day.40',
        ),
        Facture::FLAG_RAPPEL_RESILIATED => array(
          'start_at' => ' + 23 days',
          'letter'   => null,
        )
      ),
    ),

    'CEC' => array(
      'types' => array(Adherent::TYPE_CEC),
      'rappels' => array(
        Facture::FLAG_RAPPEL_1 => array(
          'start_at' => ' - 10 days',
          'letter'   => 'facture.check.payment.day.20',
        ),
        Facture::FLAG_RAPPEL_2 => array(
          'start_at' => '',
          'letter'   => 'facture.check.payment.day.30',
        ),
        Facture::FLAG_RAPPEL_3 => array(
          'start_at' => ' + 15 days',
          'letter'   => 'facture.check.payment.day.40',
        ),
        Facture::FLAG_RAPPEL_RESILIATED => array(
          'start_at' => ' + 23 days',
          'letter'   => null,
        )
      ),
    ),

    'OGA' => array(
      'types' => array(Adherent::TYPE_OGA),
      'rappels' => array(
        Facture::FLAG_RAPPEL_1 => array(
          'start_at' => ' + 20 days',
          'letter'   => 'facture.check.payment.day.20',
        ),
        Facture::FLAG_RAPPEL_2 => array(
          'start_at' => ' + 30 days',
          'letter'   => 'facture.check.payment.day.30',
        ),
        Facture::FLAG_RAPPEL_3 => array(
          'start_at' => ' + 40 days',
          'letter'   => 'facture.check.payment.day.40',
        ),
        Facture::FLAG_RAPPEL_RESILIATED => array(
          'start_at' => ' + 48 days',
          'letter'   => null,
        )
      ),
    ),
  );


  $filters = array('|IN|id' => array(
    49111, 49171, 49172, 49173, 49174, 49175, 49176, 49177, 49178, 49180, 49185, 49186, 49188, 49208, 49211, 49219, 49222, 49262, 49267, 49269,
    49272, 49273, 49279, 49291, 49292, 49293, 49294, 49295, 49299, 49302, 49317, 49318, 49340, 49342, 49349, 49356, 49359, 49372, 49373, 49374,
    49375, 49377, 49379, 49381, 49384, 49386, 49414, 49415, 49416, 49417, 49422, 49426, 49466, 49469, 49470, 49471, 49472, 49473, 49474, 49475,
    49504, 49509, 49526, 49528, 49532, 49533, 49537, 49554, 49555, 49560, 49563, 49564, 49573, 49575, 49577, 49578, 49623, 49639, 49640, 49641,
    49645, 49646, 49680, 49686, 49688, 49689, 49690, 49721, 49722, 49723, 49728, 49731, 49732, 49734, 49735, 49749, 49751, 49798, 49801, 49803,
    49804, 49805, 49807, 49808, 49809, 49810, 49828, 49829, 49830, 49831, 49833, 49836, 49837, 49877, 49878, 49883, 49884, 49929, 49935, 49937,
    49938, 49941, 49942, 49945, 49966, 49967, 49969, 49978, 49979, 49980, 49981, 49983, 50015, 50020, 50022, 50039, 50043, 50044, 50045, 50077,
    50078, 50079, 50082, 50092, 50093, 50101, 50105, 50107, 50108, 50109, 50110, 50111, 50113, 50116, 50118, 50121, 50123, 50124, 50125, 50126,
    50128, 50130, 50131, 50132, 50133, 50152, 50153, 50154, 50155, 50159, 50160, 50161, 50170, 50171, 50173, 50174, 50175, 50176, 50188, 50198,
    50201, 50202, 50203, 50205, 50206, 50211, 50223, 50224, 50228, 50233, 50234, 50240, 50241, 50242, 50254, 50255, 50256, 50257, 50258, 50261,
    50262, 50263, 50264, 50276, 50277, 50279, 50280, 50281, 50282, 50283, 50285, 50286, 50288, 50305, 50307, 50308, 50309, 50319, 50321, 50323,
    50325, 50330, 50332, 50333, 50334, 50335, 50337, 50338, 50339, 50340, 50341, 50342, 50343, 50344, 50347, 50348, 50349, 50351, 50354, 50355,
    50356, 50357, 50365, 50366, 50367, 50369, 50370, 50371, 50372, 50373, 50374, 50378, 50379, 50380, 50386, 50388, 50390, 50391, 50392, 50394,
    50395, 50402, 50408, 50409, 50416, 50418, 50419, 50420, 50440, 50441, 50443, 50444, 50445, 50446, 50448, 50450, 50452, 50453, 50454, 50456,
    50457, 50458, 50459, 50460, 50461, 50462, 50463, 50464, 50465, 50466, 50467, 50479, 50482, 50484, 50487, 50490, 50491, 50496, 50499, 50501,
    50502, 50503, 50505, 50506, 50507, 50508, 50509, 50510, 50511, 50512, 50513, 50514, 50515, 50522, 50523, 50526, 50527, 50528, 50529, 50530,
    50531, 50532, 50534, 50535, 50536, 50537, 50538, 50543, 50546, 50548, 50549, 50550, 50551, 50552, 50555, 50556, 50562, 50563, 50564, 50570,
    50572, 50574, 50578, 50580, 50582, 50583, 50594, 50600, 50601, 50612, 50613, 50614, 50615, 50617, 50618, 50625, 50626, 50627, 50628, 50637,
    50640, 50641, 50642, 50643, 50644, 50880, 50881, 50882, 50883, 50884, 50886, 50887, 50888, 50889, 50898, 50899, 50900, 50901, 50902, 50904,
    50905, 50906, 50907, 50908, 50909, 50910, 50917, 50918, 50919, 50920, 50921, 50922, 50923, 50924, 50925, 50926, 50927, 50936, 50937, 50938,
    50939, 50940, 50941, 50947, 50949, 50950, 50951, 50952, 50953, 50954, 50955, 50956, 50957, 50958, 50959, 50960, 50961, 50962, 50963, 50964,
    50965, 50967, 50968, 50969, 50970, 50971, 50978, 50979, 50980, 50981, 50982, 50983, 50877
  ));

  $factures = Facture::collect(array('filters' => $filters));
  // echo count($factures) . PHP_EOL;


  echo 'facture_id;creation;échéance;flag;date;flaguée?;dépassée?' . PHP_EOL;

  foreach ($factures as $facture) {
    $adherent = $facture->getAdherent();

    if (in_array($adherent->type, array(Adherent::TYPE_ENTREPRISE, Adherent::TYPE_PRO_SANTE))) {
      $init_start_time = $facture->start_at;
    }
    else {
      $init_start_time = $facture->start_at . ' ' . $echeance;
    }

    foreach ($adherent_types as $_type => $types) {
      if (in_array($adherent->type, $types['types'])) {

        foreach ($types['rappels'] as $flag => $rappel) {
          $start_time = strtotime($init_start_time . ' ' . $rappel['start_at']);
          $start_at = date('Y-m-d', $start_time);

          $is_flag = $facture->hasFlag($flag);
          $is_outdated = $start_time < $today;

          echo sprintf('%d;%s;%s;%s;%s;%s;%s',
            $facture->getId(),
            $facture->start_at,
            date('Y-m-d', strtotime($init_start_time)),
            Facture::$flags[$flag],
            $start_at,
            $is_flag ? 'Oui' : 'Non',
            $is_outdated ? 'Oui' : 'Non'
          ) . PHP_EOL;

          if (!$is_flag && $is_outdated) {
            if (!empty($rappel['letter'])) {
              $facture->sendLetter($rappel['letter']);
            }
            $facture->setFlag($flag);

            // echo sprintf('Facture #%d flagé %s',
            //   $facture->getId(),
            //   Facture::$flags[$flag]
            // ) . PHP_EOL;

            if ($flag == Facture::FLAG_RAPPEL_RESILIATED) {
              $souscription_filters = array(
                '' . T('facture') . '.id'              => $facture->getId(),
                '|!=|' . T('souscription') . '.status' => Souscription::STATUS_CANCELLED
              );
              $souscriptions = Souscription::collect(array('include' => 'facture',
                                                           'filters' => $souscription_filters));

              foreach ($souscriptions as $souscription) {
                // echo sprintf('Souscription #%d annulée',
                //   $souscription->getId()
                // ) . PHP_EOL;
                $souscription->setAttribute('status', Souscription::STATUS_CANCELLED);
                $souscription->setFlag(Souscription::FLAG_CANCELLED_FACTURE_NON_PAYE);
              }
            }
          }

        }

      }
    }
  }

} catch (Exception $e) {
  $err->add($e);
}
