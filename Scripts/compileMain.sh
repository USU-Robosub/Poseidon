cd ../Libraries/Drivers
git submodule update --recursive
cd ../../BoneCentral/Peripherals
if [ -d Release ]; then
    rm -rf Release
fi
mkdir Release
cd Release
cmake ..
make Peripherals

cd ../../WebApplication
npm install

cd ../Brain
npm install
