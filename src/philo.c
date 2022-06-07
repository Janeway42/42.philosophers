/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/06/07 14:07:15 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_input(int argc, char **argv, t_info *input)
{
	if (argc < 5 || argc > 6)
		return (error("wrong input"));
	
	input->nr_philo = ft_atoi(argv[1]);
	if (input->nr_philo < 1)
		return (error("Wrong number of philosophers"));
	input->t_die = ft_atoi(argv[2]);
	if (input->t_die < 1)
		return (error("Wrong time to die"));
	input->t_eat = ft_atoi(argv[3]);
	if (input->t_eat < 1)
		return(error("Wrong time to eat"));
	input->t_sleep = ft_atoi(argv[4]);
	if (input->t_sleep < 1)
		return(error("Wrong time to sleep"));
	if (argc == 6)
	{
		input->nr_rounds = ft_atoi(argv[5]);
		if (input->nr_rounds < 0)
			return(error("Not enough rounds to eat"));
	}
	return (EXIT_OK);
}

int main (int argc, char **argv)
{
	t_data data;

	if (get_input(argc, argv, &data.info))
		return (EXIT_ERROR);

	init_data(&data);

	create_pthreads(&data);
	

	printf("%d, %d, %d, %d\n", data.info.nr_philo, data.info.t_die, data.info.t_eat, data.info.t_sleep);
	printf("%d, %d, %d, %d, %d\n", data.info.nr_philo, data.info.t_die, data.info.t_eat, data.info.t_sleep, data.info.nr_rounds);
	free_all(&data);
	return (EXIT_OK);
}
