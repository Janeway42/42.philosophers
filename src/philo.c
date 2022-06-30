/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/06/25 17:49:25 by janeway       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_input(char *input, int *str)
{
	int		nr;
	size_t	lenght;
	char	*test;

	nr = ft_atoi(input);
	test = ft_itoa(nr);
	lenght = ft_strlen(input);
	if (ft_strncmp(input, test, lenght) != 0)
	{
		free(test);
		return (ERROR);
	}
	*str = nr;
	free(test);
	return (0);
}

static int	get_input(int argc, char **argv, t_data *data)
{
	if (argc < 5 || argc > 6)
		return (error("wrong number of arguments\n"));
	if (check_input(argv[1], &data->nr_philo) != 0)
		return (error("odd party of philosophers there...\n"));
	if (check_input(argv[2], &data->t_die) != 0)
		return (error("might want to check that time to die...\n"));
	if (check_input(argv[3], &data->t_eat) != 0)
		return (error("must eat brains! lunch time is off!\n"));
	if (check_input(argv[4], &data->t_sleep) != 0)
		return (error("put your glasses on and let me sleep!\n"));
	data->nr_rounds = -1;
	if (argc == 6)
	{
		if (check_input(argv[5], &data->nr_rounds) != 0)
			return (error("don't be skimpy! let us eat more times!\n"));
	}
	if (data->nr_philo < 1 || data->t_die < 0 || data->t_eat < 0
		|| data->t_sleep < 0 || (argc == 6 && data->nr_rounds < 1))
		return (error("input required:\nat least 1 philo, time to die, \
			eat and sleep of at least 0\nand if mentioned at least \
			1 round of eating\n"));
	return (OK);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (get_input(argc, argv, &data) == ERROR)
		return (ERROR);
	if (init_data(&data) == ERROR)
		return (ERROR);
	if (create_pthreads(&data) == ERROR)
		return (ERROR);
	join_threads(&data);
	clean_up(&data);
	return (OK);
}
