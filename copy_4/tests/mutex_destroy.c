#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int main()
{
	pthread_mutex_t mutex;
	pthread_mutex_t mutex1;

//	mutex = malloc(sizeof(pthread_mutex_t));
//	mutex1 = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(&mutex, NULL);
	printf("control\n");
	pthread_mutex_destroy(&mutex);
	pthread_mutex_destroy(&mutex1);
//	free(mutex);
//	free(mutex1);
	return (0);
}