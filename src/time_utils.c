/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: selcyilm <selcyilm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/18 13:56:04 by selcyilm      #+#    #+#                 */
/*   Updated: 2025/03/19 13:28:06 by selcyilm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	get_current_time(void)
{
	struct timeval	tv;
	long			milisecond;

	if (gettimeofday(&tv, NULL))
		return (-1);
	milisecond = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (milisecond);
}

long	get_program_time(long start_time)
{
	long	current_time;

	current_time = get_current_time();
	if (current_time == -1)
		return (-1);
	return (current_time - start_time);
}

t_error	ft_sleep(long mili_sec)
{
	long	current_time;

	current_time = get_current_time();
	if (current_time == -1)
		return (USLEEP_ERR);
	while (get_current_time() - current_time < mili_sec)
	{
		if (usleep(250))
			return (USLEEP_ERR);
	}
	return (NO_ERROR);
}

void	philo_wait(t_philo *philo, int msec)
{
	long	time;

	time = get_current_time();
	while (get_current_time() - time < msec && !is_philo_dead(philo))
		usleep(250);
}
