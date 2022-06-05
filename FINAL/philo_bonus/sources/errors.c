/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcele <mmarcele@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 00:42:43 by mmarcele          #+#    #+#             */
/*   Updated: 2022/06/05 14:04:42 by mmarcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static char	*ft_erno_helper(int e_status)
{
	if (e_status == ERROR_INPUT)
		return (ERROR_INPUT_STRING);
	else if (e_status == ERROR_THREADS)
	return (ERROR_INPUT_STRING);
	else if (e_status == ERROR_MEALS)
	return (ERROR_INPUT_STRING);
	else if (e_status == ERROR_MUTEX)
	return (ERROR_INPUT_STRING);
	else if (e_status == ERROR_SEMAPHORE)
		return (ERROR_INPUT_STRING);
	else if (e_status == ERROR_INITIALIZATION)
		return (ERROR_INITIALIZATION_STRING);
	else
		return (ERROR_UNKNOWN_STRING);
}

void	ft_free(t_philos *philo, int level)
{
	sem_unlink("/report");
	sem_unlink("/forks");
	sem_close(philo->report_status);
	sem_close(philo->forks_status);
	free(philo->pid);
	free(philo);
	if (level != OK)
		exit(level);
}

int	ft_error(t_philos *philo, int e_status, int level)
{
	if (!e_status)
	{
		printf("[Debug]\n");
		e_status = DEBUG;
	}
	else if (e_status)
	{
		printf("%s\n", ft_erno_helper(e_status));
	}
	if (level == 3)
		ft_free(philo, e_status);
	exit(e_status);
}
