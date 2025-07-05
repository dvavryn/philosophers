/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 22:10:55 by dvavryn           #+#    #+#             */
/*   Updated: 2025/07/06 00:37:29 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_exit(const char *error)
{
	printf(RED"%s\n"RST, error);
	exit(EXIT_FAILURE);
}

long	get_time(t_timecode timecode)
{
	struct timeval tv;
	
	if (gettimeofday(&tv, NULL))
		error_exit("gettimeofday failed");
	if (timecode == SECOND)
		return (tv.tv_sec + tv.tv_usec / 1e6);
	else if (timecode == MILISECOND)
		return (tv.tv_sec * 1e3 + tv.tv_usec / 1e3);
	else if (timecode == MICROSECOND)
		return (tv.tv_sec * 1e6 + tv.tv_usec);
	else
		error_exit("Wrong input to gettime");
	return (-1);
}

void	prec_usleep(long usec, t_table *table)
{
	long	start;
	long	elapsed;
	long	rem;
	
	start = get_time(MICROSECOND);
	while (get_time(MICROSECOND) - start < usec)
	{
		if (simulation_finished(table))
			break ;
		elapsed = get_time(MICROSECOND) - start;
		rem = usec - elapsed;
		if (rem > 1e3)
			usleep(usec / 2);
		else
		{
			while (get_time(MICROSECOND) - start < usec);
				;
		}
	}
}
