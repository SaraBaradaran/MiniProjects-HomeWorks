
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <signal.h>
#include <semaphore.h>
#include <pthread.h>

#define THREADS 20
// north_crossed_cars shows the number of cars which crossed north way already
int north_crossed_cars = 0;
int south_crossed_cars = 0;
// north_way is 1 if the way is open for going to north now
int north_way = 0;
int south_way = 0;
// north_exist is 1 if there is at least one car that want to go south
int north_exist = 0;
int south_exist = 0;

pthread_cond_t north_cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t south_cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* north(void * tid){

        north_exist = 1; // at least one car want to cross the way to going north
        pthread_mutex_lock(&mutex);
       
        while(south_way == 1) //the north cars must be stop while south cars cross
            pthread_cond_wait(&north_cond, &mutex);

        if(north_crossed_cars == 0){ //if the first car cross the north way then he open the way for others
            north_way = 1;
            for(int i=0; i<4; i++)
                pthread_cond_signal(&north_cond);
        }

        north_crossed_cars ++;
        printf("car #%d crossed from north way --> %d\n", tid, north_crossed_cars);
        // if 5 or more cars crossed and there is at least one south car then way must be yielded to south cars
        if (north_crossed_cars >= 5 && south_exist){ 

            north_way = 0;
            south_way = 1;
            north_crossed_cars = 0;
            printf("====================\n");
            pthread_cond_signal(&south_cond);
        }
        north_exist = 0;
        pthread_mutex_unlock(&mutex);
}

void* south(void * tid){

        south_exist = 1;
        pthread_mutex_lock(&mutex);

        while(north_way == 1)
            pthread_cond_wait(&south_cond, &mutex);

        if(south_crossed_cars == 0){
            south_way = 1;
            for(int i=0; i<4; i++)
                pthread_cond_signal(&south_cond);
        }

        south_crossed_cars ++;
        printf("car #%d crossed from south way --> %d\n", tid, south_crossed_cars);
       
        if (south_crossed_cars >= 5 && north_exist){
            north_way = 1;
            south_way = 0;
            south_crossed_cars = 0;
            printf("====================\n");
            pthread_cond_signal(&north_cond);
        }
        south_exist = 0;
        pthread_mutex_unlock(&mutex);
}
int main(){

    pthread_t* threads = (pthread_t*)malloc(THREADS * sizeof(pthread_t));
    for(int i=0; i<THREADS; i++){
        if(i%2)
            pthread_create(&threads[i], NULL, north, (void *)i);
        else
            pthread_create(&threads[i], NULL, south, (void *)i);
    }   
    for(int i=0; i<THREADS; i++){
        pthread_join(threads[i], NULL);    
    }
}
