#include "philo.h"
int	chexk_philo_death(t_gen_data *gen, size_t i)
{
	unsigned long	curr_time;

	curr_time = the_time_is();
	pthread_
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
			if 
			i++;
		}
	}
}