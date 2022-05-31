#include "../includes/philo.h"

# define USAGE_ERROR	"Usage error [101]\n"
# define MALLOC_ERROR	"Malloc error [102]\n"

void	initialize(philo *philos, const int argc, const char **argv, int n)
{
	int		chars;
	time_t	time_to_die;
	time_t	time_to_eat;
	time_t	time_to_sleep;

	chars = atoi(argv[1]);
	time_to_die = atoi(argv[2]) * 1000;
	time_to_eat = atoi(argv[3]) * 1000;
	time_to_sleep = atoi(argv[4]) * 1000;
	philos->number_of_philosophers = chars;
	philos->time_to_die = time_to_die;
	philos->time_to_eat = time_to_eat;
	philos->time_to_sleep = time_to_sleep;
	philos->number_of_times_each_philosopher_must_eat = n;
}

int	create_threads(philo *philos, int chars)
{
	int	i;
	pthread_t	death;

	i = 0;
	while (i < chars)
	{
		pthread_mutex_init()
	}
	
}

int	main(int argc, char **argv)
{
	philo	*philos;

	if (argc insufficient)
		return (ft_error(USAGE_ERROR))
	philos = (philo *)malloc(sizeof(philo));
	if (!philos)
		return (ft_error(MALLOC_ERROR));
	// if argc WITHOUT number_of_times_each_philosopher_must_eat
	initialize(philos, argc, argv, -1);
	return (create_threads(philos, atoi(argv[1]))); 
}
