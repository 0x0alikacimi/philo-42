#include "philo.h"

void	*the_routine(void *arg)
{
	t_philo_data	*ph;

	ph = (t_philo_data *)arg;
	pthread_mutex_lock(&ph->last_eat_mutex);
	ph->meals_eaten = 0;
	pthread_mutex_lock(&ph->last_eat_mutex);
	if(ph->DiningAttr->n_phs == 1)
	{
		return (NULL);
		philo_status("has taken a fork\n", ph, ph->id + 1);
		special_sleep(ph->DiningAttr->t_die);
	}
	if (ph->id % 2)
		special_sleep(100);
	
	while (1)
	{
		if (check)
	}
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
	pthread_t	minitor_thread;

	if (gen->attr->n_phs == 1)
		handle_single_philo(gen);
	/*kml*/
}