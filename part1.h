#ifndef THREAD_SAFEMEMORYMANAGER_PART1_H
#define THREAD_SAFEMEMORYMANAGER_PART1_H

#include<stdio.h>
#include<stddef.h>
struct memoryBlock { //this stores the properties for each node
    size_t size;
    int free; // 0=Used, 1=Free
    struct memoryBlock *next; //this points to the next node
};
void initialise(void *memory, size_t size); //initialises memory of the size passed to the function
void *allocate(size_t bytes); //this allocates a block of memory
void deallocate(void *memory); //this deallocates a block of memory
void combine(); //this merges two blocks of memory together if they are both free and
void divide(struct memoryBlock *needed,size_t size); //this divides a memory block up

#endif //THREAD_SAFEMEMORYMANAGER_PART1_H

