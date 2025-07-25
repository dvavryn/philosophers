/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 12:39:42 by dvavryn           #+#    #+#             */
/*   Updated: 2025/07/25 12:50:19 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	conv_time(struct timeval time)
{
	long	out;

	out = 0;
	out += time.tv_sec * 1000;
	out += time.tv_usec / 1000;
	return (out);
}

int	lock_print(const char *s, t_philo *philo)
{
	struct timeval	cur;
	long			timestamp;

	if (gettimeofday(&cur, NULL) == -1)
		return (-1);
	timestamp = conv_time(cur) - conv_time(philo->config->start);
	pthread_mutex_lock(&philo->config->print);
	printf("%ld ms %d %s\n", timestamp, philo->id, s);
	pthread_mutex_unlock(&philo->config->print);
	return (0);
}

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

void	destroy_config(t_config *config, int num_mtx)
{
	ssize_t	i;

	pthread_mutex_destroy(&config->print);
	i = -1;
	while (++i < num_mtx)
		pthread_mutex_destroy(&config->forks[i]);
	if (config->forks)
		free(config->forks);
	if (config->philo)
		free(config->philo);
}

int	check_input(int argc, char **argv)
{
	size_t	i;
	ssize_t	j;
	long	d;

	if (argc != 5 && argc != 6)
		return (1);
	i = 0;
	while (++i < (unsigned int) argc)
	{
		j = -1;
		while (argv[i][++j])
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				return (printf("There are non numerical"
						"characters in the argument!\n"), 1);
		}
		d = ft_atol(argv[i]);
		if (d <= 0)
			return (printf("Argument has to be over 0\n"), 1);
		else if (d > INT_MAX)
			return (printf("Argument has to be under INT_MAX\n"), 1);
	}
	return (0);
}
