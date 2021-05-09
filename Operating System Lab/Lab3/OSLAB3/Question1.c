#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

#define BUF_SIZE 5000

int main(int argc, char** argv){

    if(strcmp(argv[1], "-c") == 0){
        int fd = open(argv[3], O_CREAT, strtol(argv[2], NULL, 8));

    }
    else if(strcmp(argv[1], "-w") == 0){
        char buf[BUF_SIZE];
        fgets(buf, BUF_SIZE, stdin);
        int fd = open(argv[2], O_WRONLY|O_CREAT, 00755);
        write(fd, buf, strlen(buf));

    }
    else if(strcmp(argv[1], "-r") == 0){
        int fd = open(argv[2], O_RDONLY);
        char buf[2];
        buf[1]='\0';
		while(read(fd,buf,1))
			fprintf(stdout, buf, sizeof(buf));

    }
    else if(strcmp(argv[1], "-m") == 0){

        char path[100];
        int low = atoi(argv[5]);
        int high = atoi(argv[6]);
        for(int idx = low; idx <= high; idx++){
            strcpy(path, "");
            sprintf(path, "%s%s_%d.%s", argv[2], argv[3], idx, argv[4]);
            int fd = open(path, O_CREAT);

        }
        
    }        

}
