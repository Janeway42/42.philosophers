/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/07/07 19:01:50 by janeway       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_eat(t_philo *philo)
{
	sem_wait(philo->s_last_meal);
	philo->last_eaten = (int)get_elapsed_time(philo);
	sem_post(philo->s_last_meal);

	sem_wait(philo->s_dead);
	write_message(philo, msg_eat);
	better_sleep(philo->data->t_eat);
	philo->times_eaten += 1;
	sem_post(philo->s_dead);  // test if fine

	sem_post(philo->data->s_forks);
	sem_post(philo->data->s_forks);
	return (OK);
}

void	philo_sleep(t_philo *philo)
{
	write_message(philo, msg_sleep);
	better_sleep(philo->data->t_sleep);
}

void	philo_think(t_philo *philo)
{
	write_message(philo, msg_think);
	// if (philo->id % 2 != 0)            /// decide 
	usleep(50);
}
