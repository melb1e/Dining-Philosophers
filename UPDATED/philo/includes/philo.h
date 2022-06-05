/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcele <mmarcele@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 23:30:03 by mmarcele          #+#    #+#             */
/*   Updated: 2022/06/05 13:03:18 by mmarcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
/*
** Headers of the project
*/
# include "defines.h"

typedef struct s_philos
{
	int				id;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				right_fork_id;
	int				left_fork_id;
	int				meals_done;
	time_t			last_ate;
	time_t			initial;
	struct s_inst	*installments;
}					t_philos;

typedef struct s_inst
{
	int				number;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				meals_goal;
	int				death_status;
	time_t			timestamp;
	pthread_t		*thread;
	pthread_mutex_t	*forks;
	pthread_mutex_t	report_status;
	t_philos		*philos;
}					t_inst;
/*
** Initialization and scanning of given arguments
*/
int					scan_args(const int ac, const char **av);
t_inst				*initialization(int ac, const char **av);
int					distribute_memory(t_inst *inst);
int					create_philos(t_inst *inst);

/*
** Thread creation
*/
int					thread_master(t_inst *inst);

/*
** Master functions
*/
void				*kettle(void *arg);
void				*death_checker(void *arg);

/*
** Utils functions
*/
time_t				ft_timestamp(void);
int					display_status(t_inst *inst, size_t id, char *status);
int					ft_atoi(const char *str);
int					ft_error(int e_status, t_inst *inst, int level);
void				ft_free(t_inst *inst);
void				ft_destroy_mutex(t_inst *inst);		

#endif