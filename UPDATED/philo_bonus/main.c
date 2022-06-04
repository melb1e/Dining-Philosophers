#include "philo.h"

/*
**	Death checker function
*/

void	*death_checker(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	while (TRUE)
	{
		sem_wait(philo->philo_eat);
		if (ft_timestamp() - philo->last_ate >= philo->installments->time_to_die)
		{
			display_status(philo->installments, philo->id, PHILO_DEAD);
			exit(EXIT_FAILURE);
		}
		sem_post(philo->philo_eat);
		usleep(100);
	}
	return (NULL);
}

void	*meals_checker(void *arg)
{
	t_inst	*inst;
	int		meals_done;
	int		i;

	inst = (t_inst *)arg;
	meals_done = 0;
	while (meals_done < inst->meals_goal)
	{
		i = 0;
		while (i < inst->number)
		{
			sem_wait(inst->eat_status);
			i++;
		}
		meals_done += 1;
	}
	sem_wait(inst->report_status);
	i = 0;
	while (i < inst->number)
		kill(inst->philos[i]->pid, SIGKILL);
	return (NULL);
}

/*
**	Thread kettle functions
*/
static int	ft_strcmp(char *str1, char *str2)
{
	size_t	i;

	i = 0;
	if ((!str1 && str2) || (!str2 && str1))
		return (ERROR);
	while (str1[i] && str2[i])
	{
		if (str1[i]== str2[i])
			i++;
		else if (str1[i] != str2[i])
			return (ERROR);
	}
	return (OK);
}

void	display_status(t_inst *inst, size_t id, char *status)
{
	sem_wait(inst->report_status);
	printf("%li %li %s\n", ft_timestamp() - inst->timestamp, id + 1, status);
	if (ft_strcmp(status, PHILO_DEAD))
		sem_post(inst->report_status);
}

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
	usleep(philo->installments->time_to_sleep);
	while (ft_timestamp() - time < philo->installments->time_to_sleep)
		continue ;
	return ;
}

static void	philo_eat(t_philos *philo)
{
	sem_wait(philo->installments->forks);
	display_status(philo->installments, philo->id, PHILO_HAS_LEFT_FORK);
	sem_wait(philo->installments->forks);
	display_status(philo->installments, philo->id, PHILO_HAS_RIGHT_FORK);
	sem_wait(philo->philo_eat);
	display_status(philo->installments, philo->id, PHILO_EATING);
	philo->last_ate = ft_timestamp();
	usleep(philo->installments->time_to_eat);
	while (ft_timestamp() - philo->last_ate < philo->installments->time_to_eat)
		continue ;
	sem_post(philo->philo_eat);
	sem_post(philo->installments->forks);
	sem_post(philo->installments->forks);
	sem_post(philo->installments->eat_status);
	return ;
}

void	*kettle(t_philos *philo)
{
	while (TRUE)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
		usleep(100);
	}
	return (NULL);
}

/*
**	Master function with threads
*/
time_t	ft_timestamp(void)
{
	struct timeval	time;
	time_t			ms;

	gettimeofday(&time, NULL);
	ms = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (ms);
}

void	kill_children(t_inst *inst)
{
	int	i;
	int	j;
	int	status;

	i = 0;
	while (i < inst->number)
	{
		j = 0;
		waitpid(-1, &status, 0);
		if (WIFSIGNALED(status) || WIFEXITED(status))
			while (j < inst->number)
				kill(inst->philos[j++]->pid, SIGKILL);
		i++;
	}
	return ;
}

int	thread_master(t_inst *inst)
{
	int	i;

	i = 0;
	if (inst->meals_goal < -1 && pthread_create(&inst->meals_done, \
		NULL, &meals_checker, (void *)inst))
		return (ERROR_THREADS);
	inst->timestamp = ft_timestamp();
	while (i < inst->number)
	{
		inst->philos[i]->pid = fork();
		inst->philos[i]->last_ate = ft_timestamp();
		if (inst->philos[i]->pid == 0)
		{
			if (pthread_create(&inst->philos[i]->dead, NULL, &death_checker, \
				(void *)inst->philos[i]))
				return (ERROR_THREADS);
			kettle(inst->philos[i]);
			exit(1);
		}
		usleep(100);
		i++;
	}
	kill_children(inst);
	return (OK);
}

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

