/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: selcyilm <selcyilm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/24 20:36:04 by selcyilm      #+#    #+#                 */
/*   Updated: 2025/03/19 21:34:44 by selcyilm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdbool.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>
# include <errno.h>
# include <pthread.h>
# include <time.h>

typedef enum e_philo_state
{
	EATING,
	SLEEPING,
	THINKING,
	FORK,
	DIED
}	t_phio_state;

typedef enum e_error
{
	NO_ERROR,
	INVALID_ARG,
	INVALID_PHILO_NUM,
	INVALID_ARG_NOT_POS,
	ATOI_OVERFLOW,
	THREAD,
	JOIN,
	MUTEX_INIT,
	MUTEX_LOCK,
	MUTEX_UNLOCK,
	MALLOC_FAIL,
	USLEEP_ERR,
	TIME_ERR
}	t_error;

typedef enum e_app_state
{
	STATE_PARS,
	STATE_INIT,
	STATE_START_DINNER,
	STATE_ERROR,
	STATE_FINISH
}	t_app_state;

typedef struct s_error_info
{
	t_error	err_no;
	int		is_allocated;
	int		mutex_start;
	int		mutex_print;
	int		mutex_fork_index;
	int		mutex_philo_index;
	int		join_index;
}	t_error_info;

typedef struct s_philo
{
	pthread_t		thread;
	int				p_id;
	bool			is_alive;
	int				number_of_meal_eaten;
	long			last_meal_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	lock;
	struct s_table	*table;
}	t_philo;

typedef struct s_table
{
	int				number_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	long			start_time;
	bool			start;
	t_error_info	err_info;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	start_lock;
	pthread_mutex_t	print_lock;
}	t_table;

typedef t_app_state	(*t_state_fn)(t_table *, int, char **);

//PARSE
t_app_state	fn_parse(t_table *table, int ac, char **av);

//INIT_TABLE
t_app_state	fn_init(t_table *table, int ac, char **av);

//START
t_app_state	fn_start(t_table *table, int ac, char **av);
t_error		join_threads(t_table *table, int size);
bool		is_philo_dead(t_philo *philo);

//EAT_SLEEP_THINK
void		eat_sleep_think(t_philo *philo);

//MONITOR
void		monitor(t_table *table);

//PRINT
void		print_msg(t_philo *philo, t_phio_state state);

//CLEAN
void		fn_clean(t_table *table);

//TIME
long		get_current_time(void);
long		get_program_time(long start_time);
t_error		ft_sleep(long mili_sec);
void		philo_wait(t_philo *philo, int msec);

//THREAD_UTILS
bool		is_philo_dead(t_philo *philo);
t_error		join_threads(t_table *table, int size);
void		kill_all(t_table *table);

//ERROR
t_app_state	fn_error(t_table *table, int ac, char **av);

#endif
