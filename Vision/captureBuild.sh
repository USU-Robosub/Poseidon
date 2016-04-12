g++ -c Capture.cpp `pkg-config --cflags opencv` -std=c++11
g++ captureMain.cpp Capture.o -o capture `pkg-config --cflags opencv pkg-config --libs opencv` -std=c++11
