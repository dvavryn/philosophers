/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 00:48:24 by dvavryn           #+#    #+#             */
/*   Updated: 2025/08/05 14:22:04 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	clean(t_data *data, int ret)
{
	ssize_t	i;

	i = -1;
	while (++i < data->num_philos)
	{
		if (data->forks[i].valid)
			pthread_mutex_destroy(&data->forks[i].mtx);
		if (data->philos[i].mtx_meal.valid)
			pthread_mutex_destroy(&data->philos[i].mtx_meal.mtx);
	}
	if (data->mtx_death.valid)
		pthread_mutex_destroy(&data->mtx_death.mtx);
	if (data->mtx_print.valid)
		pthread_mutex_destroy(&data->mtx_print.mtx);
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
	return (ret);
}
