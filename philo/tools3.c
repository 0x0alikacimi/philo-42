#include "philo.h"

void	is_eating(t_philo_data *ph)
{
	pthread_mutex_lock(ph->right_fork);
	philo_status("has taken a fork\n", ph, ph->id + 1);
	pthread_mutex_lock(ph->left_fork);
	philo_status("has taken a fork\n", ph, ph->id + 1);
	pthread_mutex_lock(&ph->last_eat_mutex);
	ph->last_eat = the_time_is();
	ph->meals_eaten++;
	pthread_mutex_unlock(&ph->last_eat_mutex);
	philo_status("is eating\n", ph, ph->id + 1);
	special_sleep(ph->DiningAttr->t_eat);
	pthread_mutex_unlock(ph->left_fork);
	pthread_mutex_unlock(ph->right_fork);
}
