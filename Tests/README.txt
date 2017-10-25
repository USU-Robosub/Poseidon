In order to quickly test Arduino code without unpluging and repluging the
Arduino, these tests have been writen to use PlatformIO. PlatformIO enables
combiling and uploading Arduino code, directly from the terminal without ever
leaving your chair.



* Installing PlatformIO *

In a Linux terminal, run the following commands:
> python -c "$(curl -fsSL https://raw.githubusercontent.com/platformio/platformio/develop/scripts/get-platformio.py)"
> python get-platformio.py

To confirm PlatformIO is installed sucessfully, run:
> platformio --help



* Compiling and Uploading with PlatformIO *

> # list serial ports
> platformio serialports list

> # upload code
> platformio run -e due -t upload

> # compile code
> platformio run -e due



* Running Tests *

Step 1. Upload the corresponding Arduino code with PlatformIO (as needed)
Step 2. Compile test w/dependencies:
> g++ --std=c++11 Test_<name>.cpp [dependencies] -o run
Step 3. Run the test:
> ./run

