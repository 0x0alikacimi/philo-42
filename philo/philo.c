#include "philo.h"

void	prepare_dining(t_gen_data *gen);
void	luncher(t_gen_data *gen);
void	setup_simulation(t_DiningAttr *th);


void	prepare_dining(t_gen_data *gen)
{
	size_t				i;
	t_philo_data	*philos;

	philos = (t_philo_data *)ft_allocate(0, gen->attr->n_phs * sizeof(t_philo_data));
	i = 0;
	while (i < gen->attr->n_phs)
	{
		philos[i].right_fork = &(gen->forks[i]);
		philos[i].left_fork = &(gen->forks[(i + 1) % gen->attr->n_phs]);
		philos[i].DiningAttributes = gen->attr;
		philos[i].id = i;
		i++;
	}
	gen->philos = philos;
}
/* segmentation fault */
// void	*monitoring_routine(void *arg)
// {
// 	t_gen_data				*gen;
// 	_Atomic unsigned long	curr_t;
// 	unsigned long				i;

// 	gen = (t_gen_data *)arg;
// 	i = 0;
// 	while (1)
// 	{
// 		while (i < gen->attr->n_phs)
// 		{
// 			if (gen->attr->t_die <= (get_time(&curr_t) - *(gen->philos[i].last_eat)))
// 			{
// 				printf("%lu %zu has died\n", curr_t, gen->philos[i].id);
// 				return (NULL);
// 			}
// 			i++;
// 		}
// 		usleep(1000);
// 	}
// 	return (NULL);
// }

void	luncher(t_gen_data *gen)
{
	pthread_t	*thrds;
	// pthread_t	lbrgag;
	size_t		i;

	thrds = (pthread_t *)ft_allocate(0, gen->attr->n_phs);
	if (!thrds)
	{
		ft_allocate(36, 0);
		return;
	}
	i = 0;
	while (i < gen->attr->n_phs)
	{
		/*Start a thread for each philosopher, passing a pointer to their t_philo_data */
		if (pthread_create(&thrds[i], NULL, the_routine, (void *) &(gen->philos[i])) != 0)
		{
			ft_perror("pthread_create failed \n");
			ft_allocate(36, 0);
			return ;
		}
		i++;
	}
	// if (pthread_create(&lbrgag, NULL, monitoring_routine, (void *)gen) != 0)
	// {
	// 	ft_perror("pthread_create failed \n");
	// 	ft_allocate(36, 0);
	// 	return ;
	// }
	// pthread_join(lbrgag, NULL);
	i = 0;
	while (i < gen->attr->n_phs)
	{
		pthread_join(thrds[i], NULL);
		i++;
	}
}

void	setup_simulation(t_DiningAttr *th)
{
	t_gen_data	*gen;

	gen = NULL;
	gen = ft_allocate(0, sizeof(t_gen_data)); // protect
	gen->attr = th;
	gen->filo_id = (int *)ft_allocate(0, gen->attr->n_phs * sizeof(int));
	gen->forks = (pthread_mutex_t *)ft_allocate(0, gen->attr->n_phs * sizeof(pthread_mutex_t));

	// just printing addresses to check if it works or not later  
	for (size_t i = 0; i < gen->attr->n_phs; i++)
	{
		pthread_mutex_init(&gen->forks[i], NULL);
	}
	prepare_dining(gen);
	luncher(gen);
}
