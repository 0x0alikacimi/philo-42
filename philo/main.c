#include "philo.h"

int main (int ac, char **av)
{
	t_DiningAttr	th;
	if (ac < 5 || ac > 6)
	{
		ft_perror("Invalid number of args");
		return(1);
	}
	if (pars_it(ac, av, &th) == 1)
		return (ft_allocate(36, 0), 1);
	setup_simulation(&th);
	return (0);
}