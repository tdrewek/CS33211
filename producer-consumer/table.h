#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <pthread.h>

#define SHARED_MEM_SIZE 2*sizeof(int)
#define TABLE_SIZE 2
#define NUM_ITEMS 10

typedef struct {
    int buffer[2];
    int in;
    int out;
} Table;

// Semaphores
sem_t *empty;
sem_t *full;
sem_t *mutex;

// Shared memory
int shm_fd;
Table *table;

// Functions
void *producer(void *arg);
void *consumer(void *arg);
