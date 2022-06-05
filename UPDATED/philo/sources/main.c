/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcele <mmarcele@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 23:29:44 by mmarcele          #+#    #+#             */
/*   Updated: 2022/06/05 13:03:27 by mmarcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
			return (ft_error(ERROR_INITIALIZATION, inst, 3));
		if (distribute_memory(inst) == ERROR_MALLOC)
			return (ft_error(ERROR_MALLOC, inst, 3));
		e_status = create_philos(inst);
		if (e_status != OK)
			return (ft_error(e_status, inst, 3));
		e_status = thread_master(inst);
		if (e_status != OK)
			return (ft_error(e_status, inst, 3));
	}
	else
		return (ft_error(e_status, inst, 1));
	ft_destroy_mutex(inst);
	ft_free(inst);
	return (OK);
}
