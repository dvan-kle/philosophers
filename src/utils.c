/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-kle <dvan-kle@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/15 00:21:46 by dvan-kle      #+#    #+#                 */
/*   Updated: 2023/12/13 18:11:29 by dvan-kle      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

int	ft_atoi(const char *str)
{
	int			i;
	int			minplus;
	int			result;

	i = 0;
	minplus = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			minplus = -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - 48);
		i++;
	}
	return (result * minplus);
}

void	printer(t_data *data, int id, char *str)
{
	pthread_mutex_lock(&data->output);
	printf("%lu %d %s\n", current_time(data->starttime), id + 1, str);
	pthread_mutex_unlock(&data->output);
}
