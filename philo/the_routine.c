#include "philo.h"

void	*the_routine(void *arg);
void	take_the_forks(t_philo_data *ph);
void	make_him_sleep(t_philo_data *ph);
void	make_him_think(t_philo_data *ph);

/* pthread_mutex_lock && pthread_mutex_unlock */
void	take_the_forks(t_philo_data *ph)
{
	_Atomic unsigned long	time;

	time = 0;
	pthread_mutex_lock(ph->right_fork);
	printf("%lu %zu has taken a fork\n", get_time(&time), ph->id);
	pthread_mutex_lock(ph->left_fork);
	printf("%lu %zu has taken a fork\n", get_time(&time), ph->id);
	printf("%lu %zu is eating\n", get_time(&time), ph->id);
	ph->last_eat = (unsigned long *)(time);
	usleep(ph->DiningAttributes->t_eat * 1000);
	(pthread_mutex_unlock(ph->right_fork), pthread_mutex_unlock(ph->left_fork));
}

void	make_him_sleep(t_philo_data *ph)
{
	_Atomic unsigned long	time;
	
	time = 0;
	printf("%lu %zu is sleeping\n", get_time(&time), ph->id);
	usleep(ph->DiningAttributes->t_slp * 1000);
}

void	make_him_think(t_philo_data *ph)
{
	_Atomic unsigned long	time;

	time = 0;
	printf("%lu %zu is thinking \n", get_time(&time), ph->id);
}

void	*the_routine(void *arg)
{
	t_philo_data	*ph;

	ph = (t_philo_data *)arg;
	if (ph->id % 2)
		usleep(50);
	while(1)
		(take_the_forks(ph), make_him_sleep(ph), make_him_think(ph));
	return (NULL);
}