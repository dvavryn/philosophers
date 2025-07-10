/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:55:42 by dvavryn           #+#    #+#             */
/*   Updated: 2025/07/10 11:01:33 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

# define ARGC "Usage: ./philo 1 800 200 200 [5]\n"
# define ONE "Num of philos has to be between 1 and INT_MAX\n"
# define TWO "Time to die has to be between 0 and INT_MAX\n"
# define THREE "Time to eat has to be between 0 and INT_MAX\n"
# define FOUR "Time to sleep has to be between 0 and INT_MAX\n"
# define FIVE "Number of meals has to be between 1 and INT_MAX\n"

struct	s_philo;
struct	s_table;
struct	s_fork;

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_meals;
	struct s_philo	*philos;
}	t_data;

typedef struct s_philo
{
	pthread_t		th;
	struct s_fork	*fork_1;
	struct s_fork	*fork_2;
	int				id;
}	t_philo;

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	int				id;
}	t_fork;

// utils.c
long	ft_atol(const char *nptr);
size_t	ft_strlen(const char *s);
int		ft_error(char *msg);

// init.c
int		init_data(int argc, char **argv, t_data *data);
void	get_data(char **argv, t_data *data);
int		errorcheck(char **argv);

#endif