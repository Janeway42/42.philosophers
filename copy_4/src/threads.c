/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/06/26 12:40:29 by janeway       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_malloc_threads(t_data *data)
{
	write(STDERR_FILENO, "failed malloc threads\n", 16);
	destroy_mutexes(data);
	free_stuff(data);
	return (ERROR);
}

int	error_create_threads(t_data *data, int count)
{
	int	i;

	i = 0;
	write(STDERR_FILENO, "failed threads\n", 16);
	while (i < count)
	{
		pthread_join(data->pthread_id[i], NULL);
		i++;
	}
	destroy_mutexes(data);
	free_stuff(data);
	
	return (ERROR);
}

int	create_pthreads(t_data *data)
{
	int	i;

	i = 0;

	if (gettimeofday(&data->start, NULL) != 0)
		return (ERROR);

	data->pthread_id = malloc(sizeof(pthread_t) * data->nr_philo);
	if (!data->pthread_id)
		return (error_malloc_threads(data));
	while (i < data->nr_philo)
	{
		// data->philos[i].last_eaten = (int)((data->start.tv_sec * 1000) + (data->start.tv_usec / 1000));		
		
		if (pthread_create(&data->pthread_id[i], NULL,
					&routine, &data->philos[i]) != 0)
			return (error_create_threads(data, i));
		i++;
	}
	if (pthread_create(&data->surveilance, NULL,
			&dead_philo, data)!= 0)
		{
			write(STDERR_FILENO, "surveilance thread fail\n", 27);
			pthread_mutex_lock(&data->dead_monitor);
			data->dead_philo = 1;
			pthread_mutex_unlock(&data->dead_monitor);
			return (ERROR);
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
		pthread_join(data->surveilance, NULL);
	return (OK);
}
