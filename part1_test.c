#include "part1.h"
int main() {
    void *memory[20000];
    initialise(memory, 20000);
    void *x=allocate(600);
    void *p=allocate(1000);
    void *i=allocate(1000);
    deallocate(x);
    void *f=allocate(600);
    int *g=(int*)allocate(700* sizeof(int));
    void *u=allocate(700* sizeof(int));
    deallocate(g);
    printf("Allocation and deallocation is done successfully!");
}
