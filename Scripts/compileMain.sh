cd ../Main/Peripherals
if [ -d Release ]; then
    rm -rf Release
fi
mkdir Release
cd Release
cmake ..
make Bootstrap
make Socket

cd ../../WebApplication
npm install
