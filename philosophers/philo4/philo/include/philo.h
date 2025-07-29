#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <string.h>

typedef struct s_data
{
	int				nb_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				must_eat_count;		// optional, -1 if not used

	int				someone_died;
	
	long			start_time;
	pthread_mutex_t	*forks;				// array of mutexes
	pthread_mutex_t	print_lock;
	pthread_mutex_t	death_lock;

	struct s_philo	*philos;			// array of philosophers
}	t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal_time;

	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal_lock;

	t_data			*data;
}	t_philo;

// init.c
int	init_data(t_data *data, int argc, char **argv);
int	init_philosophers(t_data *data);

// utils.c
long	get_time(void);
void	print_status(t_philo *philo, char *msg);
int	check_if_someone_died(t_data *data);

void	custom_usleep(long ms, t_data *data);

// routine.c
void *routine(void *arg);

// monitor.c
void	monitor_philosophers(t_data *data);

#endif