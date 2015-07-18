

var Ice = require("ice").Ice;
var argo = require("./Ticker").argo;

var communicator;

Ice.Promise.try(
    function() {
        communicator = Ice.initialize(process.argv);
        console.log("Communicator is " + communicator);
        var proxy = communicator.stringToProxy("plant2:default -p 10003");
        console.log("About to ping");
        var x = proxy.ice_ping();
        //console.log("x is " + JSON.stringify(x));
        //proxy.fart();
        console.log("Pung him");
        return argo.TickerPlantPrx.checkedCast(proxy).then(
            function(x) {
                console.log("Called with x " + x );
            },
            function(ex) {
                console.log("Called with exception " + ex);
            } )
    } ).then(
        function() {
        },
        function(ex) {
            console.log(ex);
        }
    );

console.log("pung him");

