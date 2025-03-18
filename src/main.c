/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: selcyilm <selcyilm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/24 20:36:08 by selcyilm      #+#    #+#                 */
/*   Updated: 2025/03/18 18:22:21 by selcyilm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	is_philo_dead(t_philo *philo);

void	philo_wait(t_philo *philo, int msec)
{
	long	time;

	time = get_current_time();
	while (get_current_time() - time < msec && !is_philo_dead(philo))
		usleep(250);
}

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

void	set_philo_time(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->number_of_philo)
		table->philos[i++].last_meal_time = table->start_time;
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

//check if dead
//try to take fork
//eat
//relase fork
//sleep
//think

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

void	*philo_routine(void *param)
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

bool	is_everyone_alive(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->number_of_philo)
	{
		if (is_philo_dead(&table->philos[i]))
		{
			kill_all(table);
			printf("%ld %d has died\n", get_program_time(table->start_time), 
				table->philos[i].p_id);
			return (false);
		}
		i++;
	}
	return (true);
}

bool	is_everyone_ate(t_table *table)
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
	return (true);
}

void	monitor(t_table *table)
{
	usleep(table->number_of_philo * 1000);
	while (true)
	{
		if (is_everyone_alive(table) == false)
			return ;
		if (table->must_eat > 0 && is_everyone_ate(table))
			return ;
	}
}

t_app_state	fn_start(t_table *table, int ac, char **av)
{
	int	i;

	(void)ac;
	(void)av;
	printf("Start dinner!\n");
	if (pthread_mutex_lock(&table->start_lock))
		return (table->err_info.err_no = MUTEX_LOCK, STATE_ERROR);
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
	printf("after create\n");
	set_philo_time(table);
	table->start = true;
	if (pthread_mutex_unlock(&table->start_lock))
		return (table->err_info.err_no = MUTEX_UNLOCK, STATE_ERROR);
	monitor(table);
	join_threads(table, table->number_of_philo);
	return (STATE_FINISH);
}

static void	fn_state_func_init(t_state_fn *func)
{
	func[STATE_PARS] = fn_parse;
	func[STATE_INIT] = fn_init;
	func[STATE_START_DINNER] = fn_start;
	func[STATE_ERROR] = fn_error;
}

int	main(int ac, char **av)
{
	t_table		table;
	t_state_fn	state_map[STATE_FINISH];
	t_app_state	state;

	fn_state_func_init(state_map);
	state = STATE_PARS;
	while (state != STATE_FINISH)
	{
		state = state_map[state](&table, ac, av);
	}
	if (table.err_info.err_no != NO_ERROR)
		return (EXIT_FAILURE);
	fn_clean(&table);
	return (EXIT_SUCCESS);
}
