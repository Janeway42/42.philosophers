/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/07/04 16:30:24 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	close_semaphores(t_data *data)
{
	sem_close(data->s_forks);
	sem_close(data->s_write);
	sem_unlink(FORKS);
	sem_unlink(WRITE);
}

void	free_stuff(t_data *data)
{
	int	i;

	i = 0;
	while ( i < data->nr_philo)
	{
		if (data->philos[i].thread)
			free(data->philos[i].thread);
		i++;
	}
	if (data->philos)
		free(data->philos);
	if (data->s_forks)
		free(data->s_forks);
	if (data->process_id)
		free(data->process_id);
}

void	clean_up(t_data *data)
{
	close_semaphores(data);
	free_stuff(data);
}
