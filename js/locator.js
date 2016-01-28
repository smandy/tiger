console.log("Loading");

var iid = new Ice.InitializationData();
iid.properties = Ice.createProperties();
iid.properties.setProperty("Ice.Default.Locator", "IceGrid/Locator:ws -h localhost -p 4063");
//iid.properties.setProperty("Ice.Trace.Protocol", "1");
var proxies = ["foo@SimpleCppApp","foo@SimpleJavaApp","foo@SimpleApp"];
var communicator = Ice.initialize([], iid);

console.log("Woot");

proxies.forEach( function (x) {
    var proxy = communicator.stringToProxy(x).ice_timeout(60000);
    var x2 = argo.FooPrx.checkedCast(proxy).then(
        function(prx) {
            prx.ice_timeout(60000).doit().then(
                function (ret) {
                    console.log("Beep");
                    $("#main").append("<H3>Ret is " + ret + " from " + x + "</H3>");
                },
                function (ex) {
                    console.log(ex);
                }
            );
        },
        function(ex) {
            console.log("Called with exception " + ex);
            console.log(ex);
        } );
});
