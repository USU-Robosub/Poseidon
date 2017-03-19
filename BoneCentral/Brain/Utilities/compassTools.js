var vector = require('./vector.js');

var getTrueCompass = function(compv, accelv) {
    var av      = unitScale(accelv);
    var right   = unitScale(vector.cross(av, compv));
    var res     = unitScale(vector.cross(right, av));
    return res;
};

var cdeg = function(compv, va) {
    var cv = compv;
    
    if(va) {
        var az   = vector.v3(0,0,-1);
        var ax   = vector.v3(1,0, 0);
        var axis = vector.unit(vector.cross(az,va));
        var angy = vector.angle(axis, ax);
        var angx = vector.angle(va, az);
        var c    = vector.roty(cv, -angy);
        cv       = vector.rotx(c, -angx);
    }
    
    return deg(cv);
};

function unitScale(v) {
    const scale = 5;
    return vector.scale(vector.unit(v), scale);
}

function deg(v) {
    var res = 0;
    
         if(v.x===0&&v.y > 0){res = 90;}
    else if(v.x < 0&&v.y===0){res =180;}
    else if(v.x===0&&v.y < 0){res =-90;}
    else {
        d=Math.atan(v.y/v.x)*180/Math.PI;
        
             if(v.x<0&&v.y>0){res = 180+d;}// 2nd quadrant
        else if(v.x<0&&v.y<0){res =-180+d;}// 3rd quadrant
        else{return d;}                    // 1st & 4th quadrant
    }
    
    return res;
}

module.exports = {
    getTrueCompass: getTrueCompass,
    degrees: cdeg
};