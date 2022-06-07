/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_data.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/06/07 17:26:17 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		abort_init_data(t_data *data, enum err error)
{
	if (error == err_forks)
		free(data->philos);
	if (error == err_forks || error == err_neighbour)
		free(data->forks_lock);
	if (error == err_threads)
		free(data->pthread_id);
	printf("malloc failed\n");
	return (EXIT_ERROR);
}

int	abort_threads(t_data *data, int i)
{
	while (i > -1)
	{
		pthread_join(data->pthread_id[i], NULL);
		i--;
	}
	return (abort_init_data(data, err_threads));
}

void	create_pthreads(t_data *data)
{
	int	i;
	int	thread;

	i = 0;
	data->pthread_id = malloc(sizeof(pthread_t) * data->info.nr_philo);
	if (!data->pthread_id)
		abort_init_data(data, 2);
	while (i < data->info.nr_philo)
	{
		printf("i: %d\n", i);
		thread = pthread_create(&data->pthread_id[i], NULL,
					&routine, &data->philos[i]);                 //////////
		if (thread != 0)
			abort_threads(data, err_threads);
		i++;
	}
}


// data->forks_lock = the array of locks belonging to each of the forks on the table
// data->philos = struct containing info for each philosopher
void	init_data(t_data *data)
{
	int	i;

	data->a = 5;

	data->philos = malloc(sizeof(t_philo) * data->info.nr_philo);
	if (!data->philos)
		abort_init_data(data, err_philos);

	data->forks_lock = malloc(sizeof(pthread_mutex_t) * data->info.nr_philo);
	if (!data->forks_lock)
		abort_init_data(data, err_forks);

// initialize fork mutexes
	i = 0;
	while (i < data->info.nr_philo)
	{
		pthread_mutex_init(&data->forks_lock[i], NULL);
		i++;
	}

// write data data 
	i = 0;
	while (i < data->info.nr_philo)
	{
		data->philos[i].id = i;
		
		data->philos[i].left_fork = data->philos[i].id;
		data->philos[i].right_fork = data->philos[i].id - 1;
		if (data->philos[i].right_fork == -1)
			data->philos[i].right_fork = data->info.nr_philo - 1;

		data->philos[i].last_eaten = get_time();
		data->philos[i].times_eaten = 0;

		data->philos[i].neighbour_lock = malloc(sizeof(pthread_mutex_t));
		// protect malloc fail 
		pthread_mutex_init(data->philos[i].neighbour_lock, NULL);
		i++;

		printf("test a: %d\n", data->philos[i].data->a);
		printf("test: %d\n", data->philos[i].data->info.nr_philo);
	}
	gettimeofday(&data->info.start_time, NULL);

	data->write_lock = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(data->write_lock, NULL);
}