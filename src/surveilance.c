/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   surveilance.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/06/19 14:40:42 by janeway       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*dead_philo(void *arg)
{
	t_philo	*philo;
	int		elapsed_time;

	philo = (t_philo *)arg;
	while (philo->data->dead_philo == 0)
	{
		if ((philo->data->dead_philo == 1) || (philo->times_eaten == philo->data->nr_rounds))
			break;
		elapsed_time = (int)get_elapsed_time(philo);
	//	if (philo->data->dead_philo == 0 && ((elapsed_time - philo->last_eaten) > philo->data->t_die))
		if (((elapsed_time - philo->last_eaten) > philo->data->t_die) && (philo->times_eaten != philo->data->nr_rounds))
		{
			pthread_mutex_lock(&philo->dead_monitor);
			philo->data->dead_philo = 1;
			pthread_mutex_unlock(&philo->dead_monitor);
			write_message(philo, msg_die);
		}
		usleep(10);
	}
	return (NULL);
}

int	surveilance(t_philo *philo)
{
	if (pthread_create(&philo->surveilance, NULL,
			&dead_philo, philo)!= 0)
		{
			write(STDERR_FILENO, "surveilance thread fail\n", 27);
			pthread_mutex_lock(&philo->dead_monitor);
			philo->data->dead_philo = 1;
			pthread_mutex_unlock(&philo->dead_monitor);
			return (ERROR);
		}
	return (OK);
}