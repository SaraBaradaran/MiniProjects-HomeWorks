#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

#define MAXCHILD 5

int main()
{
	int inChild = 0;
	pid_t pid;

	srand(time(NULL));
	
	pid_t* child = (pid_t*)malloc(sizeof(pid_t) * MAXCHILD);
	
	for (int i = 0; i < MAXCHILD; i++)
	{
		child[i] = fork();
		if (child[i] == 0)
		{
			inChild = 1;
			break;
		}
	}

	int s;
	while(1)
	{
		if (inChild == 1)
		{
			srand(getpid());
			s = (rand() % 1000) + 1;
			sleep(s);
			printf("message from child %d waited %d seconds\n",getpid(),s);
			inChild = -1;
			exit(0);
		}
		
		if (inChild == 0)
		{
			sleep(5);
			for (int i = 0; i < MAXCHILD; i++)
			{
				int status;
				pid_t deadChild = waitpid(child[i], &status ,WNOHANG);
				if (deadChild > 0)
				{
					child[i] = fork();
					if (child[i] == 0)
						inChild = 1;
					break;
				}
			}
		}
		if (inChild == -1)
			break;
	}

	return 0;

}
