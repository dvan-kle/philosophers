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
			if (philos[i].eat_count >= data->max_eat_times)
				max_ate++;
			if (get_time() - philos[i].last_eat > data->time_to_die)
			{
				pthread_mutex_lock(&data->checking);
				printer(data, philos[i].id, "died", -1);
				data->dead = 1;
				pthread_mutex_unlock(&data->checking);
			}
			pthread_mutex_unlock(&philos[i].eating);
			i++;
		}
		if (data->dead)
			break ;
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
		printer(data, philo->id, "is thinking", -1);
		usleep(15000);
	}
	while (!data->dead)
	{
		philo_eats(philo);
		printer(data, philo->id, "is sleeping", -1);
		sleeping(data->time_to_sleep);
		printer(data, philo->id, "is thinking", -1);
		i++;
	}
	return (NULL);
}

void	philo_eats(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->l_fork]);
	printer(philo->data, philo->id, "has taken a fork", -1);
	pthread_mutex_lock(&philo->data->forks[philo->r_fork]);
	printer(philo->data, philo->id, "has taken a fork", -1);
	pthread_mutex_lock(&philo->eating);
	printer(philo->data, philo->id, "is eating", -1);
	philo->last_eat = get_time();
	sleeping(philo->data->time_to_eat);
	philo->eat_count++;
	if (philo->eat_count == philo->data->max_eat_times)
		philo->data->ate++;
	pthread_mutex_unlock(&philo->data->forks[philo->l_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->r_fork]);
	pthread_mutex_unlock(&philo->eating);
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
