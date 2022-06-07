/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/06/07 17:00:02 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->info.nr_philo)
	{
		pthread_mutex_destroy(&data->forks_lock[i]);
		pthread_mutex_destroy(data->philos[i].neighbour_lock);
		i++;
	}
	pthread_mutex_destroy(data->write_lock);
	free(data->philos);
	free(data->pthread_id);
	free(data->forks_lock);
}