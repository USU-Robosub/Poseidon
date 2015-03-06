# use to compile main.c: "> comp_c main"
function comp_c {
  # g++ [fileA.c] [fileB.c] [etc] -o [Program]
  # g++ -c [file.c] => file.o
  # g++ [fileA.o] [fileB.o] [etc] -o [Program]
  g++ $1.c -o $1
}

# use to read register address (once)
# "> readm 0x48304000 10"
function readm {
  ./main -r $1 $2 0 1
}

# use to write register address (once)
# "> writem 0x48304000 214 61A8"
function writem {
  ./main -w $1 $2 $3 1
}

# ----------------------------------------------------- #
# A 'BUS ERROR' is thrown if either the device's  clock
# is disabled (or gated), or if the specific  registers
# require elevated provledges (not sudo/root).

# A 'SEGMENTATION FAULT' is thrown when a  register  is
# being accessed outside it's permissible scope. So for
# the case of  ./main  if  a  register  offset  exceeds
# ADDR + 0xFFFF, a seg fault will be thrown.  Also  for
# the OMAP3/4 chips, if a hex value in the third  digit
# is provided (0xXXXXXn00), a seg fault  will  also  be 
# thrown. In these cases,  instead  include  the  thrid
# digit in the offset value:
#
#          0x48304200 0 -> 0x48304000 200.
# ----------------------------------------------------- #
