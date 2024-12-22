/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: selcyilm <selcyilm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/24 20:36:04 by selcyilm      #+#    #+#                 */
/*   Updated: 2024/12/22 17:22:51 by selcyilm      ########   odam.nl         */
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
# include <errno.h>
# include <pthread.h>

typedef pthread_mutex_t t_mtx;
typedef struct s_philo t_philo;

typedef enum e_mutex_type
{
	INIT,
	DESTROY,
	LOCK,
	UNLOCK,
}	t_mutex_type;

typedef enum e_thread_type
{
	CREATE,
	DETACH,
	JOIN,
}	t_thread_type;


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
	t_fork	*forks;
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

int		mutex_handle(t_mtx *mutex, t_mutex_type type);
int		thread_handle(pthread_t *thread, void *(*foo)(void *), void *data, t_thread_type type);

#endif
