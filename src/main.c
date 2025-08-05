/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 23:31:53 by dvavryn           #+#    #+#             */
/*   Updated: 2025/08/05 19:45:06 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
void	get_times(t_data *data);

int	main(int argc, char **argv)
{
	t_data	data;

	if (check(argc, argv))
		return (1);
	if (init(&data, argv))
		return (clean(&data, 1));
	get_times(&data);
	if (start_simulation(&data))
		return (clean(&data, 1));
	if (join_threads(&data))
		return (clean(&data, 1));
	return (clean(&data, 0));
}

void	get_times(t_data *data)
{
	ssize_t	i;

	i = -1;
	get_time_ms(&data->start);
	while (++i < data->num_philos)
		data->philos[i].last_meal = data->start;
}