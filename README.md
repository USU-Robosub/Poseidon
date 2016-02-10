Poseidon
===========

Software for the Poseidon, USU's latest autonomous submarine.

This submarine is the third generation of the Robosub, built by the mechanical, electrical, and software engineers at Utah State University.

Unlike the previous versions, this submarine itself was planned by the engineers, designed in a computer, and fabricated by machines. The quality of this sub sets it apart from the previous generations. We have more compact hardware, a better design, and cleaner code. We are very hopeful that our submarine will do well in the July 2016 Robosub competition.

### Installation

> 1. *apt-get install ruby ruby-dev g++ cmake*
> 2. *nano /boot/uEnv.txt # disable HDMI (we also recommend disabling eMMC and booting from microSD for more pins)*
> * \# Note: use 'apt-get update' is some apps say 'no such repository'*
> 3. cd Poseidon/Scripts; ./compileMain.sh \# you may need to change permissions

### Use
To test via the kernel code, run the following:
> 1. cd Poseidon/Main/Peripherals/Release; ./Bootstrap
> 2. \# begin entering in commands followed by their paramter values

To test via the built-in web server, run the following:
> 1. cd Poseidon/Main/WebApplication; node index.js
> 2. \# In a browser, enter the IPv* address (ie. 192.168.7.2) and a simple web interface will appear

### Commands
For all available commands, please see "Poseidon/Main/Peripherals/src/Peripherals/CommandDispatcher.cpp"
> * `goDirection x y z`  - *invokes a vectored thrust with floating values (0.0F to 1.0F) proportional to 0% to 100%*
> * `faceDirection w`  - *invokes a yaw motion about the vertical axis with floating values of 0.0F to 1.0F*
> * `turnOnEscs`  - *enable the Escs for motor control - kind of like starting a car engine*
> * `turnOffEscs`  - *disable the Escs*
