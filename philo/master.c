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
	pthread_mutex_lock(&(inst->fork[philo->id_left_fork]));
	current_print(inst, philo->id, "has taken a fork");
	pthread_mutex_lock(&(inst->fork[philo->id_right_fork]));
	current_print(inst, philo->id, "has taken a fork");
	pthread_mutex_lock(&(inst->meal));
	current_print(inst, philo->id, "is eating");
	philo->last_meal = timestamp(&(inst->meal));
	pthread_mutex_unlock();
	sleep_process(inst->time_to_eat, inst);
	philo->meals_done += 1;
	pthread_mutex_unlock(&(inst->fork[philo->id_right_fork]));
	pthread_mutex_unlock(&(inst->fork[philo->id_left_fork]));
}

static void	detect_deaths(t_installment *inst, t_philosopher *ph)
{
	int	i;

	while (!(inst->done))
	{
		i = 0;
		while (i < inst->number_of_philosophers && !(inst->life_status))
		{
			pthread_mutex_lock(&(inst->meal));
			if (difftime(timestamp(), ph[i++].last_meal) > inst->time_to_death)
			{
				current_print(inst, ph, "died");
				inst->life_status = 1;
			}
			pthread_mutex_unlock(&(inst->meal));
			usleep(100);
		}
		if (inst->life_status)
			break ;
		i = 0;
		while (inst->number_of_times_each_philosopher_must_eat != -1 && \
				i < inst->number_of_philosophers && \
				ph[i].meals_done > inst->number_of_times_each_philosopher_must_eat)
			i++;
		if (i == inst->number_of_philosophers)
			inst->done = 1;
	}
}

static void	leave(t_installment *inst, t_philosopher *philos)
{
	int	i;

	i = 0;
	while (i < inst->number_of_philosophers)
		pthread_join(philos[i++].id, NULL);
	i = 0;
	while (i < inst->number_of_philosophers)
		pthread_mutex_destroy(&(inst->fork[i]));
	pthread_mutex_destroy(&(inst->reporting));
}

static void	*action(void *input)
{
	t_installment	*inst;
	t_philosopher	*philo;
	int				i;

	i = 0;
	philo = (t_philosopher *)input;
	inst = philo->installment;
	if (philo->id % 2)
		usleep(15000);
	while (!inst->life_status)
	{
		eat_process(philo);
		if (inst->done)
			break;
		current_print(inst, philo->id, "is sleeping");
		sleeping(inst->time_to_sleep, inst);
		current_print(inst, philo->id, "is thinking");
		i++;
	}
	return (NULL);
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
		if (pthread_create(&(philo[i].thread), NULL, action, &(philo[i])))
			return (ft_error(ERROR_THREADS));
		philo[i++].last_meal = timestamp();
	}
	detect_deaths(inst, inst->philosopher);
	leave(inst, philo);
	
}