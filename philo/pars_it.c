#include "philo.h"

void	ft_init(t_DiningAttr *th)
{
	th->n_phs = -1;
	th->t_die = -1;
	th->t_eat = -1;
	th->t_slp = -1;
	th->num_meals = -1;
}

t_DiningAttr	*pars_it(int ac, char **av)
{
	t_DiningAttr	*th;
	th = malloc(sizeof(t_DiningAttr));
	ft_init(th);

	th->n_phs = valid_n(av[1]);
	th->t_die = valid_n(av[2]);
	th->t_eat = valid_n(av[3]);
	th->t_slp = valid_n(av[4]);
	if (ac == 6)
	{
		th->num_meals = valid_n(av[5]);
	}
	return (th);
}