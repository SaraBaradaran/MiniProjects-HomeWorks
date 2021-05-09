#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 100

int main(){

    int* data;
    data = (int*) malloc(SIZE * sizeof(int));
    memset(data, 0, sizeof(int)*SIZE);
    for(int i=0; i<SIZE; i++){
        printf("%d", data[i]);
    }
    printf("\n");

    return 0;
}
