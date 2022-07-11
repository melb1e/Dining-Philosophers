#include "../includes/philo.h"

static int	free_semaphore(t_philos *philo, int e_status, int level)
{
	if (level == 3)
		free(philo->pid);
	free(philo);
	return (e_status);
}

int	create_semaphores(t_philos *philo)
{
	sem_unlink("/forks");
	sem_unlink("/report");
	philo->forks_status = sem_open("/forks", O_CREAT, S_IRWXU, philo->number);
	if (philo->forks_status == SEM_FAILED)
		return (free_semaphore(philo, ERROR_SEMAPHORE, 1));
	philo->report_status = sem_open("/report", O_CREAT, S_IRWXU, 1);
	if (philo->report_status == SEM_FAILED)
		return (free_semaphore(philo, ERROR_SEMAPHORE, 2));
	philo->pid = malloc(sizeof(pid_t) * philo->number);
	if (!philo->pid)
	{
		sem_close(philo->report_status);
		sem_close(philo->forks_status);
		return (free_semaphore(philo, ERROR_SEMAPHORE, 3));
	}
	return (OK);
}
