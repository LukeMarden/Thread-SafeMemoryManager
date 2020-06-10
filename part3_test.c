#include "part3.h"
int main() {
    void *memory[20000];
    initialise(memory, 20000, "");
    pthread_t allo1 , allo2, allo3;
    pthread_create(&allo1, NULL, allocate, 1000);
    pthread_create(&allo2, NULL, allocate, 1000);
    pthread_create(&allo3, NULL, allocate, 1000);
    printf("In main \nthread id = %d\n", allo1);
    printf("In main \nthread id = %d\n", allo2);
    printf("In main \nthread id = %d\n", allo3);
    pthread_join(allo1, NULL);
    pthread_join(allo2, NULL);
    pthread_join(allo3, NULL);
}

