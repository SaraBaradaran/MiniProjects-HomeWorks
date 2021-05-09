#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#define BUF_SIZE 255

int main()
{
	pid_t childId;
	char path[255];
	char arg[255];
	pid_t pid;
	FILE* fptr = fopen("log.txt", "a+");
	fprintf(fptr,"Date \t Time \t Execution Time(ms)/path\n");
	fclose(fptr);
	while(1)
	{
		printf("\nEnter the file path : ");
		scanf("%s", path);
		getchar();
		
	    	printf("\nEnter the args : ");
	    	
      		scanf("%s", arg);  
			      	
		pid = fork();
		struct timeval start,stop; 
		gettimeofday(&start, NULL);

		if (pid == 0)
			childId = execl(path, arg, NULL);
		int status;
		wait(&status);
		gettimeofday(&stop, NULL);
		printf("file is excuted\n");
		long sec = stop.tv_sec - start.tv_sec;
		float m1 = start.tv_usec;
		float m2 = stop.tv_usec;

		long elapsed = sec*1000+(m2-m1)/1000;
		//printf("%ld\n",elapsed);
		
		struct tm * tmp;
		tmp = localtime(&start.tv_sec);

	
		char buffer[BUF_SIZE];
		sprintf(buffer, "%d-%d-%d \t %d:%02d",tmp->tm_year + 1900,
				tmp->tm_mon, tmp->tm_mday, tmp->tm_hour,
				tmp->tm_min);
		FILE* fptr = fopen("log.txt", "a+");
		fprintf(fptr,"%s \t %ld \t %s\n", buffer, elapsed, path);
		fclose(fptr);
		
	}
	
}
