var Vector = require('../Utilities/vector.js');

function VectorEqualityTest(testName, actual, expected, error ) {
    var passes = actual.equals( expected, error );
    _writeTestName( testName );
    process.stdout.write( actual.toString() );
    process.stdout.write( "\t\t\t");
    if (passes) _logSuccess();
    else _logFailure();
}

function ValueEqualityTest(testName, actual, expected, error) {
    error = error || 0;
    var difference = actual - expected;
    var passes = -error <= difference && difference <= error;
    _writeTestName( testName );
    process.stdout.write( actual.toFixed(3) );
    process.stdout.write( "\t\t\t\t\t\t");
    if (passes) _logSuccess();
    else _logFailure();
}

function _writeTestName( testName ) {
    process.stdout.write( testName );
}

function _logSuccess( ) {
    console.log( "\x1b[32m%s\x1b[0m", "PASS" )
}

function _logFailure( ) {
    console.log( "\x1b[31m%s\x1b[0m", "FAIL" )
}

// Test to verify that vector.zero is a JSON representing <0,0,0>.
VectorEqualityTest( "zero:\t\t", Vector.zero, new Vector(0, 0, 0) );

// Test to verify that vector.one is a JSON representing <1,1,1>.
VectorEqualityTest( "one:\t\t", Vector.one, new Vector(1, 1, 1) );

// Test to verify that vector.look is a JSON representing <1,0,0>.
VectorEqualityTest( "look:\t\t", Vector.look, new Vector(1, 0, 0) );

// Test to verify that vector.right is a JSON representing <0,0,1>.
VectorEqualityTest( "right:\t\t", Vector.right, new Vector(0, 0, 1) );

// Test to verify that vector.up is a JSON representing <0,1,0>.
VectorEqualityTest( "up: \t\t", Vector.up, new Vector(0, 1, 0) );

// Verify that passing the vector <1,1,1> into vector.mag returns the magnitude of <1,1,1>.
ValueEqualityTest( "mag(x,y,z):\t\t", new Vector(1, 1, 1).mag(), Math.sqrt(3) );

// Verify that vector.cross(<1,2,3>, <4,5,6>) returns the cross product of the two vectors.
var u = new Vector(1,2,3);
var v = new Vector(4,5,6);
VectorEqualityTest( "cross(u,v): ", u.cross(v), new Vector(-3, 6, -3) );

// Verify that calling vector.dot(<1,2,3>, <4,5,6>) returns the dot product of the two vectors.
ValueEqualityTest( "dot(u,v):\t\t", u.dot(v), 32 );

// Verify that calling vector.unit(<1,2,3>) returns the unit vector of <1,2,3>.
var unitizedVector = new Vector(
    0.2672612419124244,
    0.5345224838248488,
    0.8017837257372732
);
VectorEqualityTest( "unit(u):\t", u.unitize(), unitizedVector );

// Verify that calling vector.negate(<1,1,1>) returns <-1,-1,-1>
VectorEqualityTest( "negate(v):\t", Vector.one.negate(), new Vector(-1, -1, -1) );

// Verify that calling vector.add(<1,2,3>,<4,5,6>) takes the sum of <1,2,3> and <4,5,6>.
VectorEqualityTest( "add(u, v):\t", u.add(v), new Vector(5, 7, 9) );

// Verify that vector.scale(<1,1,1>,2) returns 2*<1,1,1> or <2,2,2>.
VectorEqualityTest( "scale(v,s):\t", Vector.one.scaleBy(2), new Vector(2, 2, 2) );

// Verify that vector.rot(<1,-1,0>, unit(<1,1,1>), pi) returns the vector that results
// from rotating <1,-1,0> pi about the unit vector of <1,1,1>
var rotatedVector = new Vector(1, -1, 0).rotateAbout(Vector.one).by(Math.PI);
VectorEqualityTest( "rot(v,ax,theta):\t", rotatedVector, new Vector(-1, 1, 0), error=0.0001 );

// Verify that vector.angle(<0,1,0>,vector.rotx(<0,0,1>, -pi/4)) returns the angle
// between the two vectors.
v = Vector.right.rotateAbout( Vector.look ).by( -Math.PI/4);
console.log(v.toString());
ValueEqualityTest( "angle(u,v):\n", Vector.up.angleFrom(v), Math.PI/4, error=0.0001 );
