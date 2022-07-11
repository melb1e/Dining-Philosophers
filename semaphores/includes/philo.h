/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcele <mmarcele@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 14:14:57 by mmarcele          #+#    #+#             */
/*   Updated: 2022/06/05 14:15:08 by mmarcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

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
# include "defines.h"

typedef struct s_freak
{
	int				id;
	int				number;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				meals_goal;
	int				meals_done;
	int				dead;
	time_t			last_ate;
	time_t			timestamp;
	pthread_t		death_status;
	sem_t			*forks_status;
	sem_t			*report_status;
	pid_t			*pid;
}					t_philos;

int					scan_args(int ac, char **av);
t_philos			*initialization(int ac, char **av);
int					create_semaphores(t_philos *philo);
int					thread_master(t_philos *philo);
pthread_mutex_t		*create_forks(t_philos *philo);
t_philos			**create_philos(t_philos *philo);
int					kettle(t_philos *arg);
void				*death_checker(void *arg);
void				*meals_checker(void *arg);
time_t				ft_timestamp(void);
void				display_status(t_philos *philo, int id, char *action);
int					ft_atoi(char *str);
int					ft_error(t_philos *philo, int e_status, int level);
void				ft_free(t_philos *philo, int level);

#endif