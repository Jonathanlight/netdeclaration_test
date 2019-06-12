<?php

class Millesime extends ActiveRecord {

  public function getFormulairetypes() {
    return S('dbo')->query('SELECT f.*'
                          .' FROM ' . Formulairetype::TABLE_MILLESIME . ' fm'
                          .' JOIN ' . T('formulairetype') . ' f ON fm.formulairetype_id=f.id'
                          .' WHERE millesime_id=' . $this->getId())
                  ->asCollection('formulairetype');
  }

  public function asEditHash() {
    $hash = array();

    $hash['formulairetypes'] = array();
    $ftypes = Formulairetype::collect(array('filters' => array('|!&|flags' => Formulairetype::FLAG_OLD_SYSTEM),
                                            'order' => array('code' => 'ASC')));
    foreach ($ftypes as $ftype) {
      $hash['formulairetypes'][$ftype->getId()] = $ftype->code . ' : ' . implode(', ', $ftype->getMillesimes()->asSet('id'));
    }

    $hash['formulairetypes_belongs'] = array();
    if ($this->isLoaded()) {
      $hash['formulairetypes_belongs'] = $this->getFormulairetypes()->asSet('id');

      $formulairetypes_presents = array();
      foreach ($hash['formulairetypes_belongs'] as $ftype_id) {
        $ftype = $ftypes->getItemID($ftype_id);
        if (empty($ftype)) continue;
        $formulairetypes_presents['Famille ' . substr($ftype->code, 0, 4)][] = Item::edit($ftype);
      }
      ksort($formulairetypes_presents);
      $index = 1;
      $count = 0;
      foreach ($formulairetypes_presents as $key => $ftypes) {

        $hash['formulairetypes_present' . $index][$key] = implode('<br>', $ftypes);
        $count += count($ftypes);

        if ($count > 30 && $index < 5) {
          $count = 0;
          $index++;
        }
      }
      $hash['older_millesimes'] = Millesime::collect(array('filters' => array('|!=|id' => $this->getId())));
    }
    return $hash;
  }

  protected function onBeforeCommit(&$attrs) {

    if ($attrs['mode'] == 'edit') {
      if ($this->getId() == 1) throw new Exception('Millesime ID[1] can"t be modified');
      if ($attrs['millesime'] < 1) throw new Exception('Ancien Millesime obligatoire');

      foreach ($attrs['formulairetypes'] as $ftype_id) {
        $ftype = Formulairetype::getInstance($ftype_id);
        $ftype->duplicateMillesime($this->getId(), $attrs['millesime']);
      }

      unset($attrs['formulairetypes']);
      unset($attrs['millesime']);
      unset($attrs['mode']);
    }

  }

}
