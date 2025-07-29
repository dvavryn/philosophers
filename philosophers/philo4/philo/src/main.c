#include "philo.h"

int main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
	{
		printf("Usage: ./philo num_philos time_to_die time_to_eat time_to_sleep [num_must_eat]\n");
		return (1);
	}
	if (init_data(&data, argc, argv) != 0)
		return (1);
	if (init_philosophers(&data) != 0)
		return (1);
	data.start_time = get_time();

	for (int i = 0; i < data.nb_philos; i++)
	{
		t_philo *philo = &data.philos[i];
		philo->last_meal_time = data.start_time;

		if (pthread_create(&philo->thread, NULL, &routine, philo) != 0)
		{
			printf("Failed to create thread for Philosopher %d\n", philo->id);
			return (1);
		}
	}

	monitor_philosophers(&data);

	for (int i = 0; i < data.nb_philos; i++)
		pthread_join(data.philos[i].thread, NULL);

	for (int i = 0; i < data.nb_philos; i++)
	{
		pthread_mutex_destroy(&data.forks[i]);
		pthread_mutex_destroy(&data.philos[i].meal_lock);
	}
	pthread_mutex_destroy(&data.print_lock);
	pthread_mutex_destroy(&data.death_lock);
	free(data.forks);
	free(data.philos);

	return (0);
}