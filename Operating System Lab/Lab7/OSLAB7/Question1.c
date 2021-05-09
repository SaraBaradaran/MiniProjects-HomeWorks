
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

#define MAX_TRY 3
int counter = 0;
void Myhandler(int signo){

    switch(signo){
        case SIGINT:
            counter++;
            if(counter == MAX_TRY){
                _exit(0);
            }
            break;
    }
}


int main(){

    struct sigaction act;
    act.sa_handler = Myhandler;
    act.sa_flags = 0;
    sigaction(SIGINT, (const struct  sigaction*)&act, NULL);

    while(1){
        
        printf("....\n");
        sleep(1);
    }

}