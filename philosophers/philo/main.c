/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 12:42:24 by dvavryn           #+#    #+#             */
/*   Updated: 2025/07/25 13:16:47 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_config	config;

	if (check_input(argc, argv))
		return (1);
	if (populate_config(&config, argv))
		return (1);
	populate_philos(&config);
	if (start_sim(&config))
		return (1);
	printf(">>%i<<\n", config.sim_started);
	destroy_config(&config, config.num_philos);
	return (0);
}
