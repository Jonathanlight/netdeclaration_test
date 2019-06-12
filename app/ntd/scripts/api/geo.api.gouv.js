var gouv = {};

gouv.api = {
    requestCodeInseeByPostalCode: function(elt, postalCode) {
        if (postalCode) {
            var url = 'https://geo.api.gouv.fr/communes?codePostal='+postalCode+'&fields=nom,code&format=json&geometry=centre';
            new Ajax.Request(url, {
                method: 'get',
                onSuccess: function(response) {
                    elt.innerHTML = "";

                    var value = elt.readAttribute('data-value')

                    var firstOption = document.createElement('option');
                    firstOption.setAttribute('value', '');
                    firstOption.appendChild(document.createTextNode('-'));
                    elt.appendChild(firstOption);

                    var results = response.responseJSON;
                    results.each(function(element) {
                        var option = document.createElement('option');
                        option.setAttribute('value', element.code);
                        if (value && value == element.code) {
                            option.selected = true;
                        }
                        option.appendChild(document.createTextNode(element.nom + ' - ' + element.code));
                        elt.appendChild(option);
                    })
                    // Commenté pour afficher l'erreur quand le formulaire est rechargé

                    // if (value) {
                    //     elt.removeClassName('has-error');
                    // }

                }
            })
        }
    },

    requestCodeInseeByCity: function(elt, city) {
        var url = 'https://geo.api.gouv.fr/communes?nom='+city+'&fields=nom,code&format=json&geometry=centre';
        new Ajax.Request(url, {
            method: 'get',
            onSuccess: function(response) {
                elt.innerHTML = "";

                var value = elt.readAttribute('data-value')

                var firstOption = document.createElement('option');
                firstOption.setAttribute('value', '');
                firstOption.appendChild(document.createTextNode('-'));
                elt.appendChild(firstOption);

                var results = response.responseJSON;
                results.each(function(element) {
                    var option = document.createElement('option');
                    option.setAttribute('value', element.code);
                    if (value && value == element.code) {
                        option.selected = true;
                    }
                    option.appendChild(document.createTextNode(element.nom + ' - ' + element.code));
                    elt.appendChild(option);
                })
                // if (value) {
                //     elt.removeClassName('has-error');
                // }
            }
        })
    },
}