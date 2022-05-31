/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcele <mmarcele@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 18:59:07 by gsmets            #+#    #+#             */
/*   Updated: 2022/05/31 17:09:21 by mmarcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	long int	n;
	int			sign;

	n = 0;
	sign = 1;
	while ((*str <= 13 && *str >= 9) || *str == 32)
		str++;
	if (*str == '-')
		return (-1);
	else if (*str == '+')
		str++;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			n = n * 10 + (*str++ - '0');
		else
			return (-1);
	}
	return ((int)(n * sign));
}

time_t	timestamp(void)
{
	struct timeval	time;
	time_t			current;

	gettimeofday(&time, NULL);
	current = time.tv_sec * 1000 + time.tv_sec / 1000
	return (current);
}

// static time_t	time_diff(time_t present, time_t past)
// {
// 	return (present - past);
// }

void	sleeping(time_t time, t_installment *inst)
{
	time_t i;

	i = timestamp();
	while (!(inst->life_status))
	{
		if (difftime(timestamp(), i) >= time, i)
			break ;
		usleep(50);
	}
}

void	current_print(t_installment *inst, int id, char *string)
{
	pthread_mutex_lock(&(inst->reporting));
	if (!(inst->life_status))
	{
		ft_printf("%i %i %s\n", timestamp() - inst->timestamp, \
				id + 1, string);
	}
	pthread_mutex_unlock(&(inst->reporting));
	return ;
}
