var Ice = require("ice").Ice;
var argo = require("./Foo").argo;

var myArgs = process.argv.slice(2);
console.log("Args is " + myArgs);

var id = new Ice.InitializationData();
id.properties = Ice.createProperties();

id.properties["Ice.Default.Locator"] = "IceGrid/Locator:tcp -p 4061";

var communicator = Ice.initialize(myArgs, id);
console.log("Communicator is " + communicator);

var proxy = communicator.stringToProxy("sayHello@SimpleCppApp");
console.log("About to ping " + proxy);

var x2 = argo.FooPrx.checkedCast(proxy).then(
    function(prx) {
        console.log("Called with x " + prx );
        prx.doit().then(
            function (ret) {
                console.log("Ret is " + ret);
            },
            function (ex) {
                console.log(ex);
            }
        );
    },
    function(ex) {
        console.log("Called with exception " + ex);
    } );

console.log("x is " + x2 );
console.log("Bong");

