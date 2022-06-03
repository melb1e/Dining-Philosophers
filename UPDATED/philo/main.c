#include "philo.h"

/*
**	Death checker function
*/

void	*death_checker(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	while (!philo->installments->death_status)
	{
		if (!philo->philo_eat && ft_timestamp() - philo->last_ate >= \
			philo->installments->time_to_die)
		{
			pthread_mutex_lock(&philo->eat_status);
			display_status(philo->installments, philo->id, PHILO_DEAD);
			philo->installments->death_status = 1;
			pthread_mutex_unlock(&philo->eat_status);
		}
		if (philo->installments->philos[philo->installments->number - 1]\
			->meals_done == philo->installments->meals_goal)
			philo->installments->death_status = 1;
		usleep(100);
	}
	return (NULL);
}

/*
**	Thread kettle functions
*/
static int	ft_strcmp(char *str1, char *str2)
{
	size_t	i;

	i = 0;
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
	pthread_mutex_lock(&inst->report_status);
	printf("%li %li %s\n", ft_timestamp() - inst->timestamp, id + 1, status);
	if (ft_strcmp(status, PHILO_DEAD))
		pthread_mutex_unlock(&inst->report_status);
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
	pthread_mutex_lock(&philo->installments->forks[philo->left_fork_id]);
	display_status(philo->installments, philo->id, PHILO_HAS_LEFT_FORK);
	pthread_mutex_lock(&philo->installments->forks[philo->right_fork_id]);
	display_status(philo->installments, philo->id, PHILO_HAS_RIGHT_FORK);
	pthread_mutex_lock(&philo->eat_status);
	philo->last_ate = ft_timestamp();
	philo->philo_eat = 1;
	display_status(philo->installments, philo->id, PHILO_EATING);
	usleep(philo->installments->time_to_eat);
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

int	thread_master(t_inst *inst)
{
	int	i;

	i = 0;
	inst->timestamp = ft_timestamp();
	while (i < inst->number)
	{
		inst->philos[i]->last_ate = ft_timestamp();
		if (pthread_create(&inst->philos[i]->thread, NULL, &kettle, \
			(void *)inst->philos[i]))
			return (ERROR_THREADS);
		i++;
		usleep(100);
	}
	i = 0;
	while (i < inst->number)
	{
		if (pthread_create(&inst->philos[i]->dead, NULL, &death_checker, \
			(void *)inst->philos[i]))
			return (ERROR_THREADS);
		i++;
		usleep(100);
	}
	while (!inst->death_status)
		continue ;
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
	philos = (t_philos **)malloc(sizeof(t_philos *) * inst->number + 1);
	if (philos == NULL)
		return (NULL);
	while (i < inst->number)
	{
		philos[i] = (t_philos *)malloc(sizeof(t_philos));
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

pthread_mutex_t	*create_forks(t_inst *inst)
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
	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * inst->number);
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

int	ft_atoi(const char *str)
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