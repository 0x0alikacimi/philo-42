#include "philo.h"

int	check_all(int ac , char **av)
{
	int	n;
	
	n = 1;
	while (n < ac)
	{
		if (valid_n(av[n]) == -13)
			return (-13);
		n++;
	}
	return (0);
}

int main (int ac, char **av)
{
	t_DiningAttr	*th;
	if (ac < 5 || ac > 6)
	{
		ft_perror("Invalid number of args");
		return(1);
	}
	if (check_all(ac , av) == -13)
		return (1);
	th = pars_it(ac, av);
	ft_start(th);
	return (0);
}