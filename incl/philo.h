/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-kle <dvan-kle@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 21:10:39 by dvan-kle      #+#    #+#                 */
/*   Updated: 2023/06/15 00:45:40 by dvan-kle      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include<unistd.h>

typedef struct s_data {
	int				nb_ph;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_eat_times;
	unsigned long	starttime;
	unsigned long	currenttime;
}	t_data;

typedef struct s_philo {
	int	zero;
}	t_philo;

unsigned long	get_time(void);
unsigned long	current_time(unsigned long starttime);
int				ft_atoi(const char *str);

#endif