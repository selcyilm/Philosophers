/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: selcyilm <selcyilm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/19 15:26:08 by selcyilm      #+#    #+#                 */
/*   Updated: 2025/03/19 15:26:17 by selcyilm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static bool	is_everyone_alive(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->number_of_philo)
	{
		if (is_philo_dead(&table->philos[i]))
		{
			kill_all(table);
			printf("%ld %d has died\n",
				get_program_time(table->start_time),
				table->philos[i].p_id);
			return (false);
		}
		i++;
	}
	return (true);
}

static bool	is_everyone_ate(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->number_of_philo)
	{
		pthread_mutex_lock(&(table->philos[i].lock));
		if (table->philos[i].number_of_meal_eaten != table->must_eat)
		{
			pthread_mutex_unlock(&(table->philos[i].lock));
			return (false);
		}
		pthread_mutex_unlock(&(table->philos[i].lock));
		i++;
	}
	kill_all(table);
	return (true);
}

void	monitor(t_table *table)
{
	printf("monitor\n");
	usleep(table->number_of_philo * 1000);
	while (true)
	{
		if (is_everyone_alive(table) == false)
			return ;
		if (table->must_eat > 0 && is_everyone_ate(table))
			return ;
	}
}
