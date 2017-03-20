var mag = function(v) {
    return Math.sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
};
var cross = function(u, v) {
    var res = v3(0,0,0);
    res.x = (u.y*v.z - u.z*v.y);
    res.y = (u.z*v.x - u.x*v.z);
    res.z = (u.x*v.y - u.y*v.x);
    return res;
};
var unit = function(v) {
    var res     = v3(0,0,0);
    var vmag    = mag(v);
    res.x       = v.x/vmag;
    res.y       = v.y/vmag;
    res.z       = v.z/vmag;
    return res;
};
var negate = function(v) {
    var res = v3(0,0,0);
    res.x = -v.x;
    res.y = -v.y;
    res.z = -v.z
    return res;
};
var add = function(u, v) {
    var res = v3(0,0,0);
    res.x = u.x + v.x;
    res.y = u.y + v.y;
    res.z = u.z + v.z;
    return res;
};
var scale = function(v,s) {
    var res = v3(0,0,0);
    res.x = s*v.x;
    res.y = s*v.y;
    res.z = s*v.z;
    return res;
};
var dot = function(u,v) {
    return u.x*v.x + u.y*v.y + u.z*v.z;
};
var angle = function(u, v) {
    var mu = mag(u);
    var mv = mag(v);
    if(mu === 0 || mv === 0)
        return 180;
    var q = dot(u,v) / (mu * mv);
    return Math.acos(q);
};

var rotatex = function(v, theta) {
    var res = v3(0,0,0);
    res.x = v.x;
    res.y = v.y*Math.cos(theta) - v.z*Math.sin(theta);
    res.z = v.y*Math.sin(theta) + v.z*Math.cos(theta);
    return res;
};
var rotatey = function(v, theta) {
    var res = v3(0,0,0);
    res.x =  v.x*Math.cos(theta) + v.z*Math.sin(theta);
    res.y =  v.y;
    res.z = -v.x*Math.sin(theta) + v.z*Math.cos(theta);
    return res;
};
var rotatez = function(v, theta) {
    var res = v3(0,0,0);
    res.x = v.x*Math.cos(theta) - v.y*Math.sin(theta);
    res.y = v.x*Math.sin(theta) + v.y*Math.cos(theta);
    res.z = v.z;
    return res;
};
var rotate  = function(v, axis, theta) {
    var res = v3(0,0,0);
    a = unit(axis);
    
    var _c = Math.cos(theta);
    var _s = Math.sin(theta);
    var _u = dot(a,v)*(1 - _c);
    
    res.x = a.x*_u + v.x*_c + (-a.z*v.y + a.y*a.z)*_s;
    res.y = a.y*_u + v.y*_c + ( a.z*v.x - a.x*v.z)*_s;
    res.z = a.z*_u + v.z*_c + (-a.y*v.x + a.x*v.y)*_s;
    
    return res;
};

var v3 = function(x,y,z) {
    return {x:x,y:y,z:z};
}
var print = function(v,f,m) {
    if(typeof f == 'undefined')
        f = 3;
    if(typeof m == 'undefined')
        m = "";
    console.log(m+"{x: "+v.x.toFixed(f)+",\ty: "+v.y.toFixed(f)+",\tz: "+v.z.toFixed(f)+"}");
}

module.exports = {
    mag: mag,
    cross: cross,
    unit: unit,
    dot: dot,
    negate: negate,
    add: add,
    scale: scale,
    rotx: rotatex,
    roty: rotatey,
    rotz: rotatez,
    rot:  rotate,
    angle: angle,
    
    v3: v3,
    zero: v3(0,0,0),
    one: v3(1,1,1),
    look: v3(0,0,1),
    right: v3(1,0,0),
    up: v3(0,1,0),
    
    print: print
};