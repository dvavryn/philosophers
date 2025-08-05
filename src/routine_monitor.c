/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_monitor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 01:16:20 by dvavryn           #+#    #+#             */
/*   Updated: 2025/08/05 19:53:23 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	routine_monitor_sub(t_data *data);
static int	check_death(t_data *data);

void	*routine_monitor(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (!check_death(data))
	{
		if (routine_monitor_sub(data))
			break ;
		ft_usleep(NULL, 1);
	}
	return (NULL);
}

int	routine_monitor_sub(t_data *data)
{
	ssize_t	i;
	int		full;
	long	time;

	i = -1;
	full = 0;
	while (++i < data->num_philos)
	{
		get_time_ms(&time);
		pthread_mutex_lock(&data->philos[i].mtx_meal.mtx);
		if (data->philos[i].full)
			full++;
		if (time - data->philos[i].last_meal >= data->time_die)
		{
			pthread_mutex_unlock(&data->philos[i].mtx_meal.mtx);
			pthread_mutex_lock(&data->mtx_death.mtx);
			data->death_flag = 1;
			pthread_mutex_unlock(&data->mtx_death.mtx);
			safe_print(&data->philos[i], "died");
			return (1);
		}
		else
			pthread_mutex_unlock(&data->philos[i].mtx_meal.mtx);
	}
	if (full == data->num_philos)
	{
		pthread_mutex_lock(&data->mtx_death.mtx);
		data->death_flag = 1;
		pthread_mutex_unlock(&data->mtx_death.mtx);
		return (1);
	}
	return (0);
}

static int	check_death(t_data *data)
{
	int ret;

	pthread_mutex_lock(&data->mtx_death.mtx);
	ret = data->death_flag;
	pthread_mutex_unlock(&data->mtx_death.mtx);
	return (ret);
}