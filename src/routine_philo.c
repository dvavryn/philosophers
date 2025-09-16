/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 01:16:26 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/16 17:33:55 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	single_philo(t_philo *philo);
void	odd_amount_philos(t_philo *philo);
void	even_amount_philos(t_philo *philo);

void	*routine_philo(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (philo->data->num_philos == 1)
		single_philo(philo);
	else if (philo->data->num_philos % 2 == 0)
		even_amount_philos(philo);
	else if (philo->data->num_philos % 2 == 1)
		odd_amount_philos(philo);
	return (NULL);
}

void	single_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_one->mtx);
	safe_print(philo, "has taken a fork");
	usleep(philo->data->time_die * 1000);
	safe_print(philo, "died");
	pthread_mutex_unlock(&philo->fork_one->mtx);
}

void	philo_think(t_philo *philo)
{
	safe_print(philo, "is thinking");
}

void	philo_sleep(t_philo *philo)
{
	safe_print(philo, "is sleeping");
	ft_usleep(philo->data, philo->data->time_sleep);
}

void	even_philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_one->mtx);
	safe_print(philo, "has taken a fork");	
	pthread_mutex_lock(&philo->fork_two->mtx);
	safe_print(philo, "has taken a fork");
	safe_print(philo, "is eating");
	ft_usleep(philo->data, philo->data->time_eat);
	pthread_mutex_lock(&philo->mtx_meal.mtx);
	philo->meals_eaten++;
	if (philo->meals_eaten == philo->data->num_meals)
		philo->full = 1;
	philo->last_meal = get_time_ms();
	pthread_mutex_unlock(&philo->mtx_meal.mtx);
	pthread_mutex_unlock(&philo->fork_one->mtx);
	pthread_mutex_unlock(&philo->fork_two->mtx);
}

void	even_amount_philos(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		philo_think(philo);
		ft_usleep(philo->data, philo->data->time_eat / 2);
	}
	while (!philo->data->sim_ended)
	{
		even_philo_eat(philo);
		if (philo->full == 1)
			break ;
		philo_sleep(philo);
		philo_think(philo);
	}
}



void	odd_philo_eat_even(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_one->mtx);
	safe_print(philo, "has taken a fork");
	pthread_mutex_lock(&philo->fork_two->mtx);
	safe_print(philo, "has taken a fork");
	safe_print(philo, "is eating");
	ft_usleep(philo->data, philo->data->time_eat);
	pthread_mutex_lock(&philo->mtx_meal.mtx);
	philo->meals_eaten++;
	if (philo->meals_eaten == philo->data->num_meals)
		philo->full = 1;
	philo->last_meal = get_time_ms();
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
	ft_usleep(philo->data, philo->data->time_eat);
	pthread_mutex_lock(&philo->mtx_meal.mtx);
	philo->meals_eaten++;
	if (philo->meals_eaten == philo->data->num_meals)
		philo->full = 1;
	philo->last_meal = get_time_ms();
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
	while (!philo->data->sim_ended)
	{
		if (philo->id % 2 == 0)
			odd_philo_eat_even(philo);
		else
			odd_philo_eat_odd(philo);
		if (philo->full == 1)
			break ;
		philo_sleep(philo);
		philo_think(philo);
	}
}
