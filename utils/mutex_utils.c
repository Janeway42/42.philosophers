/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mutex_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/06/20 14:44:59 by cpopa         ########   odam.nl         */
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