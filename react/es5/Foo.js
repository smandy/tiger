"use strict";

function _classCallCheck(instance, Constructor) { if (!(instance instanceof Constructor)) { throw new TypeError("Cannot call a class as a function"); } }

function _possibleConstructorReturn(self, call) { if (!self) { throw new ReferenceError("this hasn't been initialised - super() hasn't been called"); } return call && (typeof call === "object" || typeof call === "function") ? call : self; }

function _inherits(subClass, superClass) { if (typeof superClass !== "function" && superClass !== null) { throw new TypeError("Super expression must either be null or a function, not " + typeof superClass); } subClass.prototype = Object.create(superClass && superClass.prototype, { constructor: { value: subClass, enumerable: false, writable: true, configurable: true } }); if (superClass) Object.setPrototypeOf ? Object.setPrototypeOf(subClass, superClass) : subClass.__proto__ = superClass; }

// **********************************************************************
//
// Copyright (c) 2003-2017 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************
//
// Ice version 3.7.0
//
// <auto-generated>
//
// Generated from file `Foo.ice'
//
// Warning: do not edit this file.
//
// </auto-generated>
//

(function (module, require, exports) {
    var Ice = require("ice").Ice;
    var _ModuleRegistry = Ice._ModuleRegistry;
    var Slice = Ice.Slice;

    var argo = _ModuleRegistry.module("argo");

    var iceC_argo_Foo_ids = ["::Ice::Object", "::argo::Foo"];

    argo.Foo = function (_Ice$Object) {
        _inherits(_class, _Ice$Object);

        function _class() {
            _classCallCheck(this, _class);

            return _possibleConstructorReturn(this, (_class.__proto__ || Object.getPrototypeOf(_class)).apply(this, arguments));
        }

        return _class;
    }(Ice.Object);

    argo.FooPrx = function (_Ice$ObjectPrx) {
        _inherits(_class2, _Ice$ObjectPrx);

        function _class2() {
            _classCallCheck(this, _class2);

            return _possibleConstructorReturn(this, (_class2.__proto__ || Object.getPrototypeOf(_class2)).apply(this, arguments));
        }

        return _class2;
    }(Ice.ObjectPrx);

    Slice.defineOperations(argo.Foo, argo.FooPrx, iceC_argo_Foo_ids, 1, {
        "doit": [,,,, [7],,,,,],
        "doitAgain": [,,,, [7],,,,,]
    });
    exports.argo = argo;
})(typeof global !== "undefined" && typeof global.process !== "undefined" ? module : undefined, typeof global !== "undefined" && typeof global.process !== "undefined" ? require : undefined.Ice._require, typeof global !== "undefined" && typeof global.process !== "undefined" ? exports : undefined);