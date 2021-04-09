#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define AVAILABLE 0
#define OCCUPIED 1

#define IDLE 2
#define THINKING 3
#define EATING 4

typedef struct {
    sem_t is_occupied;
    sem_t is_full;
    sem_t is_void;
    int *storage;
    int size;
} Buffer;

typedef struct {
    Buffer *buffer;
    int batch_size;
} Producer;

typedef struct {
    Buffer *buffer;
    int batch_size;
} Consumer;


Buffer* create_buffer(int size);
Producer* create_producer(int batch_size, Buffer * buffer);
Consumer* create_consumer(int batch_size, Buffer * buffer);
void * producer_behavior(void * arg);
void * consumer_behavior(void * arg);
void print_buffer(Buffer * buffer, char * str);