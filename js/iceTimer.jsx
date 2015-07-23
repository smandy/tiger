
var iid = new Ice.InitializationData();
iid.properties = Ice.createProperties();
iid.properties.setProperty("Ice.Default.Locator", "IceGrid/Locator:ws -h localhost -p 4063");
//iid.properties.setProperty("Ice.Trace.Protocol", "1");
var communicator = Ice.initialize([], iid);

var FooCaller = React.createClass({
    getInitialState: function(){
        //console.log("StrProxy is " + this.props.strProxy);
        var myPrx = communicator.stringToProxy(this.props.strProxy);
        var prx = argo.FooPrx.uncheckedCast(myPrx);
        // console.log("Checked is ");
        // console.log(prx);
        return { proxy : prx , counter : 0 };
    },

    componentDidMount: function(){
        // componentDidMount is called by react when the component 
        // has been rendered on the page. We can set the interval here:
        this.timer = setInterval(this.ping, 2000);
    },

    componentWillUnmount: function(){

        // This method is called immediately before the component is removed
        // from the page and destroyed. We can clear the interval here:

        clearInterval(this.timer);
    },


    mySetState : function(x) {
        //console.log("setstate");
        //console.log(x);
        this.setState(x);
        
    },
    
    ping : function(){
        // This function is called every 50 ms. It updates the 
        // elapsed counter. Calling setState causes the component to be re-rendered
        //this.setState({elapsed: new Date() - this.props.start});
        //console.log("Proxy is ");
        //console.log( this.state.proxy);
        var outer = this;
        Ice.Promise.try( function() {
            outer.state.proxy.doit().then(
                function(ret) {
                    //console.log("Success " + ret);
                    //console.log(outer);
                    //outer.mySetState( { foo : "Bar"} );
                    var newState = { status : "Success " + ret,
                                     proxy  : outer.state.proxy ,
                                     counter : outer.state.counter + 1,
                                     date : new Date() };
                    outer.mySetState(newState);
                    //console.log(newState);
                },
                function (ex) {
                    //console.log("Failure ");
                    //console.log(outer);
                    //outer.mySetState( { foo : "Bar"} );
                    outer.mySetState( { status : "Failure" + ret,
                                        proxy  : outer.state.proxy } );
                }
            );
        } ).exception( function (ex) {
            console.log(ex);
        } );
    },

    render: function() {
        //console.log( "Rendering");
        //console.log( this.state);
        //var secs = this.state.status;
        //console.log(secs);
        var d = new Date();
        return <p>This example was started <b>{this.state.status}</b> <b>{this.state.counter}</b> seconds ago. {d.toString} </p>;
    }
});


//var proxies = ["foo@SimpleCppApp","foo@SimpleJavaApp","foo@SimpleApp"];
React.render(
        <TimerExample start={Date.now()} />,
    document.getElementById("timer")
);

React.render(
        <FooCaller strProxy="foo@SimpleApp"/>,
    document.getElementById("simpleApp")
);

React.render(
        <FooCaller strProxy="foo@SimpleCppApp"/>,
    document.getElementById("simpleCppApp")
);

React.render(
        <FooCaller strProxy="foo@SimpleJavaApp"/>,
    document.getElementById("simpleJavaApp")
);





