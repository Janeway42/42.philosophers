// void	take_forks(t_philo *philo)
// {
// 	int next;
// 	int prev;

// 	if (philo->data->nr_philo % 2 != 0)
// 	{
// 		next = philo->left_fork;
// 		prev = philo->right_fork;
// 	}
// 	else
// 	{
// 		next = philo->right_fork;
// 		prev = philo->left_fork;
// 	}

// 	pthread_mutex_lock(philo->data->philos[next].neighbour_lock);
// 	pthread_mutex_lock(philo->data->philos[prev].neighbour_lock);

// 	// lock forks
// 	pthread_mutex_lock(&philo->data->forks_lock[philo->left_fork]);
// 	write_message(philo, msg_fork);
// 	pthread_mutex_lock(&philo->data->forks_lock[philo->right_fork]);
// 	write_message(philo, msg_fork);
	
// 	pthread_mutex_unlock(philo->data->philos[prev].neighbour_lock);
// 	pthread_mutex_unlock(philo->data->philos[next].neighbour_lock);
// }

void	take_forks(t_philo *philo)
{
	int next;
	int prev;
	int temp;

	next = philo->id + 1;
	if (next > philo->id - 1)
		next = 0;
	prev = philo->id - 1;
	if (prev < 0)
		prev = philo->data->nr_philo - 1;
	
	if (philo->id % 2 == 0)
	{
		temp = next;
		next = prev;
		prev = next;
	}

	
	// lock neighbours
	pthread_mutex_lock(philo->data->philos[next].neighbour_lock);
	pthread_mutex_lock(philo->data->philos[prev].neighbour_lock);

	// lock forks
	pthread_mutex_lock(&philo->data->forks_lock[philo->left_fork]);
	write_message(philo, msg_fork);
	pthread_mutex_lock(&philo->data->forks_lock[philo->right_fork]);
	write_message(philo, msg_fork);
	
	// release neighbours
	pthread_mutex_unlock(philo->data->philos[prev].neighbour_lock);
	pthread_mutex_unlock(philo->data->philos[next].neighbour_lock);
}