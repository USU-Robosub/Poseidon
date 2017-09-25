### Project File Structure

`src` - All source code for the vision library separated into individual directories for sub projects. All `*.cpp` files must have a `*.spec.cpp` that contains unit tests.

`include` - All include headers for the vision library in a single directory.

`mocks` - Mock implementations of source files, implemented as header files, used for unit tests. All mock files should be named `[mocked header].mock.hpp`

`demo` - Demo driver to test vision library as a whole.

### How to Compile

```
cd vision
mkdir build
cmake .. -Dtests=ON
make
```

The building of unit tests can be disabled by using `-Dtests=OFF`

### How to Run Unit Tests

```
cd vision/build
./VisionTests
```
