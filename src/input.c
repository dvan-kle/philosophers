/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-kle <dvan-kle@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 21:34:30 by dvan-kle      #+#    #+#                 */
/*   Updated: 2023/12/08 16:19:57 by dvan-kle      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

// number_of_philosophers time_to_die time_to_eat time_to_sleep 
// [number_of_times_each_philosopher_must_eat]

static int	check_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= 48 && str[i] <= 57))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	input_check(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac != 5 || ac != 6)
		return (EXIT_FAILURE);
	while (av[i])
	{
		if (check_digits(av[i]))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	assign_data(t_data *data, int ac, char **av)
{
	data->nb_ph = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->max_eat_times = ft_atoi(av[5]);
}
