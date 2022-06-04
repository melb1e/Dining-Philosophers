/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcele <mmarcele@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 23:29:55 by mmarcele          #+#    #+#             */
/*   Updated: 2022/06/04 23:31:53 by mmarcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
	else if (e_status == ERROR_INITIALIZATION)
		return (ERROR_INITIALIZATION_STRING);
	else
		return (ERROR_UNKNOWN_STRING);
}

int	ft_error(int e_status)
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
	return (e_status);
}
