/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/07/01 17:17:55 by cpopa         ########   odam.nl         */
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
