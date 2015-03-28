Poseidon
===========

Software for the Poseidon, USU's latest autonomous submarine.

This submarine is the third generation of the Robosub, built by the mechanical, electronic, and software engineers at Utah State University.

Unlike the previous versions, this submarine itself was planned by the engineers, designed in a computer, and fabricated by machines. The quality of this sub sets it apart from the previous generations. We have more compact hardware, a better design, and cleaner code. We are very hopeful that our submarine will do well in the July 2015 Robosub competition.

### Installation

> 1. **sudo apt-get install ruby ruby-dev libi2c-dev autoconf automake g++ awk**
> 2. **sudo gem install rice**
> 3. **./runStable.sh**

On the first call to ./runStable.sh, the API and drivers will be compiled and then stable.rb will run, but subsequent calls to ./runStable.sh will not recompile the API because the Ruby code will just link against the generated .so file. You will need root privileges in order for the drivers to work, and run.sh will ask you for the admin password if you are not running as root. The code should work regardless of whether or not PWM/I2C motors are actually attached, though if they are hooked up to the right channels they will follow the instructions.

