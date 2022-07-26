/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_utilss.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/07/26 12:00:58 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	general_error(t_data *data, char *str)
{
	write(STDERR_FILENO, str, ft_strlen(str));
	kill_processes(data);
	free_memory(data);
	exit(ERROR);
}
