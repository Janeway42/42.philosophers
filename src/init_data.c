/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_data.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/06/08 17:09:29 by cpopa         ########   odam.nl         */
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
	return (ERROR);
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

int	create_pthreads(t_data *data)
{
	int	i;

	i = 0;
	data->pthread_id = malloc(sizeof(pthread_t) * data->nr_philo);
	if (!data->pthread_id)
		return (error("failed threads\n"));
	while (i < data->nr_philo)
	{
		if (pthread_create(&data->pthread_id[i], NULL,
					&routine, &data->philos[i]) != 0)
			abort_threads(data, err_threads);
		i++;
	}
	return (OK);
}


// data->forks_lock = the array of locks belonging to each of the forks on the table
// data->philos = struct containing info for each philosopher
int	init_data(t_data *data)
{
	int	i;

	// printf("time: %ld\n", data->start_time.tv_sec);
	if (gettimeofday(&data->start_time, NULL) != 0)
		return (error("failed gettimeofday\n"));
	printf("initial time: %ld\n", data->start_time.tv_sec);

	data->philos = malloc(sizeof(t_philo) * data->nr_philo);
	if (!data->philos)
		return (abort_init_data(data, err_philos));

// malloc and initialize fork mutexes
	data->forks_lock = malloc(sizeof(pthread_mutex_t) * data->nr_philo);
	if (!data->forks_lock)
		return (abort_init_data(data, err_forks));

	i = 0;
	while (i < data->nr_philo)
	{
		pthread_mutex_init(&data->forks_lock[i], NULL);
			// protect mutex_init
		i++;
	}

// write philo data
	i = 0;
	while (i < data->nr_philo)
	{
		data->philos[i].id = i;
		
		data->philos[i].left_fork = data->philos[i].id;
		data->philos[i].right_fork = data->philos[i].id - 1;
		if (data->philos[i].right_fork == -1)
			data->philos[i].right_fork = data->nr_philo - 1;

		data->philos[i].last_eaten = 0;
		data->philos[i].times_eaten = 0;

		data->philos[i].neighbour_lock = malloc(sizeof(pthread_mutex_t));
		// if (!data->philos[i].neighbour_lock)
		// 	return (abort_mutex_neighbour(data, i));

		pthread_mutex_init(data->philos[i].neighbour_lock, NULL);
		data->philos[i].data = data;
//		printf("test: %d\n", data->philos[i].data->t_die);
		i++;
	}

	data->write_lock = malloc(sizeof(pthread_mutex_t));
	// protect mallocc
	pthread_mutex_init(data->write_lock, NULL);
	return (OK);
}

