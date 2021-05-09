#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/wait.h>

#define SIZE 100

int main(){
    
    int* data = mmap ( NULL, SIZE*sizeof(int), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
    memset(data, 0, sizeof(int)*SIZE);
    for(int i=0; i<SIZE; i++){
        printf("%d", data[i]);
    }
    printf("\n");

    return 0;
}
