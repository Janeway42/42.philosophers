/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/07/18 12:58:12 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meal);
	philo->last_eaten = (int)get_elapsed_time(philo);
	pthread_mutex_unlock(&philo->last_meal);

	write_message(philo, msg_eat);
	better_sleep(philo->data, philo->data->t_eat);
	philo->times_eaten++;

	pthread_mutex_unlock(&philo->data->forks_lock[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks_lock[philo->right_fork]);
	return (OK);
}

void	philo_sleep(t_philo *philo)
{
	write_message(philo, msg_sleep);
	better_sleep(philo->data, philo->data->t_sleep);
}

void	philo_think(t_philo *philo)
{
	write_message(philo, msg_think);
	usleep(50);
}
