
#include <signal.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#define PERIOD 1
static sigset_t block;
struct sigaction act1;
struct timeval interval;
struct itimerval period;

char message[5];
void timer_handler(int signo){

	write( 1, message, sizeof( message ) );
}

int main(){

	bzero(message, 5);
	sprintf(message, "%s","Hi\n");
	
	sigemptyset(&block);
	sigaddset(&block, SIGVTALRM);
	act1.sa_flags = 0;
	act1.sa_mask = block;
	act1.sa_handler = timer_handler;
	assert(!sigaction(SIGVTALRM, (struct sigaction * ) & act1, NULL));
	interval.tv_sec = PERIOD;
	interval.tv_usec = 0;
	period.it_interval = interval;
	period.it_value = interval;
	setitimer(ITIMER_VIRTUAL, &period, NULL);

    while(1);
	
}
