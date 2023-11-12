#ifndef LIB_H
#define LIB_H

#include <stdint.h>

#define INCREASE_MOD(x,total)   (x) = ((x) + 1) % total;
#define DECREASE_MOD(x, total)  x--;\
                if((x)<0)\
                        x=((total) + (x)) % (total);\
                else\
                    x = (x) % (total);

void * memset(void * destination, int32_t character, uint64_t length);
void * memcpy(void * destination, const void * source, uint64_t length);
int hexToString(uint64_t num, char * buffer, int fixedLength);

char *cpuVendor(char *result);

int _xadd(unsigned int * lock, int value);
int _xchg(unsigned int * lock, int value);

#endif