/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/07/07 18:04:03 by janeway       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_stuff(t_data *data)
{
	if (data->philos)
		free(data->philos);
	// if (data->s_forks)
	//	free(data->s_forks);
	// if (data->s_write)
	//	free(data->s_write);
	if (data->process_id)
		free(data->process_id);
}

void close_semaphore(sem_t *sem, char *name)
{
	sem_unlink(name);
	sem_close(sem);
}

void	clean_up(t_data *data)
{
	close_semaphore(data->s_forks, "FORKS");
	close_semaphore(data->s_write, "WRITE");
	free_stuff(data);
}
