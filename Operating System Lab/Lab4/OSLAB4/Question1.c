#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
	int inChild = 0;
	pid_t pid;
	
	while(1)
	{
		pid = fork();
		if (pid == 0)
		{
			printf("I am child with pid = %d\n", getpid());
			exit(0);
		}
		sleep(2);
	}
}
