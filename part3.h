//
// Created by Luke Marden on 21/11/2019.
//

#ifndef THREAD_SAFEMEMORYMANAGER_PART3_H
#define THREAD_SAFEMEMORYMANAGER_PART3_H
#include<stdio.h>
#include<stddef.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
struct memoryBlock {
    size_t size;
    int free;
    struct memoryBlock *next;
};
void initialise(void *memory, size_t size, char *algorithm);
void* (*allocate)(size_t);
void deallocate(void *memory);
extern void *bestFit(size_t bytes);
extern void *worstFit(size_t bytes);
extern void *nextFit(size_t bytes);
extern void *firstFit(size_t bytes);
void combine(); //this merges two blocks of memory together if they are both free and
void divide(struct memoryBlock *needed,size_t size);
#endif //THREAD_SAFEMEMORYMANAGER_PART3_H
