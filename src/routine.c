/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/06/08 22:35:58 by janeway       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_elapsed_time(t_philo *philo)
{
	struct timeval time;
	int elapsed_time;

	if (gettimeofday(&time, NULL) != 0)
		return (ERROR);
	elapsed_time = ((time.tv_sec - philo->data->start_time.tv_sec) * 1000 + (time.tv_usec - philo->data->start_time.tv_usec) / 1000);
	return (elapsed_time);
}

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

int	check_last_eaten(t_philo *philo)
{
	int	time;

	time = get_elapsed_time(philo);
	printf("time: %d\n", time);
	printf("last eaten: %d\n", philo->last_eaten);
	if ((time - philo->last_eaten) > philo->data->t_die)
		return (1);
	philo->last_eaten = time;
	return (0);
}

int	philo_eat(t_philo *philo)
{

	// last eaten
	// if (check_last_eaten(philo) == 1)
	// 	return (2);
		// return (philo_dead(philo));
	// printf("control eat 1\n");

	// eat
	write_message(philo, msg_eat);
	usleep(philo->data->t_eat * 1000);
	//sleep(2);

	// if (usleep(philo->data->t_eat * 1000) != 0)
	// 	return (failed_sleep(philo));

	// write (1, "control eat 2\n", 15);
	
	// release forks 
	pthread_mutex_unlock(&philo->data->forks_lock[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks_lock[philo->right_fork]);
	philo->times_eaten += 1;
	printf("time eaten: %d\n", philo->times_eaten);

	return (OK);
}

void	philo_sleep(t_philo *philo)
{
	write_message(philo, msg_sleep);
	usleep(philo->data->t_sleep * 1000);
}

void	philo_think(t_philo *philo)
{
	write_message(philo, msg_think);
//	usleep(philo->data.);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;

//	while loop - while (true) - while none of the philosophers is dead 

	take_forks(philo);
	// printf("control\n");
	philo_eat(philo);
	philo_sleep(philo);
	// think

	return (NULL);
}
