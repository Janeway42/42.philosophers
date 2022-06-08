#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <pthread.h>
# include <stddef.h>
# include <sys/time.h>

#define OK 0
#define ERROR 1

#define TRUE 1
#define FALSE 0

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

enum msg
{
	msg_fork,
	msg_eat,
	msg_sleep,
	msg_think,
	msg_die
};

enum err
{
	err_philos,
	err_forks,
	err_neighbour,
	err_threads
};

// input units of time are in miliseconds 
// usleep works in mocroseconds
// 1 milisecond = 1000 microseconds

typedef struct	s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	int				last_eaten;
	int				times_eaten;
	pthread_mutex_t	*neighbour_lock;
	struct s_data	*data;
}				t_philo;

typedef struct	s_data
{
	int				nr_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				nr_rounds;
	struct timeval	start_time;
	pthread_t		*pthread_id;
	pthread_mutex_t	*forks_lock;
	pthread_mutex_t	*write_lock;
	t_philo			*philos;
}				t_data;



/*
** Init
** ---------------------------------
*/

int	init_data(t_data *data);
int	create_pthreads(t_data *data);
int	join_threads(t_data *data);

/*
** Routine
** ---------------------------------
*/

void	*routine(void *var);

/*
** Utils
** ---------------------------------
*/

int		ft_atoi(const char *nptr);
int		get_time(void);
void	write_message(t_philo *philo, enum msg message);
int		get_elapsed_time(t_philo *philo);

/*
** Outcome
** ---------------------------------
*/

int		philo_dead(t_philo *philo);

/*
** Free
** ---------------------------------
*/

void	free_all(t_data *data);


/*
** Error
** ---------------------------------
*/

int		error(char *str);
int		failed_sleep(t_philo *philo);
int		error_init_data(t_data *data, enum err error);
int		error_threads(t_data *data, int i);

#endif
