
semaphore empty1 = 1;
semaphore empty2 = 1;
semaphore full1 = 0;
semaphore full2 = 0;

Proccess_A(){
    while(1){
        wait(empty1);
        read(buffer1, "file.txt");
        post(full1);

    }
}


Proccess_B(){
    while(1){
        wait(full1);
        copy(buffer2, buffer1);
        post(full2);
    }
}


Proccess_C(){
    while(1){
        wait(full2);
        print(buffer2);
        post(empty1);
    }
}
////////////////////////////////////////////////////////////////
pthread_cond_t cv1;
pthread_cond_t cv2;
pthread_cond_t cv3;
pthread_mutex_t mutex;

int A_done = 0;
int B_done = 0;
int C_done = 1;

Proccess_A(){
    while(1){
        mutex_lock(&mutex);
        while(C_done == 0)
            cond_wait(&cv1, &mutex);
        
        read(buffer1, "file.txt");
        A_done = 1;
        C_done = 0;
        cond_signal(&cv2);
        mutex_unlock(&mutex);

    }
}


Proccess_B(){
    while(1){
        mutex_lock(&mutex);
        while(A_done == 0)
            cond_wait(&cv2, &mutex);
        
        copy(buffer2, buffer1);
        B_done = 1;
        cond_signal(&cv3);
        mutex_unlock(&mutex);
    }
}


Proccess_C(){
    while(1){
        mutex_lock(&mutex);
        while(B_done == 0)
            cond_wait(&cv3, &mutex);
        
        print(buffer2);
        C_done = 1;
        cond_signal(&cv1);
        mutex_unlock(&mutex);
    }
}
