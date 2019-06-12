asserts = {

  functions: {},
  assertsRunning: {},

  run: function(assertCode) {
    var assert = this.functions[assertCode];
    if (typeof assert !== "function") {
      //console.log('bad assertCode');
      return false;
    }

    if (typeof this.assertsRunning[assertCode] !== "undefined") {
      return false;
    }
    this.assertsRunning[assertCode] = 1;
    setTimeout(function() {
      try {
        assert(
          this.core.$elt.bind(this.core),
          this.core.$assert.bind(this.core),
          this.core.$controls,
          this.core.$isServi.bind(this.core),
          this.core.$float.bind(this.core),
          this.core.$value.bind(this.core),
          this.core.$readonly.bind(this.core),
          this.core.$isSiren.bind(this.core),
          this.core.$XOR.bind(this.core),
          this.core.$addition.bind(this.core),
          this.core.$soustraction.bind(this.core),
          this.core.$percent.bind(this.core),
          this.core.$decimalAdjust.bind(this.core)
        );
      }
      catch (error) {
        // console.log(error);
      }
      delete this.assertsRunning[assertCode];

    }.bind(this), 500);

    return true;
  },

  core: {
    $elt: function(fieldName, occurence) {
      var elt;
      if (occurence) {
        elt = occurence.select('.'+fieldName)[0];
      } else {
        elt = $(fieldName);
      }
      if (!elt) {
        // console.error(fieldName + ' not found');
      }
      return elt;
    },
    $value: function(elt, value) {
      elt = $(elt);
      if (typeof value == "undefined") {
        return elt.getValue();
      }
      if (elt.readAttribute('type') == 'checkbox') {
        elt.checked = value != '';
      } else {
        elt.setValue(value);
      }

    },
    $float: function(elt) {
      elt = $(elt);
      return parseFloat(this.$value(elt).replace(',', '.'));
    },
    $readonly: function(elt, bool) {
      if (bool) {
        elt.setAttribute('readonly', 'readonly');
        elt.addClassName('elt--readonly');
      }
      else {
        elt.removeAttribute('readonly');
        elt.removeClassName('elt--readonly');
      }
      return elt;
    },
    $isSiren: function (elt) {
      var $siren = elt.getValue().toString();
      var $matches = [];
      var $sum = 0;

      // Trim all ' ', '.', '-', '_' here if needed
      $siren = $siren.replace(/[^\w\s]/gi, '')
      if (!($matches = $siren.match(/^(\d)(\d)(\d)(\d)(\d)(\d)(\d)(\d)(\d)$/))) {
        return false;
      }

      $matches[2] *= 2;
      $matches[4] *= 2;
      $matches[6] *= 2;
      $matches[8] *= 2;

      for (var $i = 1; $i < $matches.length; $i++) {
        if ($matches[$i] > 9) {
          var $a = Number($matches[$i].toString().substr(0, 1));
          var $b = Number($matches[$i].toString().substr(1, 1));
          $matches[$i] = $a + $b;
        }
        $sum += Number($matches[$i]);
      }
      return ($sum % 10) == 0;
    },
    $isServi: function(elt) {
      // if (elt.disabled) {
      //   return false;
      // }
      if (elt.readAttribute('type') == 'checkbox') {
        return elt.checked;
      }
      else if (elt.readAttribute('type') == 'radio') {
        return elt.checked;
      }
      return (this.$value(elt)  != '-' &&
              (typeof this.$value(elt) == "string" && this.$value(elt).length > 0) && (!elt.disabled || (elt.disabled && this.$value(elt).length > 0)));
    },
    $resultField: function(elt) {
      elt.setAttribute('readonly', 'readonly');
      //elt.addClassName('result');
    },
    $XOR: function(a, b) {
      return ( a || b ) && !( a && b );
    },
    $addition: function($result) {
      var result = '';
      for (var i = 1; i < arguments.length; i++) {
        if (this.$float(arguments[i]) >= 0) {
          if (result === '') {
            result = 0;
          }
          result += this.$float(arguments[i]);
        }
      }
      if(typeof(result) == "number") {
        result = Math.round(result);
      }
      this.$value($result, result);
    },
    $soustraction: function($result, $value) {
      if (!(this.$float($value) >= 0)) {
        this.$value($result, '');
        return;
      }
      var result = this.$float($value);
      for (var i = 2; i < arguments.length; i++) {
        if (this.$float(arguments[i]) > 0) {
          result -= this.$float(arguments[i]);
        }
      }
      this.$value($result, Math.max(0, Math.round(result)));
    },
    $percent: function($result, $field, percent) {
      var result = '';
      if (this.$isServi($field) && this.$float($field) >= 0) {
        result = this.$float($field) * (percent / 100);
        result = Math.round(result);
      }
      this.$value($result, result);
    },
    /**
     * Fonction pour arrondir un nombre.
     * @see https://developer.mozilla.org/fr/docs/Web/JavaScript/Reference/Objets_globaux/Math/ceil (Arrondi décimal)
     * @param	{String}	type	Le type d'arrondi.
     * @param	{Number}	value	Le nombre à arrondir.
     * @param	{Integer}	exp		L'exposant (le logarithme en base 10 de la base pour l'arrondi).
     * @returns	{Number}			La valeur arrondie.
     */
    $decimalAdjust: function(type, value, exp) {
      // Si l'exposant vaut undefined ou zero...
      if (typeof exp === 'undefined' || +exp === 0) {
        return Math[type](value);
      }
      value = +value;
      exp = +exp;
      // Si value n'est pas un nombre
          // ou si l'exposant n'est pas entier
      if (isNaN(value) || !(typeof exp === 'number' && exp % 1 === 0)) {
        return NaN;
      }
      // Décalage
      value = value.toString().split('e');
      value = Math[type](+(value[0] + 'e' + (value[1] ? (+value[1] - exp) : -exp)));
      // Re "calage"
      value = value.toString().split('e');
      return +(value[0] + 'e' + (value[1] ? (+value[1] + exp) : exp));
    },
    $dicoContent: {
      'ou': '<span style="font-weight: bold">OU</span>',
      'obligatoire': '<span style="font-weight: bold">est obligatoire</span>',

      // kernix/clients/net_declaration/sources_client/tva/2015/code-erreur-2015
      'erreur_001': 'Partenaire EDI DGI "émetteur" invalide.',
      'erreur_002': 'Partenaire EDI DGI "donneur d\'ordre" invalide.',
      'erreur_004': 'Identification redevable absente.',
      'erreur_006': 'SIREN redevable non reconnu.',
      'erreur_007': 'Période déclarée absente.',
      'erreur_008': 'Formulaire inconnu ou invalide avec régime.',
      'erreur_010': 'Formulaire déclaratif absent.',
      'erreur_011': 'Formulaire principal absent ou invalide avec régime.',
      'erreur_012': 'Formulaires incompatibles dans un même dépôt.',
      'erreur_013': 'Vérifiez que l\'annexe 3310 A est présente.',
      'erreur_015': 'Code inconnu.',
      'erreur_016': 'Code en double',
      'erreur_017': 'Redevable non souscripteur au Télérèglement',
      'erreur_018': 'Montant télérèglement absent ou invalide dans TPn.',
      'erreur_020': 'CB télérèglement absent ou invalide dans TPn.',
      'erreur_025': 'Déclaration déposée hors du délai géré par la procédure TVA.',
      'erreur_041': 'Type de segment erroné .',
      'erreur_043': 'Code  dans  présent avec indice de répétition donnée et/ou formulaire erroné .',
      'erreur_046': 'Redevable non adhérent la procédure TVA. Filière EDI .',
      'erreur_047': 'Régime non géré dans la procédure TVA..',
      'erreur_048': 'Période déclarée invalide avec période déjà déposée (chevauchement).',
      'erreur_050': 'Le montant de la zone  du  ne peut être supérieur au total de la TVA brute due dont il constitue un des éléments.',
      'erreur_054': 'Un événement de type redressement judiciaire est inclus dans la période déclarée.',
      'erreur_060': 'Existence de régimes distincts sur la période déclarée.',
      'erreur_061': 'Le Flux remboursement n\'accepte aucun paiement. Les paiements doivent être transmis dans le flux déclaratif.',
      'erreur_062': 'la clef transmise pour le RIB est incohérente avec le code banque, le code guichet ou le numéro de compte.',
      'erreur_063': 'Couple (code banque ; code guichet) inexistant dans le fichier des implantations bancaires',
      'erreur_064': 'Absence de désignation du titulaire du compte',
      'erreur_065': 'Compte bancaire : code pays incorrecte ou invalide',
      'erreur_066': 'Compte bancaire : Clé IBAN invalide',
      'erreur_067': 'Compte bancaire : code BIC invalide (non appliqué)',
      'erreur_151': 'Absence de compte bancaire valide pour cette adhésion à Payer EDI TVA.',
      'erreur_152': 'Une des dates transmises est inexistante.',
      'erreur_153': 'Date cession/cessation déclarée incohérente avec date cession/cessation enregistrée au niveau de l’obligation fiscale. .',
      'erreur_154': 'Période déclarée incohérente avec date événement. .',
      'erreur_155': 'Dépôt non recevable : date dépôt antérieure à date de début de période déclarée.',
      'erreur_156': 'Erreur dans calcul ou report zone .',
      'erreur_157': 'Format donnée code  invalide dans formulaire',
      'erreur_158': 'Obligation fiscale TVA non trouvée pour le SIREN et la période déclarés.',
      'erreur_159': 'Obligation fiscale TVA non valide pour la période déclarée.',
      'erreur_160': 'Pas de service compétent à l’adresse fiscale du redevable.',
      'erreur_161': 'Période d’échéance de l’acompte absente pour le  formulaire principal déposé (3514)',
      'erreur_162': 'Période d’échéance de l’acompte non compatible avec le formulaire principal déposé (3514)',
      'erreur_163': 'Plus d’un événement déclaré parmi indicateur cession/cessation et date redressement judiciaire. .',
      'erreur_164': 'Plusieurs dépôts relatifs à la même obligation déclarative pour un même contribuable ont été transmis dans le même interchange. Les dépôts en double sont rejetés.',
      'erreur_165': 'Présence événement (date cession/cessation ou date redressement judiciaire) incompatible avec formulaire principal déposé (3514 ou 3525 bis). .',
      'erreur_166': 'Souscription Télépayer TVA NON valide à la date de dépôt.',
      'erreur_168': 'Date dépôt antérieure à date cession/cessation déclarée et/ou date cession/cessation enregistrée au niveau de l’obligation fiscale. .',
      'erreur_169': 'Format donnée code  invalide dans le formulaire',
      'erreur_170': 'Période déclarée invalide avec le régime et le formulaire  (formulaire principal).',
      'erreur_171': 'Période déclarée invalide sur le formulaire annexe  (à préciser = 3515 SD).',
      'erreur_172': 'Format: SIREN invalide, et Format SIRET interdit.',
      'erreur_173': 'Période déclarée invalide.',
      'erreur_174': 'Clé de contrôle du SIREN invalide',
      'erreur_175': 'Obligation fiscale TVA non trouvée pour la référence de l’obligation fiscale déclarée.',
      'erreur_176': 'Adhésion à Télédéclarer TVA filière EDI NON valide à la date de dépôt.',
      'erreur_177': 'Format Référence Obligation fiscale invalide.',
      'erreur_178': 'Période déclarée supérieure à 12 mois.',
      'erreur_179': 'Code  non valide pour la période déclarée.',
      'erreur_180': 'Format de la date et/ou de la  période invalide dans le formulaire',
      'erreur_185': 'TVA Groupe formulaire 3310CA3G invalide pour la période déclarée',
      'erreur_186': 'TVA Groupe formulaire principal absent ou invalide',
      'erreur_188': 'Période déclarée invalide avec la TVA Groupe et formulaire  (formulaire principal)',
      'erreur_189': 'Présence d’un événement déclaré incompatible avec un paiement TVAGROUPE.',
      'erreur_191': 'Compte bancaire : clé RIB invalide  dans TPn.',
      'erreur_192': 'Compte bancaire : couple (code banque ; code guichet)  invalide dans TPn.',
      'erreur_193': 'Compte bancaire : code pays incorrecte ou invalide dans TPn',
      'erreur_194': 'Compte bancaire : clé IBAN invalide dans TPn',
      'erreur_195': 'Compte bancaire : code BIC invalide dans TPn. (non appliqué)',
      'erreur_197': 'Anomalie dans la recherche de l’obligation fiscale',
      'erreur_198': 'Anomalie dans la recherche du code du  service compétent',
      'erreur_199': 'Obligation fiscale TVA sans modalité régime',

      'rcm2777_01': 'La saisie d\'une base imposable implique obligatoirement la saisie du taux correspondant. Merci d\'indiquer le taux à appliquer.',
      'rcm2777_02': 'Le pourcentage doit être strictement supérieur à 0 et inférieur ou égal à 75.',
      'rcm2777_03': 'Le pourcentage doit être strictement supérieur à 0 et inférieur ou égal à 100.',
      'rcm2777_04': 'La base de la ligne HG regroupe au moins la somme des lignes HE et HF.',
      'rcm2777_05': 'La saisie d\'une base imposable au titre de la retenue à la source (art.119 bis 2 CGI) implique la saisie d\'une base imposable à la ligne HG et/ou HH. Merci de corriger.',
      'rcm2777_06': 'La base de la ligne HH regroupe au moins la somme des lignes HA, HB et HD.',
      'rcm2777_07': 'Le total des bases des lignes HG et HH ne correspond pas à la somme des bases des  lignes de la sous-rubrique retenue à la source (art.119 bis 2 du CGI) sauf lignes HJ.',
      'rcm2777_08': 'Veuillez reporter le montant excédentaire sur la ligne TC de la présente déclaration. Merci de corriger.',
      'rcm2777_09': 'Veuillez saisir une période antérieure à la période  déclarée. Merci de corriger.',
      'rcm2777_10': 'La saisie d\'un mois de versement implique obligatoirement la saisie d\'un montant de régularisation. Merci d\'indiquer au moins un montant en colonne (a) ou (b).',
      'rcm2777_11': 'Vous ne pouvez pas saisir une base d\'acompte en dehors de la période déclarative relative au mois de septembre.',
      'rcm2777_12': 'Vous ne pouvez pas saisir de valeur en dehors de la période déclarative relative au mois de septembre.',
      'rcm2777_13': 'Vous ne pouvez pas saisir un montant d\'acompte en dehors de la période déclarative relative au mois de décembre.',
      'rcm2777_14': 'Vous ne pouvez pas saisir de valeur en dehors de la période déclarative relative au mois de décembre.',
      'rcm2777_15': 'Vous ne pouvez pas saisir un montant d\'acompte en dehors de la période déclarative relative au mois de janvier.',
      'rcm2777_16': 'Vous ne pouvez pas saisir de valeur en dehors de la période déclarative relative au mois de janvier.',
      'rcm2777_17': 'Vous ne pouvez pas saisir un montant d\'acompte  montant d\'excédent en dehors de la période déclarative relative au mois de janvier.',
      'rcm2777_18': 'Vous n\'êtes pas en situation d\'excédent, vous ne pouvez donc pas effectuer une demande de remboursement.',
      'rcm2777_19': 'Le montant excédentaire ne peut pas être reporté, la demande de remboursement est obligatoire pour le mois de janvier.',
      'rcm2777_20': 'La saisie d\'un montant de régularisation implique obligatoirement la saisie d\'un mois de versement. Merci d\'indiquer le mois de versement correspondant.',
      'rcm2777_21': 'La saisie d\'un taux implique obligatoirement la saisie de la base imposable correspondante. Merci d\'indiquer la base imposable.',
      'rcm2777_22': 'Le montant d\'impôt de la ligne HG regroupe au moins la somme des lignes HE et HF.',
      'rcm2777_23': 'La saisie d\'une base imposable au titre de la retenue à la source (art.119 bis 2 CGI) implique la saisie d\'un montant d\'impôt à la ligne HG et/ou HH. Merci de corriger.',
      'rcm2777_24': 'Le total des montants d\'impôts des lignes HG et HH ne correspond pas à la somme des montants d\'impôts des lignes de la sous-rubrique retenue à la source (art.119 bis 2 du CGI) sauf ligne HJ.',


      'cvae_erreur_201': 'le montant du chiffre d\'affaires est obligatoirement servi,  même à zéro.',
      'cvae_erreur_202': 'le montant C.A. doit être supérieur ou égal à 152 500 euros pour déposer un acompte de CVAE',
      'cvae_erreur_205': 'si un C.A. sur période différente 12 mois est présent',
      'cvae_erreur_206': 'le C.A. « groupe » doit être au moins égale au  C A.. rapporté sur 12 mois',
      'cvae_erreur_207': 'Une seule zone doit être servie pour l\'ajustement de l\'acompte ( Augmentation ou Diminution )',
      'cvae_erreur_208': 'Vous ne pouvez pas servir une augmentation ou une diminution pour l\'acompte de juin.',
      'cvae_erreur_209': 'Le SIREN doit être valide',
      'cvae_erreur_210': 'La saisie d\'un montant du chiffre d\'affaires de référence du Groupe implique obligatoirement la saisie du numéro SIREN de la société tête de groupe.',
      'cvae_erreur_211': 'La saisie du numéro SIREN de la société tête de groupe implique obligatoirement la saisie d\'un montant du chiffre d\'affaires de référence du Groupe.',
      'cvae_erreur_212': 'Aucun montant du chiffre d\'affaires de référence de groupe ne doit être saisi.',
      'cvae_erreur_214': 'Le montant de la valeur ajoutée produite est obligatoirement servi, même à zéro',
      'cvae_erreur_215': 'Vous ne pouvez saisir un chiffre d\'affaires groupe inférieur à 7 630 000 €',
      'cvae_erreur_902': 'Présence de la CVAE sans montant d\'acompte versé.',
      'cvae_erreur_903': 'Présence de frais de gestion sans montant d\'acompte versé. ',
      'cvae_erreur_904': 'Présence d\'une valeur ajoutée nulle',

      'erreur_211': 'Donnée(s) absente(s) et/ou erronée(s) les calculs formulaire sont impossibles',
      'erreur_034': 'Erreur dans multiplication zone',
      'erreur_038': 'Absence de décompte de la TVA à payer pour acquisitions intra-communautaires.',
      'erreur_042': 'Erreur zone CCDDDD du FFFFFFFFFFMMIIII: Formulaire non “ Néant ” .',
      'erreur_049': 'Absence de montant déclaré supérieur à 0 et zone \'Formulaire Néant\' non servie. Rejet TD.',
      'erreur_051': 'Le montant de la zone  du  ne peut être supérieur au total “ Autre TVA à déduire ” dont il constitue un des éléments.',
      'erreur_100': 'Code  absent dans formulaire .',
      'erreur_101': 'Le montant des excédents antérieurs à imputer ne peut pas être supérieure au montant de l’acompte mentionné.',
      'erreur_102': 'Pour cette demande de diminution, la période du décompte doit être servie.',
      'erreur_103': 'Les entreprises non établie en France doivent désigner un représentant fiscal et servir les lignes du cadre Identification de l’entreprise.',
      'erreur_104': 'Une seule zone doit être servie pour le type de demande (Première demande ou Cession/Cessation/Décès ou Autres)',
      'erreur_105': 'Si présence d\'un décompte de la TVA, la période du décompte doit être servie',
      'erreur_106': 'Au moins une des zones « à créditer au compte désigné » ou « à imputer sur une échéance future » doit être servie.',
      'erreur_107': 'Demande concomitante d’augmentation et de diminution de l’acompte impossible.',
      'erreur_108': 'Demande concomitante d’augmentation et de suspension de l’acompte impossible.',
      'erreur_109': 'Demande concomitante de diminution de l’acompte pour plusieurs motifs impossible.',
      'erreur_110': 'La présence d’un taux de TVA implique obligatoirement la présence d’opérations ouvrant droit à remboursement',
      'erreur_111': 'La présence d’une base HT implique obligatoirement la présence de la taxe due correspondante.',
      'erreur_112': 'La présence d’une taxe due implique obligatoirement la présence de la base HT correspondante .',
      'erreur_113': 'La TVA brute étant égale à zéro, la TVA sur acquisitions intra-communautaires ne peut qu’être égale à zéro',
      'erreur_114': 'Le montant à imputer ne peut être > au montant de taxe due (ligne 28 + ligne 29 + ligne 31).',
      'erreur_115': 'Le montant du nouvel acompte doit être au moins égal à celui de l’excédent à imputer ligne d.',
      'erreur_116': 'Le montant du pourcentage est incohérent.',
      'erreur_117': 'Le montant taxe due est incohérent par rapport à la base HT.',
      'erreur_118': 'Le remboursement demandé n’est pas cohérent avec la valeur présente dans la cadre Demande de Remboursement.',
      'erreur_119': 'Le remboursement demandé doit être égal au plus petit des deux montants : soit le plafond de remboursement, soit le crédit dégagé',
      'erreur_120': 'Le total des bases hors taxes lignes 08 à 14 doit être égal au total des opérations imposables lignes 01+02+2A+03+3A+3B.',
      'erreur_121': 'Le total des lignes 17, 7C et 1 8 ne peut être supérieur au total de la TVA brute due ligne 16',
      'erreur_123': 'Seuls les taux de 19, 6%, 13 %, 8,5 %, 8 %, 5,5%, 7 %, 2,1%, 1,75 %, 1,05 % et 0,90 % sont applicables.',
      'erreur_124': 'La description des acomptes ligne 30 est incohérente avec celle de la ligne 58 – (enlever 0 significatif dans acompte 1 et/ou acompte 2 et/ou acompte 3 et/ou acompte 4)',
      'erreur_125': 'Une seule procédure est possible : un seul cadre doit être servi (cadre III Procédure générale ou cadre IV Procédure spéciale exportateurs).',
      'erreur_126': 'Code erreur 126 :une seule zone doit être servie pour la nationalité de l’entreprise (entreprise française, entreprise non établie n\'ayant pas l\'obligation de désigner un représentant fiscal ou ayant l\'obligation de désigner un représentant fiscal). Rejet TD',
      'erreur_127': 'le montant du remboursement demandé ne peut pas être supérieur au montant de biens constituant les immobilisations',
      'erreur_128': 'La case "mention expresse" est servie sans mention de motif associé dans le cadre correspondance.',
      'erreur_129': 'Absence de l’année au titre de laquelle cet acompte a été imputé.',
      'erreur_130': 'Le montant à imputer doit être <= au montant Taxe nette due.',
      'erreur_131': 'Le montant du remboursement demandé ne peut pas être supérieur au crédit de TVA',
      'erreur_132': 'Le montant du remboursement demandé ne peut pas être supérieur au crédit de TVA diminué, le cas échéant, du crédit imputé sur le ou les prochains acomptes.',
      'erreur_133': 'Le total des bases hors taxes lignes 08 à 14 doit être égal au total des opérations imposables lignes 01+02+03+03A.',
      'erreur_134': 'Période saisie incohérente. Seuls peuvent être déduits les acomptes se rapportant à la période d’imposition.',
      'erreur_135': 'La présence d’un montant ligne 13 au titre des acquisitions intra-communautaires implique la présence de la ligne 17,18 ou 20 au titre de la TVA déductible.',
      'erreur_136': 'Le montant de la zone ne peut être supérieur au montant des acquisitions intra-communautaires.',
      'erreur_137': 'Le montant de la zone ne peut être supérieur au total “ Acquisitions intracommunautaires ” dont il constitue un des éléments.',
      'erreur_138': 'Si demande de diminution acompte, zone crédit dégagé sur la précédente 3517SCA12/CA12E doit être > 0.',
      'erreur_139': 'Le montant de  l\'acompte diminué doit être servi.',
      'erreur_140': 'Si montant régularisations sur TVA > 0, montants régularisations dans A-Montant des opérations réalisées doit être > 0.',
      'erreur_141': 'Le montant total à payer doit être égal à la somme des montants dont TVA et dont taxes fiscales.',
      'erreur_142': 'Le montant total des taxes fiscales doit correspondre aux total des taxes fiscales déclarées',
      'erreur_144': 'La présence d’opérations ouvrant droit à remboursement implique obligatoirement la présence d’un taux de TVA.',
      'erreur_145': 'La période du décompte doit correspondre à un trimestre civil.',
      'erreur_146': 'La période du décompte doit être antérieure à la date limite de dépôt.',
      'erreur_148': 'Lors d\'une première demande de remboursement de crédit de TVA, les factures les plus importantes ouvrant droit à déduction (cinq au plus) doivent être mentionnées dans la zone Commentaires.',
      'erreur_149': 'Le statut de la demande doit être précisé',
      'erreur_150': 'le code type de déclaration est erroné.',
      'erreur_200': 'Une seule zone doit être servie pour la nationalité de l’entreprise (entreprise française, entreprise étrangère établie dans la CE ou entreprise étrangère établie hors CE).',
      'erreur_201': 'Absence de montant déclaré ou de justificatif de non paiement',
      'erreur_202': 'Le remboursement demandé ne peut excéder le maximum remboursable.',
      'erreur_203': 'Présence d\'un libellé de Secteur avec un pourcentage de déduction erroné',
      'erreur_204': 'Le montant du solde excédentaire doit être égal au remboursement demandé plus le total des crédits à reporter ou imputé.',
      'erreur_205': 'Le montant de cette ligne ne peut être supérieur au montant de la  TVA déductible dont il constitue un des éléments.',
      'erreur_206': 'La taxe ne peut pas être déclarée pour la période d\'imposition',
      'erreur_207': 'Le crédit reportable doit être égal au maximum remboursable moins remboursement demandé',
      'erreur_208': 'Le crédit reportable doit être égal au maximum remboursable moins remboursement demandé, plus crédit dégagé si < 150 euros',
      'erreur_209': 'Le montant ne peut être servi en présence de la modulation de l’acompte.',
      'erreur_210': 'les données de modulation de l’acompte sont incohérente entre elles.',
      'erreur_212': 'Absence de donnée totalisation du formulaire de paiement de TVA groupe',
      'erreur_213': 'le montant de crédit ou de l’excédent de TVA figurant sur la CA12(E) ne doit pas excéder le montant de l’acompte attendu ou modulé.',
      'erreur_214': 'le montant de la TVA collectée au titre du semestre ne doit pas excéder le montant de TVA déductible au titre du semestre.',
      'erreur_215': 'le montant du remboursement de la TVA sur investissements demandé doit être compris entre 760 euros et le montant de crédit de TVA dégagé au titre du semestre',
      'erreur_216': 'le montant de l’acompte attendu ou modulé de TVA doit être renseigné.',
      'erreur_217': 'Les cadres 1 et 2 ne peuvent être renseignés simultanément.',
      'erreur_218': 'Aucune éolienne maritime n\'étant en production, aucun montant ne peut être saisi pour l\'heure.',
      'erreur_219': 'Erreur zone  code absent ou nul dans le formulaire du .',
      'erreur_220': 'le « Remboursement demandé » doit être égal au « Montant de remboursement demandé »',
      'erreur_221': 'Une seule des 2 cases « A créditer au compte désigné » ou « A imputer sur une échéance à venir » doit être servie.',
      'erreur_222': 'Le montant du pourcentage est incohérent.',
      'erreur_223': 'vous devez renseigner la date correspondant à cet événement',
      'erreur_224': 'le total des bases hors taxes lignes 08 à 14 doit être égal au total des opérations imposables lignes 01+02+2A+2B+03+3A+3B.',
      'erreur_225': 'Le montant ne peut être inférieur aux seuils prévus à l’article 242-0 C de l’Annexe II au CGI , sauf événements particuliers',
      'erreur_226': 'Absence de case cochée au titre de laquelle l\'année a été complétée',
      'erreur_227': 'Erreur zone : Le montant ne peut comporter que 9 chiffres au maximum',
      'erreur_229': 'Erreur zone : Le montant ne peut comporter que 6 chiffres au maximum',
      'erreur_230': 'Erreur zone : Les coordonnées bancaires doivent être obligatoirement saisies',
      'erreur_231': 'Erreur zone : Si l\'une des quatre données Base ou Taxe due est saisie, alors les trois autres données doivent être aussi saisies',
      'erreur_232': 'Erreur zone : Si l\'une des trois données Base ou Taxe due est saisie, alors les deux autres données doivent être aussi saisies',
      'erreur_233': 'Erreur zone : Vous devez saisir le numéro de département et les droits pour celui-ci.',
      'erreur_233_tva_3310a': 'Vous devez saisir la contribution, le nombre d\'hectolitres ainsi que le numéro de la commune bénéficiaire',
      'erreur_233_tva_ca3g': 'Vous devez saisir le numéro de commune et les droits pour celui-ci.',
      'erreur_233_tva_3517sca12': 'Vous devez saisir la contribution, le nombre d\'hectolitres ainsi que numéro de la commune bénéficiaire.',
      'erreur_300': 'un montant à payer et un montant d\'excédent sont exclusifs l\'un de l\'autre.',
      'erreur_301': 'le montant de l\'excédent imputé sur le premier acompte de l\'exercice suivant doit être inférieur ou égal au montant total de l\'excédent.',
      'erreur_302': 'la présence de la nature, de l\'année,le montant de la créance ou du crédit d\'impôt et le montant du remboursement sollicité sont obligatoire.',
      'erreur_303': 'l\'année servie doit être comprise entre N-13 et N (N = année de dépôt).',
      'erreur_304': 'La date servie doit être comprise entre 01/01/N-10 et la date de dépôt.',
      'erreur_305': 'Donnée absente ou invalide',
      'erreur_306': 'Date invalide',
      'erreur_307': 'RAD,  la présence de la date de clôture, de la date de cession et du montant de la créance cédée sont obligatoire.',
      'erreur_308': 'la présence de la nature, de la date de cloture, de la date de transfert et  du montant de la créance transférée sont obligatoire.',
      'erreur_309': 'les codes RES et REL ne sont plus acceptés à compter du millésime 2015.',
      'erreur_310': 'La saisie des données relatives à la contribution visée, à sa date d\'échéance et à son montant à imputer doit concerner les trois champs ou aucun.',
      'erreur_311': 'Le montant du paiement par imputation doit être inférieur ou égal au montant total à payer.',
      'erreur_312': 'La date d\'échéance de la contribution utilisée doit être strictement antérieure au premier du mois de la date de l\'échéance du 2571.',
      'erreur_313': 'Le montant de l\'intérêt légal à déduire ne peut être saisi que pour les reports en arrière de déficit d\'une entreprise en procédure collective.',
      'erreur_314': 'Le montant de la créance à utiliser doit être inférieur ou égal au remboursement sollicité.',
      'erreur_315': 'la présence de la nature, de l\'année,  et le montant du remboursement sollicité sont obligatoires.',
      'erreur_319': 'Le montant du paiement par imputation doit être inférieur ou égal au montant total de l\'excédent déduit du montant de l\'excédent imputé sur le premier acompte de l\'exercice suivant.',
      'erreur_320': 'La date servie doit être postérieure ou égale à la date de dépôt.',
      'erreur_321': 'La saisie des données relatives à  la contribution utilisée, la date de l’échéance, et le montant à utiliser  doit concerner les 3 champs ou aucun.',
      'erreur_322': 'La saisie d\'un montant du préfinancement implique obligatoirement la saisie d\'un montant positif de la créance correspondante.',
      'erreur_323': 'Cette saisie n\'est possible que pour les exercices supérieur à 12 mois et clôturant au 31/12.',
      'erreur_324': 'Aucun montant ne peut être saisi dans cette case.',
      'erreur_325': 'Ce crédit d\'impôt est supprimé à compter de 2018. Rejet TD',

      'erreur_403': 'Le montant de l\'abattement est erroné.',
      'erreur_405': 'La somme des montants de remboursement demandé, de demande d\'imputation sur échéance future et de report année suivante sur versement provisionnel 2501, doit être inférieure ou égale au montant de l\'excédent de versement.',
      'erreur_407': 'Si un excédent de versement est dégagé, au moins une des trois données "Remboursement demandé", "Demande d\'imputation sur échéance future" ou "Report année suivante sur versement provisionnel 2501" doit être saisie.',
      'erreur_408': 'Les associations ayant droit au CITS peuvent saisir cette case uniquement à partir de l\'année d\'imposition 2018.',

      'erreur_sd' : 'Les éléments saisis ne correspondent pas à ceux figurant dans la déclaration annexe 3515 SD.',

      'erreur_112_ifu' : 'Au moins une de ces trois zones doit obligatoirement être renseignée.',
      'erreur_113_ifu' : 'Ces zones ne peuvent pas être servies simultanément.',
      'erreur_114_ifu' : 'Si le nom de famille est renseigné, cette zone ne peut pas être vide.',
      'erreur_125_ifu' : 'Produits du PEP: la présence (saisie) de cette donnée (BT/MOA du 2561) implique obligatoirement la présence (saisie) d\'au moins une des données suivantes BF/MOA du 2561, BH/MOA du 2561, BJ/MOA du 2561, CA/MOA du 2561, CB/MOA du 2561, CC/MOA du 2561, CD/MOA du 2561, CW/MOA du 2561, CZ/MOA du 2561.',
      'erreur_126_ifu' : 'Répartitions de FCPR et distributions de SCR: la présence (saisie) de cette donnée (BU/MOA du 2561) implique obligatoirement la présence (saisie) d\'au moins une des données suivantes BF/MOA du 2561, BJ/MOA du 2561, CA/MOA du 2561.',
      'erreur_127_ifu' : 'Produits soumis à l’IR ayant fait l’objet d’une retenue à la source: la présence (saisie) de cette donnée (BV/MOA du 2561) implique obligatoirement la présence (saisie) d\'au moins une des données suivantes CT/MOA du 2561, CX/MOA du 2561.',
      'erreur_129_ifu' : 'Profits réalisés sur les instruments financiers à terme : les données « Gains » (DM/MOA du 2561) ou « Profits » (DN/MOA du 2561) ne peuvent pas être servies simultanément à une donnée « Pertes » (DP/MOA du 2561).',
      'erreur_130_ifu' : 'Pour un article Bénéficiaire, au moins un des montants suivants doit être servi.',
      'erreur_133_ifu' : 'Montant du prélèvement forfaitaire libératoire appliqué aux produits des versements effectués avant le 27/09/17 (CV/MOA du 2561)  implique obligatoirement la présence (saisie) de la donnée Produits des versements effectués avant le 27/09/17 soumis à un prélèvement forfaitaire libératoire (CU/MOA du 2561).',
      'erreur_144_ifu' : 'Montant du prélèvement forfaitaire libératoire appliqué aux gains attachés versements effectués avant le 27/09/17 (FL/MOA du 2561) implique obligatoirement la présence (saisie) de la donnée Gains attachés aux versements effectués avant le 27/09/17 soumis à un prélèvement forfaitaire libératoire (FK/MOA du 2561).',
      'erreur_145_ifu': 'Gain de cessions de bons ou contrat de capitalisation soumis aux prélèvements sociaux (sans CGS déductible) (FP/MOA du 2561) implique obligatoirement la présence (saisie) de la donnée Gains attachés aux versements effectués à compter du 27/09/17 ne bénéficiant pas de l’abattement (FM/MOA du 2561)',
      'erreur_216_ifu' : 'Crédit d\'impôt : la présence (saisie) de cette donnée (BA/MOA du 2561) implique obligatoirement la présence (saisie) d’au moins une des données suivantes CT/MOA du 2561, BF/MOA du 2561, BJ/MOA du 2561, CA/MOA du 2561.',
      'erreur_217_ifu' : 'Crédit d\'impôt prélèvement : la présence (saisie) de cette donnée (BC/MOA du 2561) implique obligatoirement la présence (saisie) d\'au moins une des données suivantes BF/MOA du 2561, BH/MOA du 2561, BJ/MOA du 2561, CA/MOA du 2561, CB/MOA du 2561, CC/MOA du 2561, CD/MOA du 2561, CT/MOA du 2561, CW/MOA du 2561, CX/MOA du 2561, CZ/MOA du 2561.',
      'erreur_218_ifu' : 'Montant du prélèvement : la présence (saisie) de cette donnée (BP/MOA du 2561) implique obligatoirement la présence (saisie) de la donnée Base du prélèvement (BN/MOA du 2561).',
      'erreur_219_ifu' : 'Montant de la distribution : la présence (saisie) de cette donnée (CR/MOA du 2561) implique obligatoirement la présence (saisie) d\'au moins une des données suivantes DE/DTM du 2561, DF/DTM du 2561, DG/DTM du 2561, DC/QTY du 2561, CP/MOA du 2561.',
      'erreur_220_ifu' : 'La présence (saisie) des données Début de période de dépassement (DH/DTM du 2561) et/ou Fin de période de dépassement (DJ/DTM du 2561) implique la présence (saisie) de la donnée Nombre de parts détenues (DD/QTY du 2561).',
      'erreur_221_ifu' : 'Dénomination du fond : la présence (saisie) de cette donnée (DA/FTX du 2561) implique obligatoirement la présence (saisie) d’au moins une des données comprises entre Nombre de parts cédées (DB/QTY du 2561) et Nombre de parts détenues (DD/QTY du 2561).',
      'erreur_222_ifu' : 'Date d\'ouverture du plan : la présence (saisie) de cette donnée (EB/DTM du 2561) implique obligatoirement la présence (saisie) de la donnée Référence du plan (EA/RFF du 2561).',
      'erreur_223_ifu' : 'La présence (saisie) d\'au moins une des données suivantes Date du premier retrait ou du premier rachat de contrat de capitalisation (EC/DTM du 2561), Valeur liquidative du plan ou de rachat du contrat de capitalisation à la date de clôture du plan (ED/MOA du 2561), Montant cumulé des versements (EE/MOA du 2561), '
      + 'Montant des produits éligibles à l’abattement de 40 % des titres non cotés (EF/MOA du 2561), Montant des produits non éligibles à l’abattement de 40 % des titres non cotés (EG/MOA du 2561), Montant du crédit d’impôt sur titres non cotés étrangers (EH/MOA du 2561), '
      + 'implique la présence (saisie) obligatoire des 2 données suivantes Référence du plan (EA/RFF du 2561) et Date d\'ouverture du plan (EB/DTM du 2561)',
      'erreur_224_ifu' : 'La présence (saisie) d’une des données suivantes Valeur liquidative du plan ou de rachat du contrat de capitalisation à la date de clôture du plan (ED/MOA du 2561), Montant cumulé des versements (EE/MOA du 2561) implique obligatoirement la présence (saisie) de l’autre donnée.',
      'erreur_225_ifu' : 'Montant du crédit d’impôt sur titres non cotés étrangers : la présence (saisie) de cette donnée (EH/MOA du 2561) implique obligatoirement la présence (saisie) d’au moins une des données suivantes Montant des produits éligibles à l’abattement de 40 % des titres non cotés (EF/MOA du 2561), Montant des produits non éligibles à l’abattement de 40 % des titres non cotés (EG/MOA du 2561).',
      'erreur_226_ifu' : '',
      'erreur_227_ifu' : '',
      'erreur_228_ifu' : '',
      'erreur_229_ifu' : '',
      'erreur_230_ifu' : '',
      'erreur_231_ifu' : '',
      'erreur_234_ifu' : 'Montant du PFO appliqué aux gains de cessions de bons ou contrats de capitalisation ouvrant droit à crédit d’impôt (FJ/MOA du 2561) implique obligatoirement la présence (saisie) de la donnée Gains attachés aux versements effectués à compter du 27/09/17 (FM/MOA du 2561)',
      'erreur_ifu_etranger': 'La valeur de ce champ doit commencer par 99',

      '=': 'doit être égal à',
      '<': 'doit être strictement inférieur à',
      '<=': 'doit être inférieur ou égal à',
      '>': 'doit être strictement supérieur à',
      '>=': 'doit être supérieur ou égal à',

      // a-identif-hon, das2t, das2tv
      'erreur_301_das2': 'SIRET Entreprise/Etablissement (AA/NAD du A-IDENTIF et AA/NAD du DAS2T) : Identification du déclarant absente ou inconnu.',
      'erreur_307_das2': 'Raison sociale (AA/NAD du A-IDENTIF) : la raison sociale contient des caractères non signifiants. Elle doit contenir des informations signifiantes et doit être obligatoirement renseignée.',
      'erreur_304_das2': 'SIRET de l’établissement déposant la déclaration de résultat (AB/NAD du A-IDENTIF) : les neuf premiers caractères sont différents du SIREN présent dans le SIRET de l’entreprise.',
      'erreur_310_das2': 'Raison sociale, nom de famille (AF/NAD et AE/NAD du DAS2TV) : au moins une de ces deux zones doit obligatoirement être renseignée.',
      'erreur_311_das2': 'Prénom(s) (AE/NAD du DAS2TV) : Si le nom de famille est renseigné, cette zone ne peut pas être vide.',
      'erreur_316_das2': 'Rémunérations versées : il faut obligatoirement la présence (saisie) d’au moins une des données suivantes : • Rémunération versée (BA/MOA du DAS2TV) ; • Indemnités et remboursements (BB/MOA du DAS2TV) ; • Avantage en nature (BC/MOA du DAS2TV)',
      'erreur_317_das2': 'Rémunérations versées : la présence (saisie) de cette donnée (BA/MOA du DAS2TV) implique obligatoirement la présence (saisie) de la donnée Nature des rémunérations versées (CA/CCI du DAS2TV)',
      'erreur_318_das2': 'Indemnités et remboursements : la présence (saisie) de cette donnée (BB/MOA du DAS2TV) implique obligatoirement la présence (saisie) de la donnée Modalités de prise en charges des indemnités et remboursements (CB/CCI du DAS2TV)',
      'erreur_319_das2': 'Avantages en nature : la présence (saisie) de cette donnée (BC/MOA du DAS2TV) implique obligatoirement la présence (saisie) de la donnée Nature des avantages en nature (CC/CCI du DAS2TV)',
      'erreur_409_das2': 'SIRET du bénéficiaire (AF/NAD du DAS2TV) : Si la raison sociale est renseignée, cette zone ne peut pas être vide.',
      'erreur_320_das2': 'Retenue à la source : la présence (saisie) de cette donnée (BD/MOA du DAS2TV) implique obligatoirement la présence (saisie) de la donnée Nature du taux de retenue à la source (CD/CCI du DAS2TV)',
      'erreur_das_etranger': 'La valeur de ce champ doit commencer par 99',
      'erreur_das_multiple_ua': 'Cette nature a déjà été renseignée',

      'erreur_required': 'Ce champ est requis.',
      'erreur_not_required': 'Ce champ ne doit pas être saisi.'
    },
    $dico: function(fieldName) {
      if (arguments.length == 1) {
        if (this.$dicoContent.hasOwnProperty(fieldName)) {
          return '<span class="label--dynamic__keyword">'
             // + '(' + fieldName + ') '
            + this.$dicoContent[fieldName] + '</span>';
        }
        return fieldName;
      }
      var labels = [];
      for (var i = 1; i < arguments.length; i++) {
        labels.push(this.$dico(arguments[i]));
      }
      var html = '';
      html += labels.join(" ");
      html += '';
      return html;
    },
    $controls: {
      maxOneCheckboxChecked: function(elts) {
        var checkeds = elts.filter(function(elt) {
          return elt.checked;
        });
        return checkeds.length <= 1;
      },
      atLeastOneCheckboxChecked: function(elts) {
        var checkeds = elts.filter(function(elt) {
          return elt.checked;
        });
        return checkeds.length > 0;
      },
      erreur_042: function($eltFormulaireNeant, editableFields) {
        var core = asserts.core;
        core.$assert(!(core.$isServi($eltFormulaireNeant)
                     && ( editableFields.some(function(field) {
                       return core.$isServi(field) && core.$float(field) > 0;
                     }) )),
                     'erreur_042',
                     $eltFormulaireNeant, editableFields);
      },
      erreur_049: function($eltFormulaireNeant, editableFields) {
        var core = asserts.core;

        for (var i = 0; i < editableFields.length; i++) {
          core.$assert(!(!core.$isServi($eltFormulaireNeant) && !(core.$isServi(editableFields[i]) && core.$float(editableFields[i]) >= 0)),
                       'erreur_049', $eltFormulaireNeant, editableFields[i]);
        }
      },
      erreur_111: function($fieldA, $fieldB) {
        var core = asserts.core;
        core.$assert(!(core.$isServi($fieldA) && core.$float($fieldA) > 0 && !(core.$isServi($fieldB) && core.$float($fieldB) > 0)),
                     'erreur_111', $fieldA, $fieldB);
      },
      erreur_112: function($fieldA, $fieldB) {
        var core = asserts.core;
        core.$assert(!(core.$isServi($fieldA) && core.$float($fieldA) > 0 && !(core.$isServi($fieldB) && core.$float($fieldB) > 0)),
                     'erreur_112', $fieldA, $fieldB);
      },
      erreur_112_addition: function($fieldA, $fieldB, $fieldC) {
        var core = asserts.core;
        core.$assert(!(core.$isServi($fieldA) && core.$float($fieldA) > 0 && !(core.$isServi($fieldB) && core.$isServi($fieldC) && core.$float($fieldB) + core.$float($fieldC) > 0)),
                     'erreur_112', $fieldA, $fieldB, $fieldC);
      },
      erreur_116: function($eltA, $eltB) {
        var core = asserts.core;
        core.$assert(!(core.$isServi($eltA) && !(core.$isServi($eltB) && 0 <= core.$float($eltB) && core.$float($eltB) <= 100)),
                     'erreur_116', $eltA, $eltB);
      },
      erreur_117: function($eltA, $eltB, coefMin, coefMax) {
        var core = asserts.core;
        core.$assert(!(core.$isServi($eltA) && core.$isServi($eltB)
                     && !((core.$float($eltA) * coefMin) <= core.$float($eltB) && core.$float($eltB) <= (core.$float($eltA) * coefMax))),
                     'erreur_117', $eltA, $eltB);
      },
      erreur_129: function($eltCheckbox, $eltNeeded) {
        var core = asserts.core;
        core.$assert(!(core.$isServi($eltCheckbox) && !core.$isServi($eltNeeded)), 'erreur_129', $eltCheckbox, $eltNeeded);
      },
      erreur_134: function($eltDate, $eltYearImpositionBegin, $eltYearImpositionEnd) {
        var core = asserts.core;
        var yearBegin = core.$value($eltYearImpositionBegin).split('/');
        var yearEnd = core.$value($eltYearImpositionEnd).split('/');
        yearBegin = yearBegin[2];
        yearEnd = yearEnd[2];
        core.$assert(!(core.$isServi($eltDate) && core.$isServi($eltYearImpositionBegin) && core.$isServi($eltYearImpositionEnd) && !(core.$float($eltDate) == yearBegin || core.$float($eltDate) == yearEnd)),
                     'erreur_134', $eltDate);
      },
      erreur_226: function($eltNeeded, $eltCheckbox) {
        var core = asserts.core;
        core.$assert(!(!core.$isServi($eltCheckbox) && core.$isServi($eltNeeded)), 'erreur_226', $eltNeeded, $eltCheckbox);
      },
    },
    $assert: function(assertFunc, error_code) {
      var elts = [];
      for (var i = 2; i < arguments.length; i++) {
        if (Object.isArray(arguments[i])) {
          elts.concat(arguments[i]);
        }
        else {
          elts.push(arguments[i]);
        }
      }

      NTD.Generic.none(elts, error_code);
      if (typeof assertFunc == "function") {
        assertFunc = assertFunc(elts);
      }
      if (!assertFunc) {
        NTD.Generic.negativ(elts,
                            this.$dico(error_code),
                            error_code);
      }
    }
  }
};
