/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/06/19 14:43:23 by janeway       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{

	// philo->left_fork = philo->id;
	// philo->right_fork = philo->id - 1;
	// if (philo->right_fork == -1)
	// 	philo->right_fork = philo->data->nr_philo - 1;


	//lock forks
	pthread_mutex_lock(&philo->data->forks_lock[philo->left_fork]);
	if (philo->data->dead_philo == 0)
		write_message(philo, msg_fork);
	pthread_mutex_lock(&philo->data->forks_lock[philo->right_fork]);
	if (philo->data->dead_philo == 0)
		write_message(philo, msg_fork);
}

int	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meal);
	philo->last_eaten = (int)get_elapsed_time(philo);  // does it need mutex protection? 
	pthread_mutex_unlock(&philo->last_meal);
	if (philo->data->dead_philo == 0)
	{
		write_message(philo, msg_eat);
		//better_sleep(philo->data->t_eat);
		better_sleep(philo->data, philo->data->t_eat);
		philo->times_eaten += 1;
//		printf("id: %d, time eaten: %d\n", (philo->id + 1), philo->times_eaten);    /// erase when completed

	}
	// release forks
	pthread_mutex_unlock(&philo->data->forks_lock[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks_lock[philo->right_fork]);
//	write_message(philo, msg_release);                              // erase when completed

	

	return (OK);
}

void	philo_sleep(t_philo *philo)
{
	if (philo->data->dead_philo == 0)
	{
		write_message(philo, msg_sleep);
		better_sleep(philo->data, philo->data->t_sleep);
	}
}

void	philo_think(t_philo *philo)
{
	if (philo->data->dead_philo == 0)
		write_message(philo, msg_think);
}

void *single_philo(t_philo *philo)
{
	write_message(philo, msg_fork);
	better_sleep(philo->data, philo->data->t_die);
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;

	write_message(philo, msg_born); // erase 
	if (surveilance(philo) == ERROR)
		return (NULL);
	if (philo->data->nr_philo == 1)
		return (single_philo(philo));
	if ((philo->id + 1) % 2 == 0)
		// better_sleep(philo->data, philo->data->t_eat);
		better_sleep(philo->data, (philo->data->t_eat * 90) / 100);
		
	while (philo->data->dead_philo == 0)
	{
		take_forks(philo);
		philo_eat(philo);
		if (philo->times_eaten == philo->data->nr_rounds)
			break;
		philo_sleep(philo);
		philo_think(philo);
	}
	pthread_join(philo->surveilance, NULL);
	return (NULL);
}
