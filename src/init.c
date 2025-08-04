/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 00:06:21 by dvavryn           #+#    #+#             */
/*   Updated: 2025/08/05 01:04:57 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int		init_data(t_data *data, char **argv);
static int		init_mutexes(t_data *data);
static void		init_philos(t_data *data);

int	init(t_data *data, char **argv)
{
	if (init_data(data, argv))
	{
		printf("Error: malloc() failed at init_data()\n");
		return (1);
	}
	if (init_mutexes(data))
	{
		printf("Error: pthred_mutex_init() failed at init_mutexes()\n");
		return (1);
	}
	init_philos(data);
	return (0);
}

static int	init_data(t_data *data, char **argv)
{
	memset(data, 0, sizeof(t_data));
	data->num_meals = (int)ft_atol(argv[1]);
	data->time_die = ft_atol(argv[2]);
	data->time_eat = ft_atol(argv[3]);
	data->time_sleep = ft_atol(argv[4]);
	data->num_meals = -1;
	if (argv[5])
		data->num_meals = (int)ft_atol(argv[5]);
	data->philos = ft_calloc(data->num_philos, sizeof(t_philo));
	data->forks = ft_calloc(data->num_philos, sizeof(t_mtx));
	if (!data->philos || !data->forks)
		return (1);
	return (0);
}

static int	safe_mutex_init(t_mtx *mtx)
{
	if (pthread_mutex_init(&mtx->mtx, NULL))
		return (1);
	mtx->valid = 1;
	return (0);
}

static int	init_mutexes(t_data *data)
{
	ssize_t	i;

	if (safe_mutex_init(&data->mtx_death))
		return (1);
	if (safe_mutex_init(&data->mtx_print))
		return (1);
	i = -1;
	while (++i < data->num_philos)
	{
		if (safe_mutex_init(&data->philos[i].mtx_meal))
			return (1);
		if (safe_mutex_init(&data->forks[i]))
			return (1);
	}
	return (0);
}

static void	init_philos(t_data *data)
{
	ssize_t	i;

	i = -1;
	while (++i < data->num_philos)
	{
		data->philos[i].data = data;
		data->philos[i].fork_one = &data->forks[i];
		data->philos[i].fork_two = &data->forks[(i + 1) % data->num_philos];
		data->philos[i].id = i + 1;
	}
}
