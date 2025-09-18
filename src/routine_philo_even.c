/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo_even.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 15:50:02 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/18 15:50:49 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	even_philo_eat(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	first = &philo->fork_one->mtx;
	second = &philo->fork_two->mtx;
	if (philo->fork_one > philo->fork_two)
	{
		first = &philo->fork_two->mtx;
		second = &philo->fork_one->mtx;
	}
	pthread_mutex_lock(first);
	safe_print(philo, "has taken a fork");
	pthread_mutex_lock(second);
	safe_print(philo, "has taken a fork");
	safe_print(philo, "is eating");
	ft_usleep(philo->data, philo->data->time_eat);
	pthread_mutex_lock(&philo->mtx_meal.mtx);
	philo->meals_eaten++;
	if (philo->meals_eaten == philo->data->num_meals)
		philo->full = 1;
	philo->last_meal = get_time_ms();
	pthread_mutex_unlock(&philo->mtx_meal.mtx);
	pthread_mutex_unlock(first);
	pthread_mutex_unlock(second);
}

void	even_amount_philos(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		philo_think(philo);
		ft_usleep(philo->data, philo->data->time_eat / 2);
	}
	while (!philo->data->death_flag)
	{
		even_philo_eat(philo);
		if (philo->full == 1)
			break ;
		philo_sleep(philo);
		philo_think(philo);
	}
}
