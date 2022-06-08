#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

int	make_time(void)
{
	struct timeval	tv;
	struct timezone	tz;

	gettimeofday(&tv, &tz);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int main()
{
	struct timeval time;
	struct timeval time1;

	gettimeofday(&time, NULL);
	printf("seconds: %ld, micro seconds: %d\n", time.tv_sec, time.tv_usec);
	sleep(3);
	gettimeofday(&time1, NULL);
	printf("seconds: %ld, micro seconds: %d\n", time.tv_sec, time.tv_usec);
	printf("elapsed seconds: %ld\n", time1.tv_sec - time.tv_sec);
	printf("\n");
	printf("make time: %d\n", make_time());
	return (0);
}


