/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   death.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-kle <dvan-kle@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/19 16:34:13 by dvan-kle      #+#    #+#                 */
/*   Updated: 2024/02/09 17:47:16 by dvan-kle      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

static void	died(t_philo *philos, t_data *data, int i)
{
	printer(data, philos[i].id, "died", LOCK);
	pthread_mutex_lock(&data->checking);
	data->dead = 1;
	pthread_mutex_unlock(&data->checking);
	pthread_mutex_unlock(&philos[i].eating);
}

static void	check_ate(t_data *data, int max_ate)
{
	//int		i;
	//t_philo	*philos;

	//i = 0;
	//philos = data->philos;
	// pthread_mutex_lock(&philos[i].eating);
	// while (i < data->nb_ph && philos[i].eat_count == data->max_eat_times)
	// {
	// 	// pthread_mutex_unlock(&philos[i].eating);
	// 	i++;
	// 	// pthread_mutex_lock(&philos[i].eating);
	// }
	// pthread_mutex_unlock(&philos[i].eating);
	data->ate = (max_ate == data->nb_ph);
	pthread_mutex_unlock(&data->checking);
}

static int	if_died(t_data *data)
{
	pthread_mutex_lock(&data->checking);
	if (data->dead)
	{
		pthread_mutex_unlock(&data->checking);
		return (1);
	}
	return (0);
}

void	check_death(t_data *data, t_philo *philos)
{
	int	i;
	int	max_ate;

	max_ate = 0;
	while (!data->ate)
	{
		i = -1;
		while (++i < data->nb_ph && !data->dead)
		{
			pthread_mutex_lock(&philos[i].eating);
			if (get_time() - philos[i].last_eat >= data->time_to_die)
			{
				died(philos, data, i);
				break ;
			}
			if (philos[i].eat_count == data->max_eat_times)
				max_ate++;
			pthread_mutex_unlock(&philos[i].eating);
		}
		if (if_died(data))
			break ;
		check_ate(data, max_ate);
	}
}
