/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/06/17 22:05:29 by janeway       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int	check_input(t_data *data, char *str)
// {
// 	int	nr;
// 	int	i;

// 	nr = ft_atoi(str);
// 	if (nr < 1)
// 		return (ERROR);
// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		if (ft_isdigit((int)str[i]) == 0)
// 			return (ERROR);
// 		i++;
// 	}
// 	return (nr);
// }

int	get_input(int argc, char **argv, t_data *data)
{
	if (argc < 5 || argc > 6)
		return (error("wrong number of arguments\n"));
//	data->nr_philo = check_input(data, argv[1]); //ft_atoi(argv[1]);
	data->nr_philo = ft_atoi(argv[1]);
	if (data->nr_philo < 1)
		return (error("odd party of philosophers there...\n"));
	data->t_die = ft_atoi(argv[2]);
	if (data->t_die < 1)
		return (error("might want to check that time to die...\n"));
	data->t_eat = ft_atoi(argv[3]);
	if (data->t_eat < 1)
		return(error("must eat brains! lunch time is off!\n"));
	data->t_sleep = ft_atoi(argv[4]);
	if (data->t_sleep < 1)
		return(error("put your glasses on and let me sleep!\n"));
	if (argc == 6)
	{
		data->nr_rounds = ft_atoi(argv[5]);
		if (data->nr_rounds < 1)
			return(error("don't be skimpy! let us eat more times!\n"));
	}
	return (OK);
}

int main (int argc, char **argv)
{
	t_data data;

	if (get_input(argc, argv, &data) == ERROR)
		return (ERROR);
	if (init_data(&data) == ERROR)
		return (ERROR);
	if (create_pthreads(&data) == ERROR)
		return (ERROR);
	join_threads(&data);

	// printf("%d, %d, %d, %d\n", data.nr_philo, data.t_die, data.t_eat, data.t_sleep);
	// printf("%d, %d, %d, %d, %d\n", data.nr_philo, data.t_die, data.t_eat, data.t_sleep, data.nr_rounds);
	free_all(&data);
	return (OK);
}
