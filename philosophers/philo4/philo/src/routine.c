#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*philo = (t_philo *)arg;

	if (philo->id % 2 == 0)
		usleep(1000);

	while (!check_if_someone_died(philo->data))
	{
		// 1. Thinking
		print_status(philo, "is thinking");

		// 2. Take forks
		if (philo->id % 2 == 0)
		{
			pthread_mutex_lock(philo->left_fork);
			print_status(philo, "has taken a fork");
			pthread_mutex_lock(philo->right_fork);
			print_status(philo, "has taken a fork");
		}
		else
		{
			pthread_mutex_lock(philo->right_fork);
			print_status(philo, "has taken a fork");
			pthread_mutex_lock(philo->left_fork);
			print_status(philo, "has taken a fork");
		}

		pthread_mutex_lock(&philo->meal_lock);
		philo->last_meal_time = get_time();
		pthread_mutex_unlock(&philo->meal_lock);

		print_status(philo, "is eating");
		usleep(philo->data->time_to_eat * 1000);

		// increment meals eaten count
		pthread_mutex_lock(&philo->meal_lock);
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->meal_lock);

		// 4. release forks
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);

		// 5. sleping
		print_status(philo, "is sleeping");
		usleep(philo->data->time_to_sleep * 1000);
	}
	return (NULL);
}