#include "../includes/philo.h"

int	thread_master(t_inst *inst)
{
	pthread_t	dead;
	int			i;

	i = 0;
	inst->timestamp = ft_timestamp();
	while (i < inst->number)
	{
		inst->philos[i].initial = inst->timestamp;
		inst->philos[i].last_ate = inst->timestamp;
		i++;
	}
	i = 0;
	while (i < inst->number)
	{
		pthread_create(&inst->thread[i], NULL, &kettle, &inst->philos[i]);
		i++;
	}
	pthread_create(&dead, NULL, &death_checker, (void *)inst);
	pthread_mutex_unlock(&inst->report_status);
	pthread_join(dead, NULL);
	i = 0;
	while (i < inst->number)
		pthread_join(inst->thread[i++], NULL);
	return (OK);
}
