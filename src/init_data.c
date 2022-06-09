/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_data.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/06/09 17:47:45 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_init_data(t_data *data, enum err error)
{
	write(2, "malloc failed\n", 15);
	if (error == err_forks)
		free(data->philos);
	if (error == err_forks || error == err_neighbour)
		free(data->forks_lock);
	// if (error == err_threads)
	// 	free(data->pthread_id);
	return (ERROR);
}

int	error_mutex_init(t_data *data, int count)
{
	int	i;

	i = 0;
	write (2, "mutex init failed\n", 19);
	while (i < count)
	{
		pthread_mutex_destroy(&data->forks_lock[i]);
		i++;
	}
	free(data->philos);
	free(data->forks_lock);
	return (ERROR);
}

int	error_malloc_write(t_data *data)
{
	int	i;

	i = 0;
	write(2, "failed malloc write lock\n", 25);
	while (i < data->nr_philo)
	{
		pthread_mutex_destroy(&data->forks_lock[i]);
		i++;
	}
	free(data->philos);
	free(data->forks_lock);
	free(data->write_lock);
	return (ERROR);
}

int	error_init_write(t_data *data)
{
	int	i;

	i = 0;
	write(2, "failed init write lock\n", 25);
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

int	error_malloc_neighbour_lock(t_data *data, int count)
{
	int	i;

	i = 0;
	write(2, "failed malloc neighbour_lock\n", 30);
	while (i < data->nr_philo)
	{
		pthread_mutex_destroy(&data->forks_lock[i]);
		i++;
	}
	i = 0;
	while (i < count)
	{
		free(data->philos[i].neighbour_lock);
		i++;
	}
	free(data->philos);
	free(data->forks_lock);
	pthread_mutex_destroy(data->write_lock);
	free(data->write_lock);
	return (ERROR);
}

int	error_malloc_dead_monitor(t_data *data)
{
	int	i;

	i = 0;
	write(2, "failed malloc dead_monitor\n", 28);
	while (i < data->nr_philo)
	{
		pthread_mutex_destroy(&data->forks_lock[i]);
		i++;
	}
	i = 0;
	while (i < data->nr_philo)
	{
		free(data->philos[i].neighbour_lock);
		i++;
	}
	free(data->philos);
	free(data->forks_lock);
	pthread_mutex_destroy(data->write_lock);
	free(data->write_lock);
	return (ERROR);

}
int	error_init_dead_monitor(t_data *data)
{
	int	i;

	i = 0;
	write(2, "failed init dead_monitor\n", 28);
	while (i < data->nr_philo)
	{
		pthread_mutex_destroy(&data->forks_lock[i]);
		i++;
	}
	i = 0;
	while (i < data->nr_philo)
	{
		free(data->philos[i].neighbour_lock);
		i++;
	}
	free(data->philos);
	free(data->forks_lock);
	pthread_mutex_destroy(data->write_lock);
	free(data->write_lock);
	free(data->dead_monitor);
	return (ERROR);

}

int	init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nr_philo)
	{
		data->philos[i].id = i;

	data->philos[i].left_fork = data->philos[i].id;
	data->philos[i].right_fork = data->philos[i].id - 1;
	if (data->philos[i].right_fork == -1)
		data->philos[i].right_fork = data->nr_philo - 1;
	// else if (data->philos[i].id % 2 == 0)
	// {
	// 	data->philos[i].left_fork = data->philos[i].id - 1;
	// 	if (data->philos[i].left_fork == -1)
	// 		data->philos[i].left_fork = data->nr_philo - 1;
	// 	data->philos[i].right_fork = data->philos[i].id;
	// }
		
		data->philos[i].last_eaten = 0;
		data->philos[i].times_eaten = 0;
		data->philos[i].neighbour_lock = malloc(sizeof(pthread_mutex_t));
		if (!data->philos[i].neighbour_lock)
			return (error_malloc_neighbour_lock(data, i));
		pthread_mutex_init(data->philos[i].neighbour_lock, NULL);
		data->philos[i].data = data;
		i++;
	}
	return (OK);
}

int	init_data_mutexes(t_data *data)
{
	int	i;

	i = 0;
	data->forks_lock = malloc(sizeof(pthread_mutex_t) * data->nr_philo);
	if (!data->forks_lock)
		return (error_init_data(data, err_forks));
	i = 0;
	while (i < data->nr_philo)
	{
		if (pthread_mutex_init(&data->forks_lock[i], NULL) != 0)
			error_mutex_init(data, i);
		i++;
	}
	data->write_lock = malloc(sizeof(pthread_mutex_t));
	if (!data->write_lock)
		return (error_malloc_write(data));
	if (pthread_mutex_init(data->write_lock, NULL) != 0)
		return (error_init_write(data));
	data->dead_monitor = malloc(sizeof(pthread_mutex_t));
	if (!data->dead_monitor)
		return (error_malloc_dead_monitor(data));
	if (pthread_mutex_init(data->dead_monitor, NULL) != 0)
		return (error_init_dead_monitor(data));
	return (OK);
}

int	init_data(t_data *data)
{
	if (gettimeofday(&data->start_time, NULL) != 0)
		return (error("failed gettimeofday\n"));
//	printf("initial time: %ld\n", ((data->start_time.tv_sec * 1000) + (data->start_time.tv_usec / 1000)));
	data->philos = malloc(sizeof(t_philo) * data->nr_philo);
	if (!data->philos)
		return (error_init_data(data, err_philos));
	if (init_data_mutexes(data) == ERROR)
		return (ERROR);
	if (init_philo(data) == ERROR)
		return (ERROR);
	data->dead_philo = 0;
	return (OK);
}
