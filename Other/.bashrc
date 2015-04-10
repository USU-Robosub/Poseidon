# ~/.bashrc: executed by bash(1) for non-login shells.

# Note: PS1 and umask are already set in /etc/profile. You should not
# need this unless you want different defaults for root.
# PS1='${debian_chroot:+($debian_chroot)}\h:\w\$ '
# umask 022

# You may uncomment the following lines if you want `ls' to be colorized:
# export LS_OPTIONS='--color=auto'
# eval "`dircolors`"
# alias ls='ls $LS_OPTIONS'
# alias ll='ls $LS_OPTIONS -l'
# alias l='ls $LS_OPTIONS -lA'
#
# Some more alias to avoid making mistakes:
# alias rm='rm -i'
# alias cp='cp -i'
# alias mv='mv -i'

alias edit_bash="nano ~/.bashrc"
alias edit_network="nano /etc/network/interfaces"
alias edit_ssh="nano /etc/ssh/sshd_config" 
alias edit_hostname="nano /etc/hostname"
alias edit_host="nano /etc/hosts"
alias search_desk="cd /home/debian/Desktop"

SLOTS=/sys/devices/bone_capemgr.*/slots
FIRM=/lib/firmware
PINS=/sys/kernel/debug/pinctrl/44e10800.pinmux/pins

# use to compile main.c: "> comp_c main"
function comp_c {
  # g++ [fileA.c] [fileB.c] [etc] -o [Program]
  # g++ -c [file.c] => file.o
  # g++ [fileA.o] [fileB.o] [etc] -o [Program]
  g++ $1.c -o $1
}

# use to create kernel device tree
function comp_dts {
	dtc -O dtb -o $1.dtbo -b 0 -@ $1.dts
	cp $1.dtbo /lib/firmware/$1.dtbo
}

# use to read register address (once)
# "> readm 0x48304000 10"
function readm {
  /home/debian/Desktop/CODE/memory/./main -r $1 $2 0 1
}

# use to write register address (once)
# "> writem 0x48304000 214 61A8"
function writem {
  /home/debian/Desktop/CODE/memory/./main -w $1 $2 $3 1
}

function load_i2c {
	echo BB-I2C1 > $SLOTS
	source /home/debian/Desktop/CODE/i2c/script.sh
	i2c2_enable
}

function LED {
        led_path=/sys/devices/ocp.3/gpio-leds.8/leds/beaglebone\:green\:
        mode="none"
        case $2 in
                '0') mode=none; ;;
                '1') mode=nand-disk; ;;
                '2') mode=mmc0; ;;
                '3') mode=timer; ;;
                '4') mode=oneshot; ;;
                '5') mode=heartbeat; ;;
                '6') mode=backlight; ;;
                '7') mode=gpio; ;;
                '8') mode=cpu0; ;;
                '9') mode=default-on; ;;
                'A') mode=transient; ;;
                *) echo "Unsupported Option\nTry: LED usr0 5"; ;;
        esac
        echo $mode > "$led_path$1/trigger"
}

function fix_skew {
	cp $1 $1.old
	rm -rf $1
	mv $1.old $1
}

function analize_i2c {
	printf "REVNB_LO: \t\t";	readm $1 00;
	printf "REVNB_HI: \t\t";	readm $1 04;
	printf "SYSC: \t\t\t";		readm $1 10;
	printf "IRQSTATUS_RAW: \t\t";	readm $1 24;
	printf "IRQSTATUS: \t\t";	readm $1 28;
	printf "IRQENABLE_SET: \t\t";	readm $1 2C;
	printf "IRQENABLE_CLR: \t\t";	readm $1 30;
	printf "WE: \t\t\t";		readm $1 34;
	printf "DMARXENABLE_SET: \t";	readm $1 38;
	printf "DMATXENABLE_SET: \t";	readm $1 3C;
	printf "DMARXENABLE_CLR: \t";	readm $1 40;
	printf "DMATXENABLE_CLR: \t";	readm $1 44;
	printf "DMARXWAKE_EN: \t\t";	readm $1 48;
	printf "DMATXWAKE_EN: \t\t";	readm $1 4C;
	printf "SYSS: \t\t\t";		readm $1 90;
	printf "BUF: \t\t\t";		readm $1 94;
	printf "CNT: \t\t\t";		readm $1 98;
	printf "DATA: \t\t\t";		readm $1 9C;
	printf "CON: \t\t\t";		readm $1 A4;
	printf "OA: \t\t\t";		readm $1 A8;
	printf "SA: \t\t\t";		readm $1 AC;
	printf "PSC: \t\t\t";		readm $1 B0;
	printf "SCLL: \t\t\t";		readm $1 B4;
	printf "SCLH: \t\t\t";		readm $1 B8;
	printf "SYSTEST: \t\t";		readm $1 BC;
	printf "BUFSTAT: \t\t";		readm $1 C0;
	printf "OA1: \t\t\t";		readm $1 C4;
	printf "OA2: \t\t\t";		readm $1 C8;
	printf "OA3: \t\t\t";		readm $1 CC;
	printf "ACTOA: \t\t\t";		readm $1 D0;
	printf "SBLOCK: \t\t";		readm $1 D4;
}

function analize_pwm {
	printf "IDVER\t\t\t";			readm $1 0000;
	printf "SYSCONFIG\t\t";			readm $1 0004;
	printf "CLKCONFIG\t\t";			readm $1 0008;
	printf "CLKSTATUS\t\t";			readm $1 000C;
	printf "TBSTS       | TBCTL\t";		readm $1 0200;
	printf "TBPHS       | TBPHSHR\t";	readm $1 0204;
	printf "TBPRD       | TBCNT\t";		readm $1 0208;
	printf "CMPCTL      | reserved\t";	readm $1 020C;
	printf "CMPA        | CMPAHR\t";	readm $1 0210;
	printf "AQCTLA      | CMPB\t";		readm $1 0214;
	printf "AQSFRC      | AQCTLB\t";	readm $1 0218;
	printf "DBCTL       | AQCSFRC\t";	readm $1 021C;
	printf "DBFED       | DBRED\t";		readm $1 0220;
	printf "TZSEL\t\t\t";			readm $1 0224;
	printf "TZEINT      | TZCTL\t";		readm $1 0228;
	printf "TZCLR       | TZFLG\t";		readm $1 022C;
	printf "TZSEL       | ETFRC\t";		readm $1 0230;
	printf "ETFLG       | ETPS\t";		readm $1 0234;
	printf "ETFRC       | ETCLR\t";		readm $1 0238;
	printf "PCCTL\t\t\t";			readm $1 023C;
	printf "HRCTL\t\t\t";			readm $1 0240;
}
