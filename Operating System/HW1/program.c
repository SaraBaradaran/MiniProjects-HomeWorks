#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(){

    int rc = fork();
    if(rc < 0){
        printf("fork failed\n");
    }   
    else if(rc == 0){
        printf("\nthis child runs <execl>");
        printf("\nI am the clild(1) with pid = %d\n", (int) getpid());
        char* path = "/bin/ls";
        char* arg1 = "/home";
        execl(path, path, arg1, NULL);

    }
    sleep(1);
    int rc2 = fork();
    if(rc2 < 0){
        printf("fork2 failed\n");
    }   
    else if(rc2 == 0){
        printf("\nthis child runs <execlp>");
        printf("\nI am the clild(2) with pid = %d\n", (int) getpid());
        char* file = "ls";
        char* arg1 = "/home";
        execlp(file, file, arg1, NULL);
    }
    sleep(1);
    int rc3 = fork();
    if(rc3 < 0){
        printf("fork3 failed\n");
    }   
    else if(rc3 == 0){
        printf("\nthis child runs <execv>");
        printf("\nI am the clild(3) with pid = %d\n", (int) getpid());
        char* path = "/bin/ls";
        char* args[] = {path, "/home", NULL};
        execv(path, args);
    }
    sleep(1);
    int rc4 = fork();
    if(rc4 < 0){
        printf("fork4 failed\n");
    }   
    else if(rc4 == 0){
        printf("\nthis child runs <execvp>");
        printf("\nI am the clild(4) with pid = %d\n", (int) getpid());
        char* file = "ls";
        char* args[] = {file, "/home", NULL};
        execvp(file, args);
    }
    sleep(1);
    int rc5 = fork();
    if(rc5 < 0){
        printf("fork5 failed\n");
    }   
    else if(rc5 == 0){
        printf("\nthis child runs <execle>");
        printf("\nI am the child(5) with pid = %d\n", (int) getpid());
        char* path = "/bin/ls";
        char* arg1 = "/home";
        char* const env[] = {NULL};
        execle(path, path,arg1, NULL, env);
        
    }
    sleep(1);               
    int rc6 = fork();
    if(rc6 < 0){
        printf("fork6 failed\n");
    }   
    else if(rc6 == 0){
        printf("\nthis child runs <execve>");
        printf("\nI am the clild(6) with pid = %d\n", (int) getpid());
        char* path = "/bin/ls";
        char* const args[] = {path, "/home", NULL};
        char* const env[] = {NULL};
        execve(path, args, env);
    
    }
    else{
        sleep(1);
        printf("\nI am parent with pid = %d\n", (int) getpid());
    }


}