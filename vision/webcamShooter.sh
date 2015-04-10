#!/bin/bash
#$(date "+%H") -lt 21 
echo "calculating date"
folder=$(date +%Ym%d_%H%M%S)
echo "Basic Setup"
mkdir ~/live-images/$folder &
touch ~/live-images/latest
i=0
while [ 1 ]; do
    echo taking shot $i
    #nohup fswebcam -r 640x480 --jpeg 100 -D 1 ~/roboCV/live-images/$folder/web-cam-shot$i.jpg > webcamShooter.out 2> webcamShooter.err < /dev/null
    fswebcam -r 1280x720 --jpeg 100 -D 1  ~/roboCV/live-images/$folder/web-cam-shot$i.jpg
    echo live-images/$folder/web-cam-shot$i.jpg > ./live-images/latest
    i=$((i + 1))
    #echo $i
    #sleep 1
done