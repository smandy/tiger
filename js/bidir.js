var grid;
var data = [];
var options = {
    editable: false,
    enableAddRow: false,
    enableCellNavigation: true,
    enableColumnReorder : false
};

console.log("Bidir loading");

var columns = [
    {id : "symbol", name: "Symbol", field: "symbol", width: 180},
    {id : "bidPx",  name: "Bid", field: "bidPx", width: 180},
    {id : "askPx",  name: "Ask", field: "askPx", width: 180},
    {id : "bidDirection",  name: "BD", field: "bidDirection", width: 180},
    {id : "askDirection",  name: "AD", field: "askDirection", width: 180},
];

grid = new Slick.Grid("#myGrid", data, columns, options);
var communicator = Ice.initialize();

var MyCallBackReceiver = Ice.Class( argo.TickListener, {
    onImage : function( img, currnet) {
        if (img.lenth>0) {
            img[0].forEach( function( tick, idx, _) {
                data[idx] = tick;
                grid.invalidateRow(idx);
            });
        };
    },
    
    onTick : function( ticks, current) {
        //$("#symbol").html("<pre>" + ticks[0]['symbol'] + "</pre>");
        //$("#bid").html("<pre>" + ticks[0]['bidPx'] + "</pre>");
        //$("#ask").html("<pre>" + ticks[0]['askPx'] + "</pre>");
        for (i = 0;i<ticks.length;i++) {
            data[i] = ticks[i];
            grid.invalidateRow(i);
        }
        grid.render();
    }
} );

var proxy = communicator.stringToProxy("plant:ws -h ritz -p 10666 -t 2000").ice_twoway();
console.log("About to ping " + proxy);

var x2 = argo.TickerPlantPrx.checkedCast(proxy).then(
    function(prx) {
        setInterval( function() {
            prx.sayHello().then( function (s) {
                //console.log("hello returned " + s );
                $("#greeting").html( "<H1>" + "Got " + s + "</H1>" );
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

