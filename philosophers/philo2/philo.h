#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <limits.h>
#include <stdbool.h>

typedef pthread_mutex_t t_mtx;
typedef struct s_config t_config;

typedef struct s_philo
{
	int			id;
	long		last_meal;
	int			meals_consumed;
	pthread_t	thread;
	t_mtx		*left_fork;
	t_mtx		*right_fork;
	t_config	*config;
	bool		dead;
}	t_philo;

struct	s_config
{
	int				num_philos;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	int				num_meals;
	volatile int	sim_ended;
	volatile int	sim_started;
	t_mtx			*forks;
	t_mtx			print;
	struct timeval	start;
	long			start_time_ms;
	t_philo			*philo;
};
void	destroy_config(t_config *config, int num_mtx);
long	conv_time(struct timeval time);
int	lock_print(const char *s, t_philo *philo);
long	ft_atol(const char *nptr);
int check_input(int argc, char **argv);
int	populate_config(t_config *config, char **argv);
void	populate_philos(t_config *config);
int start_sim(t_config *config);

#endif