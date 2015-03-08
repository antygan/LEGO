#!/bin/bash

if [ $# -lt 1 ]; then
	echo "ERROR: please pass the program to run on EV3"
else 
	EV3_PROG=$1
	echo "sshpass -p '' scp bin/$EV3_PROG root@192.168.0.105:/media/card" > temp
	pv temp
	rm temp
	./connect_device.sh $EV3_PROG
	echo ""
fi
