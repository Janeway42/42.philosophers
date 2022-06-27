#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *routine(pthread_mutex_t *lock, pthread_t thread, int a)
{
	int i;
	
	i = 0;
	pthread_mutex_lock(lock);

	printf("routine %d start\n", a);
	sleep (1);
	printf("routine %d end\n", a);

	pthread_mutex_unlock(lock);
	return (NULL);
}

int main()
{
	pthread_t thread_id[2];
	pthread_mutex_t lock;
	int i;

	i = 0;

	if (pthread_mutex_init(&lock, NULL) != 0)
	{
		printf("mutex init failed\n");
		return (1);
	}

	while (i < 2)
	{
		if (pthread_create(&thread_id[i], NULL, routine(&lock, thread_id[i], i), NULL) != 0)
		{
			printf("failed thread create\n");
			return (1);
		}
		i++;
	}

	i = 0;
	while (i < 2)
	{
		pthread_join(thread_id[i], NULL);
		i++;
	}

	pthread_mutex_destroy(&lock);
	return (0);

}