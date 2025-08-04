/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 23:33:06 by dvavryn           #+#    #+#             */
/*   Updated: 2025/08/05 00:42:01 by dvavryn          ###   ########.fr       */
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

	int				deat_flag;
	long			start;
}	t_data;

typedef struct s_philo
{
	t_data			*data;
	pthread_t		thread;
	t_mtx			*fork_one;
	t_mtx			*fork_two;
	t_mtx			mtx_meal;
	long			last_meal;
	int				meals_eaten;
	int				id;
}	t_philo;

// check.c
int		check(int argc, char **argv);

// utils.c
long	ft_atol(const char *nptr);
void	*ft_calloc(size_t nmemb, size_t size);

// init.c
int		init(t_data *data, char **argv);

#endif