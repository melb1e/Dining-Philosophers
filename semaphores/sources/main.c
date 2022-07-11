#include "../includes/philo.h"

int	main(int ac, char **av)
{
	t_philos	*philo;
	int			e_status;

	philo = NULL;
	e_status = scan_args(ac, av);
	if (e_status == OK)
	{
		philo = initialization(ac, av);
		if (philo == NULL)
			ft_error(philo, ERROR_INITIALIZATION, 3);
		if (create_semaphores(philo) != OK)
			ft_error(philo, ERROR_SEMAPHORE, 3);
		e_status = thread_master(philo);
		if (e_status != OK)
			ft_error(philo, e_status, 3);
		ft_free(philo, e_status);
	}
	else
		ft_error(NULL, e_status, 1);
	exit(OK);
}
