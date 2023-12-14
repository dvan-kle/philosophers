/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-kle <dvan-kle@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 17:39:41 by dvan-kle      #+#    #+#                 */
/*   Updated: 2023/12/13 18:14:04 by dvan-kle      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

void	sleeping(int time, t_data *data)
{
	usleep(time * 1000);
}

void	create_philos(t_data *data)
{
	t_philo	*philos;
	int		i;

	i = 0;
	philos = malloc(sizeof(t_philo) * data->nb_ph);
	while (i < data->nb_ph)
	{
		philos[i].id = i;
		philos[i].eat_count = 0;
		philos[i].l_fork = i;
		philos[i].r_fork = (i + 1) % data->nb_ph;
		philos[i].data = data;
		philos[i].last_eat = data->starttime;
		pthread_mutex_init(&philos[i].eating, NULL);
		i++;
	}
	data->philos = philos;
}

int	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_ph);
	if (!data->forks)
		return (EXIT_FAILURE);
	while (i < data->nb_ph)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (EXIT_FAILURE);
		i++;
	}
	if (pthread_mutex_init(&data->output, NULL))
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&data->checking, NULL))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (input_check(ac, av))
		return (EXIT_FAILURE);
	assign_data(&data, ac, av);
	if (init_mutex(&data))
		return (EXIT_FAILURE);
	create_philos(&data);
	start_routine(&data, data.philos);
	exit_threads(data.philos, &data);
	return (0);
}

/* void	print_data(t_data *data)
{
	printf("nb_ph: %d\n", data->nb_ph);
	printf("time_to_die: %d\n", data->time_to_die);
	printf("time_to_eat: %d\n", data->time_to_eat);
	printf("time_to_sleep: %d\n", data->time_to_sleep);
	printf("max_eat_times: %d\n", data->max_eat_times);
}

void	print_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_ph)
	{
		printf("id: %d\n", data->philos[i].id);
		printf("eat_count: %d\n", data->philos[i].eat_count);
		printf("l_fork: %d\n", data->philos[i].l_fork);
		printf("r_fork: %d\n", data->philos[i].r_fork);
		printf("last_eat: %lu\n", data->philos[i].last_eat);
		i++;
	}
} */
