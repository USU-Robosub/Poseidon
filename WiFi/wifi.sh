#!/bin/bash

echo "Wifi script starting!"

#pause
echo "Pausing..."
sleep 5

echo "Enabling wifi..."
ifconfig wlan0 up
ifconfig wlan0

#loop
while true
do
	#check for wifi
	echo "Looking for network..."
	while [[ $(iwlist wlan0 scan | grep USUbLAN) != *"USUbLAN"* ]]
	do
		sleep 0.5
	done

	#connect to wifi
	echo "Found network. Connecting..."
	dhclient -v -r wlan0
	iwconfig wlan0 mode Managed
	iwconfig wlan0 essid "USUbLAN"
	sleep 0.5
	dhclient -v wlan0

	#ensure proper IP
	echo "IP obtained! Maintaining..."
	while [[ $(ifconfig wlan0) == *"192.168"* ]]
	do
		sleep 1
	done

	echo "IP lost!"
done

