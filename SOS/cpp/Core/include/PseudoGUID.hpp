#ifndef PSEUDO_GUID_H
#define PSEUDO_GUID_H

// output is in the form of a guid [8]-[4]-[4]-[4]-[12] xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx
// however it is not guaranteed to be a unique id, but it is very close
// the first 4 sections are generated 4 chars at a time from a random number
// the last 12 chars are generated from the current date to the millisecond
// the date wrap time is ~8,000 years
// tested with batches of 10,000,000 generated in 1 minute, no duplicates found

#include <string>
#include <stdlib.h>
#include <sstream>
#include <ctime>

std::string generateUUID();
std::string chr12();
std::string chr8();
std::string chr4();
std::string toHex(int value);
std::string endSlice(std::string value, unsigned int length);

#endif
