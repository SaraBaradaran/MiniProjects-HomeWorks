#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define SIZE 8

int stride = SIZE/2;
int THREADS;
sem_t sem1;

int a[SIZE] = {19,28,13,14,5,9,7,14};

void swap(int t1, int t2){
    int temp = a[t2];
    a[t2] = a[t1];
    a[t1] = temp;

}

void *Myroutine(void *id){
    int indx = (int)id;
    sem_wait(&sem1);
    printf("Thread %d is woking\n", indx);

    if(a[indx] > a[indx+stride])
        swap(indx, indx+stride);

    sem_post(&sem1);
    pthread_exit((void *)indx);
}

int main(){

    sem_init(&sem1, 0, 1);
    
    while(stride){

        THREADS = stride;
        pthread_t* threads = (pthread_t*)malloc(THREADS * sizeof(pthread_t));
        for(int i=0; i<THREADS; i++){
            pthread_create(&threads[i], NULL, Myroutine, (void *)i);
        } 
        for(int i=0; i<THREADS; i++){
            pthread_join(threads[i], NULL);    
        }
        free(threads);
        stride = stride / 2;
    }
    printf("min = %d\n", a[0]);

}