/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fn_input_parse.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: selcyilm <selcyilm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/20 13:34:18 by selcyilm      #+#    #+#                 */
/*   Updated: 2024/12/21 12:00:49 by selcyilm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

static bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static const char	*valid_input(const char *str)
{
	int			len;
	const char	*num;

	len = 0;
	while (is_space(*str))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
		print_error("Error: Invalid input! Num can't be negative");
	if (is_digit(*str) == false)
		print_error("Error: Invalid input! Input isn't a correct digit!");
	num = str;
	while (is_digit(*str))
	{
		len++;
		str++;
	}
	if (len > 10)
		print_error("Error: Invalid input! Num can't be bigger then INT_MAX");
	return (num);
}


static long	ft_atol(const char *str)
{
	long	num;

	num = 0;
	str = valid_input(str);
	while (is_digit(*str))
	{
		num = (num * 10) + (*str - '0');
		str++;
	}
	if (num > INT_MAX)
		print_error("Error: Invalid input! Num can't be bigger then INT_MAX");
	return (num);
}

void	fn_input_parse(t_table *table, char **av)
{
	table->philo_nbr = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]) * 1e3;
	table->time_to_eat = ft_atol(av[3]) * 1e3;
	table->time_to_sleep = ft_atol(av[4]) * 1e3;
	if (table->time_to_die < 6e4
		|| table->time_to_eat < 6e4
		|| table->time_to_sleep < 6e4)
		print_error("Error: Time stamps less than 60ms!");
	if (av[5])
		table->nbr_limit_meals = ft_atol(av[5]);
	else
		table->nbr_limit_meals = -1;
}
