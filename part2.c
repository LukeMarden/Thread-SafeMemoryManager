#include "part2.h"
struct memoryBlock *head;
static struct memoryBlock *next; //stores the next node to go to
void divide(struct memoryBlock *needed,size_t size) {
    struct memoryBlock *new = (void *) ((void *) needed + size + sizeof(struct memoryBlock));
    new->size = (needed->size) - size - sizeof(struct memoryBlock);
    new->free = 1;
    new->next = needed->next;
    needed->size = size;
    needed->free = 0;
    needed->next = new;
    next = new; //this stores the node for next fit

}

void combine(){
    struct memoryBlock *curr;
    curr=head;
    while((curr->next)!=NULL){
        if((curr->free == 1) && (curr->next->free == 1)){
            curr->size+=(curr->next->size)+sizeof(struct memoryBlock);
            curr->next=curr->next->next;
        }
//        prev=curr;
        curr=curr->next;
    }
}
void initialise(void *memory, size_t size, char *algorithm) {
    head = (void*)memory;
    head->size = size- sizeof(struct memoryBlock);
    head->free = 1;
    head->next = NULL;
    if (algorithm == "BestFit") { //this selects the algorithm
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
void* (*allocate)(size_t); //this function pointer stores the method of memory managment to use
void deallocate(void *memory) {
    struct memoryBlock *curr = memory;
    --curr;
    curr->free = 1;
    combine();
    printf("Block Deallocated\n");
}

extern void *bestFit(size_t bytes) {
    struct memoryBlock *best = NULL; //stores the best fitting segment
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
                printf("Exact fitting block allocated\n");
                return result; //if it finds a block of the exact size it is allocated there

            } else {
                printf("Possible block located. size = %i\n", node->size);
                best = node; //everytime a node that is smaller is found, best is overwritten

            }
        }
        node =node->next; //iterates
    }
    if (best !=NULL) {
        printf("Best block size: %i\n", best->size); //the best node at the end
        divide(best, bytes); //divides it
        result=(void*)(++best);
        printf("Block allocated using a divide\n");
        return result;
    } else {
        result=NULL;
        printf("No memory available to allocate\n"); //if best == null there is no available node
        return result;
    }
}

extern void *worstFit(size_t bytes) {
    struct memoryBlock *worst = NULL; //works the same as best but fits the biggest segment
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
            printf("Exact fitting block allocated\n");
            return result;

        } else {
            divide(worst, bytes);
            result=(void*)(++worst);
            printf("Block allocated using a divide\n");
            return result;
        }

    } else {
        result=NULL;
        printf("No memory available to allocate\n");
        return result;
    }
}
extern void *nextFit(size_t bytes) {
    int looped = 0; //this is used to determine if it has gone through every segment before saying
    if (next == NULL) { //that there is no available space
        next = head;
        looped = 1;
    }
    struct memoryBlock *curr = next; //loads the global variable next
    void *result;
    //the rest works the same as first fit
    while((((next->size)<bytes)||((curr->free)==0))&&(curr->next!=NULL)){
        curr=curr->next;
        printf("Block occupied or is not big enough\n");
    }
    if((curr->size)==bytes){
        curr->free=0;
        result=(void*)(++curr);
        printf("Exact fitting block allocated\n");
        next = curr->next; //overrides next with the next node to go to
        return result;
    }
    else if((curr->size)>(bytes+sizeof(struct memoryBlock))){
        divide(curr,bytes);
        result=(void*)(++curr);
        printf("Block allocated using a divide\n");
        return result;
    }
    else{
        if (looped == 0) {
            next = NULL;
            return nextFit(bytes);
        }
        else {
            result=NULL;
            printf("No memory available to allocate\n");
            return result;
        }


    }
}
extern void *firstFit(size_t bytes) { //see part1.c
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
        return result;
    }
    else if((curr->size)>(bytes+sizeof(struct memoryBlock))){
        divide(curr,bytes);
        result=(void*)(++curr);
        printf("Block allocated using a divide\n");
        return result;
    }
    else{
        result=NULL;
        printf("No memory available to allocate\n");
        return result;
    }
}

