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

