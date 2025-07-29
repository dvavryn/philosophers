#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	print_status(t_philo *philo, char *msg)
{
	long	timestamp;

	pthread_mutex_lock(&philo->data->print_lock);
	if (!check_if_someone_died(philo->data) || !strcmp(msg, "died"))
	{
		timestamp = get_time() - philo->data->start_time;
		printf("%ld %d %s\n", timestamp, philo->id, msg);
	}
	pthread_mutex_unlock(&philo->data->print_lock);
}

int	check_if_someone_died(t_data *data)
{
	int dead;

	pthread_mutex_lock(&data->death_lock);
	dead = data->someone_died;
	pthread_mutex_unlock(&data->death_lock);
	return (dead);
}

void	custom_usleep(long ms, t_data *data)
{
	long start = get_time();

	while (!check_if_someone_died(data))
	{
		if (get_time() - start >= ms)
			break ;
		usleep(100);
	}
}