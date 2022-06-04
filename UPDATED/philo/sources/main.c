/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcele <mmarcele@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 23:29:44 by mmarcele          #+#    #+#             */
/*   Updated: 2022/06/05 00:31:52 by mmarcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	ft_free(t_inst *inst)
{
	int	i;

	i = 0;
	if (inst)
	{
		while (i < inst->number)
		{
			free(inst->philos[i++]);
		}
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
