var ctools  = require('../Utilities/compassTools.js');
var vector  = require('../Utilities/vector.js');

const p = "PASS", f = "FAIL";
const TOL = 0.0001;
var state, res, a, r, c, theta;

function within(target, precision, test) {
    return (test < target+precision) && (test > target-precision);
}

console.log("Test Flat:");
c = vector.zero;
for(i = -4; i < 5; i++){
    var test = (45*i);
    theta = test/180.0*Math.PI;
    c.x = Math.cos(theta);
    c.y = Math.sin(theta);
    res = ctools.degrees(c);
    state = within(test,TOL,res)?p:f;
    console.log("degrees(c,a): "+test+":"+res.toFixed(0)+"\t"+state);
}

console.log("Test 45-x Tilt:");
var theta = 45/180.0*Math.PI;
a = vector.rotx(vector.v3(0,0,-1), theta);
r = vector.rotx(vector.v3(1,0, 0), theta);
for(i = -4; i < 5; i++){
    var test = (45*i);
    var theta2 = test/180.0*Math.PI;
    c.x = Math.cos(theta2);
    c.y = Math.sin(theta2);
    c.z = 0;
    c = vector.rotx(c, theta);
    res = ctools.degrees(c, a, r);
    state = within(test,TOL,res)?p:f;
    console.log("degrees(c,a): "+test+":"+res.toFixed(0)+"\t"+state);
}