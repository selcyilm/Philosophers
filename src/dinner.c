#include "philo.h"

static int	start_philo(t_env *e)
{
	int	i;

	i = 0;
	while (i < e->n_phi)
	{
		if (pthread_create(&(e->phi[i].philo), NULL, thread_philo, &(e->phi[i])))
		{
			e->end = 1;
			pthread_mutex_unlock(&e->m_print);
			break ;
		}
		i++;
	}
	if (i < e->n_phi)
	{
		printf("Error: Failed on %d!\n", i);
		while (i >= 0)
			pthread_join(e->phi[i--].philo, NULL);
		pthread_join(e->printer, NULL);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	start_printer(t_env *e)
{
	if (pthread_create(&e->printer, NULL, thread_printer, e))
	{
		e->end = 1;
		pthread_mutex_unlock(&e->m_print);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	start_dinner(t_env *e)
{
	pthread_mutex_lock(&e->m_print);
	if (start_printer(e))
		return (print_error_msg("start_printer failed!"));
	if (start_philo(e))
		return (print_error_msg("start_philo failed!"));
	e->start = cur_time();
	pthread_mutex_unlock(&e->m_print);
	return (EXIT_SUCCESS);
}