#DSO Test Application

##DSO Install
 1. Download the Raspberry PI tool chain

   ```
   git clone https://github.com/raspberrypi/tools
   ```

 2. Create a environment variable for the Raspberry PI tool chain

   ```
   export PI_TOOLS_HOME:[path to raspberry pi tool chain repository]
   ```

 4. Follow the [DSO Install](https://github.com/JakobEngel/dso)

       Instead of `cmake ..` use `cmake --DCMAKE_TOOLCHAIN_FILE=[path to repository]/DSO_test/pi.cmake ..`


##Install
