#include "philo.h"

static int	error_message(int status, const char *message)
{
	printf("Error: %s\n", message);
	return (status);
}

static int	mutex_error_check(int status, t_mutex_type type)
{
	if (status == 0)
		return (0);
	else if (status == EINVAL && (type == LOCK || type == UNLOCK))
		return (error_message(status, " The value spesicified by mutex is invalid!"));
	else if (status == EINVAL && type == INIT)
		return (error_message(status, "The value spesicified by attr us invalid!"));
	else if (status == EDEADLK)
		return (error_message(status, "A deadlock condition was detected!"));
	else if (status == EPERM)
		return (error_message(status, "The current thread doesn't hold a lock on mutex"));
	else if (status == ENOMEM)
		return (error_message(status, "The process can't allocate memory to create antoher mutex!"));
	else if (status == EBUSY)
		return (error_message(status, "Mutex is locked!"));
	else
		return (error_message(status, "Wrong type for mutex handle!"));
}


int	mutex_handle(t_mtx *mutex, t_mutex_type type)
{
	if (type == INIT)
		return (mutex_error_check(pthread_mutex_init(mutex, NULL), type));
	else if (type == DESTROY)
		return (mutex_error_check(pthread_mutex_destroy(mutex), type));
	else if (type == LOCK)
		return (mutex_error_check(pthread_mutex_lock(mutex), type));
	else if (type == UNLOCK)
		return (mutex_error_check(pthread_mutex_unlock(mutex), type));
	else
		return (-1);
}