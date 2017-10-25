Poseidon
===========

#### [Utah State RoboSub team website](http://usub.cs.usu.edu/)

This repository contains the software for Poseidon and its new twin PoGen2, USU's latest autonomous submarines.

This submarine is the third generation of our submarine, built by the mechanical, electrical, and software engineers at Utah State University.

The quality of Poseidon sets it apart from previous generations of submarines. Poseidon contains cutting edge hardware, has an easy to maintain design, and cleaner code.

### Setting up Poseidon

#### Beaglebone Black

Poseidon uses a Beaglebone Black as its main computer.
From a clean install of Beaglebone Black Debian run

```
apt-get install g++ cmake
cd Poseidon/Scripts
./compileMain.sh
```

*The NodeJS on the Beaglebone Black may need to be updated.*

#### Arduino Due

Poseidon uses an Arduino Due as its hardware controller.
Follow the install instructions in `ArduinoController/README.md`.

### Use

#### Web Interface

To test via the built-in web server, run the following in cloud9 or SSH terminal

```
cd Poseidon/BoneCentral/WebApplication
node index.js
```

In a browser, enter the IP address of the Beaglebone Black (ie. 192.168.1.7) and a web interface will appear

#### Autonomous Mode

To run Poseidon's autonomous code, run the following in cloud9 or SSH terminal

```
cd Poseidon/BoneCentral/Brain
node initialize.js
```

Poseidon will wait for its action switch to be inserted before moving. Removing the action switch will cause Poseidon to stop all of its motors.
