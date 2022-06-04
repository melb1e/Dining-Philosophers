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
		if (philo->meals_goal)
			if (philo->meals_goal == philo->meals_done)
				break ;
		if (ft_timestamp() - philo->last_ate >= philo->time_to_die)
		{
			philo->dead = 1;
			display_status(philo, philo->id, PHILO_DEAD);
			break ;
		}
	}
	if (philo->dead)
		exit(EXIT_FAILURE);
	else
		exit(0);
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

void	display_status(t_philos *philo, int id, char *action)
{
	sem_wait(philo->report_status);
	printf("%li %i %s\n", ft_timestamp() - philo->timestamp, id + 1, action);
	if (ft_strcmp(action, PHILO_DEAD))
		sem_post(philo->report_status);
}

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

static int	kill_children(t_philos *philo)
{
	int	i;

	i = 0;
	while (i < philo->number)
		kill(philo->pid[i++], SIGKILL);
	return (OK);
}

int	thread_master(t_philos *philo)
{
	int	i;
	int status;

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
			if (kettle(philo) > 0)
				return (0);
		}
	}
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFSIGNALED(status) || WIFEXITED(status))
			return (kill_children(philo));
	}
	return (OK);
}

/*
**	Create semaphoress
*/
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

/*
**	Initialize installments
*/

t_philos	*initialization(int ac, char **av)
{
	t_philos	*philo;
	int		i;

	i = 1;
	philo = malloc(sizeof(t_philos));
	if (philo == NULL)
		return (NULL);
	philo->number = ft_atoi(av[i++]);
	philo->time_to_die = ft_atoi(av[i++]);
	philo->time_to_eat = ft_atoi(av[i++]);
	philo->time_to_sleep = ft_atoi(av[i]);
	if (ac - 1 == P_MAX_ARGS)
		philo->meals_goal = ft_atoi(av[++i]);
	else if (ac - 1 == P_MIN_ARGS)
		philo->meals_goal = -1;
	philo->id = 0;
	philo->meals_done = 0;
	philo->dead = 0;
	philo->timestamp = 0;
	philo->last_ate = 0;
	return (philo);
}

/*
**	Check arguments for errors
*/
static	int	ft_overflow(unsigned long long nbr, int sign)
{
	if (nbr > ULLONG_MAX && sign == -1)
		return (ERROR_OVERFLOW);
	else if ((nbr > 2147483647 && sign == 1) || (nbr > 2147483648 && sign == -1))
		return (ERROR_OVERFLOW);
	return (nbr * sign);
}

int	ft_atoi(char *str)
{
	unsigned long long	nbr;
	long long			sign;
	int				i;

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

int	scan_args(int ac, char **av)
{
	if (ac - 1 <= P_MAX_ARGS && ac - 1 >= P_MIN_ARGS)
		if (ft_atoi(av[1]) > 0 && ft_atoi(av[2]) > 0 && \
			ft_atoi(av[3]) > 0 && ft_atoi(av[4]) > 0 &&\
			(ac - 1 == P_MIN_ARGS || \
			(ac - 1 == P_MAX_ARGS && ft_atoi(av[5]) > 0)))
			return (OK);
	return (ERROR_INPUT);
}

/*
**	Main function
*/
int main(int ac, char **av)
{
	t_philos		*philo;
	int			e_status;

	philo = NULL;
	e_status = scan_args(ac, av);
	if (e_status == OK)
	{
		philo = initialization(ac, av);
		if (philo == NULL)
			return (ft_error(philo, ERROR_INITIALIZATION, 3));
		if (create_semaphores(philo) != OK)
			return (ft_error(philo, ERROR_SEMAPHORE, 3));
		e_status = thread_master(philo);
		if (e_status != OK)
			return (ft_error(philo, e_status, 3));
	}
	else
		return (ft_error(NULL, e_status, 1));
	return (OK);
}
