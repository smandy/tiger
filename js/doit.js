
var square = (x) => x * x ; 

square(12);

[1,2,3,4,5].map( (x) => x * x );

var add  = function( x ,y)  { return x + y;  };
var mult = function(x,y)    { return x * y;  };
var oper = function(o, x,y) { return o(x,y); };

oper(mult, 2, 3);

