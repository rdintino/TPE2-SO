#ifdef USE_BUDDY
#ifndef _MM_BUDDY_H_
#define _MM_BUDDY_H_

/*
La implementacion del "buddy" usa un arbol binario para tener en cuenta que bloques fueron alocados y divididos
*/

#define MIN_SIZE_CLASS 6

#define HEADER_SIZE (sizeof(uint64_t)) 

#define POW_2(exp) ((uint64_t) 1 << (exp))

typedef struct TNode{
    char isAllocated;
    char isSplit;
} TNode;


int getSmallestAvailable(unsigned int sizeClass);

#endif // _MM_BUDDY_H_
#endif // USE_BUDDY