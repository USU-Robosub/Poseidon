require 'rubygems'
require 'mkmf-rice'

# compiler flags
$CFLAGS << " -std=c++0x -O3 -Wall -Wextra -Wdouble-promotion -Wfloat-equal -Wunsafe-loop-optimizations -Wno-deprecated"

# linker flags
# $LFLAGS << " -lmath" # link libmath.so

# make Makefile
puts "KERNEL: "
create_makefile('DiveMaster')


# -- edit Makefile --
COBJ = /(?<=[a-zA-Z0-9_])[.]cpp/
RSRC = /SRCS =.*/
ROBJ = /OBJS =.*/

# get files
def dir_files(directory)
	str = ""
	Dir[Dir.pwd + directory + "/*.cpp"].each do |item|
		str += " #{item.gsub(Dir.pwd + "/", "")}"
	end
	return str
end

# whitelisted files and directories
srcs =  " DiveMaster.cpp" + 
	dir_files("/API") + 
	" drivers/Registry.cpp" + 
	" drivers/I2C/I2C.cpp" + 
	" drivers/IMU/BMP085.cpp" + 
	" drivers/IMU/HMC5883L.cpp" + 
	" drivers/IMU/MPU6050.cpp" + 
	" drivers/PWM/PWM.cpp" + 
	" drivers/PowerModule/CMPR.cpp"

objs = srcs.gsub(COBJ, ".o")



# update Makefile
ifile = File.new("Makefile", "r")
str = ifile.read().gsub(RSRC, "SRCS =#{srcs}").gsub(ROBJ, "OBJS =#{objs}")
ifile.close

ofile = File.new("Makefile", "w")
ofile.write(str)
ofile.close


