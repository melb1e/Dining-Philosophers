/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcele <mmarcele@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 23:29:30 by mmarcele          #+#    #+#             */
/*   Updated: 2022/06/05 12:10:37 by mmarcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static	int	ft_overflow(unsigned long long nbr, int sign)
{
	if (nbr > ULLONG_MAX && sign == -1)
		return (ERROR_OVERFLOW);
	else if ((nbr > 2147483647 && sign == 1) || (nbr > 2147483648 && \
				sign == -1))
		return (ERROR_OVERFLOW);
	return (nbr * sign);
}

int	ft_atoi(const char *str)
{
	unsigned long long	nbr;
	long long			sign;
	int					i;

	i = 0;
	nbr = 0;
	sign = 1;
	while (str[i] >= 8 && str[i] <= 32)
	{
		if (str[i] == 27)
			return (ERROR);
		i++;
	}
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		nbr = nbr * 10 + str[i++] - '0';
	return (ft_overflow(nbr, sign));
}

int	scan_args(const int ac, const char **av)
{
	if (ac - 1 <= MAX_ARGS && ac - 1 >= MIN_ARGS)
		if (ft_atoi(av[1]) > 0 && ft_atoi(av[2]) > 0 && \
			ft_atoi(av[3]) > 0 && ft_atoi(av[4]) > 0 && \
			(ac - 1 == MIN_ARGS || \
			(ac - 1 == MAX_ARGS && ft_atoi(av[5]) > 0)))
			return (OK);
	return (ERROR_INPUT);
}

time_t	ft_timestamp(void)
{
	struct timeval	time;
	time_t			ms;

	gettimeofday(&time, NULL);
	ms = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (ms);
}
