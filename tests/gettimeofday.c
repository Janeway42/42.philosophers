#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
	struct timeval time;
	struct timeval time1;

	gettimeofday(&time, NULL);
	printf("seconds: %ld, micro seconds: %ld\n", time.tv_sec, time.tv_usec);
	sleep(3);
	gettimeofday(&time1, NULL);
	printf("seconds: %ld, micro seconds: %ld\n", time.tv_sec, time.tv_usec);
	printf("elapsed seconds: %ld\n", time1.tv_sec - time.tv_sec);

	return (0);
}