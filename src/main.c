/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-kle <dvan-kle@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 17:39:41 by dvan-kle      #+#    #+#                 */
/*   Updated: 2023/06/15 00:16:48 by dvan-kle      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

int	main(int ac, char **av)
{
	t_philo	philo;

	philo.data.starttime = get_time();
	usleep(4000);
	philo.data.currenttime = current_time(philo.data.starttime);
	printf("TIME: %lu\n", philo.data.currenttime);
	ac = 0;
	av = NULL;
	return (0);
}
