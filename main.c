/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:04:12 by dvavryn           #+#    #+#             */
/*   Updated: 2025/07/09 14:34:33 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = -1;
	while (s[++i])
		;
	return (i);
}

int	ft_error(char *msg)
{
	write(2, msg, ft_strlen(msg));
	return (1);
}

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

int	init_data(int argc, char **argv, t_data *data)
{
	if (argc != 5 && argc != 6)
		return (ft_error(ARGC));
	if (errorcheck(argv))
		return (1);
	get_data(argv, data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (init_data(argc, argv, &data))
		return (1);
	printf("%i ", data.num_philos);
	printf("%i ", data.time_to_die);
	printf("%i ", data.time_to_eat);
	printf("%i ", data.time_to_sleep);
	printf("%i\n", data.num_meals);
	return (0);
}
