#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

int	make_time(struct timeval start)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (((tv.tv_sec - start.tv_sec) * 1000) + ((tv.tv_usec - start.tv_usec) / 1000));
}

int main()
{
	struct timeval start;
	struct timeval time;

	gettimeofday(&start, NULL);
//	sleep(3);
	usleep(300 * 1000);
	printf("time: %d\n", make_time(start));
	return (0);




	// gettimeofday(&time, NULL);
	// printf("seconds: %ld, micro seconds: %ld\n", time.tv_sec, time.tv_usec);
	// sleep(2);
	// gettimeofday(&time1, NULL);
	// printf("seconds: %ld, micro seconds: %ld\n", time.tv_sec, time.tv_usec);
	// printf("elapsed seconds: %ld\n", time1.tv_sec - time.tv_sec);
	// printf("\n");
	// printf("make time: %d\n", make_time());
	// return (0);
}


