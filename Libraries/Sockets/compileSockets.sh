if [ -d Build ]; then
	rm -rf Build
fi
mkdir Build
cd Build
cmake ..
make Sockets
