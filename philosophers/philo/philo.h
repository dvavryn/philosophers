/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 12:51:38 by dvavryn           #+#    #+#             */
/*   Updated: 2025/07/25 13:16:03 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <stdbool.h>

typedef pthread_mutex_t	t_mtx;
typedef struct s_config	t_config;

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
	int				sim_ended;
	t_mtx			*forks;
	t_mtx			print;
	struct timeval	start;
	bool			sim_started;
	t_philo			*philo;
};

int		populate_config(t_config *config, char **argv);
int		lock_print(const char *s, t_philo *philo);
int		check_input(int argc, char **argv);
int		start_sim(t_config *config);
long	conv_time(struct timeval time);
long	ft_atol(const char *nptr);
void	destroy_config(t_config *config, int num_mtx);
void	populate_philos(t_config *config);

#endif