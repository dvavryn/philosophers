#include "philo.h"

int init_data(t_data *data, int argc, char **argv)
{
	data->nb_philos = atoi(argv[1]);
	data->time_to_die = atol(argv[2]);
	data->time_to_eat = atol(argv[3]);
	data->time_to_sleep = atol(argv[4]);
	data->must_eat_count = (argc == 6) ? atoi(argv[5]) : -1;

	if (data->nb_philos <= 0
		|| data->time_to_die <= 0
		|| data->time_to_eat <= 0
		|| data->time_to_sleep <= 0
		|| (argc == 6 && data->must_eat_count <= 0))
		return (1);
	data->someone_died = 0;
	data->start_time = 0;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
	data->philos = malloc(sizeof(t_philo) * data->nb_philos);
	if (!data->forks || !data->philos)
		return (1);

	for (int i = 0; i < data->nb_philos; i++)
		pthread_mutex_init(&data->forks[i], NULL);
	pthread_mutex_init(&data->print_lock, NULL);
	pthread_mutex_init(&data->death_lock, NULL);
	return (0);
}

int init_philosophers(t_data *data)
{
	for (int i = 0; i < data->nb_philos; i++)
	{
		t_philo	*philo = &data->philos[i];
		
		philo->id = i + 1;
		philo->meals_eaten = 0;
		philo->last_meal_time = 0;
		philo->left_fork = &data->forks[i];
		philo->right_fork = &data->forks[(i + 1) % data->nb_philos];
		philo->data = data;

		if (pthread_mutex_init(&philo->meal_lock, NULL) != 0)
			return (1);
		}
	return (0);
}
