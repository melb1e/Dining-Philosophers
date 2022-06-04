/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcele <mmarcele@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 00:42:59 by mmarcele          #+#    #+#             */
/*   Updated: 2022/06/05 00:59:35 by mmarcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	philo_think(t_philos *philo)
{
	display_status(philo, philo->id, PHILO_THINKING);
	return ;
}

static void	philo_sleep(t_philos *philo)
{
	time_t	time;

	display_status(philo, philo->id, PHILO_SLEEPING);
	time = ft_timestamp();
	usleep(philo->time_to_sleep);
	while (ft_timestamp() - time < philo->time_to_sleep)
		continue ;
	return ;
}

static int	philo_eat(t_philos *philo)
{
	sem_wait(philo->forks_status);
	display_status(philo, philo->id, PHILO_HAS_LEFT_FORK);
	if (philo->number == 1)
		sem_post(philo->forks_status);
	if (philo->number == 1)
		return (EXIT_FAILURE);
	sem_wait(philo->forks_status);
	display_status(philo, philo->id, PHILO_HAS_RIGHT_FORK);
	display_status(philo, philo->id, PHILO_EATING);
	philo->last_ate = ft_timestamp();
	usleep(philo->time_to_eat);
	while (ft_timestamp() - philo->last_ate < philo->time_to_eat)
		continue ;
	philo->meals_done += 1;
	sem_post(philo->forks_status);
	sem_post(philo->forks_status);
	return (OK);
}

void	ft_usleep(time_t time)
{
	time_t	initial;

	initial = ft_timestamp();
	while (ft_timestamp() - initial < time)
		usleep(100);
	return ;
}

int	kettle(t_philos *philo)
{
	if (pthread_create(&philo->death_status, NULL, &death_checker, (void *)philo))
		return (ERROR_THREADS);
	if (philo->id % 2 == 1)
		ft_usleep(500);
	while (TRUE)
	{
		if (philo->meals_goal)
			if (philo->meals_goal == philo->meals_done)
				break ;
		if (philo_eat(philo))
			break ;
		else
		{
			philo_sleep(philo);
			philo_think(philo);
		}
	}
	if (pthread_join(philo->dead, NULL))
		return (ERROR_THREADS);
	return (OK);
}
