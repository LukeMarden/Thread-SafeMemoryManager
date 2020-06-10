#include "part1.h"

struct memoryBlock *head;

void initialise(void *memory, size_t size) {
    head = (void*)memory; //head will be the first item in the list
    head->size = size- sizeof(struct memoryBlock); //this allocates the size of the heap
    head->free = 1; //sets the whole heap to free
    head->next = NULL; //this points to the next bit of allocated memory

}

void *allocate(size_t bytes) {
    struct memoryBlock *curr = head; //sets the current node being searched to the first item
    void *result;
    while((((curr->size)<bytes)||((curr->free)==0))&&(curr->next!=NULL)){
        curr=curr->next; //it will meet these conditions if the node isnt big enough or is occupied
        printf("Block occupied or is not big enough\n"); //it will move onto the next node in the list
    }

    if((curr->size)==bytes){
        curr->free=0;
        result=(void*)(++curr);
        printf("Exact sized block allocated\n");
        return result;//it will meet this condition if the node is the exact size needed
    }
    else if((curr->size)>(bytes+sizeof(struct memoryBlock))){
        divide(curr,bytes);
        result=(void*)(++curr);
        printf("Block allocated using a divide\n");
        return result; //if the node is too big the node will be split, one half being allocated
    }                   //and the other part being free
    else{
        result=NULL; //this is executed if there is not a single item that meets the requirements
        printf("No memory available to allocate\n");
        return result;
    }
}

void deallocate(void *memory) {
    struct memoryBlock *curr = memory; //curr is equal to the pointer
    --curr;
    curr->free = 1; //sets the pointer to free
    combine(); //calls a method that checks for adjacent free nodes so that it can combine them
}

void divide(struct memoryBlock *needed,size_t size) {
    struct memoryBlock *new = (void *) ((void *) needed + size + sizeof(struct memoryBlock));
    new->size = (needed->size) - size - sizeof(struct memoryBlock);
    new->free = 1; //new is the part which isnt needed hence it being free
    new->next = needed->next;
    needed->size = size; //needed is the part which we need hence it being set to not free
    needed->free = 0;
    needed->next = new; //needed points to the new segment
}

void combine(){
    struct memoryBlock *curr;
    curr=head;
    while((curr->next)!=NULL){
        if((curr->free == 1) && (curr->next->free == 1)){ //if a segment and the next one is free
            curr->size+=(curr->next->size)+sizeof(struct memoryBlock); //their sizes are added
            curr->next=curr->next->next; //and next is set to the node after the adjacent one
        }
        curr=curr->next; //and it loops
    }
}

