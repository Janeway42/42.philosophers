/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   start_threads.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/07/17 21:10:06 by janeway       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	error_philo_threads(t_data *data, int count, char *str)
{
	int	i;

	i = 0;
	write(STDERR_FILENO, str, 16);
	while (i < count)
	{
		pthread_join(data->pthread_id[i], NULL);
		i++;
	}
	clean_up(data);
	return (ERROR);
}

static int	error_surveillance_thread(t_data *data, char *str)
{
	pthread_join(data->surveilance, NULL);
	return (error_philo_threads(data, data->nr_philo, str));
}

int	create_pthreads(t_data *data)
{
	int	i;

	i = 0;

	pthread_mutex_lock(&data->dead_monitor);

	while (i < data->nr_philo)
	{
		if (pthread_create(&data->pthread_id[i], NULL,
				&routine, &data->philos[i]) != 0)
			return (error_philo_threads(data, i, "failed threads\n"));
		i++;
	}
	if (pthread_create(&data->surveilance, NULL,
			&dead_philo, data) != 0)
		return (error_surveillance_thread(data, "failed surveilance thread\n"));

	gettimeofday(&data->start_time, NULL);
	
	pthread_mutex_unlock(&data->dead_monitor);	
	return (OK);
}

int	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nr_philo)
	{
		pthread_join(data->pthread_id[i], NULL);
		i++;
	}
	pthread_join(data->surveilance, NULL);
	return (OK);
}
