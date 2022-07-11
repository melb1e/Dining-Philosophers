#include "../includes/philo.h"

static int	ft_strcmp(char *str1, char *str2)
{
	size_t	i;

	i = 0;
	if ((!str1 && str2) || (!str2 && str1))
		return (ERROR);
	while (str1[i] && str2[i])
	{
		if (str1[i] == str2[i])
			i++;
		else if (str1[i] != str2[i])
			return (ERROR);
	}
	return (OK);
}

void	display_status(t_philos *philo, int id, char *action)
{
	sem_wait(philo->report_status);
	if (*action == 'h')
		printf("%li %i "GREEN"%s"BASIC"\n", \
				ft_timestamp() - philo->timestamp, id, action);
	else if (action[3] == 'e')
		printf("%li %i "CYAN"%s"BASIC"\n", \
				ft_timestamp() - philo->timestamp, id, action);
	else if (*action == 'i')
		printf("%li %i "YELLOW"%s"BASIC"\n", \
				ft_timestamp() - philo->timestamp, id, action);
	else if (*action == 'd')
		printf("%li %i "RED"%s"BASIC"\n", \
				ft_timestamp() - philo->timestamp, id, action);
	if (ft_strcmp(action, PHILO_DEAD))
		sem_post(philo->report_status);
}
