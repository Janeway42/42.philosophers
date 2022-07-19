/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize_data.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/07/19 13:36:01 by janeway       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	choose_forks(t_data *data, int i)
{
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
}

static int	initialize_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nr_philo)
	{
		data->philos[i].id = i;
		choose_forks(data, i);
		data->philos[i].last_eaten = 0;
		data->philos[i].times_eaten = 0;
		data->philos[i].status = ACTIVE;
		data->philos[i].data = data;
		i++;
	}
	return (OK);
}

static int	initialize_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nr_philo)
	{
		if (pthread_mutex_init(&data->forks_lock[i], NULL) != 0)
			return (error_mutex(data, "init fork_locks fail\n"));
		if (pthread_mutex_init(&data->philos[i].meal_lock, NULL) != 0)
			return (error_mutex(data, "init last_meal fail\n"));
		i++;
	}
	if (pthread_mutex_init(&data->dead_lock, NULL) != 0)
		return (error_mutex(data, "init dead_monitor fail\n"));
	if (pthread_mutex_init(&data->write_lock, NULL) != 0)
		return (error_mutex(data, "init write_lock fail\n"));
	return (OK);
}

static int	allocate_memory(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * data->nr_philo);
	data->forks_lock = malloc(sizeof(pthread_mutex_t) * data->nr_philo);
	data->pthread_id = malloc(sizeof(pthread_t) * data->nr_philo);
	if (!data->philos || !data->forks_lock || !data->pthread_id)
		return (error_memory(data, "malloc fail\n"));
	return (OK);
}

int	initialize_data(t_data *data)
{
	if (allocate_memory(data) == ERROR)
		return (ERROR);
	if (initialize_mutexes(data) == ERROR)
		return (ERROR);
	if (initialize_philo(data) == ERROR)
		return (ERROR);
	data->dead_philo = 0;
	if (gettimeofday(&data->start_time, NULL) != 0)
		return (ERROR);
	return (OK);
}
