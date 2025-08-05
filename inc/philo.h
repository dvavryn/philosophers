/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 23:33:06 by dvavryn           #+#    #+#             */
/*   Updated: 2025/08/05 19:45:54 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>
# include <string.h>

typedef struct s_mtx
{
	int				valid;
	pthread_mutex_t	mtx;
}	t_mtx;

typedef struct s_data
{
	struct s_philo	*philos;
	t_mtx			*forks;

	t_mtx			mtx_print;
	t_mtx			mtx_death;

	pthread_t		monitor;

	int				num_philos;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	int				num_meals;

	int				death_flag;
	long			start;
}	t_data;

typedef struct s_philo
{
	t_data		*data;
	pthread_t	thread;
	t_mtx		*fork_one;
	t_mtx		*fork_two;
	t_mtx		mtx_meal;
	long		last_meal;
	int			meals_eaten;
	int			full;
	int			id;
}	t_philo;

// check.c
int		check(int argc, char **argv);

// utils.c
long	ft_atol(const char *nptr);
void	*ft_calloc(size_t nmemb, size_t size);
int		get_time_ms(long *time);
void	safe_print(t_philo *philo, char *output);
void	ft_usleep(t_data *data, long ms);

// init.c
int		init(t_data *data, char **argv);

// clean.c
int		clean(t_data *data, int ret);

// join_threads.c
int		join_threads(t_data *data);

// start_simulation.c
int		start_simulation(t_data *data);

// routine_monitor.c
void	*routine_monitor(void *arg);

// routine_philo.c
void	*routine_philo(void *arg);

#endif