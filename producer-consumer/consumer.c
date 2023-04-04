#include "table.h"

int main(int argc, char *argv[]) {
    int shm_fd;
    void *table;
    sem_t *mutex, *items;

    // Open shared memory and semaphores
    shm_fd = shm_open("table", O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(1);
    }
    table = mmap(0, SHARED_MEM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (table == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }
    mutex = sem_open("mutex", O_CREAT, 0666, 1);
    items = sem_open("items", O_CREAT, 0666, 0);
    if (mutex == SEM_FAILED || items == SEM_FAILED) {
        perror("sem_open");
        exit(1);
    }

    // Consume items from the table
    int consumed_items = 0;
    while (consumed_items < NUM_ITEMS) {
        sem_wait(items); // wait for an item to be available on the table
        sem_wait(mutex); // acquire the mutex

        // consume an item from the table
        int item = ((int *)table)[consumed_items % TABLE_SIZE];
        printf("Consumer: Consuming item %d\n", item);
        consumed_items++;

        sem_post(mutex); // release the mutex
    }

    // Clean up
    sem_close(mutex);
    sem_close(items);
    shm_unlink("table");
    sem_unlink("mutex");
    sem_unlink("items");
    return 0;
}
