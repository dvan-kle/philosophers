/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-kle <dvan-kle@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 22:20:13 by dvan-kle      #+#    #+#                 */
/*   Updated: 2023/06/15 00:11:36 by dvan-kle      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

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
