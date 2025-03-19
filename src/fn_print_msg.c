/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fn_print_msg.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: selcyilm <selcyilm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/18 13:53:31 by selcyilm      #+#    #+#                 */
/*   Updated: 2025/03/19 13:51:51 by selcyilm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static char	*message_str(t_phio_state state)
{
	static char	*message[DIED + 1];

	if (message[0] == NULL)
	{
		message[EATING] = "is eating";
		message[SLEEPING] = "is sleeping";
		message[THINKING] = "is thinking";
		message[FORK] = "has taken a fork";
		message[DIED] = "died";
	}
	return (message[state]);
}

void	print_msg(t_philo *philo, t_phio_state state)
{
	if (pthread_mutex_lock(&philo->table->print_lock))
	{
		philo->table->err_info.err_no = MUTEX_LOCK;
		return ;
	}
	if (is_philo_dead(philo) != true)
	{
		printf("%ld %d %s\n", get_program_time(philo->table->start_time),
			philo->p_id,
			message_str(state));
	}
	if (pthread_mutex_unlock(&philo->table->print_lock))
	{
		philo->table->err_info.err_no = MUTEX_UNLOCK;
		return ;
	}
}
