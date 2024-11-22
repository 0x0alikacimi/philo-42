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
	special_sleep(ph->diningattr->t_eat);
	pthread_mutex_unlock(ph->left_fork);
	pthread_mutex_unlock(ph->right_fork);
}

void	perform_actions(t_philo_data *ph)
{
	is_eating(ph);
	philo_status("is sleeping\n", ph, ph->id + 1);
	special_sleep(ph->diningattr->t_slp);
	philo_status("is thinking\n", ph, ph->id + 1);
}

int	check_conditions(t_philo_data *ph)
{
	pthread_mutex_lock(&ph->diningattr->check_death_mutex);
	if (ph->diningattr->death_sign)
	{
		pthread_mutex_unlock(&ph->diningattr->check_death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&ph->diningattr->check_death_mutex);
	pthread_mutex_lock(&ph->last_eat_mutex);
	if (ph->diningattr->num_meals != (unsigned long)-1 && 
		ph->meals_eaten >= ph->diningattr->num_meals)
	{
		pthread_mutex_unlock(&ph->last_eat_mutex);
		return (1);
	}
	pthread_mutex_unlock(&ph->last_eat_mutex);
	return (0);
}
