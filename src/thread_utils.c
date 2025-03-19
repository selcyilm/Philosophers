#include "../include/philo.h"

bool	is_philo_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock);
	if (philo->is_alive == false)
	{
		pthread_mutex_unlock(&philo->lock);
		return (true);
	}
	if (get_current_time() - philo->last_meal_time >= philo->table->time_to_die)
	{
		philo->is_alive = false;
		pthread_mutex_unlock(&philo->lock);
		return (true);
	}
	pthread_mutex_unlock(&philo->lock);
	return (false);
}

t_error	join_threads(t_table *table, int size)
{
	int	i;

	if (size != table->number_of_philo)
		pthread_mutex_unlock(&(table->start_lock));
	i = 0;
	while (i < size)
		pthread_join(table->philos[i++].thread, NULL);
	return (NO_ERROR);
}

void	kill_all(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->number_of_philo)
	{
		pthread_mutex_lock(&(table->philos[i].lock));
		table->philos[i].is_alive = false;
		pthread_mutex_unlock(&(table->philos[i].lock));
		i++;
	}
}
