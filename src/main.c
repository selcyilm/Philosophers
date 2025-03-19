/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: selcyilm <selcyilm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/24 20:36:08 by selcyilm      #+#    #+#                 */
/*   Updated: 2025/03/19 13:31:47 by selcyilm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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
