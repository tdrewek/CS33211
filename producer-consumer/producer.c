#include "table.h"

// producer code
int main() {
    srand(time(NULL));
    int shared = shm_open("/Shared_memory", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR); // shared memory location
    if (shared == -1){
        printf("shm_open() ERROR");
    }
    if (ftruncate(shared, sizeof(struct table)) == -1){
        printf("ftruncate() ERROR");
    } else {
        ftruncate(shared, sizeof(struct table));
    }
    struct table *producer;
    producer = mmap(0, sizeof(struct table), PROT_READ|PROT_WRITE, MAP_SHARED, shared, 0); // pointer to shared buffer
    if (producer == MAP_FAILED){
        printf("mmap() ERROR");
    }

    // initializing the semaphores
    sem_init(&producer->emptySpaces, 1, TABLE_SIZE); // setting empty spaces to 2
    sem_init(&producer->usedSpaces, 1, 0); // setting used spaces to 0

    // setting the shared array buffer elements to 0 to show they are empty
    for (int i = 0; i < TABLE_SIZE; ++i){
        producer->buffer[i] = 0;
    }

    int itemSets = 0;
    while (itemSets < MAX_ITEM_SETS){
        while (producer->buffer[0] != 0 && producer->buffer[1] != 0); // busy while buffer has itemss
            sleep(1);
            sem_wait(&producer->emptySpaces);
        int itemValue;
        for (int i = 0; i < TABLE_SIZE; ++i){ // produces 2 itemss
            itemValue = rand() % 100 + 1; // get unique items value
            if (itemValue == 0) { // if somehow 0 is randomly generated, sets to 1
                itemValue = 1;
            }
            producer->buffer[i] = itemValue;
            printf("producer added %d\n", itemValue);
        }
        ++itemSets;
        sem_post(&producer->usedSpaces);
    }
    return 0;
}