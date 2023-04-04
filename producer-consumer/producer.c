#include "table.h"

void *producer(void *arg) {
    Table *table = (Table *)arg;
    int item = 0;

    while (1) {
        // Produce item
        item++;
        printf("Produced item %d\n", item);

        // Acquire empty semaphore
        sem_wait(empty);

        // Acquire mutex semaphore
        sem_wait(mutex);

        // Put item on table
        table->buffer[table->in] = item;
        table->in = (table->in + 1) % 2;
        printf("Put item %d on table\n", item);

        // Release mutex semaphore
        sem_post(mutex);

        // Release full semaphore
        sem_post(full);

        // Wait before producing another item
        sleep(1);
    }
}

int main() {
    // Initialize semaphores
    empty = sem_open("/empty", O_CREAT, 0666, 2);
    full = sem_open("/full", O_CREAT, 0666, 0);
    mutex = sem_open("/mutex", O_CREAT, 0666, 1);

    // Create shared memory
    shm_fd = shm_open("/table", O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, SHARED_MEM_SIZE);
    table = mmap(NULL, SHARED_MEM_SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

    // Initialize table
    table->in = 0;
    table->out = 0;

    // Create producer thread
    pthread_t prod_thread;
    pthread_create(&prod_thread, NULL, producer, (void *)table);

    // Wait for producer thread to finish
    pthread_join(prod_thread, NULL);

    // Clean up
    munmap(table, SHARED_MEM_SIZE);
    shm_unlink("/table");
    sem_close(empty);
    sem_close(full);
    sem_close(mutex);
    sem_unlink("/empty");
    sem_unlink("/full");
    sem_unlink("/mutex");

    return 0;
}