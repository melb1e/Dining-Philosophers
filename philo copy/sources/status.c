/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcele <mmarcele@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 23:29:40 by mmarcele          #+#    #+#             */
/*   Updated: 2022/06/05 00:33:28 by mmarcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_strcmp(char *str1, char *str2)
{
	size_t	i;

	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] == str2[i])
			i++;
		else if (str1[i] != str2[i])
			return (ERROR);
	}
	return (OK);
}

void	display_status(t_inst *inst, size_t id, char *status)
{
	pthread_mutex_lock(&inst->report_status);
	if (*status == 'h')
		printf("%li %li "GREEN"%s"BASIC"\n", \
				ft_timestamp() - inst->timestamp, id + 1, status);
	else if (status[3] == 'e')
		printf("%li %li "CYAN"%s"BASIC"\n", \
				ft_timestamp() - inst->timestamp, id + 1, status);
	else if (*status == 'i')
		printf("%li %li "YELLOW"%s"BASIC"\n", \
				ft_timestamp() - inst->timestamp, id + 1, status);
	else if (*status == 'd')
		printf("%li %li "RED"%s"BASIC"\n", \
				ft_timestamp() - inst->timestamp, id + 1, status);
	if (ft_strcmp(status, PHILO_DEAD))
		pthread_mutex_unlock(&inst->report_status);
}
