/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcele <mmarcele@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 23:29:44 by mmarcele          #+#    #+#             */
/*   Updated: 2022/06/05 10:40:52 by mmarcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	ft_free(t_inst *inst, int level)
{
	int	i;

	i = 0;
	if (inst)
	{
		while (i < inst->number)
		{
			if (level == 3)
			{
				pthread_mutex_destroy(&inst->philos[i]->eat_status);
				pthread_mutex_destroy(&inst->forks[i]);
			}
			free(inst->philos[i]);
		}
		pthread_mutex_destroy(&inst->report_status);
		free(inst->forks);
		free(inst->philos);
		free(inst);
	}
}

int	main(const int ac, const char **av)
{
	t_inst	*inst;
	long	e_status;

	inst = NULL;
	e_status = scan_args(ac, av);
	if (e_status == OK)
	{
		inst = initialization(ac, av);
		if (inst == NULL)
			return (ft_error(ERROR_INITIALIZATION));
		e_status = thread_master(inst);
		if (e_status != OK)
			return (ft_error(e_status));
	}
	else
		return (ft_error(e_status));
	ft_free(inst);
	return (OK);
}
