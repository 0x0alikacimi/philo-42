#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <pthread.h>

/* Holds general settings for the dining simulation */
typedef struct s_DiningAttr
{
	int		n_phs;			// Number of philosophers participating in the simulation
	int		t_die;			// Time (in ms) after which a philosopher dies if they do not eat
	int		t_eat;			// Time (in ms) it takes for a philosopher to complete eating
	int		t_slp;			// Time (in ms) a philosopher spends sleeping after eating
	int		num_meals;		// Number of times each philosopher must eat before the simulation ends
}		t_DiningAttr;

/* Stores shared resources and attributes for the simulation */
typedef struct	s_gen_data
{
	t_DiningAttr	attr;		// The overall dining attributes used by all philosophers
	int				*filo_id;		// Array of philosopher IDs, for unique identification of each philosopher thread
	pthread_mutex_t	*forks;			// Array of mutexes representing forks. Each fork is shared between two philosophers.
}	t_gen_data;

/* Represents individual philosopher's information and forks used during dining */
typedef struct s_philo_data
{
	pthread_mutex_t	*left_fork;			// Pointer to the left fork (mutex), shared with the philosopher on the left
	pthread_mutex_t	*right_fork;		// Pointer to the right fork (mutex), shared with the philosopher on the right
	t_DiningAttr	*DiningAttributes;	// Pointer to shared dining attributes, enabling access to the simulation’s settings
} t_philo_data;



void	ft_perror(char *str);
int		valid_n(const char *str);
int		ft_strlen(char *str);
int		check_all(int ac , char **av);
t_DiningAttr	*pars_it(int ac, char **av);
void	ft_start(t_DiningAttr *th);

#endif