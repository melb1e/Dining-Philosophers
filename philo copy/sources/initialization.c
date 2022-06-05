/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcele <mmarcele@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 23:29:52 by mmarcele          #+#    #+#             */
/*   Updated: 2022/06/05 00:25:52 by mmarcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*
**	Create philos HERE HERE
*/
static t_philos	**free_philos(t_philos **philos)
{
	int	i;

	i = 0;
	while (philos[i] != NULL)
		free(philos[i++]);
	free(philos);
	philos = NULL;
	return (philos);
}

static t_philos	**create_philos(t_inst *inst)
{
	t_philos	**philos;
	int			i;

	i = 0;
	philos = malloc(sizeof(t_philos *) * inst->number + 1);
	if (philos == NULL)
		return (NULL);
	while (i < inst->number)
	{
		philos[i] = malloc(sizeof(t_philos));
		if (philos[i] == NULL)
			return (free_philos(philos));
		if (pthread_mutex_init(&philos[i]->eat_status, NULL))
			return (NULL);
		philos[i]->installments = inst;
		philos[i]->id = i;
		philos[i]->philo_eat = 0;
		philos[i]->meals_done = 0;
		philos[i]->left_fork_id = i;
		philos[i]->right_fork_id = (i + 1) % philos[i]->installments->number;
		i++;
	}
	return (philos);
}

/*
**	Create forks for installments structure
*/

static pthread_mutex_t	*create_forks(t_inst *inst)
{
	pthread_mutex_t	*forks;
	int				i;

	i = 0;
	if (inst->number <= ERROR_OVERFLOW || \
	inst->meals_goal < -1 || \
	inst->time_to_die <= ERROR_OVERFLOW || \
	inst->time_to_eat <= ERROR_OVERFLOW || \
	inst->time_to_sleep <= ERROR_OVERFLOW)
		return (NULL);
	forks = malloc(sizeof(pthread_mutex_t) * inst->number);
	if (forks == NULL)
		return (NULL);
	while (i < inst->number)
		if (pthread_mutex_init(&forks[i++], NULL))
			return (NULL);
	return (forks);
}

/*
**	Initialize installments
*/

t_inst	*initialization(int ac, const char **av)
{
	t_inst	*inst;
	int		i;

	i = 1;
	inst = malloc(sizeof(t_inst));
	if (inst == NULL)
		return (NULL);
	inst->number = ft_atoi(av[i++]);
	inst->time_to_die = ft_atoi(av[i++]);
	inst->time_to_eat = ft_atoi(av[i++]);
	inst->time_to_sleep = ft_atoi(av[i]);
	if (ac - 1 == MAX_ARGS)
		inst->meals_goal = ft_atoi(av[++i]);
	else if (ac - 1 == MIN_ARGS)
		inst->meals_goal = -1;
	inst->death_status = 0;
	inst->forks = create_forks(inst);
	if (inst->forks == NULL)
		return (NULL);
	inst->philos = create_philos(inst);
	if (inst->philos == NULL || inst->number == 0)
		return (NULL);
	if (pthread_mutex_init(&inst->report_status, NULL) != 0)
		return (NULL);
	return (inst);
}
