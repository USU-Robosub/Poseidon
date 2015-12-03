
# Compile MindGem
cd ../Main/MindGem
make clean
make module

# Compile Peripherals
cd ../Peripherals
rm -rf Peripherals/Release
mkdir Release
cd Release/
cmake ..
make Bootstrap