//gcc -pthread 4_multiplication_of_matrices.c -o 4_multiplication_of_matrices
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<pthread.h>
#include<stdint.h>

#define SIZE 3
#define MAX_THREADS 3

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

int mat1[SIZE][SIZE];
int mat2[SIZE][SIZE];
int res[SIZE][SIZE] = {0};

//fill matrix with random values
void fill_matrix(){
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            mat1[i][j] = rand() % 10;
            mat2[i][j] = rand() % 10;
        }
    }
}

void print_matrix(int mat[][SIZE]){
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) 
            printf("%d\t", mat[i][j]);
        printf("\n");
    }
    printf("\n\n");
}

//mutiply row with columns of matrices using thread passing thread index as argument
void *multiply(void *arg){
    int index = (intptr_t)arg;
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            res[index][i] += mat1[index][j] * mat2[j][i];
        }
    }
    pthread_exit(NULL);
}


void error(char *msg){
	fprintf(stderr, "%s: %s\n", msg, strerror(errno));
	exit(1);
}

int main(){
    fill_matrix();
    printf("MATRIX 1\n");
    print_matrix(mat1);
    printf("MATRIX 2\n");
    print_matrix(mat2);

    pthread_t threads[MAX_THREADS];

    for(int t= 0; t < MAX_THREADS; t++){
        if(pthread_create(&threads[t],NULL, multiply, (void *)(intptr_t)(t)) == -1){
            error("cant create thread");
        }
    }

    for(int t=0; t< MAX_THREADS; t++){
		pthread_join(*(threads+t), NULL); //waits for all extra threads to finish
	}

    printf("Multiplication of matrix 1 and matrix 2\n");
    print_matrix(res);
}