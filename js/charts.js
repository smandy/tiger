angular.module('app').controller('MainCtrl', ['$scope', '$timeout', 'gliffy', 'DataService',  function ($scope, $timeout, gliffy, DataService) {
    $scope.gliffy = gliffy;
    $scope.messages = [ { counter : 0 } ];
    $scope.showRow1 = true;
    $scope.showRow2 = true;
    $scope.showRow3 = true;
    $scope.showEmitters  = false;
    $scope.showEmitters2 = false;
    $scope.showEmitters3 = false;
    
    $scope.emitters = {
        meh: true,
        dodgy : true,
        allIsWell : true,
        dodgy2 : false,
        lunch : true,
        earthQuake : true,
        disaster : true,
        flood : true,
        arb1: false,
        arb2: false,
        arb3: false,
        arb4: false
    };

    $scope.doit = function() {
        $scope.prx.sayHello().then( function(s) {
            console.log("Got " + s + " back from plant");
        });
    };
    
    $scope.emitterClass = function(b) {
        //console.log("Chpoink");
        var prefix = "well col-sm-3 div-150 ";
        return b ? prefix + "bg-green" : prefix + "bg-red";
    };
    
    $scope.options = {
        series: {
            lines: { show: true,
                     fill: false,
                     steps : true,
                     fillColor: "rgba(0, 255, 255, 0.25)" },
            points: { show: false, fill: false }
        },
        legend: {
            container: '#legend',
            show: true
        }
    };
    
    $scope.dataset = [{ data: DataService.ts1(),
                        backgroundColor : 'black',
                        color : 'cyan',
                        lineWidth : 1,
                        //yaxis: 1,
                        label: 'Woot' }];

    $scope.row3Dataset = [ { data: DataService.ts3(),
                             backgroundColor : 'black',
                             color : 'lightgreen',
                             steps : true,
                             lineWidth : 3,
                             //yaxis: 1,
                             label: 'Woot'} ];
    
    $scope.row3Options = {
        series: {
            lines: { show: true,
                     fill: false,
                     lineWidth : 2,
                     steps : true,
                     fillColor: "rgba(0, 255,0, 0.15)" },
            points: { show: false, fill: false }
        },
        legend: {
            container: '#legend',
            show: true
        }
    };

    $scope.row2Dataset = [{ data: DataService.ts2(),
                            backgroundColor : 'black',
                            color : 'red',
                            lineWidth : 3,
                            steps : true,
                            //yaxis: 1,
                            label: 'Woot' }];
    $scope.row2Options = {
        series: {
            lines: { show: true,
                     fill: false,
                     lineWidth : 3,
                     steps : true,
                     fillColor: "rgba(255, 0,0, 0.3)" },
            points: { show: false, fill: false }
        },
        legend: {
            container: '#legend',
            show: true
        }
    };
    
    $timeout( function() {

        console.log("Creating communicator");
        var communicator = Ice.initialize();

        var proxy = communicator.stringToProxy("plant:ws -h localhost -p 10666 -t 2000").ice_twoway();
        console.log("About to ping " + proxy);
        
        var x2 = argo.TickerPlantPrx.checkedCast(proxy).then(
            function(prx) {
                $scope.prx = prx;
                
                setInterval( function() {
                    prx.sayHello().then( function (s) {
                        //console.log("hello returned " + s );
                        //$("#greeting").html( "<H1>" + "Got " + s + "</H1>" );
                    } );
                } , 2000);
                
                return communicator.createObjectAdapter("").then(
                    function(adapter) {
                        var r = adapter.addWithUUID( new MyCallBackReceiver() );
                        proxy.ice_getCachedConnection().setAdapter(adapter);
                        var x3 = prx.subscribeWithIdent(r.ice_getIdentity());
                    }
                );
            },
            function(ex) {
                console.log("Called with exception " + ex);
            } );
        
        var MyCallBackReceiver = Ice.Class( argo.TickListener, {
            onTick : function(ticks, current) {
                console.log("OnTick");
                $scope.$apply( function() {
                    $scope.addPoint( ticks );
                });
            },

            onImage : function(image, current) {
                console.log("OnImage " + image.length);
                $scope.$apply( function() {
                    image.forEach( function(ticks) {
                        // TODO - efficiency!
                        $scope.addPoint( ticks );
                    } );
                });
            }
        });
        
        $scope.addPoint = function( ticks ) {
            DataService.addPoints( ticks[0].bidPx,
                                   ticks[1].bidPx,
                                   ticks[2].bidPx );
        };
    });
}]).factory( 'gliffy', [ function() {
    return function(msg) {
        if (msg.msgType=="pong") {
            return "glyphicon-chevron-left";
        } else {
            return "glyphicon-time";
        };
    };
} ] );;

