#include "ProducerConsumer.h"

int main(int argc, char * args[])
{
    if(argc != 4)
    {
        printf("ERROR: Number of arguments is wrong. \nYou need enter 3 arguments.\n|Buffer Size| Producer Batch Size| Consumer Batch Size|\n");
        return 0;
    }else
    {
        int buffer_size = atoi(args[1]);
        int producer_batch_size = atoi(args[2]);
        int consumer_batch_size = atoi(args[3]);


        #ifdef DEBUG
        printf("---------Features---------\n");
        printf("|Log: Tamanho do buffer = %d\n", buffer_size);
        printf("|Log: Vazão de produção = %d\n", producer_batch_size);
        printf("|Log: Vazão de comsumo = %d\n", consumer_batch_size);
        printf("--------------------------\n");
        #endif
        
        Buffer * buffer = create_buffer(buffer_size);
        Producer *producer = create_producer(producer_batch_size, buffer);
        Consumer *consumer = create_consumer(consumer_batch_size, buffer);

        pthread_t threads[2];

        int ret = 0;
        
        ret = pthread_create(&threads[0], NULL, &producer_behavior, producer);
        if(ret != 0) {
            printf ("Create pthread error!\n");
            exit (1);
        }
        
       
        ret = pthread_create(&threads[1], NULL, &consumer_behavior, consumer);
        if(ret != 0) {
            printf ("Create pthread error!\n");
            exit (1);
        }
        
       pthread_join(threads[0], NULL);
       pthread_join(threads[1], NULL);
    }    
}

