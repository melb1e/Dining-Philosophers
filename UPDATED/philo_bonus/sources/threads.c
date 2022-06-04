/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcele <mmarcele@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 00:43:05 by mmarcele          #+#    #+#             */
/*   Updated: 2022/06/05 01:05:39 by mmarcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	kill_children(t_philos *philo)
{
	int	i;

	i = 0;
	while (i < philo->number)
	{
		// pthread_cancel(philo->death_status);
		kill(philo->pid[i++], SIGKILL);
	}
	return (OK);
}

static int	thread_canceller(t_philos *philo, int e_status)
{
	int	i;

	i = 0;
	while (i < philo->number)
	{
		pthread_cancel(philo->death_status);
	}
	return (e_status);
}

int	thread_master(t_philos *philo)
{
	int	i;
	int status;

	i = 0;
	philo->timestamp = ft_timestamp();
	while (i < philo->number)
	{
		philo->pid[i] = fork();
		if (philo->pid[i] == -1)
			return (ERROR_FORKING);
		if (philo->pid[i++] == 0)
		{
			philo->id = i;
			philo->last_ate = philo->timestamp;
			if (kettle(philo) != OK)
				return (thread_canceller(philo, ERROR_THREADS));
		}
	}
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFSIGNALED(status) || WIFEXITED(status))
			return (kill_children(philo));
	}
	return (OK);
}
