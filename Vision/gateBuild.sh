g++ -c Capture.cpp GateDetector.cpp `pkg-config --cflags opencv` -std=c++11
g++ gateDetectorMain.cpp Capture.o GateDetector.o -o gateDetect `pkg-config --cflags opencv pkg-config --libs opencv` -std=c++11
