#include "table.h"

// consumer code
int main() {
    int shared = shm_open("/Shared_memory", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (shared == -1){
        printf("shm_open() ERROR");
    }
    if (ftruncate(shared, sizeof(struct table)) == -1){
        printf("ftruncate() ERROR");
    } else {
        ftruncate(shared, sizeof(struct table));
    }
    struct table *consumer;
    consumer = mmap(0, sizeof(struct table), PROT_READ|PROT_WRITE, MAP_SHARED, shared, 0); // pointer to shared buffer
    if (consumer == MAP_FAILED){
        printf("mmap() ERROR");
    }

    int itemSets = 0;
    while(itemSets < MAX_ITEM_SETS) {
        
        while(consumer->buffer[0] == 0 && consumer->buffer[1] == 0); // busy
            sleep(1);
            sem_wait(&consumer->usedSpaces);
        for (int i = 0; i < TABLE_SIZE; ++i) {
            printf("consumer removed %d\n", consumer->buffer[i]);
            consumer->buffer[i] = 0; // create empty space
        }
        ++itemSets;
        sem_post(&consumer->emptySpaces);
    }
    return 0;
}