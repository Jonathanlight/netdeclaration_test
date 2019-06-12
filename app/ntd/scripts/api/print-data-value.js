$all_selects = $$('select.print-data-value');

if ($all_selects.length > 0) {
    $all_selects.each(
        function (select) {
            var $options_value = select.readAttribute('data-value');
            select.insert('<option selected="selected">' + $options_value + '</option>');
        }
    );
}
