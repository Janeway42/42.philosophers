/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/06/26 11:56:08 by janeway       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nr_philo)
	{
		pthread_mutex_destroy(&data->forks_lock[i]);
		pthread_mutex_destroy(&data->philos[i].last_meal);
		i++;
	}
	pthread_mutex_destroy(&data->dead_monitor);
	pthread_mutex_destroy(&data->write_lock);
	
}

void	free_stuff(t_data *data)
{
	if (data->philos)
		free(data->philos);
	if (data->forks_lock)
		free(data->forks_lock);
	if (data->pthread_id)
		free(data->pthread_id);
}

void	clean_up(t_data *data)
{
	destroy_mutexes(data);
	free_stuff(data);
}

