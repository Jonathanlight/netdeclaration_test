<?php

interface OperationDataProvider {

  public function getValues($imprime_code, $imprime_index, $field_code);
  public function ImprimeExists($imprime_code);      

}
