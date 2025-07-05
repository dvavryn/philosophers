/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 22:01:24 by dvavryn           #+#    #+#             */
/*   Updated: 2025/07/06 00:41:21 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/time.h>

#include <limits.h>
#include <errno.h>


#define RST	"\033[0m"
#define RED	"\033[1;31m"
#define G	"\033[1;32m"
#define Y	"\033[1;33m"
#define B	"\033[1;34m"
#define M	"\033[1;35m"
#define C	"\033[1;36m"
#define W	"\033[1;37m"

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}	t_opcode;

typedef enum e_timecode
{
	SECOND,
	MILISECOND,
	MICROSECOND,
}	t_timecode;

typedef enum e_philo_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}	t_philo_status;

// ./philo 5 800 200 200 [5]

// Structs
typedef	pthread_mutex_t t_mtx;
typedef	struct s_table t_table;

typedef struct s_fork
{
	t_mtx	fork;
	int		fork_id;
}	t_fork;

typedef struct s_philo
{
	int			id;
	long		meals_counter;
	bool		full;
	long		last_meal_time;
	t_fork		*first_fork;
	t_fork		*second_fork;
	pthread_t	thread_id;
	t_table		*table;
}	t_philo;

struct s_table
{
	long	philo_num;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	num_limit_meals;
	long	start_sim;
	bool	end_sim;
	bool	all_threads_ready;
	t_mtx	table_mutex;
	t_mtx	write_mutex;
	t_fork	*forks;
	t_philo	*philos;
};

void	error_exit(const char *error);
void	parse_input(t_table *table, char **argv);
void	*safe_malloc(size_t	bytes);
void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode);
void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data, t_opcode opcode);
void	data_init(t_table *table);
void	dinner_start(t_table *table);
void	set_bool(t_mtx *mutex, bool *dest, bool val);
bool	get_bool(t_mtx *mutex, bool *val);
void	set_long(t_mtx *mutex, long *dest, long val);
long	get_long(t_mtx *mutex, long *val);
bool	simulation_finished(t_table *table);
void	wait_all_threads(t_table *table);
long	get_time(t_timecode timecode);
void	prec_usleep(long usec, t_table *table);

#endif