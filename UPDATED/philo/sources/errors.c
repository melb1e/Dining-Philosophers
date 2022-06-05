/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcele <mmarcele@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 23:29:55 by mmarcele          #+#    #+#             */
/*   Updated: 2022/06/05 13:03:13 by mmarcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_destroy_mutex(t_inst *inst)
{
	int	i;
	int	e_status;

	i = 0;
	e_status = OK;
	while (i < inst->number)
	{
		if (pthread_mutex_destroy(&inst->forks[i]))
			e_status = ERROR_MUTEX_DESTRUCTION;
		i++;
	}
	if (e_status != OK)
		ft_error(e_status, NULL, 1);
	pthread_mutex_destroy(&inst->report_status);
	return ;
}

static char	*ft_erno_helper(int e_status)
{
	if (e_status == ERROR_INPUT)
		return (ERROR_INPUT_STRING);
	else if (e_status == ERROR_THREADS)
		return (ERROR_THREADS_STRING);
	else if (e_status == ERROR_MEALS)
		return (ERROR_INPUT_STRING);
	else if (e_status == ERROR_MUTEX)
		return (ERROR_MUTEX_STRING);
	else if (e_status == ERROR_MUTEX_DESTRUCTION)
		return (ERROR_MUTEX_DESTRUCTION_STR);
	else if (e_status == ERROR_INITIALIZATION)
		return (ERROR_INITIALIZATION_STRING);
	else if (e_status == ERROR_MALLOC)
		return (ERROR_MALLOC_STING);
	else
		return (ERROR_UNKNOWN_STRING);
}

void	ft_free(t_inst *inst)
{
	if (inst->philos)
		free(inst->philos);
	if (inst->forks)
		free(inst->forks);
	if (inst->thread)
		free(inst->thread);
	free(inst);
}

int	ft_error(int e_status, t_inst *inst, int level)
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
		ft_free(inst);
	return (e_status);
}