t_philos	**create_philos(t_inst *inst)
{
	t_philos	**philos;
	int			i;

	i = 0;
	philos = (t_philos **)malloc(sizeof(t_philos *) * inst->number);
	if (philos == NULL)
		return (NULL);
	while (i < inst->number)
	{
		philos[i] = (t_philos *)malloc(sizeof(t_philos));
		if (philos[i] == NULL)
			return (free_philos(philos));
		sem_unlink("/eat");
		philos[i]->philo_eat = sem_open("/eat", O_CREAT, S_IRWXU, 1);
		if (inst->report_status == SEM_FAILED)
			return (NULL);
		philos[i]->installments = inst;
		philos[i]->id = i;
		philos[i]->meals_done = 0;
		i++;
	}
	return (philos);
}

/*
**	Create semaphoress
*/
int	create_semaphores(t_inst *inst)
{
	if (inst->number <= ERROR_OVERFLOW || \
	inst->meals_goal < -1 || \
	inst->time_to_die <= ERROR_OVERFLOW || \
	inst->time_to_eat <= ERROR_OVERFLOW || \
	inst->time_to_sleep <= ERROR_OVERFLOW)
		return (ERROR_INPUT);
	sem_unlink("/forks");
	inst->forks = sem_open("/forks", O_CREAT, S_IRWXU, inst->number);
	if (inst->forks == SEM_FAILED)
		return (ERROR_SEMAPHORE);
	sem_unlink("/report");
	inst->report_status = sem_open("/report", O_CREAT, S_IRWXU, 1);
	if (inst->report_status == SEM_FAILED)
		return (ERROR_SEMAPHORE);
	sem_unlink("/meals_done");
	inst->eat_status = sem_open("/meals_done", O_CREAT, S_IRWXU, 1);
	if (inst->eat_status == SEM_FAILED)
		return (ERROR_SEMAPHORE);
	sem_unlink("/die");
	inst->death_status = sem_open("/die", O_CREAT, S_IRWXU, 1);
	if (inst->death_status == SEM_FAILED)
		return (ERROR_SEMAPHORE);
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
	inst = (t_inst *)malloc(sizeof(t_inst));
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
	if (create_semaphores(inst) != OK)
		return (NULL);
	inst->philos = create_philos(inst);
	if (inst->philos == NULL || inst->number == 0)
		return (NULL);
	return (inst);
}

/*
**	Check arguments for errors
*/
static	int	ft_overflow(unsigned long nbr, int sign)
{
	if (sign == -1)
		return (ERROR_OVERFLOW);
	else if ((nbr > 2147483647 && sign == 1) || nbr > 2147483648)
		return (ERROR_OVERFLOW);
	return (nbr * sign);
}

int	ft_atoi(const char *str)
{
	unsigned long	nbr;
	long			sign;
	size_t			i;

	i = 0;
	nbr = 0;
	sign = 1;
	while (str[i] >= 8 && str[i] <= 32)
	{
		if (str[i] == 27)
			return (ERROR);
		i++;
	}
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while(str[i] >= '0' && str[i] <= '9')
		nbr = nbr * 10 + str[i++] - '0';
	return (ft_overflow(nbr, sign));
}

static int	ft_isnumeric(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != EOL)
	{
		if (str[i] <= '0' || str[i] >= '9')
			return (ERROR);
		i++;
	}
	return (OK);
}

int	scan_args(const int ac, const char **av)
{
	int	i;

	i = 0;
	if (ac - 1 > MAX_ARGS || ac - 1 < MIN_ARGS)
		return (ERROR_INPUT);
	while (i < (int)ac)
	{
		if (av[i][0] == '-' && ft_isnumeric(av[i]) != OK)
			return (ERROR_INPUT);
		i++;
	}
	return (OK);
}

/*
**	Main function
*/
int main(const int ac, const char **av)
{
	t_inst		*inst;
	long		e_status;

	inst = NULL;
	e_status = scan_args(ac, av);
	if (e_status == OK)
	{
		inst = initialization(ac, av);
		if (inst == NULL)
			return (ft_error(ERROR_INITIALIZATION));
		e_status = thread_master(inst);
		if (e_status != OK)
			return (ft_error(e_status));
	}
	else
		return (ft_error(e_status));
	return (OK);
}
