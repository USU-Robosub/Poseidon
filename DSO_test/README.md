#DSO Test Application

##DSO Install
 1. Download the Raspberry PI tool chain

   ```
   git clone https://github.com/raspberrypi/tools
   ```

 2. Edit the paths in pi.cmake to the location of the Raspberry PI tool chain

 3. Follow the [DSO Install](https://github.com/JakobEngel/dso)

       Instead of `cmake ..` use `cmake --DCMAKE_TOOLCHAIN_FILE=[path to repository]/DSO_test/pi.cmake ..`


##Install
