/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   processes_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/07/25 13:40:44 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_philo	*initialize_data_process(t_data *data, int i)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		error_exit("failed malloc - init_philo_process\n");
	philo->data = data;
	philo->id = i;
	philo->status = ACTIVE;
	philo->name_dead = ft_itoa(philo->id);
	if (!philo->name_dead)
		error_exit("strdup fail: name_dead\n");
	philo->s_dead = open_semaphore(&philo->s_dead, philo->name_dead, 1);
	philo->name_last_meal = ft_itoa(philo->id + 1000);
	if (!philo->name_last_meal)
		error_exit("strdup fail: name_last_meal\n");
	philo->s_last_meal = open_semaphore(&philo->s_last_meal,
			philo->name_last_meal, 1);
	philo->name_status = ft_itoa(philo->id + 2000);
	if (!philo->name_status)
		error_exit("strdup fail: name_status\n");
	philo->s_status = open_semaphore(&philo->s_status,
			philo->name_status, 1);
	philo->times_eaten = 0;
	philo->last_eaten = (int)get_elapsed_time(philo);
	return (philo);
}
