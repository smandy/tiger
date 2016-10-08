
function Circle(x, y) {
    this.x = x || 10;
    this.y = y || 20;
};

Circle.prototype.radius = function() {
    return Math.sqrt( this.x* this.x + this.y * this.y );
};

class Circle2 {
    constructor(x,y) {
        this.x = x;
        this.y = y;
    };
    radius() {
        return Math.sqrt( this.x * this.x + this.y * this.y );
    }
};

var a = new Circle2(10,20);
var b = new Circle2(10,20);

// a.radius();
// (define-key nodejs-repl-mode-map (kbd "C-c C-r") 'nodejs-repl-send-region)
