Poseidon
===========

Software for the Poseidon, USU's latest autonomous submarine.

This submarine is the third generation of the Robosub, built by the mechanical, electronic, and software engineers at Utah State University.

Unlike the previous versions, this submarine itself was planned by the engineers, designed in a computer, and fabricated by machines. The quality of this sub sets it apart from the previous generations. We have more compact hardware, a better design, and cleaner code. We are very hopeful that our submarine will do well in the July 2015 Robosub competition.

### Installation

> 1. *apt-get install ruby ruby-dev libi2c-dev autoconf automake g++ cmake*
> 2. *gem install rice*
> 3. *nano /boot/uEnv.txt # disable HDMI (we also recommend disabling eMMC and booting from microSD for more pins)*
> * \# Note: use 'apt-get update' is some apps say 'no such repository'*
> 4. cd Poseidon/kernel; ./compile.sh
> 5. cd Poseidon/other/advmem; make
> 6. cd Poseidon/server; make \# or ./build/compileRun.sh

### Use
To test or use the kernel code, run the following in a terminal:
> 1. cd Poseidon; ./init.sh
> 2. cd kernel; irb                   \# 'irb' (ruby sanbox environment)
> 3. require Dir.pwd + "/DiveMaster"
> 4. power = PowerController.new      \# control power-based applications
> 5. sensors = Sensors.new            \# read, record, and use sensor readings such as the IMU, hydrophones, DVL, etc.
> 6. thrusters = ThrustController.new \# control all or individual thrusters' thrust speeds

To control the system remotely via WiFi, execute the following:
Server-side: (on a Beaglebone Black)
> 1. cd Poseidon/other/WiFi
> 2. ./wifi.sh
> 3. cd ../../server
> 4. \# run either 'make; ruby RunServer.rb' (for ruby) or './build/compileRun.sh' (for cmake)

Client-side: (on another linux system, such as Mint)
> 1. cd Poseidon/client
> 2. ./init.sh
> 3. \# open index.html in a web browser and wait for the connection to turn 'green'
> 4. \# this shouldn't take more than 2-3 min (both server and client must be connected to the same router)
