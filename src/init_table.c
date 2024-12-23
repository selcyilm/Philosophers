#include "philo.h"

static void	clean_env_mutexes(t_env *e)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&e->m_print);
	while (i < e->n_phi)
		pthread_mutex_destroy(&e->fork[i++]);
}

static int	init_phi_mutexes(t_env *e, t_phi *p, int i)
{
	if (pthread_mutex_init(&(p->m_l), NULL))
	{
		clean_env_mutexes(e);
		while (--i >= 0)
		{
			pthread_mutex_destroy(&e->phi[i].m_eat);
			pthread_mutex_destroy(&e->phi[i].m_l);
		}
		return (print_error_msg("m_l failed!"));
	}
	if (pthread_mutex_init(&(p->m_eat), NULL))
	{
		clean_env_mutexes(e);
		pthread_mutex_destroy(&(p->m_l));
		while (--i >= 0)
		{
			pthread_mutex_destroy(&e->phi[i].m_eat);
			pthread_mutex_destroy(&e->phi[i].m_l);
		}
		return (print_error_msg("m_eat failed!"));
	}
	return (EXIT_SUCCESS);
}

static int	init_phi(t_env *e)
{
	int	i;

	i = 0;
	while (i < e->n_phi)
	{
		e->phi[i].e = e;
		e->phi[i].id = i;
		e->phi[i].end = 0;
		e->phi[i].c_meal = 0;
		e->phi[i].t_ate = 0;
		e->phi[i].l = NULL;
		if (init_phi_mutexes(e, &e->phi[i], i))
			return (print_error_msg("init_philo_mutex failed!"));
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	init_env_mutexes(t_env *e)
{
	int	i;

	if (pthread_mutex_init(&e->m_print, NULL))
		return (print_error_msg("MUtex m_print failed"));
	i = 0;
	while (i < e->n_phi)
	{
		if (pthread_mutex_init(&e->fork[i], NULL))
		{
			pthread_mutex_destroy(&e->m_print);
			while (--i >= 0)
				pthread_mutex_destroy(&e->fork[i]);
			return (print_error_msg("Mutex e->fork failed!"));
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	init_table(t_env *e)
{
	e->c_meal = 0;
	e->end = 0;
	e->phi = (t_phi *)malloc(sizeof(t_phi) * e->n_phi);
	if (!(e->phi))
		return (print_error_msg("Malloc e->phi failed!"));
	e->fork = malloc(sizeof(t_mtx) * e->n_phi);
	if (!(e->fork))
		return (free(e->phi), print_error_msg("Malloc e->fork failed!"));
	if (init_env_mutexes(e))
		return (free(e->fork), free(e->phi), print_error_msg("init_env_mutex failed!"));
	if (init_phi(e))
		return (free(e->fork), free(e->phi), print_error_msg("init_philo failed!"));
	return (EXIT_SUCCESS);
}