/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 01:16:26 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/18 15:52:43 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	single_philo(t_philo *philo);


void	*routine_philo(void *arg)
{
	t_philo	*philo;

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
