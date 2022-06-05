/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcele <mmarcele@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 00:42:48 by mmarcele          #+#    #+#             */
/*   Updated: 2022/06/05 00:42:50 by mmarcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*death_checker(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	while (TRUE)
	{
		if (philo->meals_goal)
			if (philo->meals_goal == philo->meals_done)
				break ;
		if (ft_timestamp() - philo->last_ate >= philo->time_to_die)
		{
			philo->dead = 1;
			display_status(philo, philo->id, PHILO_DEAD);
			break ;
		}
	}
	if (philo->dead)
		exit(EXIT_FAILURE);
	else
		exit(0);
}
