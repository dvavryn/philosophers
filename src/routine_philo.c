/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 01:16:26 by dvavryn           #+#    #+#             */
/*   Updated: 2025/08/05 19:52:29 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	routine_philo_solo(t_philo *philo);
void	routine_philo_even(t_philo *philo);
void	routine_philo_odd(t_philo *philo);
void	grab_forks(t_philo *philo);
void	release_forks(t_philo *philo);
static int		check_death(t_philo *philo);

void	*routine_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->num_philos == 1)
		routine_philo_solo(philo);
	else if (philo->data->num_philos % 2 == 0)
		routine_philo_even(philo);
	else if (philo->data->num_philos % 2 == 1)
		routine_philo_odd(philo);
	return (NULL);
}

void	routine_philo_solo(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_one->mtx);
	safe_print(philo, "has taken a fork");
	ft_usleep(philo->data, philo->data->time_die);
	
}

void	routine_philo_even(t_philo *philo)
{
	int meals;

	meals = 0;
	while (meals != philo->data->num_meals && !check_death(philo))
	{
		if (philo->id % 2 == 0)
			safe_print(philo, "is thinking");
		grab_forks(philo);
		pthread_mutex_lock(&philo->mtx_meal.mtx);
		philo->meals_eaten++;
		get_time_ms(&philo->last_meal);
		meals++;
		pthread_mutex_unlock(&philo->mtx_meal.mtx);
		safe_print(philo, "is eating");
		ft_usleep(philo->data, philo->data->time_sleep);
		release_forks(philo);
		if (meals == philo->data->num_meals)
		{
			pthread_mutex_lock(&philo->mtx_meal.mtx);
			philo->full = 1;
			pthread_mutex_unlock(&philo->mtx_meal.mtx);
			break ;
		}
		safe_print(philo, "is sleeping");
		ft_usleep(philo->data, philo->data->time_sleep);
		if (philo->id % 2 == 1)
			safe_print(philo, "is thinking");
	}
}

void	routine_philo_odd(t_philo *philo)
{
	int meals;

	meals = 0;
	while (meals != philo->data->num_meals && !check_death(philo))
	{
		if (philo->id % 2 == 0)
			safe_print(philo, "is thinking");
		grab_forks(philo);
		pthread_mutex_lock(&philo->mtx_meal.mtx);
		philo->meals_eaten++;
		get_time_ms(&philo->last_meal);
		meals++;
		pthread_mutex_unlock(&philo->mtx_meal.mtx);
		safe_print(philo, "is eating");
		ft_usleep(philo->data, philo->data->time_sleep);
		release_forks(philo);
		if (meals == philo->data->num_meals)
		{
			pthread_mutex_lock(&philo->mtx_meal.mtx);
			philo->full = 1;
			pthread_mutex_unlock(&philo->mtx_meal.mtx);
			break ;
		}
		safe_print(philo, "is sleeping");
		ft_usleep(philo->data, philo->data->time_sleep);
		if (philo->id % 2 == 1)
			safe_print(philo, "is thinking");
	}
}

void	grab_forks(t_philo *philo)
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

static int check_death(t_philo *philo)
{
	int	ret;

	pthread_mutex_lock(&philo->data->mtx_death.mtx);
	ret = philo->data->death_flag;
	pthread_mutex_unlock(&philo->data->mtx_death.mtx);
	return (ret);
}