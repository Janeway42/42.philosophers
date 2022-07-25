/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_processes.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/07/25 17:49:15 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	overeaten(t_philo *philo)
{
	int	eat_time;

	eat_time = 0;
	sem_wait(philo->s_last_meal);
	if (((int)get_elapsed_time(philo) - philo->last_eaten)
		>= philo->data->t_die)
		eat_time = 1;
	sem_post(philo->s_last_meal);
	return (eat_time);
}

static int	stop_dead(t_philo *philo, int exit_code)
{
	sem_wait(philo->s_dead);
	write_message(philo, msg_die);
	sem_post(philo->s_dead);
	clean_up_process(philo);
	exit(exit_code);
}

static int	stop_full(t_philo *philo, pthread_t *thread, int exit_code)
{
	sem_post(philo->s_status);
	pthread_join(*thread, NULL);
	clean_up_process(philo);
	exit (exit_code);
}

static int	execute_process(t_data *data, int i)
{
	t_philo		*philo;
	pthread_t	thread;

	free(data->philos);
	free(data->process_id);
	thread = NULL;
	philo = initialize_data_process(data, i);
	if (pthread_create(&thread, NULL, routine, philo) != 0)
		error_exit("pthread_create fail\n");
	while (1)
	{
		if (check_status(philo) == 1 && overeaten(philo) == 0)
			stop_full(philo, &thread, FULL);
		else if (overeaten(philo) == 1)
			stop_dead(philo, DEAD);
		usleep(1500);
	}
	pthread_join(thread, NULL);
	clean_up_process(philo);
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
