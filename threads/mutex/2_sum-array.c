#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<pthread.h>
#include<stdint.h>

#define ARR_SIZE 10000

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void error(char *msg){
	fprintf(stderr, "%s: %s\n", msg, strerror(errno));
	exit(1);
}

int arr[ARR_SIZE];
void create_array(){
    for(int i = 0; i < ARR_SIZE; i++){
        *(arr+i) = i+1;
    }
}


int sum_part(int index){
    int sum = 0;
    for(int i = index; i < index + 1000; i++){
        pthread_mutex_lock(&lock);
        sum += *(arr+i);
        pthread_mutex_unlock(&lock);
    }
    return sum;
}

int main(){
    create_array();
    pthread_t threads[10];
    int result;
    int sum = 0;
    for(int t= 0; t < 10; t++){
        if(pthread_create(&threads[t],NULL, (void *(*)(void *))sum_part, (void *)(intptr_t)(1000*t)) == -1){
            error("cant create thread");
        }
    }

    for(int t=0; t< 10; t++){
		pthread_join(*(threads+t), (void *)&result); //waits for all extra threads to finish
        sum += result;
        printf("The sum now is %d\n", sum);
	}
    printf("\n\nThe sum of array is %d", sum);
    return 0;
}