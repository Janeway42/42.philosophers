#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

//  int pthread_create(pthread_t *restrict thread, 			//pointer of the Thread ID - it will update the value in it
//  					const pthread_attr_t *restrict attr, 	//attributes to set the properties of thread
// 					void *(*start_routine)(void *), 		//function pointer to the function that the thread will run in parallel on start. This function should accept a void * and return void * too
// 					void *restrict arg)						//Arguments to be passed to function

void *routine(void *var)
{
	sleep (1);
	printf("Thread print\n");
	return (0);
}

int main ()
{
	pthread_t id;

	printf("before thread is created\n");
	pthread_create(&id, NULL, routine, NULL);
//  int pthread_create	(pthread_t *restrict thread, 			//pointer of the Thread ID - it will update the value in it
//  					const pthread_attr_t *restrict attr, 	//attributes to set the properties of thread
// 						void *(*start_routine)(void *), 		//function pointer to the function that the thread will run in parallel on start. This function should accept a void * and return void * too
// 						void *restrict arg)						//Arguments to be passed to function

	pthread_detach(id);
//	pthread_join(id, NULL);
//	pthread_detach(id);


// pthread_join is basically the equivalent of wait. Blocks the calling thread until the thread with id terminates
//  int pthread_join	(pthread_t thread,						//thread id
//						void **retval);							//if not NULL, then pthread_join copies the exit status of the thread supplied to pthread_exit
	sleep(3);
	printf("After thread creation\n");

	return (0);
}