/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/06/07 16:14:15 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_time()
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return (time.tv_sec);
}

void	take_forks(t_philo *philo)
{
	// lock neighbours
	// pthread_mutex_lock(&philo->data->philos[philo->left_fork].neighbour_lock);   ///////////////
	// pthread_mutex_lock(&philo->data->philos[philo->right_fork].neighbour_lock);


	// printf("%d\n", philo->id);
	// lock forks
	pthread_mutex_lock(&philo->data->forks_lock[philo->left_fork]);
	state_message(philo, msg_fork);
	pthread_mutex_lock(&philo->data->forks_lock[philo->right_fork]);
	state_message(philo, msg_fork);

	// release neighbours
	// pthread_mutex_unlock(&philo->data->philos[philo->left_fork].neighbour_lock);
	// pthread_mutex_unlock(&philo->data->philos[philo->right_fork].neighbour_lock);
}

int	check_last_eaten(t_philo *philo)
{
	int	time;
	int elapsed_time;

	time = get_time();
	elapsed_time = time - philo->last_eaten;
	if (elapsed_time > philo->data->info.t_die)
		return (1);
	philo->last_eaten = time;
	return (0);
}

int	philo_eat(t_philo *philo)
{
	// last eaten
	if (check_last_eaten(philo) == 1)
		return (philo_dead(philo));
	
	// eat
	if (usleep(philo->data->info.t_eat * 1000) == -1)
		return (failed_sleep(philo));

	// release forks 
	pthread_mutex_unlock(&philo->data->forks_lock[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks_lock[philo->right_fork]);
	philo->times_eaten += 1;

	return (EXIT_OK);
}

void	philo_sleep(t_philo *philo)
{
//	printf("philosopher %d is now sleeping\n", (philo->id + 1));
	state_message(philo, msg_sleep);
	usleep(philo->data->info.t_sleep);
}

// void	philo_think(t_philo *philo)
// {
// 	printf("philosopher %d is now thinking\n", (philo->id + 1));
// 	usleep(philo->data->input.t_th);
// }

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;

//	if (check_times_to_eat(data))

	take_forks(philo);
	philo_eat(philo);
	philo_sleep(philo);

	// think
	pthread_join(philo->data->pthread_id[philo->id], NULL);
	return (NULL);
}
