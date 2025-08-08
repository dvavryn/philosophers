/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 01:16:26 by dvavryn           #+#    #+#             */
/*   Updated: 2025/08/08 18:04:52 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo);
void	release_forks(t_philo *philo);
void	philo_eat(t_philo *philo);

void	*routine_philo(void *arg)
{
	t_philo	*philo;
	int		meals;

	meals = 0;
	philo = (t_philo *)arg;
	if (philo->data->num_philos == 1)
	{
		pthread_mutex_lock(&philo->fork_one->mtx);
		if (!check_stop(philo->data))
			safe_print(philo, "has taken a fork");
		while (!check_stop(philo->data))
			usleep(1000);
		pthread_mutex_unlock(&philo->fork_one->mtx);
		return (0);
	}
	if (philo->data->num_philos % 2 == 1 && philo->id % 2 == 0)
		usleep(1000);
	if (!check_stop(philo->data))
		safe_print(philo, "is thinking");	
	while (!check_stop(philo->data))
	{
		take_forks(philo);
		if (check_stop(philo->data))
		{
			release_forks(philo);
			break ;
		}
		philo_eat(philo);
		release_forks(philo);
		usleep(100);
		if (check_stop(philo->data))
			break ;
		if (++meals >= philo->data->num_meals)
			break ;
		if (!check_stop(philo->data))
			safe_print(philo, "is sleeping");
		ft_usleep(philo->data, philo->data->time_sleep);
		if (!check_stop(philo->data))
			safe_print(philo, "is thinking");
		// ft_usleep(philo->data,
		// 	(philo->data->time_die - philo->data->time_eat - philo->data->time_sleep) / 2);
	}
	return (NULL);
}

void	philo_eat(t_philo *philo)
{
	safe_print(philo, "is eating");
	pthread_mutex_lock(&philo->mtx_meal.mtx);
	philo->last_meal = get_time_ms();
	pthread_mutex_unlock(&philo->mtx_meal.mtx);
	ft_usleep(philo->data, philo->data->time_eat);
	if (philo->data->num_meals > 0 && !check_stop(philo->data))
	{
		pthread_mutex_lock(&philo->mtx_meal.mtx);
		philo->meals_eaten++;
		if (philo->data->num_meals != -1 && philo->meals_eaten >= philo->data->num_meals)
			philo->full = 1;
		else
			philo->full = 0;
		pthread_mutex_unlock(&philo->mtx_meal.mtx);
	}
}

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(&philo->fork_one->mtx);
		safe_print(philo, "has taken a fork");
		pthread_mutex_lock(&philo->fork_two->mtx);
		safe_print(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->fork_two->mtx);
		safe_print(philo, "has taken a fork");
		pthread_mutex_lock(&philo->fork_one->mtx);
		safe_print(philo, "has taken a fork");
	}
}

void	release_forks(t_philo *philo)
{
	if (philo->id % 2 == 1)
	{
		pthread_mutex_unlock(&philo->fork_two->mtx);
		pthread_mutex_unlock(&philo->fork_one->mtx);
	}
	else
	{
		pthread_mutex_unlock(&philo->fork_one->mtx);
		pthread_mutex_unlock(&philo->fork_two->mtx);
	}
}
