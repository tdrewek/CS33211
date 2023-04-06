#ifndef TABLE_H
#define TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <pthread.h>

// max amount of items to be produced and consumed
const int MAX_ITEMS = 20;
// max amount of items that are allowed to be on the table at once
const int TABLE_SIZE = 2;

struct table {
    int buffer[TABLE_SIZE]; // shared array buffer for the two programs to use in synchronicity
    sem_t emptySpaces; // the current amount of empty spaces on the table
    sem_t usedSpaces; // the current amount of used spaces on the table
};

#endif // TABLE_H
