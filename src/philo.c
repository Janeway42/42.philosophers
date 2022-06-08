/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/06/08 14:37:02 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_input(int argc, char **argv, t_data *data)
{
	if (argc < 5 || argc > 6)
		return (error("wrong input"));
	
	data->nr_philo = ft_atoi(argv[1]);
	if (data->nr_philo < 1)
		return (error("Wrong number of philosophers"));
	data->t_die = ft_atoi(argv[2]);
	if (data->t_die < 1)
		return (error("Wrong time to die"));
	data->t_eat = ft_atoi(argv[3]);
	if (data->t_eat < 1)
		return(error("Wrong time to eat"));
	data->t_sleep = ft_atoi(argv[4]);
	if (data->t_sleep < 1)
		return(error("Wrong time to sleep"));
	if (argc == 6)
	{
		data->nr_rounds = ft_atoi(argv[5]);
		if (data->nr_rounds < 0)
			return(error("Not enough rounds to eat"));
	}
	return (OK);
}

int main (int argc, char **argv)
{
	t_data data;

	if (get_input(argc, argv, &data))
		return (ERROR);

	if (init_data(&data) == ERROR)
		return (ERROR);
	create_pthreads(&data);

	printf("%d, %d, %d, %d\n", data.nr_philo, data.t_die, data.t_eat, data.t_sleep);
	printf("%d, %d, %d, %d, %d\n", data.nr_philo, data.t_die, data.t_eat, data.t_sleep, data.nr_rounds);
//	free_all(&data);
	return (OK);
}
