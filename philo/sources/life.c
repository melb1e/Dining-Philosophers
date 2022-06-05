/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcele <mmarcele@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 23:29:47 by mmarcele          #+#    #+#             */
/*   Updated: 2022/06/05 13:21:53 by mmarcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	ft_usleep(time_t time)
{
	time_t	initial;

	initial = ft_timestamp();
	while (ft_timestamp() - initial < time)
		usleep(50);
	return ;
}

static int	philo_think(t_philos *philo, t_inst *inst)
{
	if (inst->death_status)
		return (EXIT_FAILURE);
	display_status(philo->installments, philo->id, PHILO_THINKING);
	return (OK);
}

static int	philo_sleep(t_philos *philo, t_inst *inst)
{
	if (inst->death_status)
		return (EXIT_FAILURE);
	display_status(inst, philo->id, PHILO_SLEEPING);
	ft_usleep(inst->time_to_sleep);
	return (OK);
}

static int	philo_eat(t_philos *philo, t_inst *inst)
{
	if (inst->death_status)
		return (EXIT_FAILURE);
	pthread_mutex_lock(&inst->forks[philo->left_fork_id]);
	display_status(inst, philo->id, PHILO_HAS_LEFT_FORK);
	if (inst->number == 1)
	{
		pthread_mutex_unlock(&inst->forks[philo->left_fork_id]);
		return (EXIT_PROC);
	}
	pthread_mutex_lock(&inst->forks[philo->right_fork_id]);
	display_status(inst, philo->id, PHILO_HAS_RIGHT_FORK);
	display_status(inst, philo->id, PHILO_EATING);
	philo->meals_done += 1;
	philo->last_ate = ft_timestamp();
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(&inst->forks[philo->left_fork_id]);
	pthread_mutex_unlock(&inst->forks[philo->right_fork_id]);
	return (OK);
}

void	*kettle(void *arg)
{
	t_philos	*philo;
	t_inst		*inst;

	philo = (t_philos *)arg;
	inst = philo->installments;
	if (philo->id % 2 == 0)
	{
		philo_think(philo, inst);
		ft_usleep(50);
	}
	while (inst->death_status == 0)
	{
		if (inst->meals_goal > 0)
			if (inst->meals_goal == philo->meals_done)
				return (NULL);
		if (philo_eat(philo, inst))
			return (NULL);
		if (inst->meals_goal > 0)
			if (inst->meals_goal == philo->meals_done)
				return (NULL);
		philo_sleep(philo, inst);
		philo_think(philo, inst);
	}
	return (NULL);
}
