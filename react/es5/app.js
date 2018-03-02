var _createClass = function () { function defineProperties(target, props) { for (var i = 0; i < props.length; i++) { var descriptor = props[i]; descriptor.enumerable = descriptor.enumerable || false; descriptor.configurable = true; if ("value" in descriptor) descriptor.writable = true; Object.defineProperty(target, descriptor.key, descriptor); } } return function (Constructor, protoProps, staticProps) { if (protoProps) defineProperties(Constructor.prototype, protoProps); if (staticProps) defineProperties(Constructor, staticProps); return Constructor; }; }();

function _classCallCheck(instance, Constructor) { if (!(instance instanceof Constructor)) { throw new TypeError("Cannot call a class as a function"); } }

function _possibleConstructorReturn(self, call) { if (!self) { throw new ReferenceError("this hasn't been initialised - super() hasn't been called"); } return call && (typeof call === "object" || typeof call === "function") ? call : self; }

function _inherits(subClass, superClass) { if (typeof superClass !== "function" && superClass !== null) { throw new TypeError("Super expression must either be null or a function, not " + typeof superClass); } subClass.prototype = Object.create(superClass && superClass.prototype, { constructor: { value: subClass, enumerable: false, writable: true, configurable: true } }); if (superClass) Object.setPrototypeOf ? Object.setPrototypeOf(subClass, superClass) : subClass.__proto__ = superClass; }

var id = new Ice.InitializationData();
id.properties = Ice.createProperties();
id.properties.setProperty("Ice.Default.Locator", "IceGrid/Locator:ws -h ritz -p 4063");

var communicator = Ice.initialize([], id);
//console.log("Communicator is " + communicator);
var proxies = ["foo@SimpleApp", "foo@SimpleJavaApp", "foo@SimpleCppApp"];

var MyListener = function (_argo$TickListener) {
    _inherits(MyListener, _argo$TickListener);

    function MyListener() {
        _classCallCheck(this, MyListener);

        var _this = _possibleConstructorReturn(this, (MyListener.__proto__ || Object.getPrototypeOf(MyListener)).call(this));

        _this.listeners = [];
        return _this;
    }

    _createClass(MyListener, [{
        key: "addListener",
        value: function addListener(listener) {
            this.listeners = this.listeners.concat(listener);
        }
    }, {
        key: "onImage",
        value: function onImage(img, current) {
            this.listeners.forEach(function (x) {
                return x.onImage(img, current);
            });
        }
    }, {
        key: "onTick",
        value: function onTick(ticks, current) {
            this.listeners.forEach(function (x) {
                return x.onTick(ticks, current);
            });
        }
    }]);

    return MyListener;
}(argo.TickListener);

var tl = new MyListener();

var Foo = function (_React$Cgomponent) {
    _inherits(Foo, _React$Cgomponent);

    function Foo() {
        _classCallCheck(this, Foo);

        var _this2 = _possibleConstructorReturn(this, (Foo.__proto__ || Object.getPrototypeOf(Foo)).call(this));

        _this2.state = {
            responses: []
        };
        return _this2;
    }

    _createClass(Foo, [{
        key: "componentDidMount",
        value: function componentDidMount() {
            var outer = this;
            proxies.forEach(function (p) {
                var proxy = communicator.stringToProxy(p).ice_timeout(5000);
                argo.FooPrx.checkedCast(proxy).then(function (prx) {
                    return prx.doit();
                }).then(function (ret) {
                    return outer.setState({ responses: outer.state.responses.concat({
                            response: ret,
                            uid: uuid.v4()
                        }) });
                }).catch(function (err) {
                    return alert(err);
                });
            });
        }
    }, {
        key: "render",
        value: function render() {
            var str = communicator.toString();
            var responses = this.state.responses.map(function (x) {
                return React.createElement(
                    "p",
                    { key: x.uid },
                    "response is ",
                    x.response
                );
            });
            return React.createElement(
                "h1",
                null,
                "Hello from react"
            ), React.createElement(
                "div",
                null,
                responses
            );
        }
    }]);

    return Foo;
}(React.Cgomponent);

;

// TODO - tidy up the relationship. Have ticklistener cache image
// maybe have it emit state events that can be added to the react component's state
// Has to be a better way of doing it than this!

var DataGrid = function (_React$Component) {
    _inherits(DataGrid, _React$Component);

    function DataGrid() {
        var _ref;

        var _temp, _this3, _ret;

        _classCallCheck(this, DataGrid);

        for (var _len = arguments.length, args = Array(_len), _key = 0; _key < _len; _key++) {
            args[_key] = arguments[_key];
        }

        return _ret = (_temp = (_this3 = _possibleConstructorReturn(this, (_ref = DataGrid.__proto__ || Object.getPrototypeOf(DataGrid)).call.apply(_ref, [this].concat(args))), _this3), _this3.state = {
            data: []
        }, _temp), _possibleConstructorReturn(_this3, _ret);
    }

    _createClass(DataGrid, [{
        key: "componentDidMount",
        value: function componentDidMount() {
            //console.log("Datagrid mount");
            this.props.source.addListener(this);
        }
    }, {
        key: "onTick",
        value: function onTick(ticks, current) {
            //console.log("onTick");
            var newData = this.state.data.slice();
            ticks.forEach(function (tick, i) {
                ticks[i].key = "" + i;
                newData[i] = ticks[i];
                //console.log(ticks[i]);
                //grid.invalidateRow(i);
            });
            this.setState({ data: newData });
        }
    }, {
        key: "onImage",
        value: function onImage(img, current) {
            //console.log("onImage");
            var newData = [];
            if (img.length > 0) {
                img[0].forEach(function (tick, idx) {
                    tick.key = "" + idx;
                    newData[idx] = tick;
                });
                this.setState({ data: newData });
            }
        }
    }, {
        key: "render",
        value: function render() {
            var rows = this.state.data.map(function (x) {
                return React.createElement(
                    "tr",
                    { key: x.key },
                    React.createElement(
                        "td",
                        null,
                        x.symbol
                    ),
                    React.createElement(
                        "td",
                        null,
                        x.bidPx
                    ),
                    React.createElement(
                        "td",
                        null,
                        x.askPx
                    )
                );
            });

            return React.createElement(
                "table",
                { border: "1" },
                React.createElement(
                    "tbody",
                    null,
                    rows
                )
            );
        }
    }]);

    return DataGrid;
}(React.Component);

;

var proxy = communicator.stringToProxy("plant:ws -h ritz -p 10666 -t 2000").ice_twoway();

argo.TickerPlantPrx.checkedCast(proxy).then(function (prx) {
    setInterval(function () {
        prx.sayHello().then(function (s) {
            // console.log("hello returned " + s );
            // TODO - this isn't very reacty. Remove this junit stuff
            $("#greeting").html("<H1>" + "Got " + s + "</H1>");
        });
    }, 2000);
    return communicator.createObjectAdapter("").then(function (adapter) {
        var r = adapter.addWithUUID(tl);
        proxy.ice_getCachedConnection().setAdapter(adapter);
        var x3 = prx.subscribeWithIdent(r.ice_getIdentity());
    });
}, function (ex) {
    console.log("Called with exception " + ex);
});

ReactDOM.render(React.createElement(Foo, null), document.getElementById("content"));
ReactDOM.render(React.createElement(DataGrid, { source: tl }), document.getElementById("mygrid"));

//ReactDOM.render( <DataGrid />,  document.getElementById("mygrid"));