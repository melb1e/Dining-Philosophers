/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcele <mmarcele@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:14:58 by mmarcele          #+#    #+#             */
/*   Updated: 2022/05/31 17:14:58 by mmarcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <signal.h>

# include <sys/wait.h>

# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>

# define ERROR_SEMAPHORE	"Error 106 [Mutex initialization or creation]\n"
# define ERROR_MEALS		"Error 105 [Wrong input in \
							number_of_times_each_philosopher_must_eat]\n"
# define ERROR_INPUT		"Error 101 [Wrong input, try ./philo \
							(number_of_philosophers) \
							(time_to_die) \
							(time_to_eat) \
							(time_to_sleep) \
							{number_of_times_each_philosopher_must_eat}\n"
# define ERROR_PROCESS		"Error 103 [Something went wrong with process \
							creation]\n"
typedef	struct s_philosopher
{
	int						id;
	int						meals_done;
	int						id_left_fork;
	int						id_right_fork;
	time_t					last_meal;
	pthread_t				life_status;
	struct s_installment	*installment;
	pid_t					pid;
}							t_philosopher;

typedef struct s_installment
{
	time_t					time_to_die;
	time_t					time_to_eat;
	time_t					time_to_sleep;
	int						number_of_philosophers;
	int						number_of_times_each_philosopher_must_eat;
	int						life_status;
	int						done;
	int						timestamp;
	sem_t					*meal;
	sem_t					*fork;
	sem_t					*reporting;
	t_philosopher			philosopher[200];
}							t_installment;

/*
** Master functions
*/
int	master(t_installment *inst);

/*
** Initialization functions
*/
int	inizialize_mutex(t_installment *installment);
int	initialize_philosophers(t_installment *inst);
int	initialization(t_installment *inst, char **argv);

/*
** Utils
*/
void	current_print(t_installment *inst, int id, char *string);
void	sleeping(time_t time, t_installment *inst);
time_t	timestamp(void);
int		ft_atoi(const char *str);
void	ft_error(char *error_number);

#endif