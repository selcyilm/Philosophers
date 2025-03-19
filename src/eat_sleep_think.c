#include "../include/philo.h"

bool	take_forks(t_philo *philo)
{
	if (is_philo_dead(philo))
		return (false);
	if (philo->number_of_meal_eaten != 0)
	{
		if (philo->table->time_to_die - (get_current_time() - philo->last_meal_time) > 
			philo->table->time_to_eat)
			ft_sleep(philo->table->time_to_die - 
				(get_current_time() - philo->last_meal_time) - philo->table->time_to_eat);
	}
	pthread_mutex_lock(philo->right_fork);
	print_msg(philo, FORK);
	if (philo->table->number_of_philo == 1)
	{
		pthread_mutex_unlock(philo->right_fork);
		ft_sleep(philo->table->time_to_die);
		return (false);
	}
	pthread_mutex_lock(philo->left_fork);
	print_msg(philo, FORK);
	return (true);
}

void	eat(t_philo *philo)
{
	if (is_philo_dead(philo))
		return ;
	print_msg(philo, EATING);
	pthread_mutex_lock(&philo->lock);
	philo->number_of_meal_eaten++;
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&philo->lock);
	philo_wait(philo, philo->table->time_to_eat);
}

void	eat_sleep_think(t_philo *philo)
{
	while (true)
	{
		if (is_philo_dead(philo))
			return ;
		if (take_forks(philo) == false)
			return ;
		eat(philo);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		if (is_philo_dead(philo))
			return ;
		print_msg(philo, SLEEPING);
		philo_wait(philo, philo->table->time_to_sleep);
		if (is_philo_dead(philo))
			return ;
		print_msg(philo, THINKING);
	}
}
