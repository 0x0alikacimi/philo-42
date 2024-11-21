#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <pthread.h>
#include <sys/time.h>

/* Holds general settings for the dining simulation */
typedef struct s_DiningAttr
{
	unsigned long	n_phs;
	unsigned long	t_die;
	unsigned long	t_eat;
	unsigned long	t_slp;
	unsigned long	num_meals;
	int				death_sign;
	pthread_mutex_t	check_death_mutex;
	pthread_mutex_t	print;
	pthread_mutex_t	eat_mutex;
	unsigned long	start_time;
}		t_DiningAttr;

/* Represents individual philosopher's information and forks used during dining */
typedef struct s_philo_data
{
	size_t			id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_DiningAttr	*DiningAttr;
	unsigned long	last_eat;
	pthread_mutex_t	last_eat_mutex;
	unsigned long		meals_eaten;
} t_philo_data;

/* Stores shared resources and attributes for the simulation */
typedef struct	s_gen_data
{
	t_DiningAttr	*attr;
	pthread_mutex_t	*forks;
	t_philo_data	*philos;
}	t_gen_data;

typedef struct s_gc_e
{
	void			*ptr;
	struct s_gc_e	*next;
}					t_gc_e;


/********************************/

void			ft_perror(char *str);
int				valid_n(char *str, unsigned long *nb);

/********************************/

int				setup_simulation(t_DiningAttr *attr, t_gen_data *gen);
int				setup_philos(t_gen_data *gen);
void			philo_status(char *msg, t_philo_data *ph, size_t id);
void			special_sleep(unsigned long t);
unsigned long	the_time_is();
void			is_eating(t_philo_data *ph);

/********************************/

void			*ft_allocate(int flag, int size);

/********************************/

#endif