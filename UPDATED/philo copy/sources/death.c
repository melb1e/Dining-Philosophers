/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcele <mmarcele@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 23:29:59 by mmarcele          #+#    #+#             */
/*   Updated: 2022/06/04 23:31:22 by mmarcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*death_checker(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	while (!philo->installments->death_status)
	{
		if (!philo->philo_eat && ft_timestamp() - philo->last_ate >= \
			philo->installments->time_to_die)
		{
			pthread_mutex_lock(&philo->eat_status);
			display_status(philo->installments, philo->id, PHILO_DEAD);
			philo->installments->death_status = 1;
			pthread_mutex_unlock(&philo->eat_status);
		}
		if (philo->installments->philos[philo->installments->number - \
			1]->meals_done == philo->installments->meals_goal)
			philo->installments->death_status = 1;
		usleep(100);
	}
	return (NULL);
}
