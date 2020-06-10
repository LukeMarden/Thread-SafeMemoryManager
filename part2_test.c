#include "part2.h"
int main() {
    void *memory[20000];

    initialise(memory, 20000, "BestFit");
    void *a = allocate(1000);
    void *b = allocate(900);
    void *c = allocate(1000);
    void *d = allocate(800);
    void *e = allocate(1000);
    deallocate(b);
    deallocate(d);
    void *f = allocate(700);
    printf("Allocation and deallocation is done successfully!\n\n");

    initialise(memory, 20000, "WorstFit");
    void *g = allocate(1000);
    void *h = allocate(900);
    void *i = allocate(1000);
    void *j = allocate(800);
    void *k = allocate(1000);
    deallocate(h);
    deallocate(j);
    void *l = allocate(700);
    printf("Allocation and deallocation is done successfully!\n\n");

    initialise(memory, 20000, "FirstFit");
    void *m = allocate(1000);
    void *n = allocate(900);
    void *o = allocate(1000);
    void *p = allocate(800);
    void *q = allocate(1000);
    void *r = allocate(700);
    void *s = allocate(1000);
    deallocate(n);
    deallocate(p);
    deallocate(r);
    void *t = allocate(700);
    printf("Allocation and deallocation is done successfully!\n\n");

    initialise(memory, 20000, "NextFit");
    void *u = allocate(5000);
    void *v = allocate(5000);
    void *w = allocate(5000);
    void *x = allocate(1000);
    void *y = allocate(1000);
    void *z = allocate(1000);
    void *aa = allocate(1000);
    deallocate(v);
    void *bb = allocate(2000);
    deallocate(bb);
    printf("Allocation and deallocation is done successfully!\n\n");
}


