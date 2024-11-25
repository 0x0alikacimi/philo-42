/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkacimi <abkacimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:04:00 by abkacimi          #+#    #+#             */
/*   Updated: 2024/11/25 14:54:46 by abkacimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	is_eating(t_philo_data *ph)
{
	pthread_mutex_lock(ph->right_fork);
	philo_status("has taken a fork\n", ph, ph->id + 1);
	pthread_mutex_lock(ph->left_fork);
	philo_status("has taken a fork\n", ph, ph->id + 1);
	pthread_mutex_lock(&ph->last_eat_mutex);
	ph->last_eat = the_time_is();
	ph->meals_eaten++;
	pthread_mutex_unlock(&ph->last_eat_mutex);
	philo_status("is eating\n", ph, ph->id + 1);
	special_sleep(ph->diningattr->t_eat);
	pthread_mutex_unlock(ph->left_fork);
	pthread_mutex_unlock(ph->right_fork);
}

void	perform_actions(t_philo_data *ph)
{
	is_eating(ph);
	philo_status("is sleeping\n", ph, ph->id + 1);
	special_sleep(ph->diningattr->t_slp);
	philo_status("is thinking\n", ph, ph->id + 1);
}

int	check_conditions(t_philo_data *ph)
{
	pthread_mutex_lock(&ph->diningattr->check_end_mutex);
	if (ph->diningattr->end_sign)
	{
		pthread_mutex_unlock(&ph->diningattr->check_end_mutex);
		return (1);
	}
	pthread_mutex_unlock(&ph->diningattr->check_end_mutex);
	pthread_mutex_lock(&ph->last_eat_mutex);
	if (ph->diningattr->num_meals != (unsigned long)-1
		&& ph->meals_eaten >= ph->diningattr->num_meals)
	{
		pthread_mutex_unlock(&ph->last_eat_mutex);
		return (1);
	}
	pthread_mutex_unlock(&ph->last_eat_mutex);
	return (0);
}

void	cleanup_simulation(t_gen_data *gen)
{
	size_t	i;

	i = 0;
	while (i < gen->attr->n_phs)
	{
		pthread_mutex_destroy(&gen->forks[i]);
		pthread_mutex_destroy(&gen->philos[i].last_eat_mutex);
		i++;
	}
	pthread_mutex_destroy(&gen->attr->check_end_mutex);
	pthread_mutex_destroy(&gen->attr->print);
	pthread_mutex_destroy(&gen->attr->eat_mutex);
	ft_allocate(36, 0);
}
