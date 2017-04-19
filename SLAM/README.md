
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

#### DSO
DSO is required to build or use this library. The instructions for building the static library file can be found in the [DSO's Github repository](https://github.com/JakobEngel/dso). The Eigen3 headers are needed to build this library, and their installation instructions can be found in the DSO's Github repository `README.md`. Once the DSO static library file has been built, and Eigen3 has been installed or built. Use the following cmake command.
```
Poseidon/SLAM/build$ cmake -DDSO_DIR={path to the DSO repository} ..
```
After using the above cmake command to set the path of the DSO repository, the normal cmake command can be used for future cmake rebuilds.
```
Poseidon/SLAM/build$ cmake ..
```

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
Some terminals do not support to the color codes used in the cmake output. To disable color output use the following command.
```
cmake -DDISABLE_COLOR=1 ..
```

#### How to run tests
```bash
mkdir out
cd out
cmake ..
make slam_tests # <-- slam_tests is created
./slam_tests
```
