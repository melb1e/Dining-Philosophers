/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcele <mmarcele@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 23:29:37 by mmarcele          #+#    #+#             */
/*   Updated: 2022/06/05 00:38:07 by mmarcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

time_t	ft_timestamp(void)
{
	struct timeval	time;
	time_t			ms;

	gettimeofday(&time, NULL);
	ms = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (ms);
}

static int	thread_canceller(t_inst *inst, int e_status)
{
	int	i;

	i = 0;
	while (i < inst->number)
	{
		pthread_cancel(inst->philos[i]->thread);
		pthread_cancel(inst->philos[i]->dead);
		i++;
	}
	return (e_status);
}

int	thread_master(t_inst *inst)
{
	int	i;

	i = 0;
	inst->timestamp = ft_timestamp();
	while (i < inst->number)
	{
		inst->philos[i]->last_ate = ft_timestamp();
		if (pthread_create(&inst->philos[i]->thread, NULL, &kettle, \
			(void *)inst->philos[i]))
			return (ERROR_THREADS);
		i++;
		usleep(100);
	}
	i = 0;
	while (i < inst->number)
	{
		if (pthread_create(&inst->philos[i]->dead, NULL, &death_checker, \
			(void *)inst->philos[i]))
			return (ERROR_THREADS);
		i++;
		usleep(100);
	}
	while (!inst->death_status)
		continue ;
	return (thread_canceller(inst, OK));
}
