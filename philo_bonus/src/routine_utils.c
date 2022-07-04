/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/07/04 16:08:40 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	sem_wait(philo->s_last_meal);
	philo->last_eaten = (int)get_elapsed_time(philo);
	sem_post(philo->s_last_meal);

	write_message(philo, msg_eat);
	better_sleep(philo->data->t_eat);
	philo->times_eaten += 1;

	sem_post(&philo->data->s_forks[philo->left_fork]);
	sem_post(&philo->data->s_forks[philo->right_fork]);
}

void	philo_sleep(t_philo *philo)
{
	write_message(philo, msg_sleep);
	better_sleep(philo->data->t_sleep);
}

void	philo_think(t_philo *philo)
{
	write_message(philo, msg_think);
	better_sleep(40);
}
