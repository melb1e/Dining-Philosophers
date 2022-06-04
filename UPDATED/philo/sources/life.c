/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcele <mmarcele@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 23:29:47 by mmarcele          #+#    #+#             */
/*   Updated: 2022/06/05 00:31:26 by mmarcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	philo_think(t_philos *philo)
{
	display_status(philo->installments, philo->id, PHILO_THINKING);
	return ;
}

static void	philo_sleep(t_philos *philo)
{
	time_t	time;

	display_status(philo->installments, philo->id, PHILO_SLEEPING);
	time = ft_timestamp();
	usleep(philo->installments->time_to_sleep * 1000 - 10000);
	while (ft_timestamp() - time < philo->installments->time_to_sleep)
		continue ;
	return ;
}

static void	philo_eat(t_philos *philo)
{
	pthread_mutex_lock(&philo->installments->forks[philo->left_fork_id]);
	display_status(philo->installments, philo->id, PHILO_HAS_LEFT_FORK);
	pthread_mutex_lock(&philo->installments->forks[philo->right_fork_id]);
	display_status(philo->installments, philo->id, PHILO_HAS_RIGHT_FORK);
	pthread_mutex_lock(&philo->eat_status);
	philo->last_ate = ft_timestamp();
	philo->philo_eat = 1;
	display_status(philo->installments, philo->id, PHILO_EATING);
	usleep(philo->installments->time_to_eat * 1000 - 10000);
	while (ft_timestamp() - philo->last_ate < philo->installments->time_to_eat)
		continue ;
	philo->meals_done += 1;
	philo->philo_eat = 0;
	pthread_mutex_unlock(&philo->installments->forks[philo->left_fork_id]);
	pthread_mutex_unlock(&philo->installments->forks[philo->right_fork_id]);
	pthread_mutex_unlock(&philo->eat_status);
	return ;
}

void	*kettle(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	while (!philo->installments->death_status)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
		usleep(100);
	}
	return (NULL);
}
