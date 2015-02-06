require 'rubygems'
require 'mkmf-rice'

# compiler flags
$CFLAGS << " -std=c++0x -O3 -Wall -Wextra -Wdouble-promotion -Wfloat-equal -Wunsafe-loop-optimizations -Wno-deprecated"

# linker flags
# $LFLAGS << " -lmath" # link libmath.so

# make Makefile
create_makefile('DiveMaster')


name = (`echo $(cat /proc/cpuinfo | grep name) | grep -i "${ARM}"`)[/ARM|arm/].downcase
if(name == "arm")
	# find dependencies
	require 'find'
	srcs = "SRCS = "
	objs = ""
	Find.find(Dir.pwd) do |path|
		srcs += (path if path =~ /.*\.cpp$/).gsub(Dir.pwd + "/", "") + " "
	end
	objs = srcs.gsub(/\.cpp/, ".o").gsub(/SRCS\s=\s/, "OBJS = ")

	# add dependencies
	file_name = "Makefile"
	File.open(file_name, "w") {|file| file.puts File.read(file_name)
				.gsub(/SRCS.*$/.match(text).to_s, srcs)
				.gsub(/OBJS.*$/.match(text).to_s, objs) }
end
