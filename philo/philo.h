#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <pthread.h>
#include <sys/time.h>

/* Holds general settings for the dining simulation */
typedef struct s_DiningAttr
{
	unsigned long	n_phs;			// Number of philosophers participating in the simulation
	unsigned long	t_die;			// Time (in ms) after which a philosopher dies if they do not eat
	unsigned long	t_eat;			// Time (in ms) it takes for a philosopher to complete eating
	unsigned long	t_slp;			// Time (in ms) a philosopher spends sleeping after eating
	unsigned long	num_meals;		// Number of times each philosopher must eat before the simulation ends
}		t_DiningAttr;

/* Represents individual philosopher's information and forks used during dining */
typedef struct s_philo_data
{
	size_t			id;
	pthread_mutex_t	*left_fork;			// Pointer to the left fork (mutex), shared with the philosopher on the left
	pthread_mutex_t	*right_fork;		// Pointer to the right fork (mutex), shared with the philosopher on the right
	t_DiningAttr	*DiningAttributes;	// Pointer to shared dining attributes, enabling access to the simulation’s settings
	unsigned long	*last_eat;
} t_philo_data;

/* Stores shared resources and attributes for the simulation */
typedef struct	s_gen_data
{
	t_DiningAttr	*attr;			// The overall dining attributes used by all philosophers
	int				*filo_id;		// Array of philosopher IDs, for unique identification of each philosopher thread
	pthread_mutex_t	*forks;			// Array of mutexes representing forks. Each fork is shared between two philosophers.
	t_philo_data	*philos;
}	t_gen_data;

typedef struct s_gc_e
{
	void			*ptr;
	struct s_gc_e	*next;
}					t_gc_e;

void			ft_perror(char *str);
int				valid_n(char *str, unsigned long *nb);
int				pars_it(int ac, char **av, t_DiningAttr *th);
void			setup_simulation(t_DiningAttr *th);

void			*the_routine(void *arg);
void			take_the_forks(t_philo_data *ph);
void			make_him_sleep(t_philo_data *ph);
void			make_him_think(t_philo_data *ph);
unsigned long	get_time(_Atomic unsigned long *nb);

void			*ft_allocate(int flag, int size);

#endif