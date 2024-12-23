#include "philo.h"

static long	ft_atoi(char *str)
{
	int		i;
	size_t	ret;

	ret = 0;
	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			ret = (ret * 10) + str[i] - '0';
		else
			return (0);
		if (ret > INT_MAX)
			return (0);
		i++;
	}
	return (ret);
}

int	parse_input(t_env *e, int ac, char **av)
{
	e->n_phi = ft_atoi(av[1]);
	if (!e->n_phi)
		return (print_error_msg("Usage: 0 < n_phi <= INT_MAX!"));
	e->t_die = ft_atoi(av[2]);
	if (!e->t_die)
		return (print_error_msg("Usage: 0 < t_die <= INT_MAX!"));
	e->t_eat = ft_atoi(av[3]);
	if (!e->t_eat)
		return (print_error_msg("Usage: 0 < t_eat <= INT_MAX!"));
	e->t_sleep = ft_atoi(av[4]);
	if (!e->t_sleep)
		return (print_error_msg("Usage: 0 < t_sleep <= INT_MAX!"));
	e->n_meal = 0;
	if (ac == 6)
	{
		e->n_meal = ft_atoi(av[5]);
		if (!e->n_meal)
			return (print_error_msg("Usage: 0 < n_meal <= INT_MAX"));
	}
	return (0);
}
