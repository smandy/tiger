// **********************************************************************
//
// Copyright (c) 2003-2015 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************
//
// Ice version 3.6.0
//
// <auto-generated>
//
// Generated from file `Ticker.ice'
//
// Warning: do not edit this file.
//
// </auto-generated>
//

(function(module, require, exports)
{
    var Ice = require("ice").Ice;
    var __M = Ice.__M;
    var Slice = Ice.Slice;

    var argo = __M.module("argo");

    argo.Tick = Slice.defineStruct(
        function(symbol, bidPx, askPx)
        {
            this.symbol = symbol !== undefined ? symbol : "";
            this.bidPx = bidPx !== undefined ? bidPx : 0.0;
            this.askPx = askPx !== undefined ? askPx : 0.0;
        },
        false,
        function(__os)
        {
            __os.writeString(this.symbol);
            __os.writeDouble(this.bidPx);
            __os.writeDouble(this.askPx);
        },
        function(__is)
        {
            this.symbol = __is.readString();
            this.bidPx = __is.readDouble();
            this.askPx = __is.readDouble();
        },
        17, 
        false);
    Slice.defineSequence(argo, "TickSeqHelper", "argo.Tick", false);

    argo.TickListener = Slice.defineObject(
        undefined,
        Ice.Object, undefined, 1,
        [
            "::Ice::Object",
            "::argo::TickListener"
        ],
        -1, undefined, undefined, false);

    argo.TickListenerPrx = Slice.defineProxy(Ice.ObjectPrx, argo.TickListener.ice_staticId, undefined);

    Slice.defineOperations(argo.TickListener, argo.TickListenerPrx,
    {
        "onTick": [, , , , , , [["argo.TickSeqHelper"]], , , , ]
    });

    argo.TickerPlant = Slice.defineObject(
        undefined,
        Ice.Object, undefined, 1,
        [
            "::Ice::Object",
            "::argo::TickerPlant"
        ],
        -1, undefined, undefined, false);

    argo.TickerPlantPrx = Slice.defineProxy(Ice.ObjectPrx, argo.TickerPlant.ice_staticId, undefined);

    Slice.defineOperations(argo.TickerPlant, argo.TickerPlantPrx,
    {
        "subscribe": [, , , , , , [["argo.TickListenerPrx"]], , , , ],
        "subscribeWithIdent": [, , , , , , [[Ice.Identity]], , , , ],
        "sayHello": [, , , , , [7], , , , , ]
    });
    exports.argo = argo;
}
(typeof(global) !== "undefined" && typeof(global.process) !== "undefined" ? module : undefined,
 typeof(global) !== "undefined" && typeof(global.process) !== "undefined" ? require : window.Ice.__require,
 typeof(global) !== "undefined" && typeof(global.process) !== "undefined" ? exports : window));