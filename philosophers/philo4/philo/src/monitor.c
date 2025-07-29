#include "philo.h"

void	monitor_philosophers(t_data *data)
{
	while (1)
	{
		for (int i = 0; i < data->nb_philos; i++)
		{
			t_philo *philo = &data->philos[i];

			pthread_mutex_lock(&philo->meal_lock);
			long time_since_meal = get_time() - philo->last_meal_time;
			pthread_mutex_unlock(&philo->meal_lock);

			if (time_since_meal >= data->time_to_die)
			{
				pthread_mutex_lock(&data->death_lock);
				data->someone_died = 1;
				pthread_mutex_unlock(&data->death_lock);

				print_status(philo, "died");
				return ;
			}
		}

		if (data->must_eat_count > 0)
		{
			int full_philos = 0;
			for (int i = 0; i < data->nb_philos; i++)
			{
				t_philo *philo = &data->philos[i];
				pthread_mutex_lock(&philo->meal_lock);
				if (philo->meals_eaten >= data->must_eat_count)
					full_philos++;
				pthread_mutex_unlock(&philo->meal_lock);
			}
			if (full_philos == data->nb_philos)
			{
				pthread_mutex_lock(&data->death_lock);
				data->someone_died = 1;
				pthread_mutex_unlock(&data->death_lock);
				return ;
			}
		}
		custom_usleep(1000, data);
	}
}