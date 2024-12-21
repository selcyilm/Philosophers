/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: selcyilm <selcyilm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/24 20:36:04 by selcyilm      #+#    #+#                 */
/*   Updated: 2024/12/20 14:01:05 by selcyilm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>
# include <pthread.h>

typedef pthread_mutex_t t_mtx;
typedef struct s_philo t_philo;

typedef struct s_fork
{
	t_mtx	fork;
	int		fork_id;
}	t_fork;

typedef struct s_table
{
	long	philo_nbr;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	nbr_limit_meals;
	long	start_simulation;
	bool	end_simulation;
	t_fork	*farks;
	t_philo	*philos;
}	t_table;

typedef struct s_philo
{
	int			id;
	long		meal_numbers;
	bool		full;
	long		last_meal_time;
	t_fork		*left_fork;
	t_fork		*rigt_fork;
	pthread_t	thread_id;
	t_table		*table;
}	t_philo;

void	print_error(const char *message);
void	fn_input_parse(t_table *table, char **av);


#endif
