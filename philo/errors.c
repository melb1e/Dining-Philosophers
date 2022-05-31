/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcele <mmarcele@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 18:26:41 by mmarcele          #+#    #+#             */
/*   Updated: 2022/05/31 18:26:41 by mmarcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error(char *error)
{
	if (!error)
		return (ft_printf("[Debug]\n"));
	if (error)
		return (ft_printf(error));
	return (1);
}
