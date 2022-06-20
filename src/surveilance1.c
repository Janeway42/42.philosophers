/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   surveilance1.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/06/20 16:24:26 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*dead_philo(void *arg)
{
	t_data *data;
	int	elapsed_time;
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
			pthread_mutex_lock(&data->dead_monitor);
			elapsed_time = (int)get_elapsed_time(&data->philos[i]);
			if (data->philos[i].status == ACTIVE)
			{
				
				if ((elapsed_time - data->philos[i].last_eaten) > data->t_die)
				{
					data->dead_philo = 1;
					write_message(&data->philos[i], msg_die);
					return (NULL);
				}
				
			}
			else if (data->philos[i].status == INNACTIVE)
			{
				innactive++;
				if (innactive == data->nr_philo)
					return (NULL);
			}
			else
				i++;
			pthread_mutex_unlock(&data->dead_monitor);
		}
	}
	return (NULL);
}
