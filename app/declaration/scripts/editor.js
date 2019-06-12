if (!declaration) var declaration = {};

declaration.EditorObj = null;

declaration.Editor = Class.create({
  "editor": null,
  "dialog": null,
  "input": null,
  "container": null,
  "selected": null,
  "selected_node": null,
  "selection": [],
  "can_save": true,
  "history": true,
  "data_elt": null,
  "copied": [],
  "histories" : [],
  "last_history": 0,
  "max_history": 20,
  "initialize": function(elt) {  
    declaration.EditorObj = this;  
    var that = this;
    this.input =  $(elt);
    this.container = this.input.up('.form-editor');
    this.editor    = this.container.down(".editor-content");
    this.onBind();
  },
  "onBind": function() {
    var that = this;
    this.container.select('.item-model').each(function(item) {  
      item.observe("click", that.onModelClick.bindAsEventListener(that, item));
      item.observe("dragstart", that.onDrag.bindAsEventListener(that, item));
    });    
    this.container.down('.model-new').observe("click", that.onModelEdit.bindAsEventListener(that).curry(null));
    this.container.down('.row-duplicate').observe("click", that.onRowDuplicate.bindAsEventListener(that).curry(null));
    this.container.down('.row-delete').observe("click", that.onRowDelete.bindAsEventListener(that).curry(null));
    this.container.down('.cell-merge').observe("click", that.onCellsMerge.bindAsEventListener(that));
    this.container.down('.cell-split').observe("click", that.onCellSplit.bindAsEventListener(that));
    this.container.down('.page-add').observe("click", that.onPageAdd.bindAsEventListener(that));
    this.container.down('.table-add').observe("click", that.onTablePrompt.bindAsEventListener(that));    
    this.container.down('.table-delete').observe("click", that.onTableDelete.bindAsEventListener(that)); 
    this.container.down('.row-extensible').observe("click", that.onRowExtensible.bindAsEventListener(that));
    this.onBindEditor(true);
  },
  "onBindEditor": function(init) {
    var init = init || false;
    var that = this;
    this.editor.select('table').each(function(table) { 
      table.observe("drop", that.onDrop.bindAsEventListener(that, table)); 
    });
    this.editor.select('.item-model-data').each(function(item) {  
      item.observe("click", that.onModelDataClick.bindAsEventListener(that, item));
    });      
    if (init) {
      this.editor.observe("click", that.onItemSelect.bindAsEventListener(that));
      this.editor.observe("keydown", that.onKeyDown.bindAsEventListener(that));
      this.editor.observe("input", that.onChange.bindAsEventListener(that));
      this.editor.observe("DOMNodeInserted", that.onChange.bindAsEventListener(that));
      this.editor.observe("DOMNodeRemovedFromDocument", that.onSelect.bindAsEventListener(that));    
      this.editor.observe("mousemove", that.onSelect.bindAsEventListener(that));
    } 
  },
  "onDrag": function(event, elt) {
    event.dataTransfer.effectAllowed = 'move';
    event.dataTransfer.setData('text', elt.getAttribute('data-item'));
  },
  "onDrop": function(event, elt) {
    event.stopPropagation();
    event.preventDefault();
    this.onItemSelect(event);
    this.onModelDataEdit(event.dataTransfer.getData('text'));
    return false;
  },
  "onSelect": function() {
    var selection = window.getSelection();
    if (selection.rangeCount <= 0) return;   
    this.selection = []; 
    for (i=0; i<selection.rangeCount; i++) {
      var range  = selection.getRangeAt(i);   
      var parent = $(range.startContainer);
      if (!parent) return;
      if (parent.tagName != 'TR') return;
      var cell = parent.select('td')[range.startOffset]; 
      this.selection[this.selection.length] = {'parent':parent, 'cell': cell};
    }
  },
  "onCopy": function(event) {   
    this.copied = this.selection;
  },
  "onPaste": function(event) {
    if (this.selected.tagName != 'TD' || this.copied.length <= 0) return;
    var parent = this.selected.up('tr');
    var that   = this;
    var copied = [];
    this.copied.each(function(obj) {
      if (copied.indexOf(obj.parent) == -1 ) {        
        var clone = obj.parent.clone(true);       
        parent.insert({after: clone});
        clone.select('.item-model-data').each(function(item) {  
          that.onModelInit(item);
        });             
        parent = clone;
        copied.push(obj.parent);
      }
    });
    this.copied = [];
    this.onChange();
  },
  "onUndo": function(event) {
    if (this.last_history < 0 || this.histories.length == 0) return;
    var value = this.histories[this.last_history];       
    if (this.last_history > 0) this.last_history--;
    this.input.value = value;
    this.history = false;
    this.editor.update(value);    
    this.onStore();  
    this.onBindEditor(); 
    this.history = true;
  },
  "onRedo": function(event) {
    if (this.last_history >= this.histories.length) return;
    var value = this.histories[this.last_history];     
    if (this.last_history+1 < this.histories.length) this.last_history++;        
    this.history = false;
    this.input.value = value;
    this.editor.update(value);    
    this.onStore();  
    this.onBindEditor();
    this.history = true; 
  },
  "onKeyDown": function(event) {
    var key = String.fromCharCode(event.which).toLowerCase();
    if (event.ctrlKey && (key == 'c' || key == 'v' || key == 'z' || key == 'y')) {
      event.preventDefault();
      event.stopPropagation();
      switch(key) {
        case 'c':
         this.onCopy(event);
        break; 
        case 'v':
         this.onPaste(event);
        break; 
        case 'z':
         this.onUndo(event);
        break; 
        case 'y':
         this.onRedo(event);
        break; 
      }    
      return false;
    } 
  },  
  "onRowDuplicate": function() {
    if (this.selected.tagName != 'TD') return;   
    var that   = this;
    var parent = this.selected.up('tr');
    var body   = parent.up('tbody');
    if (body.up('table').hasAttribute('data-manager')) return;
    var number = prompt("Nombre de copies :", "1");
    if (number != null) {     
      for (i=1; i<=number; i++) {
        var clone = parent.clone(true);
        parent.insert({after: clone});
        clone.select('.item-model-data').each(function(item) {  
          that.onModelInit(item);
        });
        clone.select('.selected').invoke('removeClassName', 'selected');
      }
    }
  },
  "onRowDelete": function() {
    if (this.selected.tagName != 'TD') return;   
    if (this.selected.up('tbody').select('tr').length == 1) {
      this.selected.up('table').remove();
    }
    else {
      this.selected.up('tr').remove();
    }
    this.onChange();
  },
  onRowExtensible: function(){
    if (this.selected.tagName != 'TD') {
      alert('Sélectionnez une cellule de tableau');
      return;
    }
    var row = this.selected.up('tr');
    if (!confirm('Cette ligne est extensible ?')) {
      row.writeAttribute('row_options', row.readAttribute('row_options').replace('extensible', ''));
      row.writeAttribute('data-extensible_code', null);
    }
    else{

      var extensibleCode =  Number(prompt('Code la ligne extensible (1, 2, 3, ...)'));
      if(isNaN(extensibleCode)) {
        alert('Erreur, merci de saisir un nombre entier.');
        return;
      }
      var extensibleMax = Number(prompt('Nombre maximum de fois extensible (0 = illimité)'));
      if (isNaN(extensibleMax)) {
          alert('Erreur, merci de saisir un nombre entier.');
      }
      row.writeAttribute('row_options', 'extensible');
      row.writeAttribute('data-extensible_code', extensibleCode);
      row.writeAttribute('data-extensible_max', extensibleMax);
    }
    this.onStore();
  },
  "onModelInit": function(model) {
    model.observe("click", this.onModelDataClick.bindAsEventListener(this, model));
    model.setAttribute('data', '');
    model.down('.data').update('');
    model.select('.LB, .IMP, .FD input').invoke('update', '');
    model.select('.FD input').invoke('setValue', '');
  },
  "onModelEdit": function(model) {
    var model_id = model && model.hasAttribute('data-item') ? model.getAttribute('data-item') : 0;
    this.dialog = new Kwo.Dialog('/middle/core/editor.model', {model_id: model_id}, {width:1000, height:300});
  },
  "onModelStore": function(args) {
    Kwo.exec('/middle/core/editor.model.store', args, {callback: this.onModelStoreCallback.bind(this)});
  },
  "onModelStoreCallback": function(res) {
    if (Kwo.hasError(res)) return Kwo.error(res);
    var that = this; 
    var container = this.container.down('.editor-models div'); 
    Kwo.exec('/middle/core/editor.models', {selected: res['result']['model_id']}, {callback: function(res){
      container.update(res['result']['html']);
      container.select('.item-model').each(function(item) {  
        item.observe("click", that.onModelClick.bindAsEventListener(that, item));
        item.observe("dragstart", that.onDrag.bindAsEventListener(that, item));
      });
      that.dialog.close(); 
      if (that.selected) that.selected.focus();
    }});  
  },
  "onModelColsChange": function(elt) {
    var max = $(elt).value;
    var i   = 0;
    $('model-cols').select('.model-col').each(function(tr) {
      if (i >= max) {
        tr.hide().select('select, input').invoke('setAttribute', 'disabled', 'disabled');
      }
      else {
        tr.show().select('select, input').invoke('removeAttribute', 'disabled');
      }
      i++;
    });
  },
    "onTableDelete": function() {
    if (this.selected.tagName != 'TD') return;
    this.selected.up('table').remove();
  },
  "onModelClick": function(event, model) {  
    var item = event.target;
    if (item.hasClassName('delete-btn')) {
      return this.onModelDelete(model);
    }
    else if (item.hasClassName('edit-btn')) {
      return this.onModelEdit(model);
    }
    if (this.selected.tagName != 'TD') return;
    this.onModelDataEdit(model);
  },
  "onModelDataClick": function(event, model) { 
    var item = event.target;
    if (item.hasClassName('delete-btn')) {
      model.remove();
      return this.onChange();
    }
    this.onModelDataEdit(model);
  },
  "onModelDataEdit": function(model) {
    var itemplateId = this.container.down('input[name=itemplate_id]').value;
    this.data_elt = typeof model == 'object' ? model : null;
    var data = this.data_elt && this.data_elt.hasAttribute('data') ? this.data_elt.getAttribute('data') : null;    
    var opts = this.data_elt && this.data_elt.hasAttribute('opts') ? this.data_elt.getAttribute('opts') : null;
    this.dialog = new Kwo.Dialog('/middle/core/editor.model.data',
                                 { model_id: typeof model != 'object' ? model : model.getAttribute('data-item'),
                                   'itemplate_id': itemplateId,
                                   'data': data,
                                   'opts': opts}, 
                                 {width:1000, height:550});
  },
  "onModelDataInsert": function(args) {
    var that = this;
    Kwo.exec('/middle/core/editor.model.insert', args, {callback: function(res) {
      var replace = that.data_elt && that.data_elt.hasClassName('item-model-data') ? that.data_elt : null;
      var model   = replace ? replace : document.createElement('div');
      model.setAttribute('contenteditable', false); 
      model.setAttribute('data-item', res['result']['id']); 
      model.setAttribute('data', res['result']['data']);
      model.setAttribute('opts', res['result']['opts']);
      model.addClassName('item-model-data');
      model.update(res['result']['model']);

      if (!replace) {
        that.onItemAdd(model);
        model.observe("click", that.onModelDataClick.bindAsEventListener(that, model)); 
        that.data_elt = null;
      }

      //model.up('tr').setAttribute('row_options', res['result']['row_options']);

      that.onStore();

      that.dialog.close(); 
      if (that.selected) that.selected.focus();  
    }});
  },
  "onModelDelete": function(elt) {
    var id = elt.getAttribute('data-item');
    Kwo.exec('/middle/core/editor.model.delete', {model_id: id}, {callback: this.onModelDeleteCallback.curry(elt), confirm: "Etes vous sûr de vouloir supprimer ce modèle ?"});
  },
  "onModelDeleteCallback": function(elt, res) {
    if (Kwo.hasError(res)) return Kwo.error(res);
    elt.remove();
  },
  "onTablePrompt": function() {
    if (!this.selected || !this.selected.hasClassName('editor-page')) return alert("Veuillez ajouter/sélectionner une page !");
    this.dialog = new Kwo.Dialog('/middle/core/editor.table', null, {width:650, height:400});
  },
  "onTableInsert": function(args) {
    var that = this;
    Kwo.exec('/middle/core/editor.table.insert', args, {callback: function(res) {
      var table = document.createElement('table');     
      table.setAttribute('_moz_resizing', true); 
      table.update(res['result']['body']);  
      /*if (res['result']['extensible']) {
        table.setAttribute('data-manager', 'ExtensibleTableManager'); 
      } */
      that.onItemAdd(table); 
      table.observe("drop", that.onDrop.bindAsEventListener(that, table));
      that.dialog.close();
      if (that.selected) that.selected.focus();
    }});
  },
  "onPageAdd" : function() {
    var that = this;
    var page = document.createElement('div');
    page.setAttribute('contenteditable', true); 
    page.setAttribute('class', 'editor-page'); 
    this.editor.appendChild(page);  
    page.observe("click", that.onItemSelect.bindAsEventListener(that).curry(page));
  },
  "onItemAdd": function(item) {
    if (this.selected) {
      if (this.selected.innerHTML == '<br type="_moz">' || this.selected.innerHTML == '<br>') this.selected.update(item);
      else {
        if (item.tagName == "TABLE") {
          if (this.selected_node) this.selected_node.insert({after: item});
          else this.selected.appendChild(item);
          this.selected.insert('<br type="_moz">');          
        }
        else {
          this.selected.appendChild(item);
        }
      }
    }
    else this.editor.appendChild(item); 
  },
  "onItemSelect": function(event) {   
    var item = event.target;
    if (!item) return;
    if (item.tagName != 'TD' && item.tagName != 'DIV') return;
    this.editor.select('.selected').invoke('removeClassName', 'selected');
    item.addClassName('selected');
    this.selected = item;    
    if (window.getSelection) {
      var selected_obj   = window.getSelection();      
      var selected_range = selected_obj.getRangeAt(0); 
      if (selected_range.commonAncestorContainer.hasClassName('editor-page')) {  
        this.selected_node = selected_range.commonAncestorContainer.childNodes[selected_range.endOffset];
      }
      else {
        this.selected_node = null;
      }
    }
  },
  "onChange": function() {    
    var value = this.onParse();
    if (value == this.input.value) return;
    if (this.history) {
      if (this.histories.length >= this.max_history) {
        this.onShiftHistory();
      }
      this.last_history = this.histories.length == 0 ? 0 : this.histories.length-1;
      this.histories[this.last_history] = this.input.value;    
      this.last_history++;
      this.histories[this.last_history] = value;
    }   
    this.input.value = value;
    this.onStore.bind(this).delay(1);
  },
  "onShiftHistory": function() {
    for (var i=0; i<this.histories.length-1; i++) {
      this.histories[i] = this.histories[i+1]; 
    }
    this.histories = this.histories.splice(0, this.histories.length-1);
  },
  "onClear": function() {
    this.editor.update('');
    //this.onChange();
  },
  "onParse": function() {
    return this.editor.innerHTML; 
  }, 
  "onStore": function() {
    if (!this.can_save) return;
    this.can_save = false;
    this.container.down('textarea').value = this.editor.innerHTML;
    var args = this.container.up('form');
    Kwo.exec('/middle/core/editor.render', args, {callback: this.onStoreCallback.bind(this)});
  },
  "onStoreCallback": function(res) {
    this.can_save = true;
    if (Kwo.hasError(res)) return Kwo.error(res);
    if ($$('.rendre-html')['0']) $$('.rendre-html')['0'].innerHTML = res['result']['html'];
    if ($$('.rendre-code')['0']) $$('.rendre-code')['0'].innerHTML = res['result']['code'];
  },
  "getCursorObjectParent": function() {
    if (window.getSelection) {
      var selected_obj    = window.getSelection();      
      var selected_anchor = selected_obj.anchorNode;
      return $(selected_anchor);
    }
    return null;
  },
  "findNode": function (list, node) {
    for (var i = 0; i < list.length; i++) {
      if (list[i] == node) {           
        return i;
      }
    }
    return -1;
  },
  "onCellSplit": function() {
    if (this.selection.length <= 0) return;
    this.selection.each(function(obj) {     
      var cols     = parseInt(obj.cell.getAttribute('colspan'));
      var rows     = parseInt(obj.cell.getAttribute('rowspan'));
      var parent   = obj.parent;
      var index    = 0;
      var previous = obj.cell;
      while(previous.previous('td')) {
        previous = previous.previous('td');
        index++;
      }
      for (var row=1; row<=rows; row++) {
        var cells = "";
        for (var col=1; col<=cols; col++) {
          if (col!=1 || row!=1) cells += "<td></td>";
        }
        if (row == 1) obj.cell.insert({after: cells});
        else if (index > 0) {
          parent.select('td')[index-1].insert({after: cells});
        }
        else {
          parent.select('td')[0].insert({before: cells});
        }
        parent = parent.next();
      }
      obj.cell.removeAttribute('colspan'); 
      obj.cell.removeAttribute('rowspan');
    });
  },
  "onCellsMerge": function() {
    if (this.selection.length <= 0) return;
    var m_cell = last_parent = first_parent = null;
    var rows = cols = 1;
    this.selection.each(function(obj) {
      if (!first_parent) {
        m_cell = obj.cell;
        first_parent = obj.parent;
        if (m_cell.hasAttribute('colspan')) cols = parseInt(m_cell.getAttribute('colspan'));
        if (m_cell.hasAttribute('rowspan')) rows = parseInt(m_cell.getAttribute('rowspan'));
      }
      else {
        if (first_parent == obj.parent) {
          cols += obj.cell.hasAttribute('colspan') ? parseInt(obj.cell.getAttribute('colspan')) : 1;
        }
        else if (last_parent != obj.parent) {
          rows += obj.cell.hasAttribute('rowspan') ? parseInt(obj.cell.getAttribute('rowspan')) : 1;
        }
        obj.cell.remove();
      }
      last_parent = obj.parent;
    });
    m_cell.setAttribute('colspan', cols);
    m_cell.setAttribute('rowspan', rows);
    this.selection = [];
    this.onChange();
  }
});


declaration.Tabs = Class.create({
  "callback": null,
  "tabs":null,
  "initialize": function (elt) {
    var that = this;
    this.tabs = $(elt);
    this.tabs.down('.tabs-nav').select('a').each(function (el) { 
      if (!el.hasClassName('selected') && $(el.getAttribute('rel'))) {
        $(el.getAttribute('rel')).hide();
      }
      $(el).observe('click', that.onSelect.bind(that).curry(el)); 
    });
  },
  "onSelect": function(elt) {
    if (!$(elt.getAttribute('rel'))) return;
    this.tabs.down('.tabs-nav').select('a.selected').invoke('removeClassName', 'selected');
    this.tabs.down('.tabs-content').childElements().invoke('hide');
    elt.addClassName('selected');
    $(elt.getAttribute('rel')).show();
    if ($(elt).hasClassName('hide-actions')) {
      this.tabs.select('.actions').invoke('hide');
    }
    else {
      this.tabs.select('.actions').invoke('show');
    }
  }
});
