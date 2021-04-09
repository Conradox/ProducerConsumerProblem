#include "ProducerConsumer.h"

Buffer* create_buffer(int size)
{
    Buffer * new_buffer = (Buffer *) malloc(sizeof(Buffer));
    new_buffer->size = size;
    new_buffer->storage = (int *) malloc(sizeof(int) * size);
    for(int i = 0; i < size; i++)
    {
        new_buffer->storage[i] = -1;
    }

    sem_init(&(new_buffer->is_occupied), 0, 1);
    sem_init(&(new_buffer->is_full), 0, size);
    sem_init(&(new_buffer->is_void), 0, 0);
    
    return new_buffer;   
}

Producer* create_producer(int batch_size, Buffer * buffer)
{
    Producer * new_producer = (Producer *) malloc(sizeof(Producer));
    new_producer->batch_size = batch_size;
    new_producer->buffer = buffer;
    
    return new_producer;   
}

Consumer* create_consumer(int batch_size, Buffer * buffer)
{
    Consumer * new_comsumer = (Consumer *) malloc(sizeof(Consumer));
    new_comsumer->batch_size = batch_size;
    new_comsumer->buffer = buffer;
    
    return new_comsumer;   
}

void * producer_behavior(void * arg)
{
    Producer * me = (Producer *) arg;
    int position = 0;
    int res;
    while(1)
    {
        sem_wait(&me->buffer->is_occupied);
        for(int i = 0; i < me->batch_size; i++)
        {
            res = sem_trywait(&me->buffer->is_full);
            if(res == 0)
            {
                me->buffer->storage[position] = (int) rand() % 100;
                position = (int) (position + 1) % me->buffer->size;
                sem_post(&me->buffer->is_void);
            }else
            {
                break;
            }
        }
        #ifdef DEBUG
        print_buffer(me->buffer, "Producer");
        #endif
        sem_post(&me->buffer->is_occupied);
        #ifdef DELAY
            sleep(DELAY);
        #endif
    }
}

void * consumer_behavior(void * arg)
{
    Consumer * me = (Consumer *) arg;
    int position = 0;
    int res;
    while(1)
    {
        sem_wait(&me->buffer->is_occupied);
        for(int i = 0; i < me->batch_size; i++)
        {
            res = sem_trywait(&me->buffer->is_void);
            if(res == 0)
            {
                me->buffer->storage[position] = -1;
                position = (int) (position + 1) % me->buffer->size;
                sem_post(&me->buffer->is_full);
            }else
            {
                break;
            }
        }
        #ifdef DEBUG
        print_buffer(me->buffer, "Consumer");
        #endif
        sem_post(&me->buffer->is_occupied);
        #ifdef DELAY
            sleep(DELAY);
        #endif
    }
}

void print_buffer(Buffer * buffer, char * str)
{
    int i = 0;
    if(buffer->size > 0)
    {
        if(buffer->storage[i] == -1)
        {
            printf("|  |");
        }else{
            printf("%d|", buffer->storage[i]);
        }
        for(i = 1; i < buffer->size; i++)
        {
            if(buffer->storage[i] == -1)
            {
                printf("  |");
            }else{
                printf("%d|", buffer->storage[i]);
            }
        }
    }
    int void_value;
    int full_value;
    sem_getvalue(&buffer->is_void, &void_value);
    sem_getvalue(&buffer->is_full, &full_value);
    printf(" <- %s| VOID %d| FULL %d|\n", str, void_value, full_value);
}