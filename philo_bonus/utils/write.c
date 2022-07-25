/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   write.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/07/25 16:42:10 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	write_message(t_philo *philo, enum e_msg message)
{
	const char		*prompt[] = {"has taken a fork",
		"is eating",
		"is sleeping",
		"is thinking",
		"died"};

	sem_wait(philo->data->s_write);
	if (message == msg_die)
		printf("\033[0;31m%lu %d %s\033[0m\n",
			get_elapsed_time(philo), (philo->id + 1), prompt[message]);
	else
	{
		printf("%lu %d %s\n", get_elapsed_time(philo),
			(philo->id + 1), prompt[message]);
		sem_post(philo->data->s_write);
	}
}
