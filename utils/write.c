/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   write.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/06/09 17:13:42 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_message(t_philo *philo, enum msg message)
{
	char	*prompt[] = {"has taken a fork",
					"is now eating",
					"is now sleeping",
					"is now thinking",
					"is dead",
					"released forks"};  // erase when completed 
	unsigned long	elapsed_time;

	pthread_mutex_lock(philo->data->write_lock);
	elapsed_time = get_elapsed_time(philo);
	printf("%lu philosopher %d %s\n", elapsed_time, (philo->id + 1), prompt[message]);
	pthread_mutex_unlock(philo->data->write_lock);
}