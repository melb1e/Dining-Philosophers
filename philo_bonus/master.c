/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcele <mmarcele@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:44:56 by mmarcele          #+#    #+#             */
/*   Updated: 2022/05/31 17:44:56 by mmarcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eat_process(t_philosopher *philo)
{
	t_installment	*inst;

	inst = philo->installment;
	sem_wait(inst->fork);
	current_print(inst, philo->id, "has taken a fork");
	sem_wait(inst->fork);
	current_print(inst, philo->id, "has taken a fork");
	sem_wait(inst->meal);
	current_print(inst, philo->id, "is eating");
	philo->last_meal = timestamp();
	sem_post(inst->meal);
	sleeping(inst->time_to_eat, inst);
	philo->meals_done += 1;
	sem_post(inst->fork);
	sem_post(inst->fork);
}

static void	*detect_deaths(void *input)
{
	t_philosopher	*philo;
	t_installment	*inst;

	philo = (t_philosopher *)input;
	inst = philo->installment;
	while (1)
	{
		sem_wait(inst->meal);
		if (difftime(timestamp(), philo->t_last_meal) > inst->time_to_die)
		{
			current_print(inst, ph, "died");
			inst->life_status = 1;
			sem_wait(inst->reporting);
			exit (1);
		}
		sem_post(inst->meal);
		if (inst->life_status)
			break ;
		usleep(1000);
		if (philo->meals_done >= \
			inst->number_of_times_each_philosopher_must_eat && \
			inst->number_of_times_each_philosopher_must_eat != -1)
			break ;
	}
	return (NULL);
}

static void	leave(t_installment *inst, t_philosopher *philos)
{
	int	i;
	int	value;

	i = 0;
	while (i < inst->number_of_philosophers)
	{
		waitpid(-1, &value, 0);
		if (value)
		{
			i = 0;
			while (i < inst->number_of_philosophers)
				kill(inst->philosopher[i++].pid, 15);
			break ;
		}
		i++;
	}
	i = 0;
	sem_close(inst->fork);
	sem_close(inst->reporting);
	sem_close(inst->meal);
	sem_unlink("/philo_fork");
	sem_unlink("/philo_report");
	sem_unlink("/philo_meal");
}

static void	action(void *input)
{
	t_installment	*inst;
	t_philosopher	*philo;

	philo = (t_philosopher *)input;
	inst = philo->installment;
	philo->last_meal = timestamp();
	pthread_create(&(philo->life_status), NULL, detect_deaths, input);
	if (philo->id % 2)
		usleep(15000);
	while (!inst->life_status)
	{
		eat_process(philo);
		if (philo->meals_done >= \
			inst->number_of_times_each_philosopher_must_eat && \
			inst->number_of_times_each_philosopher_must_eat != -1)
			break ;
		current_print(inst, philo->id, "is sleeping");
		sleeping(inst->time_to_sleep, inst);
		current_print(inst, philo->id, "is thinking");
		i++;
	}
	pthread_join(philo->life_status, NULL);
	if (inst->life_status)
		exit(1);
	return (0);
}

int	master(t_installment *inst)
{
	t_philosopher	*philo;
	int				i;

	i = 0;
	philo = inst->philosopher;
	inst->timestamp = timestamp();
	while (i < inst->number_of_philosophers)
	{
		philo[i].pid = fork();
		if (philo[i].pid < 0)
			return (ft_error(ERROR_PROCESS))
		if (philo[i].pid == 0)
			action(&(philo[i++]));
		usleep(100);
	}
	leave(inst, philo);
	return (0);
}
