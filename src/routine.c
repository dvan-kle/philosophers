#include "../incl/philo.h"

// void	*p_thread(void *void_philosopher)
// {
// 	int				i;
// 	t_philosopher	*philo;
// 	t_rules			*rules;

// 	i = 0;
// 	philo = (t_philosopher *)void_philosopher;
// 	rules = philo->rules;
// 	if (philo->id % 2)
// 		usleep(15000);
// 	while (!(rules->dieded))
// 	{
// 		philo_eats(philo);
// 		if (rules->all_ate)
// 			break ;
// 		action_print(rules, philo->id, "is sleeping");
// 		smart_sleep(rules->time_sleep, rules);
// 		action_print(rules, philo->id, "is thinking");
// 		i++;
// 	}
// 	return (NULL);
// }

void	start_routine(t_data *data, t_philo *philos)
{
    int i;

    i = 0;
    while (i < data->nb_ph)
    {
        pthread_create(&philos[i].thread_id, NULL, simulation, (void *)&philos[i]);
        i++;
    }

}

void *simulation(void *arg)
{
    int        i;
    t_philo    *philo;
    t_data     *data;

    i = 0;
    philo = (t_philo *)arg;
    data = philo->data;
    if (philo->id % 2)
        usleep(15000);
    while (i < 3)
    {
        philo_eats(philo);
        dprintf(2, "lekker gegeten\n");
        printer(data, philo->id, "is sleeping");
        sleeping(data->time_to_sleep);
        printer(data, philo->id, "is thinking");
        i++;
    }
    return (NULL);
}

void philo_eats(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->forks[philo->l_fork]);
    printer(philo->data, philo->id, "has taken a fork");
    pthread_mutex_lock(&philo->data->forks[philo->r_fork]);
    printer(philo->data, philo->id, "has taken a fork");
    printer(philo->data, philo->id, "is eating");
    philo->last_eat = get_time();
    sleep(1000);
    pthread_mutex_unlock(&philo->data->forks[philo->l_fork]);
    pthread_mutex_unlock(&philo->data->forks[philo->r_fork]);
    philo->eat_count++;
}

void exit_threads(t_philo *philos, t_data *data)
{
    int	i;

    i = 0;
    while (i < data->nb_ph)
    {
        pthread_join(philos[i].thread_id, NULL);
        i++;
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