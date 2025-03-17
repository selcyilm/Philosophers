#include "../include/philo.h"

static void	select_fork(t_table *table, t_philo *philo)
{
	if (philo->p_id % 2 == 0)
	{
		philo->right_fork = &(table->forks[philo->p_id - 1]);
		philo->left_fork = &(table->forks[philo->p_id % table->number_of_philo]);
	}
	else
	{
		philo->right_fork = &(table->forks[philo->p_id % table->number_of_philo]);
		philo->left_fork = &(table->forks[philo->p_id - 1]);
	}
}

static t_error	fn_init_forks(t_table *table)
{
	int	i;

	table->forks = malloc(sizeof(pthread_mutex_t) * table->number_of_philo);
	if (table->forks == NULL)
		return (MALLOC_FAIL);
	table->err_info.is_allocated = 1;
	i = 0;
	while (i < table->number_of_philo)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
			return (table->err_info.mutex_fork_index = i, MUTEX_INIT);
		i++;
	}
	table->err_info.mutex_fork_index = i;
	return (NO_ERROR);
}

static t_error fn_init_philos(t_table *table)
{
	int	i;

	table->philos = malloc(sizeof(t_philo) * table->number_of_philo);
	if (table->philos == NULL)
		return (MALLOC_FAIL);
	table->err_info.is_allocated = 2;
	i = 0;
	while (i < table->number_of_philo)
	{
		table->philos[i].p_id = i + 1;
		table->philos[i].number_of_meal_eaten = 0;
		table->philos[i].is_alive = true;
		if (pthread_mutex_init(&(table->philos[i].lock), NULL) != 0)
		{
			table->err_info.mutex_philo_index = i;
			return (MUTEX_INIT);
		}
		table->philos[i].table = table;
		select_fork(table, &table->philos[i]);
		i++;
	}
	table->err_info.mutex_fork_index = i;
	return (NO_ERROR);
}

t_app_state	fn_init(t_table *table, int ac, char **av)
{
	printf("Init!\n");
	(void)ac;
	(void)av;
	if (pthread_mutex_init(&(table->start_lock), NULL) != 0)
		return (table->err_info.err_no = MUTEX_INIT, STATE_ERROR);
	table->err_info.mutex_start = 1;
	if (pthread_mutex_init(&(table->print_lock), NULL) != 0)
		return (table->err_info.err_no = MUTEX_INIT, STATE_ERROR);
	table->err_info.mutex_print = 1;
	table->err_info.err_no = fn_init_forks(table);
	if (table->err_info.err_no != NO_ERROR)
		return (STATE_ERROR);
	table->err_info.err_no = fn_init_philos(table);
	if (table->err_info.err_no != NO_ERROR)
		return (STATE_ERROR);
	return (STATE_START_DINNER);
}
