/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 10:49:40 by dvavryn           #+#    #+#             */
/*   Updated: 2025/08/07 11:04:24 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_stop(t_data *data)
{
	int	ret;

	pthread_mutex_lock(&data->mtx_death.mtx);
	ret = data->death_flag;
	pthread_mutex_unlock(&data->mtx_death.mtx);
	return (ret);
}

int	set_death(t_data *data)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&data->mtx_death.mtx);
	if (!data->death_flag)
	{
		data->death_flag = 1;
		ret = 1;	
	}
	pthread_mutex_unlock(&data->mtx_death.mtx);
	return (ret);
}
