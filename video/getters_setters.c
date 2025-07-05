/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 00:10:00 by dvavryn           #+#    #+#             */
/*   Updated: 2025/07/06 00:15:02 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_bool(t_mtx *mutex, bool *dest, bool val)
{
	safe_mutex_handle(mutex, LOCK);
	*dest = val;
	safe_mutex_handle(mutex, UNLOCK);
}

bool	get_bool(t_mtx *mutex, bool *val)
{
	bool	out;
	
	safe_mutex_handle(mutex, LOCK);
	out = *val;
	safe_mutex_handle(mutex, UNLOCK);
	return (out);
}

void	set_long(t_mtx *mutex, long *dest, long val)
{
	safe_mutex_handle(mutex, LOCK);
	*dest = val;
	safe_mutex_handle(mutex, UNLOCK);
}

long	get_long(t_mtx *mutex, long *val)
{
	long	out;
	
	safe_mutex_handle(mutex, LOCK);
	out = *val;
	safe_mutex_handle(mutex, UNLOCK);
	return (out);
}

bool	simulation_finished(t_table *table)
{
	return (get_bool(&table->table_mutex, &table->end_sim));
}