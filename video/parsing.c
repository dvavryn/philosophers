/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 22:19:38 by dvavryn           #+#    #+#             */
/*   Updated: 2025/07/06 00:35:26 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline bool is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static inline bool is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static const char *valid_input(const char *s)
{
	size_t		len;
	const char	*out;

	len = 0;
	while (is_space(*s))
		s++;
	if (*s == '+')
		s++;
	else if (*s == '-')
		error_exit("Feed me only positive values");
	if (!is_digit(*s))
		error_exit("Input is not a correct digit");
	out = s;
	while (*s++)
		len++;
	if (len > 10)
		error_exit("Limit is INT_MAX");
	return (out);
}

static long	ft_atol(const char *s)
{
	long	out;
	
	out = 0;
	s = valid_input(s);
	while (is_digit(*s))
		out = (out * 10) + (*s++ - 48);
	if (out > INT_MAX)
		error_exit("Limit is INT_MAX");
	return (out);
}

void	parse_input(t_table *table, char **argv)
{
	table->philo_num = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]) * 1e3;
	table->time_to_eat = ft_atol(argv[3]) * 1e3;
	table->time_to_sleep = ft_atol(argv[4]) * 1e3;
	if (table->time_to_die < 6e4
		|| table->time_to_eat < 6e4
		|| table->time_to_sleep < 6e4)
		error_exit("Use timestamps major than 60ms");
	if (argv[5])
		table->num_limit_meals = ft_atol(argv[5]);
	else
		table->num_limit_meals = -1;
}
