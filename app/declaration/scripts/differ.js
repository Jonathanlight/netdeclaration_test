var differModule = angular.module('differModule', ['ui.router'],
                                  function($httpProvider) {
                                    // Use x-www-form-urlencoded Content-Type
                                    $httpProvider.defaults.headers.post['Content-Type'] = 'application/x-www-form-urlencoded;charset=utf-8';

                                    /**
                                     * The workhorse; converts an object to x-www-form-urlencoded serialization.
                                     * @param {Object} obj
                                     * @return {String}
                                     */
                                    var param = function(obj) {
                                      var query = '', name, value, fullSubName, subName, subValue, innerObj, i;

                                      for (name in obj) {
                                        value = obj[name];

                                        if (value instanceof Array) {
                                          for (i = 0; i < value.length; ++i) {
                                            subValue = value[i];
                                            fullSubName = name + '[' + i + ']';
                                            innerObj = {};
                                            innerObj[fullSubName] = subValue;
                                            query += param(innerObj) + '&';
                                          }
                                        }
                                        else if (value instanceof Object) {
                                          for (subName in value) {
                                            subValue = value[subName];
                                            fullSubName = name + '[' + subName + ']';
                                            innerObj = {};
                                            innerObj[fullSubName] = subValue;
                                            query += param(innerObj) + '&';
                                          }
                                        }
                                        else if (value !== undefined && value !== null)
                                          query += encodeURIComponent(name) + '=' + encodeURIComponent(value) + '&';
                                      }

                                      return query.length ? query.substr(0, query.length - 1) : query;
                                    };

                                    // Override $http service's default transformRequest
                                    $httpProvider.defaults.transformRequest = [function(data) {
                                      return angular.isObject(data) && String(data) !== '[object File]' ? param(data) : data;
                                    }];
                                  });

differModule.config(function($stateProvider, $urlRouterProvider) {
  $urlRouterProvider.otherwise("/");
  $stateProvider
    .state('home', {
             url: "/",
             templateUrl: "/decbdd.template/-/template/decbdd.home"
           })
    .state('model', {
             url: "model/:model",
             templateUrl: "/decbdd.template/-/template/decbdd.model",
             controller: 'ModelController'
           })
  ;
});

differModule.controller('mainController', function($scope, $http) {
  $http.get('/decbdd.models')
    .success(function(resp) {
               $scope.models = resp['result']['models'];
             });

});

differModule.controller('MenuController', function($scope, $state) {

});

differModule.controller('ModelController', function($scope, $stateParams, $http) {
  //$http.defaults.headers.post["Content-Type"] = "application/x-www-form-urlencoded";

  $scope.model = $stateParams.model;

  $scope.form = {
    page: 1,
    limit: 10,
    max_last_id: 0,
    max_next_increment_id: 0,
    max_item_id: 0
  };
  $scope.syncForm = {
    from_app: '',
    to_app: '',
    mode: 'sync',
    model: $scope.model
  };

  $scope.ids = Object.keys($scope.models[$scope.model]['items']) || [];
  $scope.selectedItemIds = {};

  $scope.getItems = function() {
    if ($scope.ids.length < 1) {
      console.log('aucun item');
      return;
    }
    var offset = $scope.form.limit * ($scope.form.page - 1);

    var ids = $scope.ids.slice(offset, offset + $scope.form.limit);
    $http.get('/decbdd.model'
              + '?model=' + $scope.model
              + '&page=' + $scope.form.page
              + '&ids[]=' + ids.join('&ids[]='))
      .success(function(resp) {
                 $scope.selectedItemIds = {};
                 console.log(resp);
                 var result = resp.result;
                 $scope.reference_app = result.reference_app;
                 $scope.apps = result.apps;
                 $scope.rows = result.rows;

                    for (var rowIndex in $scope.rows) {
                      for (var fieldIndex in $scope.rows[rowIndex]['fields']) {
                        var field =$scope.rows[rowIndex]['fields'][fieldIndex];
                        for(var appIndex in $scope.apps) {
                          var app = $scope.apps[appIndex];
                          $scope.rows[rowIndex]['values'][app][field]['difference'] = $scope.getDiff($scope.rows[rowIndex]['values'][$scope.reference_app][field]['value'],
                                                                                                     $scope.rows[rowIndex]['values'][app][field]['value']);
                        }
                      }
                    }
               });
  };

  $scope.getDiff = function(base, newtxt) {
    if (typeof base != "string") {
      base = JSON.stringify(base);
    }
    if (typeof newtxt != "string") {
      newtxt = JSON.stringify(newtxt);
    }

    var dmp = new diff_match_patch();

    var a = dmp.diff_linesToChars_(base, newtxt);
    var lineText1 = a.chars1;
    var lineText2 = a.chars2;
    var lineArray = a.lineArray;

    var diffs = dmp.diff_main(lineText1, lineText2, false);
    dmp.diff_charsToLines_(diffs, lineArray);

    return diffs;
  };

  $scope.checkAll = function() {
    $scope.selectedItemIds = {};
    for (var i = 0; i < $scope.rows.length; i++) {
      $scope.selectedItemIds[$scope.rows[i].id] = true;
    }
  };
  $scope.getCheckums = function() {
    $http.get('/decbdd.checksums'
              + '?model=' + $scope.model)
      .success(function(resp) {
                 var result = resp.result;
                 $scope.models[$scope.model] = result['checksums'];
                 $scope.ids = Object.keys($scope.models[$scope.model]['items']) || [];
                 $scope.getItems();
               });

  };

  $scope.onLimitChange = function() {
    $scope.setFormPage(1);
  };
  $scope.setFormPage = function(page) {
    $scope.form.page = Math.max(1, Math.min(page, Math.ceil($scope.ids.length / $scope.form.limit)));
    $scope.getItems();
  };

  $scope.onFormSyncItemsSubmit = function() {
    if (!confirm('êtes-vous sûr ?')) {
      return false;
    }
    $scope.syncForm.ids = [];
    for (var id in $scope.selectedItemIds) {
      if ($scope.selectedItemIds[id]) {
        $scope.syncForm.ids.push(id);
      }
    }

    if ($scope.syncForm.ids.length < 1) {
      alert('aucun Item sélectionné');
      return false;
    }
    var modal = $('#modal--main').modal();
    $http.post('/decbdd.item.sync', $scope.syncForm)
      .success(function(data) {
                 modal.find('.modal-title').text('Result');
                 modal.find('.modal-body').html(data);
                 modal.show();
               }
    );
  };


  $scope.getItems();
});

differModule.filter('getPropertiesCount', function() {
                      return function(input) {
                        return Object.keys(input).length;
                      }
                    }
);
