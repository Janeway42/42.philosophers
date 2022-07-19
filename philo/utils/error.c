/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/07/19 13:37:08 by janeway       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error(char *str)
{
	write(STDERR_FILENO, str, ft_strlen(str));
	return (ERROR);
}

int	error_memory(t_data *data, char *str)
{
	free_memory(data);
	write(STDERR_FILENO, str, ft_strlen(str));
	return (ERROR);
}

int	error_mutex(t_data *data, char *str)
{
	free(data->philos);
	free(data->forks_lock);
	destroy_mutexes(data);
	write(STDERR_FILENO, str, ft_strlen(str));
	return (ERROR);
}

int	error_threads(t_data *data, int count, char *str)
{
	int	i;

	i = 0;
	write(STDERR_FILENO, str, ft_strlen(str));
	while (i < count)
	{
		pthread_join(data->pthread_id[i], NULL);
		i++;
	}
	destroy_mutexes(data);
	free_memory(data);
	return (ERROR);
}
