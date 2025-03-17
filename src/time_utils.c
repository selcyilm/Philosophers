#include "../include/philo.h"

long	get_current_time(void)
{
	struct timeval	tv;
	long			milisecond;

	if(gettimeofday(&tv, NULL))
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
	//how to hell am i gonna check inside the while loop with norminette
	while (get_current_time() - current_time < mili_sec)
	{
		if (usleep(250))
			return (USLEEP_ERR);
	}
	return (NO_ERROR);
}