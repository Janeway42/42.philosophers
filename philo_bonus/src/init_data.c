/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_data.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/07/04 16:51:36 by cpopa         ########   odam.nl         */
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

static int	init_philo(t_data *data)
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

		data->philos[i].thread = malloc(sizeof(pthread_t));
		if (!data->philos[i].thread)
			error("malloc fail: thread\n");
		data->philos[i].s_last_meal = malloc(sizeof(sem_t));
		if (!data->philos[i].s_last_meal)
			error("malloc fail: s_last_meal\n");
			
		data->philos[i].data = data;
		i++;
	}
	return (OK);
}

static int	init_semaphores(t_data *data)
{
	sem_unlink(FORKS);
	data->s_forks = malloc(sizeof(sem_t) * data->nr_philo);
	if (!data->s_forks)
		error("malloc fail: s_forks\n");
	data->s_forks = sem_open(FORKS, O_CREAT, 0664, data->nr_philo);
	if (data->s_forks == SEM_FAILED)
		error("sem_open fail: s_forks\n");

	sem_unlink(WRITE);
	data->s_write = malloc(sizeof(sem_t));
	if (!data->s_write)
		error("malloc fail: s_write\n");
	data->s_write = sem_open(WRITE, O_CREAT, 0664, 1);
	if (data->s_write == SEM_FAILED)
		error("sem_open fail: s_write\n");
	return (OK);
}

int	init_data(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * data->nr_philo);
	if (!data->philos)
		return (error("malloc fail: philos\n"));

	data->process_id = malloc(sizeof(pid_t) * data->nr_philo);
	if(!data->process_id)
		error("malloc failed: process_id\n");
	
	if (init_semaphores(data) == ERROR)
		return (ERROR);
	if (init_philo(data) == ERROR)
		return (ERROR);
	if (gettimeofday(&data->start_time, NULL) != 0)
		return (ERROR);
	printf("test end init data\n");  //--------------------------------
	return (OK);
}
