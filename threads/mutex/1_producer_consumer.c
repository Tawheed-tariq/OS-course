// gcc -pthread 1_producer_consumer.c -o 1_producer_consumer
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<pthread.h>
#include<stdint.h>

#define MAXSIZE 5

pthread_mutex_t mutex;
pthread_cond_t full;
pthread_cond_t empty;

int queue[MAXSIZE];
int head = 0;
int tail = 0;

void *producer(void *arg){
    printf("running producer thread \t\t");
    int data = (intptr_t)arg;
    pthread_mutex_lock(&mutex);
    if((head+1) % MAXSIZE == tail){
        printf("waiting for empty\n\n");
        pthread_cond_wait(&empty, &mutex);
    }
        
    queue[head] = data;
    printf("produced ................ %d\n\n", data);
    head = (head + 1) % MAXSIZE;
    pthread_cond_signal(&full);
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

void *consumer(){
    printf("running consumer thread \t\t");
    pthread_mutex_lock(&mutex);
    if(tail == head){
        printf("waiting for full\n\n");
        pthread_cond_wait(&full, &mutex);
    }
    
    int data = queue[tail];
    printf("Consumed _______________ %d\n\n", data);
    tail = (tail + 1) % MAXSIZE;
    pthread_cond_signal(&empty);
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

int main(){

    pthread_t producer_thread , consumer_thread;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&full, NULL);
    pthread_cond_init(&empty, NULL);

    for(int i = 0; i < MAXSIZE; i++){
        pthread_create(&producer_thread, NULL, producer, (void *)(intptr_t)(i + 10));
        pthread_create(&consumer_thread, NULL, consumer, NULL);
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&full);
    pthread_cond_destroy(&empty);
}