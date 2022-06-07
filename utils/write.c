/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   write.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/06/07 16:59:21 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	state_message(t_philo *philo, enum msg message)
{
	char	*prompt[] = {"has taken a fork",
					"is now eating",
					"is now sleeping",
					"is now thinking",
					"is dead"};
	struct	timeval time;
	int		elapsed_time;

	pthread_mutex_lock(philo->data->write_lock);
	gettimeofday(&time, NULL);
	elapsed_time = time.tv_sec - philo->data->info.start_time.tv_sec;
	printf("%d philosopher %d %s\n", elapsed_time, (philo->id + 1), prompt[message]);
	pthread_mutex_unlock(philo->data->write_lock);
}