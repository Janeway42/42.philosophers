/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/07/26 12:00:51 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	error(char *str)
{
	write(STDERR_FILENO, str, ft_strlen(str));
	return (ERROR);
}

int	error_exit(char *str)
{
	write(STDERR_FILENO, str, ft_strlen(str));
	return (ERROR);
}

int	error_exit_process(char *str, t_philo *philo)
{
	write(STDERR_FILENO, str, ft_strlen(str));
	clean_up_process(philo);
	exit(ERROR);
}

int	error_memory(t_data *data, char *str)
{
	write(STDERR_FILENO, str, ft_strlen(str));
	free_memory(data);
	return (ERROR);
}

int	error_semaphore(char *str, t_data *data)
{
	write(STDERR_FILENO, str, ft_strlen(str));
	close_semaphore(data->s_forks, "FORKS");
	close_semaphore(data->s_write, "WRITE");
	free_memory(data);
	return (ERROR);
}
