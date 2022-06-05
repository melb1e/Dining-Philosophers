#ifndef DEFINES_H
# define DEFINES_H

# define GREEN							"\033[0;32m"
# define YELLOW							"\033[0;33m"
# define RED							"\033[1;31m"
# define CYAN							"\033[0;36m"
# define BLUE							"\033[0;34m"
# define WHITE							"\033[0;37m"
# define BASIC							"\033[0m"

# define ERROR_INPUT					-101
# define ERROR_THREADS					-102
# define ERROR_MEALS					-103
# define ERROR_MUTEX					-104
# define ERROR_SEMAPHORE				-105
# define DEBUG							-107
# define ERROR_UNKNOWN 					-108
# define ERROR_FORKS					-110
# define ERROR_INITIALIZATION			-111
# define ERROR_FORKING					-112

# define ERROR_OVERFLOW					-202

# define ERROR_MUTEX_STRING				"Error 104 [Mutex initialization or creation]"
# define ERROR_MEALS_STRING				"Error 103 [Wrong input in \
number_of_times_each_philosopher_must_eat]"
# define ERROR_INPUT_STRING				"Error 101 [Wrong input, try ./philo \
'(number_of_philosophers)' '(time_to_die)' '(time_to_eat)' '(time_to_sleep)' \
'<number_of_times_each_philosopher_must_eat>']"
# define ERROR_THREADS_STRING			"Error 102 [Something went wrong with threads]"
# define ERROR_SEMAPHORE_STRING			"Error 105 [Semaphores isn't working properly]"
# define ERROR_UNKNOWN_STRING			"Error 108 [Unknown error]"
# define ERROR_INITIALIZATION_STRING	"Error 109 [Initialization error]"

# define PHILO_HAS_LEFT_FORK			"has taken a fork"
# define PHILO_HAS_RIGHT_FORK			"has taken a fork"
# define PHILO_EATING					"is eating"
# define PHILO_SLEEPING					"is sleeping"
# define PHILO_THINKING					"is thinking"
# define PHILO_DEAD						"died"

# define P_MAX_ARGS						5
# define P_MIN_ARGS						4

# define EOL							'\0'
# define STDIN							0
# define STDOUT 						1
# define STDERR 						2

# define OK								0
# define ERROR							-404
# define EXIT_PROC						1

# define TRUE							1
# define FALSE							0

#endif