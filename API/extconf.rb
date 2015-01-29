# extconf file specific to the BeagleBone Black
require 'rubygems'
require 'mkmf-rice'

# compiler flags
$CFLAGS << " -std=c++0x -Wno-deprecated"

# linker flags
# $LFLAGS << " -lmath" # link libmath.so

# make Makefile
create_makefile('DiveMaster')




# ---  white-list alternative  ---
#file_name = "Makefile"
#text = File.read(file_name)
#text = text.gsub(/SRCS.*$/.match(text).to_s, "SRCS = files.cpp")
#text = text.gsub(/OBJS.*$/.match(text).to_s, "OBJS = files.o")
#File.open(file_name, "w") {|file| file.puts text }




# find all .cpp files in working directory
require 'find'
files = []
Find.find(Dir.pwd) do |path|
	files << path if path =~ /.*\.cpp$/
end
# clean up string tokens
srcs = "SRCS = "
objs = ""
files.each do |file|
	srcs += file.gsub(Dir.pwd + "/", "")
	srcs += " "
end
objs = srcs.gsub(/\.cpp/, ".o").gsub(/SRCS\s=\s/, "OBJS = ")
# replace SRCS and OBJS variables in Makefile
file_name = "Makefile"
text = File.read(file_name)
text = text.gsub(/SRCS.*$/.match(text).to_s, srcs)
text = text.gsub(/OBJS.*$/.match(text).to_s, objs)
File.open(file_name, "w") {|file| file.puts text }
