/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_processes.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/07/12 17:19:27 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	overeaten(t_philo *philo)
{
	int	elapsed_time;
	int	eat_time;

	eat_time = 0;
	elapsed_time = (int)get_elapsed_time(philo);
	sem_wait(philo->s_last_meal);
	if ((elapsed_time - philo->last_eaten) >= philo->data->t_die)
		eat_time = 1;
	sem_post(philo->s_last_meal);
	return (eat_time);
}

t_philo	*init_data_process(t_data *data, int i)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		error_exit("failed malloc - init_philo_process\n");
	philo->data = data;
	philo->id = i;
	philo->name_dead = ft_itoa(philo->id + 1000);
	if (!philo->name_dead)
		error_exit("strdup fail: name_dead\n");
	philo->s_dead = open_semaphore(&philo->s_dead, philo->name_dead, 1);
	philo->name_last_meal = ft_itoa(philo->id);
	if (!philo->name_last_meal)
		error_exit("strdup fail: name_last_meal\n");
	philo->s_last_meal = open_semaphore(&philo->s_last_meal,
			philo->name_last_meal, 1);
	philo->times_eaten = 0;
	philo->status = ACTIVE;
	philo->last_eaten = (int)get_elapsed_time(philo);
	return (philo);
}

static void	clean_up_process(t_philo *philo, pthread_t *thread)
{
	close_semaphore(philo->s_last_meal, philo->name_last_meal);
	close_semaphore(philo->s_dead, philo->name_dead);
	free(philo->name_last_meal);
	free(philo->name_dead);
	free(thread);
}

int	execute_process(t_data *data, int i)
{
	pthread_t	*thread;
	t_philo		*philo;

	free(data->philos);
	philo = init_data_process(data, i);
	thread = malloc(sizeof(pthread_t));
	if (!thread)
		error_exit("malloc fail: thread\n");
	if (pthread_create(thread, NULL, routine, philo) != 0)
		error_exit("pthread_create fail\n");
	if (pthread_detach(*thread) != 0)
		error_exit("pthread_detach fail\n");
	while (1)
	{
		sem_wait(philo->s_dead);
		if (philo->status == ACTIVE && overeaten(philo) == 1)
		{
			write_message(philo, msg_die);
			exit(DEAD);
		}
		sem_post(philo->s_dead);
		usleep(50);
	}
	clean_up_process(philo, thread);
	return (OK);
}

int	create_processes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nr_philo)
	{
		data->process_id[i] = fork();
		if (data->process_id[i] == -1)
			error_exit("fork failed \n");
		if (data->process_id[i] == 0)
			return (execute_process(data, i));
		i++;
	}
	return (OK);
}
