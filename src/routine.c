/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-kle <dvan-kle@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/13 18:12:44 by dvan-kle      #+#    #+#                 */
/*   Updated: 2024/01/19 17:17:36 by dvan-kle      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

void	start_routine(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->nb_ph)
	{
		philos[i].last_eat = get_time();
		pthread_create(&philos[i].thread_id, NULL, simulation,
			(void *)&philos[i]);
		i++;
	}
	check_death(data, philos);
	if (data->dead)
		pthread_mutex_unlock(&data->output);
	exit_threads(philos, data);
}

void	*simulation(void *arg)
{
	int		i;
	t_philo	*philo;
	t_data	*data;

	i = 0;
	philo = (t_philo *)arg;
	data = philo->data;
	if (philo->id % 2 && data->nb_ph > 1)
	{
		printer(data, philo->id, "is thinking", UNLOCK);
		usleep(2000);
	}
	pthread_mutex_lock(&data->checking);
	while (!data->dead && !data->ate)
	{
		pthread_mutex_unlock(&data->checking);
		philo_eats(philo);
		printer(data, philo->id, "is sleeping", UNLOCK);
		sleeping(data->time_to_sleep, data);
		printer(data, philo->id, "is thinking", UNLOCK);
		i++;
		pthread_mutex_lock(&data->checking);
	}
	pthread_mutex_unlock(&data->checking);
	return (NULL);
}

void	philo_eats(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->l_fork]);
	printer(philo->data, philo->id, "has taken a fork", UNLOCK);
	pthread_mutex_lock(&philo->data->forks[philo->r_fork]);
	printer(philo->data, philo->id, "has taken a fork", UNLOCK);
	pthread_mutex_lock(&philo->eating);
	printer(philo->data, philo->id, "is eating", UNLOCK);
	philo->last_eat = get_time();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->eating);
	sleeping(philo->data->time_to_eat, philo->data);
	pthread_mutex_unlock(&philo->data->forks[philo->l_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->r_fork]);
}

void	exit_threads(t_philo *philos, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_ph)
	{
		pthread_join(philos[i].thread_id, NULL);
		pthread_mutex_destroy(&philos[i].eating);
		i++;
	}
	i = -1;
	while (++i < data->nb_ph)
		pthread_mutex_destroy(&data->forks[i]);
	pthread_mutex_destroy(&data->output);
	pthread_mutex_destroy(&data->checking);
	free(philos);
	free(data->forks);
}
