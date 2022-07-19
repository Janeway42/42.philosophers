/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_threads.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/07/19 13:36:34 by janeway       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_pthreads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nr_philo)
	{
		if (pthread_create(&data->pthread_id[i], NULL,
				&routine, &data->philos[i]) != 0)
			return (error_threads(data, i, "failed threads\n"));
		i++;
	}
	if (pthread_create(&data->surveilance, NULL,
			&dead_philo, data) != 0)
		return (error_threads(data, data->nr_philo,
				"failed surveillance thread\n"));
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
