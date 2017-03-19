var vector = require('../Utilities/vector.js')

const p = "PASS", f = "FAIL";
var state;

function within(target, precision, test) {
    return (test < target+precision) && (test > target-precision);
}

var res = vector.zero;
state = (res &&
        (typeof res.x != 'undefined' && res.x===0)&&
        (typeof res.y != 'undefined' && res.y===0)&&
        (typeof res.z != 'undefined' && res.z===0))?p:f;
console.log("zero: "+JSON.stringify(res)+"\t\t\t"+state);

res = vector.one;
state = (res &&
        (typeof res.x != 'undefined' && res.x===1)&&
        (typeof res.y != 'undefined' && res.y===1)&&
        (typeof res.z != 'undefined' && res.z===1))?p:f;
console.log("one:  "+JSON.stringify(res)+"\t\t\t"+state);

res = vector.look;
state = (res &&
        (typeof res.x != 'undefined' && res.x===0)&&
        (typeof res.y != 'undefined' && res.y===0)&&
        (typeof res.z != 'undefined' && res.z===1))?p:f;
console.log("look:  "+JSON.stringify(res)+"\t\t\t"+state);

res = vector.right;
state = (res &&
        (typeof res.x != 'undefined' && res.x===1)&&
        (typeof res.y != 'undefined' && res.y===0)&&
        (typeof res.z != 'undefined' && res.z===0))?p:f;
console.log("right:  "+JSON.stringify(res)+"\t\t\t"+state);

res = vector.up;
state = (res &&
        (typeof res.x != 'undefined' && res.x===0)&&
        (typeof res.y != 'undefined' && res.y===1)&&
        (typeof res.z != 'undefined' && res.z===0))?p:f;
console.log("up:  "+JSON.stringify(res)+"\t\t\t"+state);

res = vector.v3(1,2,3);
state = (res &&
        (typeof res.x != 'undefined' && res.x===1)&&
        (typeof res.y != 'undefined' && res.y===2)&&
        (typeof res.z != 'undefined' && res.z===3))?p:f;
console.log("xyz:  "+JSON.stringify(res)+"\t\t\t"+state);

var r3= Math.sqrt(3);
res = vector.v3(1,1,1);
res = vector.mag(res);
state = (r3 === res)?p:f;
console.log("mag(x,y,z): "+res.toFixed(3)+"\t\t\t\t"+state);

var u = vector.v3(1,2,3);
var v = vector.v3(4,5,6);
res = vector.cross(u,v);
state = (res.x===-3&&res.y===6&&res.z===-3)?p:f;
console.log("cross(u,v): "+JSON.stringify(res)+"\t\t"+state);

var w = vector.v3(1, 2, 3);
res = vector.unit(w);
state = (res.x===0.2672612419124244&&
         res.y===0.5345224838248488&&
         res.z===0.8017837257372732)?p:f;
console.log("unit(v): {\"x\":"+res.x.toFixed(2)+",\"y\":"+res.y.toFixed(2)+
        ",\"z\":"+res.z.toFixed(2)+"}\t\t"+state);

res = vector.dot(u,v);
state = (res===32)?p:f;
console.log("dot(u,v): "+res+"\t\t\t\t\t"+state);

res = vector.negate(vector.one);
state = (res.x===-1&&res.y===-1&&res.z===-1)?p:f;
console.log("negate(v): "+JSON.stringify(res)+"\t\t"+state);

res = vector.add(u, v);
state = (res.x===5&&res.y===7&&res.z===9)?p:f;
console.log("add(u, v): "+JSON.stringify(res)+"\t\t\t"+state);

res = vector.scale(vector.one, 2);
state = (res.x===2&&res.y===2&&res.z===2)?p:f;
console.log("scale(v,s): "+JSON.stringify(res)+"\t\t\t"+state);

res = vector.rotx(vector.up, 0.5*Math.PI);
state = (within(0,0.0001,res.x)&&
         within(0,0.0001,res.y)&&
         within(1,0.0001,res.z))?p:f;
console.log("rotx(v,theta): {\"x\":"+res.x.toFixed(2)+
        ",\"y\":"+res.y.toFixed(2)+",\"z\":"+res.z.toFixed(2)+"}\t"+state);
        
res = vector.rotz(vector.up, 0.5*Math.PI);
state = (within(-1,0.0001,res.x)&&
         within(0,0.0001,res.y)&&
         within(0,0.0001,res.z))?p:f;
console.log("rotz(v,theta): {\"x\":"+res.x.toFixed(2)+
        ",\"y\":"+res.y.toFixed(2)+",\"z\":"+res.z.toFixed(2)+"}\t"+state);

res = vector.roty(vector.look, 0.5*Math.PI);
state = (within(1,0.0001,res.x)&&
         within(0,0.0001,res.y)&&
         within(0,0.0001,res.z))?p:f;
console.log("roty(v,theta): {\"x\":"+res.x.toFixed(2)+
        ",\"y\":"+res.y.toFixed(2)+",\"z\":"+res.z.toFixed(2)+"}\t"+state);

u = vector.up;
v = vector.look;
res = vector.angle(u,v)*180/Math.PI;
state = within(90,0.0001,res)?p:f;
console.log("angle(u,v): "+res.toFixed(2)+"\t\t\t\t"+state);

v = vector.rotx(v, -45/180.0*Math.PI);
res = vector.angle(u,v)*180/Math.PI;
state = within(45,0.0001,res)?p:f;
console.log("angle(u,v): "+res.toFixed(2)+"\t\t\t\t"+state);

var axis = vector.unit(vector.one);
v = vector.v3(1,-1,0);
res = vector.rot(v, axis, Math.PI);
state = (within(-1,0.0001,res.x)&&
         within(1,0.0001,res.y)&&
         within(0,0.0001,res.z))?p:f;
console.log("rot(v,ax,theta): {\"x\":"+res.x.toFixed(2)+
        ",\"y\":"+res.y.toFixed(2)+",\"z\":"+res.z.toFixed(2)+"}\t"+state);
