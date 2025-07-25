#include "philo.h"


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

