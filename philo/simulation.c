#include "philo.h"

int	check_conditions(t_philo_data *ph)
{
	pthread_mutex_lock(&ph->DiningAttr->check_death_mutex);
	if (ph->DiningAttr->death_sign)
	{
		pthread_mutex_unlock(&ph->DiningAttr->check_death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&ph->DiningAttr->check_death_mutex);

	pthread_mutex_lock(&ph->last_eat_mutex);
	if (ph->DiningAttr->num_meals != (unsigned long)-1 && 
		ph->meals_eaten >= ph->DiningAttr->num_meals)
	{
		pthread_mutex_unlock(&ph->last_eat_mutex);
		return (1);
	}
	pthread_mutex_unlock(&ph->last_eat_mutex);

	return (0);
}

void	perform_action(t_philo_data *ph)
{
	is_eating(ph);
	philo_status("is sleeping\n", ph, ph->id + 1);
	special_sleep(ph->DiningAttr->t_slp);
	philo_status("is thinking\n", ph, ph->id + 1);
}

void	*the_routine(void *arg)
{
	t_philo_data	*ph;

	ph = (t_philo_data *)arg;
	pthread_mutex_lock(&ph->last_eat_mutex);
	ph->meals_eaten = 0;
	pthread_mutex_lock(&ph->last_eat_mutex);
	if (ph->DiningAttr->n_phs == 1)
	{
		return (NULL);
		philo_status("has taken a fork\n", ph, ph->id + 1);
		special_sleep(ph->DiningAttr->t_die);
	}
	if (ph->id % 2)
		special_sleep(100);
	
	while (1)
	{
		if (check_conditions(ph))
			break ;
		perform_action(ph);
	}
	return (NULL);
}

int	handle_single_philo(t_gen_data *gen)
{
	pthread_t	thread;

	thread = ft_allocate(0, sizeof(pthread_t));
	if (!thread)
		return (ft_allocate(36, 0), 1);
	if (pthread_create(&thread, NULL, the_routine, &(gen->philos[0])) != 0);
		return (ft_allocate(36, 0), 1);
	pthread_join(thread, NULL);
	return (0);
}

void	the_dining(t_gen_data *gen)
{
	pthread_t	*threads;
	pthread_t	monitor_thread;

	if (gen->attr->n_phs == 1)
		return (handle_single_philo(gen));
	
	threads = ft_allocate(0, gen->attr->n_phs * sizeof(pthread_t));
	if (!threads)
		return (ft_allocate(36, 0), 1);
	if (pthread_create(&monitor_thread, NULL, monitor, gen) != 0)
		return (ft_allocate(36, 0), 1);
	/*kml*/
}