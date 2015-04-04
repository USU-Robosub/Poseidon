require 'mkmf-rice'

str_flg = " -std=c++0x -O3 -Wall -Wextra -Wdouble-promotion "+
          "-Wno-deprecated -Ilibs/pstreams-0.8.1"
$CFLAGS << str_flg

create_makefile('Server')
