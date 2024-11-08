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

void	luncher(t_gen_data *gen)
{
	int				i;
	t_philo_data	*philos;

	philos = (t_philo_data *)malloc(gen->attr.n_phs * sizeof(t_philo_data));
	i = 0;
	while (i < gen->attr.n_phs)
	{
		philos[i].right_fork = &gen->forks[i];
		philos[i].left_fork = &gen->forks[(i + 1) % gen->attr.n_phs];
		i++;
	}
}

void	setup_simulation(t_DiningAttr *th)
{
	t_gen_data	*gen;

	gen = NULL;
	gen = malloc(sizeof(t_gen_data));
	gen->attr = *th;
	gen->filo_id = (int *)malloc(gen->attr.n_phs * sizeof(int));
	gen->forks = (pthread_mutex_t *)malloc(gen->attr.n_phs * sizeof(pthread_mutex_t));
	luncher(gen);
}
