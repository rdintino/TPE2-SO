#ifndef USE_BUDDY

#ifndef _MM_IMPL_H_
#define _MM_IMPL_H_

/*
Basado en : https://www.youtube.com/watch?v=74s0m4YoHgM
El asignador de memoria usa una lista implicita de bloques que soporta hacer merge-forward.
*/

#include "memoryManager.h"

typedef union header_t {
    uint64_t size;
    uint8_t allocated : 1;  // bit_0
} header_t;

#define HEADER_SIZE (sizeof(header_t))
#define EOL_SIZE HEADER_SIZE
#define MIN_REQUEST (HEADER_SIZE + 2)

// *ptr % 2 == 0 => no asignada / free
// -2 = 111...1110
#define MASK_LAST_BIT(num) ((num) & ~0x1)
#define GET_SIZE(size) (MASK_LAST_BIT(size))

// size == 0 && allocated == 1 => EOL
// si *ptr == 1 porque 1 = 000...001
#define IS_EOL(size) ( !(GET_SIZE(size) > 0) )



void freeBlock(header_t * ptr);

void addBlock(header_t * ptr, uint64_t len);

header_t * findFree(uint64_t len);

/**
EOL means End of List
*/
void addEOL(header_t * ptr);

#endif 
#endif 