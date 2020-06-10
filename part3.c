//
// Created by Luke Marden on 21/11/2019.
//

#include "part3.h"
static pthread_mutex_t locklist = PTHREAD_MUTEX_INITIALIZER; //this is the lock
pthread_cond_t signal = PTHREAD_COND_INITIALIZER;
struct memoryBlock *head;
static struct memoryBlock *next;
void divide(struct memoryBlock *needed,size_t size) {
    struct memoryBlock *new = (void *) ((void *) needed + size + sizeof(struct memoryBlock));
    new->size = (needed->size) - size - sizeof(struct memoryBlock);
    new->free = 1;
    new->next = needed->next;
    needed->size = size;
    needed->free = 0;
    needed->next = new;
    next = new;

}

void combine(){
    struct memoryBlock *curr;
    curr=head;
    while((curr->next)!=NULL){
        if((curr->free == 1) && (curr->next->free == 1)){
            curr->size+=(curr->next->size)+sizeof(struct memoryBlock);
            curr->next=curr->next->next;
        }
        curr=curr->next;
    }
}
void initialise(void *memory, size_t size, char *algorithm) {
    head = (void*)memory;
    head->size = size- sizeof(struct memoryBlock);
    head->free = 1;
    head->next = NULL;
    if (algorithm == "BestFit") {
        allocate = &bestFit;
        printf("Best Fit method selected\n");
    }
    else if (algorithm == "WorstFit") {
        allocate = &worstFit;
        printf("Worst Fit method selected\n");
    }
    else if (algorithm == "NextFit") {
        allocate = &nextFit;
        next = head;
        printf("Next Fit method selected\n");
    }
    else {
        allocate = &firstFit;
        printf("First Fit method selected\n");
    }

}
void* (*allocate)(size_t);
void deallocate(void *memory) {
    pthread_mutex_lock(&locklist); //this locks it so another thread cant access it
    printf("In function \nthread id = %d\n", pthread_self());
    struct memoryBlock *curr = memory;
    --curr;
    curr->free = 1;
    combine();
    printf("Block Deallocated\n");
    pthread_mutex_unlock(&locklist); //this unlocks it so that another thread can access it
    pthread_cond_signal(&signal);
}

extern void *bestFit(size_t bytes) {
    pthread_mutex_lock(&locklist);
    printf("In function \nthread id = %d\n", pthread_self());
    struct memoryBlock *best = NULL;
    struct memoryBlock *node = head;
    void *result;
    while (node!=NULL) {
        if (node->free == 0 || node->size < bytes) {
            printf("Block Occupied or Is Not Big Enough\n");

        }
        else if ((node->size>= bytes) && (best==NULL || node->size < best->size)) {
            if (node->size == bytes) {
                node->free=0;
                result=(void*)(++node);
                printf("Exact sized block allocated\n");
                return result;

            } else {
                printf("Possible block located. size = %i\n", node->size);
                best = node;

            }
        }
        node =node->next;
    }
    if (best !=NULL) {
        printf("Best block size: %i\n", best->size);
        divide(best, bytes);
        result=(void*)(++best);
        printf("Block allocated using a divide\n");

    } else {
        result=NULL;
        printf("Sorry. No sufficient memory to allocate\n");

    }
    pthread_mutex_unlock(&locklist);
    pthread_cond_signal(&signal);
    return result;


}

extern void *worstFit(size_t bytes) {
    pthread_mutex_lock(&locklist);
    printf("In function \nthread id = %d\n", pthread_self());
    struct memoryBlock *worst = NULL;
    struct memoryBlock *node = head;
    void *result;
    while (node!=NULL) {
        if (node->free == 0 || node->size < bytes) {
            printf("Block Occupied or Is Not Big Enough\n");
        }
        else if ((node->size>= bytes) && (worst==NULL || node->size > worst->size)) {
            printf("Possible block located. size = %i\n", node->size);
            worst = node;
        }
        node = node->next;
    }
    if (worst !=NULL) {
        printf("Worst Block Size: %i\n", worst->size);
        if (worst->size == bytes) {
            worst->free=0;
            result=(void*)(++worst);
            printf("Exact sized block allocated\n");


        } else {
            divide(worst, bytes);
            result=(void*)(++worst);
            printf("Block allocated using a divide\n");

        }

    } else {
        result=NULL;
        printf("No memory available to allocate");

    }
    pthread_mutex_unlock(&locklist);
    pthread_cond_signal(&signal);
    return result;
}
extern void *nextFit(size_t bytes) {
    pthread_mutex_lock(&locklist);
    printf("In function \nthread id = %d\n", pthread_self());
    int looped = 0;
    if (next == NULL) {
        next = head;
        looped = 1;
    }
    struct memoryBlock *curr = next;
    void *result;

    while((((next->size)<bytes)||((curr->free)==0))&&(curr->next!=NULL)){
        curr=curr->next;
        printf("Block occupied or is not big enough\n");
    }
    if((curr->size)==bytes){
        curr->free=0;
        result=(void*)(++curr);
        printf("Exact sized block allocated\n");
        next = curr->next;
    }
    else if((curr->size)>(bytes+sizeof(struct memoryBlock))){
        divide(curr,bytes);
        result=(void*)(++curr);
        printf("Block allocated using a divide\n");
    }
    else{
        if (looped == 0) {
            next = NULL;
            return nextFit(bytes);
        }
        else {
            result=NULL;
            printf("No memory available to allocate\n");
        }


    }
    pthread_mutex_unlock(&locklist);
    pthread_cond_signal(&signal);
    return result;
}
extern void *firstFit(size_t bytes) {
    pthread_mutex_lock(&locklist);
    printf("In function \nthread id = %d\n", pthread_self());
    struct memoryBlock *curr = head;
    void *result;
    while((((curr->size)<bytes)||((curr->free)==0))&&(curr->next!=NULL)){
        curr=curr->next;
        printf("Block occupied or is not big enough\n");
    }

    if((curr->size)==bytes){
        curr->free=0;
        result=(void*)(++curr);
        printf("Exact sized block allocated\n");
        
    }
    else if((curr->size)>(bytes+sizeof(struct memoryBlock))){
        divide(curr,bytes);
        result=(void*)(++curr);
        printf("Block allocated using a divide\n");
        
    }
    else{
        result=NULL;
        printf("No memory available to allocate\n");
        
    }
    pthread_mutex_unlock(&locklist);
    pthread_cond_signal(&signal);
    return result;
}