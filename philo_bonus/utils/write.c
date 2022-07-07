/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   write.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/07/07 11:18:25 by janeway       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_message(t_philo *philo, enum e_msg message)
{
	const char		*prompt[] = {"has taken a fork",
		"is eating",
		"is sleeping",
		"is thinking",
		"died"};
	unsigned long	elapsed_time;

	elapsed_time = get_elapsed_time(philo);
	sem_wait(philo->data->s_write);
	if (message == msg_die)
		printf("\033[0;31m%lu %d %s\033[0m\n",
			elapsed_time, (philo->id + 1), prompt[message]);
	else
	{
		printf("%lu %d %s\n", elapsed_time, (philo->id + 1), prompt[message]);
		sem_post(philo->data->s_write);
	}
}
