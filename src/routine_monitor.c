/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_monitor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 01:16:20 by dvavryn           #+#    #+#             */
/*   Updated: 2025/08/08 17:58:25 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_death(t_philo *philo, long now)
{
	long	last;

	pthread_mutex_lock(&philo->mtx_meal.mtx);
	last = philo->last_meal;
	pthread_mutex_unlock(&philo->mtx_meal.mtx);
	if (now - last >= philo->data->time_die)
	{
		if (set_death(philo->data))
			safe_print(philo, "died");
		return (1);
	}
	return (0);
}

static int	all_full(t_data *data)
{
	int	i;
	int	is_full;

	if (data->num_meals == -1)
		return (0);
	i = -1;
	while (++i < data->num_philos)
	{
		is_full = 0;
		pthread_mutex_lock(&data->philos[i].mtx_meal.mtx);
		is_full = data->philos[i].full;
		pthread_mutex_unlock(&data->philos[i].mtx_meal.mtx);
		if (!is_full)
			return (0);
	}
	return (1);
}

static int	check_full(t_philo *philo)
{
	if (philo->data->num_meals == -1)
		return (0);
	pthread_mutex_lock(&philo->mtx_meal.mtx);
	if (philo->full)
	{
		pthread_mutex_unlock(&philo->mtx_meal.mtx);
		return (1);
	}
	pthread_mutex_unlock(&philo->mtx_meal.mtx);
	return (0);
}

void	*routine_monitor(void *arg)
{
	t_data	*data;
	int		i;
	long	now;

	data = (t_data *)arg;
	while (!check_stop(data))
	{
		now = get_time_ms();
		i = -1;
		while (++i < data->num_philos && !check_stop(data))
		{
			if (!check_full(&data->philos[i])
				&& check_death(&data->philos[i], now))
				return (NULL);
		}
		if (!check_stop(data) && all_full(data))
		{
			set_death(data);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
