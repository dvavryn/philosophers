/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 01:05:57 by dvavryn           #+#    #+#             */
/*   Updated: 2025/08/05 01:19:06 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_simulation(t_data *data)
{
	ssize_t	i;

	i = -1;
	while (++i < data->num_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
			routine_philo, &data->philos[i]))
		{
			printf("Error: pthread_create()-philo failed at start_simulation()\n");
			return (1);
		}
	}
	if (pthread_create(&data->monitor, NULL, routine_monitor, &data))
	{
		printf("Error: pthread_create()-monitor failed at start_simulation()\n");
		return (1);
	}
	return (0);
}