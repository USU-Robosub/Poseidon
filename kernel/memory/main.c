#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
using namespace std;

#define DEBUG(v) printf("debug: %s\n", v)
#define DEBUG2(v) printf("debug: %u\n", v)
#define ERROR_FMT(str,arg) printf("Error: %s is not in a correct format (%s)\n", str, arg)
#define HELP "\n\n\n\
./main [flags] [address] [offset] [value] [optional:loop]\n\n\
-r: read from address\n\
-w: write to address\n\n\
(all numeric values are in hex)\n\n\n"
#define IDX_IS_HEX(v) (v == 'x') ? 2 : 0

// 0: read 1: write
static int rd_wr = 0;

int append_hex(char,int*);
int parse_string(char*,int*);
int memory_map(int,int,int,int);

/* The entry point of the program. 
 * First initialize local variables, then collect w/r flag and 
 * set local variables in their order, and finally perform
 * register access.
 */
int main(int argc, char** argv) {
	int reg_address = 0;
	int reg_offset = 0;
	int reg_value = 0;  // used in write mode
	int reg_loop = 0;
	short next = 0; // store register set flags
	argc--;

	if(argc)
	{
		for(int i = 1; i < 1+argc; i++)
		{
			// search for flag; default = read
			if(argv[i][0] == '-')
			{
				if(argv[i][1] == 'r')      rd_wr = 0;
				else if(argv[i][1] == 'w') rd_wr = 1;
				else
				{
					printf("%s is not a recognized command%s", argv[i], HELP);
					return 0;
				}
			}
			// read hex values
			else
			{
				switch(next)
				{
					case 0: // get address
						if(!parse_string(argv[i], &reg_address))
						{
							ERROR_FMT("address", argv[i]); exit(1);
						}
						next++;
						break;
					case 1: // get offset
						if(!parse_string(argv[i], &reg_offset))
                        {
                            ERROR_FMT("offset", argv[i]); exit(1);
                        }
						next++;
						break;
					case 2: // get write value
						if(!parse_string(argv[i], &reg_value))
                        {
                            ERROR_FMT("value", argv[i]); exit(1);
                        }
						next++;
						break;
					case 3: // get loop value
						if(!parse_string(argv[i], &reg_loop))
						{
							ERROR_FMT("loop", argv[i]); exit(1);
						}
						next++;
						break;
					default:
						printf("Too many arguments!%s", HELP);
						return 1;
				}
			}
		}
	}
	return memory_map(reg_address, reg_offset, reg_value, reg_loop);
}

/* Maps 65535 bytes from a given address
 * In Read  Mode: reads from register value at least once
 * In Write Mode: writes to  register value at least once
 */
int memory_map(int addr, int off, int val, int loop)
{
	int mem_fd = open("/dev/mem", O_RDWR);
    if (mem_fd < 0) {
        printf("Failed to open /dev/mem (%s)\n", strerror(errno));
        return -1;
    }
    unsigned long* ddrMem = (unsigned long *)mmap(0, 0x0000FFFF, PROT_WRITE | PROT_READ, MAP_SHARED, mem_fd, addr);
    if (ddrMem == NULL) {
        printf("Failed to map the device (%s)\n", strerror(errno));
        close(mem_fd);
        return -1;
    }

	do
	{
		if(rd_wr) ddrMem[off/4] = val; 		// write mode
		else printf("%X\n", ddrMem[off/4]); // read  mode
		loop--;
	}
	while(loop > 0);

	munmap(ddrMem, 0x0000FFFF);
  close(mem_fd);

  return 0;
}

/* Converts a base-16 string to an int */
int parse_string(char* str, int* v)
{
	int i = IDX_IS_HEX(str[1]);	// Is the hex in 0xMode?
	int j = i;
	*v = 0; // clear mem
	for(; str[i] != '\0' && i < 8+j; i++)
		if(!append_hex(str[i], v)) return 0;
	return 1;
}

/* Appends a hex character to the LSBs of an int */
int append_hex(char c, int* v)
{
	char n = c-48; //UTF8: 30

	// numeric value
	if(n >= 0 && n < 10)
	{
		*v <<= 4;
		*v |= n;
		return 1;
	}
	// capital value
	else if(n >= 17 && n < 23)
	{
		n -= 7; //UTF8: 1
		*v <<= 4;
		*v |= n;
		return 1;
	}
	// lower value
	else if(n >= 49 && n < 55)
	{
		n -= 39; //UTF8: 21
		*v <<= 4;
		*v |= n;
		return 1;
	}

	// catch parse error
	return 0;
}
