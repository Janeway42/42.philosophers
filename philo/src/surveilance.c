/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   surveilance.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/07/20 13:35:27 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	still_alive(t_data *data)
{
	int	dead;

	dead = 0;
	pthread_mutex_lock(&data->dead_lock);
	if (data->dead_philo == 1)
		dead = 1;
	pthread_mutex_unlock(&data->dead_lock);
	return (dead);
}

static int	check_overeaten(t_philo *philo)
{
	// int	elapsed_time;
	int	eat_time;

	eat_time = 0;
	// elapsed_time = (int)get_elapsed_time(philo);
	pthread_mutex_lock(&philo->local_dead_lock);
	pthread_mutex_lock(&philo->meal_lock);
	if (((int)get_elapsed_time(philo) - philo->last_eaten) > philo->data->t_die)
		eat_time = 1;
	pthread_mutex_unlock(&philo->meal_lock);
	pthread_mutex_unlock(&philo->local_dead_lock);
	return (eat_time);
}

void	*overeaten(t_data *data, int i)
{
	pthread_mutex_lock(&data->dead_lock);
	data->dead_philo = 1;
	pthread_mutex_unlock(&data->dead_lock);
	write_message(&data->philos[i], msg_die);
	return (NULL);
}

void	*dead_philo(void *arg)
{
	t_data	*data;
	int		i;
	int		innactive;

	data = (t_data *)arg;
	innactive = 0;
	while (data->dead_philo == 0)
	{
		i = 0;
		while (i < data->nr_philo && innactive != data->nr_philo)
		{
			if (data->philos[i].status == ACTIVE
				&& check_overeaten(&data->philos[i]) == 1)
				return (overeaten(data, i));
			if (data->philos[i].status == INNACTIVE)
			{
				innactive++;
				if (innactive == data->nr_philo)
					return (NULL);
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
