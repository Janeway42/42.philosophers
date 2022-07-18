/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/07/17 21:11:31 by janeway       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error(char *str)
{
	write(STDERR_FILENO, str, ft_strlen(str));
	return (ERROR);
}

int	error_free(char *str, t_data *data)
{
	write(STDERR_FILENO, str, ft_strlen(str));
	free_allocated(data);
	return (ERROR);
}

int	error_mutex(t_data *data, char *str)
{
	write(STDERR_FILENO, str, ft_strlen(str));
	destroy_mutexes(data);
	free_allocated(data);
	return (ERROR);
}

int	error_malloc_threads(t_data *data, char *str)
{
	write(STDERR_FILENO, str, ft_strlen(str));
	destroy_mutexes(data);
	free_allocated(data);
	return (ERROR);
}
