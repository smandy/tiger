var iid = new Ice.InitializationData();
iid.properties = Ice.createProperties();
iid.properties.setProperty("Ice.Default.Locator", "IceGrid/Locator:ws -h localhost -p 4063");

var communicator = Ice.initialize([], iid);

var FooCaller = React.createClass({
    getInitialState: function() {
        var myPrx = communicator.stringToProxy(this.props.strProxy);
        var prx = argo.FooPrx.uncheckedCast(myPrx);
        return { proxy : prx ,
                 strProxy : this.props.strProxy,
                 counter : 0 };
    },
    componentDidMount: function() {
        this.timer = setInterval(this.ping, 2000);
    },
    componentWillUnmount: function(){
        clearInterval(this.timer);
    },
    mySetState : function(x) {
        this.setState(x);
    },
    ping : function() {
        var outer = this;
        outer.state.proxy.doit().then(
            function(ret) {
                var newState = outer.state;
                newState.counter = newState.counter + 1;
                newState.date = new Date();
                newState.status = "Success " + ret;
                outer.mySetState(newState);
            },
            function (ex) {
                var state = outer.state;
                state.status = "Failure " + ret;
                outer.mySetState( state );
            }
        );
    },
    render: function() {
        var d = new Date();
        return <p>{this.state.strProxy} ret="{this.state.status}" {this.state.counter}  {d.toString()}</p>;
    }
});

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
