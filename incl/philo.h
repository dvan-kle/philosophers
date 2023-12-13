/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-kle <dvan-kle@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 21:10:39 by dvan-kle      #+#    #+#                 */
/*   Updated: 2023/12/13 18:08:45 by dvan-kle      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data {
	int				nb_ph;
	unsigned long	time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_eat_times;
	unsigned long	starttime;
	struct s_philo	*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	output;
	pthread_mutex_t	checking;
	int				dead;
	int				ate;
}	t_data;

typedef struct s_philo {
	pthread_t		thread_id;
	int				id;
	unsigned long	last_eat;
	int				eat_count;
	int				l_fork;
	int				r_fork;
	pthread_mutex_t	eating;
	t_data			*data;
}	t_philo;

unsigned long	get_time(void);
unsigned long	current_time(unsigned long starttime);
void			assign_data(t_data *data, int ac, char **av);
int				ft_atoi(const char *str);
int				input_check(int ac, char **av);
void			start_routine(t_data *data, t_philo *philos);
void			exit_threads(t_philo *philos, t_data *data);
void			sleeping(int time);
void			philo_eats(t_philo *philo);
void			printer(t_data *data, int id, char *str, int tid);
void			*simulation(void *arg);
#endif