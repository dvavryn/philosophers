/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 15:06:07 by dvavryn           #+#    #+#             */
/*   Updated: 2025/07/25 16:18:52 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*routine_philo(void *data);
static void	*routine_monitor(void *data);

int start_sim(t_config *config)
{
	ssize_t	i;
	pthread_t	monitor;

	i = -1;
	while (++i < config->num_philos)
	{
		if (pthread_create(&config->philo[i].thread, NULL, &routine_philo,&config->philo[i]))
			return (printf("thread create failed philo[%zi]\n", i), 1);
	}
	if (pthread_create(&monitor, NULL, &routine_monitor, config))
		return (printf("thread create failed monitor\n"), 1);
	config->sim_started = 1;
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

static void	*routine_philo(void *data)
{
	t_philo	*philo;
	struct timeval cur;

	philo = (t_philo *)data;
	while (!philo->config->sim_started)
		;
	philo->last_meal = philo->config->start_time_ms;
	if (philo->id % 2 == 0)
		usleep(philo->config->time_die / 4);
	while (!philo->dead && !philo->config->sim_ended)
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

static void	*routine_monitor(void *data)
{
	t_config		*config;
	struct timeval cur;
	ssize_t	i;
	t_philo	*ptr;
	int fin_philos;

	config = (t_config *)data;
	while (!config->sim_started)
		;
	config->start_time_ms = conv_time(config->start) + 60;
	while (!config->sim_ended)
	{
		i = -1;
		fin_philos = 0;
		while (++i < config->num_philos)
		{
			ptr = &config->philo[i];
			gettimeofday(&cur, NULL);
			if (config->time_die <= conv_time(cur) - ptr->last_meal)
			{	
				lock_print("has died --------------------------", ptr);
				ptr->dead = true;
				config->sim_ended = true;
				break;
			}
			if (ptr->meals_consumed == config->num_meals && config->num_meals != -1)
				fin_philos++;
		}
		if (fin_philos == config->num_philos)
		{
			config->sim_ended = true;
			break;
		}
		usleep(1000);
	}
	return (NULL);
}
