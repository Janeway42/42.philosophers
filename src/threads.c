/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/06/09 14:24:20 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_malloc_threads(t_data *data)
{
	int	i;

	i = 0;
	write(2, "failed malloc threads\n", 16);
	while (i < data->nr_philo)
	{
		free(data->philos[i].neighbour_lock);
		i++;
	}
	i = 0;
	while (i < data->nr_philo)
	{
		pthread_mutex_destroy(&data->forks_lock[i]);
		i++;
	}
	free(data->philos);
	free(data->forks_lock);
	pthread_mutex_destroy(data->write_lock);
	free(data->write_lock);
	return (ERROR);
}

int	error_create_threads(t_data *data, int count)
{
	int	i;

	i = 0;
	write(2, "failed threads\n", 16);
	while (i < count)
	{
		pthread_join(data->pthread_id[i], NULL);
		i++;
	}
	i = 0;
	while (i < data->nr_philo)
	{
		free(data->philos[i].neighbour_lock);
		i++;
	}
	i = 0;
	while (i < data->nr_philo)
	{
		pthread_mutex_destroy(&data->forks_lock[i]);
		i++;
	}
	free(data->philos);
	free(data->forks_lock);
	free(data->pthread_id);
	pthread_mutex_destroy(data->write_lock);
	free(data->write_lock);
	return (ERROR);
}

int	create_pthreads(t_data *data)
{
	int	i;

	i = 0;
	data->pthread_id = malloc(sizeof(pthread_t) * data->nr_philo);
	if (!data->pthread_id)
		return (error_malloc_threads(data));
	while (i < data->nr_philo)
	{
		if (pthread_create(&data->pthread_id[i], NULL,
					&routine, &data->philos[i]) != 0)
			error_create_threads(data, i);
		i++;
	}
	return (OK);
}

int	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nr_philo)
	{
		pthread_join(data->pthread_id[i], NULL);
		i++;
	}
	return (OK);
}
