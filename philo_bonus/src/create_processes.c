/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_processes.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/07/22 13:21:03 by cpopa         ########   odam.nl         */
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

static t_philo	*initialize_data_process(t_data *data, int i)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		error_exit("failed malloc - init_philo_process\n");
	philo->data = data;
	philo->id = i;
	philo->status = ACTIVE;

	philo->name_dead = ft_itoa(philo->id);
	// dprintf(2, "name_dead = %p\n", philo->name_dead);
	if (!philo->name_dead)
		error_exit("strdup fail: name_dead\n");
	philo->s_dead = open_semaphore(&philo->s_dead, philo->name_dead, 1);
	if (philo->s_dead == SEM_FAILED)
		error_exit("sem fail: s_dead\n");

	// dprintf(2, "s_dead = %p\n", philo->s_dead);
	philo->name_last_meal = ft_itoa(philo->id + 1000);
	// dprintf(2, "name_dead = %p\n", philo->name_last_meal);
	if (!philo->name_last_meal)
		error_exit("strdup fail: name_last_meal\n");
	philo->s_last_meal = open_semaphore(&philo->s_last_meal,
			philo->name_last_meal, 1);
	if (philo->s_last_meal == SEM_FAILED)
		error_exit("sem fail: s_last_meal\n");


	philo->name_status = ft_itoa(philo->id + 2000);
	if (!philo->name_status)
		error_exit("strdup fail: name_status\n");
	philo->s_last_meal = open_semaphore(&philo->s_status,
			philo->name_last_meal, 1);
	if (philo->s_status == SEM_FAILED)
		error_exit("sem fail: s_status\n");

	philo->times_eaten = 0;
	philo->last_eaten = (int)get_elapsed_time(philo);
	return (philo);
}

void	clean_up_process(t_philo *philo) // it never reaches here
{
	// dprintf(2, "pid = %d, sems: %p, %p\n",getpid(), philo->s_last_meal, philo->s_dead);
	close_semaphore(philo->s_last_meal, philo->name_last_meal);
	close_semaphore(philo->s_dead, philo->name_dead);
	free(philo->name_last_meal);
	free(philo->name_dead);
	free(philo->name_status);
	free(philo->thread);
	free(philo);
}

static int	execute_process(t_data *data, int i)
{
	t_philo		*philo;

	free(data->philos);
	free(data->process_id);

	
	// dprintf(2, "pid = %d, data = %p\n", getpid(), data);
	philo = initialize_data_process(data, i);

	philo->thread = malloc(sizeof(pthread_t));
	// dprintf(2, "thread: %p\n", philo->thread);
	if (!philo->thread)
		error_exit("malloc fail: thread\n");
	if (pthread_create(philo->thread, NULL, routine, philo) != 0)
		error_exit("pthread_create fail\n");
	// if (pthread_detach(*(philo->thread)) != 0)
	// 	error_exit("pthread_detach fail\n");

	
	while (1)
	{
		sem_wait(philo->s_dead);
		if (overeaten(philo) == 1)
		{
			write_message(philo, msg_die);
			exit(DEAD);
		}
		sem_post(philo->s_dead);
		
		sem_wait(philo->s_status);
		if (philo->status == INNACTIVE)
		{
			pthread_join(*philo->thread, NULL);
			exit (FULL);
		}
		sem_post(philo->s_status);

		usleep(5000);
	}
	pthread_join(*philo->thread, NULL);
	// clean_up_process(philo);
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
			exit(execute_process(data, i));
		i++;
	}
	return (OK);
}
