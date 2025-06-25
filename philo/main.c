/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 22:05:14 by dvavryn           #+#    #+#             */
/*   Updated: 2025/06/25 22:31:35 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
	Here are the key things you need to know to succeed in this assignment:
	
		One or more philosophers sit at a round table.
		There is a large bowl of spaghetti in the middle of the table.

		The philosophers take turns eating, thinking and sleeping.
		While they are eating, they are not thinking nor sleeping;
		while thinking, they are not eating nor sleeping;
		and, of course, while sleeping, they are nor eating nor thinking.

		There are also forks on the table. There are as many forks as philosophers.
		
		Since eating spaghetti with just one fork is impractical, a philosopher
		must pick up both the fork to their right and the fork to their left
		before eating.

		When a philosopher has finished eating, they put their forks back on the
		table and start sleeping. Once awake, they start thinking again, The
		simulation stops when a philosopher dies of starvation.

		Every philosopher needs to eat and should never starve.

		Philosophers do not communicate with each other.

		Philosophers do not know if another philosopher is about to die.

		Needless to say philosophers should avoid dying!



	No Global Variables are allowed!
	
	Arguments:
		nr of philosophers
				The number of philosophers and also the number of forks.
		time to die (in ms)
				If a philosopher has not started eating within time to
				die ms since the start of their last meas or the start
				of the simulation they die
		time to eat (in ms)
				The time it takes for a philosopher to eat. During that
				time, they will need to hold two forks.
		time to sleep (in ms)
				The time a philosopher will spend sleeping.
		number of times each philosopher must eat (optional argument)
				If all philosophers have eaten at least number of times
				each philosopher must eat times, the simulation stops.
				If not specified the simulation stops when a philosopher
				dies.
	
	Each philosopher has a number ranging from 1 to number of philosophers

	Philosopher number 1 sits next to philosopher number number of philosophers.
	Any other philosopher, numbered N, sits between philo N -1 and philo N +1.

	About the logs of your program:
	Any state change of a philosopher must be formatted as follows:
		timestamp_in_ms X has taken a fork
		timestamp_in_ms X is eating
		timestamp_in_ms X is sleeping
		timestamp_in_ms X is thinking
		timestamp_in_ms X died
	
	A displayed state message should not overlap with another message.

	A message announcing a philosophers death must be displayed within 10 ms
	of their actual death.

	Again, philosophers should avoid dying.

	!!!!!	Your program must not have any data races.
	*/

int main(void)
{

}