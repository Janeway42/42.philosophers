/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sleep.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/06/13 14:23:58 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	get_time()
{
	struct timeval time;

	if (gettimeofday(&time, NULL) == -1)
		return (ERROR);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	better_sleep(int sleep_time)
{
	unsigned long start;
	unsigned long ms_time;

	start = get_time();
	ms_time = sleep_time;
	while ((get_time() - start) < ms_time)
		usleep(50);
}

unsigned long	get_elapsed_time(t_philo *philo)
{
	struct timeval time;
	unsigned long elapsed_time;

	if (gettimeofday(&time, NULL) != 0)
		return (ERROR);
	elapsed_time = ((time.tv_sec - philo->data->start_time.tv_sec) * 1000
					+ (time.tv_usec - philo->data->start_time.tv_usec) / 1000);
	return (elapsed_time);
}
