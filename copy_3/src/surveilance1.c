/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   surveilance1.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/06/25 16:14:49 by janeway       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	still_alive(t_data *data)
{
	int	dead;

	dead = 0;
	pthread_mutex_lock(&data->dead_monitor);
	if (data->dead_philo == 1)
		dead = 1;
	pthread_mutex_unlock(&data->dead_monitor);
	return (dead);
}

static int	overeaten(t_philo *philo)
{
	int	elapsed_time;
	int	eat_time;

	eat_time = 0;
	elapsed_time = (int)get_elapsed_time(philo);
	pthread_mutex_lock(&philo->last_meal);
	if ((elapsed_time - philo->last_eaten) > philo->data->t_die)
		eat_time = 1;
	pthread_mutex_unlock(&philo->last_meal);
	return (eat_time);
}

void	*dead_philo(void *arg)
{
	t_data *data;
	int		i;
	int		innactive;

	data = (t_data *)arg;
	innactive = 1;
	while (data->dead_philo == 0)
	{
		i = 0;
		innactive = 1;
		while (i < data->nr_philo && innactive != data->nr_philo)
		{
			if (data->philos[i].status == ACTIVE)
			{
				if (overeaten(&data->philos[i]) == 1)
				{
					pthread_mutex_lock(&data->dead_monitor);
					data->dead_philo = 1;
					pthread_mutex_unlock(&data->dead_monitor);
					write_message(&data->philos[i], msg_die);
					return (NULL);
				}
				i++;
			}
			else if (data->philos[i].status == INNACTIVE)
			{
				innactive++;
				if (innactive == data->nr_philo)
					return (NULL);
			}
		}
	}
	return (NULL);
}
