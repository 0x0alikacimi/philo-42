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

int main (int ac , char **av)
{
	t_DiningAttr	attr;
	t_gen_data		gen;

	if (ac < 5 || ac > 6)
	{
		ft_perror("Invalid number of args");
		return (1);
	}
	if (pars_it(ac, av, &attr) == 1)
		return (ft_allocate(36, 0), 1);
	if (setup_simulation(&attr, &gen) != 0)
		return (1);
	if (setup_philos(&gen) != 0)
		return (1);
	the_dining(&gen);
}