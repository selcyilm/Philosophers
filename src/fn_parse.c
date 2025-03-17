#include "../include/philo.h"

static bool	is_numeric_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

static t_error	fn_pars_check_numeric(char **av)
{
	int	i = 1;
	while (av[i])
	{
		if (is_numeric_str(av[i]) == false)
			return (INVALID_ARG_NOT_POS);
		i++;
	}
	return (NO_ERROR);
}

static int	ft_atoi(char *str)
{
	long	res;

	res = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
		if (res > INT_MAX)
			return (-1);
	}
	return ((int)res);
}

static bool	is_there_overflow(t_table *table)
{
	return (table->time_to_die == -1 ||
		table->time_to_eat == -1 ||
		table->time_to_sleep == -1 ||
		table->must_eat == -1);
}

t_app_state	fn_parse(t_table *table, int ac, char **av)
{
	printf("Parse!\n");
	memset(table, 0, sizeof(t_table));
	memset(&table->err_info, 0, sizeof(t_error_info));
	if (ac != 5 && ac != 6)
	{
		table->err_info.err_no = INVALID_ARG;
		return (STATE_ERROR);
	}
	table->err_info.err_no = fn_pars_check_numeric(av);
	if (table->err_info.err_no != NO_ERROR)
		return (STATE_ERROR);
	table->number_of_philo = ft_atoi(av[1]);
	if (table->number_of_philo <= 0)
		return (table->err_info.err_no = INVALID_PHILO_NUM, STATE_ERROR);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		table->must_eat = ft_atoi(av[5]);
	if (is_there_overflow(table))
		return (table->err_info.err_no = ATOI_OVERFLOW, STATE_ERROR);
	return (STATE_INIT);
}
