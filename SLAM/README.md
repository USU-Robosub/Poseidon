
# SLAM
Simultaneous Location and Mapping for the USU Autonomous RoboSub.

---

## Dependencies

#### CMake
CMake is required to compile and build the library. Follow 
[these instructions](INSTALLING_CMAKE.md) to get CMake up and
running on your machine.

#### OpenCV 2.4
OpenCV is required to build or use this library. Any version 
in the `2.4.x.x` range should work. At the ime of this writing, 
the most recent stable release was `2.4.13.2`. Follow 
[these instructions](INSTALLING_OPENCV.md) to get OpenCV
up and running on your machine.

---

## Contributing

#### Basics

- Please place all headers `.h` and `.hpp` files in `include/`.
- Please place all source `.cpp` files in `src/`.

#### Namespace `slam`

Please place everything in `namespace slam`. For example:

```c++
namespace slam {
    class MyClass {...}
    struct MyStruct {...}
    void doSomething() {...}
}
```

#### Tests

Use `test/` folder for writing unit tests. Every concrete class 
should have a set of associated unit tests. Structs should also 
probably have unit tests for sanity's sake. Take a look at the
existing tests to figure out how to write them.

#### How to build
```bash
mkdir out
cd out
cmake ..
make slam # <-- libslam.a is created
```

#### How to run tests
```bash
mkdir out
cd out
cmake ..
make slam_tests # <-- slam_tests is created
./slam_tests
```
