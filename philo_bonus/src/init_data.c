/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_data.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/07/07 18:00:25 by janeway       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	// data->s_forks = malloc(sizeof(sem_t) * data->nr_philo);  // Why ? slack
	// if (!data->s_forks)
	// 	return (error_free("malloc fail: s_forks\n", data));
	// data->s_write = malloc(sizeof(sem_t));
	// if (!data->s_write)
	// 	return (error_free("malloc fail: s_write\n", data));
	data->process_id = malloc(sizeof(pid_t) * data->nr_philo);
	if (!data->process_id)
		return (error_free("malloc fail: process_id\n", data));
	if (init_semaphores(data) == ERROR)
		return (ERROR);
	if (gettimeofday(&data->start_time, NULL) != 0)
		return (ERROR);
	// printf("start time1: %ld\n",((data->start_time.tv_sec * 1000)
	// 		+ (data->start_time.tv_usec / 1000)));
	return (OK);
}
