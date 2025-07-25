#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <limits.h>
#include <stdbool.h>

typedef pthread_mutex_t t_mtx;
typedef struct s_config t_config;

typedef struct s_philo
{
	int			id;
	long		last_meal;
	int			meals_consumed;
	pthread_t	thread;
	t_mtx		*left_fork;
	t_mtx		*right_fork;
	t_config	*config;
	bool		dead;
}	t_philo;

struct	s_config
{
	int				num_philos;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	int				num_meals;
	int				sim_ended;
	t_mtx			*forks;
	t_mtx			print;
	struct timeval	start;
	t_philo			*philo;
};

int		check_input(int argc, char **argv);
long	ft_atol(const char *nptr);
void	convert_args(t_config *config, char **argv);
void	destroy_config(t_config *config, int num_mtx);
int		populate_config(t_config *config, char **argv);
void	populate_philos(t_config *config);
long	conv_time(struct timeval time);
int		lock_print(const char *s, t_philo *philo);
void	*routine_philo(void *data);
int		start_sim(t_config *config);

void	*routine_monitor(void *data)
{
	t_config		*config;
	struct timeval cur;
	ssize_t	i;
	t_philo	*ptr;
	int fin_philos;

	config = (t_config *)data;
	while (!config->sim_ended)
	{
		i = -1;
		fin_philos = 0;
		while (++i < config->num_philos)
		{
			ptr = &config->philo[i];
			gettimeofday(&cur, NULL);
			if (config->time_die <= conv_time(cur) - ptr->last_meal)
			{	
				lock_print("has died", ptr);
				ptr->dead = true;
				config->sim_ended = true;
				break;
			}
			if (ptr->meals_consumed == config->num_meals && config->num_meals != -1)
				fin_philos++;
		}
		if (fin_philos == config->num_philos)
		{
			config->sim_ended = true;
			break;
		}
		usleep(300);
	}
	return (NULL);
}

int main(int argc, char **argv)
{
	t_config config;

	if (check_input(argc, argv))
		return (1);
	if (populate_config(&config, argv))
		return (1);
	populate_philos(&config);
	if (start_sim(&config))
		return (1);
	destroy_config(&config, config.num_philos);
	return (0);
}

int check_input(int argc, char **argv)
{
	size_t	i;
	ssize_t	j;
	long	d;

	if (argc != 5 && argc != 6)
		return (1);
	i = 0;
	while (++i < (unsigned int) argc)
	{
		j = -1;
		while (argv[i][++j])
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				return (printf("There are non numerical characters in the argument!\n"), 1);
		}
		d = ft_atol(argv[i]);
		if (d <= 0)
			return (printf("Argument has to be over 0\n"), 1);
		else if (d > INT_MAX)
			return (printf("Argument has to be under INT_MAX\n"), 1);
	}	
	return (0);
}

long	ft_atol(const char *nptr)
{
	long	out;
	long	sign;
	size_t	i;

	out = 0;
	sign = 1;
	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		out = out * 10 + (nptr[i] - '0');
		i++;
	}
	return (out * sign);
}

void	convert_args(t_config *config, char **argv)
{
	config->num_philos = (int)ft_atol(argv[1]);
	config->time_die = ft_atol(argv[2]);
	config->time_eat = ft_atol(argv[3]);
	config->time_sleep = ft_atol(argv[4]);
	if (argv[5])
		config->num_meals = (int)ft_atol(argv[5]);
	else
		config->num_meals = -1;
}

void	destroy_config(t_config *config, int num_mtx)
{
	ssize_t	i;

	pthread_mutex_destroy(&config->print);
	i = -1;
	while (++i < num_mtx)
		pthread_mutex_destroy(&config->forks[i]);
	if (config->forks)
		free(config->forks);
	if (config->philo)
		free(config->philo);
}

