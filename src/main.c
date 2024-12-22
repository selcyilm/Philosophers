/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: selcyilm <selcyilm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/24 20:36:08 by selcyilm      #+#    #+#                 */
/*   Updated: 2024/12/22 18:46:27by selcyilm      ########   odam.nl         */
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

# define SUM 1000

t_mtx		mutex;

void	*one(void *args)
{
	int *num = (int *)args;
	while (*num < SUM)
	{
		mutex_handle(&mutex, LOCK);
		if (*num + 1 <= SUM)
		{
			printf("Thread 1: Counter + 1 = %d\n", *num + 1);
			*num += 1;
		}
		mutex_handle(&mutex, UNLOCK);
	}
	return (NULL);
}
void	*two(void *args)
{
	int *num = (int *)args;
	while (*num < SUM)
	{
		mutex_handle(&mutex, LOCK);
		if (*num + 2 <= SUM)
		{
			printf("Thread 2: Counter + 2 = %d\n", *num + 2);
			*num += 2;
		}
		mutex_handle(&mutex, UNLOCK);
	}
	return (NULL);
}
void	*three(void *args)
{
	int *num = (int *)args;
	while (*num < SUM)
	{
		mutex_handle(&mutex, LOCK);
		if (*num + 3 <= SUM)
		{
			printf("Thread 3: Counter + 3 = %d\n", *num + 3);
			*num += 3;
		}
		mutex_handle(&mutex, UNLOCK);
	}
	return (NULL);
}

int main(void)
{
	pthread_t one1, two2, three3;

	int i = 0;
	mutex_handle(&mutex, INIT);

	thread_handle(&one1, one, &i, CREATE);
	thread_handle(&two2, two, &i, CREATE);
	thread_handle(&three3, three, &i, CREATE);

	thread_handle(&one1, one, &i, JOIN);
	thread_handle(&two2, two, &i, JOIN);
	thread_handle(&three3, three, &i, JOIN);

	printf("value at the end %d\n", i);
	mutex_handle(&mutex, DESTROY);
}


// int	main(int ac, char **av)
// {
// 	// t_table	table;

// 	// if (ac != 5 && ac != 6)
// 	// 	print_error("Error: Invalid argument!");
// 	// //parse input
// 	// fn_input_parse(&table, av);
// 	// print_table(&table);
// 	(void)ac;
// 	(void)av;
// 	pthread_t t1, t2;
// 	long i = 0;
	
// 	thread_handle(&t1, func, &i, CREATE);
// 	thread_handle(&t2, func, &i, CREATE);

// 	thread_handle(&t1, NULL, &i, JOIN);
// 	thread_handle(&t2, NULL, &i, JOIN);
// 	//data init
// 	printf("%ld\n", i);
// 	//simulation

// 	//clean
	
// 	return (EXIT_SUCCESS);
// }