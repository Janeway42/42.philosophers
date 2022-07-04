/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   surveillance.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/07/04 16:48:20 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	overeaten(t_philo *philo)
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

void	kill_processes(t_data *data, pid_t pid)
{
	int	i;

	i = 0;
	while (i < data->nr_philo)
	{
		if (pid != data->process_id[i])
			kill(data->process_id[i], SIGKILL);
		i++;
	}

}

int	surveillance(t_data *data)
{
	int		i;
	int		status;
	pid_t	pid;

	i = 0;
	while (1)
	{
		while (i < data->nr_philo)
		{
			pid = waitpid(-1, &status, 0);
			if (WIFEXITED(status) && WEXITSTATUS(status) == DIED)
			{
				printf("test10\n");
				kill_processes(data, pid);
				break ;
			}
			i++;
		}
	}

}
