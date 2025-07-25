/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 12:38:09 by dvavryn           #+#    #+#             */
/*   Updated: 2025/07/25 13:46:14 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	convert_args(t_config *config, char **argv);

int	populate_config(t_config *config, char **argv)
{
	ssize_t	i;

	memset(config, 0, sizeof(t_config));
	convert_args(config, argv);
	i = -1;
	config->forks = malloc(config->num_philos * sizeof(t_mtx));
	if (!config->forks)
		return (printf("Malloc forks failed\n"), destroy_config(config, i), 1);
	while (++i < config->num_philos)
	{
		if (pthread_mutex_init(&config->forks[i], NULL) == -1)
			return (printf("mutex init fork %zi failed\n", i), 1);
	}
	if (pthread_mutex_init(&config->print, NULL) == -1)
		return (printf("mutex init print failed\n"), 1);
	config->philo = malloc(config->num_philos * sizeof(t_philo));
	if (!config->philo)
		return (printf("Malloc philo failed\n"), destroy_config(config, i), 1);
	config->sim_ended = false;
	return (0);
}

void	populate_philos(t_config *config)
{
	ssize_t	i;
	t_philo	*ptr;

	i = -1;
	while (++i < config->num_philos)
	{
		ptr = &config->philo[i];
		ptr->right_fork = &config->forks[i];
		ptr->left_fork = &config->forks[(i + 1) % config->num_philos];
		ptr->id = i + 1;
		ptr->meals_consumed = 0;
		ptr->config = config;
		ptr->dead = false;
	}
}

static void	convert_args(t_config *config, char **argv)
{
	config->num_philos = (int)ft_atol(argv[1]);
	config->time_die = ft_atol(argv[2]);
	config->time_eat = ft_atol(argv[3]);
	config->time_sleep = ft_atol(argv[4]);
	if (argv[5])
		config->num_meals = (int)ft_atol(argv[5]);
	else
		config->num_meals = -1;
}
