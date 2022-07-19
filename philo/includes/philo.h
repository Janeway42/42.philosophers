/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: janeway <janeway@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/26 12:01:51 by janeway       #+#    #+#                 */
/*   Updated: 2022/07/19 13:35:46 by janeway       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <pthread.h>
# include <stddef.h>
# include <sys/time.h>

# define OK 0
# define ERROR 1

# define ACTIVE 1
# define INNACTIVE 0

# define INPUT "input required: nr philo > 0, time to die > -1,\
time to eat > -1, time to sleep > -1, nr times to \
eat (optional) > 0\n"

/*
**	typedef struct t_data:
** ---------------------------------
**	nr_philo		the number of philosophers and also the number of forks 
**	t_die		(in miliseconds) if a philosopher didn't start eating
**				t_die miliseconds since the begining of their last meal
**				or the begining of the simulation they die
**	t_eat		(in miliseconds) the time ot takes for a philosopher to eat
**				during that time they will need to hold two forks
**	t_sleep		(in miliseconds) the time a philosopher will spend sleeping
**	nr_rounds	(optional argument) if all the philosophers hasve eaten at leat
**				nr_rounds times, the simulation stops. If not specified,
**				the simulation stops when a philosopher dies.
*/

enum e_msg
{
	msg_fork,
	msg_eat,
	msg_sleep,
	msg_think,
	msg_die,
};

/*
** input units of time are in miliseconds 
** usleep works in mocroseconds
** 1 milisecond = 1000 microseconds
*/

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	int				last_eaten;
	int				times_eaten;
	pthread_mutex_t	meal_lock;
	int				status;
	struct s_data	*data;
}				t_philo;

typedef struct s_data
{
	int				nr_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				nr_rounds;
	struct timeval	start_time;
	pthread_t		*pthread_id;
	pthread_mutex_t	*forks_lock;
	pthread_mutex_t	write_lock;
	int				dead_philo;
	pthread_t		surveilance;
	pthread_mutex_t	dead_lock;
	t_philo			*philos;
}				t_data;

/*
** Initialize
** ---------------------------------
*/

int				initialize_data(t_data *data);
int				create_pthreads(t_data *data);
int				join_threads(t_data *data);

/*
** Routine
** ---------------------------------
*/

void			*routine(void *var);
int				philo_eat(t_philo *philo);
void			philo_sleep(t_philo *philo);
void			philo_think(t_philo *philo);

/*
** Basics
** ---------------------------------
*/

int				ft_atoi(const char *nptr);
char			*ft_itoa(int n);
size_t			ft_strlen(const char *str);
int				ft_strncmp(const char *s1, const char *s2, size_t n);

/*
** Utils
** ---------------------------------
*/

void			write_message(t_philo *philo, enum e_msg message);
unsigned long	get_time(void);
unsigned long	get_elapsed_time(t_philo *philo);
// void			better_sleep(int sleep_time);
void			better_sleep(t_data *data, int sleep_time);

/*
** Surveillance
** ---------------------------------
*/

int				surveilance(t_data *data);
int				still_alive(t_data *data);
void			*dead_philo(void *arg);

/*
** Free
** ---------------------------------
*/

void			destroy_mutexes(t_data *data);
void			free_memory(t_data *data);
void			clean_up(t_data *data);

/*
** Error
** ---------------------------------
*/

int				error(char *str);
int				error_memory(t_data *data, char *str);
int				error_mutex(t_data *data, char *str);
int				error_threads(t_data *data, int count, char *str);

#endif
