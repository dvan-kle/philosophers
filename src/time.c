/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-kle <dvan-kle@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 22:20:13 by dvan-kle      #+#    #+#                 */
/*   Updated: 2024/02/05 17:51:17 by dvan-kle      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

void	sleeping(int time)
{
	unsigned long	start;

	start = get_time();
	while ((get_time() - start) < (unsigned long)time)
		usleep(150);
}

unsigned long	get_time(void)
{
	struct timeval	timevals;

	gettimeofday(&timevals, NULL);
	return ((timevals.tv_usec / 1000) + (timevals.tv_sec * 1000));
}

unsigned long	current_time(unsigned long starttime)
{
	return ((get_time() - starttime));
}
