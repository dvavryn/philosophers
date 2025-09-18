/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo_odd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 15:50:02 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/18 19:13:40 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	odd_philo_eat_even(t_philo *philo)
{
	// 5 600 200 200 should die!!!
	pthread_mutex_lock(&philo->fork_one->mtx);
	safe_print(philo, "has taken a fork");
	pthread_mutex_lock(&philo->fork_two->mtx);
	safe_print(philo, "has taken a fork");
	safe_print(philo, "is eating");
	pthread_mutex_lock(&philo->mtx_meal.mtx);
	philo->last_meal = get_time_ms();
	pthread_mutex_unlock(&philo->mtx_meal.mtx);
	ft_usleep(philo->data, philo->data->time_eat);
	pthread_mutex_lock(&philo->mtx_meal.mtx);
	philo->meals_eaten++;
	if (philo->meals_eaten == philo->data->num_meals)
		philo->full = 1;
	pthread_mutex_unlock(&philo->mtx_meal.mtx);
	pthread_mutex_unlock(&philo->fork_two->mtx);
	pthread_mutex_unlock(&philo->fork_one->mtx);
}

void	odd_philo_eat_odd(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_two->mtx);
	safe_print(philo, "has taken a fork");
	pthread_mutex_lock(&philo->fork_one->mtx);
	safe_print(philo, "has taken a fork");
	safe_print(philo, "is eating");
	pthread_mutex_lock(&philo->mtx_meal.mtx);
	philo->last_meal = get_time_ms();
	pthread_mutex_unlock(&philo->mtx_meal.mtx);
	ft_usleep(philo->data, philo->data->time_eat);
	pthread_mutex_lock(&philo->mtx_meal.mtx);
	philo->meals_eaten++;
	if (philo->meals_eaten == philo->data->num_meals)
		philo->full = 1;
	pthread_mutex_unlock(&philo->mtx_meal.mtx);
	pthread_mutex_unlock(&philo->fork_one->mtx);
	pthread_mutex_unlock(&philo->fork_two->mtx);
}

void	odd_amount_philos(t_philo *philo)
{
	if (philo->id == 1 || philo->id % 2 == 0)
	{
		philo_think(philo);
		ft_usleep(philo->data, philo->data->time_eat / 2);
		if (philo->id == 1)
			ft_usleep(philo->data, philo->data->time_eat);
	}
	while (!philo->data->death_flag)
	{
		if (philo->id % 2 == 0)
			odd_philo_eat_even(philo);
		else
			odd_philo_eat_odd(philo);
		if (philo->full == 1)
			break ;
		philo_sleep(philo);
		philo_think(philo);
		if (philo->data->time_eat > philo->data->time_sleep)
			ft_usleep(philo->data, philo->data->time_eat
				+ philo->data->time_eat / 2);
		else
			ft_usleep(philo->data, philo->data->time_eat);
	}
}
