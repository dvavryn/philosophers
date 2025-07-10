/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 11:01:41 by dvavryn           #+#    #+#             */
/*   Updated: 2025/07/10 11:13:53 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	errorcheck(char **argv)
{
	if ((ft_atol(argv[1]) < 1 || ft_atol(argv[1]) > INT_MAX))
		return (ft_error(ONE));
	if (ft_atol(argv[2]) < 0 || ft_atol(argv[2]) > INT_MAX)
		return (ft_error(TWO));
	if (ft_atol(argv[3]) < 0 || ft_atol(argv[3]) > INT_MAX)
		return (ft_error(THREE));
	if (ft_atol(argv[4]) < 0 || ft_atol(argv[4]) > INT_MAX)
		return (ft_error(FOUR));
	if (argv[5] && (ft_atol(argv[5]) < 1 && ft_atol(argv[5]) > INT_MAX))
		return (ft_error(FIVE));
	return (0);
}

void	get_data(char **argv, t_data *data)
{
	data->num_philos = (int)ft_atol(argv[1]);
	data->time_to_die = (int)ft_atol(argv[2]);
	data->time_to_eat = (int)ft_atol(argv[3]);
	data->time_to_sleep = (int)ft_atol(argv[4]);
	if (argv[5])
		data->num_meals = (int)ft_atol(argv[5]);
	else
		data->num_meals = -1;
}

int	create_philos(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->num_meals)
	{
		pthread_create(data->philos, NULL, &hmm, NULL);
	}
}

int	init_data(int argc, char **argv, t_data *data)
{
	if (argc != 5 && argc != 6)
		return (ft_error(ARGC));
	if (errorcheck(argv))
		return (1);
	get_data(argv, data);
	data->philos = malloc(data->num_philos * sizeof(t_philo));
	if (!data->philos)
		return (1);
	create_philos(data);
	return (0);
}