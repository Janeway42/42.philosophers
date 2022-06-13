/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/06/13 17:52:46 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void monitor(void *arg)
{
	t_philo *philo;
	int time;
	int i;

	i = 0;
	philo = (t_philo *)arg;

	while (1)
	{
		time = get_time();
		pthread_mutex_lock(philo->data->dead_monitor);
		if ((time - philo->last_eaten) > philo->data->t_die)
				philo->data->dead_philo = 1;
		pthread_mutex_unlock(philo->data->dead_monitor);
		usleep(50);
	}
	return (NULL);
}