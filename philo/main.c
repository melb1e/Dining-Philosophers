/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcele <mmarcele@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:09:07 by mmarcele          #+#    #+#             */
/*   Updated: 2022/05/31 17:09:07 by mmarcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	inizialize_mutex(t_installment *installment)
{
	int	i;

	i = installment->number_of_philosophers;
	while (--i >= 0)
	{
		if (pthread_mutex_init(&(installment->fork[i]), NULL))
			return (ft_error(ERROR_MUTEX));
	}
	if (pthread_mutex_init(&(installment->reporting), NULL))
		return (ft_error(ERROR_MUTEX));
	if (pthread_mutex_init(&(installment->meal), NULL))
		return (ft_error(ERROR_MUTEX));
	return (0);
}

static int	initialize_philosophers(t_installment *inst)
{
	int	i;

	i = inst->number_of_philosophers;
	while (--i >= 0)
	{
		inst->philosopher[i].id = i;
		inst->philosopher[i].id_left_fork = i;
		inst->philosopher[i].id_right_fork = (i + 1) % \
											inst->number_of_philosophers;
		inst->philosopher[i].last_meal = 0;
		inst->philosopher[i].installments = inst;
	}
	return (0);
}

static int	initialization(t_installment *inst, char **argv)
{
	inst->number_of_philosophers = ft_atoi(argv[1]);
	inst->time_to_die = ft_atoi(argv[2]);
	inst->time_to_eat = ft_atoi(argv[3]);
	inst->time_to_sleep = ft_atoi(argv[4]);
	inst->life_status = 0;
	inst->done = 0;
	if ((inst->number_of_philosophers < 2 || inst->number_of_philosophers > \
		200) || inst->time_to_die < 0 || inst->time_to_eat < 0 || \
		inst->time_to_sleep < 0)
	if (argv[5])
	{
		inst->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
		if (inst->number_of_times_each_philosopher_must_eat <= 0)
			return (ft_error(ERROR_MEALS));
	}
	else
		inst->number_of_times_each_philosopher_must_eat = -1;
	if (initialize_mutex(inst))
		return (ERROR_MUTEX);
	initialize_philosophers(inst);
	return (0);
}

int	main(int argc, char **argv)
{
	t_installment	installment;

	if (argc != 5 && argc != 6)
	{
		return (ft_error(ERROR_INPUT));
	}
	if (initialization(&installment, argv))
	{
		return (ft_error(ERROR_INPUT));
	}
	if (master(&installment))
	{
		return (ft_error(ERROR_THREADS));
	}
	return (0);
}