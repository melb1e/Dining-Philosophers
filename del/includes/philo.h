#ifndef PHILO_H
# define PHILO_H

# include <time.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <libc.h>

typedef struct
{
	pthread_t	thread;
	time_t		time_to_die;
	time_t		time_to_eat;
	time_t		time_to_sleep;
	int			number_of_philosophers;
	int			number_of_times_each_philosopher_must_eat;
}				philo;




#endif