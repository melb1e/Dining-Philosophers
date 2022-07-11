#include "../includes/philo.h"

static int	kill_children(t_philos *philo)
{
	int	i;

	i = 0;
	while (i < philo->number)
	{
		kill(philo->pid[i++], SIGKILL);
	}
	return (OK);
}

static int	thread_canceller(int e_status)
{
	ft_error(NULL, e_status, 1);
	exit(1);
}

int	thread_master(t_philos *philo)
{
	int	i;
	int	status;

	i = 0;
	philo->timestamp = ft_timestamp();
	while (i < philo->number)
	{
		philo->pid[i] = fork();
		if (philo->pid[i] == -1)
			return (ERROR_FORKING);
		if (philo->pid[i++] == 0)
		{
			philo->id = i;
			philo->last_ate = philo->timestamp;
			if (kettle(philo) != OK)
				return (thread_canceller(ERROR_THREADS));
		}
	}
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFSIGNALED(status) || WIFEXITED(status))
			return (kill_children(philo));
	}
	return (OK);
}
