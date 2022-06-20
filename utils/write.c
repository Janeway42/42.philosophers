/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   write.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/06/20 17:02:02 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_message(t_philo *philo, enum msg message)
{
	char	*prompt[] = {"has taken a fork",
					"is eating",
					"is sleeping",
					"is thinking",
					"died"};
//					"released forks",  // erase when completed 
//					"is born ----------------"};  // erase when completed 
	unsigned long	elapsed_time;

	pthread_mutex_lock(&philo->data->write_lock);
	elapsed_time = get_elapsed_time(philo);
	if (message == msg_die)
		printf("\033[0;31m%lu %d %s\033[0m\n", elapsed_time, (philo->id + 1), prompt[message]);
	else
		printf("%lu %d %s\n", elapsed_time, (philo->id + 1), prompt[message]);
	pthread_mutex_unlock(&philo->data->write_lock);
}