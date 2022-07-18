/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/07/17 20:59:53 by janeway       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks_lock[philo->left_fork]);
	if (still_alive(philo->data) == 0)
		write_message(philo, msg_fork);
	pthread_mutex_lock(&philo->data->forks_lock[philo->right_fork]);
	if (still_alive(philo->data) == 0)
		write_message(philo, msg_fork);
}

void	*single_philo(t_philo *philo)
{
	write_message(philo, msg_fork);
	better_sleep(philo->data->t_die);
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;

	pthread_mutex_lock(&philo->data->dead_monitor);
	pthread_mutex_unlock(&philo->data->dead_monitor);

	if (philo->data->nr_philo == 1)
		return (single_philo(philo));
	if ((philo->id + 1) % 2 == 0)
	{
		write_message(philo, msg_sleep);
		better_sleep(philo->data->t_eat / 2);
	}
	while (still_alive(philo->data) == 0)
	{
		take_forks(philo);
		philo_eat(philo);
		if (philo->data->nr_rounds != -1
			&& philo->times_eaten == philo->data->nr_rounds)
			break ;
		philo_sleep(philo);
		philo_think(philo);
	}
	philo->status = INNACTIVE;
	return (NULL);
}
