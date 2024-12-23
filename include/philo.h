/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: selcyilm <selcyilm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/24 20:36:04 by selcyilm      #+#    #+#                 */
/*   Updated: 2024/12/23 17:34:18 by selcyilm      ########   odam.nl         */
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

typedef struct s_list
{
	long			ms;
	int				i;
	char			s[20];
	struct s_list	*next;
}	t_list;

typedef struct s_env
{
	int	c_meal;
	int	end;
	long	start;
	struct s_phi	*phi;
	t_mtx			*fork;
	t_mtx			m_print;
	pthread_t		printer;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_phi;
	int				n_meal;
}	t_env;

typedef struct s_phi
{
	int	id;
	int	end;
	int	c_meal;
	long	t_ate;
	t_env	*e;
	t_list	*l;
	pthread_t	philo;
	t_mtx		m_eat;
	t_mtx		m_l;
}	t_phi;


//PARSE
int		parse_input(t_env *e, int ac, char **av);

//INIT_TABLE
int		init_table(t_env *e);

//UTILS
int		print_error_msg(const char *msg);
int		ft_strcmp(char *s1, char *s2);

//PRINTER
void	*thread_printer(void *input);
int		check_end(t_env *e);

//PRINT
int		count_meal(t_phi *p, t_list *l);
int		add_cond(long ms, t_phi *p, char *s);

//PHILO
void	*thread_philo(void *input);
int		check_starvation(t_phi *p);

//TIME
void	ft_better_sleep(long time);
long	dinner_time(t_env *e);
long	cur_time(void);

//DINNER
int		start_dinner(t_env *e);

#endif
