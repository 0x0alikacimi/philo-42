#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0); 
	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_perror(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
}

int	valid_n(const char *str)
{
	int res;
	int i;
	int check;
	
	res = 0;
	i = 0;
	while ((str[i]) == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '+')
		i++;
	if (str[i] == '\0' || str[i] < '0' || str[i] > '9')
		return(ft_perror("invalid arg\n"), -13);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return(ft_perror("invalid arg\n"), -13);
		check = res;
		res = res * 10 + (str[i] - '0');
		if (res / 10 != check)
			return(ft_perror("invalid arg\n"), -13);
		i++;
	}
	return (res);
}