int	populate_config(t_config *config, char **argv)
{
	ssize_t	i;

	memset(config, 0, sizeof(t_config));
	convert_args(config, argv);;
	i = -1;
	if (gettimeofday(&config->start, NULL) == -1)
		return (printf("gettimeofday failed\n"),1);
	config->forks = malloc(config->num_philos * sizeof(t_mtx));
	if (!config->forks)
		return (printf("Malloc forks failed\n"),destroy_config(config, i),1);
	while (++i < config->num_philos)
	{
		if (pthread_mutex_init(&config->forks[i], NULL) == -1)
			return (printf("mutex init fork %zi failed\n",i),1);
	}
	if (pthread_mutex_init(&config->print, NULL) == -1)
		return (printf("mutex init print failed\n"),1);
	config->philo = malloc(config->num_philos * sizeof(t_philo));
	if (!config->philo)
		return (printf("Malloc philo failed\n"),destroy_config(config, i),1);
	config->sim_ended = false;
	return (0);
}

void	populate_philos(t_config *config)
{
	ssize_t	i;
	t_philo	*ptr;

	i = -1;
	while (++i < config->num_philos)
	{
		ptr = &config->philo[i];

		ptr->right_fork = &config->forks[i];
		ptr->left_fork = &config->forks[(i + 1) % config->num_philos];
		ptr->id = i + 1;
		ptr->meals_consumed = 0;
		ptr->config = config;
		ptr->dead = false;
	}
}

long	conv_time(struct timeval time)
{
	long out;

	out = 0;
	out += time.tv_sec * 1000;
	out += time.tv_usec / 1000;
	return (out);
}

int	lock_print(const char *s, t_philo *philo)
{
	struct timeval	cur;
	long			timestamp;

	if (gettimeofday(&cur, NULL) == -1)
		return (-1);
	timestamp = conv_time(cur) - conv_time(philo->config->start);
	pthread_mutex_lock(&philo->config->print);
	printf("%ld ms %d %s\n", timestamp, philo->id, s);
	pthread_mutex_unlock(&philo->config->print);
	return (0);
}

void	*routine_philo(void *data)
{
	t_philo	*philo;
	struct timeval cur;

	philo = (t_philo *)data;
	philo->last_meal = conv_time(philo->config->start);
	while (!philo->dead && !philo->config->sim_ended)
	{
		lock_print("is thinking", philo);
		if (philo->id % 2 == 1)
		{
			pthread_mutex_lock(philo->left_fork);
			lock_print("has taken a fork", philo);
			pthread_mutex_lock(philo->right_fork);
			lock_print("has taken a fork", philo);
			lock_print("is eating", philo);
			usleep(philo->config->time_eat * 1000);
			lock_print("has finished eating", philo);
			pthread_mutex_unlock(philo->right_fork);
			pthread_mutex_unlock(philo->left_fork);
		}
		else
		{
			pthread_mutex_lock(philo->right_fork);
			lock_print("has taken a fork", philo);
			pthread_mutex_lock(philo->left_fork);
			lock_print("has taken a fork", philo);
			lock_print("is eating", philo);
			usleep(philo->config->time_eat * 1000);
			lock_print("has finished eating", philo);
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
		}
		gettimeofday(&cur, NULL);
		philo->last_meal = conv_time(cur);
		philo->meals_consumed++;
		if (philo->meals_consumed == philo->config->num_meals)
			break ;
		lock_print("is sleeping", philo);
		usleep(philo->config->time_sleep * 1000);
	}
	return (NULL);
}

int start_sim(t_config *config)
{
	ssize_t	i;
	pthread_t	monitor;

	i = -1;
	while (++i < config->num_philos)
	{
		if (pthread_create(&config->philo[i].thread, NULL, &routine_philo,&config->philo[i]))
			return (printf("thread create failed philo[%zi]\n", i), 1);
	}
	if (pthread_create(&monitor, NULL, &routine_monitor, config))
		return (printf("thread create failed monitor\n"), 1);
	if (pthread_join(monitor, NULL))
		return (printf("thread join failed monitor\n"), 1);
	i = -1;
	while (++i < config->num_philos)
	{
		if (pthread_join(config->philo[i].thread, NULL))
			return (printf("thread join failed philo[%zi]\n", i), 1);
	}
	return (0);
}