/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fn_start.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: selcyilm <selcyilm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/19 15:24:11 by selcyilm      #+#    #+#                 */
/*   Updated: 2025/05/05 13:20:03 by selcyilm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	*philo_routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	pthread_mutex_lock(&philo->table->start_lock);
	if (philo->table->start == false)
	{
		pthread_mutex_unlock(&philo->table->start_lock);
		return (NULL);
	}
	pthread_mutex_unlock(&philo->table->start_lock);
	if (philo->p_id % 2 == 0)
		usleep(10000);
	eat_sleep_think(philo);
	return (NULL);
}

static void	set_philo_time(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->number_of_philo)
		table->philos[i++].last_meal_time = table->start_time;
}

t_app_state	fn_start(t_table *table, int ac, char **av)
{
	int	i;

	(void)ac;
	(void)av;
	pthread_mutex_lock(&table->start_lock);
	i = 0;
	while (i < table->number_of_philo)
	{
		if (pthread_create(&(table->philos[i].thread), NULL,
				&philo_routine, &(table->philos[i])))
			return (table->err_info.err_no = THREAD,
				table->err_info.join_index = i, STATE_ERROR);
		i++;
	}
	table->err_info.join_index = i;
	table->start_time = get_current_time();
	set_philo_time(table);
	table->start = true;
	pthread_mutex_unlock(&table->start_lock);
	monitor(table);
	join_threads(table, table->number_of_philo);
	return (STATE_FINISH);
}
