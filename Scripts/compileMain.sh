cd ../Main/Peripherals
rm -rf Release
mkdir Release
cd Release/
cmake ..
make Bootstrap

cd ../../WebApplication
npm install