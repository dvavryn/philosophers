/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 23:43:11 by dvavryn           #+#    #+#             */
/*   Updated: 2025/08/05 00:39:05 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_argc(int argc);
static int	check_numerical(char **argv);
static int	check_boundary(char **argv);

int	check(int argc, char **argv)
{
	if (check_argc(argc))
		return (1);
	if (check_numerical(argv))
		return (1);
	if (check_boundary(argv))
		return (1);
	return (0);
}

static int	check_argc(int argc)
{
	if (argc < 5 || argc > 6)
	{
		printf("Usage: ./philo 5 800 200 200 [5]\n");
		return (1);
	}
	return (0);
}

static int	check_numerical(char **argv)
{
	size_t	i;
	ssize_t	j;

	i = 0;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
			{
				printf("Error: Input must be numerical\n");
				return (1);
			}
		}
	}
	return (0);
}

static int	check_boundary(char **argv)
{
	size_t	i;
	long	buf;

	i = 0;
	while (argv[++i])
	{
		buf = ft_atol(argv[i]);
		if ((i == 1 || i == 5) && (buf <= 0 || buf > INT_MAX))
		{
			printf("Error: num_philos and num_meals have to be\n"
				"\tbigger than 0 and lower than INT_MAX\n");
			return (1);
		}
		else if ((i >= 2 && i <= 4) && (buf < 0 || buf > INT_MAX))
		{
			printf("Error: times have to be between 0 and INT_MAX\n");
			return (1);
		}
	}
	return (0);
}
