#include "philo.h"

int	somthing_wrong(t_DiningAttr *th)
{
	if (th->num_meals == 0)
	{
		puts("no meals huh!?");
		return (1);
	}
	return (0);
}

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

void	take_the_forks(t_philo_data *ph)
{
	/* pthread_mutex_lock && pthread_mutex_unlock */
	pthread_mutex_lock(ph->right_fork);
	printf("%zu has taken a fork\n", ph->id);
	pthread_mutex_lock(ph->left_fork);
	printf("%zu has taken a fork\n", ph->id);
	printf("%zu is eating\n", ph->id);
	usleep(ph->DiningAttributes->t_eat * 1000);
	pthread_mutex_unlock(ph->right_fork);
	pthread_mutex_unlock(ph->left_fork);
}

void	make_him_sleep(t_philo_data *ph)
{
	printf("%zu is sleeping\n", ph->id);
	usleep(ph->DiningAttributes->t_slp * 1000);
}

void	make_him_think(t_philo_data *ph)
{
	printf("%zu is thinking \n", ph->id);
}

void	*the_routine(void *arg)
{
	t_philo_data *ph;

	ph = (t_philo_data *)arg;

	if (ph->id % 2)
		usleep(50);

	while(1)
	{
		take_the_forks(ph);
		make_him_sleep(ph);
		make_him_think(ph);
	}
	return (NULL);
}

void	luncher(t_gen_data *gen)
{
	pthread_t	*thrds;
	size_t		i;

	thrds = (pthread_t *)ft_allocate(0, gen->attr->n_phs);
	if (!thrds)
	{
		ft_allocate(36, 0);
		return;
	}
	i = 0;
	while(i < gen->attr->n_phs)
	{
		/*Start a thread for each philosopher, passing a pointer to their t_philo_data */
		if (pthread_create(&thrds[i], NULL, the_routine, (void *) &(gen->philos[i])) == -1)
		{
			ft_perror("pthread_create failed \n");
			ft_allocate(36, 0);
			return ;
		}
		i++;
	}
	/*join them*/
	for (size_t i = 0; i < gen->attr->n_phs; i++)
	{
		pthread_join(thrds[i], NULL);
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
		// printf ("fork : %zu : %p\n", i, &gen->forks[i]);
	}

	prepare_dining(gen);
	// size_t i = 0;
	// checks the addresses if the function prepare_dining did it job correctly 
	// while(i < th->n_phs)
	// {
	// 	printf("philo %zu {right fork : %p | left fork : %p}\n", i, gen->philos[i].right_fork, gen->philos[i].left_fork);
	// 	i++;
	// }
	luncher(gen);
}
