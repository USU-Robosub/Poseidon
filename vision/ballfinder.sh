fswebcam -r 1280x720 --jpeg 100 -D 1 circlefinder-raw.jpg
./contours circlefinder-raw.jpg 40
./circles circlefinder-raw.jpg 40 50