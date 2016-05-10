if ! [ -d "$Build" ]; then
mkdir Build
fi
cd Build
cmake ..
make Sockets
