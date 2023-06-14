/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-kle <dvan-kle@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 17:39:41 by dvan-kle      #+#    #+#                 */
/*   Updated: 2023/06/15 00:47:15 by dvan-kle      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

void create_philos(t_philo *philo)
{
	pthread_create();
}


int	main(int ac, char **av)
{
	t_philo	philo;
	t_data	data;

	data.starttime = get_time();
	usleep(4000);
	data.currenttime = current_time(data.starttime);
	printf("TIME: %lu\n", data.currenttime);
	ac = 0;
	av = NULL;
	return (0);
}
