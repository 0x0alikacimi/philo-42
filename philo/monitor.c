#include "philo.h"

int	check_all_ate_enough(t_gen_data *gen)
{
	size_t	i;
	int		all_ate_enough;

	all_ate_enough = 1;
	i = 0;
	while (i < gen->attr->n_phs)
	{
		pthread_mutex_lock(&gen->philos[i].last_eat_mutex);
		if (gen->philos[i].meals_eaten < gen->attr->num_meals)
			all_ate_enough = 0;
		pthread_mutex_unlock(&gen->philos[i].last_eat_mutex);
		if (!all_ate_enough)
			break ;
		i++;
	}
	return (all_ate_enough);
}

int	check_philo_death(t_gen_data *gen, size_t i)
{
	unsigned long	curr_time;

	curr_time = the_time_is();
	pthread_mutex_lock(&gen->philos[i].last_eat_mutex);
	if (curr_time - gen->philos[i].last_eat >= gen->attr->t_die)
	{
		pthread_mutex_lock(&gen->attr->check_death_mutex);
		gen->attr->death_sign = 1;
		pthread_mutex_unlock(&gen->attr->check_death_mutex);
		printf("%lu %zu died\n", (the_time_is() - gen->attr->start_time),
			gen->philos[i].id);
		pthread_mutex_unlock(&gen->philos[i].last_eat_mutex);
		return (1);
	}
	pthread_mutex_unlock(&gen->philos[i].last_eat_mutex);
	return (0);
}

void	*monitor(void *arg)
{
	t_gen_data	*gen;
	size_t		i;

	gen = (t_gen_data *)arg;
	while (1)
	{
		i = 0;
		while (i < gen->attr->n_phs)
		{
			if (check_philo_death(gen, i))
				return (NULL);
			i++;
		}
		if (gen->attr->num_meals != (unsigned long)-1
			&& check_all_ate_enough(gen))
		{
			pthread_mutex_lock(&gen->attr->check_death_mutex);
			gen->attr->death_sign = 1;
			pthread_mutex_unlock(&gen->attr->check_death_mutex);
			return (NULL);
		}
		usleep(100);
	}
	return (NULL);
}
