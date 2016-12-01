// Ionic Starter App

// angular.module is a global place for creating, registering and retrieving Angular modules
// 'starter' is the name of this angular module example (also set in a <body> attribute in index.html)
// the 2nd parameter is an array of 'requires'
var app = angular.module('starter', ['ionic', 'firebase'])

.run(function($ionicPlatform) {
    $ionicPlatform.ready(function($scope) {
        if (window.cordova && window.cordova.plugins.Keyboard) {
            // Hide the accessory bar by default (remove this to show the accessory bar above the keyboard
            // for form inputs)
            cordova.plugins.Keyboard.hideKeyboardAccessoryBar(true);

            // Don't remove this line unless you know what you are doing. It stops the viewport
            // from snapping when text inputs are focused. Ionic handles this internally for
            // a much nicer keyboard experience.
            cordova.plugins.Keyboard.disableScroll(true);
        }
        if (window.StatusBar) {
            StatusBar.styleDefault();
        }
    });
})

.config(function() {
    var config = {
        apiKey: "AIzaSyCO7Gf1jRsrLZpJDG0G9BmC4ZXlxdYwswg",
        authDomain: "digital-project-60005.firebaseapp.com",
        databaseURL: "https://digital-project-60005.firebaseio.com",
        storageBucket: "digital-project-60005.appspot.com",
        messagingSenderId: "107199148627"
    };
    firebase.initializeApp(config);
})

app.controller('IndexCtrl', function($scope, $firebaseObject) {

    var ref = firebase.database().ref();
    var obj = $firebaseObject(ref);
    $scope.data = {
        "temp": 30,
        "moisture": 80
    }
    $scope.originalt = {
        "temp": 30,
        "moisture": 80
    }

    data ={
      "range": 0
    };

    $scope.text="";
    $scope.settext = function() {
      if($scope.data.range==0){
        $scope.text2="ปิด";
      }else if ($scope.data.range<=15) {
        $scope.text2="auto";
      }else if ($scope.data.range<=24) {
        $scope.text2="ระดับที่ 1";
      }else if ($scope.data.range<=50) {
        $scope.text2="ระดับที่ 2";
      }else if ($scope.data.range<=75) {
        $scope.text2="ระดับที่ 3";
      }else if ($scope.data.range<=100) {
        $scope.text2="ระดับที่ 4";
      }

      $scope.text = angular.copy($scope.text2);

    }

    // reset temp and moisture
    $scope.reset = function() {
        $scope.data = angular.copy($scope.originalt);
        //$scope.myForm.$setPristine();
        console.log($scope.data);
    }

    // set temp and moisture
    $scope.set = function() {
        console.log($scope.data);
    }

    // toggle
    $scope.value1 = false;
    $scope.value2 = false;
    $scope.value3 = false;
    $scope.value4 = false;
    $scope.value1o = false;
    $scope.value2o = false;
    $scope.value3o = false;
    $scope.value4o = false;

    $scope.toggleChange1 = function() {
        if ($scope.value1 == false) {
            $scope.value1 = true;
            $scope.value2 = angular.copy($scope.value2o);
            $scope.value3 = angular.copy($scope.value3o);
            $scope.value4 = angular.copy($scope.value4o);
        } else {
            $scope.value1 = false;
        }
        console.log('testToggle 1 changed to ' + $scope.value1);
    };

    $scope.toggleChange2 = function() {
        if ($scope.value2 == false) {
            $scope.value2 = true;
            $scope.value1 = angular.copy($scope.value1o);
            $scope.value3 = angular.copy($scope.value3o);
            $scope.value4 = angular.copy($scope.value4o);
        } else {
            $scope.value2 = false;
        }
        console.log('testToggle 2 changed to ' + $scope.value2);
    };

    $scope.toggleChange3 = function() {
        if ($scope.value3 == false) {
            $scope.value3 = true;
            $scope.value1 = angular.copy($scope.value1o);
            $scope.value2 = angular.copy($scope.value2o);
            $scope.value4 = angular.copy($scope.value4o);
        } else {
            $scope.value3 = false;
        }
        console.log('testToggle 3 changed to ' + $scope.value3);
    };

    $scope.toggleChange4 = function() {
        if ($scope.value4 == false) {
            $scope.value4 = true;
            $scope.value1 = angular.copy($scope.value1o);
            $scope.value2 = angular.copy($scope.value2o);
            $scope.value3 = angular.copy($scope.value3o);
        } else {
            $scope.value4 = false;
        }
        console.log('testToggle 4 changed to ' + $scope.value4);
    };


    obj.$bindTo($scope, "data");

});
