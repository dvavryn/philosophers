/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_monitor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 01:16:20 by dvavryn           #+#    #+#             */
/*   Updated: 2025/08/05 19:12:20 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int routine_monitor_one(t_data *data, ssize_t i);
static int	routine_monitor_two(t_data *data);

void	*routine_monitor(void *arg)
{
	// (void)arg;
	
	t_data	*data;
	// 
	data = (t_data *)arg;
	while (1)
	{
		if (routine_monitor_one(data, -1))
			return (NULL);
		if (routine_monitor_two(data))
			return (NULL);
		ft_usleep(data, 1);
	}
	return (NULL);
}

static int routine_monitor_one(t_data *data, ssize_t i)
{
	long	time_since_meal;

	while (++i < data->num_philos)
	{
		get_time_ms(&time_since_meal);
		pthread_mutex_lock(&data->philos[i].mtx_meal.mtx);
		time_since_meal -= data->philos[i].last_meal;
		pthread_mutex_unlock(&data->philos[i].mtx_meal.mtx);
		if (time_since_meal >= data->time_die)
		{
			pthread_mutex_lock(&data->mtx_death.mtx);
			if (!data->deat_flag)
			{
				data->deat_flag = 1;
				pthread_mutex_unlock(&data->mtx_death.mtx);
				safe_print(&data->philos[i], "died");
			}
			else
				pthread_mutex_unlock(&data->mtx_death.mtx);
			return (1);
		}
	}
	return (0);
}

static int	routine_monitor_two(t_data *data)
{
	ssize_t	i;
	int		full_philos;

	if (data->num_meals == -1)
		return (0);
	full_philos = 0;
	i = -1;
	while (++i < data->num_philos)
	{
		pthread_mutex_lock(&data->philos[i].mtx_meal.mtx);
		if (data->philos[i].meals_eaten >= data->num_meals)
			full_philos++;
		pthread_mutex_unlock(&data->philos[i].mtx_meal.mtx);
	}
	if (full_philos == data->num_philos)
	{
		pthread_mutex_lock(&data->mtx_death.mtx);
		data->deat_flag = 1;
		pthread_mutex_unlock(&data->mtx_death.mtx);
		return (1);
	}
	return (0);
}