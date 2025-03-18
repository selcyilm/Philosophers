/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fn_clean.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: selcyilm <selcyilm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/18 13:52:00 by selcyilm      #+#    #+#                 */
/*   Updated: 2025/03/18 13:52:07 by selcyilm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	clear_mutex(t_table *table)
{
	int	i_fork;
	int	i_philo;

	pthread_mutex_destroy(&table->print_lock);
	pthread_mutex_destroy(&table->start_lock);
	i_fork = 0;
	while (i_fork < table->number_of_philo)
		pthread_mutex_destroy(&table->forks[i_fork++]);
	i_philo = 0;
	while (i_philo < table->number_of_philo)
		pthread_mutex_destroy(&table->philos[i_philo++].lock);
}

static void	clear_alloc(t_table *table)
{
	if (table->forks)
		free(table->forks);
	if (table->philos)
		free(table->philos);
}

void	fn_clean(t_table *table)
{
	printf("End clean!\n");
	clear_mutex(table);
	clear_alloc(table);
}
