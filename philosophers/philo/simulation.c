/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 12:41:05 by dvavryn           #+#    #+#             */
/*   Updated: 2025/07/25 16:08:29 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*routine_philo(void *data);
void		*routine_monitor(void *data);

int	start_sim(t_config *config)
{
	ssize_t		i;
	pthread_t	monitor;

	i = -1;
	while (++i < config->num_philos)
	{
		if (pthread_create(&config->philo[i].thread, NULL,
				&routine_philo, &config->philo[i]))
			return (printf("thread create failed philo[%zi]\n", i), 1);
	}
	if (pthread_create(&monitor, NULL, &routine_monitor, config))
		return (printf("thread create failed monitor\n"), 1);
	usleep(60000);
	config->sim_ended = 1;
	if (pthread_join(monitor, NULL))
		return (printf("thread join failed monitor\n"), 1);
	i = -1;
	while (++i < config->num_philos)
	{
		if (pthread_join(config->philo[i].thread, NULL))
			return (printf("thread join failed philo[%zi]\n", i), 1);
	}
	return (0);
}

static void	routine_philo_sub(t_philo *philo)
{
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		lock_print("has taken a fork", philo);
		pthread_mutex_lock(philo->right_fork);
		lock_print("has taken a fork", philo);
		lock_print("is eating", philo);
		usleep(philo->config->time_eat * 1000);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		lock_print("has taken a fork", philo);
		pthread_mutex_lock(philo->left_fork);
		lock_print("has taken a fork", philo);
		lock_print("is eating", philo);
		usleep(philo->config->time_eat * 1000);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
}

static void	*routine_philo(void *data)
{
	t_philo			*philo;
	struct timeval	cur;

	philo = (t_philo *)data;
	while (philo->config->sim_started)
		;
	philo->last_meal = conv_time(philo->config->start);
	while (!philo->dead && !philo->config->sim_ended)
	{
		routine_philo_sub(philo);
		gettimeofday(&cur, NULL);
		philo->last_meal = conv_time(cur);
		philo->meals_consumed++;
		if (philo->meals_consumed == philo->config->num_meals)
			break ;
		lock_print("is sleeping", philo);
		usleep(philo->config->time_sleep * 1000);
		lock_print("is thinking", philo);
	}
	return (NULL);
}

void	routine_monitor_sub(t_config *config, struct timeval *cur,
	t_philo *ptr, int *fin_philos)
{
	ssize_t	i;

	i = -1;
	fin_philos = 0;
	while (++i < config->num_philos)
	{
		ptr = &config->philo[i];
		gettimeofday(cur, NULL);
		if (config->time_die <= conv_time(*cur) - ptr->last_meal)
		{
			ptr->dead = true;
			lock_print("has died", ptr);
			config->sim_ended = true;
			break ;
		}
		if (ptr->meals_consumed == config->num_meals
			&& config->num_meals != -1)
			fin_philos++;
	}
}

void	*routine_monitor(void *data)
{
	t_config		*config;
	struct timeval	cur;
	t_philo			*ptr;
	int				fin_philos;

	config = (t_config *)data;
	if (gettimeofday(&config->start, NULL) == -1)
	{
		config->start.tv_usec += 60000;
		config->sim_ended = true;
		return (printf("gettimeofday failed\n"), NULL);
	}
	config->sim_started = true;
	while (!config->sim_ended)
	{
		routine_monitor_sub(config, &cur, ptr, &fin_philos);
		if (fin_philos == config->num_philos)
		{
			config->sim_ended = true;
			break ;
		}
		usleep(300);
	}
	return (NULL);
}
