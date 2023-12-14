/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-kle <dvan-kle@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/13 18:12:44 by dvan-kle      #+#    #+#                 */
/*   Updated: 2023/12/13 18:12:45 by dvan-kle      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

void	check_death(t_data *data, t_philo *philos)
{
	int	i;
	int	max_ate;

	max_ate = 0;
	while (max_ate < data->nb_ph)
	{
		i = 0;
		while (i < data->nb_ph && !data->dead)
		{
			pthread_mutex_lock(&philos[i].eating);
			if (get_time() - philos[i].last_eat > data->time_to_die)
			{
				pthread_mutex_lock(&data->checking);
				printer(data, philos[i].id, "died", LOCK);
				data->dead = 1;
				pthread_mutex_unlock(&data->checking);
			}
			if (philos[i].eat_count == data->max_eat_times)
				max_ate++;
			pthread_mutex_unlock(&philos[i].eating);
			i++;
		}
		pthread_mutex_lock(&data->checking);
		if (data->dead)
			break ;
		pthread_mutex_unlock(&data->checking);
	}
}

void	start_routine(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->nb_ph)
	{
		pthread_create(&philos[i].thread_id, NULL, simulation,
			(void *)&philos[i]);
		i++;
	}
	check_death(data, philos);
}

void	*simulation(void *arg)
{
	int		i;
	t_philo	*philo;
	t_data	*data;

	i = 0;
	philo = (t_philo *)arg;
	data = philo->data;
	if (philo->id % 2)
	{
		printer(data, philo->id, "is thinking", UNLOCK);
		usleep(20000);
	}
	pthread_mutex_lock(&data->checking);
	while (!data->dead)
	{
		pthread_mutex_unlock(&data->checking);
		philo_eats(philo);
		if (philo->eat_count == philo->data->max_eat_times)
			break ;
		printer(data, philo->id, "is sleeping", UNLOCK);
		sleeping(data->time_to_sleep, data);
		printer(data, philo->id, "is thinking", UNLOCK);
		i++;
		pthread_mutex_lock(&data->checking);
	}
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
	sleeping(philo->data->time_to_eat, philo->data);
	philo->eat_count++;
	if (philo->eat_count == philo->data->max_eat_times)
		philo->data->ate++;
	pthread_mutex_unlock(&philo->eating);
	pthread_mutex_unlock(&philo->data->forks[philo->r_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->l_fork]);
}

void	exit_threads(t_philo *philos, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_ph)
	{
		pthread_join(philos[i].thread_id, NULL);
		i++;
		pthread_mutex_destroy(&philos[i].eating);
	}
	i = 0;
	while (i < data->nb_ph)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->output);
	pthread_mutex_destroy(&data->checking);
}
