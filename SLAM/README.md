
# SLAM
Simultaneous Location and Mapping for the USU Autonomous RoboSub.

---

## Contributing

Please place all headers `.h` and `.hpp` files in `include/`.

Please place all source `.cpp` files in `src/`.

### Namespace `slam`

Please place everything in `namespace slam`. For example:

```c++
namespace slam {
    class MyClass {...}
    struct MyStruct {...}
    void doSomething() {...}
}
```

### Tests

Use `test/` folder for writing unit tests. Every concrete class should have
a set of associated unit tests.

### How to build
```bash
mkdir out
cd out
cmake ..
make slam # <-- libslam.a is created
```

### How to run tests
```bash
mkdir out
cd out
cmake ..
make slam_tests # <-- slam_tests is created
./slam_tests
```
