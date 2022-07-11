#include "../includes/philo.h"

/*
**	Create philos HERE HERE
*/
int	create_philos(t_inst *inst)
{
	int	i;

	i = 0;
	while (i < inst->number)
	{
		inst->philos[i].id = i + 1;
		inst->philos[i].time_to_die = inst->time_to_die;
		inst->philos[i].time_to_eat = inst->time_to_eat;
		inst->philos[i].time_to_sleep = inst->time_to_sleep;
		inst->philos[i].meals_done = 0;
		inst->philos[i].left_fork_id = i;
		if (i < inst->number - 1)
			inst->philos[i].right_fork_id = i + 1;
		else
			inst->philos[i].right_fork_id = 0;
		inst->philos[i].last_ate = 0;
		inst->philos[i].installments = inst;
		i++;
	}
	i = 0;
	while (i < inst->number)
		if (pthread_mutex_init(&inst->forks[i++], NULL))
			return (ERROR_MUTEX);
	return (OK);
}

int	distribute_memory(t_inst *inst)
{
	inst->philos = malloc(sizeof(t_philos) * inst->number);
	if (inst->philos == NULL)
		return (ERROR_MALLOC);
	inst->forks = malloc(sizeof(pthread_mutex_t) * inst->number);
	if (inst->forks == NULL)
		return (ERROR_MALLOC);
	inst->thread = malloc(sizeof(pthread_t) * inst->number);
	if (inst->thread == NULL)
		return (ERROR_MALLOC);
	return (OK);
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
	inst->timestamp = 0;
	if (pthread_mutex_init(&inst->report_status, NULL) != OK)
		return (NULL);
	inst->thread = NULL;
	inst->forks = NULL;
	inst->philos = NULL;
	return (inst);
}
