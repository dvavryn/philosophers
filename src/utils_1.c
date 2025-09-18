/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 23:42:04 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/18 16:33:09 by dvavryn          ###   ########.fr       */
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
	return (out);
}

long	get_time_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
	{
		printf("Error: gettimeofday() failed\n");
		return (0);
	}
	return (tv.tv_usec / 1000 + tv.tv_sec * 1000);
}

void	safe_print(t_philo *philo, const char *output)
{
	long	time;

	pthread_mutex_lock(&philo->data->mtx_print.mtx);
	if (check_stop(philo->data) && ft_strcmp(output, "died"))
	{
		pthread_mutex_unlock(&philo->data->mtx_print.mtx);
		return ;
	}
	time = get_time_ms() - philo->data->start;
	printf("%ld %d %s\n", time, philo->id, output);
	pthread_mutex_unlock(&philo->data->mtx_print.mtx);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	ssize_t	i;

	i = -1;
	while (s1[++i] && s2[i] && s1[i] == s2[i])
		;
	return (s1[i] - s2[i]);
}
