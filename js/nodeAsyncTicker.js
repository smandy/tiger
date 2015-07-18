var Ice = require("ice").Ice;
var argo = require("./Ticker").argo;

var myArgs = process.argv.slice(2);
console.log("Args is " + myArgs);
var communicator = Ice.initialize(myArgs);
console.log("Communicator is " + communicator);

var MyCallBackReceiver = Ice.Class( argo.TickListener, {
    onTick : function( ticks, current) {
        ticks.forEach( function(x) { console.log(x); } );
    }
} );

var proxy = communicator.stringToProxy("plant:tcp -p 10667 -t 2000").ice_twoway();
console.log("About to ping " + proxy);

var x2 = argo.TickerPlantPrx.checkedCast(proxy).then(
    function(prx) {
        console.log("Called with x " + prx );
        return communicator.createObjectAdapter("").then(
            function(adapter) {
                var r = adapter.addWithUUID( new MyCallBackReceiver() );
                proxy.ice_getCachedConnection().setAdapter(adapter);
                console.log("Subscribing!");
                var x3 = prx.subscribeWithIdent(r.ice_getIdentity());
                //console.log(x3);
                console.log("It worked");
            }
        );
    },
    function(ex) {
        console.log("Called with exception " + ex);
    } );

console.log("x is " + x2 );
console.log("Bong");

