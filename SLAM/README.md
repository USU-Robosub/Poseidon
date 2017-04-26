
# SLAM
Simultaneous Location and Mapping for the USU Autonomous RoboSub.

---

## Dependencies

| Library                                              | Scope   | Version   | Windows                                                  | macOS                                                        | Linux                                             |
| :--------------------------------------------------: | :-----: | :-------: | :------------------------------------------------------: | :----------------------------------------------------------: | :-----------------------------------------------: |
| **CMake**                                            | Compile | 3.5+      | Follow [these instructions](https://tinyurl.com/lmtdwax) | Comes installed with Xcode.                                  | `sudo apt-get install build-essential cmake`      |
| **Homebrew (macOS Only)**                            | Install | latest    | --                                                       | /usr/bin/ruby -e "$(curl -fsSL https://tinyurl.com/oe9dlto)" | --                                                |
| **Boost**                                            | Compile | 1.6+.     | Follow [these instructions](https://tinyurl.com/ndwdq45) | `brew install boost`                                         | `sudo apt-get install libboost-all-dev`           |
| **OpenCV**                                           | Compile | 2.4.x.x   | Follow [these instructions](https://tinyurl.com/kyeab9u) | `brew tap homebrew/science && brew install opencv`           | `sudo apt-get install libopencv-dev`              |
| **Eigen3**                                           | Compile | latest    | Follow [these instructions](https://tinyurl.com/lo3m36b) | `brew install eigen`                                         | `sudo apt-get install libeigen3-dev`              |
| **SuiteSparse**                                      | Compile | latest    | Follow [these instructions](https://tinyurl.com/lx7d82c) | `brew tap homebrew/science && brew install suitesparse`      | `sudo apt-get install libsuitesparse-dev`         |
| **[USU's fork of DSO](https://tinyurl.com/k8r7sod)** | Compile | latest    | Installed automatically when `cmake` is executed         | Installed automatically when `cmake` is executed             | Installed automatically when `cmake` is executed  |
| **Catch**                                            | Test    | 1.9.1     | Installed automatically when `cmake` is executed         | Installed automatically when `cmake` is executed             | Installed automatically when `cmake` is executed  |
    

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
mkdir build
cd build
cmake ..
make slam # <-- libslam.a is created
```
Some terminals do not support to the color codes used in the cmake output. To disable color output, replace `cmake ..` with `cmake -DDISABLE_COLOR=1 ..`.

#### How to run tests
```bash
mkdir build
cd build
cmake ..
make slam_tests # <-- slam_tests is created
./slam_tests
```
