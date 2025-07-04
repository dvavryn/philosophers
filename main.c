/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:36:53 by dvavryn           #+#    #+#             */
/*   Updated: 2025/07/04 13:42:44 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>

typedef struct	s_data
{
	long	num_of_philos;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	num_of_meals;
}	t_data;

long	ft_atol(const char *nptr);
int check_input(int argc, char **argv);
t_data	get_data(int argc, char **argv);
void	util_print(t_data data);

int main(int argc, char **argv)
{
	t_data	data;

	if (check_input(argc, argv))
		return (printf("wrong input\n"), 1);
	data = get_data(argc, argv);
	util_print(data);
	return (0);
}

void	util_print(t_data data)
{
	printf("Philos: %ld\nTime to die: %ld\nTime to eat: %ld\nTime to sleep: %ld\nMeals: %ld\n",
		data.num_of_philos, data.time_to_die, data.time_to_eat, data.time_to_sleep, data.num_of_meals);
}

t_data	get_data(int argc, char **argv)
{
	t_data	out;

	out.num_of_philos = ft_atol(argv[1]);
	out.time_to_die = ft_atol(argv[2]);
	out.time_to_eat = ft_atol(argv[3]);
	out.time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		out.num_of_meals = ft_atol(argv[5]);
	else
		out.num_of_meals = -1;
	return (out);
}

int check_input(int argc, char **argv)
{
	size_t	i = 0;
	size_t	j = 0;
	if (argc != 5 && argc != 6)
		return (printf("ac != 5 || 6\n"), 1);
	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				return (1);
			j++;
		}
		if (i > 1 && i < 5 && ft_atol(argv[i]) < 60)
			return (printf("argv[%zu] < 60\n", i), 1);
		if (ft_atol(argv[i]) > INT_MAX)
			return (printf("argv[i] > INT_MAX\n"), 1);
		i++;
	}
	if (argc == 6)
		if (ft_atol(argv[5]) <= 0 || ft_atol(argv[5]) > INT_MAX)
			return (printf("Too many meals\n"), 1);
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