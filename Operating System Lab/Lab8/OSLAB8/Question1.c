#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define SIZE 5
#define THREADS 3

int product = 0;
sem_t sem1;

int a[SIZE] = {1,2,3,4,5};
int b[SIZE] = {5,4,3,2,1};

void *Myroutine(void *id){
    int indx = (int )id;
    sem_wait(&sem1);
    printf("Thread %d is woking\n", indx);
    for(int i=indx; i<SIZE; i+=THREADS){
        product += a[indx] * b[indx];
    }
    sem_post(&sem1);
    pthread_exit((void *)indx);
}

int main(){

    sem_init(&sem1, 0, 1);
    pthread_t threads[THREADS];

    for(int i=0; i<THREADS; i++){
        pthread_create(&threads[i], NULL, Myroutine, (void *)i);
    } 
    for(int i=0; i<THREADS; i++){
        pthread_join(threads[i], NULL);    
    }
    printf("product = %d\n", product);

}