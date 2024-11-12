#include "philo.h"

void	ft_init(t_DiningAttr *th)
{
	th->n_phs = -1;
	th->t_die = -1;
	th->t_eat = -1;
	th->t_slp = -1;
	th->num_meals = -1;
}

int	pars_it(int ac, char **av, t_DiningAttr *th)
{
	int	i;

	ft_init(th);
	i = 1;
	if ((valid_n(av[1], &th->n_phs) == 1)
		|| (valid_n(av[2], &th->t_die) == 1)
		|| (valid_n(av[3], &th->t_eat) == 1)
		|| (valid_n(av[4], &th->t_slp) == 1))
	{
		return (1);
	}
	if (ac == 6 && (valid_n(av[5], &th->num_meals) == 1))
		return (1);
	return (0);
}