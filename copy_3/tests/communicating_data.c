#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_philo
{
	int i;
	int j;
	struct s_data *data;
}			t_philo;

typedef struct s_data
{
	int x;
	int y;
	int	t_sleep;
	t_philo *philo;
}			t_data;

int main()
{
	int i = 0;
	t_data *data;

	data->x = 5;
	data->y = 7;
	data->t_sleep = 3;// 3 sec

	data->philo = malloc(sizeof(t_philo) * 3);
	while (i < 3)
	{
		data->philo[i].i = i + 10;
		data->philo[i].j = i + 20;
		data->philo[i].data = data;
		i++;
	}

	printf("data x: %d, data y: %d\n", data->x, data->y);
	usleep(3 * 1000);
	printf("data->philo i: %d, data->philo j: %d\n", data->philo[1].i, data->philo[1].j);
	printf("data->philo[1]->data->x: %d, data->philo[1]->data->y: %d\n", data->philo[1].data->x, data->philo[1].data->y);
}