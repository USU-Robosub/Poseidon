var vector = require('../Utilities/vector.js')

const pass = "PASS", fail = "FAIL";
var state;

function within(target, precision, test) {
    return (test < target+precision) && (test > target-precision);
}

// Test to verify that vector.zero is a JSON representing <0,0,0>.
var res = vector.zero;
state = (res &&
        (res.x===0)&&
        (res.y===0)&&
        (res.z===0))?pass:fail;
console.log("zero: "+JSON.stringify(res)+"\t\t\t"+state);

// Test to verify that vector.one is a JSON representing <1,1,1>.
res = vector.one;
state = (res &&
        (res.x===1)&&
        (res.y===1)&&
        (res.z===1))?pass:fail;
console.log("one:  "+JSON.stringify(res)+"\t\t\t"+state);

// Test to verify that vector.look is a JSON representing <0,0,1>.
res = vector.look;
state = (res &&
        (res.x===0)&&
        (res.y===0)&&
        (res.z===1))?pass:fail;
console.log("look:  "+JSON.stringify(res)+"\t\t\t"+state);

// Test to verify that vector.right is a JSON representing <1,0,0>.
res = vector.right;
state = (res &&
        (res.x===1)&&
        (res.y===0)&&
        (res.z===0))?pass:fail;
console.log("right:  "+JSON.stringify(res)+"\t\t\t"+state);

// Test to verify that vector.up is a JSON representing <0,1,0>.
res = vector.up;
state = (res &&
        (res.x===0)&&
        (res.y===1)&&
        (res.z===0))?pass:fail;
console.log("up:  "+JSON.stringify(res)+"\t\t\t"+state);

// Test to verify that calling v3(1,2,3) returns a JSON representing the vector <1,2,3>.
res = vector.v3(1,2,3);
state = (res &&
        (res.x===1)&&
        (res.y===2)&&
        (res.z===3))?pass:fail;
console.log("xyz:  "+JSON.stringify(res)+"\t\t\t"+state);

// Verify that passing the vector <1,1,1> into vector.mag returns the magnitude of <1,1,1>.
var r3Magnitude= Math.sqrt(3);
res = vector.v3(1,1,1);
var magnitudeOfResult = vector.mag(res);
state = (r3Magnitude === magnitudeOfResult)?pass:fail;
console.log("mag(x,y,z): "+res.toFixed(3)+"\t\t\t\t"+state);

// Verify that vector.cross(<1,2,3>, <4,5,6>) returns the cross product of the two vectors.
var u = vector.v3(1,2,3);
var v = vector.v3(4,5,6);
res = vector.cross(u,v);
state = (res.x===-3&&res.y===6&&res.z===-3)?pass:fail;
console.log("cross(u,v): "+JSON.stringify(res)+"\t\t"+state);

// Verify that calling vector.dot(<1,2,3>, <4,5,6>) returns the dot product of the two vectors.
res = vector.dot(u,v);
state = (res===32)?pass:fail;
console.log("dot(u,v): "+res+"\t\t\t\t\t"+state);

// Verify that calling vector.unit(<1,2,3>) returns the unit vector of <1,2,3>.
var w = vector.v3(1, 2, 3);
res = vector.unit(w);
state = (res.x===0.2672612419124244&&
         res.y===0.5345224838248488&&
         res.z===0.8017837257372732)?pass:fail;
console.log("unit(v): {\"x\":"+res.x.toFixed(2)+",\"y\":"+res.y.toFixed(2)+
        ",\"z\":"+res.z.toFixed(2)+"}\t\t"+state);

// Verify that calling vector.negate(<1,1,1>) returns <-1,-1,-1>
res = vector.negate(vector.one);
state = (res.x===-1&&res.y===-1&&res.z===-1)?pass:fail;
console.log("negate(v): "+JSON.stringify(res)+"\t\t"+state);

// Verify that calling vector.add(<1,2,3>,<4,5,6>) takes the sum of <1,2,3> and <4,5,6>.
res = vector.add(u, v);
state = (res.x===5&&res.y===7&&res.z===9)?pass:fail;
console.log("add(u, v): "+JSON.stringify(res)+"\t\t\t"+state);

// Verify that vector.scale(<1,1,1>,2) returns 2*<1,1,1> or <2,2,2>.
res = vector.scale(vector.one, 2);
state = (res.x===2&&res.y===2&&res.z===2)?pass:fail;
console.log("scale(v,s): "+JSON.stringify(res)+"\t\t\t"+state);

// Verify that vector.rotx(<0,1,0>, 0.5*pi) returns the resulting vector from 
// rotating <0,1,0> pi/2 about the x-axis.
res = vector.rotx(vector.up, 0.5*Math.PI);
state = (within(0,0.0001,res.x)&&
         within(0,0.0001,res.y)&&
         within(1,0.0001,res.z))?pass:fail;
console.log("rotx(v,theta): {\"x\":"+res.x.toFixed(2)+
        ",\"y\":"+res.y.toFixed(2)+",\"z\":"+res.z.toFixed(2)+"}\t"+state);
        
// Verify that vector.rotz(<0,1,0>,pi/2) returns the vector that results from 
// rotating <0,1,0> pi/2 about the z-axis.
res = vector.rotz(vector.up, 0.5*Math.PI);
state = (within(-1,0.0001,res.x)&&
         within(0,0.0001,res.y)&&
         within(0,0.0001,res.z))?pass:fail;
console.log("rotz(v,theta): {\"x\":"+res.x.toFixed(2)+
        ",\"y\":"+res.y.toFixed(2)+",\"z\":"+res.z.toFixed(2)+"}\t"+state);

// Verify that vector.roty(<0,0,1>, pi/2) returns the vector that results from
// rotating <0,0,1> pi/2 about the y-axis.
res = vector.roty(vector.look, 0.5*Math.PI);
state = (within(1,0.0001,res.x)&&
         within(0,0.0001,res.y)&&
         within(0,0.0001,res.z))?pass:fail;
console.log("roty(v,theta): {\"x\":"+res.x.toFixed(2)+
        ",\"y\":"+res.y.toFixed(2)+",\"z\":"+res.z.toFixed(2)+"}\t"+state);

// Verify that vector.angle(<0,1,0>,<0,0,1>) returns the angle between <0,1,0> and <0,0,1>.
u = vector.up;
v = vector.look;
res = vector.angle(u,v)*180/Math.PI;
state = within(90,0.0001,res)?pass:fail;
console.log("angle(u,v): "+res.toFixed(2)+"\t\t\t\t"+state);

// Verify that vector.angle(<0,1,0>,vector.rotx(<0,0,1>, -pi/4)) returns the angle
// between the two vectors.
v = vector.rotx(v, -45/180.0*Math.PI);
res = vector.angle(u,v)*180/Math.PI;
state = within(45,0.0001,res)?pass:fail;
console.log("angle(u,v): "+res.toFixed(2)+"\t\t\t\t"+state);

// Verify that vector.rot(<1,-1,0>, unit(<1,1,1>), pi) returns the vector that results
// from rotating <1,-1,0> pi about the unit vector of <1,1,1>
var axis = vector.unit(vector.one);
v = vector.v3(1,-1,0);
res = vector.rot(v, axis, Math.PI);
state = (within(-1,0.0001,res.x)&&
         within(1,0.0001,res.y)&&
         within(0,0.0001,res.z))?pass:fail;
console.log("rot(v,ax,theta): {\"x\":"+res.x.toFixed(2)+
        ",\"y\":"+res.y.toFixed(2)+",\"z\":"+res.z.toFixed(2)+"}\t"+state);
