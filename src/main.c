/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: selcyilm <selcyilm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/24 20:36:08 by selcyilm      #+#    #+#                 */
/*   Updated: 2024/12/20 14:11:13 by selcyilm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_table(t_table *table)
{
	printf("Philo Number: %ld\n", table->philo_nbr);
	printf("Time to die: %ld\n", table->time_to_die);
	printf("Time to eat: %ld\n", table->time_to_eat);
	printf("Time to sleep: %ld\n", table->time_to_sleep);
	printf("Number of time philo should eat: %ld\n", table->nbr_limit_meals);
}

void	print_error(const char *message)
{
	printf("%s\n", message);
	exit(EXIT_FAILURE);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (ac != 5 && ac != 6)
		print_error("Error: Invalid argument!");
	//parse input
	fn_input_parse(&table, av);
	print_table(&table);
	//data init
	
	//simulation

	//clean
	
	return (EXIT_SUCCESS);
}