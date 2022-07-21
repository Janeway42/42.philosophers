/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize_data.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/07/21 16:55:22 by cpopa         ########   odam.nl         */
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
	data->philos = malloc(sizeof(t_philo) * data->nr_philo);
	data->process_id = malloc(sizeof(pid_t) * data->nr_philo);
	if (!data->philos || !data->process_id)
		return (error_memory(data, "malloc fail: process_id\n"));
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
