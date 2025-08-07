/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 23:42:04 by dvavryn           #+#    #+#             */
/*   Updated: 2025/08/07 13:15:46 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(const char *nptr)
{
	long	out;
	long	sign;
	size_t	i;

	out = 0;
	sign = 1;
	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		out = out * 10 + (nptr[i] - '0');
		i++;
	}
	return (out * sign);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	total;
	void	*out;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	total = nmemb * size;
	if (total / nmemb != size)
		return (NULL);
	out = malloc(total);
	if (!out)
		return (NULL);
	memset(out, 0, total);
	return (out);
}

long	get_time_ms()
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		printf("Error: gettimeofday() failed\n");
	return (tv.tv_usec / 1000 * tv.tv_sec * 1000);	
}

void	safe_print(t_philo *philo, char *output)
{
	long	time;

	pthread_mutex_lock(&philo->data->mtx_death.mtx);
	if (philo->data->death_flag == 1)
	{
		pthread_mutex_unlock(&philo->data->mtx_death.mtx);
		return ;
	}
	else
		pthread_mutex_unlock(&philo->data->mtx_death.mtx);
	pthread_mutex_lock(&philo->data->mtx_print.mtx);
	time = get_time_ms();
	printf("%ld %d %s\n", time - philo->data->start, philo->id, output);
	pthread_mutex_unlock(&philo->data->mtx_print.mtx);
}

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
