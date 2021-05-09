#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/wait.h>

#define SIZE 5

int main(){
    
    int* data = mmap ( NULL, SIZE*sizeof(int), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
    if(data == MAP_FAILED){
        printf("Mapping Failed\n");
        return 1;
    }
    for(int i=0; i<SIZE; i++){
        data[i] = i+1;
    }

    int child_pid = fork();
    if(child_pid == 0){
        for(int i=0; i<SIZE; i++)
            data[i] = data[i] * 10;
    }
    else{

        waitpid(child_pid, NULL, 0);
        printf("child work has been finished\n");
        for(int i=0; i<SIZE; i++){
            printf("data[%d] = %d\n", i, data[i]);
        }
    }
    return 0;
}