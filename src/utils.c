#include "philo.h"

int	print_error_msg(const char *msg)
{
	printf("Error: %s\n", msg);
	return (EXIT_FAILURE);
}

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}