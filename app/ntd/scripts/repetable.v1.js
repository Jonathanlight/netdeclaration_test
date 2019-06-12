document.observe("dom:loaded", function() {
    $$('.formulaire-repetable-select select').each(function(element) {
        element.on('change', function() {
            var occurence = element.getValue();
            var formCode = element.up('.formulaire-repetable').readAttribute('data-code');
            var blockForm = $$('.formulaire-block.'+formCode);
            if (!blockForm.length) {
                blockForm = $$('.formulaire-visibility.'+formCode);
            }
            var formContents = blockForm[0].childElements('div');
            var currentForm = blockForm[0].select('.page-repetable.visible')
            formContents.each(function(element) {
                if (element.hasAttribute('data-position')) {
                    if (element.readAttribute('data-position') == occurence && element.readAttribute('data-label') == currentForm[0].readAttribute('data-label')) {
                        element.show();
                        element.addClassName('visible');
                    } else {
                        element.hide();
                        element.removeClassName('visible');
                    }
                }
            })
        })
    })
});