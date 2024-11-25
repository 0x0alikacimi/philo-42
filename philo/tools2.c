/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkacimi <abkacimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:03:56 by abkacimi          #+#    #+#             */
/*   Updated: 2024/11/25 20:52:31 by abkacimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	the_time_is(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	special_sleep(unsigned long t, t_diningattr *attr)
{
	unsigned long	st;

	st = the_time_is();
	while (the_time_is() - st < t)
	{
		pthread_mutex_lock(&attr->check_end_mutex);
		if (attr->end_sign)
		{
			pthread_mutex_unlock(&attr->check_end_mutex);
			return ;
		}
		pthread_mutex_unlock(&attr->check_end_mutex);
		usleep(500);
	}
}

void	philo_status(char *msg, t_philo_data *ph, size_t id)
{
	pthread_mutex_lock(&ph->diningattr->print);
	pthread_mutex_lock(&ph->diningattr->check_end_mutex);
	if (!ph->diningattr->end_sign)
		printf ("%lu %zu %s", (the_time_is() - ph->diningattr->start_time),
			id, msg);
	pthread_mutex_unlock(&ph->diningattr->check_end_mutex);
	pthread_mutex_unlock(&ph->diningattr->print);
}

int	setup_simulation(t_diningattr *attr, t_gen_data *gen)
{
	size_t	i;

	gen->attr = attr;
	gen->forks = ft_allocate(0, gen->attr->n_phs * sizeof(pthread_mutex_t));
	if (!gen->forks)
		return (ft_allocate(36, 0), 1);
	gen->attr->start_time = the_time_is();
	i = 0;
	while (i < gen->attr->n_phs)
	{
		pthread_mutex_init(&gen->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&gen->attr->check_end_mutex, NULL);
	pthread_mutex_init(&gen->attr->print, NULL);
	pthread_mutex_init(&gen->attr->eat_mutex, NULL);
	return (0);
}

int	setup_philos(t_gen_data *gen)
{
	t_philo_data	*philos;
	size_t			i;

	philos = ft_allocate(0, gen->attr->n_phs * sizeof(t_philo_data));
	if (!philos)
		return (ft_allocate(36, 0), 1);
	i = 0;
	while (i < gen->attr->n_phs)
	{
		pthread_mutex_init(&philos[i].last_eat_mutex, NULL);
		philos[i].right_fork = &(gen->forks[i]);
		philos[i].left_fork = &(gen->forks[(i + 1) % gen->attr->n_phs]);
		philos[i].id = i;
		philos[i].last_eat = the_time_is();
		pthread_mutex_lock(&philos[i].last_eat_mutex);
		philos[i].meals_eaten = 0;
		pthread_mutex_unlock(&philos[i].last_eat_mutex);
		philos[i].diningattr = gen->attr;
		gen->attr->end_sign = 0;
		i++;
	}
	gen->philos = philos;
	return (0);
}
