#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHILD 3
#define MAXIMUM   50

char path[30];
int namedPipe;
char buf[255];
int total = 0;

void Myhandler(int signo){
    int num;
    switch(signo){
        case SIGUSR1:
            namedPipe = open(path, O_RDONLY|O_NONBLOCK);
            bzero(buf, 255);
            read(namedPipe, buf, 255);
            num = atoi(buf);
            //It may two child write inside the namedPipe at the same time,
            //We separate the numbers because we know childs generate random numbers less than 10
            if(num > 10){
                for(int i=0; i<strlen(buf); i++){
                    printf("parent reads %c\n", buf[i]);
                    total += buf[i] - '0';
                    printf("total = %d\n", total);
                    if(total > MAXIMUM)
                        break;
                }
            }
            else{

                printf("parent reads %d\n", num);
                total += num;
                printf("total = %d\n", total);
            }
            if(total > MAXIMUM){
                kill(0, SIGKILL);
            }
            break;
    }

}


int main(){

    sprintf(path, "%s", "1.pipe");
    mkfifo(path, 0777);

    
    pid_t pid;
    int inChild = 0;

    struct sigaction act;
    act.sa_flags = 0;
    act.sa_handler = Myhandler;
    sigaction(SIGUSR1, (const struct sigaction*)&act, NULL);

    for(int i=0; i<MAX_CHILD; i++){

        pid = fork();
        if(pid == 0){
            inChild = 1;
            break;
        }
    }

    if(inChild == 1){
        srand(getpid());
        namedPipe = open(path, O_WRONLY);
        while(1){
            
            int t = rand() % 10;
            bzero(buf, 255);
            sprintf(buf, "%d", t);
            sleep(t);
            printf("\nchild generates %s\n", buf);
            write(namedPipe, buf, strlen(buf));
            kill(getppid(), SIGUSR1);
        }

    }
        
    else{

        while(1){
            
        }
        
    }

}