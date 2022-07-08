/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_data_processes.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/08 13:21:18 by cpopa         #+#    #+#                 */
/*   Updated: 2022/07/08 15:23:47 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static sem_t	*init_semaphore(sem_t **address, char *name)
{
	sem_unlink(name);
	*address = sem_open(name, O_CREAT | O_EXCL, 0777, 1);
	if (*address == SEM_FAILED)
		error_exit("sem_open fail\n");
	return (*address);
}

t_philo	*init_data_process(t_data *data, int i)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		error_exit("failed malloc - init_philo_process\n");
	philo->data = data;
	philo->id = i;
	philo->times_eaten = 0;
	philo->status = ACTIVE;
	philo->last_eaten = (int)get_elapsed_time(philo);
	philo->name_last_meal = ft_itoa(philo->id);
	if (!philo->name_last_meal)
		error_exit("strdup fail: name_last_meal\n");
	philo->s_last_meal = init_semaphore(&philo->s_last_meal,
			philo->name_last_meal);
	philo->name_dead = ft_itoa(philo->id + 1000);
	if (!philo->name_dead)
		error_exit("strdup fail: name_dead\n");
	philo->s_dead = init_semaphore(&philo->s_dead, philo->name_dead);
	return (philo);
}
