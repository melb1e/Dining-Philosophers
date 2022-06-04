#ifndef PHILO_H
# define PHILO_H

/*
** Libraries
*/
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
/*
** Headers of the project
*/
# include "defines.h"

typedef struct s_philos
{
	int				id;
	int				meals_done;
	pid_t			pid;
	sem_t			*philo_eat;
	time_t			last_ate;
	pthread_t		dead;
	pthread_t		thread_meals;
	struct s_inst	*installments;
}					t_philos;

typedef struct s_inst
{
	int				number;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				meals_goal;
	int				dead;
	time_t			timestamp;
	sem_t			*forks;
	sem_t			*death_status;
	sem_t			*report_status;
	sem_t			*eat_status;
	pthread_t		meals_done;
	t_philos		**philos;
}					t_inst;

/*
** Initialization and scanning of given arguments
*/
int					scan_args(const int ac, const char **av);
t_inst				*initialization(int ac, const char **av);

/*
** Thread creation
*/
int					thread_master(t_inst *inst);
pthread_mutex_t		*create_forks(t_inst *inst);
t_philos			**create_philos(t_inst *inst);

/*
** Master functions
*/
void				*kettle(t_philos *arg);
void				*death_checker(void *arg);
void				*meals_checker(void *arg);

/*
** Utils functions
*/
time_t				ft_timestamp(void);
void				display_status(t_inst *inst, size_t id, char *status);
int					ft_atoi(const char *str);
int					ft_error(int e_status);

#endif