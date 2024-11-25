/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkacimi <abkacimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:02:03 by abkacimi          #+#    #+#             */
/*   Updated: 2024/11/25 12:20:33 by abkacimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init(t_diningattr *th)
{
	th->n_phs = -1;
	th->t_die = -1;
	th->t_eat = -1;
	th->t_slp = -1;
	th->num_meals = -1;
}

int	pars_it(int ac, char **av, t_diningattr *th)
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
	if (!(th->n_phs >= 1 && th->n_phs <= 200))
		return (ft_perror("philos number should be  between 200 and 1\n"), 1);
	if (ac == 6 && th->num_meals == 0)
		return (ft_perror("no meals huh!!??\n"), 1);
	return (0);
}

int	main(int ac, char **av)
{
	t_diningattr	attr;
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
	cleanup_simulation(&gen);
}
