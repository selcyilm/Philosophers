/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: selcyilm <selcyilm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/24 20:36:08 by selcyilm      #+#    #+#                 */
/*   Updated: 2024/12/22 18:46:27by selcyilm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
static void	join_threads(t_env *e)
{
	int	i;

	i = -1;
	pthread_join(e->printer, NULL);
	while (++i < e->n_phi)
		pthread_join(e->phi[i].philo, NULL);
}

static void	clean_table(t_env *e)
{
	t_list	*tmp;
	t_list	*cur;
	int		i;

	pthread_mutex_destroy(&e->m_print);
	i = -1;
	while (++i < e->n_phi)
		pthread_mutex_destroy(&(e->fork[i]));
	free(e->fork);
	i = -1;
	while (++i < e->n_phi)
	{
		cur = e->phi[i].l;
		while (cur)
		{
			tmp = cur;
			cur = cur->next;
			free(tmp);
		}
		pthread_mutex_destroy(&(e->phi[i].m_l));
		pthread_mutex_destroy(&(e->phi[i].m_eat));
	}
	free(e->phi);
}

static void	check_cond(t_env *e)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < e->n_phi)
		{
			usleep(1000);
			if (check_starvation(&(e->phi[i])))
				return ;
			i++;
		}
	}
}

int	main(int ac, char **av)
{
	t_env	e;

	if (ac != 5 && ac != 6)
		return (print_error_msg("INput must be 4 or 5 integer!"));
	if (parse_input(&e, ac, av))
		return (print_error_msg("Parse Input Failed!"));
	if (e.n_phi == 1)
	{
		printf("0 Philosopher 1 has taken a fork.\n");
		usleep(e.t_die * 1000);
		printf("%d Philosopher 1 died.\n", e.t_die);
		return (EXIT_FAILURE);
	}
	if (init_table(&e))
		return (print_error_msg("Init table failed!"));
	if (start_dinner(&e))
	{
		clean_table(&e);
		return (print_error_msg("start dinner failed!"));
	}
	check_cond(&e);
	join_threads(&e);
	clean_table(&e);
	return (EXIT_SUCCESS);
}