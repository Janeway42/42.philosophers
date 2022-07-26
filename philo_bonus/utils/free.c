/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/07/26 12:01:32 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	free_memory(t_data *data)
{
	if (data->philos)
		free(data->philos);
	if (data->process_id)
		free(data->process_id);
}

void	free_memory_process(t_philo *philo)
{
	if (philo->name_dead)
		free(philo->name_dead);
	if (philo->name_last_meal)
		free(philo->name_last_meal);
	if (philo->name_status)
		free(philo->name_status);
	if (philo)
		free(philo);
}

void	close_semaphore(sem_t *sem, char *name)
{
	sem_unlink(name);
	sem_close(sem);
}

void	clean_up_process(t_philo *philo)
{
	close_semaphore(philo->s_last_meal, philo->name_last_meal);
	close_semaphore(philo->s_dead, philo->name_dead);
	close_semaphore(philo->s_status, philo->name_status);
	free_memory_process(philo);
}

void	clean_up(t_data *data)
{
	close_semaphore(data->s_forks, "FORKS");
	close_semaphore(data->s_write, "WRITE");
	free_memory(data);
}
