#include "philo.h"

static int	error_message(int status, const char *message)
{
	printf("Error: %s\n", message);
	return (status);
}

static int handle_thread_error(int status, t_thread_type type)
{
	if (status == 0)
		return (0);
	else if (status == EAGAIN)
		return (error_message(status, "Insufficient resources to create another thread!"));
	else if (status == EINVAL && type == CREATE)
		return (error_message(status, "Invalid settings in attr!"));
	else if (status == EINVAL && (type == JOIN || type == DETACH))
		return (error_message(status, "Thread is not a joinable thread."));
	else if (status == EDEADLK)
		return (error_message(status, "A deadlock was detected!"));
	else if (status == ESRCH)
		return (error_message(status, "No thread with the ID thread could be found!"));
	else
		return (error_message(status, "Wrong type for thread handle!"));
}

int	thread_handle(pthread_t *thread, void *(*foo)(void *), void *data, t_thread_type type)
{
	if (type == CREATE)
		return (handle_thread_error(pthread_create(thread, NULL, foo, data), type));
	else if (type == JOIN)
		return (handle_thread_error(pthread_join(*thread, NULL), type));
	else if (type == DETACH)
		return (handle_thread_error(pthread_detach(*thread), type));
	else
		return (handle_thread_error(-1, type));
}