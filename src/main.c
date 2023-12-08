/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-kle <dvan-kle@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 17:39:41 by dvan-kle      #+#    #+#                 */
/*   Updated: 2023/12/08 16:40:17 by dvan-kle      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

void	sleeping(int time)
{
	int	i;

	i = 0;
	while (i < time)
	{
		usleep(250);
		i++;
	}
}

void	*start_routine(void *data)
{
	sleep(1);
	data = NULL;
	return (data);
}

void	create_philos(t_data *data)
{
	t_philo		*philos;
	int			i;

	i = 0;
	philos = malloc(sizeof(t_philo) * data->nb_ph);
	data->philos = philos;
	while (i < data->nb_ph)
	{
		philos[i].id = i;
		philos[i].eat_count = 0;
		philos[i].l_fork = i;
		philos[i].r_fork = (i + 1) % data->nb_ph;
		philos[i].data = data;
		philos[i].last_eat = data->starttime;
		//pthread_create(&philos[i].thread_id, NULL, start_routine, (void *)data);
		i++;
	}
}

void	init_forks(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_ph);
	while (i < data->nb_ph)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_data	data;

	assign_data(&data, ac, av);
	init_forks(&data);
	create_philos(&data);
	printf("philo: %d\n", data.philos[0].id + 1);
	return (0);
}
