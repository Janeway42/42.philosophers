/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_data.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/07/08 15:23:56 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_semaphores(t_data *data)
{
	sem_unlink("FORKS");
	sem_unlink("WRITE");
	data->s_forks = sem_open(FORKS, O_CREAT | O_EXCL, 0777, data->nr_philo);
	if (data->s_forks == SEM_FAILED)
		return (error_semaphore("sem failed: s_forks\n", data));
	data->s_write = sem_open(WRITE, O_CREAT | O_EXCL, 0777, 1);
	if (data->s_write == SEM_FAILED)
		return (error_semaphore("sem failed: s_write\n", data));
	return (OK);
}

int	init_data(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * data->nr_philo);
	if (!data->philos)
		return (error("malloc fail\n"));
	data->process_id = malloc(sizeof(pid_t) * data->nr_philo);
	if (!data->process_id)
		return (error_free("malloc fail: process_id\n", data));
	if (init_semaphores(data) == ERROR)
		return (ERROR);
	if (gettimeofday(&data->start_time, NULL) != 0)
		return (ERROR);
	return (OK);
}
