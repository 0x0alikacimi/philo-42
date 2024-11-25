/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkacimi <abkacimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:03:48 by abkacimi          #+#    #+#             */
/*   Updated: 2024/11/25 20:53:29 by abkacimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*the_routine(void *arg)
{
	t_philo_data	*ph;

	ph = (t_philo_data *)arg;
	pthread_mutex_lock(&ph->last_eat_mutex);
	ph->meals_eaten = 0;
	pthread_mutex_unlock(&ph->last_eat_mutex);
	if (ph->diningattr->n_phs == 1)
	{
		philo_status("has taken a fork\n", ph, ph->id + 1);
		special_sleep(ph->diningattr->t_die, ph->diningattr);
		printf("%lu %zu died\n", (the_time_is() - ph->diningattr->start_time),
			ph->id + 1);
		return (NULL);
	}
	if (ph->id % 2)
		usleep(100);
	while (1)
	{
		if (check_conditions(ph))
			break ;
		perform_actions(ph);
	}
	return (NULL);
}

int	handle_single_philo(t_gen_data *gen)
{
	pthread_t	thread;

	thread = ft_allocate(0, sizeof(pthread_t));
	if (!thread)
		return (ft_allocate(36, 0), 1);
	if (pthread_create(&thread, NULL, the_routine, &(gen->philos[0])) != 0)
		return (ft_allocate(36, 0), 1);
	pthread_join(thread, NULL);
	return (0);
}

int	create_philosopher_threads(t_gen_data *gen, pthread_t *threads)
{
	size_t	i;

	i = 0;
	while (i < gen->attr->n_phs)
	{
		if (pthread_create(&threads[i], NULL, the_routine,
				&(gen->philos[i])) != 0)
		{
			return (ft_allocate(36, 0), 1);
		}
		i++;
	}
	return (0);
}

void	join_threads(pthread_t *threads, size_t n_threads)
{
	size_t	i;

	i = 0;
	while (i < n_threads)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

int	the_dining(t_gen_data *gen)
{
	pthread_t	*threads;
	pthread_t	monitor_thread;

	if (gen->attr->n_phs == 1)
		return (handle_single_philo(gen));
	threads = ft_allocate(0, gen->attr->n_phs * sizeof(pthread_t));
	if (!threads)
		return (ft_allocate(36, 0), 1);
	if (pthread_create(&monitor_thread, NULL, monitor, gen) != 0)
		return (ft_allocate(36, 0), 1);
	if (create_philosopher_threads(gen, threads) != 0)
		return (1);
	pthread_join(monitor_thread, NULL);
	join_threads(threads, gen->attr->n_phs);
	return (0);
}
