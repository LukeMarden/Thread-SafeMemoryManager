#ifndef THREAD_SAFEMEMORYMANAGER_PART2_H
#define THREAD_SAFEMEMORYMANAGER_PART2_H
#include<stdio.h>
#include<stddef.h>
struct memoryBlock {
    size_t size;
    int free;
    struct memoryBlock *next;
};
void initialise(void *memory, size_t size, char *algorithm);
void* (*allocate)(size_t); //function pointer
void deallocate(void *memory);
extern void *bestFit(size_t bytes);
extern void *worstFit(size_t bytes);
extern void *nextFit(size_t bytes);
extern void *firstFit(size_t bytes);
void combine();
void divide(struct memoryBlock *needed,size_t size);

#endif //THREAD_SAFEMEMORYMANAGER_PART2_H
