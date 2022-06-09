/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/06/09 17:48:03 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	// lock neighbours
	pthread_mutex_lock(philo->data->philos[philo->left_fork].neighbour_lock);
	pthread_mutex_lock(philo->data->philos[philo->right_fork].neighbour_lock);

	// lock forks
	pthread_mutex_lock(&philo->data->forks_lock[philo->left_fork]);
	write_message(philo, msg_fork);
	pthread_mutex_lock(&philo->data->forks_lock[philo->right_fork]);
	write_message(philo, msg_fork);

	// release neighbours
	pthread_mutex_unlock(philo->data->philos[philo->left_fork].neighbour_lock);
	pthread_mutex_unlock(philo->data->philos[philo->right_fork].neighbour_lock);
}

void	check_last_eaten(t_philo *philo)
{
	int	time;

	time = get_elapsed_time(philo);
	printf("time: %d\n", time);
	printf("last eaten: %d\n", philo->last_eaten);
	if ((time - philo->last_eaten) > philo->data->t_die)
		philo->data->dead_philo = 1;
	philo->last_eaten = time;
}

int	philo_eat(t_philo *philo)
{

	write_message(philo, msg_eat);

	better_sleep(philo->data->t_sleep);
	//if (usleep(philo->data->t_eat * 1000) != 0)
	//	return (error_sleep(philo->data));

	// release forks
	pthread_mutex_unlock(&philo->data->forks_lock[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks_lock[philo->right_fork]);
	write_message(philo, msg_release);                              // erase when completed

	philo->times_eaten += 1;
	printf("time eaten: %d\n", philo->times_eaten);    /// erase when completed

	return (OK);
}

void	philo_sleep(t_philo *philo)
{
	write_message(philo, msg_sleep);
	//better_sleep(philo->data->t_sleep);
	if (usleep(philo->data->t_sleep * 1000) != 0)
		error_sleep(philo->data);
}

void	philo_think(t_philo *philo)
{
	write_message(philo, msg_think);
}

int	check_dead(t_data *data)
{
	pthread_mutex_lock(data->dead_monitor);
	if (data->dead_philo == 1)
		return (1);
	pthread_mutex_unlock(data->dead_monitor);
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (check_dead(philo->data) == 1)
			break;
		take_forks(philo);
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}


