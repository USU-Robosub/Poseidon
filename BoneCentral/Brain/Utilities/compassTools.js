var Vector = require('./vector.js');

var cdeg = function(polarNorth, down) {
    if (!down) return polarNorth;

    var axis = down.cross(Vector.right).unitize();
    var angleY = axis.angleFrom(Vector.look);
    var angleX = down.angleFrom(Vector.right.scaleBy(-1));
    return deg(polarNorth
        .rotateAbout(Vector.up).by(-angleY)
        .rotateAbout(Vector.look).by(-angleX));
};

function deg(v) {
    var res = 0;
    
         if(v._x===0&&v._y > 0){res = 90;}
    else if(v._x < 0&&v._y===0){res =180;}
    else if(v._x===0&&v._y < 0){res =-90;}
    else {
        d=Math.atan(v._y/v._x)*180/Math.PI;
        
             if(v._x<0&&v._y>0){res = 180+d;}// 2nd quadrant
        else if(v._x<0&&v._y<0){res =-180+d;}// 3rd quadrant
        else{return d;}                    // 1st & 4th quadrant
    }
    
    return res;
}

module.exports = {
    degrees: cdeg
};