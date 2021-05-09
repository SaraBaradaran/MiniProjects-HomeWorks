#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define MAX_CHILD  5
#define t          1

int main(){


    int inChild = 0;
    int ChildNo;

    int x;
    
    pid_t child[MAX_CHILD];

    char path[100] = "1.pipe";
    mkfifo(path, 0777);

    for(int i=0; i<MAX_CHILD; i++){

        child[i] = fork();
        
        if(child[i] == 0){

            inChild = 1;
            ChildNo = i;
            break;
        }
    }
    if(inChild == 1){
        
        printf("‫‪child‬‬ ‫‪%d ‫‪starts‬‬\n", ChildNo);
        int p;
        char buf[256];
        x = open(path, O_RDWR);

        while(1){
            
            p = read(x, buf, 255);
            if(p > 0){

                printf("‫‪child‬‬ %d ‫‪pipevalue:‬‬ ‪%s\n", ChildNo, buf);
                if(ChildNo == atoi(buf)){
                    if(ChildNo > 0){
                        
                        sprintf(buf, "%d", ChildNo - 1);
                        write(x, buf, 255);
                    }
                    else{
                        
                        write(x, buf, 255);
                        printf("child %d reach the point\n", ChildNo);
                        kill(getpid(), SIGKILL);
                    }
                }
                else if(atoi(buf) == 0){

                    sprintf(buf, "%d", 0);
                    write(x, buf, 255);
                    printf("child %d reach the point\n", ChildNo);
                    kill(getpid(), SIGKILL);
                }
                else{
                    write(x, buf, 255);
                }
            }
            sleep(t);
        }
    }
    else{

        int p;
        int status = 0;                   
        char buf[256];
        sprintf(buf, "%d", MAX_CHILD - 1);
        x = open(path, O_WRONLY);
        write(x, buf, strlen(buf));
        int aliveChild = MAX_CHILD;

        while(1){

            for (int i = 0; i < MAX_CHILD; i++){

				pid_t dead = waitpid(child[i], &status ,WNOHANG);

				if (dead > 0){
                    aliveChild -= 1;
				}
                if(aliveChild == 0)
                    break;
			}
            if(aliveChild == 0)
                break;
        }
        printf("‫‪The‬‬ ‫‪program‬‬ ‫‪finished‬‬ ‫‪successfully‬‬\n");
    }
}