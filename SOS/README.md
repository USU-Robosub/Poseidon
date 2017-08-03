### Compiling SOS

Compile and run `SOS`

```
cd Poseidon/SOS
mkdir build
cd build
cmake ..
make
./SOS
```

### Running tests

Googletest and Googlemock need to be compiled before compiling the tests.

Compile `libgtest.a`

```
cd Poseidon/Libraries/googletest/googletest
mkdir build
cd build
cmake ..
make
```

Compile `libgmock.a`

```
cd Poseidon/Libraries/googletest/googlemock
mkdir build
cd build
cmake ..
make
```

Compile and run `SOStests`

```
cd Poseidon/SOS
mkdir build
cd build
cmake .. -Dtests=ON
make
./SOStests
```
