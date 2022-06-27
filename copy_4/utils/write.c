/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   write.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/06/26 12:14:56 by janeway       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_message(t_philo *philo, enum e_msg message)
{
	char	*prompt[] = {"has taken a fork",
					"is eating",
					"is sleeping",
					"is thinking",
					"died"};
//					"released forks",  // erase when completed 
//					"is born ----------------"};  // erase when completed 
	unsigned long	elapsed_time;

	elapsed_time = get_elapsed_time(philo);
	pthread_mutex_lock(&philo->data->write_lock);
	if (message == msg_die)
	{
		printf("\033[0;31m%lu %d %s\033[0m\n", elapsed_time, (philo->id + 1), prompt[message]);
		printf("id: %d, time eaten: %d\n", (philo->id + 1), philo->times_eaten);    /// erase when completed
	}
	else if (still_alive(philo->data) == 0)
		printf("%lu %d %s\n", elapsed_time, (philo->id + 1), prompt[message]);
	pthread_mutex_unlock(&philo->data->write_lock);
}