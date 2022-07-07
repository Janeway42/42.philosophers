/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/07/07 16:14:21 by janeway       ########   odam.nl         */
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
	free_stuff(data);
	return (ERROR);
}

int	error_semaphore(char *str, t_data *data)
{
	write(STDERR_FILENO, str, ft_strlen(str));
	sem_unlink("FORKS");
	sem_unlink("WRITE");
	close_semaphore(data->s_forks, "FORKS");
	close_semaphore(data->s_write, "WRITE");
	free_stuff(data);
	return (ERROR);
}

int	error_exit(char *str)
{
	write(STDERR_FILENO, str, ft_strlen(str));
	exit(1);
}
