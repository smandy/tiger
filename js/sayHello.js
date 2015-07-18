var Ice = require("ice").Ice;
var argo = require("./Foo").argo;

var myArgs = process.argv.slice(2);
console.log("Args is " + myArgs);

var id = new Ice.InitializationData();
id.properties = Ice.createProperties();
id.properties.setProperty("Ice.Default.Locator", "IceGrid/Locator:tcp -p 4061");

var communicator = Ice.initialize(myArgs, id);
console.log("Communicator is " + communicator);
var out = 3;

["foo@SimpleCppApp","foo@SimpleJavaApp","foo@SimpleApp"].forEach( function (x) {
    var proxy = communicator.stringToProxy(x).ice_timeout(5000);
    var x2 = argo.FooPrx.uncheckedCast(proxy).ice_timeout(5000).then(
    function(prx) {
        //console.log("Called with x " + prx );
        prx.doit().then(
            function (ret) {
                console.log("Ret is " + ret + " from " + x);
                out -= 1;
                if (out == 0 ) {
                    console.log("Shutting down");
                    communicator.shutdown();
                    process.exit(0);
                };
            },
            function (ex) {
                console.log(ex);
            }
        );
    },
    function(ex) {
        console.log("Called with exception " + ex);
    } );
});

//console.log("x is " + x2 );
console.log("Bong");

