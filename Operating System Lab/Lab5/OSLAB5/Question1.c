#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_CHILD  5
#define MAXIMUM    100
#define t          1

int main(){


    int inChild = 0;
    int ChildNo;

    int total = 0;
    pid_t pid;

    int fd[MAX_CHILD][2];
    int x;

    
    for(int i=0; i<MAX_CHILD; i++){

        x = pipe(fd[i]);
        pid = fork();
        
        if(pid == 0){

            inChild = 1;
            ChildNo = i;
            break;
        }
        else{   
            close(fd[i][1]);
        }
    }
    srand(getpid());
    if(inChild == 1){
        int random;
        close(fd[ChildNo][0]);
        char buf[256];

        while(1){
            
            random = rand() % 11;
            printf("child %d generate random = %d\n",ChildNo, random);
            sprintf(buf, "%d", random);
            int res = write(fd[ChildNo][1], buf, 255);
            sleep(t);
        }
    }
    else{

        int p;
        char buf[256];
        while(1){

            for(int i=0; i<MAX_CHILD; i++){
                p = read(fd[i][0], buf, 255);
                
                if(p > 0){
                    total+= atoi(buf);
                    printf("total = %d\n", total);
                }
                if(total > MAXIMUM)
                    kill(0, SIGKILL);
            }
        }
    }
}