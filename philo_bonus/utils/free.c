/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/07/25 13:40:36 by cpopa         ########   odam.nl         */
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

void	close_semaphore(sem_t *sem, char *name)
{
	sem_unlink(name);
	sem_close(sem);
}

void	clean_up_process(t_philo *philo)
{
	close_semaphore(philo->s_last_meal, philo->name_last_meal);
	close_semaphore(philo->s_dead, philo->name_dead);
	free(philo->name_last_meal);
	free(philo->name_dead);
	free(philo->name_status);
	free(philo);
}

void	clean_up(t_data *data)
{
	close_semaphore(data->s_forks, "FORKS");
	close_semaphore(data->s_write, "WRITE");
	free_memory(data);
}
