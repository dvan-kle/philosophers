/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-kle <dvan-kle@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 17:39:41 by dvan-kle      #+#    #+#                 */
/*   Updated: 2023/10/14 19:07:30 by danielvankl   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

// void	create_philos(t_philo *philo)
// {
// 	pthread_create();
// }

int	ft_isdigit(int c)
{
	if (!(c >= 48 && c <= 57))
	{
		return (0);
	}
	return (1);
}

static int	check_digits(char *str)
{
	int	i;

	i = 0;
	if ((str[0] == '-' && str[1] == '\0') || str[0] == '+')
		return (0);
	if (str[0] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_input(char *str)
{
	int	nb;

	if (!check_digits(str))
		return (-1);
	nb = ft_atoi(str);
	return (nb);
}

int	get_data(int ac, char **av, t_data *data)
{
	if (input_check(ac, av))
		return (EXIT_FAILURE);
	assign_data(data, ac, av);
	return (0);
}

int	main(int ac, char **av)
{
	//t_philo	philo;
	t_data	*data;

	data = malloc(sizeof(t_data *));
	if (get_data(ac, av, data) == EXIT_FAILURE)
		return (printf("Error\n"), 1);
	usleep(4000);
	data->currenttime = current_time(data->starttime);
	printf("TIME: %lu\n", data->currenttime);
	return (0);
}
 // ./philo nb_ph time_to_die time_to_eat time_to_sleep max_eat