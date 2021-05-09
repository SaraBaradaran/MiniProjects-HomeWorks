#include <stdlib.h>
#include <ucontext.h>
#include <signal.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/wait.h>
#include <semaphore.h>

#include "green.h"
#include "queue.h"


#define FALSE 0
#define TRUE 1
#define PERIOD 1000 //(ms)

#define STACK_SIZE 4*1024

unsigned int AutoNumber(){
	static unsigned int ID = 0;
	return ++ID;
}
static ucontext_t main_cntx = {0};

static green_t main_green = {&main_cntx, NULL, NULL, NULL, NULL, NULL, FALSE};

static green_t * running = &main_green;

static green_t * head;
static green_t * tail;

queue_t * ready_queue;

static sigset_t block;
struct sigaction act1;

// this function is called once program loads into memory regurdless of what function is called!
static void init( ) __attribute__((constructor));
void init(){

	getcontext(&main_cntx);
	main_green.gtid =  AutoNumber();
	head = &main_green;
	tail = &main_green;
	tail->next = NULL;
	ready_queue = createQueue();
	sigemptyset(&block);
	sigaddset(&block, SIGALRM);
	act1.sa_flags = 0;
	act1.sa_handler = timer_handler;
	assert(!sigaction(SIGALRM, (struct sigaction * ) & act1, NULL));
	ualarm(PERIOD, 0);	
}

void timer_handler(int signo){

	if(signo == SIGALRM){
		green_yield();
	}
}
// this functions is mapped to every Context
void green_thread(){

	//sigprocmask(SIG_BLOCK, &block, NULL);
	green_t * this = running;
	// call target function and save its result
	void * result = (*this->fun)(this->arg);
	// place waiting (joining) thread in ready queue
	if(this->join)
		enQueue(ready_queue, this->join);
	// save result of execution and zombie status
	this->retval = result;
	this->zombie = TRUE;
	// find the next thread to run and write its address to next variable
	green_t * next = deQueue(ready_queue);
	running = next;
	setcontext(next->context);
	//sigprocmask(SIG_UNBLOCK, &block, NULL);
}

// will create a new green thread
int green_create(green_t *new ,void *(*fun)(void *),void *arg) {

	//sigprocmask(SIG_BLOCK, &block, NULL);
	ucontext_t * cntx = (ucontext_t *) malloc(sizeof(ucontext_t));
	// intialize cntx
	getcontext(cntx);
	void * stack = malloc(STACK_SIZE);
	// assign allocated stack to cntx
	cntx->uc_stack.ss_sp = stack;
	cntx->uc_stack.ss_size = STACK_SIZE;
	// assign green_thread function to cntx
	makecontext(cntx, green_thread, 0);
	
	new->context = cntx ;
	new->fun = fun ;
	new->arg = arg ;
	new->next = NULL;
	new->join = NULL;
	new->retval = NULL;
	new->zombie = FALSE;
	new->gtid =  AutoNumber();
	// add this new thread to end of linked list
	new->next = NULL;
	tail->next = new;
	tail = new;
	// add new thread to the ready queue
	enQueue(ready_queue, new);
	//sigprocmask(SIG_UNBLOCK, &block, NULL);
	return 0 ;
}

// will give other green thread opportunity of having CPU!
int green_yield(){
	
	//sigprocmask(SIG_BLOCK, &block, NULL);
	green_t * susp = running ;
	// add susp to ready queue
	enQueue(ready_queue, susp);
	// select the next thread for execution
	green_t * next = deQueue(ready_queue);
	running = next ;
	ualarm(PERIOD, 0);
	// save current state into susp->context and switch to next->context
	swapcontext(susp->context, next->context);
	//sigprocmask(SIG_UNBLOCK, &block, NULL);
	return 0 ;
}

// waits for specefied thread till it finishes and get result value
int green_join(green_t * thread ,void ** res) {
	// check if target thread has finished
	//sigprocmask(SIG_BLOCK, &block, NULL);
	if(!thread->zombie){
		
		green_t * susp = running ;
		// add as joining thread
		thread->join = susp;
		// select the next thread for execution
		green_t * next = deQueue(ready_queue);
		running = next ;
		// save current state into susp->context and switch to next->context
		swapcontext(susp->context, next->context);
	}
	// collect result
	*res = thread->retval;
	// free context
	free(thread->context);
	return 0 ;
}

void green_print(){

	green_t * temp = head;
	for(;temp; temp = temp->next){
		printf("%d --> ", temp->gtid);
	}
	printf(" NULL‌ \n");
}