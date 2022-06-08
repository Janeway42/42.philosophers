/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/06/08 20:14:42 by janeway       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_threads(t_data *data, int i)
{
	while (i > -1)
	{
		pthread_join(data->pthread_id[i], NULL);
		i--;
	}
	return (error_init_data(data, err_threads));
}

int	create_pthreads(t_data *data)
{
	int	i;

	i = 0;
	data->pthread_id = malloc(sizeof(pthread_t) * data->nr_philo);
	if (!data->pthread_id)
		return (error("failed threads\n"));
	while (i < data->nr_philo)
	{
		if (pthread_create(&data->pthread_id[i], NULL,
					&routine, &data->philos[i]) != 0)
			error_threads(data, err_threads);
		i++;
	}
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
	return (OK);
}