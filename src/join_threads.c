/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 01:11:04 by dvavryn           #+#    #+#             */
/*   Updated: 2025/08/05 17:41:41 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	join_threads(t_data *data)
{
	ssize_t	i;

	i = -1;
	while (++i < data->num_philos)
	{
		if (pthread_join(data->philos[i].thread, NULL))
		{
			printf("Error: pthread_join()-philo failed at join_thread()\n");
			return (1);
		}
	}
	if (data->monitor && pthread_join(data->monitor, NULL))
	{
		printf("Error: pthreadjoin()-monitor failed at join_thead()\n");
		return (1);
	}
	return (0);
}
