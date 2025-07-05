/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 22:37:18 by dvavryn           #+#    #+#             */
/*   Updated: 2025/07/06 00:09:30 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_forks(t_philo *philo, t_fork *forks, int pos)
{
	int philo_num;

	philo_num = philo->table->philo_num;
	philo->first_fork = &forks[(pos + 1) % philo_num];
	philo->second_fork = &forks[pos];
	if (philo->id % 2)
	{
		philo->first_fork = &forks[pos];
		philo->second_fork = &forks[(pos + 1) % philo_num];
	}
}

static void	philo_init(t_table *table)
{
	int	i;
	t_philo	*philo;

	i = -1;
	while (++i < table->philo_num)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meals_counter = 0;
		philo->table = table;

		assign_forks(philo, table->forks, i);
	}
}

void	data_init(t_table *table)
{
	int	i;

	i = -1;
	table->end_sim = false;
	table->all_threads_ready = false;
	table->philos = safe_malloc(sizeof(t_philo) *table->philo_num);
	safe_mutex_handle(&table->table_mutex, INIT);
	table->forks = safe_malloc(sizeof(t_fork) * table->philo_num);
	while (++i < table->philo_num)
	{
		safe_mutex_handle(&table->forks[i], INIT);
		table->forks[i].fork_id = i;
	}
	philo_init(table);
}