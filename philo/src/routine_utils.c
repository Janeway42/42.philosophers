/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/07/13 13:25:38 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meal);
	philo->last_eaten = (int)get_elapsed_time(philo);
	pthread_mutex_unlock(&philo->last_meal);
	if (still_alive(philo->data) == 0)
	{
		write_message(philo, msg_eat);
		better_sleep(philo->data, philo->data->t_eat);
		philo->times_eaten += 1;
	}
	pthread_mutex_unlock(&philo->data->forks_lock[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks_lock[philo->right_fork]);
	return (OK);
}

void	philo_sleep(t_philo *philo)
{
	if (still_alive(philo->data) == 0)
	{
		write_message(philo, msg_sleep);
		better_sleep(philo->data, philo->data->t_sleep);
	}
}

void	philo_think(t_philo *philo)
{
	if (still_alive(philo->data) == 0)
	{
		write_message(philo, msg_think);
		usleep(50);
	}
}
