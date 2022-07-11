#include "../includes/philo.h"

void	*death_checker(void *arg)
{
	t_philos	*philos;
	t_inst		*inst;
	int			i;

	inst = (t_inst *)arg;
	philos = inst->philos;
	while (TRUE)
	{
		i = 0;
		while (i < inst->number)
		{
			if (inst->meals_goal > 0)
				if (inst->meals_goal == philos->meals_done)
					return (NULL);
			if (ft_timestamp() - philos[i].last_ate >= philos[i].time_to_die)
			{
				inst->death_status = 1;
				display_status(inst, philos->id, PHILO_DEAD);
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}
