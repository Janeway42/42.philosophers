/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   write.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/06/08 20:02:03 by janeway       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_message(t_philo *philo, enum msg message)
{
	char	*prompt[] = {"has taken a fork",
					"is now eating",
					"is now sleeping",
					"is now thinking",
					"is dead"};
//	struct	timeval time;
	int		elapsed_time;

	pthread_mutex_lock(philo->data->write_lock);
	// gettimeofday(&time, NULL);
	// elapsed_time = time.tv_sec - philo->data->start_time.tv_sec;
	elapsed_time = get_elapsed_time(philo);
	// printf("write time: %d\n", elapsed_time);
	printf("%d philosopher %d %s\n", elapsed_time, (philo->id + 1), prompt[message]);
	pthread_mutex_unlock(philo->data->write_lock);
}