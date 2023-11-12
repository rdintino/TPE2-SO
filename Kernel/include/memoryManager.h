#ifndef _MEM_MANAGER_H_
#define _MEM_MANAGER_H_

#include <stdint.h>
#include <stdlib.h>
#include <mm_utils.h>
#include <mm_impl.h>
#include <stddef.h>

#define SUM_PTR(ptr, num) ((uint64_t) (ptr) + (num))

#define TRUE 1
#define FALSE 0

#define HEAP_SIZE 0x100000  // 1Mb   
#define HEAP_START ((void *) 0xA00000)  // 10 Mb
#define HEAP_END ((void *) (SUM_PTR(HEAP_START, HEAP_SIZE)))


void mm_init();

void * mm_malloc(uint64_t size);

void mm_free(void * ptr);

memStatus * getMemStatus();

#endif