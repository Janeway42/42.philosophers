/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_processes.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/07/04 17:01:05 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	execute_process(t_philo *philo)
{
	char		*s_surveillance;

	sem_unlink(s_surveillance);
	printf("test start create process\n");
	if (pthread_create(philo->thread, NULL, routine, &philo) != 0)
		error("pthread_create fail - thread\n");
	printf("test start create process -x\n");
	// pthread_detach(*philo->thread);
	printf("test start create process -xx\n");
	
	philo->s_last_meal = sem_open(s_surveillance, O_CREAT, 0660, 1);
	if (philo->s_last_meal == SEM_FAILED)
		exit(1); // exit code	

	printf("test start create process -xxx\n");

	while (1)
	{
		if (philo->status == ACTIVE && overeaten(philo) == 1)
		{
			write_message(philo, msg_die);
			exit(-1); // exit kill
		}
		if (philo->status == INNACTIVE)
			break ;
		usleep(50);
	}
	pthread_join((*philo->thread), NULL);
	sem_close(philo->s_last_meal);
	free(philo->s_last_meal);
	return (OK);
}

int	create_processes(t_data *data)
{
	int		i;
	
	i = 0;
	while (i < data->nr_philo)
	{
		data->process_id[i] = fork();
		if (data->process_id[i] == -1)
			error("fork failed\n");
		if (data->process_id[i] == 0)
			return(execute_process(&data->philos[i]));
		i++;
	}
	printf("test1 - end create processes\n");  // -------------------------------
	return (OK);
}
