/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcele <mmarcele@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 23:29:40 by mmarcele          #+#    #+#             */
/*   Updated: 2022/06/05 12:55:54 by mmarcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	display_status(t_inst *inst, size_t id, char *status)
{
	if (inst->death_status && status[0] != 'd')
		return (EXIT_FAILURE);
	pthread_mutex_lock(&inst->report_status);
	if (inst->death_status && status[0] != 'd')
		return (EXIT_FAILURE);
	if (status[0] == 'h')
		printf("%li %li "GREEN"%s"BASIC"\n", \
				ft_timestamp() - inst->timestamp, id, status);
	else if (status[0] == 'd')
		printf("%li %li "RED"%s"BASIC"\n", \
				ft_timestamp() - inst->timestamp, id, status);
	else if (status[3] == 'e')
		printf("%li %li "CYAN"%s"BASIC"\n", \
				ft_timestamp() - inst->timestamp, id, status);
	else if (status[0] == 'i')
		printf("%li %li "YELLOW"%s"BASIC"\n", \
				ft_timestamp() - inst->timestamp, id, status);
	if (status[0] != 'd')
		pthread_mutex_unlock(&inst->report_status);
	return (OK);
}
