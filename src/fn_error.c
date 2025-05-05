/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fn_error.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: selcyilm <selcyilm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/18 13:50:08 by selcyilm      #+#    #+#                 */
/*   Updated: 2025/05/05 13:03:19 by selcyilm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	error_msg(t_error status)
{
	static char	*error[14];

	if (error[0] == NULL)
	{
		error[NO_ERROR] = "No Error";
		error[INVALID_ARG] = "Invalid Arguments";
		error[INVALID_PHILO_NUM] = "Invalid Philo Number";
		error[INVALID_ARG_NOT_POS] = "Invalid arg, should be positive number";
		error[ATOI_OVERFLOW] = "Invalid arg, atoi overflow detected";
		error[THREAD] = "Theread init failure";
		error[JOIN] = "Thread Join Failure";
		error[MUTEX_INIT] = "Mutex init Failure";
		error[MUTEX_LOCK] = "Mutex Lock Failure";
		error[MUTEX_UNLOCK] = "Mutex Unlock Failure";
		error[MALLOC_FAIL] = "Memory Allocation Failure";
		error[USLEEP_ERR] = "Usleep Failure";
		error[TIME_ERR] = "GetTimeofday Failure";
	}
	printf("Error: %s\n", error[status]);
}

static void	clear_mutex(t_table *table)
{
	int	i_fork;
	int	i_philo;

	if (table->err_info.mutex_print)
		pthread_mutex_destroy(&table->print_lock);
	if (table->err_info.mutex_start)
		pthread_mutex_destroy(&table->start_lock);
	i_fork = 0;
	while (i_fork < table->err_info.mutex_fork_index)
		pthread_mutex_destroy(&table->forks[i_fork++]);
	i_philo = 0;
	while (i_philo < table->err_info.mutex_philo_index)
		pthread_mutex_destroy(&table->philos[i_philo++].lock);
}

static void	clear_alloc(t_table *table)
{
	if (table->err_info.is_allocated >= 1)
		free(table->forks);
	if (table->err_info.is_allocated >= 2)
		free(table->philos);
}

t_app_state	fn_error(t_table *table, int ac, char **av)
{
	(void)ac;
	(void)av;
	error_msg(table->err_info.err_no);
	join_threads(table, table->err_info.join_index);
	clear_mutex(table);
	clear_alloc(table);
	return (STATE_FINISH);
}
