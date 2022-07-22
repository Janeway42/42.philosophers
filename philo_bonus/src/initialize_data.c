/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize_data.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/07/22 23:26:24 by janeway       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

sem_t	*open_semaphore(sem_t **address, char *name, int size)
{
	sem_unlink(name);
	*address = sem_open(name, O_CREAT | O_EXCL, 0777, size);
	if (*address == SEM_FAILED)
		error_exit("sem_open fail\n");
	return (*address);
}

static int	initialize_semaphores(t_data *data)
{
	data->s_forks = open_semaphore(&data->s_forks, "FORKS", data->nr_philo);
	if (data->s_forks == SEM_FAILED)
		return (error_semaphore("sem failed: s_forks\n", data));
	// dprintf(2, "FORKS = %p\n", data->s_forks);
	data->s_write = open_semaphore(&data->s_write, "WRITE", 1);
	if (data->s_write == SEM_FAILED)
		return (error_semaphore("sem failed: s_write\n", data));
	return (OK);
}

static int	allocate_memory(t_data *data)
{
	// int i = 0;

	data->philos = malloc(sizeof(t_philo) * data->nr_philo);
	data->process_id = malloc(sizeof(pid_t) * data->nr_philo);
	if (!data->philos || !data->process_id)
		return (error_memory(data, "malloc fail: process_id\n"));
	// while (i < data-> nr_philo)
	// {
	// 	dprintf(2, "processes = %p\n", &data->process_id[i]);
	// 	i++;

	// }
	return (OK);
}

int	initialize_data(t_data *data)
{
	if (allocate_memory(data) == ERROR)
		return (ERROR);
	if (initialize_semaphores(data) == ERROR)
		return (ERROR);
	if (gettimeofday(&data->start_time, NULL) != 0)
		return (ERROR);
	return (OK);
}
