
# SLAM
Simultaneous Location and Mapping for the USU Autonomous RoboSub.

---

## Contributing

Use `src` and `include` folders for code.

Use `test` folder for writing unit tests. Every concrete class should have
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