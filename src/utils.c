/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 23:42:04 by dvavryn           #+#    #+#             */
/*   Updated: 2025/08/05 14:34:45 by dvavryn          ###   ########.fr       */
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

int	get_time_ms(long *time)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
	{
		printf("Error: gettimeofday() failed\n");
		return (1);
	}
	*time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (0);
}

void	safe_print(t_philo *philo, char *output)
{
	long	time;

	pthread_mutex_lock(&philo->data->mtx_print.mtx);
	get_time_ms(&time);
	printf("%ld %d %s\n", time - philo->data->start, philo->id, output);
	pthread_mutex_unlock(&philo->data->mtx_print.mtx);
}

void	ft_usleep(t_data *data, long ms)
{
	(void)data;
	usleep(ms * 1000);
}