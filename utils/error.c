/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/06/13 17:33:28 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error(char *str)
{
	write(2, &str, ft_strlen(str));
	return (ERROR);
}

// int	error_sleep(t_data *data)  // do I need to release mutexes in this case? 
// {
// 	write(2, "failed usleep\n", 15);
// 	//printf("failed usleep\n");
// 	free_all(data);
// 	return (ERROR);
// }