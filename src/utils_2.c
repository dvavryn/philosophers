/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 17:02:12 by dvavryn           #+#    #+#             */
/*   Updated: 2025/08/08 17:02:45 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(t_data *data, long ms)
{
	long	end;
	long	now;
	long	rem;

	now = get_time_ms();
	end = now + ms;
	while (!check_stop(data))
	{
		now = get_time_ms();
		if (now >= end)
			break ;
		rem = end - now;
		if (rem > 1)
			usleep(1000);
		else
			usleep(100);
	}
}
