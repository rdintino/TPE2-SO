#ifndef USE_BUDDY

#include "../include/memoryManager.h"

static memStatus mmStatusInfo = { 0 };

memStatus * getMemStatus() {
    return &mmStatusInfo;
}


void mm_init() {
    mmStatusInfo.freeBytes = HEAP_SIZE;
    addEOL((header_t *) HEAP_START);
}

 void * mm_malloc(uint64_t len) {
    if(len <= 0) {
        return NULL;
    }

    uint64_t newSize = MASK_LAST_BIT(len + 1 + HEADER_SIZE); // Redondea el numero
    header_t * out = findFree(newSize);

    if(out == NULL){
        return NULL;
    }
    addBlock(out, newSize);

    return (void *) SUM_PTR(out, HEADER_SIZE);
 }

 void mm_free(void * ptr) {
    if(ptr == NULL || ptr < HEAP_START || ptr >= HEAP_END){
        return;
    }

    header_t * head = (header_t *) SUM_PTR(ptr, -HEADER_SIZE);

    uint64_t size = GET_SIZE(head->size);
    mmStatusInfo.allocatedBytes -= size;
    mmStatusInfo.freeBytes += size;
    mmStatusInfo.allocatedBlocks -= 1;

    freeBlock(head);
 }

void freeBlock(header_t * ptr) {
    ptr->allocated = FALSE;

    header_t * next = (header_t *) SUM_PTR(ptr, ptr->size);
    if(!next->allocated){
        ptr->size += next->size;
    }
}

 void addBlock(header_t * ptr, uint64_t newSize) {
    uint64_t oldSize = GET_SIZE(ptr->size);

    if(IS_EOL(ptr->size)) { 
        addEOL((header_t *) SUM_PTR(ptr, newSize));

        ptr->size = newSize;
        ptr->allocated = TRUE;

        mmStatusInfo.allocatedBytes += newSize;
        mmStatusInfo.freeBytes -= newSize;
    }
    else if(newSize + MIN_REQUEST < oldSize) { // divide
        ptr->size = newSize;
        ptr->allocated = TRUE;

        mmStatusInfo.allocatedBytes += newSize;
        mmStatusInfo.freeBytes -= newSize;

        ptr = (header_t *) SUM_PTR(ptr, newSize); // proximo bloque

        ptr->size = oldSize - newSize;
        ptr->allocated = FALSE; 
    }
    else { 
        ptr->size = oldSize;
        ptr->allocated = TRUE;

        mmStatusInfo.allocatedBytes += oldSize;
        mmStatusInfo.freeBytes -= oldSize;
    }
    mmStatusInfo.allocatedBlocks += 1;
 }

 header_t * findFree(uint64_t len) {
     header_t * ptr = (header_t *) HEAP_START;

     while( !IS_EOL(ptr->size) && (ptr->allocated || GET_SIZE(ptr->size) < len) ){
         ptr = (header_t *) SUM_PTR(ptr, GET_SIZE(ptr->size));
     }

     if(IS_EOL(ptr->size)) {
         // Check if it fits
         if(SUM_PTR(ptr, len + EOL_SIZE) > (uint64_t) HEAP_END){
             return NULL;
         }
     }
     return ptr;
 }

 void addEOL(header_t * ptr) {
    ptr->size = 0;
    ptr->allocated = TRUE;
 }

#endif 