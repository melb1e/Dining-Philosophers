/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcele <mmarcele@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 00:42:54 by mmarcele          #+#    #+#             */
/*   Updated: 2022/06/05 14:09:22 by mmarcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_philos	*initialization(int ac, char **av)
{
	t_philos	*philo;
	int		i;

	i = 1;
	philo = malloc(sizeof(t_philos));
	if (philo == NULL)
		return (NULL);
	philo->number = ft_atoi(av[i++]);
	philo->time_to_die = ft_atoi(av[i++]);
	philo->time_to_eat = ft_atoi(av[i++]);
	philo->time_to_sleep = ft_atoi(av[i]);
	if (ac - 1 == P_MAX_ARGS)
		philo->meals_goal = ft_atoi(av[++i]);
	else if (ac - 1 == P_MIN_ARGS)
		philo->meals_goal = -1;
	philo->id = 0;
	philo->meals_done = 0;
	philo->dead = 0;
	philo->timestamp = 0;
	philo->last_ate = 0;
	return (philo);
}
