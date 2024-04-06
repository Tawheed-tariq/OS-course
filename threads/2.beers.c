#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<pthread.h> // header file for pthread library

pthread_mutex_t beers_lock = PTHREAD_MUTEX_INITIALIZER;

void error(char *msg){
	fprintf(stderr, "%s: %s\n", msg, strerror(errno));
	exit(1);
}

int beers = 2000000; //begin with 2 million bears
void* drink_lots(void *a){ //Each thread will run this function.
	int i;
	pthread_mutex_lock(&beers_lock);
	for (i = 0; i < 100000; i++) {
		beers = beers - 1;
	}
	pthread_mutex_unlock(&beers_lock);
	printf("beers = %i\n", beers);
	//The function will reduce the beers variable by 100,000.
	return NULL;
}

int main(){
	pthread_t threads[20];
	int t;
	printf("%i bottles of beer on the wall\n%i bottles of beer\n", beers, beers);

	//create 20 threads that will run above function
	for(t=0; t< 20; t++){
		if(pthread_create(threads+t, NULL, drink_lots, NULL) == -1){
			error("cant create thread");
		}
	}

	void* result;
	for(t=0; t< 20; t++){
		pthread_join(*(threads+t), &result); //waits for all extra threads to finish
	}

	printf("There are now %i bottles of beer on the wall\n", beers);
	return 0;
}