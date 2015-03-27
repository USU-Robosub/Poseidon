#!/bin/bash
#$(date "+%H") -lt 21 
folder=$(date +%Ym%d_%H%M%S)
mkdir live-images/$folder
i=0
while [ 1 ]; do
    nohup fswebcam -r 640x480 --jpeg 100 -D 1 ~/roboCV/live-images/$folder/web-cam-shot$i.jpg > webcamShooter.out 2> webcamShooter.err < /dev/null
    i=$((i + 1))
    sleep 1
    echo $i
done