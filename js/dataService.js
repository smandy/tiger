angular.module('app', ['angular-flot', 'ui.bootstrap']).factory("DataService", function() {
    console.log("Creating dataservice");
    
    var ts1 = new Array();
    var ts2 = new Array();
    var ts3 = new Array();
    
    var dataLength = 0;
    var count = 0;
    
    return {
        length : function() {
            return dataLength;
        },
        ts1 : function() {
            return ts1;
        },
        ts2 : function() {
            return ts2;
        },
        ts3 : function() {
            return ts3;
        },
        addPoints : function(x,y,z) {
            ts1[ts1.length] = [count,x];
            ts2[ts2.length] = [count,y];
            ts3[ts3.length] = [count,z];
            
            dataLength += 1;
            count += 1;
            
            if (dataLength > 300) {
                ts1.shift();
                ts2.shift();
                ts3.shift();
                dataLength -= 1;
            };
        }
    };
});
