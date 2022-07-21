/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: janeway <janeway@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/26 12:01:51 by janeway       #+#    #+#                 */
/*   Updated: 2022/07/21 20:42:02 by janeway       ########   odam.nl         */
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
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>

# define OK 0
# define ERROR 1

# define ACTIVE 1
# define INNACTIVE 0

# define DEAD 5
# define FULL 7

# define FORKS "FORKS"
# define WRITE "WRITE"

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
	int				last_eaten;
	int				times_eaten;
	sem_t			*s_dead;
	char			*name_dead;
	sem_t			*s_last_meal;
	char			*name_last_meal;
	int				status;
	sem_t			*s_status;
	char			*name_status;
	pthread_t		*thread;
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
	pid_t			*process_id;
	sem_t			*s_forks;
	sem_t			*s_write;
	t_philo			*philos;
}				t_data;

/*
** Init
** ---------------------------------
*/

int				initialize_data(t_data *data);
sem_t			*open_semaphore(sem_t **address, char *name, int size);

/*
** Create Processes
** ---------------------------------
*/

int				create_processes(t_data *data);

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
char			*ft_strdup(const char *s);
int				ft_strncmp(const char *s1, const char *s2, size_t n);

/*
** Utils
** ---------------------------------
*/

unsigned long	get_time(void);
unsigned long	get_elapsed_time(t_philo *philo);
void			better_sleep(int sleep_time);
void			write_message(t_philo *philo, enum e_msg message);

/*
** Surveillance
** ---------------------------------
*/

int				surveillance(t_data *data);
int				kill_processes(t_data *data);

/*
** Free
** ---------------------------------
*/

void			free_memory(t_data *data);
void			clean_up_process(t_philo *philo);
void			close_semaphore(sem_t *sem, char *name);
void			clean_up(t_data *data);

/*
** Error
** ---------------------------------
*/

int				error(char *str);
int				error_memory(t_data *data, char *str);
int				error_semaphore(char *str, t_data *data);
int				error_exit(char *str);
int				general_error(t_data *data, char *str);

#endif
