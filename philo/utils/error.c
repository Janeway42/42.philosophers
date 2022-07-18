/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/07/18 17:01:59 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error(char *str)
{
	write(STDERR_FILENO, str, ft_strlen(str));
	return (ERROR);
}

int	error_forks(t_data *data, char *str)
{
	free(data->philos);
	write(STDERR_FILENO, str, ft_strlen(str));
	return (ERROR);
}

int	error_init_mutexes(t_data *data, char *str)
{
	free(data->philos);
	free(data->forks_lock);
	destroy_mutexes(data);
	write(STDERR_FILENO, str, ft_strlen(str));
	return (ERROR);
}

int	error_malloc_threads(t_data *data, char *str)
{
	write(STDERR_FILENO, str, ft_strlen(str));
	destroy_mutexes(data);
	free_stuff(data);
	return (ERROR);
}

int	error_create_threads(t_data *data, int count)
{
	int	i;

	i = 0;
	write(STDERR_FILENO, "failed threads\n", 16);
	while (i < count)
	{
		pthread_join(data->pthread_id[i], NULL);
		i++;
	}
	destroy_mutexes(data);
	free_stuff(data);
	return (ERROR);
}
