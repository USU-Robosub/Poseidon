cd ../Drivers
git submodule update --recursive
cd ../Main/Peripherals
if [ -d Release ]; then
    rm -rf Release
fi
mkdir Release
cd Release
cmake ..
make Bootstrap

cd ../../WebApplication
npm install
