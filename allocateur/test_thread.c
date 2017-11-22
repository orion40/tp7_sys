#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

#include "mem.h"
#include "common.h"

#define MAX_ITER 20
#define MAX_ALLOC 1024

void afficher_zone(void *adresse, size_t taille, int free)
{
  printf("Zone %s, Adresse : %lu, Taille : %lu\n", free?"libre":"occupee",
         adresse - get_memory_adr(), (unsigned long) taille);
}

void* th1 (void* args){
    char* allocs[MAX_ITER];
    for (int i = 0; i < MAX_ITER; i++){
        puts("Thread 1 allocating...");
        allocs[i] = (char*) malloc(rand() % MAX_ALLOC);
        sleep(rand() % 2);
    }
    for (int i = 0; i < MAX_ITER; i++){
        puts("Thread 1 freeing...");
        free(allocs[i]);
        sleep(rand() % 2);
    }
    return NULL;
}

void* th2 (void* args){
    char* allocs[MAX_ITER];
    for (int i = 0; i < MAX_ITER; i++){
        puts("Thread 2 allocating...");
        allocs[i] = (char*) malloc(rand() % MAX_ALLOC);
        sleep(rand() % 2);
    }
    for (int i = 0; i < MAX_ITER; i++){
        puts("Thread 2 freeing...");
        free(allocs[i]);
        sleep(rand() % 2);
    }
    return NULL;
}

int main(int argc, char **argv){
    srand(time(NULL));
    pthread_t t1, t2;
    char* init = malloc(1);
    free(init);
    puts("Before:");
    mem_show(afficher_zone);
    pthread_create(&t1, NULL, th1, NULL);
    pthread_create(&t2, NULL, th2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    puts("After:");
    //mem_show(afficher_zone);

    return 0;
}
