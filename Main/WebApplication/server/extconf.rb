require 'mkmf-rice'

str_flg = " -std=c++0x -O3 -Wall -Wextra -Wdouble-promotion "+
          "-Wno-deprecated -Ilibs/pstreams-0.8.1 -Wno-unused-parameter"
$CFLAGS << str_flg

puts "SERVER: "
create_makefile('Server')


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
srcs =  " RCServer.cpp" + 
	" main.cpp" + 
	" libs/jsoncpp-1.5.0/jsoncpp.cpp";

objs = srcs.gsub(COBJ, ".o") +
	dir_files("/../kernel/API").gsub(COBJ, ".o") + 
	" ../kernel/drivers/Registry.o" + 
	" ../kernel/drivers/I2C/I2C.o" + 
	" ../kernel/drivers/IMU/BMP085.o" + 
	" ../kernel/drivers/IMU/HMC5883L.o" + 
	" ../kernel/drivers/IMU/MPU6050.o" + 
	" ../kernel/drivers/PWM/PWM.o" + 
	" ../kernel/drivers/PowerModule/CMPR.o"



# update Makefile
ifile = File.new("Makefile", "r")
str = ifile.read().gsub(RSRC, "SRCS =#{srcs}").gsub(ROBJ, "OBJS =#{objs}")
ifile.close

ofile = File.new("Makefile", "w")
ofile.write(str)
ofile.close
