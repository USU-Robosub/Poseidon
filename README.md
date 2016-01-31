Poseidon
===========

Software for the Poseidon, USU's latest autonomous submarine.

This submarine is the third generation of the Robosub, built by the mechanical, electronic, and software engineers at Utah State University.

Unlike the previous versions, this submarine itself was planned by the engineers, designed in a computer, and fabricated by machines. The quality of this sub sets it apart from the previous generations. We have more compact hardware, a better design, and cleaner code. We are very hopeful that our submarine will do well in the July 2016 Robosub competition.

### Installation

> 1. *nano /boot/uEnv.txt # disable HDMI (we also recommend disabling eMMC and booting from microSD for more pins)*
> * \# Note: use 'apt-get update' if some apps say 'no such repository'*
> 2. cd Poseidon/Scripts; ./compileMain.sh

### Use

> For normal run: ./run.sh
> For control via web app: ./startWebApp.sh
