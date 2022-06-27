/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_data.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/06/25 17:19:13 by janeway       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nr_philo)
	{
		data->philos[i].id = i;

		// data->philos[i].left_fork = data->philos[i].id;
		// data->philos[i].right_fork = data->philos[i].id - 1;
		// if (data->philos[i].right_fork == -1)
		// 	data->philos[i].right_fork = data->nr_philo - 1;
			
	if (data->philos[i].id % 2 != 0)
	{
		data->philos[i].left_fork = data->philos[i].id;
		data->philos[i].right_fork = data->philos[i].id - 1;
		if (data->philos[i].right_fork == -1)
			data->philos[i].right_fork = data->nr_philo - 1;
	}
	
	else if (data->philos[i].id % 2 == 0)
	{
		data->philos[i].left_fork = data->philos[i].id - 1;
		if (data->philos[i].left_fork == -1)
			data->philos[i].left_fork = data->nr_philo - 1;
		data->philos[i].right_fork = data->philos[i].id;
	}
		if (gettimeofday(&data->philos[i].start_time, NULL) != 0)
		return (ERROR);
	
	//	data->philos[i].last_eaten = (data->start_time.tv_sec * 1000) + (data->start_time.tv_usec / 1000);
		data->philos[i].last_eaten = get_elapsed_time(&data->philos[i]);


		data->philos[i].last_eaten = 0;
		data->philos[i].times_eaten = 0;
		if (pthread_mutex_init(&data->dead_monitor, NULL) != 0)
			return (error_init_dead_monitor(data));
		if (pthread_mutex_init(&data->philos[i].last_meal, NULL) != 0)
			return (error_init_dead_monitor(data));
		data->philos[i].data = data;
		i++;
	}
	return (OK);
}

int	init_data_mutexes(t_data *data)
{
	int	i;

	data->forks_lock = malloc(sizeof(pthread_mutex_t) * data->nr_philo);
	if (!data->forks_lock)
		return (error_init_data(data, err_forks));
	i = 0;
	while (i < data->nr_philo)
	{
		if (pthread_mutex_init(&data->forks_lock[i], NULL) != 0)
			error_mutex_init(data);
		i++;
	}
	if (pthread_mutex_init(&data->write_lock, NULL) != 0)
		return (error_init_write(data));
	return (OK);
}

int	init_data(t_data *data)
{
	// printf("initial time: %ld\n", ((data->start_time.tv_sec * 1000) + (data->start_time.tv_usec / 1000)));

	data->philos = malloc(sizeof(t_philo) * data->nr_philo);
	if (!data->philos)
		return (error("malloc fail\n"));
	if (init_data_mutexes(data) == ERROR)
		return (ERROR);
	if (init_philo(data) == ERROR)
		return (ERROR);
	data->dead_philo = 0;
	return (OK);
}
